#include "../Game/Game.h"


Game::Game(DotRenderer* aRenderer)
{
	renderer = aRenderer;
	collideAmount.resize(DOT_AMOUNT);
	physicsComponents.reserve(DOT_AMOUNT);
	renderComponents.reserve(DOT_AMOUNT);
	
	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		PhysicsComponent physics = PhysicsComponent({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		physicsComponents.push_back(physics);
		RenderComponent renderComp = RenderComponent(renderer);
		renderComp.SetStartPos(physics.GetPosition());
		renderComponents.push_back(renderComp);
		
		// physics.SetPosition();
		Dot dot = Dot(i , 3, &physicsComponents[i], &renderComponents[i]);
		// dot.renderComponent = &renderComp;
		// dot.physicsComponent->SetBound(SCREEN_WIDTH, SCREEN_HEIGHT);
		dots.push_back(dot);
		
	}
	std::vector<PhysicsComponent*> componentReference;
	for (size_t i = 0; i < physicsComponents.size(); i++)
	{
		componentReference.push_back(&physicsComponents[i]);
	}
	swapTree = new SwapTree(componentReference);
	//To debug collision
	// dots[0].overriden = true;
	// dots[0].radius = 10;
	//To debug collision
}

void Game::Init()
{

}

int Game::Update(float deltaTime)
{
	quadTree = swapTree->GetQuadTree();
	if(!quadTree) {
		return 1;
	}
	// quadTree = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
	// for (PhysicsComponent& component : physicsComponents)
	// {
	// 	quadTree->Insert(&component);
	// }
	//Slightly reducing reallocation by having result here
	std::vector<PhysicsComponent*> result;
	for (PhysicsComponent& component : physicsComponents)
	{
		glm::vec2 dotPosition = component.GetPosition();
		
		quadTree->Search(result, dotPosition);
		for(PhysicsComponent* neighbor : result){
			if(glm::distance(component.GetPosition(), neighbor->GetPosition()) > (component.GetRadius() + neighbor->GetRadius()) 
				|| component.GetPosition() == neighbor->GetPosition()) continue;
			component.AddNeighbor(neighbor);
		}
		result.clear();
	}
	
	for (Dot& dot : dots)
	{
		dot.Update(deltaTime);
		if(dot.GetHealth() > 0) continue;
		dot.SetPosition({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		Dot newDot = Dot(dot.GetId(), 3, &physicsComponents[dot.GetId()], &renderComponents[dot.GetId()]);
		dot = newDot;
		newDot.GetRenderComponent()->SetStartPos(newDot.GetPosition());
	}
	return 0;
}

void Game::Render(float deltaTime){
	for (size_t i = 0; i < renderComponents.size(); i++)
	{
		renderComponents[i].Render(physicsComponents[i].GetPosition(), physicsComponents[i].GetRadius(), deltaTime);
	}
	if(debugMode == DebugDrawMode::Quad && quadTree){
		quadTree->DebugDraw(renderer);
	}
	if(debugMode == DebugDrawMode::Both && quadTree){
		quadTree->DebugDraw(renderer);
		for (size_t i = 0; i < physicsComponents.size(); i++)
		{
			// auto neighbors = physicsComponents[i].GetNeighbors();
			// for (int n = 0; 0 < neighbors.size(); n++)
			// {
			// 	renderer->DrawLineBetweenPoints(physicsComponents[i].GetPosition(), neighbors[n]->GetPosition());
			// }
			
		}
		
	}
}

void Game::CleanUp()
{
	if(quadTree){
	 	quadTree->CleanUp();
	}
}
