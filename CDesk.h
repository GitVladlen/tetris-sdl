#ifndef _CDESK_H_
    #define _CDESK_H_

#include "Define.h"
#include "CFigure.h"

class CDesk {

//Constructor
    public:
        CDesk();

//Parameters
    private:
        //Grid of Desk
        int Grid[DESK_HEIGHT][DESK_WIDTH];
    public:
        //Figure that is inside the Desk (Falling Figure)
        CFigure Figure;
        //Position of Figure on Desk Grid
        SRect FigurePosition;

//Funcions
    //Action functions
    public:
        //Action with Desk
        void DeleteLine(int row);
        //Action with Figure
        void MoveFigureTo(int r, int c);
        void RotateFigure();
    //Get functions
    public:
        int GetCell(int r, int c);
    //Set functions
    public:
        void SetCell(int r, int c, int BlockID);
    //Check functions
    private:
        bool IsFreeSpaceForFigure(int DeskGridRow, int DeskGridCol);
    public:
        bool CanMoveFigureTo(int r, int c);

};

#endif
