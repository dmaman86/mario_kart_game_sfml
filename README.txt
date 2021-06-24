	OOP 2 Course - Super Mario kart
=========================================================================
Name: David Maman, Id: 327437422
Name: Daniel Cohen, Id: 311551386
Name: Liron Hatabi, Id: 315711242
Name: Liran Mizrahi, Id: 207902909
=========================================================================
General Explanation:


=========================================================================
Design:


=========================================================================
List of files:

CMakeLists.txt
README.txt

File external:
CMakeLists.txt
Boost library

File include:
* Button.h              * Services.h
* CMakeLists.txt        * Utilities.h
* Macros.h              * MarioKart.h

1. GameObjects File:
* Banana.h              * Ghost.h               * Player.h
* CMakeLists.txt        * MacrosGameObj.h       * PlayerBase.h
* Coin.h                * Mushroom.h            * PlayerOnline.h
* Floor.h               * Object.h              * StaticObject.h
* GameObj.h             * Pipe.h

2. GameTools file:
* Animation.h           * GameStatusBar.h
* Board.h               * mode7.h
* Camera.h              * SkyLine.h
* CMakeLists.txt        * SpeedScreen.h
* CollisionHandling.h

3. GuiItems
* CMakeLists.txt
* StartCloud.h
* TraficLight.h

4. Machine
* CMakeLists.txt
* State.h
* StateStack.h

5. Models
* CMakeLists.txt
* User.h

6. ResourcesClasses
* CMakeLists.txt
* Fonts.h
* Pictures.h
* Sounds.h

7. States
* AboutState.h          * GetDataState.h        * ShowUsersDataBase.h
* CareerMenu.h          * helpState.h           * StateOfMenu.h
* CareerState.h         * HostState.h           * WelcomeState.h
* CMakeLists.txt        * MenuState.h
* GarageState.h         * SettingsState.h

7.1 RaceModes
* CMakeLists.txt
* CoinRace.h
* DriftKingRace.h
* OnlineRace.h
* RaceStatesBase.h
* TimeRace.h


File resources:
* Drivers pictures
* Fonts
* Maps pictures and txt
* Pictures
* Sounds
* CMakeLists.txt

File src:
	like include file but here cpp files

=========================================================================
Data Structures:


=========================================================================
Algorithms:


=========================================================================
Known bugs:


=========================================================================
Other:
