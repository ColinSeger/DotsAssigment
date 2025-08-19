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

    QuadTree* Swap();
    
private:
    std::future<void> compute;
    QuadTree* returnValue;
    QuadTree* selection;
    QuadTree* primary;
    QuadTree* secondary;
    std::mutex lockThing;
    std::vector<PhysicsComponent*> components;
};
