#include "../Game/Game.h"


Game::Game(DotRenderer* newRenderer)
{
	m_renderer = newRenderer;
	m_physicsComponents.reserve(DOT_AMOUNT);
	m_renderComponents.reserve(DOT_AMOUNT);
	
	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		PhysicsComponent physics = PhysicsComponent({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		m_physicsComponents.push_back(physics);
		RenderComponent renderComp = RenderComponent(m_renderer);
		renderComp.SetStartPos(physics.GetPosition());
		m_renderComponents.push_back(renderComp);
		
		// physics.SetPosition();
		Dot dot = Dot(i , DOT_SIZE, &m_physicsComponents[i], &m_renderComponents[i]);
		// dot.renderComponent = &renderComp;
		// dot.physicsComponent->SetBound(SCREEN_WIDTH, SCREEN_HEIGHT);
		m_dots.push_back(dot);
		
	}
	std::vector<PhysicsComponent*> componentReference;
	for (size_t i = 0; i < m_physicsComponents.size(); i++)
	{
		componentReference.push_back(&m_physicsComponents[i]);
	}
	m_swapTree = new SwapTree(componentReference);
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
	m_quadTree = m_swapTree->GetQuadTree();
	if(!m_quadTree) {
		return 1;
	}
	// return 0;
	// quadTree = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_WIDTH, (float)SCREEN_HEIGHT}));
	// for (PhysicsComponent& component : physicsComponents)
	// {
	// 	quadTree->Insert(&component);
	// }
	//Slightly reducing reallocation by having result here
	std::vector<PhysicsComponent*> result;
	for (PhysicsComponent& component : m_physicsComponents)
	{
		glm::vec2 dotPosition = component.GetPosition();
		
		m_quadTree->Search(result, dotPosition);
		for(PhysicsComponent* neighbor : result){
			if(glm::distance(component.GetPosition(), neighbor->GetPosition()) > (component.GetRadius() + neighbor->GetRadius())) continue;
			component.AddNeighbor(neighbor);
		}
		result.clear();
	}
	
	for (Dot& dot : m_dots)
	{
		dot.Update(deltaTime);
		if(dot.GetHealth() > 0) continue;
		dot.SetPosition({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT });
		Dot newDot = Dot(dot.GetId(), DOT_SIZE, &m_physicsComponents[dot.GetId()], &m_renderComponents[dot.GetId()]);
		dot = newDot;
		newDot.GetRenderComponent()->SetStartPos(newDot.GetPosition());
	}
	return 0;
}

void Game::Render(float deltaTime){
	for (size_t i = 0; i < m_renderComponents.size(); i++)
	{
		m_renderComponents[i].Render(m_physicsComponents[i].GetPosition(), m_physicsComponents[i].GetRadius(), deltaTime);
	}
	if(debugMode == DebugDrawMode::Quad && m_quadTree){
		m_quadTree->DebugDraw(m_renderer);
	}
	if(debugMode == DebugDrawMode::Both && m_quadTree){
		m_quadTree->DebugDraw(m_renderer);
		for (size_t i = 0; i < m_physicsComponents.size(); i++)
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
	if(m_quadTree){
	 	m_quadTree->CleanUp();
	}
}
