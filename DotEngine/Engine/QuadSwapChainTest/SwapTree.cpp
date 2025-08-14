#include "../../Engine/QuadSwapChainTest/SwapTree.h"

SwapTree::SwapTree(std::vector<PhysicsComponent*> components)
{
    compute = std::async(&SwapTree::Construct, this);
}

SwapTree::~SwapTree()
{

}

void SwapTree::Start()
{

}
void SwapTree::Swap(QuadTree* quad){
    quad = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
    for (PhysicsComponent* component : components)
    {
        quad->Insert(component);
    }
}

void SwapTree::Construct()
{
    if(primary == selection){
        Swap(secondary);
        selection = secondary;
    }
    else{
        Swap(primary);
        selection = primary;
    }
}

QuadTree* SwapTree::GetQuadTree()
{
    if(selection){
        return selection;
    }
    // compute.get();
    return GetQuadTree();
}