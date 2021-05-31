
target_sources (test_mario_kart PRIVATE
        "main.cpp"
        "MarioKart.cpp"
        "TestState.cpp"
        "RaceState.cpp"
        "mode7.cpp"
        "MapFileCollision.cpp")

add_subdirectory(Machine)
add_subdirectory(GameObjects)
add_subdirectory(RessourcesClasses)
