#ifndef SIMULATION_HELPER_HPP
#define SIMULATION_HELPER_HPP

#include <string>
#include <vector>

struct Animal;

const int FIELD_SIZE = 50;

const int HERBIVORE_COUNT = 200;
const int CARNIVORE_COUNT = 25;

const int GIRAFFE_COUNT = 150;
const int SLOTH_COUNT = 150;
const int TIGER_COUNT = 15;
const int WOLF_COUNT = 15;

void Simulation_clearContext(int*** globalMapPtr);
void Simulation_initializeGrass(int*** globalMapPtr);
void Simulation_prepare(const std::string& studentID,
                        int*** globalMapPtr);
void Simulation_spawnInitialAnimals(int*** globalMapPtr,
                                    std::vector<Animal*>& animals);

#endif // SIMULATION_HELPER_HPP
