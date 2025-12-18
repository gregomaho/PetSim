# GitHub Copilot instructions for PetSim

Summary
- Small C++ pet simulator (no external deps). Primary executable is built from `main.cpp` plus `Pet.cpp` and `EcosystemManager.cpp`.
- Key runtime files: `main.cpp` (example usage), `EcosystemManager.*` (entity management, save/load), `Pet.*` (base logic), `*Pet.h` (species-specific behavior), `FoodItem.h` (food model).

Quick start (how to build & run locally) 🔧
- Build (simple manual compile):
  g++ -std=c++17 -Wall -Wextra -O2 -o petsim main.cpp Pet.cpp EcosystemManager.cpp
- Run:
  ./petsim
- The example `main.cpp` demonstrates creating pets, feeding/playing, ticking the sim, and saving/loading to `petsim_save.txt`.

Big-picture architecture / why things are structured this way 💡
- Single-process simulator with a small object model:
  - `Pet` = base class that holds common state (hunger, happiness, health, mood) and implements shared behaviors (feed, play, updateStats).
  - Per-species classes (`DogPet`, `CatPet`, `BirdPet`, `DragonPet`) are header-only and override small hooks: `makeSound()`, `favoriteFoodTags()`, and `speciesUpdate()`.
  - `EcosystemManager` owns pets (`std::vector<std::unique_ptr<Pet>>`) and provides operations: create, feed, play, tick, list, save, load.
- Save/load is a simple line-based text format (first line = `nextId`, subsequent lines are `id|name|typeInt|hunger|happiness|health`). The load path instantiates the appropriate subclass based on `typeInt` and calls `fromSaveFields`.

Project-specific patterns & conventions ✅
- Header-only small species types: add minimal logic in `*Pet.h` (constructor + the three overrides). Keep small helpers in `Pet.cpp`.
- Serialization: use `Pet::toSaveLine()` and `Pet::fromSaveFields()` for per-pet persistence. If you add new state, update both serialization and the `load` switch in `EcosystemManager::load`.
- Case-insensitive lookup: `EcosystemManager::findPetPtr` lowercases names before compare. However, `ensureUniqueName` checks exact equality when creating pets—beware of case-sensitivity edge cases.
- Error handling: methods throw `std::runtime_error` or `std::invalid_argument` on misuse (e.g., duplicate name, bad save file, invalid inputs). Follow this pattern when adding APIs.
- Operator convention: feeding uses `Pet::operator+(const FoodItem&)` which forwards to `feed`; `EcosystemManager::feedPet` uses this.

Examples (concrete edits an agent might perform) 🛠️
- Add a new pet species `Ferret`:
  1. Create `FerretPet.h` with class `FerretPet : public Pet`.
  2. Implement `makeSound()`, `favoriteFoodTags()` and `speciesUpdate()`.
  3. Add factory method `createFerret(const std::string&)` to `EcosystemManager.h/cpp` and a `case` in `load()` to construct `FerretPet` for its `PetType` int.
  4. If `Ferret` needs extra state, extend `toSaveLine`/`fromSaveFields` accordingly and keep load compatibility in mind.

- Change save format/fields:
  - Update `Pet::toSaveLine()` and `Pet::fromSaveFields()` together.
  - Update `EcosystemManager::load` to accept the new format; keep backward compatibility if possible.

Where to look first when debugging or extending 🔍
- Runtime flows: `main.cpp` -> `EcosystemManager` methods -> `Pet` hooks.
- Persistence: `EcosystemManager::save/load`, `Pet::toSaveLine/fromSaveFields`.
- Species behavior: `*Pet.h` files (small, self-contained overrides).

Testing & validation
- There are no automated tests currently. Use `main.cpp` as a smoke test or add a small test executable (GoogleTest or a simple `tests.cpp`) that exercises create/feed/tick/save/load flows.

Notes / Gotchas ⚠️
- No build system (CMake/Make) is present—add one if you expect frequent compilation or CI.
- Names are enforced for uniqueness with a case-sensitive check; lookups are case-insensitive. This can produce surprising behavior if different-cased names are used.
- All species classes are header-only, so keeping logic minimal helps compile times and maintenance.

If anything above is unclear or you'd like extra examples (e.g., adding unit tests or a CMake file), tell me which part to expand and I will iterate. 👇