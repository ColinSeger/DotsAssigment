#pragma once
#include "glm/glm.hpp"
#include "../Engine/DotRenderer.h"
#include "../Engine/Components/PhysicsComponent.h"
#include <vector>
#include <array>
class BoundingBox
{
    const glm::vec2 upperLeft = {0, 0};
    const glm::vec2 bottomRight = {0, 0};
public:
    

    BoundingBox(){}
    constexpr BoundingBox(const glm::vec2 newLeft,const glm::vec2 newRight) : 
        upperLeft(newLeft), 
        bottomRight(newRight)
    {

    }

    constexpr bool InBounds(float xPos, float yPos) const {
        return InBounds({xPos, yPos});
    }
    constexpr bool InBounds(const glm::vec2 position) const {
        if(position.x >= upperLeft.x && position.x <= bottomRight.x
            && position.y >= upperLeft.y && position.y <= bottomRight.y){
            return true;
        }
        return false;
    }

    constexpr float Area() const {
        const float width = bottomRight.x - upperLeft.x;
        const float height = bottomRight.y - upperLeft.y;
        return width * height;
    }

    constexpr BoundingBox SplitTopLeft() const{
        const glm::vec2 botRight = glm::vec2{
            (upperLeft.x + bottomRight.x) / 2,
            (upperLeft.y + bottomRight.y) / 2
        };
        return BoundingBox(upperLeft, botRight);
    }
    constexpr BoundingBox SplitBottomLeft() const{
        const glm::vec2 botRight = glm::vec2{
            (upperLeft.x + bottomRight.x) / 2,
            bottomRight.y
        };
        const  glm::vec2 topLeft = glm::vec2{
            upperLeft.x,
            (upperLeft.y + bottomRight.y) / 2
        };
        return  BoundingBox(topLeft, botRight);
    }
    constexpr BoundingBox SplitTopRight() const{
        const glm::vec2 botRight = glm::vec2{
            bottomRight.x,
            (upperLeft.y + bottomRight.y) / 2
        };
        const  glm::vec2 topLeft = glm::vec2{
            (upperLeft.x + bottomRight.x) / 2,
            upperLeft.y
        };
        return BoundingBox(topLeft, botRight);
    }
    constexpr BoundingBox SplitBottomRight() const{
        const  glm::vec2 topLeft = glm::vec2{
            (upperLeft.x + bottomRight.x) / 2,
            (upperLeft.y + bottomRight.y) / 2
        };
        return BoundingBox(topLeft, bottomRight);
    }

    constexpr glm::vec2 UpperLeft() const {
        return upperLeft;
    }
    constexpr glm::vec2 BottomRight() const {
        return bottomRight;
    }
};

constexpr uint8_t CAPACITY = 64;
class QuadTree
{
public:
    QuadTree();
    QuadTree(const BoundingBox boundingBox);

    void PreWarm(const unsigned int amount, unsigned int& depth);

    /*Tries to add new node, will crash if nullptr is inserted*/
    bool Insert(PhysicsComponent* newNode);

    const void Search(std::vector<PhysicsComponent*>& result, const glm::vec2 position);

    /*Performs a check on bounding box to see if they are in range*/
    constexpr bool InRange(glm::vec2 position, float range);

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

    const BoundingBox& GetBounds(){
        return m_treeBoundingBox;
    }

private:
    std::array<QuadTree*, 4> m_directions = {nullptr, nullptr, nullptr, nullptr};
    
    std::vector<PhysicsComponent*> m_nodes;
    
    const BoundingBox m_treeBoundingBox;

    constexpr void ClearNodes();
    constexpr void AddNode(PhysicsComponent* node);
    inline void SubDivide();
};

