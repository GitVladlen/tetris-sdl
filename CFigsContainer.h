#ifndef _CFIGSCONTAINER_H_
    #define _CFIGSCONTAINER_H_

#include "Define.h"
#include <array>

class CFigsContainer {
    private:
        std::array< std::array<int, 4>, 4> IFig1;
        std::array< std::array<int, 4>, 4> IFig2;
        std::array< std::array<int, 4>, 4> JFig1;
        std::array< std::array<int, 4>, 4> JFig2;
        std::array< std::array<int, 4>, 4> JFig3;
        std::array< std::array<int, 4>, 4> JFig4;
        std::array< std::array<int, 4>, 4> LFig1;
        std::array< std::array<int, 4>, 4> LFig2;
        std::array< std::array<int, 4>, 4> LFig3;
        std::array< std::array<int, 4>, 4> LFig4;
        std::array< std::array<int, 4>, 4> OFig1;
        std::array< std::array<int, 4>, 4> SFig1;
        std::array< std::array<int, 4>, 4> SFig2;
        std::array< std::array<int, 4>, 4> ZFig1;
        std::array< std::array<int, 4>, 4> ZFig2;
        std::array< std::array<int, 4>, 4> TFig1;
        std::array< std::array<int, 4>, 4> TFig2;
        std::array< std::array<int, 4>, 4> TFig3;
        std::array< std::array<int, 4>, 4> TFig4;

        std::array< std::array< std::array< std::array<int, 4>, 4>*, 4>, 7> pFigs;

    public:
        CFigsContainer();
        std::array< std::array<int, 4>, 4>* GetPointerOnFig(int FigureID, int RotationFrameID);
};

#endif
