//###########################################################################
//
// FILE:   K17100_dacFunction.c
//
// TITLE: DAC function to use k17100 board
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/

#include "K17100_dacFunction.h"

void N_ConfigDACABC(u4 base){
    DAC_setReferenceVoltage(base, DAC_REF_VDAC);
    DAC_setLoadMode(base, DAC_LOAD_SYSCLK);
    DAC_enableOutput(base);
    DAC_tuneOffsetTrim(base,3.0f);
}

void N_ConfigDACSPI (void){
    // SPIa
    SpiaRegs.SPIFFTX.all = 0xE040;
    SpiaRegs.SPIFFRX.all = 0x2044;
    SpiaRegs.SPIFFCT.all = 0x0;

    // Reference code of F2837xD_Spi.c
    SpiaRegs.SPICCR.bit.SPISWRESET = 0;      // Set reset low before configuration changes
    SpiaRegs.SPICCR.bit.CLKPOLARITY = 0;     // Clock polarity (0 == rising, 1 == falling)
    SpiaRegs.SPICCR.bit.SPICHAR = (8-1);     // 8-bit character
    SpiaRegs.SPICCR.bit.SPILBK = 1;          // Enable loop-back
    SpiaRegs.SPICTL.bit.MASTER_SLAVE = 1;    // Enable master (0 == slave, 1 == master)
    SpiaRegs.SPICTL.bit.TALK = 1;            // Enable transmission (Talk)
    SpiaRegs.SPICTL.bit.CLK_PHASE = 1;       // Clock phase (0 == normal, 1 == delayed)
    SpiaRegs.SPICTL.bit.SPIINTENA = 0;       // SPI interrupts are disabled
    // Set the baud rate
    SpiaRegs.SPIBRR.bit.SPI_BIT_RATE = ((200E6 / 4) / 500E3) - 1;   //500 kHz
    // Set FREE bit
    // Halting on a breakpoint will not halt the SPI
    SpiaRegs.SPIPRI.bit.FREE = 1;
    // Release the SPI from reset
    SpiaRegs.SPICCR.bit.SPISWRESET = 1;

    // scale range is 0V to 5V
    SpiaRegs.SPITXBUF = 0xE000; //
    SpiaRegs.SPITXBUF = 0x0000; //
    SpiaRegs.SPITXBUF = 0x0000; //
    DEVICE_DELAY_US(100);
}
