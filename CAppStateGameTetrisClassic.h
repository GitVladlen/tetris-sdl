#ifndef __CAPPSTATEGAMETETRISCLASSIC_H__
    #define __CAPPSTATEGAMETETRISCLASSIC_H__

#include <SDL2/SDL_ttf.h>
#include <string>
#include "CAppState.h"
#include "CTetris.h"

class CAppStateGameTetrisClassic : public CAppState {
    private:
        static CAppStateGameTetrisClassic Instance;

        SDL_Texture* Tex_Title_Next;
        SDL_Texture* Tex_Title_Lines;
        SDL_Texture* Tex_Title_Level;

        TTF_Font* Font_Desk_Titles;
        TTF_Font* Font_Desk_Titles40;


    private:
        CAppStateGameTetrisClassic();

    private:
        CTetris* Tetris_1;

    public:
        void OnKeyDown(SDL_Keycode sym);

        void OnKeyUp(SDL_Keycode sym);

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:
        static CAppStateGameTetrisClassic* GetInstance();
};

#endif
