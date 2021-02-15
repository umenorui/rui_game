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
#include "score.h"
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "Pause.h"

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

	//プレイヤーの初期化処理
	InitPlayer();

	//敵の初期化処理
	InitEnemy();

	//弾の初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//スコアの初期化処理
	InitScore();

	//敵の出現場所
	SetEnemy(D3DXVECTOR3(100, 200, 0), 0);

	//ポーズの初期化処理
	InitPause();

	//サウンドを再生
	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//----------------------
//ゲーム画面の終了処理
//----------------------
void UninitGame(void)
{
	//サウンドの停止
	StopSound();

	//ポーズの終了処理
	UninitPause();

	//スコアの終了処理
	UninitScore();

	//爆発の終了処理
	UninitExplosion();

	//弾の終了処理
	UninitBullet();

	//敵の終了処理
	UninitEnemy();

	//プレイヤーの終了処理
	UninitPlayer();

	//背景の終了処理
	UninitBg();
}

//----------------------
//ゲーム画面の更新処理
//----------------------
void UpdateGame(void)
{
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

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

		//プレイヤーの更新処理
		UpdatePlayer();

		//敵の更新処理
		UpdateEnemy();

		//弾の更新処理
		UpdateBullet();

		//爆発の更新処理
		UpdateExplosion();

		//スコアの更新処理
		UpdateScore();

		//フェードの更新処理
		if (pEnemy->bUse == false)
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

	//プレイヤーの描画処理
	DrawPlayer();

	//敵の描画処理
	DrawEnemy();
	
	//弾の描画処理
	DrawBullet();

	//爆発の描画処理
	DrawExplosion();

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
