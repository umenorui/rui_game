#ifndef _TIMER_H_
#define _TIMER_H_

#include "main.h"

#define MAX_TIMER (8)//スコアの最大数

//===============
//弾の構造体
//===============
typedef struct
{
	int nTimer;//時間
}TIMER;

//===============
//プロトタイプ宣言
//===============
HRESULT InitTimer(void);
void UninitTimer(void);
void UpdateTimer(void);
void DrawTimer(void);
TIMER *GetTimer(void);
void AddTimer(int nValue);
#endif
