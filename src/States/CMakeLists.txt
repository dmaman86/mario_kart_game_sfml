target_sources(test_mario_kart PRIVATE "CareerMenu.cpp"
	                                   "CareerState.cpp"
									   "GarageState.cpp"
		                               "GetDataState.cpp"
									   "helpState.cpp"
									   "HostState"
									   "MenuState.cpp"
		                               "SettingsState.cpp"
									   "ShowUsersDataBase.cpp"
                                       "StateOfMenu.cpp"
							           "WelcomeState.cpp"
			                           "AboutState.cpp")

add_subdirectory(RaceModes)