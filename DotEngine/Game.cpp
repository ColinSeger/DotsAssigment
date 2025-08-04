#include "Game.h"


Game::Game(DotRenderer* aRenderer)
{
	renderer = aRenderer;

	for (size_t i = 0; i < DOT_AMOUNT; i++)
	{
		Dot* d = new Dot({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT }, 3);

		dots.push_back(d);
	}

	//To debug collision
	dots[0]->overriden = true;
	dots[0]->radius = 10;
	//To debug collision
}

void Game::Update(float aDeltaTime)
{
	std::vector<Dot*> toDestroy;
	for (Dot* dotOne : dots)
	{
		for (Dot* dotTwo : dots)
		{
			if (dotOne != dotTwo && dotOne != nullptr && dotTwo != nullptr)
			{
				float dist = glm::distance(dotOne->position, dotTwo->position);
				float minDist = dotOne->radius + dotTwo->radius;

				if (dist < minDist)
				{
					glm::vec2 normal = glm::normalize(dotTwo->position - dotOne->position);

					dotOne->velocity = glm::reflect(dotOne->velocity, normal);
					dotTwo->velocity = glm::reflect(dotTwo->velocity, -normal);

					float overlap1 = 1.5f * ((minDist + 1) - dist);
					float overlap2 = 1.5f * (minDist - dist);
					dotOne->position -= normal * overlap1;
					dotTwo->position += normal * overlap2;
					dotOne->TakeDamage(1);
					dotOne->radius++;
				}
				if (dotOne->health <= 0)
				{
					toDestroy.push_back(dotOne);
				}
			}
		}
	}

	std::vector<int> indexesToRemove;

	for (Dot* d : toDestroy)
	{
		for (size_t i = 0; i < dots.size(); i++)
		{
			if (std::find(indexesToRemove.begin(), indexesToRemove.end(), i) != indexesToRemove.end())
			{
				continue;
			}
			else if (dots[i] == d)
			{
				indexesToRemove.push_back(i);
			}
		}
	}

	for (int i : indexesToRemove)
	{
		delete dots[i];
		dots[i] = new Dot({ std::rand() % SCREEN_WIDTH, std::rand() % SCREEN_HEIGHT }, 3);
	}
	Render(aDeltaTime);
}

void Game::Render(float deltaTime){
	for (Dot* d : dots)
	{
		if (!d) continue;
		d->Render(renderer, deltaTime);
	}
}

void Game::CleanUp()
{

}
