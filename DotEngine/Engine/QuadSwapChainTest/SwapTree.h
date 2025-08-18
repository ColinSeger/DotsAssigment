/*
#pragma once
#include <future>
#include <thread>
#include <stack>
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
    // QuadTree* selection;
    // QuadTree* primary;
    // QuadTree* secondary;
    // std::thread thread;
    std::mutex lockThing;
    std::stack<QuadTree*> readyTrees;
    bool ready = false;
    std::vector<PhysicsComponent*> components;
};
*/