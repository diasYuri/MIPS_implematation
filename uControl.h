#ifndef UCONTROL_H
#define UCONTROL_H


class uControl
{
    public:
        uControl();
        ~uControl();
        void setOpcode(int op){ opcode = op; };
        bool getPCWriteCond(){ return PCWriteCond; };

    private:
        int opcode;
        int ALUSrcB, ALUOp, PCSource;
        bool PCWriteCond, PCWrite, IorD, MemRead, MemWrite, MemtoRed, IRWrite, ALUSrcA, RegWrite, RegDst;

};

#endif // UCONTROL_H
