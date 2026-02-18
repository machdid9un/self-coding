// Animal.hpp

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Utils.hpp" 
typedef struct Animal* (*Animal_init_func)(Location loc, int*** map_ptr, std::vector<struct Animal*>* animals_ptr);
// Animal 구조체 정의
struct Animal {

    Location loc;
    int energy;   
    int movingCost; 
    int birthThreshold; 
    int birthCost; // 출산 시 소모 에너지 
    int energyValue; 
    int viewRange; 
    int** viewArray; 
    int*** map; 
    std::vector<Location> allspot;
    std::vector<struct Animal*>* animals_list_ptr;
   
    void (*observe)(Animal* self); 
    int (*move)(Animal* self);
    struct Animal* (*giveBirth)(Animal* self);
    
  
};

int Animal_move(Animal* self);
Animal* Animal_giveBirth(struct Animal* self, Animal_init_func init_child);
void Animal_init_base(Animal* self, Location loc, int view_range, int energy_value, int*** map_ptr);
void Animal_observe(Animal* self, int*** map);

#endif