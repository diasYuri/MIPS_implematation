#include "Mips.h"

using namespace std;


Mips::Mips()
{
    cout<<"Mips iniciado"<<endl;
    reset();

    arq = fopen("ArqGrav.txt", "wt");  // Cria um arquivo texto para gravação
    if (arq == NULL) // Se não conseguiu criar
    {
        printf("Problemas na CRIACAO do arquivo\n");
        return;
    }
}

Mips::~Mips()
{
    fclose(arq);
}

unsigned int Mips::binToDec(string bin, int len)
{
    unsigned int dec = 0;

    for(int i=0; i<=len; i++)
            if(bin[i] == '1' )
                    dec = dec + pow(2, len-1-i) ;

    return dec;
}

void Mips::reset()
{
    tamInst = 0;
    pc = 0;
    ciclo = 0;
    EspReservado = 64;

    for(int i=0; i<32; i++)
        Registers[i] = 0;
    //&sp
    Registers[29] = 256;
}

int Mips::controlALU()
{
    switch(uc.getALUOp())
    {
        case 0:
            return 2;
            break;
        case 1:
            return 6;
            break;
        case 2:
            // Desconsiderando o bit mais significativo do campo funct
            bitset<5> funct;
            funct = IR;
            cout<<"campo funct: "<<funct<<endl;

            switch(funct.to_ulong())
            {
                case 0:
                    return 2;
                    break;
                case 2:
                    return 6;
                    break;
                case 4:
                    return 0;
                    break;
                case 5:
                    return 1;
                    break;
                case 10:
                    return 7;
                    break;
                default:
                    cout<<"Error funct"<<endl;
            }
            break;
    }
    cout<<"Error alucontrol"<<endl;
    return 0;
} 


void Mips::ALU()
{
    int a, b, aluresult;


    //Multiplexadores
    if(uc.getALUSrcA())
        a = A;
    else
        a = pc;


    switch(uc.getALUSrcB())
    {  
        case 0:
            b = B;
            break;
        case 1:
            b = 1;
            break;
        case 2:
            b = SignExtension();
            break; 
        case 3:
            // Não é necessário fazer o shift left x2
            b = SignExtension();
            break;
        default:
            cout<<"error aluscrb"<<endl;
    }

    switch(controlALU())
    {
        case 2:
            aluresult = a+b;
            break;
        case 6:
            aluresult = a-b;
            if(aluresult == 0 && !uc.isBNE)
                zeroALU = true;
            else if(aluresult != 0 && uc.isBNE)
                zeroALU = true;
            else
                zeroALU = false;

            setPC(ALUout);
            break;
        case 0:
            //and
            aluresult = a & b;
            break;
        case 1:
            //or
            aluresult = a | b;
            break;
        case 7:
            //slt
            aluresult = (a<b) ? 1:0;
            break;
        default:
            cout<<"error alu"<<endl;
    }


    ALUout = aluresult;

}

int Mips::SignExtension()
{
    bitset<16> res = IR;
    bitset<32> ext;

    int convertido;
    if(res[15] == 1)
    {
        res = (~res);
        convertido = (res.to_ulong() + 1) * -1;
    }
    else
        convertido = res.to_ulong();


    return convertido;
}


void Mips::MemoryData()
{
    int add;

    // Multiplexador
    if(uc.getIorD())
        add = (ALUout/4)+EspReservado;
    else
        add = pc;
    ////////////////

    if(uc.getMemRead() && add<=256)
    {
        if(uc.getIRWrite())
            IR = memoria[add];
         MDR = memoria[add];
    }

    if(uc.getMemWrite())
    {
        if(add>=EspReservado && add<=256)
            memoria[add] = B;
        else if(add<EspReservado || add>256)
            cout<<"Error: local de memoria invalido"<<endl;
    }
}



