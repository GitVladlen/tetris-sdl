#ifndef _CTETRIS_H_
    #define _CTETRIS_H_

#include <cstdlib>
#include <time.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "CTetrisEngine.h"
#include "Define.h"


class CTetris : public CTetrisEngine {
    //Constructor
    public:
        CTetris();
    //Parameters
    public:
        //Static value for randomizing
        static long RandBase;
    private:
        //Main Parameters
        //Textures Names
        std::string Blocks_Texture_ID;
        //Surfaces

        SDL_Surface* Surf_Lines_Font;
        SDL_Surface* Surf_Level_Font;
        //Positions of elements on Display
        int DeskX, DeskY;
        int NextFigureX, NextFigureY;
        int LinesX, LinesY;
        int LevelX, LevelY;
        //Font
        TTF_Font* Font_Output;
        //Pointer on other Tetris for dual game
        CTetris* pOtherPlayer;



    private:
        //bool Parameters
        bool LevelUp;
        bool DeleteFullLinesFlag;

        bool MoveLeft;
        bool MoveRight;
        bool Rotate;

    public:
        bool Pause;
        bool FigureFallingDown;

    private:
        //int Parameters
        int FrameRate; //Milliseconds
        int FrameRateBuffer;
        int FrameRateRightLeft; //Milliseconds
        int FrameRateRotate; //Milliseconds
        int Lines;
        int Level;


    private:
        //long Parameters
        long OldTime;
        long TimeCounterRight;
        long TimeCounterLeft;
        long TimeCounterRotate;

    //Action functions
    public:
        //Main functions
        bool OnInit(std::string Texture_ID, int Desk_X, int Desk_Y, int NextFigure_X, int NextFigure_Y, int Lines_X, int Lines_Y, int Level_X, int Level_Y, CTetris* p_Other_Player = NULL);
        void OnLoop();
        void OnRender();
        void OnCleanUp();

    public:
        //Interface functions
        void MoveFigureLeft();
        void MoveFigureRight();
        void FigureRotate(); //Rotate in loop
        void SpeedUp();
        void SpeedDown();
        void Reset();
        //must be private and used in DeleteFullLines to add line to ypur opponent
        void AddLine();
        //For dual game mode
        void Win();

    private:
        //Extra functions
        void MoveFallingFigureDown();

        void RotateFigure(); //Once Rotate

        void DeleteFullLines();

        void RandomizeFigures(); //Randomizing fugures based on RandBase

    //Check functions
    private:
        //Extra functions
        bool CanMoveFallingFigureDown();

        bool FigureMustMoveRight();
        bool FigureMustMoveLeft();
        bool FigureMustRotate();
        bool FigureMustFallDown();

};

#endif
