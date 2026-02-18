#include "Herbivore.hpp"
#include "Animal.hpp"
#include <vector>
#include "Utils.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
inline bool operator==(const Location& lhs, const Location& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
//got helped from gemini to set init
Animal* Herbivore_init(Location loc, int*** map_ptr, std::vector<Animal*>* animals_ptr) {
    struct Herbivore* self_h = new  Herbivore;
    struct Animal* self = &self_h->base;
    

    Animal_init_base(self, loc, 1, 5, map_ptr); // viewRange: 1, energyValue: 5 [cite: 110, 111]
    
    self->movingCost = 1; 
    self->birthThreshold = 15; 
    self->birthCost = 5;

    self->observe = Herbivore_observe;
    self->giveBirth = Herbivore_giveBirth;
    
    self->animals_list_ptr = nullptr;
   
    return self; 
}

#include <iostream>

void Herbivore_observe(Animal* self_base){
   

    if (self_base->viewRange <= 0 || self_base->viewRange > 5) {
        return;
    }

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

    if (self_base->map == nullptr) {
        return;
    }

    Animal_observe(self_base, self_base->map);

    int much    = self_base->allspot.size();
    if (much == 0) return;

    int selfidx = (much - 1) / 2;   // 가운데 = 자기 자리

    for (int idx = 0; idx < much; ++idx) {
        Location pos = self_base->allspot[idx];
        int wx = ((pos.x % 50) + 50) % 50;
        int wy = ((pos.y % 50) + 50) % 50;

        int row = idx / size;
        int col = idx % size;

        if (row < 0 || row >= size || col < 0 || col >= size) {
            continue;
        }

        int cell = (*self_base->map)[wx][wy];

        // 4. 자기 자리
        if (idx == selfidx) {
            self_base->viewArray[row][col] = -1000;
            continue;
        }

        if (cell <= -1000000) {
            self_base->viewArray[row][col] = -10000;
            continue;
        }

        int score = cell; 
        bool predator_adj = false;
        for (int dy = -1; dy <= 1 && !predator_adj; ++dy) {
            for (int dx = -1; dx <= 1 && !predator_adj; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int nx = wx + dx;
                int ny = wy + dy;

                nx = ((nx % 50) + 50) % 50;
                ny = ((ny % 50) + 50) % 50;

                int ncell = (*self_base->map)[nx][ny];
                // carnivore 마커: -2000000 이하
                if (ncell <= -2000000) {
                    predator_adj = true;
                }
            }
        }

        if (predator_adj) {
            score -= 100;
        }

        self_base->viewArray[row][col] = score;
    }
}



int Herbivore_move(struct Animal* self_base){
    int k= Animal_move(self_base);
    return k;
}

Animal* Herbivore_giveBirth(struct Animal*self_base){
    return Animal_giveBirth(self_base, Herbivore_init);
}