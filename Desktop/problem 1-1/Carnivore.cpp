#include "Carnivore.hpp"
#include "Animal.hpp"
#include <vector>
#include "Utils.hpp"
#include <iostream>
extern int Animal_move(struct Animal*self);
extern Animal* Animal_giveBirth(struct Animal*self);

inline bool operator==(const Location& lhs, const Location& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
//got helped from gemini to set init
Animal* Carnivore_init(Location loc, int*** map_ptr,std::vector<Animal*>* animals_ptr) {
    struct Carnivore* self_c = new Carnivore;
    struct Animal* self = &self_c->base;
    
    Animal_init_base(self, loc, 1, 5, map_ptr); 


    self->movingCost = 2; 
    self->birthThreshold = 40;
    self->birthCost = 30; 


    self->observe = Carnivore_observe; 
    self->giveBirth = Carnivore_giveBirth;
    self->animals_list_ptr = nullptr;
    return self;
}


void Carnivore_observe(Animal* self_base){
    
    
    if (self_base->viewArray == nullptr) {
        int size = 2 * self_base->viewRange + 1;
        self_base->viewArray = (int**)malloc(sizeof(int*) * size);
        for (int r = 0; r < size; ++r) {
            self_base->viewArray[r] = (int*)malloc(sizeof(int) * size);
        }
    }

    int size = 2 * self_base->viewRange + 1;

    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            self_base->viewArray[r][c] = 0;
        }
    }

   
    Animal_observe(self_base, self_base->map);

    int much = self_base->allspot.size();
    

    int selfidx = (much - 1) / 2;   // 가운데가 자기 자리라고 가정

    for (int idx = 0; idx < much; ++idx) {
        Location pos = self_base->allspot[idx];
        int wx = pos.x;
        int wy = pos.y;

        wx = ((wx % 50) + 50) % 50;
        wy = ((wy % 50) + 50) % 50;

        int row = idx / size;   
        int col = idx % size;  

       

        int gival = (*self_base->map)[wx][wy];

        if (idx == selfidx) {
        
            self_base->viewArray[row][col] = -1000;
        } else {
            
            if (gival <= -2000000) {
                self_base->viewArray[row][col] = -10000;
            } else if (gival <= -1000000 && gival > -2000000) {
                self_base->viewArray[row][col] = 5;  // prey의 energyValue
            } else {
                self_base->viewArray[row][col] = 0;
            }
        }
    }


}


int Carnivore_move(struct Animal*self_base){
    int k= Animal_move(self_base);
    return k;
}

Animal* Carnivore_giveBirth(struct Animal*self_base){
    return Animal_giveBirth(self_base, Carnivore_init);
}