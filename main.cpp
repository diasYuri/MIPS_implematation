#include <iostream>
#include <bitset>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "uControl.h"
#include "Mips.h"

using namespace std;



int main()
{
    Mips mips;
    bool stop = 0;
    string opcao, nometxt, instr;
    int op;

    while(!stop)
    {
        cout<<endl;
        cout<<"Deseja inserir o código via arquivo.txt [aperte a] ou via linha de comando [aperte b]"<<endl;
        cout<<">> ";
        getline(cin, opcao);

        if(opcao == "a")
        {
            cout<<endl;
            cout<<"Digite o nome do arquivo sem a extensao: ";
            getline(cin, nometxt);

            cout<<endl;
            cout<<"Deseja executar passo a passo[1] ou direto[2]: ";
            getline(cin, opcao);
            if(opcao == "1")
                op = 1;
            else
                op = 2;


            mips.start(1, op, nometxt);
        }
        else if(opcao == "b")
        {
            cout<<endl;
            cout<<"Digite a instrucao"<<endl;
            cout<<">> ";
            getline(cin, instr);

            cout<<endl;
            cout<<"Deseja executar passo a passo[1] ou direto[2]: ";
            getline(cin, opcao);
            if(opcao == "1")
                op = 1;
            else
                op = 2;

            mips.start(2, op, instr);
        }
        else
        {
            cout<<endl;
            cout<<"opcao invalida"<<endl;
            exit(0);
        }

        cout<<endl;
        cout<<"Deseja resetar a maquina [s|n]?"<<endl;
        cout<<">> ";
        getline(cin, opcao);
        if(opcao == "s")
        {
            mips.reset();
        }
        else if(opcao != "n")
        {
            cout<<endl;
            cout<<"opcao invalida"<<endl;
            exit(0);
        }

        cout<<endl;
        cout<<"Deseja Finalizar [s|n]?"<<endl;
        cout<<">> ";
        getline(cin, opcao);
        if(opcao == "s")
        {
            stop = 1;
        }
    }

    return 0;
}
