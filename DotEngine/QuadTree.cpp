#include "QuadTree.h"

QuadTree::QuadTree()
{
    treeBoundingBox = BoundingBox();
}

QuadTree::QuadTree(BoundingBox boundingBox)
{
    treeBoundingBox = boundingBox;
}

void QuadTree::Insert(Node* node)
{
    if(!node || !treeBoundingBox.InBounds(node->x, node->y)) return;
    if( glm::abs(treeBoundingBox.upperLeft.x - treeBoundingBox.bottomRight.x) <= 1 && 
        glm::abs(treeBoundingBox.upperLeft.y - treeBoundingBox.bottomRight.y) <= 1)
    {
        // if(node)
    }
}