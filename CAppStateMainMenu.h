#ifndef __CAPPSTATEMAINMENU_H__
    #define __CAPPSTATEMAINMENU_H__

#include <SDL2/SDL_ttf.h>
#include <string>
#include "CAppState.h"
//#include "CTetris.h"

class CAppStateMainMenu : public CAppState {
    private:
        static CAppStateMainMenu Instance;

        SDL_Texture* Tex_Text_1;
        SDL_Texture* Tex_Text_2;
        SDL_Texture* Tex_Text_3;

        TTF_Font* Font;

    private:
        CAppStateMainMenu();

    public:
        void OnKeyDown(SDL_Keycode sym);

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:
        static CAppStateMainMenu* GetInstance();
};

#endif

