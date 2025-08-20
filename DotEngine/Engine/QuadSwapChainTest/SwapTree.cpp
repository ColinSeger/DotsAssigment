#include "../../Engine/QuadSwapChainTest/SwapTree.h"

SwapTree::SwapTree(std::vector<PhysicsComponent*> componentContainer)
{
    m_componentPointers = componentContainer;
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
    unsigned int test = 0;
    // quad->PreWarm(components.size(), test);
    for (PhysicsComponent* component : m_componentPointers)
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
        
        if(m_lockThing.try_lock()){
            if(m_selection == m_primary){
                if(m_secondary) {
                    m_secondary->CleanUp();
                }
                m_secondary = tree;
                m_selection = m_secondary;
            }else{
                if(m_primary){
                    m_primary->CleanUp();
                } 
                m_primary = tree;
                m_selection = m_primary;
            }
            m_lockThing.unlock();
        }else{
            tree->CleanUp();            
        }
    }
}

QuadTree* SwapTree::GetQuadTree()
{
    m_lockThing.lock();
    QuadTree* returnValue = nullptr;
    if(m_selection == m_primary){
        returnValue = m_primary;
        m_primary = nullptr;
    }else{
        returnValue = m_secondary;
        m_secondary = nullptr;
    }
    m_lockThing.unlock();
    return returnValue;
}