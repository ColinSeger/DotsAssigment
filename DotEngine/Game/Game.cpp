#include "../Game/Game.h"


Game::Game(DotRenderer* aRenderer)
{
	renderer = aRenderer;

	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		Dot dot = Dot({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT }, 3);

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
		glm::vec2 pos = glm::vec2(dotOne.GetPosition());
		Node node = Node(pos);
		node.position.x = pos.x;
		node.position.y = pos.y;
		quad->Insert(&node);
		
	}
	for (Dot& dot : dots)
	{
		glm::vec2 dotPosition = dot.GetPosition();
		glm::vec2 upperLeft = dotPosition - dot.radius;
		auto neighbor = quad->Search(dotPosition);
		for(int i = 0; i < neighbor.size(); i++){
			glm::vec2 pos = neighbor[i].GetPosition();
			dot.neighbors.push_back(pos);
			// renderer->DrawLineBetweenPoints(dotPosition, pos);
		}
		dot.Update(deltaTime);
		if(dot.health > 0) continue;
		dot.neighbors.clear();
		Dot newDot = Dot({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT }, 3);
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