void Mips::setPC(int result)
{

    if(uc.getPCWrite() || (uc.getPCWriteCond() &&  zeroALU))
    {
        switch(uc.getPCSource())
        {
            case 0:
                pc = result;
                break;
            case 1:
                pc = ALUout;
                break;
            case 2:
                pc = result;
                break;
        }
    }

}

void Mips::Reg()
{
    bitset<5> rs, rt, rd;

    rd = IR >> 11;
    rt = IR >> 16;
    rs = IR >> 21;


    if(uc.getRegwrite())
    {
        int store;

        if(uc.getMemtoReg())
            store = MDR;
        else
            store = ALUout;

        //cout<<"store: "<<ALUout<<endl;

        if(uc.getRegDst() && rd.to_ulong() != 0)
            Registers[rd.to_ulong()] = store;
        else if(rt.to_ulong() != 0)
            Registers[rt.to_ulong()] = store;
    }

    if(uc.getMemRead())
    {
        A = Registers[rs.to_ulong()];
        B = Registers[rt.to_ulong()];
    }
 

}

void Mips::Desvio()
{
    if(uc.getPCWrite())
    {
        bitset <32> pcSig = pc>>28;
        pcSig = pcSig<<28;

        bitset<26> j = IR;

        int result = pcSig.to_ulong() + j.to_ulong();

        if(uc.isJal)
            Registers[31] = pc+1;

        setPC(result);
    }
}

void Mips::decodInstr(int instr)
{
    bitset<32> binInstr;
    bitset<6> opcode;


    //opcode
    opcode = instr >> 26;

    // operações
    uc.setOpcode(opcode.to_ulong());
    Reg();

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
                    bin = result;
                    memoria[tamInst] = binToDec(bin, 32);
                    tamInst++;
                    if(tamInst>EspReservado)
                        EspReservado = tamInst;
                }
            i++;
        }


    fclose(arq);
}

void Mips::geraTxt()
{
    fprintf(arq,"$s0: %d\n", Registers[16]);
    fprintf(arq,"$s1: %d\n", Registers[17]);
    fprintf(arq,"$s2: %d\n", Registers[18]);
    fprintf(arq,"$s3: %d\n", Registers[19]);
    fprintf(arq,"$s4: %d\n", Registers[20]);
    fprintf(arq,"$s5: %d\n", Registers[21]);
    fprintf(arq,"$s6: %d\n", Registers[22]);
    fprintf(arq,"$s7: %d\n\n", Registers[23]);

    fprintf(arq,"$t0: %d\n", Registers[8]);
    fprintf(arq,"$t1: %d\n", Registers[9]);
    fprintf(arq,"$t2: %d\n", Registers[10]);
    fprintf(arq,"$t3: %d\n", Registers[11]);
    fprintf(arq,"$t4: %d\n", Registers[12]);
    fprintf(arq,"$t5: %d\n", Registers[13]);
    fprintf(arq,"$t6: %d\n", Registers[14]);
    fprintf(arq,"$t7: %d\n", Registers[15]);
    fprintf(arq,"$t8: %d\n", Registers[24]);
    fprintf(arq,"$t9: %d\n\n", Registers[25]);


    fprintf(arq,"Memoria de dados\n");
    for(int i=EspReservado; i<256; i++)
    {
        if(memoria[i] != 0)
            fprintf(arq,"Memoria[%d]: %d\n",i ,memoria[i]);
    }

}

