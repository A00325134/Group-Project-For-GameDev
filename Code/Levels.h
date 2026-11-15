#pragma once
#include "Level.h"

class BeginnerLevel : public Level
{
public:
    BeginnerLevel();
    void DisplayIntro() const override;
};

class HighRollerLevel : public Level
{
public:
    HighRollerLevel();
    void DisplayIntro() const override;
};

class VIPLevel : public Level
{
public:
    VIPLevel();
    void DisplayIntro() const override;
};
