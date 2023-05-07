#include "GameBase.h"
#include "GameUtils.h"
#include "LTexture.h"
#include "Button.h"
#include "Character.h"
#include "Enemy1.h"
#include "Enemy2.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Color textColor = {139, 195, 74};
TTF_Font* gFont = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gMuteButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[CHARACTER_FRAMES];

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture;
LTexture gCharacterTexture;
LTexture gEnemy1Texture;
LTexture gEnemy2Texture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gMuteButtonTexture;
LTexture gPlayerScoreTexture;
LTexture gText1Texture;
LTexture gHighScoreTexture;
LTexture gText2Texture;
LTexture gLoseTexture;

Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button MuteButton(MUTE_BUTTON_POSX, MUTE_BUTTON_POSY);

Character character;

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool LoadMedia()
{
	bool success = true;

    gMenuMusic = Mix_LoadMUS("sound/menu.wav");
	if (gMenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}

	gMusic = Mix_LoadMUS("sound/music.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load game music", MIX_ERROR);
		success = false;
	}

    gClick = Mix_LoadWAV("sound/click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	gLose = Mix_LoadWAV("sound/lose.wav");
	if (gLose == nullptr)
	{
		LogError("Failed to load losing sound", MIX_ERROR);
		success = false;
	}
    else
    {
		gFont = TTF_OpenFont("font/tomato.ttf", 28);
		if (gFont == NULL)
		{
			LogError("Failed to load font", MIX_ERROR);
			success = false;
		}
		else
		{
			if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text1 texture" << endl;
				success = false;
			}

			if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
			{
				cout << "Failed to render text2 texture" << endl;
				success = false;
			}

			if (!gMenuTexture.LoadFromFile("imgs/background/menu.png", gRenderer))
			{
				cout << "Failed to load menu image" << endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("imgs/background/instruction.png", gRenderer))
			{
				cout << "Failed to load instruction image" << endl;
				success = false;
			}

			if (!gBackgroundTexture.LoadFromFile("imgs/background/ingame_bkgr.png", gRenderer))
			{
				cout << "Failed to load ground image" << endl;
				success = false;
			}

			if (!gCharacterTexture.LoadFromFile("imgs/character/tomato.png", gRenderer))
			{
				cout << "Failed to load character image" << endl;
			}
			else
			{
				for (int i = 0; i < CHARACTER_FRAMES; ++i)
				{
					gCharacterClips[i].x = 60 * i;
					gCharacterClips[i].y = 0;
					gCharacterClips[i].w = 60;
					gCharacterClips[i].h = 60;
				}
			}

			if (!gEnemy1Texture.LoadFromFile("imgs/enemy/knife.png", gRenderer))
			{
				cout << "Failed to load knife image" << endl;
				success = false;
			}

			if (!gEnemy2Texture.LoadFromFile("imgs/enemy/shuriken.png", gRenderer))
			{
				cout << "Failed to load shuriken image" << endl;
				success = false;
			}

			if (!gPlayButtonTexture.LoadFromFile("imgs/button/play.png", gRenderer))
			{
				cout << "Failed to load play button image." << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPlayButton[i].x = 150 * i;
					gPlayButton[i].y = 0;
					gPlayButton[i].w = 150;
					gPlayButton[i].h = 50;
				}
			}

			if (!gHelpButtonTexture.LoadFromFile("imgs/button/help.png", gRenderer))
			{
				cout << "Failed to load help button image." << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i].x = 150 * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = 150;
					gHelpButton[i].h = 50;
				}
			}

			if (!gExitButtonTexture.LoadFromFile("imgs/button/quit.png", gRenderer))
			{
				cout << "Failed to load quit button image." << endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = 150 * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = 150;
					gExitButton[i].h = 50;
				}
			}

			if (!gBackButtonTexture.LoadFromFile("imgs/button/back.png", gRenderer))
				{
					cout << "Failed to load back button image" << endl;
					success = false;
				}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = 150 * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = 150;
					gBackButton[i].h = 50;
				}
			}

			if (!gPauseButtonTexture.LoadFromFile("imgs/button/pause.png", gRenderer))
				{
					cout << "Failed to load pause image" << endl;
					success = false;
				}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i].x = 30 * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = 30;
					gPauseButton[i].h = 30;
				}
			}

			if (!gMuteButtonTexture.LoadFromFile("imgs/button/mute.png", gRenderer))
				{
					cout << "Failed to load mute button image" << endl;
					success = false;
				}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gMuteButton[i].x = 30 * i;
					gMuteButton[i].y = 0;
					gMuteButton[i].w = 30;
					gMuteButton[i].h = 30;
				}
			}

			if (!gLoseTexture.LoadFromFile("imgs/background/lose.png", gRenderer))
				{
					cout << "Failed to load lose background image" << endl;
					success = false;
				}
		}	
    }

	return success;
}

