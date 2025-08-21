#pragma once
#include <future>
#include <thread>
#include <mutex>
#include "../../Engine/QuadTree.h"
#include "../../Engine/Constants.h"

class SwapTree
{
public:
    SwapTree(std::vector<PhysicsComponent*> components);
    ~SwapTree();

    void Start();

    QuadTree* GetQuadTree();

    void Construct();

    inline QuadTree* Swap();
    
private:
    std::future<void> compute;
    QuadTree* m_selection;
    QuadTree* m_primary;
    QuadTree* m_secondary;
    std::mutex m_lockThing;
    std::vector<PhysicsComponent*> m_componentPointers;
};
