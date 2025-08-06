#pragma once
#include "Dot.h"
#include "glm/glm.hpp"

struct Node
{
    glm::vec2 position;
    
    Node(){
        position = {0,0};
    }

    Node(float x, float y){
        position = {x, y};
    }
    Node(glm::vec2 newPosition){
        position = newPosition;
    }
};

struct BoundingBox
{
public:
    glm::vec2 upperLeft;
    glm::vec2 bottomRight;

    BoundingBox(){

    }
    BoundingBox(glm::vec2 newLeft, glm::vec2 newRight){
        upperLeft = newLeft;
        bottomRight = newRight;
    }

    bool InBounds(float xPos, float yPos){
        if(xPos < upperLeft.x || yPos > bottomRight.y) return false;
        return true;
    }

    BoundingBox operator/(int divideBy){
        float upperX = (upperLeft.x / divideBy);
        float upperY = (upperLeft.y / divideBy);
        float bottomX = (bottomRight.x / divideBy);
        float bottomY = (bottomRight.y / divideBy);
        
        BoundingBox returnBounds;
        returnBounds.upperLeft = {upperX, upperY};
        returnBounds.bottomRight = {bottomX, bottomY};
        return returnBounds;
    }
};

class QuadTree
{
    const static int CAPACITY = 4;

    BoundingBox treeBoundingBox;

    std::vector<Node*> nodes;

    // Children
    QuadTree* northWest = nullptr;
    QuadTree* northEast = nullptr;
    QuadTree* southWest = nullptr;
    QuadTree* southEast = nullptr;
public:
    QuadTree();
    QuadTree(BoundingBox boundingBox);

    void Insert(Node* node);

    void SubDivide();

    // void QueryRange();

    void CleanUp();
};

