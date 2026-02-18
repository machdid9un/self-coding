#include "SimulationHelper.hpp"
#include "Utils.hpp"
#include "Animal.hpp"
#include "Herbivore.hpp"
#include "Carnivore.hpp"

#include <iostream>
#include <vector>
#include <cmath>

/*****************************************
YOU MUST EDIT THE STUDENT ID BELOW!!!
******************************************/
std::string studentID = "2025150058"; 
/*****************************************
YOU MUST EDIT THE STUDENT ABOVE!!!
******************************************/

const int SIMULATE_ITERATION_COUNT = 100000;

int** globalMap = nullptr;




int main() {

    globalMap = new int*[FIELD_SIZE];
    for (int i = 0; i < FIELD_SIZE; ++i) {
        globalMap[i] = new int[FIELD_SIZE];
    }

    Simulation_prepare(studentID, &globalMap);

    std::vector<Animal*> animals;
    Simulation_spawnInitialAnimals(&globalMap, animals);

   
    for (auto* a : animals) {
        if (a) a->animals_list_ptr = &animals;
    }

    for (int iter = 0; iter < SIMULATE_ITERATION_COUNT; ++iter) {
        

        int current_animal_count = animals.size();
        
        for (int i = 0; i < current_animal_count; ++i) {
            Animal* current_animal = animals[i];
            
          
            if (current_animal->energy <= 0) continue;
            
      
            current_animal->observe(current_animal);
            
            
            int result = current_animal->move(current_animal);
            
 
            if (result != 100000 && result >= 0 && result < (int)animals.size()) {
                if (animals[result]->energy > 0) {
                    animals[result]->energy = 0; // 사망 처리
                }
            }
            if (current_animal->energy > 0) {
                Animal* baby = current_animal->giveBirth(current_animal);
                if (baby != nullptr) {
                    animals.push_back(baby); // 리스트에 추가
                    baby->animals_list_ptr = &animals; // 포인터 연결
                    
                    
                    int baby_idx = animals.size() - 1;
                    int marker = 0;
                    if (baby->birthThreshold == 15) {
                       marker = -1000000 - baby_idx;
                    } else {
                        marker = -2000000 - baby_idx;
                    }
                    globalMap[baby->loc.x][baby->loc.y] = marker;
                }                     
            }

            
            current_animal->energy -= current_animal->movingCost;
            
            // 굶어 죽음 처리
            if (current_animal->energy <= 0) {
                current_animal->energy = 0;
            }

        } // 행동 루프 끝

        
        std::vector<Animal*> survivors;
        survivors.reserve(animals.size());
        
        for (int i = 0; i < (int)animals.size(); ++i) {
            Animal* anim = animals[i];
            if (!anim) continue;

            if (anim->energy > 0) {
                survivors.push_back(anim);
            } else {
 
                if (anim->viewArray != nullptr) {
                    for (int v = 0; v < 2 * anim->viewRange + 1; v++) {
                        free(anim->viewArray[v]);
                    }
                    free(anim->viewArray);
                }
                
         
                if (anim->birthThreshold == 15) {
                    Herbivore* h = (Herbivore*)anim;
                    delete h;
                } else {
                    Carnivore* c = (Carnivore*)anim;
                    delete c;
                }
            }
        }
        
        animals = survivors;
        

        for (auto* a : animals) {
            if (a) a->animals_list_ptr = &animals;
        }

   
        for (int r = 0; r < 50; r++) {
            for (int c = 0; c < 50; c++) {
                if (globalMap[r][c] < 0) {
                    globalMap[r][c] = 0;
                }
            }
        }

   
        for (int i = 0; i < (int)animals.size(); ++i) {
            Animal* anim = animals[i];
            int r = anim->loc.x;
            int c = anim->loc.y;

            int marker = 0;
            if (anim->birthThreshold == 15) {
                marker = -1000000 - i; // Herbivore
            } else { 
                marker = -2000000 - i; // Carnivore
            }
            globalMap[r][c] = marker;
        }

        for (int r = 0; r < 50; r++) {
            for (int c = 0; c < 50; c++) {
                int val = globalMap[r][c];
      
                if (val >= 0 && val < 5) { 
                    globalMap[r][c]++;
                }
            }
        }

        
        int turn = iter + 1;

    } 

    long long finalVal = 0;
    for (int i = 1; i < FIELD_SIZE * FIELD_SIZE; ++i) {
        int x = (i - 1) % FIELD_SIZE;
        int y = (i - 1) / FIELD_SIZE;
        finalVal += std::abs(static_cast<long long>(i) * globalMap[x][y]);
        finalVal %= 100000000;
    }
    
    std::cout << "test1 result: " << finalVal << std::endl;

    for (int i = 0; i < FIELD_SIZE; ++i) {
        delete[] globalMap[i];
    }
    delete[] globalMap;

    return 0;
}