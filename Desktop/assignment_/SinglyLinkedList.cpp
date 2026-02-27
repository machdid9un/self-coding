#include "SinglyLinkedList.hpp"
#include <algorithm>
#include <iostream>
void initSinglyLinkedList(Node*& head, int* array, int length) {
    // TODO: Implement this function to initialize a new singly-linked list from an array of integers.
    // input: head   - A reference to the head pointer.
    //        array  - A pointer to an unsorted array of integers that will become the 'num' values for the Nodes.
    //        length - The number of elements in the 'array'.
    // output: This function does not return a value. It should create the linked list and modify the 'head' pointer directly.
    // For your reference, a sample solution might have around 30-40 lines of code, potentially including a sorting step.
    std::sort(array, array+length);
    head = nullptr;
    Node * tail = nullptr;
    for (int k=0; k <length; k++){
        Node * newnode = new Node;
        newnode->num= array[k];
        newnode->next = nullptr;
        ///서브노드 저장
        for (int n=0;n<=8; n++){
            SubNode * newsubnode = &newnode->subNodeArray[n];
            newsubnode->digit=n+1;
            newsubnode->parentNode = newnode;
            newsubnode->greatestDivisorPtr = nullptr;
            
    }

    if (head== nullptr){
        head = newnode;
        tail= newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }
        }
        Node * iter= head;
         while (iter!= nullptr){
    if (iter->next!=nullptr){
            for (int n=0; n<9; n++ ){
                SubNode * newsubnode =  &iter->subNodeArray[n];
            int j = (iter->num*10 +n+1);
            int gd=1;
            for (int y=1; y<=9;y++){
                if (j%y==0){
                    gd=y;
                }
            }///////////used chat gpt to debug and avoid infinite loop////
            Node*nextnode =iter->next;
            newsubnode->greatestDivisorPtr =&nextnode->subNodeArray[gd-1];
            }

}   iter= iter->next;//used chat gpt to debug and avoid infinite loop////
}
}
int addNode(Node*& head, int value) {
    int index=0;
    if (head == nullptr) {
        Node* newNode = new Node;
        newNode->num = value;
        newNode->next = nullptr;
        head = newNode;
        for (int n=0;n<=8; n++){
            SubNode * newsubnode = &newNode->subNodeArray[n];
            newsubnode->digit=n+1;
            newsubnode->parentNode = newNode;
            newsubnode->greatestDivisorPtr = nullptr;            
    }
        return 0;
    }
    if (value == head->num){
        return -1;
    }
    if (value < head->num) {
        Node* newNode = new Node;
        newNode->num = value;
        newNode->next = head;
        head = newNode;
        for (int n=0;n<=8; n++){
            SubNode * newsubnode = &newNode->subNodeArray[n];
            newsubnode->digit=n+1;
            newsubnode->parentNode = newNode;
            newsubnode->greatestDivisorPtr = nullptr;
            
    }
    Node * iter= head;
         while (iter!= nullptr){
    if (iter->next!=nullptr){
            for (int n=0; n<9; n++ ){
                SubNode * newsubnode =  &iter->subNodeArray[n];
            int j = (iter->num*10 +n+1);
            int gd=1;
            for (int y=1; y<=9;y++){
                if (j%y==0){
                    gd=y;
                }
            }///////////used chat gpt to debug and avoid infinite loop////
            Node*nextnode =iter->next;
            newsubnode->greatestDivisorPtr =&nextnode->subNodeArray[gd-1];
            }

}   iter= iter->next;//used chat gpt to debug and avoid infinite loop////
}
    return 0;
} 

    Node* cur = head;
    while (cur->next != nullptr && cur->next->num < value) {
        cur = cur->next;
        index++;
    }

    if (cur->next != nullptr && cur->next->num == value) {
        return -1;
    }

    Node* newNode = new Node;
    newNode->num = value;
    newNode->next = cur->next;
    cur->next = newNode;
    for (int n=0;n<=8; n++){
            SubNode * newsubnode = &newNode->subNodeArray[n];
            newsubnode->digit=n+1;
            newsubnode->parentNode = newNode;
            newsubnode->greatestDivisorPtr = nullptr;
            
    }
    Node * iter= head;
         while (iter!= nullptr){
    if (iter->next!=nullptr){
            for (int n=0; n<9; n++ ){
                SubNode * newsubnode =  &iter->subNodeArray[n];
            int j = (iter->num*10 +n+1);
            int gd=1;
            for (int y=1; y<=9;y++){
                if (j%y==0){
                    gd=y;
                }
            }///////////used chat gpt to debug and avoid infinite loop////
            Node*nextnode =iter->next;
            newsubnode->greatestDivisorPtr =&nextnode->subNodeArray[gd-1];
            }

}   iter= iter->next;//used chat gpt to debug and avoid infinite loop////
}


    return index+1;  
}


int removeNode(Node*& head, int value) {
    // TODO: Implement this function to find and remove a Node from the linked list.
    // input: head  - A reference to the head pointer of the linked list.
    //        value - The 'num' of the Node to be found and removed.
    // output: The function should return the original 0-based index of the removed Node.
    //         If no Node with the given 'value' is found, it should return -1.
    // For your reference, a sample solution for this function might have around 25-30 lines of code.
    Node * alihead = head;
    int k=1;
    if (head==nullptr){
        return -1;
    }
    if(alihead->num==value){
            Node* delnode= head;
            head=alihead->next;
            delete delnode;
            return 0;
    }

    while(alihead->next != nullptr){
     if(alihead->next->num==value){///alihead next지우기
            Node* delnode= alihead->next;
            alihead->next= alihead->next->next;
            if (alihead->next!=nullptr){
            for (int n=0; n<9; n++ ){
                SubNode * newsubnode =  &alihead->subNodeArray[n];
            int j = (alihead->num*10 +n+1);
            int gd=1;
            for (int y=1; y<=9;y++){
                if (j%y==0){
                    gd=y;
                }
            }
            Node*nextnode =alihead->next;
            newsubnode->greatestDivisorPtr =&nextnode->subNodeArray[gd-1];
            }

} else {
    for (int n=0; n<9; n++){
        alihead->subNodeArray[n].greatestDivisorPtr= nullptr;
    }
}
            delete delnode;
            
            return k;
    }else if(alihead->next->num<value){
        alihead= alihead->next;
        k++;
    }else if(alihead->next->num>value){
        return -1;
    }
}
return -1;
}


