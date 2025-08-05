#pragma once
#include "Dot.h"
#include "glm/glm.hpp"

struct Node
{
    float x = 0;
    float y = 0;

    Node(){

    }

    Node(float x, float y){

    }
};

struct BoundingBox
{
    glm::vec2 upperLeft;
    glm::vec2 bottomRight;

    bool InBounds(float xPos, float yPos){
        if(xPos < upperLeft.x || yPos > bottomRight.y) return false;
        return true;
    }
};

class QuadTree
{
    const static int CAPACITY = 4;

    BoundingBox treeBoundingBox;

    Node nodes[CAPACITY];

    // Children
    QuadTree* northWest = nullptr;
    QuadTree* northEast = nullptr;
    QuadTree* southWest = nullptr;
    QuadTree* southEast = nullptr;

    QuadTree();
    QuadTree(BoundingBox boundingBox);

    void Insert(Node* node);

    void SubDivide();

    // void QueryRange();
};

