cmake_minimum_required(VERSION 3.20)

project(RPGGameSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	RPGGameSystem.cpp
	Character/Character.cpp
	Combat/TurnbasedCombat.cpp
	Core/LoadExternalData.cpp
	Creation/CharacterCreation.cpp
	Inventory/Crafting.cpp
	Inventory/Inventory.cpp
	Inventory/Items.cpp
	UI/CharacterCreationScreen/CharacterCreationScreen.cpp
	UI/GameScreen/GameScreen.cpp
	UI/StartScreen/StartScreen.cpp
)

add_executable(RPGGameSystem ${SOURCES}
)

set(SFML_ROOT "" CACHE PATH "Path to SFML 2.6.2")
set(SFML_DIR "${SFML_ROOT}/lib/cmake")

find_package(SFML 2.6 COMPONENTS graphics window audio system REQUIRED)

target_include_directories(RPGGameSystem PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${SFML_ROOT}/include"
)

target_link_libraries(RPGGameSystem PRIVATE
	sfml-graphics
	sfml-window
	sfml-system
	sfml-audio
)

set_target_properties(RPGGameSystem PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

add_custom_command(TARGET RPGGameSystem POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${SFML_ROOT}/bin"
	"$<TARGET_FILE_DIR:RPGGameSystem>"
)

add_custom_command(TARGET RPGGameSystem POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/DataBases"
	"$<TARGET_FILE_DIR:RPGGameSystem>/DataBases"
)

add_custom_command(TARGET RPGGameSystem POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${CMAKE_SOURCE_DIR}/Assets"
	"$<TARGET_FILE_DIR:RPGGameSystem>/Assets"
)
