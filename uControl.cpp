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
    opcode = op;
}


void uControl::resetSinal()
{
    
}


void uControl::setSinalEtapa2()
{
    //resetSinal();
    ALUSrcA = 0;
    ALUSrcB = 3;
    ALUOp = 0;
}


void uControl::setSinalEtapa3()
{
    switch(op)
    {
        case 0:
            cout<<"type r"<<endl;
            ALUSrcA = 1;
            ALUSrcB = 0;
            ALUOp = 2;
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
            ALUSrcA = 1;
            ALUSrcB = 0;
            ALUOp = 2;
            break;
        case 43:
            cout<<"sw"<<endl;
            ALUSrcA = 1;
            ALUSrcB = 0;
            ALUOp = 2;
            break;
        default:
            cout<<"opcode error"<<endl;
            break;
    }
}


void uControl::setSinalEtapa4()
{

}


void uControl::setSinalEtapa5()
{

}


