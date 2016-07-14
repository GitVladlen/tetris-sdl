#ifndef _CTETRISENGINE_H_
    #define _CTETRISENGINE_H_

#include <cstdlib>
#include <time.h>

#include "Define.h"
#include "CFigure.h"
#include "CDesk.h"

class CTetrisEngine {
    public:
        //Constructor
        CTetrisEngine();

    public:
        //Action functions----------------------------------------------------------

        //With Falling Figure: Moving and Rotating
        virtual void MoveFallingFigureLeft();
        virtual void MoveFallingFigureRight();
        virtual void MoveFallingFigureDown();



        int GetDeskCell(int r, int c);

    protected:
        //With Desk: If in Desk Grid is full lines its delete it
        virtual void DeleteFullLines();

    protected:
        //Getting new state of Falling Figure From Next Figure
        void ExchangeFigures();

        void ResetFigure();

    protected:
        //Parameters-------------------------------------------------------------
        //Objects (containers)
        CFigure NextFigure;
        CDesk Desk;

    protected:
        //State Of Game
        bool GameOver;

    public:
        bool IsGameOver();

};

#endif
