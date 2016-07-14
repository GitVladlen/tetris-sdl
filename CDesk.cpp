#include "CDesk.h"

//********************************************************
//Constructor
//********************************************************
CDesk::CDesk() {
    //Seting up position of Figure to the grid range
    FigurePosition.row = 0;
    FigurePosition.col = 0;
    FigurePosition.h = FIGURE_HEIGHT;
    FigurePosition.w = FIGURE_WIDTH;

    //Visibility of Figure on Desk
    Figure.Visible = false;

    //Filling our Grid to Zero values
    for(int r = 0; r < DESK_HEIGHT; r++) {
        for(int c = 0; c < DESK_WIDTH; c++) {
            SetCell(r, c, BLOCK_NONE);
        }
    }
}
//--------------------------------------------------------

//********************************************************
//Action functions
//********************************************************
void CDesk::DeleteLine(int row) {
    for(int r = row; r > 0; r--) {
        for(int c = 0; c < DESK_WIDTH; c++) {
            this->Grid[r][c] = this->Grid[r-1][c];
        }
    }
}

void CDesk::MoveFigureTo(int r, int c) {
    FigurePosition.row = r;
    FigurePosition.col = c;
}

void CDesk::RotateFigure() {
    int CurrentFigureID = Figure.GetFigureID();
    int CurrentRotationID = Figure.GetFigureRotationID();
    int OldRotationID = CurrentRotationID;

    if(CurrentRotationID < ROTATION_FRAME_4) {
        CurrentRotationID++;
        Figure.SetFigureGrid(CurrentFigureID, CurrentRotationID);
    }else {
        CurrentRotationID = ROTATION_FRAME_1;
        Figure.SetFigureGrid(CurrentFigureID, CurrentRotationID);
    }

    if(!IsFreeSpaceForFigure(FigurePosition.row, FigurePosition.col)) {
        Figure.SetFigureGrid(CurrentFigureID, OldRotationID);
    }
}
//--------------------------------------------------------

//********************************************************
//Get functions
//********************************************************
int CDesk::GetCell(int r, int c) {
    //Checking input
    if(r < 0 || r >= DESK_HEIGHT || c < 0 || c >= DESK_WIDTH) {
        return BLOCK_ERROR;
    }

    //If all are OK
    return Grid[r][c];
}
//--------------------------------------------------------

//********************************************************
//Set functions
//********************************************************
void CDesk::SetCell(int r, int c, int BlockID) {
    //Checking input
    if(r < 0 || r >= DESK_HEIGHT || c < 0 || c >= DESK_WIDTH) {
        return;
    }

    if(BlockID < BLOCK_NONE || BlockID > BLOCK_ID_MAX) {
        return;
    }

    //If all are OK fill appropriate cell of Grid with BlockID
    Grid[r][c] = BlockID;
}
//--------------------------------------------------------

//********************************************************
//Check functions
//********************************************************
bool CDesk::IsFreeSpaceForFigure(int DeskGridRow, int DeskGridCol) {

    for(int rf = 0; rf < Figure.GetHeight(); rf++) {
        for(int cf = 0; cf < Figure.GetWidth(); cf++) {
            if(Figure.GetCell(rf, cf) != BLOCK_NONE) {
                if(DeskGridRow+rf >= 0) {
                    if(DeskGridRow+rf >= DESK_HEIGHT) {
                        return false;
                    }

                    if(this->GetCell(DeskGridRow+rf, DeskGridCol+cf) != BLOCK_NONE) {
                        return false;
                    }
                }else
                if(DeskGridCol+cf < 0 || DeskGridCol+cf >= DESK_WIDTH) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool CDesk::CanMoveFigureTo(int r, int c) {

    if(IsFreeSpaceForFigure(FigurePosition.row, FigurePosition.col) && IsFreeSpaceForFigure(r, c)) {
        return true;
    }

    return false;
}
//--------------------------------------------------------
