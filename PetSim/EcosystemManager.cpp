#include "EcosystemManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "DogPet.h"
#include "CatPet.h"
#include "BirdPet.h"
#include "DragonPet.h"

static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}

Pet* EcosystemManager::findPetPtr(const std::string& n) {
    std::string target = n;
    std::transform(target.begin(), target.end(), target.begin(), ::tolower);

    for (auto& p : pets) {
        std::string name = p->getName();
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (name == target) return p.get();
    }
    return nullptr;
}

static void ensureUniqueName(const std::vector<std::unique_ptr<Pet>>& pets, const std::string& name) {
    for (auto& p : pets) {
        if (p->getName() == name) throw std::runtime_error("Pet name already exists.");
    }
}

void EcosystemManager::createDog(const std::string& name) {
    ensureUniqueName(pets, name);
    pets.push_back(std::make_unique<DogPet>(nextId++, name));
}
void EcosystemManager::createCat(const std::string& name) {
    ensureUniqueName(pets, name);
    pets.push_back(std::make_unique<CatPet>(nextId++, name));
}
void EcosystemManager::createBird(const std::string& name) {
    ensureUniqueName(pets, name);
    pets.push_back(std::make_unique<BirdPet>(nextId++, name));
}
void EcosystemManager::createDragon(const std::string& name) {
    ensureUniqueName(pets, name);
    pets.push_back(std::make_unique<DragonPet>(nextId++, name));
}

void EcosystemManager::feedPet(const std::string& petName, const FoodItem& food) {
    Pet* p = findPetPtr(petName);
    if (!p) throw std::runtime_error("No pet named: " + petName);
    (*p) + food; // uses operator+
}

void EcosystemManager::playWithPet(const std::string& petName, int minutes) {
    Pet* p = findPetPtr(petName);
    if (!p) throw std::runtime_error("No pet named: " + petName);
    p->play(minutes);
}

void EcosystemManager::tick(int deltaMinutes) {
    for (auto& p : pets) p->updateStats(deltaMinutes);
}

void EcosystemManager::listPets() const {
    std::cout << "---- Pet List ----\n";
    for (auto& p : pets) std::cout << *p << "\n";
}

void EcosystemManager::save(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) throw std::runtime_error("Could not open save file for writing.");

    out << nextId << "\n";
    for (auto& p : pets) out << p->toSaveLine() << "\n";
}

void EcosystemManager::load(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Could not open save file for reading.");

    pets.clear();

    std::string line;
    if (!std::getline(in, line)) throw std::runtime_error("Save file is empty.");
    nextId = std::stoi(line);

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        auto f = split(line, '|');
        if (f.size() < 6) continue;

        Pet::PetType t = (Pet::PetType)std::stoi(f[2]);

        std::unique_ptr<Pet> pet;
        // create right subclass, then fill fields
        switch (t) {
            case Pet::PetType::Dog: pet = std::make_unique<DogPet>(0, "temp"); break;
            case Pet::PetType::Cat: pet = std::make_unique<CatPet>(0, "temp"); break;
            case Pet::PetType::Bird: pet = std::make_unique<BirdPet>(0, "temp"); break;
            case Pet::PetType::Dragon: pet = std::make_unique<DragonPet>(0, "temp"); break;
            default: continue;
        }

        pet->fromSaveFields(f);
        pets.push_back(std::move(pet));
    }
}
