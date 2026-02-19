#include <iostream>
#include <vector>
#include <random>
static int getRandom() {
        // static을 붙여서 딱 한 번만 초기화되도록 함
        static std::mt19937 gen(std::random_device{}()); 
        static std::bernoulli_distribution dist(0.5); // 50% 확률로 true/false
        
        return dist(gen);
}
class Human {
    public:
    int autosome[2]{0,0};// 1,0으로 표시, 1은 우성 0은 열성 -- 이 유전병은 우성일 때 발현
    int chromosome[2][2];// 성염색체 X,Y [0][0], [1][0]-> x=1,y=0 차이 
    //[0][1] [1][1]->x에서 유전병 r유무  =0 없음 =1 있음
     //이 유전병은 x염색체 위의 열성 유전자. y염색체에서의 [1]에 들어갈 값은...

    int age;
    int marker=0;
    int sex;
    int is_chromosome=0;
    void information(){    
        if (sex==0){
            std::cout<<"male"<<std::endl;
        } else {std::cout<<"female"<<std::endl;}
        
        for (int k: autosome){
            if (k==1){
                marker=1;
                break;
            }
        }

        if (sex==0){
            if(chromosome[0][1]==1){
                is_chromosome=1;
            }
        }else{
            if (chromosome[0][1]==1 && chromosome[1][1]==1){
                is_chromosome=1;
            }
        }
        if (marker==1){
            std::cout<<"autosome disease: O"<<std::endl;
        } else{  std::cout<<"autosome disease: X"<<std::endl;}

        if (is_chromosome==1){
            std::cout<<"chromosome disease: O"<<std::endl;
        }else{std::cout<<"chromosome disease: X"<<std::endl;}

    }
    
    
};

class Male :public Human {
    public:
    Male(): Human() {
        chromosome[0][0]= 1;
        chromosome[1][0]= 0;
        chromosome[0][1] =1;
        chromosome[1][1]= -1;
        sex=0;
        age= 0;
        
    }

};
class Female :public Human {
    public:
    Female(): Human() {
        chromosome[0][0]= 1;
        chromosome[1][0]= 1;
        chromosome[0][1] =1;
        chromosome[1][1]=0;
        sex=1;
        age=0;
        
    }
};

Human* have_a_child(Male* man, Female* woman){
    int k= getRandom();
        if (k==0){
            Male* child= new Male();
            int y = getRandom();
            int j= getRandom();
            int v = getRandom();
            child->autosome[0]= man->autosome[y];
            child->autosome[1]= woman->autosome[j];
            child->chromosome[0][0]=1;
            child->chromosome[1][0]=0;
            child->chromosome[0][1]=woman->chromosome[v][1];
            child->chromosome[1][1]=-1;

            return child;
        } else{
            Female* child= new Female();
            int y = getRandom();
            int j= getRandom();
            int v = getRandom();
            child->autosome[0]= man->autosome[y];
            child->autosome[1]= woman->autosome[j];
            child->chromosome[0][0]=0;
            child->chromosome[1][0]=0;
            child->chromosome[0][1]=man->chromosome[0][1];
            child->chromosome[1][1]=woman->chromosome[v][1];

            return child;
        }    
}
