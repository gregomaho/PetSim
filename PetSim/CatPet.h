#pragma once
#include "Pet.h"

class CatPet : public Pet {
public:
    CatPet(int id, const std::string& name) : Pet(id, name, PetType::Cat) {}
    std::string makeSound() const override { return "Meow."; }
    std::vector<std::string> favoriteFoodTags() const override { return {"fish","treat"}; }
    void speciesUpdate(int deltaMinutes) override {
        happiness += deltaMinutes / 20; // cats are chill
    }
};
