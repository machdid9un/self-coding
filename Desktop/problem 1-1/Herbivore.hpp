#ifndef HERBIVORE_HPP
#define HERBIVORE_HPP
#include "Animal.hpp"
#include <vector>
#include "Utils.hpp"
#include <cmath>


struct Herbivore {
    // Animal parent: embedded Animal struct acting as the base data.
    Animal base={{0,0}, 5, 1,15,5 ,5, 1,nullptr,nullptr, {},{},{}, {},{}};
    
    // You may add additional attributes and helper functions if needed.
};
void Herbivore_observe(Animal* self);

Animal* Herbivore_init(Location loc, int*** map_ptr, std::vector<struct Animal*>* animals_ptr);
int Herbivore_move(Animal* self);
Animal* Herbivore_giveBirth(Animal* self);
// You may add additional functions if needed.

#endif // HERBIVORE_HPP
