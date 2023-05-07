#pragma once

#include "LTexture.h"
#include "Character.h"

class Enemy1
{
public:
    Enemy1();

    void Move(const int &acceleration);

    void Render(SDL_Renderer* gRenderer, LTexture gEnemy1Texture);

    int GetPosX();

	int GetPosY();

    void SpawnEnemy1(Character character);

    Circle& getCollider();

	void shiftColliders();


private:
	int posX, posY;

    double angle;

    Circle collider;
};