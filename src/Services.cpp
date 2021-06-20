#include "Services.h"

Services::Services(): m_ostream(),
                      m_stream()
{

}

Services::~Services()
{

}

bool Services::createUser(User* user)
{
    m_ostream.str("");
    m_ostream.clear();
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_post(HttpNetwork::path_user, sf::Http::Request::Post);

    m_ostream << "name=" << user->getName() << "&sprite=" << user->getSprite()
              << "&host=" << user->getIfHost() << "&map=" << user->getMapGame();
    request_post.setBody( m_ostream.str() );

    response = http.sendRequest( request_post );
    if( response.getStatus() != sf::Http::Response::Created ||
        response.getStatus() == sf::Http::Response::Unauthorized)
        return false;

    m_stream << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setId( pt.get<std::string>("id") );
    return true;
}

bool Services::getUser(User* user, const std::string idOther )
{
    m_stream.str("");
    m_stream.clear();
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_get(HttpNetwork::path_user + "/" + idOther, sf::Http::Request::Get);

    response = http.sendRequest( request_get );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setId(idOther);
    user->setIdOther(pt.get<std::string>("idOther"));
    user->setSprite( pt.get<std::string>("sprite") );
    user->setName( pt.get<std::string>("name") );
    return true;
}

bool Services::updateUser(User* user)
{
    m_ostream.str("");
    m_ostream.clear();

    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_put(HttpNetwork::path_user + "/" + user->getId(), sf::Http::Request::Put);

    m_ostream << "name=" << user->getName() << "&sprite=" << user->getSprite()
              << "&host=" << user->getIfHost() << "&map=" << user->getMapGame()
              << "&idOther=" << user->getOtherId();
    request_put.setField("Content-Type", "application/x-www-form-urlencoded");
    request_put.setBody(m_ostream.str());

    response = http.sendRequest( request_put );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;
    return true;
}

bool Services::deleteUser(User* user)
{
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_del(HttpNetwork::path_delete + user->getId(), sf::Http::Request::Put);
    request_del.setField("Content-Type", "application/x-www-form-urlencoded");

    response = http.sendRequest( request_del );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;
    user->setId("");
    user->setIdOther("");
    user->updateInGame(false);
    return true;
}

bool Services::resetUser(User *user)
{
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_reset(HttpNetwork::path_reset + user->getId(), sf::Http::Request::Put);
    request_reset.setField("Content-Type", "application/x-www-form-urlencoded");

    response = http.sendRequest( request_reset );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;
    user->setIdOther("");
    user->updateInGame(false);
    return true;
}

bool Services::createRace(User * user)
{
    m_ostream.str("");
    m_ostream.clear();
    m_stream.str("");
    m_stream.clear();
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_put(HttpNetwork::path_createRace + user->getId(), sf::Http::Request::Put);

    request_put.setField("Content-Type", "application/x-www-form-urlencoded");
    m_ostream << "idOther=" << user->getOtherId();
    request_put.setBody( m_ostream.str() );
    response = http.sendRequest( request_put );
    if( response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setMapGame( pt.get<std::string>("map") );

    return true;
}

bool Services::getIdOtherUser(User * user)
{
    m_stream.str("");
    m_stream.clear();
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_get(HttpNetwork::path_user + "/" + user->getId(), sf::Http::Request::Get);

    response = http.sendRequest( request_get );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);
    user->setIdOther( pt.get<std::string>("idOther") );
    return true;
}

bool Services::getUsers(std::vector<User> & users, const std::string id)
{
    m_stream.str("");
    m_stream.clear();
    sf::Http http(HttpNetwork::url);
    sf::Http::Response response;
    sf::Http::Request request_get( HttpNetwork::path_user, sf::Http::Request::Get);

    users.clear();

    response = http.sendRequest( request_get );

    if( response.getStatus() != sf::Http::Response::Ok )
        return false;

    m_stream << response.getBody();
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(m_stream, pt);

    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("users"))
                {
                    assert(v.first.empty()); // array elements have no names
                    buildVecUsers(users, id, v.second);
                }
    return true;
}

void Services::buildVecUsers(std::vector<User>& users, const std::string id, boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    std::vector< std::string > values;
    for (ptree::const_iterator it = pt.begin(); it != pt.end(); ++it)
    {
        values.emplace_back( it->second.get_value<std::string>() );
    }
    if( values[0] != id )
    {
        User user(values[ 0 ], values[ 1 ], values[ 2 ], values[ 3 ] );
        std::stringstream ss(values[4]);
        bool game = false;
        ss >> game;
        user.updateInGame(game);
        users.emplace_back( user );
    }
}

void Services::updatePosition(User* user, PlayerBase* player, std::mutex* mutex, bool* finish )
{
    static int f = 0;
    sf::Http::Response local_response;
    sf::Http::Request request_put(HttpNetwork::path_player + "/" + user->getId(), sf::Http::Request::Put);
    sf::Http http(HttpNetwork::url);
    request_put.setField("Content-Type", "application/x-www-form-urlencoded");

    while( f < 1 )
    {
        m_ostream.str("");
        m_ostream.clear();

        m_ostream << "positionX=" << player->getLocation().x
                  << "&positionY=" << player->getLocation().y;
        request_put.setBody(m_ostream.str());
        local_response = http.sendRequest( request_put );
       // std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if(*finish)
            return;
        mutex->lock();
        if(local_response.getStatus() != sf::Http::Response::Ok )
            user->setOnline(false);
        mutex->unlock();
    }
}

void Services::getPosition(User* otherUser, PlayerBase* player, std::mutex* mutex, bool* finish )
{
    static int i = 0;
    sf::Http::Response local_response;
    sf::Http::Request request(HttpNetwork::path_player + "/" + otherUser->getId(), sf::Http::Request::Get);
    sf::Http http(HttpNetwork::url);
    while( i < 1 )
    {
        m_stream.str("");
        m_stream.clear();

        local_response = http.sendRequest( request );
       // std::this_thread::sleep_for(std::chrono::milliseconds(5));
        if(*finish)
            return;
        mutex->lock();
        if( local_response.getStatus() != sf::Http::Response::Ok )
            otherUser->setOnline(false);
        else
        {
			player->updateLastLocation();
            m_stream << local_response.getBody();
            boost::property_tree::ptree pt;
            boost::property_tree::read_json(m_stream, pt);
            auto x = pt.get<float>("positionX");
            auto y = pt.get<float>("positionY");
            player->setLocation(sf::Vector2f(x, y));
        }
        mutex->unlock();
    }
}