#include "CAppStateGameTetrisClassic.h"

#include "CAppStateManager.h"
#include "Log.h"
#include "App.h"


CAppStateGameTetrisClassic CAppStateGameTetrisClassic::Instance;

CAppStateGameTetrisClassic::CAppStateGameTetrisClassic() {
    Tetris_1 = NULL;
}

void CAppStateGameTetrisClassic::OnKeyDown(SDL_Keycode sym) {

    if(sym == SDLK_ESCAPE || sym == SDLK_q)
        CAppStateManager::SetActiveAppState(APPSTATE_MAIN_MENU);

    if(sym == SDLK_p || sym == SDLK_SPACE) {
        if(Tetris_1->Pause) {
            Tetris_1->Pause = false;
        } else {
            if(!Tetris_1->IsGameOver())
                Tetris_1->Pause = true;
        }
    }

    if(!Tetris_1->IsGameOver()) {
        switch(sym) {
            case SDLK_LEFT : {
                Tetris_1->MoveFigureLeft(true);
            } break;

            case SDLK_RIGHT : {
                Tetris_1->MoveFigureRight(true);
            } break;

            case SDLK_UP : {
                Tetris_1->FigureRotate(true);
            } break;

            case SDLK_DOWN : {
                Tetris_1->SpeedUp();
            } break;

            default: {
            }
        }
    } else {
        switch(sym) {
            case SDLK_SPACE : {
                Tetris_1->Reset();
            } break;


            default: {
            }
        }
    }
}

void CAppStateGameTetrisClassic::OnKeyUp(SDL_Keycode sym){
    if(!Tetris_1->IsGameOver()) {
        switch(sym) {
            case SDLK_DOWN : {
                Tetris_1->SpeedDown();
            } break;

            case SDLK_RIGHT : {
                Tetris_1->MoveFigureRight(false);
            } break;

            case SDLK_LEFT : {
                Tetris_1->MoveFigureLeft(false);
            } break;

            case SDLK_UP : {
                Tetris_1->FigureRotate(false);
            } break;

            default: {
            }
        }
    }
}

