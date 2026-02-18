#include "SimulationHelper.hpp"
#include "Animal.hpp"
#include "Carnivore.hpp"
#include "Herbivore.hpp"

#include <iostream>
#include <vector>
#include "Utils.hpp"

constexpr int kIndexDigitBase = 10000;
constexpr int kMarkerEncodingMultiplier = kIndexDigitBase * 10;

int encodeMarkerWithIndex(int marker, int index) {
    int clampedIndex = index % kIndexDigitBase;
    int baseValue = marker * kMarkerEncodingMultiplier;
    return baseValue + (marker < 0 ? -clampedIndex : clampedIndex);
}

int decodeMarkerFromEncoded(int encodedValue) {
    if (encodedValue == 0) return 0;
    return encodedValue / kMarkerEncodingMultiplier;
}

void refreshEncodedIndices(int*** globalMapPtr,
                           const std::vector<Animal*>& animals) {
    int** globalMap = *globalMapPtr;
    for (size_t i = 0; i < animals.size(); ++i) {
        Animal* animal = animals[i];
        Location loc = animal->loc;
        int encodedValue = globalMap[loc.x][loc.y];
        int marker = decodeMarkerFromEncoded(encodedValue);
        globalMap[loc.x][loc.y] =
            encodeMarkerWithIndex(marker, static_cast<int>(i));
    }
}

void shuffleAnimals(std::vector<Animal*>& animals) {
    for (int i = static_cast<int>(animals.size()) - 1; i > 0; --i) {
        int j = randomRange(i + 1);
        if (i == j) continue;
        Animal* temp = animals[i];
        animals[i] = animals[j];
        animals[j] = temp;
    }
}

void prepareFreeCells(std::vector<Location>& freeCells) {
    freeCells.clear();
    freeCells.reserve(FIELD_SIZE * FIELD_SIZE);
    for (int y = 0; y < FIELD_SIZE; ++y) {
        for (int x = 0; x < FIELD_SIZE; ++x) {
            freeCells.push_back({x, y});
        }
    }
    shuffleLocations(freeCells);
}

template <typename CreateAnimalFn>
void spawnSpecies(int count,
                  int marker,
                  int*** globalMapPtr,
                  std::vector<Location>& freeCells,
                  std::vector<Animal*>& animals,
                  CreateAnimalFn&& createAnimal) {
    int** globalMap = *globalMapPtr;
    for (int i = 0; i < count; ++i) {
        if (freeCells.empty()) break;
        Location loc = freeCells.back();
        freeCells.pop_back();
        Animal* animal = createAnimal();
        if (animal == nullptr) continue;

        animal->loc = loc;
        animal->energy = 5;
        animal->energyValue = 5;
        animal->viewRange = 1;
        animal->map = globalMapPtr;
        animal->viewArray = nullptr;

        if (marker == HERBIVORE_MARKER) {
            animal->birthThreshold = 15;
            animal->birthCost = 5;
            animal->movingCost = 1;
            animal->observe = Herbivore_observe;
            animal->move = Herbivore_move;
            animal->giveBirth = Herbivore_giveBirth;
        } else if (marker == CARNIVORE_MARKER) {
            animal->birthThreshold = 40;
            animal->birthCost = 30;
            animal->movingCost = 2;
            animal->observe = Carnivore_observe;
            animal->move = Carnivore_move;
            animal->giveBirth = Carnivore_giveBirth;
        }

        animals.push_back(animal);
        int index = static_cast<int>(animals.size()) - 1;
        globalMap[loc.x][loc.y] = encodeMarkerWithIndex(marker, index);
    }
}

void Simulation_clearContext(int*** globalMapPtr) {
    int** globalMap = *globalMapPtr;
    for (int x = 0; x < FIELD_SIZE; ++x) {
        for (int y = 0; y < FIELD_SIZE; ++y) {
            globalMap[x][y] = 0;
        }
    }
}

void Simulation_initializeGrass(int*** globalMapPtr) {
    int** globalMap = *globalMapPtr;
    for (int x = 0; x < FIELD_SIZE; ++x) {
        for (int y = 0; y < FIELD_SIZE; ++y) {
            int value = randomRange(5) + 1;
            globalMap[x][y] = value;
        }
    }
}

void Simulation_prepare(const std::string& studentID,
                        int*** globalMapPtr) {
    Simulation_clearContext(globalMapPtr);
    initRandom(studentID);
    Simulation_initializeGrass(globalMapPtr);
}

void Simulation_spawnInitialAnimals(int*** globalMapPtr,
                                    std::vector<Animal*>& animals) {
    animals.clear();
    animals.reserve(HERBIVORE_COUNT + CARNIVORE_COUNT);

    std::vector<Location> freeCells;
    prepareFreeCells(freeCells);

    spawnSpecies(HERBIVORE_COUNT, HERBIVORE_MARKER, globalMapPtr, freeCells,
    animals, []() -> Animal* {
                 return reinterpret_cast<Animal*>(new Herbivore());
             });
    spawnSpecies(CARNIVORE_COUNT, CARNIVORE_MARKER, globalMapPtr, freeCells,
    animals, []() -> Animal* {
                 return reinterpret_cast<Animal*>(new Carnivore());
             });

    shuffleAnimals(animals);
    refreshEncodedIndices(globalMapPtr, animals);
}
