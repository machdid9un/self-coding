#include <iostream>
#include <vector>
#include <cstdlib> // rand(), srand()
#include <ctime>
#include <algorithm>


int main() {
    std::cout << "--- 프로그램 시작 확인 ---" << std::endl;
    std::cout << "현재 Seed: " << std::time(NULL) << std::endl;
    std::vector<std::string> position_name = {"탑","원딜","정글","서폿","미드"};
    std::srand(std::time(NULL));
    std::vector<int> firstpos {};
    std::vector<int> secondpos {};
    std::vector<int> poscheck {};

    for (int i=0; i<5; i++){
        int position_index1 = std::rand() %5;
        int position_index2 = std::rand() %5;
        while (position_index1==position_index2){
             position_index2 = std::rand() %5;
        }
        firstpos.push_back(position_index1);
        secondpos.push_back(position_index2);
    }//기본세팅


    
    std::vector <std::vector<int>> position(5);


    for (int i = 0; i < 5; i++) {
        position[i].push_back(i); // pos[0]은 이제 포지션 번호입니다!
    }

    //for (int i=0; i<5; i++){
        //if(firstpos[i] ==0){
        //    top.push_back(i);
       // }else if (firstpos[i]==1){
        //    bot.push_back(i);
       //}else if (firstpos[i]==2){
        //    jun.push_back(i);
       //}else if (firstpos[i]==3){
        //    sup.push_back(i);
       // }else if (firstpos[i]==4){
       //     mid.push_back(i);
       // }
   //}// ->너무 복잡. 포지션 번호 자체가 인덱스인걸 활용
   for (int i =0; i<5; i++){
   position[firstpos[i]].push_back(i);
   }//1지망 넣었다잉? position{0///,2,3}
   //2지망 바구니 만들기 {탑,탑,미드...}
   int secondwant[5]= {0,0,0,0,0};
   for (int i =0; i<5; i++){//여기서 커지는 i는 플레이어인덱스를 말하는것이다. 
   secondwant[i] = secondpos[i];
   }
   
    int result[5] = {-1, -1, -1, -1, -1}; 
    bool player_assigned[5] = {false};

    for (auto& pos: position){
        if (pos.size()==2){
            result[pos[0]]= pos[1];
            player_assigned[pos[1]]= true;
        } 
    }// 일단 1지망 1명인 경우 배정완료. 
    //지금 result example {-1,-1,0,2,-1} 0,2는 여기서 플레이어 인덱스
    int check =0;
    int second_index = 0;
    for (int i=0; i<5; i++){
        if (position[i].size()>2){
            check=0;
            for (int player_id: position[i]){
                
                if (check>0){
                    second_index =secondwant[player_id];
                    if (position[second_index].size()==1){
                        result[second_index] = player_id;
                        player_assigned[player_id]= true; //2지망 배정완료.

                    }
                }
                check++;//첫번째는 포지션인덱스니 건들 ㄴㄴ
            }
            for (int k=0; k<position[i].size();k++){
                if (player_assigned[position[i][k]]==false){
                    result[position[i][0]]= position[i][k];
                    player_assigned[position[i][k]]=true;
                    break;

                }
            }

        }

    }

    //마지막 배정
    for (int i=0; i<5; i++){
        if (player_assigned[i]==false){
            for (int k=0; k<5; k++){
                if (result[k]==-1){
                    result[k]= i;
                    player_assigned[i]=true;
                    break;
                }
            }
        }
    }
    
std::cout << "\n--- [최종 포지션 배정 결과] ---" << std::endl;

for (int i = 0; i < 5; i++) {
    // i는 포지션 인덱스(0:탑, 1:원딜...), result[i]는 플레이어 번호
    if (result[i] != -1) {
        std::cout << "플레이어 " << result[i] << "님 : " << position_name[i] << std::endl;
    } else {
        std::cout << position_name[i] << " : 배정 실패(오류)" << std::endl;
    }
}
}
