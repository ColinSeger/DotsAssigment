#include "Game.h"


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
	dots[0].radius = 10;
	//To debug collision
}

void Game::Update(float deltaTime)
{
	QuadTree* quad = new QuadTree(BoundingBox({0, 0}, {(float)SCREEN_HEIGHT, (float)SCREEN_WIDTH}));
	for (Dot& dotOne : dots)
	{
		for (Dot& dotTwo : dots)
		{
			if (&dotOne == &dotTwo) continue;
			
			float dist = glm::distance(dotOne.GetPosition(), dotTwo.GetPosition());
			float minDist = dotOne.radius + dotTwo.radius;

			if (dist < minDist)
			{
				auto test = dotTwo.GetPosition();
				glm::vec2 normal = glm::normalize(test - dotOne.GetPosition());

				dotOne.velocity = glm::reflect(dotOne.velocity, normal);
				dotTwo.velocity = glm::reflect(dotTwo.velocity, -normal);

				float overlap1 = 1.5f * ((minDist + 1) - dist);
				float overlap2 = 1.5f * (minDist - dist);
				dotOne.SetPosition((dotOne.GetPosition() - normal * overlap1));
				dotTwo.SetPosition((dotTwo.GetPosition() - normal * overlap2));
				dotOne.TakeDamage(1);
				dotOne.radius++;
			}
		}
		
		if(quad){
			Node node = Node(dotOne.GetPosition());
			quad->Insert(&node);
		}
	}
	

	for (Dot& dot : dots)
	{
		dot.Update(deltaTime);
		if(dot.health > 0) continue;
		Dot newDot = Dot({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT }, 3);
		dot = newDot;
	}

	Render(deltaTime);
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
