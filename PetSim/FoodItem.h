#pragma once
#include <string>

struct FoodItem {
    std::string name;
    int nutrition;      // lowers hunger
    int funBonus;       // increases happiness
    std::string tag;    // "fish", "seed", "meat", etc.
};
