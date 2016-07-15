#ifndef __CAPPSTATEGAMETETRISDUAL_H__
    #define __CAPPSTATEGAMETETRISDUAL_H__

#include <SDL2/SDL_ttf.h>
#include <string>
#include "CAppState.h"
#include "CTetris.h"

class CAppStateGameTetrisDual : public CAppState {
    private:
        static CAppStateGameTetrisDual Instance;

        SDL_Texture* Tex_Title_Next;
        SDL_Texture* Tex_Title_Lines;
        SDL_Texture* Tex_Title_Level;

        SDL_Texture* Tex_Text_Pause;
        SDL_Texture* Tex_Text_GameOver;
        SDL_Texture* Tex_Text_GameOverInfo;

        TTF_Font* Font_Desk_Titles;
        TTF_Font* Font_Desk_Titles40;


    private:
        CAppStateGameTetrisDual();

    private:
        CTetris* Tetris_1;
        CTetris* Tetris_2;

    public:
        void OnKeyDown(SDL_Keycode sym);

        void OnKeyUp(SDL_Keycode sym);

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:
        static CAppStateGameTetrisDual* GetInstance();
};

#endif

