#include "../Engine/QuadTree.h"

QuadTree::QuadTree()
{
    nodes.reserve(CAPACITY);
    treeBoundingBox = BoundingBox({0, 0}, {10, 10});
}

QuadTree::QuadTree(BoundingBox boundingBox)
{
    treeBoundingBox = boundingBox;
    nodes.reserve(CAPACITY);
}

bool QuadTree::Insert(PhysicsComponent* newNode)
{
    assert(newNode && "You tried to add a non existent node to QuadTree");
    if(!treeBoundingBox.InBounds(newNode->GetPosition())) return false;

    if(nodes.size() < CAPACITY && !directions[0]){
        nodes.push_back(newNode);
        return true;
    }
    if(!directions[0]){
        SubDivide();
    }
    for(QuadTree* tree : directions){
        for(int i = 0; i < nodes.size(); i++){
            if(!nodes[i]) continue;
            if(tree->Insert(nodes[i])){
                nodes[i] = nullptr;
            }
        }
        tree->Insert(newNode);
    }
    nodes.clear();
    return true;
}

inline void QuadTree::SubDivide()
{
    glm::vec2 topLeft = treeBoundingBox.UpperLeft();
    glm::vec2 bottomRight = treeBoundingBox.BottomRight();
    // glm::vec2 newTopLeft = topLeft;
    // glm::vec2 newBottomRight = bottomRight;
    // BoundingBox newBox;
    {// Top Left
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[0] = new QuadTree(newBox);
    }
    {// Bottom Left
        topLeft = treeBoundingBox.UpperLeft();
        bottomRight = treeBoundingBox.BottomRight();
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[1] = new QuadTree(newBox);
    }
    {// Top Right
        topLeft = treeBoundingBox.UpperLeft();
        bottomRight = treeBoundingBox.BottomRight();
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[2] = new QuadTree(newBox);
    }
    {// Bottom Right
        topLeft = treeBoundingBox.UpperLeft();
        bottomRight = treeBoundingBox.BottomRight();
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[3] = new QuadTree(newBox);
    }
}

void QuadTree::Search(std::vector<PhysicsComponent*>& result, glm::vec2 position)
{
    const float range = 5;
    if(!InRange(position, range)){
        return;
    }
    if(nodes.size() > 0 || !directions[0]){
        result.insert(result.end(), nodes.begin(), nodes.end());
        return;
    }
    for(QuadTree* tree : directions){
        if(!tree->InRange(position, range)) continue;
        tree->Search(result, position);
    }
    return;
}

bool QuadTree::InRange(glm::vec2 position, float range)
{
    //Top left
    glm::vec2 location = position - range;
    if(treeBoundingBox.InBounds(location)){
        return true;
    }
    //Top right
    location = {position.x + range, position.y - range};
    if(treeBoundingBox.InBounds(location)){
        return true;
    }
    //Bottom left
    location = {position.x - range, position.y + range};
    if(treeBoundingBox.InBounds(location)){
        return true;
    }
    //Bottom right
    location = position + range;
    if(treeBoundingBox.InBounds(location)){
        return true;
    }
    return false;
}

void QuadTree::CleanUp()
{
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