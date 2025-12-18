//Gregory Mahoy
//12/18/25
//PetSim Project
//final project assignment for CSCI201
//Purpose of this project is to create a pet simulator program with hunger meter and happiness levels while also having an enviroment that will 
# PetSim – Virtual Pet Ecosystem Simulator

## Overview
PetSim is a console-based C++ application that simulates a virtual pet ecosystem. 
Users can create and manage multiple pets, including dogs, cats, birds, and dragons. 
Each pet has attributes such as hunger, happiness, health, and mood that change over time 
based on user interactions and environmental conditions.

This project was created as a final programming project to demonstrate object-oriented 
programming concepts in C++.

---

## Features
- Create multiple pets of different species
- Feed pets using different food types
- Play with pets to increase happiness
- Advance time to simulate natural stat changes
- View the status of all pets
- Random environmental effects (weather/events)
- Save and load the ecosystem to/from a file

---

## Object-Oriented Concepts Used
- **Inheritance:** Dog, Cat, Bird, and Dragon classes inherit from the base Pet class
- **Polymorphism:** Each pet type overrides species-specific behavior
- **Encapsulation:** Pet data and behaviors are managed through class methods
- **Collections:** Pets are stored using vectors and maps
- **Exception Handling:** Used for invalid input and file errors
- **Enumerations:** Used for pet types, moods, and weather states
- **Operator Overloading:** Used to feed pets and display pet information
- **File I/O:** Save and load pet data from a text file

---

## File Structure
```
PetSim/
│── main.cpp
│── Pet.h / Pet.cpp
│── DogPet.h
│── CatPet.h
│── BirdPet.h
│── DragonPet.h
│── EcosystemManager.h / EcosystemManager.cpp
│── Environment.h / Environment.cpp
│── FoodItem.h
│── petsim_save.txt
```

---

## How to Compile and Run
Navigate to the PetSim directory and run:

```
g++ -std=c++17 -Wall -Wextra -g3 main.cpp Environment.cpp Pet.cpp EcosystemManager.cpp -o petsim
./petsim
```

---

## How to Use the Program
1. Run the program
2. Choose options from the menu to add pets or interact with them
3. Feed or play with pets to affect their stats
4. Advance time to simulate the ecosystem
5. Save or load the ecosystem as needed
6. Exit the program when finished

---

## Sample Output
```
===== PetSim Menu =====
1) Add a pet
2) Feed a pet
3) Play with a pet
4) Advance time
5) View all pets
6) Save
7) Load
0) Quit
```

---


## Notes
This project is intended for educational purposes and was designed to meet the 
requirements of a C++ programming course final project.
