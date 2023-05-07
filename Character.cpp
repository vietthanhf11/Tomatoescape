#include "Character.h"

Character::Character()
{
	posX = (SCREEN_WIDTH - 60) / 2;
	posY = (SCREEN_HEIGHT - 70) / 2;

	velX = 0;
	velY = 0;

    collider.r = 25;

    shiftColliders();
}

void Character::HandleEvent(SDL_Event& e, bool& UpDown, bool& LeftRight)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch( e.key.keysym.sym )
        {
            case SDLK_w: velY = -CHARACTER_VEL; UpDown = true; break;
            case SDLK_s: velY = CHARACTER_VEL; UpDown = false; break;
            case SDLK_a: velX = -CHARACTER_VEL; LeftRight = true; break;
            case SDLK_d: velX = CHARACTER_VEL; LeftRight = false; break;
        }
	}
	else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_w: 
            if (UpDown)
            {
                velY = 0; 
            }
            break;
            case SDLK_s: 
            if (!UpDown)
            {
                velY = 0; 
            }
            break;
            case SDLK_a: 
            if (LeftRight)
            {
                velX = 0; 
            }
            break;
            case SDLK_d:
            if (!LeftRight)
            {
                velX = 0;
            }
            break;
        }
    }
}

void Character::SetVel(int x, int y)
{
    velX = x;
    velY = y;
}

void Character::Move()
{
    posX += velX;
    shiftColliders();

    if( ( posX < -10 ) || ( posX > SCREEN_WIDTH - 60 ) )
    {
        posX -= velX;
        shiftColliders();
    }

    posY += velY;
    shiftColliders();

    if( ( posY < -10 ) || ( posY > SCREEN_HEIGHT - 60 ) )
    {
        posY -= velY;
        shiftColliders();
    }
}

void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}

Circle& Character::getCollider()
{
	return collider;
}

void Character::shiftColliders()
{
	collider.x = posX + 35;
	collider.y = posY + 35;
}