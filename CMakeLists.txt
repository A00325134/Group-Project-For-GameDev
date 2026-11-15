cmake_minimum_required(VERSION 4.3)
project(RoadToVIP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RoadToVIP
        Code/BlackjackGame.cpp
        Code/BlackjackGame.h
        Code/Card.cpp
        Code/Card.h
        Code/Dealer.cpp
        Code/Dealer.h
        Code/Deck.cpp
        Code/Deck.h
        Code/Hand.cpp
        Code/Hand.h
        Code/Level.cpp
        Code/Level.h
        Code/LevelFactory.cpp
        Code/LevelFactory.h
        Code/Levels.cpp
        Code/Levels.h
        Code/main.cpp
        Code/Participant.cpp
        Code/Participant.h
        Code/Player.cpp
        Code/Player.h
        Code/SaveManager.cpp
        Code/SaveManager.h)
