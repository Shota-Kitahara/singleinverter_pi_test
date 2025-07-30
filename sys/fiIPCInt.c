//###########################################################################
//
// FILE:  fiIPUInt.c
//
// TITLE: interrupt IPC program for PE Scouter
//
//###########################################################################
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/



#include "fiIPCInt.h"


volatile tIpcController g_sIpcController1;
volatile tIpcController g_sIpcController2;

u4 	*pulMsgRam;
u4	u4_Trace_freq;
u4	u4_Sci_spped;
u4  u4_RsetCnt;

s4	s4_IPCCounter=0;

// ***Add a function for PEScouter***
__interrupt void CPU02toCPU01IPC0IntHandler(void)
{
	fiIPCInt();

    IpcRegs.IPCACK.bit.IPC0 = 1;
    if(IpcRegs.IPCSTS.bit.IPC18 == 1){
        IpcRegs.IPCACK.bit.IPC18 = 1;
    }
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

void fiIPCInt(){
    tIpcMessage sMessage = {0,0,0,0};
    // Continue processing messages as long as CPU02toCPU01 GetBuffer1 is full
    while(IpcGet(&g_sIpcController1, &sMessage,DISABLE_BLOCKING)!= STATUS_FAIL){
        switch (sMessage.ulcommand){
        case IPC_DATA_WRITE:
            IPCRtoLDataWrite(&sMessage);
            break;
        case IPC_DATA_READ:
            IPCRtoLDataRead(&g_sIpcController1, &sMessage,ENABLE_BLOCKING);
            break;
        case IPC_DATA_WRITE_PROTECTED:
            IPCRtoLDataWrite_Protected(&sMessage);
            break;
        default:
            break;
        }
    }
    s4_IPCCounter++;
}

void fiIPCIntInit(){
    IPCInitialize(&g_sIpcController1, IPC_INT0, IPC_INT0);
    IPCInitialize(&g_sIpcController2, IPC_INT1, IPC_INT1);

    u4_Trace_freq  = TRACE_FRQ;
    u4_Sci_spped = FREQUENCY_SCI;
    u4_RsetCnt = RSET_CNT;

    pulMsgRam =(void *) CPU02TOCPU01_PASSMSG;
}

void IPC_config(){
	//CPU2使用するGPIO
    EALLOW;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS10 = 1;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS11 = 1;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS12 = 1;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS13 = 1;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS14 = 1;
    MemCfgRegs.GSxMSEL.bit.MSEL_GS15 = 1;
    DevCfgRegs.CPUSEL5.bit.SCI_A = 1;
    DevCfgRegs.CPUSEL5.bit.SCI_B = 1;
    DevCfgRegs.CPUSEL5.bit.SCI_D = 1;
    EDIS;

    // Enable interrupt IPC_INT0
    IER |= M_INT1;
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;   	// Enable IPC CPU1 to CPU2 INT0
}

void fiIPCSend(){

    IPCLtoRDataWrite(&g_sIpcController2, pulMsgRam[0],u4_Trace_freq,
                     IPC_LENGTH_32_BITS, DISABLE_BLOCKING, NO_FLAG);

    IPCLtoRDataWrite(&g_sIpcController2, pulMsgRam[1],u4_Sci_spped,
                     IPC_LENGTH_32_BITS, DISABLE_BLOCKING, NO_FLAG);

    IPCLtoRDataWrite(&g_sIpcController2, pulMsgRam[2],u4_RsetCnt,
                     IPC_LENGTH_32_BITS, DISABLE_BLOCKING, NO_FLAG);
    IpcRegs.IPCSET.bit.IPC17 = 1;                   // IPC of CPU2 start flag

}

void fiIPCtimer(void){
    IpcRegs.IPCSET.bit.IPC17 = 1;                   // IPC of timer flag
}
