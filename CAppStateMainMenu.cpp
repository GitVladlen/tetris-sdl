#include "CAppStateMainMenu.h"

#include "CAppStateManager.h"
#include "Log.h"
#include "App.h"

CAppStateMainMenu CAppStateMainMenu::Instance;

CAppStateMainMenu::CAppStateMainMenu() {
    Font = NULL;
}

void CAppStateMainMenu::OnKeyDown(SDL_Keycode sym) {
    switch(sym) {
        case SDLK_1 : {
//            CAppStateManager::SetActiveAppState(APPSTATE_GAME_TETRIS_CLASSIC);
        } break;

        case SDLK_2 : {
//            CAppStateManager::SetActiveAppState(APPSTATE_GAME_TETRIS_DUAL);
        } break;

        case SDLK_ESCAPE : {
            CAppStateManager::SetActiveAppState(APPSTATE_NONE);
        } break;

        default: {
        }
    }
}

void CAppStateMainMenu::OnActivate() {
    const char* file = "fonts/Century_Gothic_Bold_Italic.ttf";
    int ptsize = 30;

    if((Font = TTF_OpenFont(file, ptsize)) == NULL) {
        Log("Couldn't initialize SDL_ttf: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();

    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 0;

    const char* Text1 = "\"1\" - Одиночная игра";

    SDL_Surface* Surf_Text = NULL;

    if((Surf_Text = TTF_RenderUTF8_Blended(Font, Text1, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    Tex_Text_1 = SDL_CreateTextureFromSurface(Renderer, Surf_Text);

    const char* Text2 = "\"2\" - Игра на двоих";

    if((Surf_Text = TTF_RenderUTF8_Blended(Font, Text2, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    Tex_Text_2 = SDL_CreateTextureFromSurface(Renderer, Surf_Text);

    const char* Text3 = "\"ESC\" - Выход";

    if((Surf_Text = TTF_RenderUTF8_Blended(Font, Text3, color)) == NULL) {
        Log("TTF_RenderText_Blended Error: %s\n", TTF_GetError());
        CAppStateManager::SetActiveAppState(APPSTATE_NONE);
    }

    Tex_Text_3 = SDL_CreateTextureFromSurface(Renderer, Surf_Text);

    SDL_FreeSurface(Surf_Text);
}

void CAppStateMainMenu::OnDeactivate() {
    if(Font) {
        TTF_CloseFont(Font);
        Font = NULL;
    }

    if(Tex_Text_1) {
		SDL_DestroyTexture(Tex_Text_1);
		Tex_Text_1 = NULL;
	}

	if(Tex_Text_2) {
		SDL_DestroyTexture(Tex_Text_2);
		Tex_Text_2 = NULL;
	}

	if(Tex_Text_3) {
		SDL_DestroyTexture(Tex_Text_3);
		Tex_Text_3 = NULL;
	}
}

void CAppStateMainMenu::OnLoop() {
}

void CAppStateMainMenu::OnRender() {
    TextureBank::Get("bg")->Render(0, 0);

    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();

    int w = 0;
    int h = 0;

    SDL_QueryTexture(Tex_Text_1, NULL, NULL, &w, &h);

    SDL_Rect Destination_1 = {
        AppInstance->GetWindowWidth()/2-w/2,
        AppInstance->GetWindowHeight()/2-3*h/2,
        w,
        h
    };

	SDL_RenderCopy(Renderer, Tex_Text_1, NULL, &Destination_1);

	SDL_QueryTexture(Tex_Text_2, NULL, NULL, &w, &h);

    SDL_Rect Destination_2 = {
        AppInstance->GetWindowWidth()/2-w/2,
        AppInstance->GetWindowHeight()/2-3*h/2+h,
        w,
        h
    };

	SDL_RenderCopy(Renderer, Tex_Text_2, NULL, &Destination_2);

    SDL_QueryTexture(Tex_Text_3, NULL, NULL, &w, &h);

    SDL_Rect Destination_3 = {
        AppInstance->GetWindowWidth()/2-w/2,
        AppInstance->GetWindowHeight()/2-3*h/2+2*h,
        w,
        h
    };

	SDL_RenderCopy(Renderer, Tex_Text_3, NULL, &Destination_3);
}

CAppStateMainMenu* CAppStateMainMenu::GetInstance() {
    return &Instance;
}

