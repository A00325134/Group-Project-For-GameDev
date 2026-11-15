#include "LevelFactory.h"
#include "Levels.h"

Level* LevelFactory::CreateLevel(int levelNumber)
{
    if (levelNumber == 1)
    {
        return new BeginnerLevel();
    }

    if (levelNumber == 2)
    {
        return new HighRollerLevel();
    }

    if (levelNumber == 3)
    {
        return new VIPLevel();
    }

    return nullptr;
}
