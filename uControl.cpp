#include "uControl.h"

uControl::uControl()
{
    MemRead = 1;
    IRWrite = 1;
    IorD = 0;
    ALUSrcA = 0;
    PCWrite = 1;

    ALUSrcB = 1;
    ALUOp = 0;
    PCSource = 0;
}

uControl::~uControl()
{
    //dtor
}
