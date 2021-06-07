#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "Pipe.h"
#include "Player.h"

namespace // anonymous namespace — the standard way to make function "static"
{

// primary collision-processing functions
void PlayerPipe(GameObj& player,
	GameObj& pipe)
{
    // To get the actual types and use them:
	Player& Pl = dynamic_cast<Player&>(player);
	Pipe&  pi  = dynamic_cast<Pipe&>(pipe);

	Pl.driveBack();
}

//...

// secondary collision-processing functions that just
// implement symmetry: swap the parameters and call a
// primary function
void PipePlayer(GameObj& Pipe,
	GameObj& Player)
{
	PlayerPipe(Player,Pipe);
}
//...

using HitFunctionPtr = void (*)(GameObj&, GameObj&);
// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Player   ), typeid(Pipe    ))] = &PlayerPipe;
    phm[Key(typeid(Pipe), typeid(Player))] = &PipePlayer;
    //...
    return phm;
}

HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

} // end namespace

void processCollision(GameObj& object1, GameObj& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
