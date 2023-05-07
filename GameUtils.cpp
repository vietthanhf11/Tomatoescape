#include "GameUtils.h"

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& quit_menu,
	bool& play_again,
	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		quit_menu = true;
	}

	if (PlayButton.IsInside(e, MENU_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			play_again = true;
			quit_menu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton, 
	Button& BackButton, 
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &quit_game, 
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, MENU_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool back_menu = false;
			while (!back_menu)
			{
				while (SDL_PollEvent( e ) != 0)
				{
					if (e->type == SDL_QUIT)
					{
						back_menu = true;
						quit_game = true;
						Close();
					}

					else if (BackButton.IsInside(e, MENU_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							back_menu = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(100, 100, gRenderer);

					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);

					SDL_RenderPresent(gRenderer);
				}
			}
		}
	}
	else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& quit_menu,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, MENU_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			quit_menu = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

int UpdateGameTimeAndScore(int& time,
    int& acceleration,
    int& score,
    int& chasing_time)
{
	if (time == TIME_MAX)
	{
		acceleration += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)
	{
		time = 0;
	}

	if (time % 5 == 0)
	{
		score += SCORE_INCREASEMENT;
	}
	
	time += TIME_INCREASEMENT;

	chasing_time += TIME_INCREASEMENT;

	return time;
}

void DrawPlayerScore(LTexture gTextTexture,
	LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont, 
	const int& score)
{
	gTextTexture.Render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
	if (gScoreTexture.LoadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
}

void DrawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const std::string& HighScore)
{
	gTextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
	if (gHighScoreTexture.LoadFromRenderedText(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
	}
}

void HandlePauseButton(SDL_Event* e,
	Button& PauseButton,
	bool& game_paused,
	bool& quit_game,
	Mix_Chunk* gClick,
    LTexture gPauseButtonTexture,
    SDL_Renderer* gRenderer,
	Character& character,
    SDL_Rect(&gPauseButton)[BUTTON_TOTAL])
{
	if (e->type == SDL_QUIT)
	{
		quit_game = true;
		Close();
	}

	if (PauseButton.IsInside(e, IN_GAME_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			game_paused = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			while (game_paused)
			{
				while (SDL_PollEvent( e ) != 0)
				{
					if (e->type == SDL_QUIT)
					{
						quit_game = true;
						Close();
					}

					else if (PauseButton.IsInside(e, IN_GAME_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEBUTTONDOWN:
							PauseButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							game_paused = false;
							break;
						default:
							PauseButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						}
					}

					SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
					PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);

					SDL_RenderPresent(gRenderer);
				}
				character.SetVel(0, 0);
			}
			PauseButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleMuteButton(SDL_Event* e,
	Button& MuteButton,
	bool& game_muted,
	bool& quit_game,
	Mix_Chunk* gClick,
    LTexture gMuteButtonTexture,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gMuteButton)[BUTTON_TOTAL])
{
	if (e->type == SDL_QUIT)
	{
		quit_game = true;
	}

	if (!game_muted)
	{
		if (MuteButton.IsInside(e, IN_GAME_BUTTON))
		{
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				MuteButton.currentSprite = BUTTON_MOUSE_OVER;
				Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
				Mix_PauseMusic();
				game_muted = true;
				break;
			default:
				MuteButton.currentSprite = BUTTON_MOUSE_OUT;
				break;
			}
		}
		else
		{
			MuteButton.currentSprite = BUTTON_MOUSE_OUT;
		}
	}
	else
	{
		if (MuteButton.IsInside(e, IN_GAME_BUTTON))
		{
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				MuteButton.currentSprite = BUTTON_MOUSE_OUT;
				Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
				Mix_ResumeMusic();
				game_muted = false;
				break;
			
			default:
				MuteButton.currentSprite = BUTTON_MOUSE_OVER;
				break;
			}
		}
		else
		{
			MuteButton.currentSprite = BUTTON_MOUSE_OVER;
		}
	}
}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

bool checkCollision( Character character,
    Enemy1 enemy1,
    Enemy2 enemy2)
{
	Circle a = character.getCollider();
	Circle b = enemy1.getCollider();
	Circle c = enemy2.getCollider();

    int totalRadiusSquared = a.r + b.r;
    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

    if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) )
    {
        return true;
    }

	if( distanceSquared( a.x, a.y, c.x, c.y ) < ( totalRadiusSquared ) )
	{
		return true;
	}

    return false;
}

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool& play_again,
    bool& quit_menu,
	bool& quit_game)
{
	play_again = false;
	while (!play_again)
	{
		while (SDL_PollEvent(e) != 0)
		{
			if (e->type == SDL_QUIT)
			{
				quit_game = true;
				play_again = true;
			}

			if (e->type == SDL_KEYDOWN)
			{
				switch (e->key.keysym.sym)
				{
				case SDLK_RETURN:
					play_again = true;
					break;
				case SDLK_ESCAPE:
					quit_menu = false;
					play_again = true;
					break;
				}
			}
		}

		gLoseTexture.Render(100, 100, gRenderer);

		SDL_RenderPresent(gRenderer);
	}

	if (!quit_menu && play_again)
	{
		play_again = false;
	}

	if (quit_game && play_again)
	{
		play_again = false;
	}
}

string GetHighScoreFromFile(string path)
{
	fstream HighScoreFile;
	string highscore;

	HighScoreFile.open(path, ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(string path,
	const int& score, 
	const string& old_high_score)
{
	int oldHighScore = 0;
	fstream HighScoreFile;
	string newHighScore;
	stringstream Converter(old_high_score);

	HighScoreFile.open(path, ios::out);

	Converter >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}

	newHighScore = to_string(oldHighScore);

	HighScoreFile << newHighScore;
}