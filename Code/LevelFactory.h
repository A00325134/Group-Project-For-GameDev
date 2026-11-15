#pragma once
#include "Level.h"

class LevelFactory
{
public:
    // The caller owns the returned Level pointer and must delete it.
    static Level* CreateLevel(int levelNumber);
};
