#include "CTetris.h"
#include <stdlib.h>
#include <string>

#include "TextureBank.h"
#include "App.h"
#include "Log.h"
#include "Texture.h"

//***********************************************************************
//Static value for randomazing
//***********************************************************************
long CTetris::RandBase = time(NULL);
//-----------------------------------------------------------------------

//***********************************************************************
//Constructor
//***********************************************************************
CTetris::CTetris() {
    Tex_Lines = NULL;
    Tex_Level = NULL;
    Font_Output = NULL;
    pOtherPlayer = NULL;
}
//-----------------------------------------------------------------------

//***********************************************************************
//Action functions
//***********************************************************************
bool CTetris::OnInit(std::string Texture_ID, int Desk_X, int Desk_Y, int NextFigure_X, int NextFigure_Y, int Lines_X, int Lines_Y, int Level_X, int Level_Y, CTetris* p_Other_Player) {
    Blocks_Texture_ID = Texture_ID;
    pOtherPlayer = p_Other_Player;

    DeskX = Desk_X;
    DeskY = Desk_Y;

    NextFigureX = NextFigure_X;
    NextFigureY = NextFigure_Y;

    NextFigure.Visible = true;

    LinesX = Lines_X;
    LinesY = Lines_Y;
    Lines = 0;

    LevelX = Level_X;
    LevelY = Level_Y;
    Level = 0;
    LevelUp = true;

    FigureFallingDown = false;
    FrameRate       = 1000; //Milliseconds
    FrameRateBuffer       = 0; //Milliseconds
    FrameRateRightLeft = 150; //Milliseconds
    FrameRateRotate = 200; //Milliseconds
    OldTime         = 0;

    Pause = false;

    const char* file = "fonts/Century_Gothic_Bold_Italic.ttf";
    int ptsize = 20;

    if((Font_Output = TTF_OpenFont(file, ptsize)) == NULL) {
        Log("CTetris: TTF_OpenFont Error: %s\n", TTF_GetError());
        return false;
    }

    DeleteFullLinesFlag = true;

    //Debuging
    MoveLeft = false;
    MoveRight = false;
    Rotate = false;

    TimeCounterLeft = 0;
    TimeCounterRight = 0;
    TimeCounterRotate = 0;

    RandomizeFigures();

}

void CTetris::OnLoop() {

    if(FigureFallingDown) {
        if(FigureMustFallDown()) {

                if(CanMoveFallingFigureDown()) {
                    MoveFallingFigureDown();
                } else {
                    ResetFigure();
                    if(!GameOver) {
                        ExchangeFigures();
                    } else {
                        if(pOtherPlayer) {
                            pOtherPlayer->Win();
                        }
                    }
                    DeleteFullLines();
                }

        }
    }

    if(MoveRight) {
        if(FigureMustMoveRight()) {
            MoveFallingFigureRight();
        }
    }

    if(MoveLeft) {
        if(FigureMustMoveLeft()) {
            MoveFallingFigureLeft();
        }
    }

    if(Rotate) {
        if(FigureMustRotate()) {
            RotateFigure();
        }
    }

    if(Level != (Lines/20)) {
        LevelUp = true;
        Level = Lines/20;

        if(FrameRateBuffer != 0) {
            if(FrameRateBuffer*0.7 > 0) {
                FrameRateBuffer = FrameRateBuffer*0.7;
            }
        } else {
            if(FrameRate*0.7 > 0) {
                FrameRate = FrameRate*0.7;
            }
        }

    }

}

