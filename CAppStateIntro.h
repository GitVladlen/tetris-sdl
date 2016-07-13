#ifndef __CAPPSTATEINTRO_H__
    #define __CAPPSTATEINTRO_H__

#include "CAppState.h"
#include <SDL2/SDL_ttf.h>
//#include "CSurface.h"

class CAppStateIntro : public CAppState {
    private:
        static CAppStateIntro Instance;

        int StartTime;

    private:
        CAppStateIntro();

    public:
        void OnKeyDown(SDL_Keycode sym);

    public:
        void OnActivate();

        void OnDeactivate();

        void OnLoop();

        void OnRender();

    public:
        static CAppStateIntro* GetInstance();
};

#endif