void Mips::start(int tipo, int opcao, string nometxt)
{
    string s;
    if(tipo == 1)
        leTxt(nometxt);
    else if(tipo == 2)
    {
        memoria[tamInst] = binToDec(nometxt, 32);
        tamInst++;
    }
    
    
    
    while(pc<tamInst)
    {
        cout<<"----------- INSTRUCAO "<<pc+1<<" -----------"<<endl;
        fprintf(arq,"\n\n----------- INSTRUCAO %d -----------\n\n",pc+1);

        etapa01();
        cout<<endl;
        etapa02();
        cout<<endl;
        etapa03();
        cout<<endl;
        etapa04();
        cout<<endl;
        etapa05();  

        cout<<"Banco de Registradores"<<endl;
        fprintf(arq,"Banco de Registradores\n");

        cout<<"$s0: "<<Registers[16]<<endl;
        cout<<"$s1: "<<Registers[17]<<endl;
        cout<<"$s2: "<<Registers[18]<<endl;
        cout<<"$s3: "<<Registers[19]<<endl;
        cout<<"$s4: "<<Registers[20]<<endl;
        cout<<"$s5: "<<Registers[21]<<endl;
        cout<<"$s6: "<<Registers[22]<<endl;
        cout<<"$s7: "<<Registers[23]<<endl;
        cout<<endl;
        cout<<"$t0: "<<Registers[8]<<endl;
        cout<<"$t1: "<<Registers[9]<<endl;
        cout<<"$t2: "<<Registers[10]<<endl;
        cout<<"$t3: "<<Registers[11]<<endl;
        cout<<"$t4: "<<Registers[12]<<endl;
        cout<<"$t5: "<<Registers[13]<<endl;
        cout<<"$t6: "<<Registers[14]<<endl;
        cout<<"$t7: "<<Registers[15]<<endl;
        cout<<"$t8: "<<Registers[24]<<endl;
        cout<<"$t8: "<<Registers[25]<<endl;

        
        geraTxt();
        cout<<endl;
        

        if(opcao == 1)
        {
            cout<<"Aperte ENTER para continuar"<<endl;
            cout<<">> ";
            getline(cin, s);
        }
    }

}


void Mips::etapa01()
{
    uc.setSinalEtapa1();

    ciclo++;
    cout<<"Busca da instrucao"<<endl;
    cout<<"ciclo: "<<ciclo<<endl;
    cout<<"PC: "<<pc<<endl;

    fprintf(arq,"Busca da instrucao\n");
    fprintf(arq,"ciclo: %d\n", ciclo);
    fprintf(arq,"PC: %d\n\n\n", pc);

    
    MemoryData();
    ALU();
    setPC(ALUout);
}



void Mips::etapa02()
{
    uc.setSinalEtapa2();

    ciclo++;
    cout<<"Decodificação da instrução e busca dos registradores"<<endl;
    cout<<"ciclo: "<<ciclo<<endl;
    cout<<"PC: "<<pc<<endl;

    fprintf(arq,"Decodificação da instrução e busca dos registradores\n");
    fprintf(arq,"ciclo: %d\n", ciclo);
    fprintf(arq,"PC: %d\n\n\n", pc);
   
    decodInstr(IR);
    ALU();
}



void Mips::etapa03()
{
    if(uc.getState())
    {
        uc.setSinalEtapa3(arq);
        ciclo++;
        cout<<"ciclo: "<<ciclo<<endl;
        cout<<"PC: "<<pc<<endl;
        
        fprintf(arq,"ciclo: %d\n", ciclo);
        fprintf(arq,"PC: %d\n\n\n", pc);

        Desvio();
        ALU();
    }  
}



void Mips::etapa04()
{
    if(uc.getState())
    {
        uc.setSinalEtapa4(arq);
        ciclo++;
        cout<<"ciclo: "<<ciclo<<endl;
        cout<<"PC: "<<pc<<endl;
        
    
        fprintf(arq,"ciclo: %d\n", ciclo);
        fprintf(arq,"PC: %d\n\n\n", pc);

        if(uc.getRegwrite())
            Reg();
        
        if(uc.getMemWrite())
            MemoryData();
    }
}


void Mips::etapa05()
{
    if(uc.getState())
    {
        uc.setSinalEtapa5(arq);
        ciclo++;
        cout<<"ciclo: "<<ciclo<<endl;
        cout<<"PC: "<<pc<<endl;
        
        
        fprintf(arq,"ciclo: %d\n", ciclo);
        fprintf(arq,"PC: %d\n\n\n", pc);

        Reg();
    }
}