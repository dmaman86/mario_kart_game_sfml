target_sources (test_mario_kart PRIVATE
        "main.cpp"
        "MarioKart.cpp"
        "TestState.cpp"
        "RaceState.cpp"
        "Player.cpp"
        "RessourcesClasses/Fonts.cpp"
        "RessourcesClasses/Pictures.cpp"
        "RessourcesClasses/Sounds.cpp"
        "mode7.cpp")

add_subdirectory(Machine)