#include <future>
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

    void Swap(QuadTree* quad);
    
private:
    std::future<void> compute;
    QuadTree* selection;
    QuadTree* primary;
    QuadTree* secondary;
    std::vector<PhysicsComponent*> components;
};
