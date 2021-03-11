#include "Mips.h"

using namespace std;

unsigned int Mips::binToDec(string bin, int len)
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


Mips::Mips()
{
    cout<<"Mips iniciado"<<endl;
    tamInst = 0;
}

Mips::~Mips()
{
    delete [] memoria;
}

void Mips::leTxt(string nometxt)
{
    // Leitura do arquivo externo
    FILE *arq;
    char linha[32];
    char *result;
    int i;
    string bin;

    nometxt += ".txt";
    const char * c = nometxt.c_str();

    // Abre um arquivo TEXTO para LEITURA
    arq = fopen(c, "r");

    if (arq == NULL)  // Se houve erro na abertura
        {
            printf("Problemas na abertura do arquivo\n");
            exit(0);
        }

    i = 0;
    while (!feof(arq))
        {
            //cout<<"i: "<<i<<endl;
            result = fgets(linha, 64, arq);
            if (result)
                {
                    //cout<<"resultado: "<<tamInst<<endl;
                    bin = result;
                    memoria[tamInst] = binToDec(bin, 32);
                    tamInst++;
                }
            i++;
        }

        for(int i=0; i<tamInst; i++)
        {
            cout<<memoria[i]<<endl;
        }



    fclose(arq);
}

void Mips::start()
{
    string nometxt;
    cout<<"Digite o nome do arquivo: ";
    getline(cin, nometxt);
    leTxt(nometxt);




    while(pc<tamInst)
    {

    }



}
