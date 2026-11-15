cmake_minimum_required(VERSION 3.20)

project(RoadToVIP)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RoadToVIP
        Code/main.cpp
        Code/BlackjackGame.cpp
        Code/Card.cpp
        Code/Deck.cpp
        Code/Hand.cpp
        Code/Participant.cpp
        Code/Player.cpp
        Code/Dealer.cpp
        Code/Level.cpp
        Code/Levels.cpp
        Code/LevelFactory.cpp
        Code/SaveManager.cpp
)

target_include_directories(RoadToVIP PRIVATE Code)