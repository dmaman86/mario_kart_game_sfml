add_subdirectory(Pictures)
add_subdirectory(Sounds)
add_subdirectory(Maps)
add_subdirectory(Drivers)
add_subdirectory(Fonts)

configure_file("logo.jpeg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file("uml-mario-kart.png" ${CMAKE_BINARY_DIR} COPYONLY)
