/*
 * AD_det.h
 *
 *  Created on: 2015/12/01
 *      Author: ohnuma
 */

#ifndef ADDETECTION_H_
#define ADDETECTION_H_

#include "GlobalParameters.h"

//==============================================================================
// Global関数のプロトタイプ宣言
//==============================================================================
extern void adDet(void);
extern void adDetInit(void);

//==============================================================================
// Global変数宣言
//==============================================================================

extern s4      s4g_flg_offset;
extern s4      s4g_offsetError;
extern s4      s4g_state_offset;   /* オフセット調整状況　0で未実施　1以上が回数*/


extern f4      f4g_v1Det,f4g_v2Det,f4g_v3Det,f4g_v4Det,f4g_v5Det,f4g_v6Det;
extern f4      f4g_i1Det,f4g_i2Det,f4g_i3Det,f4g_i4Det,f4g_i5Det,f4g_i6Det;
extern f4      f4g_th1Det,f4g_th2Det,f4g_th3Det,f4g_th4Det;
extern f4	   f4g_tempInternal;

extern f4      f4g_gainI1,f4g_gainI2,f4g_gainI3,f4g_gainI4,f4g_gainI5,f4g_gainI6;


#endif /* ADDETECTION_H_ */
