#pragma once
#include "glm/glm.hpp"
#include "../Engine/DotRenderer.h"
#include "../Engine/Components/PhysicsComponent.h"
#include <vector>
#include <array>
struct BoundingBox
{
public:
    glm::vec2 upperLeft;
    glm::vec2 bottomRight;

    BoundingBox(){
        upperLeft = {0, 0};
        bottomRight = {0, 0};
    }
    BoundingBox(glm::vec2 newLeft, glm::vec2 newRight){
        upperLeft = newLeft;
        bottomRight = newRight;
    }

    bool InBounds(float xPos, float yPos){
        return InBounds({xPos, yPos});
    }
    inline bool InBounds(glm::vec2 position){
        if(position.x >= upperLeft.x && position.x <= bottomRight.x
            && position.y >= upperLeft.y && position.y <= bottomRight.y){
            return true;
        }
        return false;
    }

    const glm::vec2 UpperLeft()
    {
        return upperLeft;
    }
    const glm::vec2 BottomRight()
    {
        return bottomRight;
    }
};
const int CAPACITY = 8;
class QuadTree
{
public:
    QuadTree();
    QuadTree(BoundingBox boundingBox);

    /*Tries to add new node, will crash if nullptr is inserted*/
    bool Insert(PhysicsComponent* newNode);

    void Search(std::vector<PhysicsComponent*>& result, glm::vec2 position);

    /*Performs a check on bounding box to see if they are in range*/
    bool InRange(glm::vec2 position, float range);

    void CleanUp();

    void DebugDraw(DotRenderer* render){
        glm::vec2 topRight = {treeBoundingBox.UpperLeft().x, treeBoundingBox.BottomRight().y};
        glm::vec2 bottomLeft = {treeBoundingBox.BottomRight().x, treeBoundingBox.UpperLeft().y};

        render->DrawLineBetweenPoints(treeBoundingBox.UpperLeft(), topRight);
        render->DrawLineBetweenPoints(treeBoundingBox.UpperLeft(), bottomLeft);
        render->DrawLineBetweenPoints(treeBoundingBox.BottomRight(), topRight);
        render->DrawLineBetweenPoints(treeBoundingBox.BottomRight(), bottomLeft);
        for(QuadTree* tree : directions){
            if(!tree) continue;
            tree->DebugDraw(render);
        }
    }

    BoundingBox& GetBounds(){
        return treeBoundingBox;
    }

private:
    std::array<QuadTree*, 4> directions = {nullptr, nullptr, nullptr, nullptr};
    
    std::vector<PhysicsComponent*> nodes;
    
    BoundingBox treeBoundingBox;

    constexpr void ClearNodes();
    constexpr void AddNode(PhysicsComponent* node);
    inline void SubDivide();
};

