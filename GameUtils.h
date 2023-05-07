#pragma once

#include "Button.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Character.h"

bool Init();
bool LoadMedia();
void Close();

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& quit_menu,
	bool& play_again,
	Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_TOTAL],
    Button& HelpButton,
    Button& BackButton,
    LTexture gInstructionTexture,
    LTexture gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& quit_game,
    Mix_Chunk* gClick);

void HandleExitButton(SDL_Event* e,
    Button& ExitButton,
    bool& quit_menu,
    Mix_Chunk* gClick);

int UpdateGameTimeAndScore(int& time,
    int& acceleration,
    int& score,
    int& chasing_time);

void DrawPlayerScore(LTexture gTextTexture,
    LTexture gScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const int& score);

void DrawPlayerHighScore(LTexture gTextTexture,
    LTexture gHighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont, 
    const std::string& HighScore);

void HandlePauseButton(SDL_Event* e,
	Button& PauseButton,
	bool& game_paused,
	bool& quit_game,
	Mix_Chunk* gClick,
    LTexture gPauseButtonTexture,
    SDL_Renderer* gRenderer,
    Character& character,
    SDL_Rect(&gPauseButton)[BUTTON_TOTAL]);

void HandleMuteButton(SDL_Event* e,
	Button& MuteButton,
	bool& game_muted,
	bool& quit_game,
	Mix_Chunk* gClick,
    LTexture gMuteButtonTexture,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gMuteButton)[BUTTON_TOTAL]);

double distanceSquared( int x1, int y1, int x2, int y2 );

bool checkCollision( Character character,
    Enemy1 enemy1,
    Enemy2 enemy2);

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool& play_again,
    bool& quit_menu,
    bool& quit_game);

string GetHighScoreFromFile(string path);

void UpdateHighScore(string path,
	const int& score, 
	const string& old_high_score);