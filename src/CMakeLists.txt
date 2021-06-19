target_sources (test_mario_kart PRIVATE
		"Button.cpp"
		"main.cpp"
        "MarioKart.cpp"
		"Services.cpp"
		"Utilities.cpp"
		)

add_subdirectory(GameObjects)
add_subdirectory(GameTools)
add_subdirectory(GuiItems)
add_subdirectory(Machine)
add_subdirectory(Models)
add_subdirectory(RessourcesClasses)
add_subdirectory(States)