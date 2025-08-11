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

void QuadTree::Insert(PhysicsComponent* newNode)
{
    if(!newNode || !treeBoundingBox.InBounds(newNode->GetPosition())) return;

    if(nodes.size() < CAPACITY && !directions[0]){
        nodes.push_back(newNode);
        // AddNode(newNode);
        return;
    }
    if(!directions[0]){
        SubDivide();
    }
    for(QuadTree* tree : directions){
        for(auto position : nodes){
            tree->Insert(position);
            // break;
        }
        
        tree->Insert(newNode);
    }
    // int n = sizeof(nodes) / sizeof(nodes[0]);
    // ClearNodes();
    nodes.clear();
/*
    if((treeBoundingBox.upperLeft.x + treeBoundingBox.bottomRight.x) / 2 >= newNode->position.x){
        if((treeBoundingBox.upperLeft.y + treeBoundingBox.bottomRight.y) / 2 >= newNode->position.y){
            if(!directions[0]){
                glm::vec2 topLeft = treeBoundingBox.upperLeft;
                glm::vec2 bottomRight = treeBoundingBox.bottomRight;
                bottomRight.x = (topLeft.x + bottomRight.x) / 2;
                bottomRight.y = (topLeft.y + bottomRight.y) / 2;
                BoundingBox newBox = BoundingBox(topLeft, bottomRight);
                directions[0] = new QuadTree(newBox);
            }
            directions[0]->Insert(newNode);
            return;
        }
        if(!directions[1]){
            glm::vec2 topLeft = treeBoundingBox.upperLeft;
            glm::vec2 bottomRight = treeBoundingBox.bottomRight;
            topLeft.y = (topLeft.y + bottomRight.y) / 2;
            bottomRight.x = (topLeft.x + bottomRight.x) / 2;
            BoundingBox newBox = BoundingBox(topLeft, bottomRight);
            directions[1] = new QuadTree(newBox);
        }
        directions[1]->Insert(newNode);
        return;
    }
    if((treeBoundingBox.upperLeft.y + treeBoundingBox.bottomRight.y) / 2 >= newNode->position.y){
        if(!directions[2]){
            glm::vec2 topLeft = treeBoundingBox.upperLeft;
            glm::vec2 bottomRight = treeBoundingBox.bottomRight;
            topLeft.x = (topLeft.x + bottomRight.x) / 2;
            bottomRight.y = (topLeft.y + bottomRight.y) / 2;
            BoundingBox newBox = BoundingBox(topLeft, bottomRight);
            directions[2] = new QuadTree(newBox);
        }
        directions[2]->Insert(newNode);
        return;
    }
    if(!directions[3]){
        glm::vec2 topLeft = treeBoundingBox.upperLeft;
        glm::vec2 bottomRight = treeBoundingBox.bottomRight;
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[3] = new QuadTree(newBox);
    }
    directions[3]->Insert(newNode);
    */
}

inline void QuadTree::SubDivide()
{
    {// Top Left
        glm::vec2 topLeft = treeBoundingBox.UpperLeft();
        glm::vec2 bottomRight = treeBoundingBox.BottomRight();
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[0] = new QuadTree(newBox);
    }
    {// Bottom Left
        glm::vec2 topLeft = treeBoundingBox.UpperLeft();
        glm::vec2 bottomRight = treeBoundingBox.BottomRight();
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[1] = new QuadTree(newBox);
    }
    {// Top Right
        glm::vec2 topLeft = treeBoundingBox.UpperLeft();
        glm::vec2 bottomRight = treeBoundingBox.BottomRight();
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[2] = new QuadTree(newBox);
    }
    {// Bottom Right
        glm::vec2 topLeft = treeBoundingBox.UpperLeft();
        glm::vec2 bottomRight = treeBoundingBox.BottomRight();
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[3] = new QuadTree(newBox);
    }
}

void QuadTree::Search(std::vector<PhysicsComponent*>& result, glm::vec2 position)
{
    float range = 5;
    if(!InRange(position, range)){
        std::vector<PhysicsComponent*> empty;
        return;
    }
    if(nodes.size() > 0){
        result.insert(result.end(), nodes.begin(), nodes.end());
    }
    for(QuadTree* tree : directions){
        if(!tree || !tree->InRange(position, range)) continue;
        tree->Search(result, position);
        // result.insert(result.end(), contains.begin(), contains.end());
    }
    return;
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
    // if(!directions[0]) delete this;
    for(QuadTree* tree : directions){
        if(!tree) break;
        tree->CleanUp();
    }
    delete this;
}

constexpr void QuadTree::ClearNodes()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        nodes[i] = nullptr;
    }
}

constexpr void QuadTree::AddNode(PhysicsComponent* newNode)
{
    for (int i = 0; i < CAPACITY; i++)
    {
        if(!nodes[i]){
            nodes[i] = newNode;
        }
    }
}