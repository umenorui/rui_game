#pragma once
#ifndef _PLAYER_H_
#define _PLATER_H_
#include "main.h"
#include "input.h"
#include "bullet.h"

//----------------------
//プロトタイプ宣言
//----------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

#endif