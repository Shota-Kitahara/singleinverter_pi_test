//###########################################################################
//
// FILE:   NLibrary.c
//
// TITLE: NPE library
//
//###########################################################################
// $TI Release: NPE Library ver.1.0 $
// $Release Date: Thu July 21 2020  $
// $Copyright:
// Copyright (C) 2020 Nagaoka Power Electronics Co., Ltd. http://www.npe.co.jp/


#ifndef NLIBRARY_H_
#define NLIBRARY_H_

// 変数の型名定義
typedef     unsigned char   u1;                             // 符号無16ビットデータ (C28 compiler)
typedef     signed   char   s1;                             // 符号付16ビットデータ (C28 compiler)
typedef     unsigned short  u2;                             // 符号無16ビットデータ
typedef     signed   short  s2;                             // 符号付16ビットデータ
typedef     unsigned long   u4;                             // 符号無32ビットデータ
typedef     signed   long   s4;                             // 符号付32ビットデータ
typedef              float  f4;                             // 単精度(32ビット)浮動小数点データ

// 関数
#define DEG360 0x3ff
#define LIMIT(n,min,max)    (((n) > (max)) ? (max) : (((n) < (min)) ? (min) : (n)))
#define PI(n)   (3.14159265358979f * (n))
#define ARCTAN(x)   (x>=0.75f)? (0.567588218f*x + 0.217809945f):(x>=0.50f)? (0.719413999f*x + 0.103940609f):(x>=0.25f)? (0.874675783f*x + 0.026309717f):(0.979914653f*x);
// 3つの最大値検出
#define MAX3(u,v,w) (((u)>(v)) ? (((u)>(w)) ? (u):(w)):(((v)>(w)) ? (v):(w)))
// 3つの最小値検出
#define MIN3(u,v,w) (((u)<(v)) ? (((u)<(w)) ? (u):(w)):(((v)<(w)) ? (v):(w)))
// 3つの中間値検出
#define MID3(u,v,w) (((u)>(v)) ? (((u)<(w)) ? (u):(((w)>(v)) ? (w):(v))):(((u)>(w)) ? (u):(((w)>(v)) ? (v):(w))))
#define ABS(n)      ((n) < (0) ? (-n) : (n))

static inline s4 LIMIT_s4(s4 n, s4 min, s4 max){
    if(n < min){
        n = min;
    }else if (n > max){
        n = max;
    }else{
        ;
    }
    return n;
}

static inline f4 LIMIT_f4(f4 n, f4 min, f4 max){
    if(n < min){
        n = min;
    }else if (n > max){
        n = max;
    }else{
        ;
    }
    return n;
}

// Include TI header files
#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"

// Include NLibrary header files
#include "K17100_ioFunction.h"
#include "K17100_cmpFunction.h"
#include "K17100_dacFunction.h"
#include "ePwmFunction.h"

#endif /* NLIBRARY_H_ */
