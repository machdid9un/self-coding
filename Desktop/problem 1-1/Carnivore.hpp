#ifndef CARNIVORE_HPP
#define CARNIVORE_HPP
#include "Animal.hpp"
#include <vector>
#include "Utils.hpp"
#include <cmath>

struct Carnivore {
    // Animal parent: embedded Animal struct acting as the base data.
    Animal base= {{0,0}, 5, 2,40, 30,0, 1,nullptr,nullptr, {},{},{}, {},{}};


    
    // You may add additional attributes and helper functions if needed.
};
void Carnivore_observe(Animal* self);
int Carnivore_move(Animal* self);
Animal* Carnivore_giveBirth(Animal* self);
Animal* Carnivore_init(Location loc, int*** map_ptr, std::vector<struct Animal*>* animals_ptr);

// You may add additional functions if needed.

#endif // CARNIVORE_HPP