#include "CAppStateIntro.h"

#include "CAppStateManager.h"
#include "TextureBank.h"
#include "Log.h"
#include "App.h"

CAppStateIntro CAppStateIntro::Instance;

CAppStateIntro::CAppStateIntro() {
}

void CAppStateIntro::OnKeyDown(SDL_Keycode sym) {
    CAppStateManager::SetActiveAppState(APPSTATE_MAIN_MENU);
}

void CAppStateIntro::OnActivate() {
    StartTime = SDL_GetTicks();
}

void CAppStateIntro::OnDeactivate() {
}

void CAppStateIntro::OnLoop() {
    if(StartTime + 3000 < SDL_GetTicks()) {
        CAppStateManager::SetActiveAppState(APPSTATE_MAIN_MENU);
    }
}

void CAppStateIntro::OnRender() {
    TextureBank::Get("logo")->Render(0, 0);
}

CAppStateIntro* CAppStateIntro::GetInstance() {
    return &Instance;
}
