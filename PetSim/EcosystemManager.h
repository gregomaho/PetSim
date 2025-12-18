#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Pet.h"

class EcosystemManager {
    std::vector<std::unique_ptr<Pet>> pets;
    int nextId{1};

    Pet* findPetPtr(const std::string& name);

public:
    void createDog(const std::string& name);
    void createCat(const std::string& name);
    void createBird(const std::string& name);
    void createDragon(const std::string& name);

    void feedPet(const std::string& petName, const FoodItem& food);
    void playWithPet(const std::string& petName, int minutes);
    void tick(int deltaMinutes);

    void listPets() const;

    void save(const std::string& filename) const;
    void load(const std::string& filename);
};
