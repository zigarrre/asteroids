cmake_minimum_required(VERSION 2.8)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

project(asteroids)

set(ASTEROIDS_SHARED_LIBS TRUE CACHE BOOL "Use shared libraries")

############################################
# Compiler specific settings
############################################

# Windows: Choose to link CRT libraries statically or dynamically
if(WIN32)
    set(ASTEROIDS_STATIC_STD_LIBS FALSE CACHE BOOL "Use statically linked standard libraries? This option must match the one used for SFML and Thor.")
    
    # Modify compiler flags globally
	if(ASTEROIDS_STATIC_STD_LIBS)
		if(MSVC)
			foreach(flag CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
				if(${flag} MATCHES "/MD")
				string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
				endif()
			endforeach()
		elseif(CMAKE_COMPILER_IS_GNUCXX)
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
		endif()
	endif()
endif()


# GCC specific
if(CMAKE_COMPILER_IS_GNUCXX)
    # C++11 support
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
	endif()
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

############################################
# Find libs
############################################

# Add the directory containing the Find-scripts to module path
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/;${CMAKE_MODULE_PATH}")

# Find Boost
set(Boost_ADDITIONAL_VERSIONS "1.51" "1.51.0")
if(NOT ASTEROIDS_SHARED_LIBS)
	set(Boost_USE_STATIC_LIBS TRUE)
endif()
if(ASTEROIDS_STATIC_STD_LIBS)
	set(Boost_USE_STATIC_RUNTIME ON)
endif()
find_package(Boost 1.42.0 COMPONENTS program_options)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
else()
	set(BOOST_ROOT "" CACHE PATH "Boost top-level directory")
	message("\n-> Boost directory not found. Set BOOST_ROOT to Boost's top-level path")
	message("-> Make sure the Boost libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Find SFML
if(NOT ASTEROIDS_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(SFML 2 COMPONENTS graphics window audio system)

if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

# Find Thor
if(NOT ASTEROIDS_SHARED_LIBS)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()
find_package(Thor)

if(SFML_FOUND)
	include_directories(${THOR_INCLUDE_DIR})
else()
	set(THOR_ROOT "" CACHE PATH "Thor top-level directory")
	message("\n-> Thor directory not found. Set THOR_ROOT to Thor's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the Thor libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

############################################
# Generate config.h
############################################

include(GetGitRevisionDescription)
git_describe(ASTEROIDS_VERSION_DESC --tag)
set(ASTEROIDS_PATHS_RES "res" CACHE STRING "Path to the resources folder")
set(ASTEROIDS_PATHS_CONFIG "config.cfg" CACHE STRING "Path to the config file")
set(ASTEROIDS_PATHS_HIGHSCORE "highscore.csv" CACHE STRING "path to the highscore file")
set(ASTEROIDS_PATHS_HIGHSCORE_HOME false CACHE BOOL "Make ASTEROIDS_PATHS_HIGHSCORE relative to the home directory ($HOME or %APPDATA%)")
if(ASTEROIDS_PATHS_HIGHSCORE_HOME)
    set(ASTEROIDS_PATHS_HIGHSCORE_HOME "true")
else()
    set(ASTEROIDS_PATHS_HIGHSCORE_HOME "false")
endif()

configure_file(${CMAKE_SOURCE_DIR}/include/config.h.in ${CMAKE_BINARY_DIR}/generated/config.h)
include_directories(${CMAKE_BINARY_DIR}/generated)

############################################
# Specify source files and lining
############################################

# all source files
set(SRC
    src/Asteroid.cpp
	src/ButtonManager.cpp
	src/DebrisChunk.cpp
	src/EnergyBullet.cpp
	src/Entity.cpp
	src/EntityManager.cpp
	src/Game.cpp
	src/GameOver.cpp
	src/GameOverNewHighscore.cpp
	src/GamestateManager.cpp
	src/Highscore.cpp
	src/HighscoreView.cpp
	src/HUD.cpp
	src/main.cpp
	src/MainMenu.cpp
	src/ManagedButton.cpp
	src/MessageSystem.cpp
	src/Singleplayer.cpp
	src/Spaceship.cpp
	src/utility.cpp
        src/SoundService.cpp
)

if(NOT ASTEROIDS_SHARED_LIBS)
	add_definitions(-DTHOR_STATIC -DSFML_STATIC)
endif()

add_executable (asteroids ${SRC}) 

target_link_libraries(asteroids ${SFML_LIBRARIES})
target_link_libraries(asteroids ${THOR_LIBRARY})
target_link_libraries(asteroids ${Boost_LIBRARIES})

file(COPY res config.cfg DESTINATION ./)
