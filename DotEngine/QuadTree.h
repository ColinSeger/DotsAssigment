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
    bool InBounds(glm::vec2 position){
        return (position.x >= upperLeft.x && position.x <= bottomRight.x
            && position.y >= upperLeft.y && position.y <= bottomRight.y);
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
    const static int MIN_BOX_SIZE = 10;

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

    std::vector<Node*>& GetNeighbors(glm::vec2 position, BoundingBox range);

    std::vector<Node*>& Search(glm::vec2 position);

    void CleanUp();

    void DebugDraw(DotRenderer* render){
        glm::vec2 topRight = {treeBoundingBox.upperLeft.x, treeBoundingBox.bottomRight.y};
        glm::vec2 bottomLeft = {treeBoundingBox.bottomRight.x, treeBoundingBox.upperLeft.y};

        render->DrawLineBetweenPoints(treeBoundingBox.upperLeft, topRight);
        render->DrawLineBetweenPoints(treeBoundingBox.upperLeft, bottomLeft);
        render->DrawLineBetweenPoints(treeBoundingBox.bottomRight, topRight);
        render->DrawLineBetweenPoints(treeBoundingBox.bottomRight, bottomLeft);

        if(northWest){
            northWest->DebugDraw(render);
        }
        if(northEast){
            northEast->DebugDraw(render);
        }
        if(southWest){
            southWest->DebugDraw(render);
        }
        if(southEast){
            southEast->DebugDraw(render);
        }
    }

    BoundingBox GetBounds(){
        return treeBoundingBox;
    }
};

