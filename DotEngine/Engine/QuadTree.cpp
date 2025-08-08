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
    if(!newNode || !treeBoundingBox.InBounds(newNode->GetPosition())) return;
    // if( glm::abs(treeBoundingBox.upperLeft.x - treeBoundingBox.bottomRight.x) <= MIN_BOX_SIZE && 
    //     glm::abs(treeBoundingBox.upperLeft.y - treeBoundingBox.bottomRight.y) <= MIN_BOX_SIZE)
    // {
    //     Node node = Node(newNode->GetPosition());
    //     nodes.push_back(node);
    //     std::cout << "Something is wrong with Quad tree \n";
    //     return;
    //     // if(nodes.size() <= CAPACITY){     
    //     // }
    // }
    if(nodes.size() < CAPACITY && !directions[0]){
        Node node = Node(newNode->GetPosition());
        nodes.push_back(node);
        return;
    }
    if(!directions[0]){
        SubDivide();
    }
    for(QuadTree* tree : directions){
        for(Node& position : nodes){
            Node node = Node(position.GetPosition());
            tree->Insert(&node);
            // break;
        }
        
        
        tree->Insert(newNode);
    }
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
        glm::vec2 topLeft = treeBoundingBox.upperLeft;
        glm::vec2 bottomRight = treeBoundingBox.bottomRight;
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[0] = new QuadTree(newBox);
    }
    {// Bottom Left
        glm::vec2 topLeft = treeBoundingBox.upperLeft;
        glm::vec2 bottomRight = treeBoundingBox.bottomRight;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[1] = new QuadTree(newBox);
    }
    {// Top Right
        glm::vec2 topLeft = treeBoundingBox.upperLeft;
        glm::vec2 bottomRight = treeBoundingBox.bottomRight;
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[2] = new QuadTree(newBox);
    }
    {// Bottom Right
        glm::vec2 topLeft = treeBoundingBox.upperLeft;
        glm::vec2 bottomRight = treeBoundingBox.bottomRight;
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        BoundingBox newBox = BoundingBox(topLeft, bottomRight);
        directions[3] = new QuadTree(newBox);
    }
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
    for(QuadTree* tree : directions){
        if(!tree || !tree->InRange(position, range)) continue;
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
    for(QuadTree* tree : directions){
        if(!tree) continue;
        tree->CleanUp();
    }
    delete this;
}