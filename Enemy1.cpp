#include "Enemy1.h"

Enemy1::Enemy1()
{
    posX = -101;
    posY = -101;

    angle = 0;

    collider.r = 15;

    shiftColliders();
}

void Enemy1::Render(SDL_Renderer* gRenderer, LTexture gEnemy1Texture)
{
    gEnemy1Texture.Render(posX, posY, gRenderer, nullptr, angle * 180 / PI);
}

void Enemy1::Move(const int &acceleration)
{
	posX += ((ENEMY_1_SPEED + 2 * acceleration) * cos(angle));
    shiftColliders();
    
	posY += ((ENEMY_1_SPEED + 2 * acceleration) * sin(angle));
    shiftColliders();
}

int Enemy1::GetPosX()
{
	return posX;
}

int Enemy1::GetPosY()
{
	return posY;
}

void Enemy1::SpawnEnemy1(Character character)
{
    if ( ( posX < -100 ) || ( posX > SCREEN_WIDTH + 100  ) || 
            ( posY < -100 ) || ( posY > SCREEN_HEIGHT + 100  ) )
    {
        srand(time(NULL));
        int type = rand() % TOTAL_SPAWN_POSITION;

        if (type == TOP_SPAWN)
        {
            posX = rand() % SCREEN_WIDTH;
            posY = 0;
        }
        else if (type == RIGHT_SPAWN)
        {
            posX = SCREEN_WIDTH;
            posY = rand() % SCREEN_HEIGHT;
        }
        else if (type == BOTTOM_SPAWN)
        {
            posX = rand() % SCREEN_WIDTH;
            posY = SCREEN_HEIGHT;
        }
        else if (type == LEFT_SPAWN)
        {
            posX = 0;
            posY = rand() % SCREEN_HEIGHT;
        }

        Circle character_collider = character.getCollider();

        angle = atan2(character_collider.y - posY, character_collider.x - posX);
    }
}

Circle& Enemy1::getCollider()
{
	return collider;
}

void Enemy1::shiftColliders()
{
	collider.x = posX + 55;
	collider.y = posY + 15;
}