void CTetris::OnRender() {


    for(int r = 0; r < DESK_HEIGHT; r++) {
        for(int c = 0; c < DESK_WIDTH; c++){
            if(GetDeskCell(r,c) >= BLOCK_RED){
                int x = DeskX + c * BLOCK_SIZE;
                int y = DeskY + r * BLOCK_SIZE;

                TextureBank::Get(Blocks_Texture_ID)->Render(x, y, 0, (GetDeskCell(r,c)-1)*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
            }
        }
    }


    if(NextFigure.Visible){

        for(int r = 0; r < NextFigure.GetHeight(); r++) {
            for(int c = 0; c < NextFigure.GetWidth(); c++){
                if(NextFigure.GetCell(r,c) != BLOCK_NONE){
                    int x = NextFigureX + c * BLOCK_SIZE;
                    int y = NextFigureY + r * BLOCK_SIZE;

                    TextureBank::Get(Blocks_Texture_ID)->Render(x, y, 0, (NextFigure.GetCell(r,c)-1)*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                }
            }
        }
    }

    App* AppInstance = App::GetInstance();
    SDL_Renderer* Renderer = AppInstance->GetRenderer();

    SDL_Surface* Surf_Lines_Font = NULL;
    SDL_Surface* Surf_Level_Font = NULL;

    int w = 0;
    int h = 0;

    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 0;

    if(DeleteFullLinesFlag) {
        DeleteFullLinesFlag = false;
    }

    char msg1[10];
    sprintf(msg1,"%d",Lines);
    const char* msgLines = msg1;

    if((Surf_Lines_Font = TTF_RenderText_Blended(Font_Output, msgLines, color)) == NULL) {
        Log("CTetris: TTF_RenderText_Blended Error: %s\n", TTF_GetError());
    }

    if(Tex_Lines) {
        SDL_DestroyTexture(Tex_Lines);
        Tex_Lines = NULL;
    }

    Tex_Lines = Texture::SurfaceToTexture(Renderer, Surf_Lines_Font);

    SDL_QueryTexture(Tex_Lines, NULL, NULL, &w, &h);
    SDL_Rect Destination_Lines = {LinesX, LinesY, w, h};
    SDL_RenderCopy(Renderer, Tex_Lines, NULL, &Destination_Lines);

    if(LevelUp) {
        LevelUp = false;
    }

    char msg2[10];
    sprintf(msg2, "%d", Level);
    const char* msgLevel = msg2;

    if((Surf_Level_Font = TTF_RenderText_Blended(Font_Output, msgLevel, color)) == NULL) {
        Log("CTetris: TTF_RenderText_Blended Error: %s\n", TTF_GetError());
    }

    if(Tex_Level) {
        SDL_DestroyTexture(Tex_Level);
        Tex_Level = NULL;
    }
    Tex_Level = Texture::SurfaceToTexture(Renderer, Surf_Level_Font);

    SDL_QueryTexture(Tex_Level, NULL, NULL, &w, &h);
    SDL_Rect Destination_Level = {LevelX, LevelY, w, h};
    SDL_RenderCopy(Renderer, Tex_Level, NULL, &Destination_Level);
}

void CTetris::MoveFallingFigureDown() {
    Desk.MoveFigureTo(Desk.FigurePosition.row+1, Desk.FigurePosition.col);
}

void CTetris::MoveFigureRight(bool value) {
    MoveRight = value;
}

void CTetris::MoveFigureLeft(bool value) {
    MoveLeft = value;
}

void CTetris::FigureRotate(bool value) {
    Rotate = value;
}

void CTetris::RotateFigure() {
    Desk.RotateFigure();
}

void CTetris::SpeedUp() {if(Tex_Lines) {
		SDL_DestroyTexture(Tex_Lines);
		Tex_Lines = NULL;
	}
    if (FrameRateBuffer == 0) FrameRateBuffer = FrameRate;
    FrameRate = 50;
}

void CTetris::SpeedDown() {
    FrameRate = FrameRateBuffer;
    FrameRateBuffer = 0;
}

void CTetris::Reset() {
    for(int r = 0; r < DESK_HEIGHT; r++) {
        for(int c = 0; c < DESK_WIDTH; c++) {
            Desk.SetCell(r, c, BLOCK_NONE);
        }
    }

    //ResetFigure();
    Desk.FigurePosition.row = FIGURE_RESET_POSITION_ROW;
    Desk.FigurePosition.col = FIGURE_RESET_POSITION_COL;

    ExchangeFigures();

    FigureFallingDown = true;

    GameOver = false;

    FrameRate       = 1000; //Milliseconds
    FrameRateRightLeft = 150; //Milliseconds
    FrameRateRotate = 200; //Milliseconds
    OldTime         = 0;

    Lines = 0;
    Level = 0;
    DeleteFullLinesFlag = true;
    LevelUp = true;

    RandomizeFigures();

}



void CTetris::DeleteFullLines() {
    bool Full;
    for(int r = 0; r < DESK_HEIGHT; r++) {
        Full = true;
        for(int c = 0; c < DESK_WIDTH; c++) {
            if(Desk.GetCell(r, c) == BLOCK_NONE) {
                Full = false;
                break;
            }
        }
        if(Full) {
            Desk.DeleteLine(r);
            Lines++;
            DeleteFullLinesFlag = true;
            if(pOtherPlayer) {
                pOtherPlayer->AddLine();
            }
        }
    }
}

void CTetris::AddLine() {
    for(int r = 1; r < DESK_HEIGHT; r++) {
        for(int c = 0; c < DESK_WIDTH; c++) {
            Desk.SetCell(r-1, c, Desk.GetCell(r, c));
        }
    }

    if(RandBase >= 64000) {
        RandBase = 0;
    }

    RandBase++;
    srand(RandBase);

    bool NotValid = true;

    while(NotValid) {
        for(int r = DESK_HEIGHT-1, c = 0; c < DESK_WIDTH; c++) {

            int min = BLOCK_NONE; int max = BLOCK_ID_MAX+1;
            int BT = min+rand()%(max-min);

            Desk.SetCell(r, c, BT);

            if(BT == BLOCK_NONE) {
                NotValid = false;
            }
        }
    }

    if(Desk.FigurePosition.row != FIGURE_RESET_POSITION_ROW) {
        Desk.FigurePosition.row--;
    }
}

void CTetris::Win() {
    GameOver = true;
}

void CTetris::RandomizeFigures() {
    if(RandBase >= 64000) {
        RandBase = 0;
    }

    RandBase++;
    srand(RandBase);

    int min = FIGURE_NONE+1; int max = FIGURE_ID_MAX+1;

    int CurrentFallingFigureID = min+rand()%(max-min);
    int CurrentNextFigureID = min+rand()%(max-min);

    min = ROTATION_FRAME_NONE+1; max = ROTATION_FRAME_ID_MAX +1;

    int CurrentFallingFigureRotationID = min+rand()%(max-min);
    int CurrentNextFigureRotationID = min+rand()%(max-min);

    Desk.Figure.SetFigureGrid(CurrentFallingFigureID, CurrentFallingFigureRotationID);
    NextFigure.SetFigureGrid(CurrentNextFigureID, CurrentNextFigureRotationID);

}

void CTetris::OnCleanUp() {
    if(Tex_Lines) {
		SDL_DestroyTexture(Tex_Lines);
		Tex_Lines = NULL;
	}

	if(Tex_Level) {
		SDL_DestroyTexture(Tex_Level);
		Tex_Level = NULL;
	}

    if(Font_Output) TTF_CloseFont(Font_Output);

    pOtherPlayer = NULL;

    for(int r = 0; r < DESK_HEIGHT; r++) {
        for(int c = 0; c < DESK_WIDTH; c++) {
            Desk.SetCell(r, c, BLOCK_NONE);
        }
    }

    Desk.FigurePosition.row = FIGURE_RESET_POSITION_ROW;
    Desk.FigurePosition.col = FIGURE_RESET_POSITION_COL;

    ExchangeFigures();

    FigureFallingDown = true;
    GameOver = false;

    FrameRate       = 1000; //Milliseconds
    FrameRateRightLeft = 150; //Milliseconds
    FrameRateRotate = 200; //Milliseconds
    OldTime         = 0;

    Lines = 0;
    Level = 0;

    DeleteFullLinesFlag = true;
    LevelUp = true;
}
//-----------------------------------------------------------------------

//***********************************************************************
//Check functions
//***********************************************************************
bool CTetris::FigureMustFallDown() {
    if(Pause) {
        return false;
    }

    if(OldTime + FrameRate > SDL_GetTicks()) {
        return false;
    }

    OldTime = SDL_GetTicks();

    return true;
}

bool CTetris::FigureMustMoveRight() {
    if(Pause) {
        return false;
    }

    if(TimeCounterRight + FrameRateRightLeft > SDL_GetTicks()) {
        return false;
    }

    TimeCounterRight = SDL_GetTicks();

    return true;
}

bool CTetris::FigureMustMoveLeft() {
    if(Pause) {
        return false;
    }

    if(TimeCounterLeft + FrameRateRightLeft > SDL_GetTicks()) {
        return false;
    }

    TimeCounterLeft = SDL_GetTicks();

    return true;
}

bool CTetris::FigureMustRotate() {
    if(Pause) {
        return false;
    }

    if(TimeCounterRotate + FrameRateRotate > SDL_GetTicks()) {
        return false;
    }

    TimeCounterRotate = SDL_GetTicks();

    return true;
}

bool CTetris::CanMoveFallingFigureDown() {
    if(Desk.CanMoveFigureTo(Desk.FigurePosition.row+1, Desk.FigurePosition.col) == false && Desk.FigurePosition.row < 0) {
        FigureFallingDown = false;
        GameOver = true;
    }
    return Desk.CanMoveFigureTo(Desk.FigurePosition.row+1, Desk.FigurePosition.col);
}
//-----------------------------------------------------------------------







