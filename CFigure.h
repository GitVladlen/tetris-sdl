#ifndef _CFIGURE_H_
    #define _CFIGURE_H_

#include "Define.h"
#include "CFigsContainer.h"

class CFigure {
    public:
        //Source of grids for all figures
        static CFigsContainer FigsContainer;

    public:
        //Constructor and Destructor
        CFigure();
        ~CFigure();

    public:
        //Get functions
        int GetCell(int r, int c);
        int GetWidth();
        int GetHeight();
        int GetFigureID();
        int GetFigureRotationID();

    public:
        //Set functions
        void SetFigureGrid(int FigureID, int RotationFrameID);

        //Parameters
    private:
        //Figure grid parameterss
        std::array< std::array<int, 4>, 4>* pFigureGrid;
        int FigureID;
        int FigureRotationID;

        //Size of Figure in Blocks
        int Width;
        int Height;

    public:
        //Visibility of the Figure
        bool Visible;
};

#endif
