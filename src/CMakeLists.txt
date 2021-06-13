
target_sources (test_mario_kart PRIVATE
        "main.cpp"
        "MarioKart.cpp"
        "RaceState.cpp"
        "mode7.cpp"
        "MapFileCollision.cpp"
        "WelcomeState.cpp"
        "MenuState.cpp"
        "helpState.cpp"
        "GetDataState.cpp"
		"ShowUsersDataBase.cpp"
        "SettingsState.cpp"
        "StateOfMenu.cpp"
		"Utilities.cpp"
		"CollisionHandling.cpp"
		"HostState.cpp"
		"Animation.cpp"
		"Services.cpp"
		"CareerState.cpp"
        "GameStatusBar.cpp"
        "UserCareer.cpp")

add_subdirectory(Machine)
add_subdirectory(GameObjects)
add_subdirectory(RessourcesClasses)
add_subdirectory(Models)
add_subdirectory(States)
