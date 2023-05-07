#pragma once

#include "LTexture.h"
#include "Character.h"

class Enemy2
{
public:
    Enemy2();

    void MoveStraight(const int& acceleration);

    void ChasePlayer(const int& acceleration, Character character);
    
    void Move(int chasing_time, const int& acceleration, Character character);

    void Render(SDL_Renderer* gRenderer, LTexture gEnemy1Texture, double degrees);

    int GetPosX();

	int GetPosY();

    bool SpawnEnemy2(Character character);

    Circle& getCollider();

	void shiftColliders();


private:
	int posX, posY;

    double angle;

    Circle collider;
};