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
                //fprintf(stderr, "MoveFigureLeftKeyDown\n");
                Tetris_1->MoveFigureLeft();
            } break;

            case SDLK_RIGHT : {
                //fprintf(stderr, "MoveFigureRightKeyDown\n");
                Tetris_1->MoveFigureRight();
            } break;

            case SDLK_UP : {
                //fprintf(stderr, "MoveFigureRotateKeyDown\n");
                Tetris_1->FigureRotate();
            } break;

            case SDLK_DOWN : {
                //fprintf(stderr, "MoveFigureDownKeyDown\n");
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
                Tetris_1->MoveFigureRight();
            } break;

            case SDLK_LEFT : {
                Tetris_1->MoveFigureLeft();
            } break;

            case SDLK_UP : {
                Tetris_1->FigureRotate();
            } break;

            default: {
            }
        }
    }
}

void CAppStateGameTetrisClassic::OnActivate() {
    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();
    SDL_Surface* Surf_Desk_Titles = NULL;

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

    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 0;

    const char* Title_Next = "Далее:";

    if((Surf_Desk_Titles = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Next, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    Tex_Title_Next = SDL_CreateTextureFromSurface(Renderer, Surf_Desk_Titles);

    const char* Title_Lines = "Линии:";

    if((Surf_Desk_Titles = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Lines, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    Tex_Title_Lines = SDL_CreateTextureFromSurface(Renderer, Surf_Desk_Titles);

    const char* Title_Levels = "Уровень:";


    if((Surf_Desk_Titles = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Levels, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    Tex_Title_Level = SDL_CreateTextureFromSurface(Renderer, Surf_Desk_Titles);

    SDL_FreeSurface(Surf_Desk_Titles);
}

void CAppStateGameTetrisClassic::OnDeactivate() {
    delete Tetris_1;

    TTF_CloseFont(Font_Desk_Titles);
    TTF_CloseFont(Font_Desk_Titles40);
}

void CAppStateGameTetrisClassic::OnLoop() {
    Tetris_1->OnLoop();
}

void CAppStateGameTetrisClassic::OnRender() {
    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();
    int w = 0;
    int h = 0;

    int desk_start_x = AppInstance->GetWindowWidth()/2 - TextureBank::Get("desk")->GetWidth()/2;

    TextureBank::Get("bg")->Render(0, 0);
    TextureBank::Get("desk")->Render(desk_start_x, 0);

    SDL_QueryTexture(Tex_Title_Next, NULL, NULL, &w, &h);
    SDL_Rect Destination_Next = {
        desk_start_x+(260 + (340-260)/2) - (w/2),
        40 - h,
        w, h
    };
	SDL_RenderCopy(Renderer, Tex_Title_Next, NULL, &Destination_Next);

    SDL_QueryTexture(Tex_Title_Lines, NULL, NULL, &w, &h);
    SDL_Rect Destination_Lines = {
        desk_start_x+(240 + (360-240)/2) - (w/2),
        160 - h,
        w, h
    };
	SDL_RenderCopy(Renderer, Tex_Title_Lines, NULL, &Destination_Lines);

    SDL_QueryTexture(Tex_Title_Level, NULL, NULL, &w, &h);
    SDL_Rect Destination_Level = {
        desk_start_x+(240 + (360-240)/2) - (w/2),
        220 - h,
        w, h
    };
	SDL_RenderCopy(Renderer, Tex_Title_Level, NULL, &Destination_Level);

    if(Tetris_1->IsGameOver()) {
////        CSurface::OnDraw(Surf_Display, Surf_BG, 0, 0);
//        SDL_Color color;
//        color.r = 255;
//        color.g = 255;
//        color.b = 0;
//
//        const char* Title_GameOver = "Игра окончена!";
//
//        if((Surf_Desk_Titles = TTF_RenderUTF8_Blended(Font_Desk_Titles40, Title_GameOver, color)) == NULL) {
//            fprintf(stderr,
//                    "TTF_RenderText_Blended Error: %s\n", TTF_GetError());
//            CAppStateManager::SetActiveAppState(APPSTATE_NONE);
//        }
//
//        int x = Surf_Display->w/2 - Surf_Desk_Titles->w/2;
//        int y = Surf_Display->h/2 - Surf_Desk_Titles->h/2;
//        int h = Surf_Desk_Titles->h;
//
//        CSurface::OnDraw(Surf_Display, Surf_Desk_Titles, x, y);
//
//        const char* Title_Info1 = "Нажмите \"пробел\" чтобы начать заново";
//
//        if((Surf_Desk_Titles = TTF_RenderUTF8_Blended(Font_Desk_Titles, Title_Info1, color)) == NULL) {
//            fprintf(stderr,
//                    "TTF_RenderText_Blended Error: %s\n", TTF_GetError());
//            CAppStateManager::SetActiveAppState(APPSTATE_NONE);
//        }
//
//        x = Surf_Display->w/2 - Surf_Desk_Titles->w/2;
//        y = Surf_Display->h - Surf_Desk_Titles->h;
//
//        CSurface::OnDraw(Surf_Display, Surf_Desk_Titles, x, y);
    } else {
        Tetris_1->OnRender();
    }

//    if(Tetris_1->Pause) {
//        //CSurface::OnDraw(Surf_Display, Surf_Pause, 0, 0);
//        CSurface::OnDraw(Surf_Display, Surf_BG, 0, 0);
//
//        SDL_Color color2 = {255, 255, 0};
//
//        const char* Title_GameOver = "Пауза";
//
//        if((Surf_Desk_Titles = TTF_RenderUTF8_Blended(Font_Desk_Titles40, Title_GameOver, color2)) == NULL) {
//            fprintf(stderr,
//                    "TTF_RenderText_Blended Error: %s\n", TTF_GetError());
//            CAppStateManager::SetActiveAppState(APPSTATE_NONE);
//        }
//
//        CSurface::OnDraw(Surf_Display, Surf_Desk_Titles, Surf_Display->w/2 - Surf_Desk_Titles->w/2, Surf_Display->h/2 - Surf_Desk_Titles->h/2);
//    }
}

CAppStateGameTetrisClassic* CAppStateGameTetrisClassic::GetInstance() {
    return &Instance;
}
