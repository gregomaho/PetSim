#pragma once
#include "Pet.h"

class BirdPet : public Pet {
public:
    BirdPet(int id, const std::string& name) : Pet(id, name, PetType::Bird) {}
    std::string makeSound() const override { return "Chirp!"; }
    std::vector<std::string> favoriteFoodTags() const override { return {"seed","fruit"}; }
    void speciesUpdate(int deltaMinutes) override {
        hunger += deltaMinutes / 8; // faster metabolism
    }
};
