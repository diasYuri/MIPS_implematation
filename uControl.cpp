#include <ostream>
#include <iostream>
#include "uControl.h"
using namespace std;

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

void uControl::setOpcode(int op)
{
    switch(op)
    {
        case 0:
            cout<<"type r"<<endl;
            break;
        case 2:
            cout<<"j"<<endl;
            break;
        case 3:
            cout<<"jal"<<endl;
            break;
        case 4:
            cout<<"beq"<<endl;
            break;
        case 5:
            cout<<"bne"<<endl;
            break;
        case 8:
            cout<<"add immediate"<<endl;
            break;
        case 35:
            cout<<"lw"<<endl;
            break;
        case 43:
            cout<<"sw"<<endl;
            break;
        default:
            cout<<"opcode error"<<endl;
            break;
    }
}
