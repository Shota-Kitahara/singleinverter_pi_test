//###########################################################################
//
// FILE:   configuration.c
//
// TITLE: configuration f28379d device
//
//###########################################################################
// $TI Release: K17100 Base program ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/



#include "Configuration.h"


//
// configCPUTimer - This function initializes the selected timer to the
// period specified by the "freq" and "period" parameters. The "freq" is
// entered as Hz and the period in uSeconds. The timer is held in the stopped
// state after configuration.
//
void configCPUTimer(uint32_t cpuTimer, float freq, float period){
    uint32_t temp;
    f4  f4_cast;

    f4_cast = freq / 1000000.0f * period;
    temp = (uint32_t)f4_cast;
    //temp = (uint32_t)(freq / 1000000 * period);     // Initialize timer period:
    CPUTimer_setPeriod(cpuTimer, temp);
    CPUTimer_setPreScaler(cpuTimer, 0);             // Set pre-scale counter to divide by 1 (SYSCLKOUT):
    // Initializes timer control register. The timer is stopped, reloaded,
    // free run disabled, and interrupt enabled.
    // Additionally, the free and soft bits are set
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
    CPUTimer_startTimer(cpuTimer);
}

void configGPIO(void)
{
    u4 pin;
    // set EPWM pin
    GPIO_setPinConfig(GPIO_0_EPWM1A);              // GPIO1 = PWM1A
    GPIO_setPinConfig(GPIO_1_EPWM1B);              // GPIO1 = PWM1B
    GPIO_setPinConfig(GPIO_2_EPWM2A);              // GPIO2 = PWM2A
    GPIO_setPinConfig(GPIO_3_EPWM2B);              // GPIO3 = PWM2B
    GPIO_setPinConfig(GPIO_4_EPWM3A);              // GPIO4 = PWM3A
    GPIO_setPinConfig(GPIO_5_EPWM3B);              // GPIO5 = PWM3B
    GPIO_setPinConfig(GPIO_6_EPWM4A);              // GPIO6 = PWM4A
    GPIO_setPinConfig(GPIO_7_EPWM4B);              // GPIO7 = PWM4B
    GPIO_setPinConfig(GPIO_8_EPWM5A);              // GPIO8 = PWM5A
    //    GPIO_setPinConfig(GPIO_8_ADCSOCAO);              // GPIO8 = ADCSOCA
    //    SysCtl_enableExtADCSOCSource(SYSCTL_ADCSOC_SRC_PWM1SOCA);
    GPIO_setPinConfig(GPIO_9_EPWM5B);              // GPIO9 = PWM5B
    GPIO_setPinConfig(GPIO_10_EPWM6A);             // GPIO10 = PWM6A
    GPIO_setPinConfig(GPIO_11_EPWM6B);             // GPIO11 = PWM6B
    GPIO_setPinConfig(GPIO_12_EPWM7A);             // GPIO12 = PWM7A
    GPIO_setPinConfig(GPIO_13_EPWM7B);             // GPIO13 = PWM7B
    GPIO_setPinConfig(GPIO_14_EPWM8A);             // GPIO14 = PWM8A
    GPIO_setPinConfig(GPIO_15_EPWM8B);             // GPIO15 = PWM8B
    GPIO_setPinConfig(GPIO_16_EPWM9A);             // GPIO16 = PWM9A
    GPIO_setPinConfig(GPIO_17_EPWM9B);             // GPIO17 = PWM9B
    GPIO_setPinConfig(GPIO_18_EPWM10A);            // GPIO18 = PWM10A
    GPIO_setPinConfig(GPIO_19_EPWM10B);            // GPIO19 = PWM10B
    GPIO_setPinConfig(GPIO_20_EPWM11A);            // GPIO20 = PWM11A
    GPIO_setPinConfig(GPIO_21_EPWM11B);            // GPIO21 = PWM11B
    GPIO_setPinConfig(GPIO_22_EPWM12A);            // GPIO22 = PWM12A
    GPIO_setPinConfig(GPIO_23_EPWM12B);            // GPIO23 = PWM12B
    // Enable SPI-B on GPIO24 - GPIO27
    GPIO_setPinConfig(GPIO_24_SPISIMOB);            // GPIO24 = SPISIMOB
    GPIO_setPinConfig(GPIO_25_SPISOMIB);            // GPIO25 = SPISOMIB
    GPIO_setPinConfig(GPIO_26_SPICLKB);             // GPIO26 = SPICLK
    GPIO_setPinConfig(GPIO_27_SPISTEB);             // GPIO27 = SPISTEB
    GPIO_setPadConfig(24, GPIO_PIN_TYPE_PULLUP);    // Pullup on GPIO24 (SPISIMOB)
    GPIO_setPadConfig(25, GPIO_PIN_TYPE_PULLUP);    // Pullup on GPIO25 (SPISOMIB)
    GPIO_setPadConfig(26, GPIO_PIN_TYPE_PULLUP);    // Pullup on GPIO22 (SPICLKB)
    GPIO_setPadConfig(27, GPIO_PIN_TYPE_PULLUP);    // Pullup on GPIO27 (SPISTEB)
    GPIO_setQualificationMode(24, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(25, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(26, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(27, GPIO_QUAL_ASYNC); // asynch input
    // Enable SCI-A on GPIO28 - GPIO29
    GPIO_setPinConfig(GPIO_28_SCIRXDA);             // GPIO28 = SCIRXDA
    GPIO_setPinConfig(GPIO_29_SCITXDA);             // GPIO29 = SCITXDA
    GPIO_setPadConfig(28, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO28
    GPIO_setPadConfig(29, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO29
    GPIO_setQualificationMode(28, GPIO_QUAL_ASYNC); // asynch input
    // OP1
    GPIO_setPinConfig(GPIO_30_GPIO30);               // GPIO30 = GPIO30
    GPIO_setDirectionMode(30, GPIO_DIR_MODE_IN);     // GPIO30 = input
    GPIO_setPadConfig(30, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO30
    GPIO_setQualificationMode(30, GPIO_QUAL_6SAMPLE);// 6 samples
    // LD2
    GPIO_setPinConfig(GPIO_31_GPIO31);               // GPIO31 = LD1
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);    // GPIO31 = output
    GPIO_writePin(31, 0);                            // output low (LED ON)
    // Enable I2C-A on GPIO32 - GPIO33
    GPIO_setPinConfig(GPIO_32_SDAA);                 // GPIO32 = SDAA
    GPIO_setPinConfig(GPIO_33_SCLA);                 // GPIO33 = SCLA
    GPIO_setPadConfig(32, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO32
    GPIO_setPadConfig(33, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO33
    GPIO_setQualificationMode(32, GPIO_QUAL_ASYNC);  // asynch input
    GPIO_setQualificationMode(33, GPIO_QUAL_ASYNC);  // asynch input
    // LD3
    GPIO_setPinConfig(GPIO_34_GPIO34);               // GPIO34 = LD3
    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);    // GPIO34 = output
    GPIO_writePin(34, 0);                            // output low (LED ON)
    // DNC
    for (pin = 35; pin <= 38; pin++){
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
        GPIO_writePin(pin, 0);                            // output low
    }
    // INPUT Qualification GPIO40 - GPIO47
    //    GPIO_setQualificationPeriod(40, 4);              // Qual period=SYSCLKOUT/4
    // OP2 - OP4
    GPIO_setPinConfig(GPIO_39_GPIO39);               // GPIO39 = OP2
    GPIO_setPinConfig(GPIO_40_GPIO40);               // GPIO40 = OP3
    GPIO_setPinConfig(GPIO_41_GPIO41);               // GPIO41 = OP4
    GPIO_setDirectionMode(39, GPIO_DIR_MODE_IN);     // GPIO39 = input
    GPIO_setDirectionMode(40, GPIO_DIR_MODE_IN);     // GPIO40 = input
    GPIO_setDirectionMode(41, GPIO_DIR_MODE_IN);     // GPIO41 = input
    GPIO_setPadConfig(39, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO39
    GPIO_setPadConfig(40, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO40
    GPIO_setPadConfig(41, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO41
    GPIO_setQualificationMode(39, GPIO_QUAL_6SAMPLE);// 6 samples
    GPIO_setQualificationMode(40, GPIO_QUAL_6SAMPLE);// 6 samples
    GPIO_setQualificationMode(41, GPIO_QUAL_6SAMPLE);// 6 samples
    // DIN1 - DIN2
    GPIO_setPinConfig(GPIO_42_GPIO42);               // GPIO42 = GPIO42
    GPIO_setPinConfig(GPIO_43_GPIO43);               // GPIO43 = GPIO43
    GPIO_setDirectionMode(42, GPIO_DIR_MODE_IN);     // GPIO42 = input
    GPIO_setDirectionMode(43, GPIO_DIR_MODE_IN);     // GPIO43 = input
    GPIO_setPadConfig(42, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO42
    GPIO_setPadConfig(43, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO43
    // OP5 - OP8
    GPIO_setPinConfig(GPIO_44_GPIO44);               // GPIO44 = OP5
    GPIO_setPinConfig(GPIO_45_GPIO45);               // GPIO45 = OP6
    GPIO_setPinConfig(GPIO_46_GPIO46);               // GPIO46 = OP7
    GPIO_setPinConfig(GPIO_47_GPIO47);               // GPIO47 = OP8
    GPIO_setDirectionMode(44, GPIO_DIR_MODE_IN);     // GPIO44 = input
    GPIO_setDirectionMode(45, GPIO_DIR_MODE_IN);     // GPIO45 = input
    GPIO_setDirectionMode(46, GPIO_DIR_MODE_IN);     // GPIO46 = input
    GPIO_setDirectionMode(47, GPIO_DIR_MODE_IN);     // GPIO47 = input
    GPIO_setPadConfig(44, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO44
    GPIO_setPadConfig(45, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO45
    GPIO_setPadConfig(46, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO46
    GPIO_setPadConfig(47, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO47
    GPIO_setQualificationMode(44, GPIO_QUAL_6SAMPLE);// 6 samples
    GPIO_setQualificationMode(45, GPIO_QUAL_6SAMPLE);// 6 samples
    GPIO_setQualificationMode(46, GPIO_QUAL_6SAMPLE);// 6 samples
    GPIO_setQualificationMode(47, GPIO_QUAL_6SAMPLE);// 6 samples
    // DIN3 - DIN5
    GPIO_setPinConfig(GPIO_48_GPIO48);               // GPIO48 = GPIO48
    GPIO_setPinConfig(GPIO_49_GPIO49);               // GPIO49 = GPIO49
    GPIO_setPinConfig(GPIO_50_GPIO50);               // GPIO50 = GPIO50
    GPIO_setDirectionMode(48, GPIO_DIR_MODE_IN);     // GPIO48 = input
    GPIO_setDirectionMode(49, GPIO_DIR_MODE_IN);     // GPIO49 = input
    GPIO_setDirectionMode(50, GPIO_DIR_MODE_IN);     // GPIO50 = input
    GPIO_setPadConfig(48, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO48
    GPIO_setPadConfig(49, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO49
    GPIO_setPadConfig(50, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO50
    // DOUT1 - DOUT3
    GPIO_setPinConfig(GPIO_51_GPIO51);               // GPIO51 = DOUT1
    GPIO_setPinConfig(GPIO_52_GPIO52);               // GPIO52 = DOUT2
    GPIO_setPinConfig(GPIO_53_GPIO53);               // GPIO53 = DOUT3
    GPIO_setDirectionMode(51, GPIO_DIR_MODE_OUT);    // GPIO51 = output
    GPIO_setDirectionMode(52, GPIO_DIR_MODE_OUT);    // GPIO52 = output
    GPIO_setDirectionMode(53, GPIO_DIR_MODE_OUT);    // GPIO53 = output
    GPIO_writePin(51, 0);                            // output low
    GPIO_writePin(52, 0);                            // output low
    GPIO_writePin(53, 0);                            // output low
    // DIN6 - DIN8
    GPIO_setPinConfig(GPIO_54_GPIO54);               // GPIO54 = DIN6
    GPIO_setPinConfig(GPIO_55_GPIO55);               // GPIO55 = DIN7
    GPIO_setPinConfig(GPIO_56_GPIO56);               // GPIO56 = DIN8
    GPIO_setDirectionMode(54, GPIO_DIR_MODE_IN);     // GPIO54 = input
    GPIO_setDirectionMode(55, GPIO_DIR_MODE_IN);     // GPIO55 = input
    GPIO_setDirectionMode(56, GPIO_DIR_MODE_IN);     // GPIO56 = input
    GPIO_setPadConfig(54, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO54
    GPIO_setPadConfig(55, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO55
    GPIO_setPadConfig(56, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO56
    // DOUT4
    GPIO_setPinConfig(GPIO_57_GPIO57);               // GPIO57 = DOUT4
    GPIO_setDirectionMode(57, GPIO_DIR_MODE_OUT);    // GPIO57 = output
    GPIO_writePin(57, 0);                            // output low
    // Enable SPI-A on GPIO58 - GPIO61
    GPIO_setPinConfig(GPIO_58_SPISIMOA);            // GPIO58 = SPISIMOA
    GPIO_setPinConfig(GPIO_59_SPISOMIA);            // GPIO59 = SPIS0MIA
    GPIO_setPinConfig(GPIO_60_SPICLKA);             // GPIO60 = SPICLKA
    GPIO_setPinConfig(GPIO_61_SPISTEA);             // GPIO61 = SPISTEA
    GPIO_setPadConfig(58, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO58 (SPISIMOA)
    GPIO_setPadConfig(59, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO59 (SPIS0MIA)
    GPIO_setPadConfig(60, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO60 (SPICLKA)
    GPIO_setPadConfig(61, GPIO_PIN_TYPE_PULLUP); // Pullup on GPIO61 (SPISTEA)
    GPIO_setQualificationMode(58, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(59, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(60, GPIO_QUAL_ASYNC); // asynch input
    GPIO_setQualificationMode(61, GPIO_QUAL_ASYNC); // asynch input
    // Enable CAN-A on GPIO62 - GPIO63
    GPIO_setPinConfig(GPIO_62_CANRXA);               // GPIO62 = CANRXA
    GPIO_setPinConfig(GPIO_63_CANTXA);               // GPIO63 = CANTXA
    GPIO_setPadConfig(62, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO62
    GPIO_setPadConfig(63, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO63
    GPIO_setQualificationMode(62, GPIO_QUAL_ASYNC);  // asynch input
    // DOUT9 - DOUT12
    GPIO_setPinConfig(GPIO_64_GPIO64);               // GPIO64 = DOUT9
    GPIO_setPinConfig(GPIO_65_GPIO65);               // GPIO65 = DOUT10
    GPIO_setPinConfig(GPIO_66_GPIO66);               // GPIO66 = DOUT11
    GPIO_setPinConfig(GPIO_67_GPIO67);               // GPIO67 = DOUT12
    GPIO_setDirectionMode(64, GPIO_DIR_MODE_OUT);    // GPIO64 = output
    GPIO_setDirectionMode(65, GPIO_DIR_MODE_OUT);    // GPIO65 = output
    GPIO_setDirectionMode(66, GPIO_DIR_MODE_OUT);    // GPIO66 = output
    GPIO_setDirectionMode(67, GPIO_DIR_MODE_OUT);    // GPIO67 = output
    GPIO_writePin(64, 0);                            // output low
    GPIO_writePin(65, 0);                            // output low
    GPIO_writePin(66, 0);                            // output low
    GPIO_writePin(67, 0);                            // output low
    // CPOP3 - CPOP4
    GPIO_setPinConfig(GPIO_68_GPIO68);               // GPIO68 = CPOP3
    GPIO_setPinConfig(GPIO_69_GPIO69);               // GPIO69 = CPOP4
    GPIO_setDirectionMode(68, GPIO_DIR_MODE_IN);     // GPIO68 = input
    GPIO_setDirectionMode(69, GPIO_DIR_MODE_IN);     // GPIO69 = input
    GPIO_setPadConfig(68, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO68
    GPIO_setPadConfig(69, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO69
    // Enable SCI-B on GPIO70 - GPIO71
    GPIO_setPinConfig(GPIO_70_SCITXDB);             // GPIO70 = SCITXDB
    GPIO_setPinConfig(GPIO_71_SCIRXDB);             // GPIO71 = SCIRXDB
    GPIO_setPadConfig(70, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO70
    GPIO_setPadConfig(71, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO71
    GPIO_setQualificationMode(71, GPIO_QUAL_ASYNC); // asynch input
    // Enable CAN-B on GPIO72 - GPIO73
    GPIO_setPinConfig(GPIO_72_CANTXB);               // GPIO72 = CANTXB
    GPIO_setPinConfig(GPIO_73_CANRXB);               // GPIO73 = CANRXB
    GPIO_setPadConfig(72, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO72
    GPIO_setPadConfig(73, GPIO_PIN_TYPE_PULLUP);     // Enable pullup on GPIO73
    GPIO_setQualificationMode(73, GPIO_QUAL_ASYNC);  // asynch input
    // LED1 - LE4
    GPIO_setPinConfig(GPIO_74_GPIO74);               // GPIO74 = LED1
    GPIO_setPinConfig(GPIO_75_GPIO75);               // GPIO75 = LED2
    GPIO_setPinConfig(GPIO_76_GPIO76);               // GPIO76 = LED3
    GPIO_setPinConfig(GPIO_77_GPIO77);               // GPIO77 = LED4
    GPIO_setDirectionMode(74, GPIO_DIR_MODE_OUT);    // GPIO74 = output
    GPIO_setDirectionMode(75, GPIO_DIR_MODE_OUT);    // GPIO75 = output
    GPIO_setDirectionMode(76, GPIO_DIR_MODE_OUT);    // GPIO76 = output
    GPIO_setDirectionMode(77, GPIO_DIR_MODE_OUT);    // GPIO77 = output
    GPIO_writePin(74, 0);                            // output low  (LED ON)
    GPIO_writePin(75, 0);                            // output low  (LED ON)
    GPIO_writePin(76, 0);                            // output low  (LED ON)
    GPIO_writePin(77, 0);                            // output low  (LED ON)
    // Enable EQEP2 on GPIO78 - GPIO 83
    GPIO_setPinConfig(GPIO_78_EQEP2A);              // GPIO78 = EQEP2A
    GPIO_setPinConfig(GPIO_79_EQEP2B);              // GPIO79 = EQEP2B
    GPIO_setPinConfig(GPIO_80_EQEP2S);              // GPIO80 = EQEP2S
    GPIO_setPinConfig(GPIO_81_EQEP2I);              // GPIO81 = EQEP2I
    GPIO_setPadConfig(78, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO78
    GPIO_setPadConfig(79, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO79
    GPIO_setPadConfig(80, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO80
    GPIO_setPadConfig(81, GPIO_PIN_TYPE_PULLUP);    // Enable pullup on GPIO81
    GPIO_setQualificationMode(78, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(79, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(80, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    GPIO_setQualificationMode(81, GPIO_QUAL_SYNC);  // Synch to SYSCLKOUT
    // DOUT5 - DOUT8
    GPIO_setPinConfig(GPIO_84_GPIO84);               // GPIO84 = DOUT5
    GPIO_setPinConfig(GPIO_85_GPIO85);               // GPIO85 = DOUT6
    GPIO_setPinConfig(GPIO_86_GPIO86);               // GPIO86 = DOUT7
    GPIO_setPinConfig(GPIO_87_GPIO87);               // GPIO87 = DOUT8
    GPIO_setDirectionMode(84, GPIO_DIR_MODE_OUT);    // GPIO84 = output
    GPIO_setDirectionMode(85, GPIO_DIR_MODE_OUT);    // GPIO85 = output
    GPIO_setDirectionMode(86, GPIO_DIR_MODE_OUT);    // GPIO86 = output
    GPIO_setDirectionMode(87, GPIO_DIR_MODE_OUT);    // GPIO87 = output
    GPIO_writePin(84, 0);                            // output low
    GPIO_writePin(85, 0);                            // output low
    GPIO_writePin(86, 0);                            // output low
    GPIO_writePin(87, 0);                            // output low
    // DNC
    for (pin = 88; pin <= 92; pin++){
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
        GPIO_writePin(pin, 0);                        // output low
    }
    // Enable SCI-D on GPIO93 - GPIO94
    GPIO_setPinConfig(GPIO_93_SCITXDD);               // GPIO93 = SCITXDD
    GPIO_setPinConfig(GPIO_94_SCIRXDD);               // GPIO94 = SCIRXDD
    GPIO_setPadConfig(93, GPIO_PIN_TYPE_PULLUP);      // Enable pullup on GPIO93
    GPIO_setPadConfig(94, GPIO_PIN_TYPE_PULLUP);      // Enable pullup on GPIO94
    GPIO_setQualificationMode(94, GPIO_QUAL_ASYNC);   // asynch input
    // DNC
    for (pin = 95; pin <= 168; pin++){
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);
        GPIO_writePin(pin, 0);                        // output low
    }
}

void configADC(void)
{
    u4 acqps_12,acqps_16;
    acqps_12 = 15; //75nsec
    acqps_16 = 64; //320nsec

    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);   // Set ADCCLK divider to /4
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setInterruptPulseMode(ADCA_BASE, ADC_PULSE_END_OF_CONV); // Set pulse positions to late
    ADC_enableConverter(ADCA_BASE); //power up the ADC

    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);   // Set ADCCLK divider to /4
    ADC_setMode(ADCB_BASE, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);
    ADC_setInterruptPulseMode(ADCB_BASE, ADC_PULSE_END_OF_CONV); // Set pulse positions to late
    ADC_enableConverter(ADCB_BASE); //power up the ADC

    ADC_setPrescaler(ADCC_BASE, ADC_CLK_DIV_4_0);   // Set ADCCLK divider to /4
    ADC_setMode(ADCC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setInterruptPulseMode(ADCC_BASE, ADC_PULSE_END_OF_CONV); // Set pulse positions to late
    ADC_enableConverter(ADCC_BASE); //power up the ADC

    ADC_setPrescaler(ADCD_BASE, ADC_CLK_DIV_4_0);   // Set ADCCLK divider to /4
    ADC_setMode(ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);
    ADC_setInterruptPulseMode(ADCD_BASE, ADC_PULSE_END_OF_CONV); // Set pulse positions to late
    ADC_enableConverter(ADCD_BASE); //power up the ADC

    ASysCtl_enableTemperatureSensor();

    DEVICE_DELAY_US(1000);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN2, acqps_12);     // CT1
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN14, acqps_12);    // VT1
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN4, acqps_12);     // CT4
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN5, acqps_12);     // VT4
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN3, acqps_12);     // TH2
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN13, 140);   // TemperatureSensor

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN2, acqps_16);     // VT6

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN2, acqps_12);     // CT2
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN3, acqps_12);     // VT2
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN4, acqps_12);     // CT5
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN15, acqps_12);    // TH3
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN5, acqps_12);     // TH4

    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN0, acqps_12);     // CT3
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN1, acqps_12);     // VT3
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN2, acqps_12);     // CT6
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN3, acqps_12);     // VT5
    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER4, ADC_TRIGGER_EPWM1_SOCA,ADC_CH_ADCIN4, acqps_12);     // TH1

    ADC_setInterruptSource(ADCA_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER3);
    ADC_enableInterrupt(ADCA_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
}

void configEPWM(void)
{
    SysCtl_setEPWMClockDivider(SYSCTL_EPWMCLK_DIV_1);

    N_ConfigSTDInverterEPWMs(EPWM1_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM2_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM3_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM4_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM5_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM6_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM7_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM8_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM9_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM10_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM11_BASE, DSP_CAPK, DSP_DEADT);
    N_ConfigSTDInverterEPWMs(EPWM12_BASE, DSP_CAPK, DSP_DEADT);

    //Event-Trigger Submodule Registers
    EPWM_setADCTriggerSource(EPWM1_BASE, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO);
    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
    // 間引き
    EPWM_setADCTriggerEventPrescale(EPWM1_BASE, EPWM_SOC_A, INT_COUNT);
}




