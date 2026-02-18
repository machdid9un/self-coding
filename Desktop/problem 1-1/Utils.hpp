#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>

#include "SimulationHelper.hpp"

const int HERBIVORE_MARKER = -10;
const int CARNIVORE_MARKER = -20;
const int GIRAFFE_MARKER = -11;
const int SLOTH_MARKER = -12;
const int TIGER_MARKER = -21;
const int WOLF_MARKER = -22;
const int SCORE_BLOCKED = -1000000;
const int SCORE_PREDATOR_NEIGHBOR = -1000;

struct Location {
    int x;
    int y;
};

void initRandom(const std::string& sid);
long long nextRandom();
int randomRange(int maxExclusive);
Location randomSelection(const std::vector<Location>& candidates); // use this function to randomly select a Location


int wrapWithFieldSize(int value);
Location wrapLocation(int x, int y);
void shuffleLocations(std::vector<Location>& locations);

#endif // UTIL_HPP
