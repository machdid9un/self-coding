#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include "gene.cpp"
int main() {
    int simulate_num = 1;
    double birthrate= 0.8;
    ////기본세팅
    int initial = 10;
    std::vector <std::unique_ptr<Male>> manlist;
    std::vector <std::unique_ptr<Female>> womanlist;
    //유전병케이스에 따라서 초기화시킴
    for (int i=0; i< initial; i++){
        Male* abnormalman= new Male;
        abnormalman->autosome[0]=1;
        abnormalman->autosome[1]= 1;
        manlist.push_back(abnormalman);
        Female *abnormalwoman= new Female();
        abnormalwoman->autosome[0]=1;
        abnormalwoman->autosome[1]= 1;
        womanlist.push_back(abnormalwoman);
    }

    for (int i=0; i< initial*2; i++){
        Male* abnormalman= new Male();
        abnormalman->autosome[0]=1;
        abnormalman->autosome[1]= 0;
        manlist.push_back(abnormalman);
        Female *abnormalwoman= new Female();
        abnormalwoman->autosome[0]=1;
        abnormalwoman->autosome[1]= 0;
        womanlist.push_back(abnormalwoman);
    }

    for (int i=0; i< initial*4; i++){
        Male* abnormalman= new Male();
        abnormalman->autosome[0]=0;
        abnormalman->autosome[1]= 0;
        manlist.push_back(abnormalman);
        Female *abnormalwoman= new Female();
        abnormalwoman->autosome[0]=0;
        abnormalwoman->autosome[1]= 0;
        womanlist.push_back(abnormalwoman);
    }

    //랜덤으로 셔플하기 
    std::random_device rd; 
    std::mt19937 g(rd()); 
    std::shuffle(manlist.begin(), manlist.end(), g);
    std::random_device rd2; 
    std::mt19937 g(rd2()); 
    std::shuffle(womanlist.begin(), womanlist.end(), g);

    int k= manlist.size()/4;
    int j= manlist.size()/5;
    //랜덤으로 성염색체 이상을 기부
    std::random_device rd3; 
    std::mt19937 gen(rd3()); 
    std::uniform_int_distribution<int> dis(0, manlist.size()-1);
    
    for (int i=0; i<k; i++){
        int randomNumber = dis(gen);
        manlist[randomNumber]->chromosome[0][1]= 0;
        womanlist[randomNumber]->chromosome[0][1]= 0;
    }

    for (int i=0; i<j; i++){
        int randomNumber = dis(gen);
        womanlist[randomNumber]->chromosome[1][1]= 0;
    }




    int simulate_time = 20;// simulate_time x10 년 간 진행. 시간은 10년 기준으로 흐름
    //본격 시뮬레이팅 스타트
    //나이먹고 -> 상염색체 유전병 발현 체크 안해도됨(사망영향없음)->나이 70넘으면 사망처리
    //->성염색체 유전병 발현 체크(30세 넘어가면 사망)->출산율 맡게 아기 탄생시키기 ->
    for (int decade=0; decade<simulate_time; decade++){
        // 나이 먹고 사망 처리: 나이 70 넘으면 사망
        manlist.erase(std::remove_if(manlist.begin(), manlist.end(), [](Male* m){ return m->age >= 70; }), manlist.end());
        womanlist.erase(std::remove_if(womanlist.begin(), womanlist.end(), [](Female* f){ return f->age >= 70; }), womanlist.end());

        // 성염색체 유전병 발현 체크 (30세 넘어가면 사망)
        manlist.erase(std::remove_if(manlist.begin(), manlist.end(), [](Male* m){ return m->age > 30 && m->chromosome[0][1] == 0; }), manlist.end());
        womanlist.erase(std::remove_if(womanlist.begin(), womanlist.end(), [](Female* f){ return f->age > 30 && (f->chromosome[0][1] == 0 && f->chromosome[1][1] == 0); }), womanlist.end());

        //출산율에 맞게 출산!!
        std::vector <Male*> capable_male;
        std::vector <Female*> capable_female;
        for (auto & man: manlist){
            if (man->age>=20 && man->age<=40){
                capable_male.push_back(man);
            }
        }
        for (auto & woman: womanlist){
            if (woman->age>=20 && woman->age<=40){
                capable_female.push_back(woman);
            }
        }
        std::random_device rd; 
        std::mt19937 g(rd()); 
        std::shuffle(capable_male.begin(), capable_male.end(), g);
        std::shuffle(capable_female.begin(), capable_female.end(), g);
        int size=0;
        if (capable_male.size()>=capable_female.size()){
            size = capable_female.size();
        }else {size = capable_male.size();}
        std::random_device rd4; 
        std::mt19937 gen(rd4()); 
        std::uniform_int_distribution<int> dis(0, size-1);
        //출산률 = 연간 총출생아수/가임연령층수    
       int baby_size= birthrate*capable_female.size();
       for (int i=0; i<baby_size; i++){
            int randomnum = dis(gen);
            auto child= have_a_child(capable_male[randomnum], capable_female[randomnum]);
            if (child->sex ==0){
                manlist.push_back(static_cast<Male*>(child));
            } else{
                womanlist.push_back(static_cast<Female*>(child));
            }
       }
 
        // 나이 증가
        for (auto& man : manlist) man->age += 10;
        for (auto& woman : womanlist) woman->age += 10;
        
        int popularity = manlist.size() + womanlist.size();
        std::cout<<"현재 인구수:"<<popularity<<std::endl;

        int autosome_count =0;
        int chromosome_count=0;
        for (auto& man: manlist){
            if (man->is_chromosome==1){
                chromosome_count ++;
            }
            if (man->marker==1){
                autosome_count++;
            }
        }
        for (auto& woman: womanlist){
            if (woman->is_chromosome==1){
                chromosome_count ++;
            }
            if (woman->marker==1){
                autosome_count++;
            }
        }

        std::cout<<"상염색체 유전병 수: "<<autosome_count<<std::endl;
        std::cout<<"성염색체 유전병 수:"<<chromosome_count<<std::endl;

        
    }




}
