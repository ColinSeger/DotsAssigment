/*#include "../../Engine/QuadSwapChainTest/SwapTree.h"

SwapTree::SwapTree(std::vector<PhysicsComponent*> componentContainer)
{
    components = componentContainer;
    // primary = new QuadTree(BoundingBox({ 0, 0 }, { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }));
    // for (PhysicsComponent* component : components)
    // {
    //     primary->Insert(component);
    // }
    // readyTrees
    // compute = std::async(&SwapTree::Construct, this);
    // std::thread thread(SwapTree::Construct);
}

SwapTree::~SwapTree()
{

}

void SwapTree::Start()
{

}
QuadTree* SwapTree::Swap(){
    QuadTree* quad = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
    for (PhysicsComponent* component : components)
    {
        quad->Insert(component);
    }
    return quad;
}

void SwapTree::Construct()
{
    // selection = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
    // return;
    while (true)
    {
        QuadTree* tree = Swap();
        // if(ready) continue;
        if(lockThing.try_lock()){
            readyTrees.emplace(tree);
            lockThing.unlock();
        }else{
            tree->CleanUp();            
        }
    }
}

QuadTree* SwapTree::GetQuadTree()
{
    lockThing.lock();
    if(readyTrees.size() <= 0) {
        lockThing.unlock();
        return nullptr;
    }
    
    ready = true;
    QuadTree* result = readyTrees.top();
    readyTrees.pop();
    while (readyTrees.size() > 0)
    {
        QuadTree* tree = readyTrees.top();
        tree->CleanUp();
        
        readyTrees.pop();
    }
    ready = false;
    lockThing.unlock(); 
    return result;

    // if(ready){
    //     if(selection == primary){
    //         selection = secondary;
    //         ready = false;
    //         return selection;
    //     }
    //     selection = primary;
    //     ready = false;
    //     return selection;
    // }

    // if(selection){
    //     // compute = std::async(&SwapTree::Construct, this);
    //     // compute.get();
    //     return selection;
    // }
    // compute.get();
    // compute = std::async(&SwapTree::Construct, this);
    return nullptr;
}*/