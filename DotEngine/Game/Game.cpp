#include "../Game/Game.h"


Game::Game(DotRenderer* aRenderer)
{
	renderer = aRenderer;

	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		PhysicsComponent physics = PhysicsComponent();
		physicsComponents.push_back(physics);
		physics.SetPosition({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		Dot dot = Dot(3, &physics);

		dots.push_back(dot);
	}

	//To debug collision
	// dots[0].overriden = true;
	// dots[0].radius = 10;
	//To debug collision
}

void Game::Update(float deltaTime)
{
	QuadTree* quad = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
	for (Dot& dotOne : dots)
	{
		Node node = Node(dotOne.physicsComponent->GetPosition());
		quad->Insert(&node);
		
	}
	for (Dot& dot : dots)
	{
		glm::vec2 dotPosition = dot.physicsComponent->GetPosition();
		auto neighbor = quad->Search(dotPosition);
		for(int i = 0; i < neighbor.size(); i++){
			glm::vec2 pos = neighbor[i].GetPosition();
			dot.neighbors.push_back(pos);
			// renderer->DrawLineBetweenPoints(dotPosition, pos);
		}
		dot.Update(deltaTime);
		if(dot.health > 0) continue;
		dot.neighbors.clear();
		dot.physicsComponent->SetPosition({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		Dot newDot = Dot(3, dot.physicsComponent);
		dot = newDot;
	}

	Render(deltaTime);
	// quad->DebugDraw(renderer);
	quad->CleanUp();
}

void Game::Render(float deltaTime){
	for (Dot& dot : dots)
	{
		dot.Render(renderer, deltaTime);
		dot.neighbors.clear();
	}
}

void Game::CleanUp()
{

}
