#pragma once
#include "Pet.h"

class DogPet : public Pet {
public:
    DogPet(int id, const std::string& name) : Pet(id, name, PetType::Dog) {}
    std::string makeSound() const override { return "Woof!"; }
    std::vector<std::string> favoriteFoodTags() const override { return {"meat","treat"}; }
    void speciesUpdate(int deltaMinutes) override {
        happiness -= deltaMinutes / 8; // dogs get bored faster
    }
};
