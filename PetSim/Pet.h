#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "FoodItem.h"

class Pet {
public:
    enum class PetType { Dog, Cat, Bird, Dragon };
    enum class Mood { Happy, Hungry, Sick, Playful, Tired };

protected:
    int id{};
    std::string name;
    PetType type{PetType::Dog};

    int hunger{50};      // 0..100 (0 = full, 100 = starving)
    int happiness{50};   // 0..100
    int health{80};      // 0..100
    Mood mood{Mood::Happy};

    void clampStats();
    void updateMood();

public:
    Pet(int id, std::string name, PetType type);
    virtual ~Pet() = default;

    int getId() const { return id; }
    const std::string& getName() const { return name; }
    PetType getType() const { return type; }
    Mood getMood() const { return mood; }

    int getHunger() const { return hunger; }
    int getHappiness() const { return happiness; }
    int getHealth() const { return health; }

    // Polymorphism hooks
    virtual std::string makeSound() const = 0;
    virtual void speciesUpdate(int deltaMinutes) = 0;
    virtual std::vector<std::string> favoriteFoodTags() const { return {}; }

    // Shared behaviors
    virtual void updateStats(int deltaMinutes);
    virtual void feed(const FoodItem& food);
    virtual void play(int minutes);

    // Operator overloads
    friend std::ostream& operator<<(std::ostream& os, const Pet& p);
    Pet& operator+(const FoodItem& food); // feeding via operator

    // Save/load line (simple text format)
    virtual std::string toSaveLine() const;
    virtual void fromSaveFields(const std::vector<std::string>& fields);
};
