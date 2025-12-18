#include <iostream>
#include <string>
#include <stdexcept>
#include "EcosystemManager.h"
#include "FoodItem.h"

static int readInt() {
    int x;
    if (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        throw std::runtime_error("Invalid number input.");
    }
    std::cin.ignore(100000, '\n');
    return x;
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static void printMenu() {
    std::cout << "\n===== PetSim Menu =====\n"
              << "1) Add a pet\n"
              << "2) Feed a pet\n"
              << "3) Play with a pet\n"
              << "4) Advance time\n"
              << "5) View all pets\n"
              << "6) Save\n"
              << "7) Load\n"
              << "0) Quit\n"
              << "Choice: ";
}

static int choosePetType() {
    std::cout << "Choose type:\n"
              << "1) Dog\n"
              << "2) Cat\n"
              << "3) Bird\n"
              << "4) Dragon\n"
              << "Type: ";
    int c = readInt();
    if (c < 1 || c > 4) throw std::runtime_error("Invalid pet type choice.");
    return c;
}

static FoodItem chooseFood() {
    std::cout << "Choose food:\n"
              << "1) Fish (fish)\n"
              << "2) Seeds (seed)\n"
              << "3) Fruit (fruit)\n"
              << "4) Steak (meat)\n"
              << "5) Treat (treat)\n"
              << "6) Spicy Meat (spicy)\n"
              << "Food: ";
    int c = readInt();
    switch (c) {
        case 1: return {"Fish", 20, 6, "fish"};
        case 2: return {"Seeds", 15, 4, "seed"};
        case 3: return {"Fruit", 14, 5, "fruit"};
        case 4: return {"Steak", 25, 8, "meat"};
        case 5: return {"Treat", 10, 12, "treat"};
        case 6: return {"Spicy Meat", 22, 7, "spicy"};
        default: throw std::runtime_error("Invalid food choice.");
    }
}

int main() {
    EcosystemManager sim;
    const std::string defaultSave = "petsim_save.txt";

    std::cout << "Welcome to PetSim!\n";

    bool running = true;
    while (running) {
        try {
            printMenu();
            int choice = readInt();

            switch (choice) {
                case 1: {
                    int t = choosePetType();
                    std::string name = readLine("Enter pet name: ");
                    if (name.empty()) throw std::runtime_error("Name cannot be empty.");

                    //  Uses existing API:
                    if (t == 1) sim.createDog(name);
                    else if (t == 2) sim.createCat(name);
                    else if (t == 3) sim.createBird(name);
                    else sim.createDragon(name);

                    std::cout << "Pet added!\n";
                    break;
                }
                case 2: {
                    std::string petName = readLine("Which pet to feed? (name): ");
                    FoodItem food = chooseFood();
                    sim.feedPet(petName, food);
                    std::cout << "Fed " << petName << " with " << food.name << ".\n";
                    break;
                }
                case 3: {
                    std::string petName = readLine("Which pet to play with? (name): ");
                    std::cout << "Minutes to play: ";
                    int minutes = readInt();
                    sim.playWithPet(petName, minutes);
                    std::cout << "Played with " << petName << ".\n";
                    break;
                }
                case 4: {
                    std::cout << "Advance time by how many minutes? ";
                    int mins = readInt();
                    sim.tick(mins);
                    std::cout << "Time advanced.\n";
                    break;
                }
                case 5: {
                    sim.listPets();
                    break;
                }
                case 6: {
                    std::string file = readLine("Save filename (enter for default): ");
                    if (file.empty()) file = defaultSave;
                    sim.save(file);
                    std::cout << "Saved to " << file << "\n";
                    break;
                }
                case 7: {
                    std::string file = readLine("Load filename (enter for default): ");
                    if (file.empty()) file = defaultSave;
                    sim.load(file);
                    std::cout << "Loaded from " << file << "\n";
                    break;
                }
                case 0: {
                    running = false;
                    std::cout << "Goodbye!\n";
                    break;
                }
                default:
                    std::cout << "Invalid choice.\n";
                    break;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