void CAppStateGameTetrisClassic::OnActivate() {
    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();
    SDL_Surface* Surf_Text_Buf = NULL;

    int w = AppInstance->GetWindowWidth()/2 - TextureBank::Get("desk")->GetWidth()/2;

    Tetris_1 = new CTetris;

    Tetris_1->OnInit("icons", w+20, 20, w+260, 40, w+244, 156, w+244, 216);
    Tetris_1->FigureFallingDown = true;

    const char* file = "fonts/Century_Gothic_Bold_Italic.ttf";

    int ptsize = 20;
    if((Font_Desk_Titles = TTF_OpenFont(file, ptsize)) == NULL) {
        Log("Couldn't initialize SDL_ttf: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    ptsize = 40;
    if((Font_Desk_Titles40 = TTF_OpenFont(file, ptsize)) == NULL) {
        Log("Couldn't initialize SDL_ttf: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    SDL_Color color = {255 , 255, 0};

    const char* Title_Next = "Далее:";
    if((Surf_Text_Buf = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Next, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }
    Tex_Title_Next = SDL_CreateTextureFromSurface(Renderer, Surf_Text_Buf);

    const char* Title_Lines = "Линии:";
    if((Surf_Text_Buf = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Lines, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }
    Tex_Title_Lines = SDL_CreateTextureFromSurface(Renderer, Surf_Text_Buf);

    const char* Title_Levels = "Уровень:";
    if((Surf_Text_Buf = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Levels, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }
    Tex_Title_Level = SDL_CreateTextureFromSurface(Renderer, Surf_Text_Buf);

    const char* Title_Pause = "Пауза";
    if((Surf_Text_Buf = TTF_RenderUTF8_Blended(Font_Desk_Titles40, Title_Pause, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }
    Tex_Text_Pause = SDL_CreateTextureFromSurface(Renderer, Surf_Text_Buf);

    const char* Title_GameOver = "Игра окончена!";
    if((Surf_Text_Buf = TTF_RenderUTF8_Blended(Font_Desk_Titles40, Title_GameOver, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }
    Tex_Text_GameOver = SDL_CreateTextureFromSurface(Renderer, Surf_Text_Buf);

    const char* Title_Info = "Нажмите \"пробел\" чтобы начать заново";
    if((Surf_Text_Buf = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Info, color)) == NULL) {
        fprintf(stderr,
                "TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }
    Tex_Text_GameOverInfo = SDL_CreateTextureFromSurface(Renderer, Surf_Text_Buf);

    SDL_FreeSurface(Surf_Text_Buf);
}

void CAppStateGameTetrisClassic::OnDeactivate() {
    delete Tetris_1;

    if(Tex_Title_Next) {
		SDL_DestroyTexture(Tex_Title_Next);
		Tex_Title_Next = NULL;
	}

	if(Tex_Title_Lines) {
		SDL_DestroyTexture(Tex_Title_Lines);
		Tex_Title_Lines = NULL;
	}

	if(Tex_Title_Level) {
		SDL_DestroyTexture(Tex_Title_Level);
		Tex_Title_Level = NULL;
	}

	if(Tex_Text_Pause) {
		SDL_DestroyTexture(Tex_Text_Pause);
		Tex_Text_Pause = NULL;
	}

	if(Tex_Text_GameOver) {
		SDL_DestroyTexture(Tex_Text_GameOver);
		Tex_Text_GameOver = NULL;
	}

	if(Tex_Text_GameOverInfo) {
		SDL_DestroyTexture(Tex_Text_GameOverInfo);
		Tex_Text_GameOverInfo = NULL;
	}

    TTF_CloseFont(Font_Desk_Titles);
    TTF_CloseFont(Font_Desk_Titles40);
}

void CAppStateGameTetrisClassic::OnLoop() {
    Tetris_1->OnLoop();
}

void CAppStateGameTetrisClassic::OnRender() {
    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();
    int w = 0, h = 0;

    TextureBank::Get("bg")->Render(0, 0);

    if(Tetris_1->IsGameOver()) {
        SDL_QueryTexture(Tex_Text_GameOver, NULL, NULL, &w, &h);
        SDL_Rect Destination_GameOver = {
            AppInstance->GetWindowWidth()/2 - w/2,
            AppInstance->GetWindowHeight()/2 - h/2,
            w, h};
        SDL_RenderCopy(Renderer, Tex_Text_GameOver, NULL, &Destination_GameOver);

        SDL_QueryTexture(Tex_Text_GameOverInfo, NULL, NULL, &w, &h);
        SDL_Rect Destination_GameOverInfo = {
            AppInstance->GetWindowWidth()/2 - w/2,
            AppInstance->GetWindowHeight() - h,
            w, h};
        SDL_RenderCopy(Renderer, Tex_Text_GameOverInfo, NULL, &Destination_GameOverInfo);
    } else {
        if(Tetris_1->Pause) {
            SDL_QueryTexture(Tex_Text_Pause, NULL, NULL, &w, &h);
            SDL_Rect Destination_Pause = {
                AppInstance->GetWindowWidth()/2 - w/2,
                AppInstance->GetWindowHeight()/2 - h/2,
                w, h};
            SDL_RenderCopy(Renderer, Tex_Text_Pause, NULL, &Destination_Pause);
        } else {
            int desk_start_x = AppInstance->GetWindowWidth()/2 - TextureBank::Get("desk")->GetWidth()/2;

            TextureBank::Get("desk")->Render(desk_start_x, 0);

            SDL_QueryTexture(Tex_Title_Next, NULL, NULL, &w, &h);
            SDL_Rect Destination_Next = {
                desk_start_x+(260 + (340-260)/2) - (w/2),
                40 - h,
                w, h};
            SDL_RenderCopy(Renderer, Tex_Title_Next, NULL, &Destination_Next);

            SDL_QueryTexture(Tex_Title_Lines, NULL, NULL, &w, &h);
            SDL_Rect Destination_Lines = {
                desk_start_x+(240 + (360-240)/2) - (w/2),
                160 - h,
                w, h};
            SDL_RenderCopy(Renderer, Tex_Title_Lines, NULL, &Destination_Lines);

            SDL_QueryTexture(Tex_Title_Level, NULL, NULL, &w, &h);
            SDL_Rect Destination_Level = {
                desk_start_x+(240 + (360-240)/2) - (w/2),
                220 - h,
                w, h};
            SDL_RenderCopy(Renderer, Tex_Title_Level, NULL, &Destination_Level);

            Tetris_1->OnRender();
        }
    }
}

CAppStateGameTetrisClassic* CAppStateGameTetrisClassic::GetInstance() {
    return &Instance;
}