void Close()
{
	gMenuTexture.Free();
    gInstructionTexture.Free();
    gBackgroundTexture.Free();
    gCharacterTexture.Free();
	gEnemy1Texture.Free();
	gEnemy2Texture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
    gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gMuteButtonTexture.Free();
	gPlayerScoreTexture.Free();
	gText1Texture.Free();
	gHighScoreTexture.Free();
	gText2Texture.Free();
	gLoseTexture.Free();

	Mix_FreeMusic(gMenuMusic);
	Mix_FreeMusic(gMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	gMenuMusic = nullptr;
	gMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!Init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!LoadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit_menu = false;
            bool play_again = false;
			bool quit_game = false;
			bool game_muted = false;
			

            SDL_Event e;
            
			while (!quit_game)
			{
				Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);

				while (!quit_menu)
				{
					while (SDL_PollEvent( &e ) != 0)
					{
						if( e.type == SDL_QUIT )
						{
							quit_menu = true;
						}
						
						quit_game = false;
						
						HandlePlayButton(&e, PlayButton, quit_menu, play_again, gClick);
						HandleHelpButton(&e, gBackButton,
											HelpButton, BackButton, 
											gInstructionTexture, gBackButtonTexture,
											gRenderer, quit_game, gClick);
						HandleExitButton(&e, ExitButton, quit_game, gClick);

						HandleMuteButton(&e, MuteButton, 
								game_muted, quit_game, gClick,
								gMuteButtonTexture, gRenderer,
								gMuteButton);
						
						if (quit_game == true)
						{	
							return 0;
						}
					}

					gMenuTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
					PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

					SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
					HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

					SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
					ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

					SDL_Rect* currentClip_Mute = &gMuteButton[MuteButton.currentSprite];
					MuteButton.Render(currentClip_Mute, gRenderer, gMuteButtonTexture);

					SDL_RenderPresent(gRenderer);
				}

				while (play_again)
				{	
					int time = 0;
					int score = 0;
					int acceleration = 0;
					int chasing_time = 0;

					bool UpDown = false;
					bool LeftRight = false;

					string highscore = GetHighScoreFromFile("highscore.txt");

					bool quit = false;
					bool game_paused = false;
					bool game_muted = false;

					Enemy1 enemy1;
					enemy1.SpawnEnemy1(character);
					
					Enemy2 enemy2;
					enemy2.SpawnEnemy2(character);

					character.SetVel(0, 0);

					Mix_HaltMusic();

					Mix_PlayMusic(gMusic, IS_REPEATITIVE);

					while (!quit)
					{	
						while (SDL_PollEvent( &e ))
						{
							if (e.type == SDL_QUIT)
							{
								quit = true;
								play_again = false;
							}

							bool quit_game = false;

							character.HandleEvent(e, UpDown, LeftRight);

							HandlePauseButton(&e, PauseButton, 
								game_paused, quit_game, gClick,
								gPauseButtonTexture, gRenderer, character,
								gPauseButton);

							HandleMuteButton(&e, MuteButton, 
								game_muted, quit_game, gClick,
								gMuteButtonTexture, gRenderer,
								gMuteButton);

							if (quit_game == true)
							{
								return 0;
							}
						}
		
						if (!game_paused)
						{
							UpdateGameTimeAndScore(time, acceleration, score, chasing_time);
							enemy1.SpawnEnemy1(character);
							enemy1.Move(acceleration);
							character.Move();
							enemy2.Move(chasing_time, acceleration, character);
							if (enemy2.SpawnEnemy2(character))
							{
								chasing_time = 0;
							}
						}

						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						gBackgroundTexture.Render(0, 0, gRenderer);

						SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
						PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);

						SDL_Rect* currentClip_Mute = &gMuteButton[MuteButton.currentSprite];
						MuteButton.Render(currentClip_Mute, gRenderer, gMuteButtonTexture);
						
						SDL_Rect* currentClip_Character = &gCharacterClips[0];
						character.Render(currentClip_Character, gRenderer, gCharacterTexture);
		
						enemy1.Render(gRenderer, gEnemy1Texture);
					
						enemy2.Render(gRenderer, gEnemy2Texture, time * 15);
						
						DrawPlayerScore(gText1Texture, gPlayerScoreTexture, textColor, gRenderer, gFont, score);
						DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

						if (checkCollision(character, enemy1, enemy2))
						{
							quit = true;
							Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
							UpdateHighScore("highscore.txt", score, highscore);
							character.SetVel(0, 0);
							SDL_Rect* currentClip_Character = &gCharacterClips[1];
							character.Render(currentClip_Character, gRenderer, gCharacterTexture);
						}

						SDL_RenderPresent(gRenderer);
					}
					
					DrawEndGameSelection(gLoseTexture, &e, gRenderer, play_again, quit_menu, quit_game);
				}
			}
		}
	}
	Close();

	return 0;
}