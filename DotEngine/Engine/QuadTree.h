#pragma once
#include "glm/glm.hpp"
#include "../Engine/DotRenderer.h"
#include "../Engine/Components/PhysicsComponent.h"
#include <vector>
#include <array>
class BoundingBox
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

    float Area(){
        float width = bottomRight.x - upperLeft.x;
        float height = bottomRight.y - upperLeft.y;
        return width * height;
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

const uint8_t CAPACITY = 32;
class QuadTree
{
public:
    QuadTree();
    QuadTree(BoundingBox boundingBox);

    void PreWarm(const unsigned int amount, unsigned int& depth);

    /*Tries to add new node, will crash if nullptr is inserted*/
    bool Insert(PhysicsComponent* newNode);

    void Search(std::vector<PhysicsComponent*>& result, glm::vec2 position);

    /*Performs a check on bounding box to see if they are in range*/
    bool InRange(glm::vec2 position, float range);

    void CleanUp();

    void DebugDraw(DotRenderer* render){
        if(!this) return;
        glm::vec2 topRight = {m_treeBoundingBox.UpperLeft().x, m_treeBoundingBox.BottomRight().y};
        glm::vec2 bottomLeft = {m_treeBoundingBox.BottomRight().x, m_treeBoundingBox.UpperLeft().y};

        render->DrawLineBetweenPoints(m_treeBoundingBox.UpperLeft(), topRight);
        render->DrawLineBetweenPoints(m_treeBoundingBox.UpperLeft(), bottomLeft);
        render->DrawLineBetweenPoints(m_treeBoundingBox.BottomRight(), topRight);
        render->DrawLineBetweenPoints(m_treeBoundingBox.BottomRight(), bottomLeft);
        for(QuadTree* tree : m_directions){
            if(!tree) continue;
            tree->DebugDraw(render);
        }
    }

    BoundingBox& GetBounds(){
        return m_treeBoundingBox;
    }

private:
    std::array<QuadTree*, 4> m_directions = {nullptr, nullptr, nullptr, nullptr};
    
    std::vector<PhysicsComponent*> m_nodes;
    
    BoundingBox m_treeBoundingBox;

    constexpr void ClearNodes();
    constexpr void AddNode(PhysicsComponent* node);
    inline void SubDivide();
};

