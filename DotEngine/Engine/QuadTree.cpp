#include "../Engine/QuadTree.h"

QuadTree::QuadTree()
{
    m_nodes.reserve(CAPACITY);
    m_treeBoundingBox = BoundingBox({0, 0}, {10, 10});
}

QuadTree::QuadTree(BoundingBox boundingBox)
{
    m_treeBoundingBox = boundingBox;
    m_nodes.reserve(CAPACITY);
}

void QuadTree::PreWarm(const unsigned int amount, unsigned int& depth)
{
    
    unsigned int myDepth = amount / CAPACITY;
    if(depth > 180) return;
    SubDivide();
    depth++;
    for(auto tree : m_directions){
        tree->PreWarm(myDepth, depth);
    }
}

bool QuadTree::Insert(PhysicsComponent* newNode)
{
    assert(newNode && "You tried to add a non existent node to QuadTree");
    if(!m_treeBoundingBox.InBounds(newNode->GetPosition())) return false;

    if(!m_directions[0]){
        if(m_nodes.size() < CAPACITY || m_treeBoundingBox.Area() <= 1){
            m_nodes.emplace_back(newNode);
            return true;
        }
        SubDivide();
    }
    for(QuadTree* tree : m_directions){
        for(size_t i = 0; i < m_nodes.size(); i++){
            tree->Insert(m_nodes[i]);
        }
        tree->Insert(newNode);
    }
    m_nodes.clear();
    // m_nodes.shrink_to_fit();
    return true;
}

inline void QuadTree::SubDivide()
{
    glm::vec2 topLeft = m_treeBoundingBox.UpperLeft();
    glm::vec2 bottomRight = m_treeBoundingBox.BottomRight();
    // glm::vec2 newTopLeft = topLeft;
    // glm::vec2 newBottomRight = bottomRight;
    BoundingBox newBox;
    // Top Left
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        newBox = BoundingBox(topLeft, bottomRight);
        m_directions[0] = new QuadTree(newBox);
    
    // Bottom Left
        topLeft = m_treeBoundingBox.UpperLeft();
        bottomRight = m_treeBoundingBox.BottomRight();
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        bottomRight.x = (topLeft.x + bottomRight.x) / 2;
        newBox = BoundingBox(topLeft, bottomRight);
        m_directions[1] = new QuadTree(newBox);
    
    // Top Right
        topLeft = m_treeBoundingBox.UpperLeft();
        bottomRight = m_treeBoundingBox.BottomRight();
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        bottomRight.y = (topLeft.y + bottomRight.y) / 2;
        newBox = BoundingBox(topLeft, bottomRight);
        m_directions[2] = new QuadTree(newBox);
    
    // Bottom Right
        topLeft = m_treeBoundingBox.UpperLeft();
        bottomRight = m_treeBoundingBox.BottomRight();
        topLeft.x = (topLeft.x + bottomRight.x) / 2;
        topLeft.y = (topLeft.y + bottomRight.y) / 2;
        newBox = BoundingBox(topLeft, bottomRight);
        m_directions[3] = new QuadTree(newBox);
    
}

const void QuadTree::Search(std::vector<PhysicsComponent*>& result, const glm::vec2 position)
{
    constexpr float range = 5;
    // if(!InRange(position, range)){
    //     return;
    // }
    if(m_nodes.size() > 0 || !m_directions[0]){
        result.insert(result.end(), m_nodes.begin(), m_nodes.end());
        return;
    }
    for(QuadTree* tree : m_directions){
        if(!tree->InRange(position, range)) continue;
        tree->Search(result, position);
    }
}

constexpr bool QuadTree::InRange(const glm::vec2 position, const float range)
{
    //Top left
    glm::vec2 location = position - range;
    if(m_treeBoundingBox.InBounds(location)){
        return true;
    }
    //Top right
    location = {position.x + range, position.y - range};
    if(m_treeBoundingBox.InBounds(location)){
        return true;
    }
    //Bottom left
    location = {position.x - range, position.y + range};
    if(m_treeBoundingBox.InBounds(location)){
        return true;
    }
    //Bottom right
    location = position + range;
    if(m_treeBoundingBox.InBounds(location)){
        return true;
    }
    return false;
}

void QuadTree::CleanUp()
{
    for(QuadTree* tree : m_directions){
        if(!tree) break;
        tree->CleanUp();
    }
    delete this;
}

constexpr void QuadTree::ClearNodes()
{
    for (int i = 0; i < CAPACITY; i++)
    {
        m_nodes[i] = nullptr;
    }
}

constexpr void QuadTree::AddNode(PhysicsComponent* newNode)
{
    for (int i = 0; i < CAPACITY; i++)
    {
        if(!m_nodes[i]){
            m_nodes[i] = newNode;
        }
    }
}