#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECIINPUT_VERSION (0x0800)
//インクルードファイル
#include <windows.h>
#include "d3dx9.h"						//描画処理に必要
#include "dinput.h"						//入力処理に必要
#include "xaudio2.h"					//サウンド再生に必要

//----------------------
//ライブラリのリンク
//----------------------
#pragma comment(lib, "d3d9.lib")		//描画処理に必要
#pragma comment(lib, "d3dx9.lib")		//拡張ライブラリ
#pragma comment(lib, "dxguid.lib")		//コンポーネント使用に必要

//ライブラリファイル
#pragma comment(lib,"dinput8.lib")		//入力処理に必要
#pragma comment(lib,"winmm.lib")

//----------------------
//マクロ定義
//----------------------
#define SCREEN_WIDTH (1000)			//横
#define SCREEN_HEIGHT (800)			//縦
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME	"WINDOWCLASS"	//ウインドウクラスの名前
#define WINDOW_NAME	"wind"			//ウインドウの名前
#define WINDOW_POS_X (100)			//X始点
#define WINDOW_POS_Y (100)			//Y始点
#define ID_TIMER (121)				//タイマー
#define TIMER_INTERVAL (1000/60)	//タイマー発生間隔
#define nNumber (3)					//
#define ID_BUTTON000 (101)			

//----------------------
//構造体
//----------------------
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//１．０で固定
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
}VERTEX_2D;

//----------------------
//モードの設定
//----------------------
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_TUTORIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
}MODE;

//----------------------
//プロトタイプ宣言
//----------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif
