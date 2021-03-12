#ifndef UCONTROL_H
#define UCONTROL_H
using namespace std;


class uControl
{
    public:
        uControl();
        ~uControl();
        void setOpcode(int op);
        void setSinalEtapa2();
        void setSinalEtapa3();
        void setSinalEtapa4();
        void setSinalEtapa5();

        int getALUSrcB(){ return ALUSrcB; };
        int getALUOp(){ return ALUOp; };
        int getPCSource(){ return PCSource; };
        bool getPCWriteCond(){ return PCWriteCond; };
        bool getPCWrite(){ return PCWrite; };
        bool getIorD(){ return IorD; };
        bool getMemRead(){ return MemRead; };
        bool getMemWrite(){ return MemWrite; };
        bool getMemtoRed(){ return MemtoReg; }; 
        bool getIRWrite(){ return IRWrite; };
        bool getALUSrcA(){ return ALUSrcA; };
        bool getRegwrite(){ return RegWrite; };
        bool getRegDst(){ return RegDst; };


    private:
        int opcode;
        int ALUSrcB, ALUOp, PCSource;
        bool PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoReg, IRWrite, ALUSrcA, RegWrite, RegDst;

       void resetSinal();
};

#endif // UCONTROL_H
