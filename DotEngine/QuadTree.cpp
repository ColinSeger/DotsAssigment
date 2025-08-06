#include "QuadTree.h"

QuadTree::QuadTree()
{
    nodes.reserve(CAPACITY);
    treeBoundingBox = BoundingBox();
}

QuadTree::QuadTree(BoundingBox boundingBox)
{
    nodes.reserve(CAPACITY);
    treeBoundingBox = boundingBox;
}

void QuadTree::Insert(Node* newNode)
{
    if(!newNode || !treeBoundingBox.InBounds(newNode->position.x, newNode->position.y)) return;
    if( glm::abs(treeBoundingBox.upperLeft.x - treeBoundingBox.bottomRight.x) <= 1 && 
        glm::abs(treeBoundingBox.upperLeft.y - treeBoundingBox.bottomRight.y) <= 1)
    {
        if(nodes.size() >= CAPACITY){
            nodes.push_back(newNode);
            return;
        }
    }

    if((treeBoundingBox.upperLeft.x + treeBoundingBox.bottomRight.x) / 2 >= newNode->position.x){
        if((treeBoundingBox.upperLeft.y + treeBoundingBox.bottomRight.y) / 2 >= newNode->position.y){
            if(!northWest){
                glm::vec2 topLeft = treeBoundingBox.upperLeft;
                glm::vec2 bottomRight = treeBoundingBox.bottomRight;
                bottomRight.x = (topLeft.x + bottomRight.x) / 2;
                bottomRight.y = (topLeft.y + bottomRight.y) / 2;
                BoundingBox newBox = BoundingBox(topLeft, bottomRight);
                northWest = new QuadTree(newBox);
            }
            northWest->Insert(newNode);
            return;
        }
        if(!southWest){
            glm::vec2 topLeft = treeBoundingBox.upperLeft;
            glm::vec2 bottomRight = treeBoundingBox.bottomRight;
            topLeft.y = (topLeft.y + bottomRight.y) / 2;
            bottomRight.x = (topLeft.x + bottomRight.x) / 2;
            BoundingBox newBox = BoundingBox(topLeft, bottomRight);
            southWest = new QuadTree(newBox);
        }
        southWest->Insert(newNode);
        return;
    }
    if((treeBoundingBox.upperLeft.y + treeBoundingBox.bottomRight.y) / 2 >= newNode->position.y){
        if(!northEast){
            glm::vec2 topLeft = treeBoundingBox.upperLeft;
            glm::vec2 bottomRight = treeBoundingBox.bottomRight;
            topLeft.x = (topLeft.x + bottomRight.x) / 2;
            bottomRight.y = (topLeft.y + bottomRight.y) / 2;
            BoundingBox newBox = BoundingBox(topLeft, bottomRight);
            northEast = new QuadTree(newBox);
        }
        northEast->Insert(newNode);
    }
    if(!southEast){
        glm::vec2 topLeft = treeBoundingBox.upperLeft;
        glm::vec2 bottomRight = treeBoundingBox.bottomRight;
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        southEast = new QuadTree(newBox);
    }
    southEast->Insert(newNode);
}

void QuadTree::CleanUp()
{
    if(northWest){
        northWest->CleanUp();
    }
    if(northEast){
        northEast->CleanUp();
    }
    if(southWest){
        southWest->CleanUp();
    }
    if(southEast){
        southEast->CleanUp();
    }
    delete this;
}