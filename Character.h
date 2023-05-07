#pragma once

#include "LTexture.h"

class Character
{
public:
	static const int CHARACTER_VEL = 10;

	Character();

	void HandleEvent(SDL_Event& e, bool& UpDown, bool& LeftRight);

	void SetVel(int x, int y);

	void Move();

	void Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture);

	int GetPosX();

	int GetPosY();

	Circle& getCollider();

	void shiftColliders();

private:
	int posX, posY;

	int velX, velY;

	Circle collider;
};