#include <ostream>
#include <iostream>
#include "uControl.h"
using namespace std;

uControl::uControl()
{
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
    PCWrite = 0;
    MemWrite = 0;
    IRWrite = 0;
    RegWrite = 0;
}


void uControl::setSinalEtapa1()
{
    resetSinal();
    MemRead = 1;
    IRWrite = 1;
    IorD = 0;
    ALUSrcA = 0;
    PCWrite = 1;

    ALUSrcB = 1;
    ALUOp = 0;
    PCSource = 0;

    state = 1;
}

void uControl::setSinalEtapa2()
{
    resetSinal();
    ALUSrcA = 0;
    ALUSrcB = 3;
    ALUOp = 0;
}


void uControl::setSinalEtapa3(FILE *arq)
{
    resetSinal();
    switch(opcode)
    {
        case 0:
            cout<<"Tipo de instrução: type r"<<endl;
            cout<<"Execusao ALU"<<endl;
            fprintf(arq,"Tipo de instrução: type r\nExecusao ALU\n");
            ALUSrcA = 1;
            ALUSrcB = 0;
            ALUOp = 2;
            break;
        case 2:
            cout<<"Tipo de instrução: j"<<endl;
            cout<<"Conclusao de desvio"<<endl;
            fprintf(arq,"Tipo de instrução: j\nConclusao de desvio\n");

            PCWrite = 1;
            PCSource = 2;
            state = 0;
            isJal = 0;
            break;
        case 3:
            cout<<"Tipo de instrução: jal"<<endl;
            cout<<"Conclusao de desvio"<<endl;
            fprintf(arq,"Tipo de instrução: jal\nConclusao de desvio\n");


            PCWrite = 1;
            PCSource = 2;
            state = 0;
            isJal = 1;
            break;
        case 4:
            cout<<"Tipo de instrução: beq"<<endl;
            cout<<"Conclusao de desvio"<<endl;
            fprintf(arq,"Tipo de instrução: beq\nConclusao de desvio\n");


            ALUSrcA = 1;
            ALUSrcB = 0;
            ALUOp = 1;
            PCWriteCond = 1;
            PCSource = 1;
            isBNE = 0;
            state = 0;
            break;
        case 5:
            cout<<"Tipo de instrução: bne"<<endl;
            cout<<"Conclusao de desvio"<<endl;
            fprintf(arq,"Tipo de instrução: bne\nConclusao de desvio\n");


            ALUSrcA = 1;
            ALUSrcB = 0;
            ALUOp = 1;
            PCWriteCond = 1;
            PCSource = 1;
            isBNE = 1;
            state = 0;
            break;
        case 8:
            cout<<"Tipo de instrução: add immediate"<<endl;
            cout<<"Execusao ALU"<<endl;
            fprintf(arq,"Tipo de instrução: add immediate\nExecusao ALU\n");


            ALUSrcA = 1;
            ALUSrcB = 2;
            ALUOp = 0;
            break;
        case 35:
            cout<<"Tipo de instrução: lw"<<endl;
            cout<<"Cálculo do endereço de memória na ALU"<<endl;
            fprintf(arq,"Tipo de instrução: lw\nCálculo do endereço de memória na ALU\n");

            
            ALUSrcA = 1;
            ALUSrcB = 2;
            ALUOp = 0;
            break;
        case 43:
            cout<<"Tipo de instrução: sw"<<endl;
            cout<<"Cálculo do endereço de memória na ALU"<<endl;
            fprintf(arq,"Tipo de instrução: sw\nCálculo do endereço de memória na ALU\n");


            ALUSrcA = 1;
            ALUSrcB = 2;
            ALUOp = 0;
            break;
        default:
            cout<<"opcode error"<<endl;
            break;
    }
}


void uControl::setSinalEtapa4(FILE *arq)
{
    resetSinal();
    switch(opcode)
    {
        case 0:
            cout<<"Escrita no Banco de Registradores"<<endl;
            fprintf(arq,"Escrita no Banco de Registradores\n");
            RegDst = 1;
            RegWrite = 1;
            MemtoReg = 0;
            state = 0;
            break;
        case 8:
            cout<<"Escrita no Banco de Registradores"<<endl;
            fprintf(arq,"Escrita no Banco de Registradores\n");

            RegDst = 0;
            RegWrite = 1;
            MemtoReg = 0;
            state = 0;
            break;
        case 35:
            cout<<"Leitura da Memoria"<<endl;
            fprintf(arq,"Leitura da Memoria\n");

            MemRead = 1;
            IorD = 1;
            break;
        case 43:
            cout<<"Escrita na Memoria"<<endl;
            fprintf(arq,"Escrita na Memoria\n");

            MemWrite = 1;
            IorD = 1;
            state = 0;
            break;
        default:
            cout<<"opcode error"<<endl;
            break;
    }
}


void uControl::setSinalEtapa5(FILE *arq)
{
    resetSinal();
    if(opcode == 35){
        cout<<"Escrita no Banco de Registradores"<<endl;
        fprintf(arq,"Escrita no Banco de Registradores\n");

        RegDst = 0;
        RegWrite = 1;
        MemtoReg = 1;
        state = 0;
    }
    else
        cout<<"opcode error"<<endl;
}
