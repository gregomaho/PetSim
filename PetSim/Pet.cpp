#include "Pet.h"
#include <algorithm>
#include <sstream>

static int clampInt(int v, int lo, int hi) {
    return std::max(lo, std::min(v, hi));
}

Pet::Pet(int id_, std::string name_, PetType type_)
    : id(id_), name(std::move(name_)), type(type_) {}

void Pet::clampStats() {
    hunger = clampInt(hunger, 0, 100);
    happiness = clampInt(happiness, 0, 100);
    health = clampInt(health, 0, 100);
}

void Pet::updateMood() {
    if (health < 25) mood = Mood::Sick;
    else if (hunger > 70) mood = Mood::Hungry;
    else if (happiness > 70) mood = Mood::Playful;
    else if (happiness < 30) mood = Mood::Tired;
    else mood = Mood::Happy;
}

void Pet::feed(const FoodItem& food) {
    if (food.nutrition <= 0) throw std::invalid_argument("Food nutrition must be > 0");

    hunger -= food.nutrition;
    happiness += food.funBonus / 2;

    auto fav = favoriteFoodTags();
    if (std::find(fav.begin(), fav.end(), food.tag) != fav.end()) {
        happiness += 8;
        health += 2;
    }

    clampStats();
    updateMood();
}

void Pet::play(int minutes) {
    if (minutes <= 0) throw std::invalid_argument("Play minutes must be > 0");

    happiness += minutes / 2;
    hunger += minutes / 3;

    if (hunger > 85) health -= 3;

    clampStats();
    updateMood();
}

void Pet::updateStats(int deltaMinutes) {
    if (deltaMinutes <= 0) return;

    hunger += deltaMinutes / 2;
    happiness -= deltaMinutes / 6;

    speciesUpdate(deltaMinutes);

    if (hunger > 90) health -= 2;
    if (happiness < 15) health -= 1;

    clampStats();
    updateMood();
}

Pet& Pet::operator+(const FoodItem& food) {
    feed(food);
    return *this;
}

static std::string typeToString(Pet::PetType t) {
    switch (t) {
        case Pet::PetType::Dog: return "Dog";
        case Pet::PetType::Cat: return "Cat";
        case Pet::PetType::Bird: return "Bird";
        case Pet::PetType::Dragon: return "Dragon";
    }
    return "Unknown";
}

static std::string moodToString(Pet::Mood m) {
    switch (m) {
        case Pet::Mood::Happy: return "Happy";
        case Pet::Mood::Hungry: return "Hungry";
        case Pet::Mood::Sick: return "Sick";
        case Pet::Mood::Playful: return "Playful";
        case Pet::Mood::Tired: return "Tired";
    }
    return "Unknown";
}

std::ostream& operator<<(std::ostream& os, const Pet& p) {
    os << p.name << " (" << typeToString(p.type) << ") "
       << "Hunger=" << p.hunger
       << " Happy=" << p.happiness
       << " Health=" << p.health
       << " Mood=" << moodToString(p.mood)
       << " Sound=" << p.makeSound();
    return os;
}

// Format: id|name|typeInt|hunger|happiness|health
std::string Pet::toSaveLine() const {
    std::ostringstream out;
    out << id << "|" << name << "|" << (int)type << "|"
        << hunger << "|" << happiness << "|" << health;
    return out.str();
}

void Pet::fromSaveFields(const std::vector<std::string>& f) {
    if (f.size() < 6) throw std::runtime_error("Corrupt save line (not enough fields)");
    id = std::stoi(f[0]);
    name = f[1];
    type = (PetType)std::stoi(f[2]);
    hunger = std::stoi(f[3]);
    happiness = std::stoi(f[4]);
    health = std::stoi(f[5]);
    clampStats();
    updateMood();
}
