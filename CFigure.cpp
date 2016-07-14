#include <cstddef>
#include "CFigure.h"

//****************************************************************
//Static member
//****************************************************************
CFigsContainer CFigure::FigsContainer;
//----------------------------------------------------------------

//****************************************************************
//Constructor
//****************************************************************
CFigure::CFigure() {
    //Set up to NULL our pointer to grid of Figure that is containing in FigsContainer
    Height = FIGURE_HEIGHT;
    Width = FIGURE_WIDTH;
    pFigureGrid = NULL;
    Visible = false;
}
//----------------------------------------------------------------

//****************************************************************
//Destructor
//****************************************************************
CFigure::~CFigure() {
    //After work with pointer Set up to NULL our pointer to grid of Figure that is containing in FigsContainer
    pFigureGrid = NULL;
}
//----------------------------------------------------------------

//****************************************************************
//Set functions
//****************************************************************
void CFigure::SetFigureGrid(int Figure_ID, int Rotation_Frame_ID) {
    //Checking input
    if(Figure_ID <= FIGURE_NONE  || Figure_ID > FIGURE_ID_MAX || Rotation_Frame_ID <= ROTATION_FRAME_NONE ||Rotation_Frame_ID > ROTATION_FRAME_ID_MAX) {
        pFigureGrid = NULL;
        return;
    }

    //If all are OK getting pointer to Grid of Figure from FigsContainer
    pFigureGrid = FigsContainer.GetPointerOnFig(Figure_ID, Rotation_Frame_ID);
    FigureID = Figure_ID;
    FigureRotationID = Rotation_Frame_ID;
}
//----------------------------------------------------------------

//****************************************************************
//Get functions
//****************************************************************
int CFigure::GetCell(int r, int c) {
    //Checking input
    if(r < 0 || r >= FIGURE_HEIGHT || c < 0 || c >= FIGURE_WIDTH) {
        return BLOCK_ERROR;
    }
    if(!pFigureGrid) {
        return BLOCK_ERROR;
    }

    //If all are OK
//    return *(pFigureGrid+(FIGURE_HEIGHT*r+c));
    return (*pFigureGrid)[r][c];
}

int CFigure::GetWidth() {
    return Width;
}

int CFigure::GetHeight() {
    return Height;
}

int CFigure::GetFigureID() {
    return FigureID;
}

int CFigure::GetFigureRotationID() {
    return FigureRotationID;
}
//----------------------------------------------------------------
