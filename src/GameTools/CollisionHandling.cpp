#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>
#include "Floor.h"
#include "Pipe.h"
#include "Banana.h"
#include "Mushroom.h"
#include "Ghost.h"
#include "Coin.h"
#include "Player.h"
#include "PlayerOnline.h"

namespace // anonymous namespace — the standard way to make function "static"
{

	void PlayerSpeedMultiplier(Object& player, Object& speedMultiplier)
	{
		Player& Pl = dynamic_cast<Player&>(player);
		Mushroom& Bn = dynamic_cast<Mushroom&>(speedMultiplier);
		if (Bn.getIsActive())
			Pl.DriveFast();
		Bn.setIsActive(false);
	}
//=============================================================================

	void SpeedMultiplierPlayer(Object& Multiplier, Object& Player)
	{
		PlayerSpeedMultiplier(Player, Multiplier);
	}


//=============================================================================

	void PlayerBanana(Object& player, Object& banana)
	{
		Player& Pl = dynamic_cast<Player&>(player);
        Banana& Bn = dynamic_cast<Banana&>(banana);
        if(Bn.getIsActive())
            Pl.SpinDriver();
        Bn.setIsActive(false);
	}
//=============================================================================

	void BananaPlayer(Object& Banana,
		Object& Player)
	{
		PlayerBanana(Player, Banana);
	}
//=============================================================================

	void PlayerGhost(Object& player, Object& ghost)
	{
		Player& Pl = dynamic_cast<Player&>(player);
		Ghost& gh = dynamic_cast<Ghost&>(ghost);
		if (gh.getIsActive())
			Pl.DriveSmaller();
		gh.setIsActive(false);
	}
//=============================================================================

	void GhostPlayer(Object& Ghost,
		Object& Player)
	{
		PlayerGhost(Player, Ghost);
	}
//=============================================================================

	void PlayerCoin(Object& player, Object& coin)
	{
		Player& Pl = dynamic_cast<Player&>(player);
		Coin& co = dynamic_cast<Coin&>(coin);
		if (co.getIsActive())
			co.addCollected();
		co.setIsActive(false);
	}
//=============================================================================

	void CoinPlayer(Object& coin, Object& Player)
	{
		PlayerCoin(Player, coin);
	}
//=============================================================================

	// primary collision-processing functions
	void PlayerPipe(Object& player,Object& pipe)
	{
		// To get the actual types and use them:
		Player& Pl = dynamic_cast<Player&>(player);

		Pl.DriveBack();
	}
//=============================================================================

	void PlayerPlayerOnline(Object& player,Object& player2)
    {

    }



void PipePlayer(Object& Pipe,
	Object& Player)
{
	PlayerPipe(Player,Pipe);
}
//=============================================================================

void PlayerFloorAsphalt(Object& player,
	Object& floor_asphalt)
{
	// To get the actual types and use them:
	Player& Pl = dynamic_cast<Player&>(player);
	Pl.setCoefficientOfFriction(1);
}
//=============================================================================

void PlayerFloorBrick(Object& player,
	Object& floorbrick)
{
	// To get the actual types and use them:
	Player& Pl = dynamic_cast<Player&>(player);
	Pl.setCoefficientOfFriction(2);
	Pl.DriveBack();
}
//=============================================================================

void PlayerFloorSand(Object& player,
	Object& floorsand)
{
	// To get the actual types and use them:
	Player& Pl = dynamic_cast<Player&>(player);
	Pl.setCoefficientOfFriction(2);

}
//=============================================================================

using HitFunctionPtr = void (*)(Object&, Object&);
// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;
//=============================================================================

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Player), typeid(Pipe))] = &PlayerPipe;
    phm[Key(typeid(Pipe), typeid(Player))] = &PipePlayer;
	
	phm[Key(typeid(Player), typeid(Banana))] = &PlayerBanana;
	phm[Key(typeid(Banana), typeid(Player))] = &BananaPlayer;
	
	phm[Key(typeid(Player), typeid(Ghost))] = &PlayerGhost;
	phm[Key(typeid(Ghost), typeid(Player))] = &GhostPlayer;

	phm[Key(typeid(Player), typeid(Coin))] = &PlayerCoin;
	phm[Key(typeid(Coin), typeid(Player))] = &CoinPlayer;
	
	phm[Key(typeid(Player), typeid(Mushroom))] = &PlayerSpeedMultiplier;
	phm[Key(typeid(Mushroom), typeid(Player))] = &SpeedMultiplierPlayer;

    phm[Key(typeid(Player), typeid(PlayerOnline))] = &PlayerPlayerOnline;
    phm[Key(typeid(PlayerOnline), typeid(Player))] = &PlayerPlayerOnline;

	phm[Key(typeid(Player), typeid(FloorAsphalt))] = &PlayerFloorAsphalt;
	phm[Key(typeid(Player), typeid(FloorBrick))] = &PlayerFloorBrick;
	phm[Key(typeid(Player), typeid(FloorSand))] = &PlayerFloorSand;
    //...
    return phm;
}
//=============================================================================

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
//=============================================================================

void processCollision(Object& object1, Object& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
//=============================================================================
