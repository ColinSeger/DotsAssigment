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

std::vector<Node> QuadTree::Search(glm::vec2 position)
{
    std::vector<Node> result;
    float range = 5;
    if(!InRange(position, range)){
        std::vector<Node> empty;
        return empty;
    }
    if(nodes.size() > 0){
        result.insert(result.end(), nodes.begin(), nodes.end());
    }
    std::vector<QuadTree*> toSearch;
    if(northWest && northWest->InRange(position, range)){
        toSearch.push_back(northWest);
    }
    if(southWest && southWest->InRange(position, range)){
        toSearch.push_back(southWest);
    }
    if(northEast && northEast->InRange(position, range)){
        toSearch.push_back(northEast);
    }
    if(southEast && southEast->InRange(position, range)){
        toSearch.push_back(southEast);
    }
    for(QuadTree* tree : toSearch){
        auto contains = tree->Search(position);
        result.insert(result.end(), contains.begin(), contains.end());
    }
    return result;
}

bool QuadTree::InRange(glm::vec2 position, float range)
{
    // return treeBoundingBox.InBounds(position);
    glm::vec2 topLeft = position - range;
    if(treeBoundingBox.InBounds(topLeft)){
        return true;
    }
    glm::vec2 topRight = {position.x + range, position.y - range};
    if(treeBoundingBox.InBounds(topRight)){
        return true;
    }
    glm::vec2 bottomLeft = {position.x - range, position.y + range};
    if(treeBoundingBox.InBounds(bottomLeft)){
        return true;
    }
    glm::vec2 bottomRight = position + range;
    if(treeBoundingBox.InBounds(bottomRight)){
        return true;
    }
    return false;
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