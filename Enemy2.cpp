#include "Enemy2.h"

Enemy2::Enemy2()
{
    posX = -101;
    posY = -101;

    angle = 0;

    collider.r = 35;

    shiftColliders();
}

void Enemy2::Render(SDL_Renderer* gRenderer, LTexture gEnemy2Texture, double degrees)
{
    gEnemy2Texture.Render(posX, posY, gRenderer, nullptr, degrees);
}

void Enemy2::MoveStraight(const int &acceleration)
{
	posX += ((ENEMY_2_SPEED + acceleration) * cos(angle));
    shiftColliders();
    
	posY += ((ENEMY_2_SPEED + acceleration) * sin(angle));
    shiftColliders();
}

void Enemy2::ChasePlayer(const int& acceleration, Character character)
{
	posX += ((ENEMY_2_SPEED + acceleration) * cos(angle));
    shiftColliders();
    
	posY += ((ENEMY_2_SPEED + acceleration) * sin(angle));
    shiftColliders();

    Circle character_collider = character.getCollider();

    angle = atan2(character_collider.y - posY - 35, character_collider.x - posX - 35);
}

void Enemy2::Move(int chasing_time, const int& acceleration, Character character)
{
    if (chasing_time < 300 / (acceleration + 1)) ChasePlayer(acceleration, character);
    else MoveStraight(acceleration);
}

int Enemy2::GetPosX()
{
	return posX;
}

int Enemy2::GetPosY()
{
	return posY;
}

bool Enemy2::SpawnEnemy2(Character character)
{
    if ( ( posX < -100 ) || ( posX > SCREEN_WIDTH  ) || 
            ( posY < -100 ) || ( posY > SCREEN_HEIGHT  ) )
    {
        srand(time(nullptr));
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

        return true;
    }

    return false;
}

Circle& Enemy2::getCollider()
{
	return collider;
}

void Enemy2::shiftColliders()
{
	collider.x = posX + 30;
	collider.y = posY + 35;
}