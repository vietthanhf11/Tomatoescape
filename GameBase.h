#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 500
#define CHASE_TIME_MAX 100
#define TIME_INCREASEMENT 1
#define SPEED_INCREASEMENT 1
#define SCORE_INCREASEMENT 1

#define MENU_BUTTON 1
#define IN_GAME_BUTTON 2

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define TOP_SPAWN 0
#define RIGHT_SPAWN 1
#define BOTTOM_SPAWN 2
#define LEFT_SPAWN 3
#define TOTAL_SPAWN_POSITION 4

#define ENEMY_1_SPEED 5
#define ENEMY_2_SPEED 2
#define MAX_ACCELERATION 10

#define PI 3.14159265

const string WINDOW_TITLE = "Tomatoescape";

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 750;

const int MENU_BUTTON_WIDTH = 150;
const int MENU_BUTTON_HEIGHT = 50;
const int IN_GAME_BUTTON_WIDTH = 30;
const int IN_GAME_BUTTON_HEIGHT = 30;

const int PLAY_BUTTON_POSX = 225;
const int PLAY_BUTTON_POSY= 350;
const int HELP_BUTTON_POSX = 225;
const int HELP_BUTTON_POSY = 450;
const int EXIT_BUTTON_POSX = 225;
const int EXIT_BUTTON_POSY = 550;
const int BACK_BUTTON_POSX = 25;
const int BACK_BUTTON_POSY = 25;
const int PAUSE_BUTTON_POSX = 555;
const int PAUSE_BUTTON_POSY = 15;
const int MUTE_BUTTON_POSX = 555;
const int MUTE_BUTTON_POSY = 50;

const int TEXT_1_POSX = 30;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 30;
const int TEXT_2_POSY = 70;
const int SCORE_POSX = 230;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 230;
const int HIGH_SCORE_POSY = 70;

const int CHARACTER_FRAMES = 2;

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

struct Circle
{
	int x, y;
	int r;
};

void LogError(string msg, int error_code = SDL_ERROR);