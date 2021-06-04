
target_sources (test_mario_kart PRIVATE
        "main.cpp"
        "MarioKart.cpp"
        "RaceState.cpp"
        "mode7.cpp"
        "MapFileCollision.cpp"
        "WelcomeState.cpp"
        "MenuState.cpp"
        "helpState.cpp"
        "GetDataState.cpp")

add_subdirectory(Machine)
add_subdirectory(GameObjects)
add_subdirectory(RessourcesClasses)
add_subdirectory(Models)
