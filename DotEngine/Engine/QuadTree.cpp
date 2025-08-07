#include "../Engine/QuadTree.h"

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
    if( glm::abs(treeBoundingBox.upperLeft.x - treeBoundingBox.bottomRight.x) <= MIN_BOX_SIZE && 
        glm::abs(treeBoundingBox.upperLeft.y - treeBoundingBox.bottomRight.y) <= MIN_BOX_SIZE)
    {
        if(nodes.size() <= CAPACITY){
            Node node = Node(newNode->GetPosition());
            nodes.push_back(node);
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
        return;
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

std::vector<Node>& QuadTree::Search(glm::vec2 position)
{
    std::vector<Node> empty;
    if(!treeBoundingBox.InBounds(position)){
        return empty;
    }
    if(nodes.size() > 0){
        return nodes;
    }
    if((treeBoundingBox.upperLeft.x + treeBoundingBox.bottomRight.x) / 2 >= position.x){
        if((treeBoundingBox.upperLeft.y + treeBoundingBox.bottomRight.y) / 2 >= position.y){
            if(!northWest) return empty;
            return northWest->Search(position);
        }
        if(!southWest) return empty;
        return southWest->Search(position);
    }
    if((treeBoundingBox.upperLeft.y + treeBoundingBox.bottomRight.y) / 2 >= position.y){
        if(!northEast) return empty;
        return northEast->Search(position);
    }
    if(!southEast) return empty;
    return southEast->Search(position);
}

// std::vector<Node*>& QuadTree::GetNeighbors(glm::vec2 position, BoundingBox range){
//     std::vector<Node*> result;
//     auto res1 = Search(range.upperLeft);
//     auto res2 = Search(range.bottomRight);
//     for (int i = 0; i < res1.size(); i++)
//     {
//         result.push_back(res1[i]);
//     }
//     for (int i = 0; i < res2.size(); i++)
//     {
//         result.push_back(res2[i]);
//     }
//     return result;
// }

void QuadTree::CleanUp()
{
    // for(int i = 0; i < nodes.size(); i++){
    //     // delete nodes[i];
    // }
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