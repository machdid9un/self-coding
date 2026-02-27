#ifndef SINGLYLINKEDLIST_HPP
#define SINGLYLINKEDLIST_HPP

#include <iostream>
#include <string>


/**********************************************************************************
YOU MUST EDIT THE studentID, nodeStructSize, and nodeStructPaddingSize BELOW!!!
***********************************************************************************/
const std::string studentID = "2025150058";
const int nodeStructSize =232; // size of struct Node
const int nodeStructAlignmentSize =8; // alignment of struct Node
/**********************************************************************************
YOU MUST EDIT THE studentID, nodeStructSize, and nodeStructPaddingSize BELOW!!!
***********************************************************************************/

struct Node;
struct SubNode;


// TODO: Implement the struct SubNode
struct SubNode {
    int digit; Node* parentNode; SubNode*greatestDivisorPtr;
};

// TODO: Implement the struct Node
struct Node {
    int num; SubNode subNodeArray[9]; Node*next;
};

void initSinglyLinkedList(Node*& head, int* array, int length);

int addNode(Node*& head, int value);

int removeNode(Node*& head, int value);

#endif // SINGLYLINKEDLIST_HPP
