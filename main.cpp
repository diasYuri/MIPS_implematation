#include <iostream>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "uControl.h"
#include "Mips.h"

using namespace std;



unsigned int binToDec(string bin, int len=32)
{
    unsigned int dec = 0;


    for(int i=0; i<=len; i++)
        {
            if(bin[i] == '1' )
                {
                    dec = dec + pow(2, len-1-i) ;
                }

        }

    return dec;
}

int leTxt(unsigned int *memoria)
{
    // Leitura do arquivo externo
    FILE *arq;
    char linha[32];
    char *result;
    int i;
    string bin;
    int tamMemoria = 0;


    // Abre um arquivo TEXTO para LEITURA
    arq = fopen("test.txt", "r");

    if (arq == NULL)  // Se houve erro na abertura
        {
            printf("Problemas na abertura do arquivo\n");
        }

    i = 0;
    while (!feof(arq))
        {
            //cout<<"i: "<<i<<endl;
            result = fgets(linha, 64, arq);
            if (result)
                {
                    //cout<<"resultado: "<<i<<endl;
                    bin = result;
                    memoria[tamMemoria] = binToDec(bin);
                    tamMemoria++;
                }
            i++;
        }

    for(int i=0; i<tamMemoria; i++)
        {
            //cout<<memoria[i]<<endl;
        }

    fclose(arq);

    return tamMemoria;
}

void alu(int a1, int a2, int alucontrol)
{
    // Converter immediate value
    bitset<16> res;
    res = -6 ;
    int convertido;
    if(res[15] == 1)
    {
        res = (~res);
        convertido = (res.to_ulong() + 1) * -1;
        cout<<convertido<<endl;
    }
    else
        convertido = res.to_ulong();

    //test
    /*
    binInstr = instr;
    unsigned int test = binInstr.to_ulong();

    int op = abs(instr >> 26);
    cout<<test<<endl;
    */
    //fim do test
}

void Control(int opcode)
{
    cout<<opcode<<endl;
    switch(opcode)
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

void decodInstr(int instr = 2149231339)
{
    bitset<32> binInstr;
    bitset<26> address;
    bitset<16> immediate;
    bitset<6> opcode, funct;
    bitset<5> rs, rt, rd, shamt;

    //binInstr = instr;
    //cout<<binInstr<<endl;
    // 1000 0000 0001 1010 1010 1010 1110 1011

    address = instr;
    immediate = instr;
    funct = instr;
    shamt = instr >> 6;
    rd = instr >> 11;
    rt = instr >> 16;
    rs = instr >> 21;

    //opcode
    opcode = instr >> 26;
    Control(opcode.to_ulong());

    /*cout<<opcode;
    cout<<rs;
    cout<<rt;
    cout<<rd;
    cout<<shamt;
    cout<<funct<<endl;*/




}

void executaInstr(int instr)
{
    decodInstr(instr);
}


int main()
{
    /*// Componente da memoria
    unsigned int memoria[256];
    int tamInst = leTxt(memoria);

    // program counter
    int pc = 0;

    // Banco de registradores
    int Registers[32];

    // Unidade de controle
    uControl *uc = new uControl();

    while(pc<2)
    {
        int ir = memoria[pc];
        pc = pc + 4/4;

        executaInstr(ir);
    }*/


    Mips test;
    test.start();


    return 0;
}
