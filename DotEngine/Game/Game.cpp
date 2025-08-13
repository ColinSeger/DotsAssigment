#include "../Game/Game.h"


Game::Game(DotRenderer* aRenderer)
{
	renderer = aRenderer;
	physicsComponents.reserve(DOT_AMOUNT);
	renderComponents.reserve(DOT_AMOUNT);
	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		PhysicsComponent physics = PhysicsComponent({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		physicsComponents.push_back(physics);
		RenderComponent renderComp = RenderComponent(renderer);
		renderComponents.push_back(renderComp);
		// physics.SetPosition();
		Dot dot = Dot(3, &physicsComponents[i], &renderComponents[i]);
		// dot.renderComponent = &renderComp;
		dot.physicsComponent->SetBound(SCREEN_WIDTH, SCREEN_HEIGHT);
		dots.push_back(dot);
	}

	//To debug collision
	// dots[0].overriden = true;
	// dots[0].radius = 10;
	//To debug collision
}

void Game::Init()
{

}

void Game::Start()
{
	// for (size_t i = 0; i < DOT_AMOUNT; i++)
	// {
	// 	PhysicsComponent physics = PhysicsComponent({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
	// 	physicsComponents.push_back(physics);
	// 	// physics.SetPosition();
	// 	Dot dot = Dot(3, &physicsComponents[i]);
	// 	dot.physicsComponent->SetBound(SCREEN_WIDTH, SCREEN_HEIGHT);
	// 	dots.push_back(dot);
	// }
}

int Game::Update(float deltaTime)
{
	quadTree = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
	for (PhysicsComponent& component : physicsComponents)
	{
		quadTree->Insert(&component);
	}
	{
		//Slightly reducing reallocation by having result here
		std::vector<PhysicsComponent*> result;
		for (PhysicsComponent& component : physicsComponents)
		{
			glm::vec2 dotPosition = component.GetPosition();
			
			quadTree->Search(result, dotPosition);
			component.SetNeighbors(result);
			component.Update(deltaTime);
			result.clear();
		}
	}
	
	for (Dot& dot : dots)
	{
		dot.Update(deltaTime);
		if(dot.health > 0) continue;
		dot.physicsComponent->SetPosition({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		Dot newDot = Dot(3, dot.physicsComponent, dot.renderComponent);
		dot = newDot;
		newDot.renderComponent->Reset();
		newDot.renderComponent->SetStartPos(newDot.physicsComponent->GetPosition());
	}
	return 1;
}

void Game::Render(float deltaTime){
	for (size_t i = 0; i < renderComponents.size(); i++)
	{
		renderComponents[i].Render(physicsComponents[i].GetPosition(), physicsComponents[i].radius, deltaTime);
	}
}

void Game::CleanUp()
{
	if(quadTree){
		quadTree->CleanUp();		
	}
}
