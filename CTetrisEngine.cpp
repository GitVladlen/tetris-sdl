#include "CTetrisEngine.h"

#include <time.h>

CTetrisEngine::CTetrisEngine() {
    Desk.FigurePosition.row = FIGURE_RESET_POSITION_ROW;
    Desk.FigurePosition.col = FIGURE_RESET_POSITION_COL;
    Desk.FigurePosition.w = 4;
    Desk.FigurePosition.h = 4;
    Desk.Figure.Visible = true;

    //Initializing of Desk.Figure and NextFigure
    srand(time(NULL));
    int min = FIGURE_NONE+1; int max = FIGURE_ID_MAX+1;

    int CurrentFallingFigureID = min+rand()%(max-min);
    int CurrentNextFigureID = min+rand()%(max-min);

    min = ROTATION_FRAME_NONE+1; max = ROTATION_FRAME_ID_MAX +1;

    int CurrentFallingFigureRotationID = min+rand()%(max-min);
    int CurrentNextFigureRotationID = min+rand()%(max-min);

    Desk.Figure.SetFigureGrid(CurrentFallingFigureID, CurrentFallingFigureRotationID);
    NextFigure.SetFigureGrid(CurrentNextFigureID, CurrentNextFigureRotationID);
    //--

    GameOver = false;
}

int CTetrisEngine::GetDeskCell(int r, int c) {
    if((r >= Desk.FigurePosition.row && r < Desk.FigurePosition.row+Desk.FigurePosition.h && c >= Desk.FigurePosition.col && c < Desk.FigurePosition.col+Desk.FigurePosition.w) && Desk.Figure.Visible && Desk.Figure.GetCell(r-Desk.FigurePosition.row, c-Desk.FigurePosition.col) != BLOCK_NONE) {
            return Desk.Figure.GetCell(r-Desk.FigurePosition.row, c-Desk.FigurePosition.col);
    } else {
        return Desk.GetCell(r, c);
    }
}

void CTetrisEngine::MoveFallingFigureLeft() {
    if(Desk.CanMoveFigureTo(Desk.FigurePosition.row, Desk.FigurePosition.col-1)) {
        Desk.MoveFigureTo(Desk.FigurePosition.row, Desk.FigurePosition.col-1);
    }
}

void CTetrisEngine::MoveFallingFigureRight() {
    if(Desk.CanMoveFigureTo(Desk.FigurePosition.row, Desk.FigurePosition.col+1)) {
        Desk.MoveFigureTo(Desk.FigurePosition.row, Desk.FigurePosition.col+1);
    }
}

void CTetrisEngine::MoveFallingFigureDown() {
    if(Desk.CanMoveFigureTo(Desk.FigurePosition.row+1, Desk.FigurePosition.col)) {
        Desk.MoveFigureTo(Desk.FigurePosition.row+1, Desk.FigurePosition.col);
    }
}

void CTetrisEngine::DeleteFullLines() {
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
        }
    }
}

void CTetrisEngine::ExchangeFigures() {
    srand(time(NULL));
    int min = FIGURE_NONE+1; int max = FIGURE_ID_MAX+1;

    int CurrentNextFigureID = min+rand()%(max-min);

    min = ROTATION_FRAME_NONE+1; max = ROTATION_FRAME_ID_MAX +1;

    int CurrentNextFigureRotationID = min+rand()%(max-min);

    Desk.Figure.SetFigureGrid(NextFigure.GetFigureID(), NextFigure.GetFigureRotationID());
    NextFigure.SetFigureGrid(CurrentNextFigureID, CurrentNextFigureRotationID);
}

void CTetrisEngine::ResetFigure() {
    if(Desk.CanMoveFigureTo(FIGURE_RESET_POSITION_ROW, FIGURE_RESET_POSITION_COL)) {
        for(int rf = 0; rf < Desk.Figure.GetHeight(); rf++) {
            for(int cf = 0; cf < Desk.Figure.GetWidth(); cf++) {
                if(Desk.Figure.GetCell(rf, cf) != BLOCK_NONE) {
                    Desk.SetCell(Desk.FigurePosition.row+rf, Desk.FigurePosition.col+cf, Desk.Figure.GetCell(rf, cf));
                }
            }
        }

        Desk.FigurePosition.row = FIGURE_RESET_POSITION_ROW;
        Desk.FigurePosition.col = FIGURE_RESET_POSITION_COL;
    } else {
        Desk.Figure.Visible = false;
        GameOver = true;
    }


}

bool CTetrisEngine::IsGameOver() {
    return GameOver;
}
