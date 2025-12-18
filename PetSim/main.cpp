#include <iostream>
#include "EcosystemManager.h"
#include "FoodItem.h"

int main() {
    EcosystemManager sim;

    FoodItem fish{"Fish", 20, 6, "fish"};
    FoodItem seeds{"Seeds", 15, 4, "seed"};
    FoodItem steak{"Steak", 25, 8, "meat"};

    try {
        sim.createDog("Buddy");
        sim.createCat("Mochi");
        sim.createBird("Kiwi");
        sim.createDragon("Ember");

        sim.feedPet("Mochi", fish);
        sim.feedPet("Kiwi", seeds);
        sim.playWithPet("Buddy", 10);
        sim.feedPet("Ember", steak);

        sim.tick(30);
        sim.listPets();

        sim.save("petsim_save.txt");
        sim.load("petsim_save.txt");
        sim.listPets();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}