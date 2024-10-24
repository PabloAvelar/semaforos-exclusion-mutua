//
// Created by Avelar on 10/24/2024.
//

#ifndef NODE_H
#define NODE_H

struct Node {
    struct Node* next;
    struct Node* prev;
    int value;
};

#endif //NODE_H
