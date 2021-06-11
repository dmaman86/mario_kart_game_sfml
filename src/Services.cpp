#include "Services.h"

Services::Services(): m_http(HttpNetwork::url),
                      m_request_post(),
                      m_request_put(),
                      m_request_del(),
                      m_request_get(),
                      m_ostream(),
                      m_stream(),
                      m_response()
{

}

Services::~Services()
{

}

bool Services::createUser( UserNetwork* user)
{
    m_ostream.str("");
    m_ostream.clear();
    m_request_post.setMethod(sf::Http::Request::Post);
    m_request_post.setUri(HttpNetwork::path_user );

    m_ostream << "name=" << user->getName() << "&sprite=" << user->getSprite()
              << "&host=" << user->getIfHost() << "&map=" << user->getMapGame();
    m_request_post.setBody( m_ostream.str() );

    m_response = m_http.sendRequest( m_request_post );

    if( m_response.getStatus() != sf::Http::Response::Created ||
        m_response.getStatus() == sf::Http::Response::Unauthorized)
        return false;

    m_stream << m_response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setId( pt.get<std::string>("id") );
    return true;
}

bool Services::getUser( UserNetwork* user, const std::string idOther )
{
    m_stream.str("");
    m_stream.clear();
    m_request_get.setMethod(sf::Http::Request::Get);
    m_request_get.setUri(HttpNetwork::path_user + "/" + idOther );

    m_response = m_http.sendRequest( m_request_get );

    if( m_response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << m_response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setId(idOther);
    user->setIdOther(pt.get<std::string>("idOther"));
    user->setSprite( pt.get<std::string>("sprite") );
    user->setName( pt.get<std::string>("name") );
    return true;
}

bool Services::updateUser(UserNetwork* user)
{
    m_ostream.str("");
    m_ostream.clear();
    m_request_put.setMethod( sf::Http::Request::Put );
    m_request_put.setUri( HttpNetwork::path_user + "/" + user->getId() );

    m_ostream << "name=" << user->getName() << "&sprite=" << user->getSprite()
              << "&host=" << user->getIfHost() << "&map=" << user->getMapGame();
    m_request_put.setField("Content-Type", "application/x-www-form-urlencoded");
    m_request_put.setBody(m_ostream.str());

    m_response = m_http.sendRequest( m_request_put );

    if( m_response.getStatus() != sf::Http::Response::Ok )
    {
        //std::cout << m_response.getBody() << std::endl;
        return false;
    }
    return true;
}

bool Services::deleteUser(UserNetwork* user)
{
    m_request_del.setMethod(sf::Http::Request::Delete);
    m_request_del.setUri(HttpNetwork::path_user + "/" + user->getId() );

    m_response = m_http.sendRequest( m_request_del );

    if( m_response.getStatus() != sf::Http::Response::Ok )
        return false;
    return true;
}

bool Services::createRace(UserNetwork * user)
{
    m_ostream.str("");
    m_ostream.clear();
    m_request_put.setMethod( sf::Http::Request::Put );
    m_request_put.setUri( "/app/api/create_race/" + user->getId() );
    m_request_put.setField("Content-Type", "application/x-www-form-urlencoded");
    m_ostream << "idOther=" << user->getOtherId();
    m_request_put.setBody( m_ostream.str() );
    m_response = m_http.sendRequest( m_request_put );
    if( m_response.getStatus() != sf::Http::Response::Ok )
    {
        //std::cout << m_response.getBody() << std::endl;
        return false;
    }
    return true;
}

bool Services::getIdOtherUser(UserNetwork * user)
{
    m_stream.str("");
    m_stream.clear();
    m_request_get.setMethod(sf::Http::Request::Get);
    m_request_get.setUri(HttpNetwork::path_user + "/" + user->getId() );

    m_response = m_http.sendRequest( m_request_get );

    if( m_response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << m_response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setIdOther( pt.get<std::string>("idOther") );
    return true;
}

bool Services::getUsers(std::vector<UserNetwork> & users, const std::string id)
{
    m_stream.str("");
    m_stream.clear();
    m_request_get.setMethod( sf::Http::Request::Get );
    m_request_get.setUri( HttpNetwork::path_user );
    users.clear();

    m_response = m_http.sendRequest( m_request_get );

    if( m_response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << m_response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("users"))
                {
                    assert(v.first.empty()); // array elements have no names
                    buildVecUsers(users, id, v.second);
                }
    return true;
}

void Services::buildVecUsers( std::vector<UserNetwork>& users, const std::string id, boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    std::vector< std::string > values;
    for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        values.emplace_back( it->second.get_value<std::string>() );
    }
    if( values[0] != id )
    {
        UserNetwork user( values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ] );
        std::stringstream ss(values[4]);
        bool game = false;
        ss >> game;
        user.updateInGame(game);
        users.emplace_back( user );
    }
}

bool Services::updatePosition( std::string id, PlayerBase player )
{
    m_ostream.str("");
    m_ostream.clear();
    m_request_put.setMethod( sf::Http::Request::Put );
    m_request_put.setUri( HttpNetwork::path_player + "/" + id );

    m_ostream << "positionX=" << player.getLocation().x
              << "&positionY=" << player.getLocation().y;
    m_request_put.setField("Content-Type", "application/x-www-form-urlencoded");
    m_request_put.setBody(m_ostream.str());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return m_http.sendRequest(m_request_put).getStatus() == sf::Http::Response::Ok;
}

bool Services::getPosition( std::string idOther, PlayerBase* player )
{
    m_stream.str("");
    m_stream.clear();
    m_request_get.setMethod(sf::Http::Request::Get);
    m_request_get.setUri(HttpNetwork::path_player + "/" + idOther );

    m_response = m_http.sendRequest( m_request_get );
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    if( m_response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << m_response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    // player->getLocation().x = pt.get<float>("positionX");
    // player->getLocation().y = pt.get<float>("positionY");
    player->setLocation( pt.get<float>("positionX"), pt.get<float>("positionY") );
    return true;
}