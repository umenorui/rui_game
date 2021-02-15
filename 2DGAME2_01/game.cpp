//======================
//
//gameの処理
//Author:uneno rui
//
//======================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy2.h"
#include "score.h"
//#include "sound.h"
#include "bg.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "pause.h"
#include "allscore.h"
#include "brock.h"
#include "timer.h"

//===============
//グローバル変数
//===============
bool g_bPause;			//ポーズ中かどうか

//----------------------
//ゲーム画面の初期化処理
//----------------------
HRESULT InitGame(void)
{
	//背景の初期化処理
	InitBg();

	//ブロックの初期化
	InitBrock();

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//敵の初期化処理
	InitEnemy2();

	//弾の初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//タイマーの初期化処理
	InitTimer();

	//スコアの初期化処理
	InitScore();

	//ブロックの設置場所
	SetBrock(D3DXVECTOR3(0, 750, 0), 0);

	//敵の出現場所
	SetEnemy(D3DXVECTOR3(800, 665, 0), 0);

	//敵の出現場所
	SetEnemy2(D3DXVECTOR3(800, 165, 0), 0);

	//ポーズの初期化処理
	InitPause();

	////サウンドを再生
	//PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//----------------------
//ゲーム画面の終了処理
//----------------------
void UninitGame(void)
{
	//サウンドの停止
	//StopSound();

	//ポーズの終了処理
	UninitPause();

	//スコアの終了処理
	UninitScore();

	//タイマーの終了処理
	UninitTimer();

	//爆発の終了処理
	UninitExplosion();

	//弾の終了処理
	UninitBullet();

	//敵の終了処理
	UninitEnemy();

	//敵の終了処理
	UninitEnemy2();

	//プレイヤーの終了処理
	UninitPlayer();

	//ブロックの開放
	UninitBrock();

	//背景の終了処理
	UninitBg();
}

//----------------------
//ゲーム画面の更新処理
//----------------------
void UpdateGame(void)
{
	ENEMY *pEnemy;
	ENEMY2 *pEnemy2;
	PLAYER *pPlayer;
	/*TIMER *pTimer;*/

	pEnemy = GetEnemy();
	pEnemy2 = GetEnemy2();

	pPlayer = GetPlayer();
	//pTimer = GetTimer();

	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{	//TRUEならポーズ
		UpdatePause();
	}
	else
	{	//FALSEなら通常通り
		//背景の更新処理
		UpdateBg();

		//ブロックの更新処理
		UpdateBrock();

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//敵の更新処理
		UpdateEnemy2();

		//弾の更新処理
		UpdateBullet();

		//爆発の更新処理
		UpdateExplosion();

		//タイマーの更新処理
		UpdateTimer();

		//スコアの更新処理
		UpdateScore();

		//フェードの更新処理
		if (pEnemy->bUse == false || pPlayer->bUse == false)
		{
			if (nFade == FADE_IN)
			{
				SetFade(FADE_NONE, MODE_GAME);
			}
			else if (nFade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}
		}
	}
}

//----------------------
//ゲーム画面の描画処理
//----------------------
void DrawGame(void)
{
	//背景の描画処理
	DrawBg();

	//ブロックの描画
	DrawBrock();		

	//プレイヤーの描画処理
	DrawPlayer();

	//敵の描画処理
	DrawEnemy();

	//敵2の描画処理
	DrawEnemy2();

	//弾の描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

	//タイマーの描画処理
	DrawTimer();

	//スコアの描画処理
	DrawScore();

	//ポーズの描画処理
	if (g_bPause == true)
	{
		DrawPause();
	}
}

void SetPause(bool bPause)
{
}