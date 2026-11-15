cmake_minimum_required(VERSION 4.3)
project(RoadToVIP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(RoadToVIP
        BlackjackGame.cpp
        BlackjackGame.h
        Card.cpp
        Card.h
        Dealer.cpp
        Dealer.h
        Deck.cpp
        Deck.h
        Hand.cpp
        Hand.h
        Level.cpp
        Level.h
        LevelFactory.cpp
        LevelFactory.h
        Levels.cpp
        Levels.h
        main.cpp
        Participant.cpp
        Participant.h
        Player.cpp
        Player.h
        SaveManager.cpp
        SaveManager.h)
