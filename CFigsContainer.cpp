#include "CFigsContainer.h"

CFigsContainer::CFigsContainer() {
    int x;

    //--------Figure: I------

        x = BLOCK_AZURE;

        IFig1 = {{{0,0,0,0},
                 {x,x,x,x},
                 {0,0,0,0},
                 {0,0,0,0}}};

//        IFig1[1][0] = x;
//        IFig1[1][1] = x;
//        IFig1[1][2] = x;
//        IFig1[1][3] = x;

        IFig2 = {{{0,0,x,0},
                 {0,0,x,0},
                 {0,0,x,0},
                 {0,0,x,0}}};

//        IFig2[0][2] = x;
//        IFig2[1][2] = x;
//        IFig2[2][2] = x;
//        IFig2[3][2] = x;

    //------------------------

    //--------Figure: J-------

        x = BLOCK_BLUE;

        JFig1 = {{{0,0,0,0},
                 {0,x,0,0},
                 {0,x,x,x},
                 {0,0,0,0}}};

        JFig2 = {{{0,0,0,0},
                 {0,x,x,0},
                 {0,x,0,0},
                 {0,x,0,0}}};

        JFig3 = {{{0,0,0,0},
                 {x,x,x,0},
                 {0,0,x,0},
                 {0,0,0,0}}};

        JFig4 = {{{0,0,x,0},
                 {0,0,x,0},
                 {0,x,x,0},
                 {0,0,0,0}}};

    //------------------------

    //--------Figure: L-------

        x = BLOCK_ORANGE;

        LFig1 = {{{0,0,0,0},
                 {0,0,x,0},
                 {x,x,x,0},
                 {0,0,0,0}}};

        LFig2 = {{{0,x,0,0},
                 {0,x,0,0},
                 {0,x,x,0},
                 {0,0,0,0}}};

        LFig3 = {{{0,0,0,0},
                 {0,x,x,x},
                 {0,x,0,0},
                 {0,0,0,0}}};

        LFig4 = {{{0,0,0,0},
                 {0,x,x,0},
                 {0,0,x,0},
                 {0,0,x,0}}};

    //------------------------

    //--------Figure: O-------

        x = BLOCK_YELLOW;

        OFig1 = {{{0,0,0,0},
                 {0,x,x,0},
                 {0,x,x,0},
                 {0,0,0,0}}};

    //------------------------

    //--------Figure: S-------

        x = BLOCK_GREEN;

        SFig1 = {{{0,0,0,0},
                 {0,0,x,x},
                 {0,x,x,0},
                 {0,0,0,0}}};

        SFig2 = {{{0,0,0,0},
                 {0,x,0,0},
                 {0,x,x,0},
                 {0,0,x,0}}};

    //------------------------

    //--------Figure:Z--------

        x = BLOCK_RED;

        ZFig1 = {{{0,0,0,0},
                 {0,x,x,0},
                 {0,0,x,x},
                 {0,0,0,0}}};

        ZFig2 = {{{0,0,0,0},
                 {0,0,x,0},
                 {0,x,x,0},
                 {0,x,0,0}}};

    //------------------------

    //--------Figure: T-------

        x = BLOCK_PURPLE;

        TFig1 = {{{0,0,0,0},
                 {0,0,x,0},
                 {0,x,x,x},
                 {0,0,0,0}}};

        TFig2 = {{{0,0,0,0},
                 {0,0,x,0},
                 {0,0,x,x},
                 {0,0,x,0}}};

        TFig3 = {{{0,0,0,0},
                 {0,0,0,0},
                 {0,x,x,x},
                 {0,0,x,0}}};

        TFig4 = {{{0,0,0,0},
                 {0,0,x,0},
                 {0,x,x,0},
                 {0,0,x,0}}};

    //------------------------

    pFigs = {{{&IFig1,&IFig2,&IFig1,&IFig2},
             {&JFig1,&JFig2,&JFig3,&JFig4},
             {&LFig1,&LFig2,&LFig3,&LFig4},
             {&OFig1,&OFig1,&OFig1,&OFig1},
             {&SFig1,&SFig2,&SFig1,&SFig2},
             {&ZFig1,&ZFig2,&ZFig1,&ZFig2},
             {&TFig1,&TFig2,&TFig3,&TFig4}}};
}

std::array< std::array<int, 4>, 4>* CFigsContainer::GetPointerOnFig(int FigureID, int RotationFrameID) {
    return pFigs[FigureID][RotationFrameID];
}
