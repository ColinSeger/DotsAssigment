#pragma once
#include "glm/glm.hpp"
#include "../Engine/DotRenderer.h"
#include <vector>
#include <array>

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

    glm::vec2 GetPosition(){
        return position;
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
        return InBounds({xPos, yPos});
    }
    bool InBounds(glm::vec2 position){
        if(position.x >= upperLeft.x && position.x <= bottomRight.x
            && position.y >= upperLeft.y && position.y <= bottomRight.y){
            return true;
        }
        return false;
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
    const static int MIN_BOX_SIZE = 20;

    BoundingBox treeBoundingBox;

    std::vector<Node> nodes;

    std::array<QuadTree*, CAPACITY> directions = {nullptr, nullptr, nullptr, nullptr};
public:
    QuadTree();
    QuadTree(BoundingBox boundingBox);

    void Insert(Node* node);

    inline void SubDivide();

    std::vector<Node> Search(glm::vec2 position);

    bool InRange(glm::vec2 position, float range);

    void CleanUp();

    void DebugDraw(DotRenderer* render){
        glm::vec2 topRight = {treeBoundingBox.upperLeft.x, treeBoundingBox.bottomRight.y};
        glm::vec2 bottomLeft = {treeBoundingBox.bottomRight.x, treeBoundingBox.upperLeft.y};

        render->DrawLineBetweenPoints(treeBoundingBox.upperLeft, topRight);
        render->DrawLineBetweenPoints(treeBoundingBox.upperLeft, bottomLeft);
        render->DrawLineBetweenPoints(treeBoundingBox.bottomRight, topRight);
        render->DrawLineBetweenPoints(treeBoundingBox.bottomRight, bottomLeft);
        for(QuadTree* tree : directions){
            if(!tree) continue;
            tree->DebugDraw(render);
        }
    }

    BoundingBox GetBounds(){
        return treeBoundingBox;
    }
};

