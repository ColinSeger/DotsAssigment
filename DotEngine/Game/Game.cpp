#include "../Game/Game.h"


Game::Game(DotRenderer* aRenderer)
{
	renderer = aRenderer;
	physicsComponents.reserve(DOT_AMOUNT);
	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		PhysicsComponent physics = PhysicsComponent({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		physicsComponents.push_back(physics);
		// physics.SetPosition();
		Dot dot = Dot(3, &physicsComponents[i]);

		dots.push_back(dot);
	}

	//To debug collision
	// dots[0].overriden = true;
	// dots[0].radius = 10;
	//To debug collision
}
glm::vec2 SCREEN_CENTRE = {SCREEN_WIDTH /2, SCREEN_HEIGHT / 2};
void Game::Update(float deltaTime)
{
	QuadTree* quad = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
	for (PhysicsComponent& component : physicsComponents)
	{
		quad->Insert(&component);
	}
	for (PhysicsComponent& component : physicsComponents)
	{
		glm::vec2 dotPosition = component.GetPosition();
		auto tempDebug = quad->Search(dotPosition);
		component.SetNeighbors(tempDebug);
		component.Update(deltaTime);
		// for(auto debug : tempDebug){
		// 	renderer->DrawLineBetweenPoints(component.GetPosition(), debug->GetPosition());
		// }
	}
	for (Dot& dot : dots)
	{
		dot.Update(deltaTime);
		if(dot.health > 0) continue;
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
	}
}

void Game::CleanUp()
{

}
