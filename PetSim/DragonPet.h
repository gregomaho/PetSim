#pragma once
#include "Pet.h"

class DragonPet : public Pet {
public:
    DragonPet(int id, const std::string& name) : Pet(id, name, PetType::Dragon) {}
    std::string makeSound() const override { return "Roooar!"; }
    std::vector<std::string> favoriteFoodTags() const override { return {"meat","spicy"}; }
    void speciesUpdate(int /*deltaMinutes*/) override {
        if (hunger > 90) health += 1; // tougher
    }
};
