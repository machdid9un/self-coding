#include "Animal.hpp"
#include <vector>
#include <algorithm>
#include <iterator>
#include "Utils.hpp"
#include <cstdlib>

void allocate_view_array(Animal* self) {
    int size = 2 * self->viewRange + 1;
    self->viewArray = (int**)malloc(sizeof(int*) * size);
    for (int i = 0; i < size; ++i) {
        self->viewArray[i] = (int*)malloc(sizeof(int) * size);
    }
}

void Animal_init_base(Animal* self, Location loc, int view_range, int energy_value, int*** map_ptr) {
    self->loc = loc;
    self->energy = 5; 
    self->energyValue = energy_value;
    self->viewRange = view_range; 
    self->map = map_ptr;
    self->animals_list_ptr = nullptr;
    
    allocate_view_array(self); 
    self->move = Animal_move; 
}

void Animal_observe(Animal * self, int *** map){
    self->allspot.clear();

   
    for (int dx = -self->viewRange; dx <= self->viewRange; ++dx) {
        for (int dy = -self->viewRange; dy <= self->viewRange; ++dy) {

            int xval = self->loc.x + dx;
            int yval = self->loc.y + dy;

  
            if (xval >= 50) xval -= 50; else if (xval < 0) xval += 50;
            if (yval >= 50) yval -= 50; else if (yval < 0) yval += 50;

            self->allspot.push_back({xval, yval});
        }
    }
}

int Animal_move(Animal* self){
    int size  = 2 * self->viewRange + 1;
    int total = size * size;


    int bestScore = -1000000000;
    std::vector<int> bestIdx;

    for (int idx = 0; idx < total; ++idx) {
        int row = idx / size;
        int col = idx % size;
        int score = self->viewArray[row][col];

        if (score > bestScore) {
            bestScore = score;
            bestIdx.clear();
            bestIdx.push_back(idx);
        } else if (score == bestScore) {
            bestIdx.push_back(idx);
        }
    }

    std::vector<Location> cand;
    for (int idx : bestIdx) {
        if (idx >= 0 && idx < (int)self->allspot.size()) {
            cand.push_back(self->allspot[idx]);   
        }
    }

    if (cand.empty()) return 100000;

    Location worldLoc = randomSelection(cand);
    
    int newX = worldLoc.x;
    int newY = worldLoc.y;
    int oldX = self->loc.x;
    int oldY = self->loc.y;

    int prevnum = (*self->map)[newX][newY]; 
    int curMarker = (*self->map)[oldX][oldY];

    // 먹이 섭취 로직
    int eatenIndex = -1;

    // 내가 초식동물)이고 풀이 있으면
    if (curMarker <= -1000000 && curMarker > -2000000) {
        if (prevnum > 0) {
            self->energy += prevnum;
        }
    }
    // 내가 육식동물이고 초식동물이 있으면
    else if (curMarker <= -2000000) {
        if (prevnum <= -1000000 && prevnum > -2000000) {
            eatenIndex = -1000000 - prevnum;
            if (self->animals_list_ptr != nullptr &&
                eatenIndex >= 0 &&
                eatenIndex < (int)self->animals_list_ptr->size()) {
                
                Animal* prey = (*(self->animals_list_ptr))[eatenIndex];
                self->energy += prey->energyValue; 
            } else {
                self->energy += 5; // 예외 처리
            }
        }
    }

    // 이동 처리
    (*self->map)[oldX][oldY] = 0; 
    (*self->map)[newX][newY] = curMarker;

    self->loc.x = newX;
    self->loc.y = newY;

    if (eatenIndex >= 0) return eatenIndex;
    return 100000;
}

Animal* Animal_giveBirth(Animal* self, Animal_init_func init_child) {
    if (self->energy <= self->birthThreshold) { 
        return nullptr;
    }

    std::vector<Location> space;

    for (int dx = -self->viewRange; dx <= self->viewRange; ++dx) {
        for (int dy = -self->viewRange; dy <= self->viewRange; ++dy) {
            if (dx == 0 && dy == 0) continue; 

            int xval = self->loc.x + dx;
            int yval = self->loc.y + dy;

            if (xval >= 50) xval -= 50; else if (xval < 0) xval += 50;
            if (yval >= 50) yval -= 50; else if (yval < 0) yval += 50;

            if ((*self->map)[xval][yval] >= 0) { // 풀이 있는 빈 곳
                space.push_back({xval, yval});
            }
        }
    }

    if (space.empty()) return nullptr;

    Location bornplace = randomSelection(space);
    
    Animal* child = init_child(bornplace, self->map, self->animals_list_ptr);
    child->energy = 5;

    self->energy -= self->birthCost;
    
    return child;
}
