#include "Mips.h"

using namespace std;

unsigned int Mips::binToDec(string bin, int len)
{
    unsigned int dec = 0;

    for(int i=0; i<=len; i++)
            if(bin[i] == '1' )
                    dec = dec + pow(2, len-1-i) ;

    return dec;
}

Mips::Mips()
{
    cout<<"Mips iniciado"<<endl;
    tamInst = 0;

    for(int i=0; i<32; i++)
        Registers[i] = i;
}

Mips::~Mips()
{
    delete [] memoria;
}

void Mips::ALU(bool ALUSrcA, int ALUSrcB, int ALUOp)
{
    int a, b, aluresult;
    cout<<"ALU ok"<<endl;

    //Multiplexadores
    if(ALUSrcA)
        a = A;
    else
        a = pc;

    switch(ALUSrcB)
    {  
        case 0:
            b = B;
            break;
        case 1:
            b = 4;
            break;
        //case 2:
            //b =  
        //case 3:
        default:
            cout<<"error aluscrb"<<endl;
    }

    //ALUop
    switch(ALUOp)
    {
        case 0:
            aluresult = a+b;
            break;
        case 1:
            aluresult = a+b;
            break;
        //case 2:
        default:
            cout<<"error aluop"<<endl;
    }


    //ZeroALU
    //
    //
    //

    ALUout = aluresult;

}

void Mips::MultiplexPc(int result)
{

    switch(uc.getPCSource())
    {
        case 0:
            pc = result;
            break;
        //case 1:

        //case 2:
    }

}

void Mips::buscaReg(int rs, int rt)
{
    A = Registers[rs];
    B = Registers[rt];
}

void Mips::decodInstr(int instr)
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

    // operações
    uc.setOpcode(opcode.to_ulong());
    buscaReg(rs.to_ulong(), rt.to_ulong());

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

    etapa01();
    cout<<"pc: "<<pc<<endl;
    etapa02();

    //while(pc<tamInst)
    {
        //ciclo01();
        //ciclo02();
        //ciclo03();
        //ciclo04();
        //ciclo05();  
    }



}


void Mips::etapa01()
{
    cout<<"ciclo 01"<<endl;
    IR = memoria[pc];

    ALU(0, 1, 0);

    // gambiarra
    MultiplexPc(ALUout);
}



void Mips::etapa02()
{
    decodInstr(IR);
}

/*

void Mips::ciclo03()
{

}

void Mips::ciclo04()
{

}

void Mips::ciclo05()
{

}*/