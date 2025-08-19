#include "../../Engine/QuadSwapChainTest/SwapTree.h"

SwapTree::SwapTree(std::vector<PhysicsComponent*> componentContainer)
{
    components = componentContainer;
    // primary = new QuadTree(BoundingBox({ 0, 0 }, { (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT }));
    // for (PhysicsComponent* component : components)
    // {
    //     primary->Insert(component);
    // }
    // readyTrees
    compute = std::async(&SwapTree::Construct, this);
    // pthread_mutex_init(lockThing, compute);
    // std::thread thread(&SwapTree::Construct, this);
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
    while (true)
    {
        QuadTree* tree = Swap();
        
        if(lockThing.try_lock()){
            if(selection == primary){
                if(secondary) {
                    secondary->CleanUp();
                }
                secondary = tree;
                selection = secondary;
            }else{
                if(primary){
                    primary->CleanUp();
                } 
                primary = tree;
                selection = primary;
            }
            lockThing.unlock();
        }else{
            tree->CleanUp();            
        }
    }
}

QuadTree* SwapTree::GetQuadTree()
{
    lockThing.lock();
    if(selection == primary){
        returnValue = primary;
        primary = nullptr;
    }else{
        returnValue = secondary;
        secondary = nullptr;
    }
    lockThing.unlock();
    return returnValue;
}