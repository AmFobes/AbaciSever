
cmake_minimum_required (VERSION 3.8)

project(Abaci_Server)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# TODO: Add tests and install targets if needed.
if(WIN32)
set(CMAKE_PREFIX_PATH "C://Qt/5.12.5/msvc2017_64/lib/cmake")

set(GUI_TYPE WIN32)

endif()
find_package(Qt5 COMPONENTS Widgets Core Sql Network REQUIRED) # Search for QT5

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(Abaci_Server ${GUI_TYPE} main.cpp gui/CreateClient.cpp gui/CreateClient.h gui/CreateClient.ui sqlServer.h gui/MainWindow.cpp gui/MainWindow.h gui/MainWindow.ui
			gui/DatabaseOptions.cpp gui/DatabaseOptions.h gui/DatabaseOptions.ui gui/ClientData.cpp gui/ClientData.h gui/ClientData.ui server.h)

target_include_directories(Abaci_Server PUBLIC Qt5_INCLUDE_DIRS)
target_link_libraries(Abaci_Server Qt5::Widgets Qt5::Core Qt5::Sql Qt5::Network)
if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Core> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Gui> $<TARGET_FILE_DIR:${PROJECT_NAME}>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Widgets> $<TARGET_FILE_DIR:${PROJECT_NAME}> 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Sql> $<TARGET_FILE_DIR:${PROJECT_NAME}> 
		COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:Qt5::Network> $<TARGET_FILE_DIR:${PROJECT_NAME}> )
endif(WIN32)
