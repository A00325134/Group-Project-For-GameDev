#pragma once
#include <iostream>
#include <string>

class Card
{
private:
    std::string _rank;
    std::string _suit;
    int _value;

public:
    Card(std::string rank, std::string suit, int value);

    std::string GetRank() const;
    std::string GetSuit() const;
    int GetValue() const;
    void PrintCard() const;
};
