#ifndef MIPS_H
#define MIPS_H
#include <iostream>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "uControl.h"

using namespace std;

class Mips
{
    public:
        Mips();
        ~Mips();

        void start(int tipo, int opcao, string nometxt);
        void reset();


    private:
        unsigned int *memoria = new unsigned int [256];

        // Componente da memoria
        int tamInst;
        int EspReservado = 64;

        // program counter
        int pc = 0;
        int ciclo = 0;

        // Banco de registradores
        int Registers[32];

        // Unidade de controle
        uControl uc;

        //saida
        FILE *arq;

        //
        int A;
        int B;
        unsigned int IR;
        int ALUout;
        int MDR;
        bool zeroALU;


        void leTxt(string nometxt); 
        unsigned int binToDec(string bin, int len);
        void decodInstr(int instr);
        void ALU();
        void setPC(int result);
        void Reg();
        int SignExtension();
        void MemoryData();
        int controlALU();
        void Desvio();
        void geraTxt();

        void etapa01();
        void etapa02();
        void etapa03();
        void etapa04();
        void etapa05();


};

#endif // MIPS_H
