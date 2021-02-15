//======================
//
//playerの処理
//Author:uneno rui
//
//======================
//インクルードファイル
//====================
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy2.h"

//==============
//マクロ定義
//==============
#define PLAYER_WIDTH (100)			//横
#define PLAYER_HEIGHT (150)			//縦

//==============
//グローバル変数
//==============
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチュアのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファのポインタ
PLAYER g_PosPlayer;
D3DXVECTOR3 g_rotPlayer;
float g_fLengthPlayer;		//対角線の長さ
float g_fAnglePlayer;		//対角線の角度

//====================
//プレイヤーの初期化処理
//====================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player000.png", &g_pTexturePlayer);

	//変数初期化
	g_PosPlayer.nCnterAnim = 0;
	g_PosPlayer.nPatternAnim = 0;
	g_PosPlayer.nPatternnSeatAnim = 0;
	g_PosPlayer.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_PosPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosPlayer.bUse = true;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//プレイヤーの初期位置
	g_PosPlayer.pos = D3DXVECTOR3(100,600, 0.0f);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(PLAYER_WIDTH - 50, PLAYER_HEIGHT - 50, 0.0f);	//最後2Dは0.0固定
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH - 50, PLAYER_HEIGHT + 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYER_WIDTH + 50, PLAYER_HEIGHT - 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH + 50, PLAYER_HEIGHT + 50, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//==================
//プレイヤーの終了処理
//==================
void UninitPlayer(void)
{
	//テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//====================
//プレイヤーの更新処理
//====================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;
	pPlayer = &g_PosPlayer;

	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	ENEMY2 *pEnemy2;
	pEnemy2 = GetEnemy2();

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	//ロック

	if(pPlayer->bUse == true)
	{
	g_PosPlayer.nCnterAnim;				//アニメーションカウンター更新

	//対角線の長さ
	g_fLengthPlayer = sqrtf(30 * 30 + 60 * 60);

	//対角線の角度
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//if (g_PosPlayer.bUse == false)
	//{
		//右押した
		if (GetKeyboardPress(DIK_D) == true)
		{
			//移動量
			g_PosPlayer.move.x += 4.0f;
			if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W) == true)
			{
				pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.50f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.50f, 0.0f);
			}
			else
			{	
				//アニメーション
				if((g_PosPlayer.nCnterAnim % 5) == 0)
				g_PosPlayer.nPatternAnim = (g_PosPlayer.nPatternAnim + 1) % 5;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 0.0f);
			}
		}

		//左押した
		if (GetKeyboardPress(DIK_A) == true)
		{
			//移動量
			g_PosPlayer.move.x += -4.0f;
			if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W) == true)
			{
				pVtx[0].tex = D3DXVECTOR2(0.25f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.50f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.50f, 0.5f);
			}
			else
			{
				//アニメーション
				if ((g_PosPlayer.nCnterAnim % 5) == 0)
				{
					g_PosPlayer.nPatternAnim = (g_PosPlayer.nPatternAnim + 1) % 5;

					pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
					pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
				}
			}
		}

		//ジャンプ
		if (GetKeyboardTrigger(DIK_W) == true && g_PosPlayer.pos.y >= 600)
		{
			//移動量
			g_PosPlayer.move.y -= 25.0f;
			//if (GetKeyboardPress(DIK_W) == true)	//長く浮く
			//{
			//	g_PosPlayer.move.y -= 2.0f;
			//}
		}

		//左発射
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			D3DXVECTOR3 move;
			move = D3DXVECTOR3(-8.0f, 0.0f, 0.0f);
			SetBullet(g_PosPlayer.pos, move, 10);
		}

		//右発射
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			D3DXVECTOR3 move;
			move = D3DXVECTOR3(8.0f, 0.0f, 0.0f);
			SetBullet(g_PosPlayer.pos, move, 10);
		}

		//上発射
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			D3DXVECTOR3 move;
			move = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
			SetBullet(g_PosPlayer.pos, move, 10);
		}

		//重力
		g_PosPlayer.move.y += 1.0f;

		////位置更新
		g_PosPlayer.pos.x += g_PosPlayer.move.x;
		g_PosPlayer.pos.y += g_PosPlayer.move.y;

		//移動量の減衰
		g_PosPlayer.move.x += (0.0f - g_PosPlayer.move.x) *0.5f;

		//重なったら終わり
		if (pPlayer->pos.x +30 >= pEnemy->pos.x -30 &&
			pPlayer->pos.x -30 <= pEnemy->pos.x +30 &&
			pPlayer->pos.y + 30 >= pEnemy->pos.y - 30 &&
			pPlayer->pos.y - 30 <= pEnemy->pos.y + 30)
		{
			pPlayer->bUse = false;
		}

		//if (pPlayer->pos.x + 30 >= pEnemy2->pos.x - 30 &&
		//	pPlayer->pos.x - 30 <= pEnemy2->pos.x + 30 &&
		//	pPlayer->pos.y + 30 >= pEnemy2->pos.y - 30 &&
		//	pPlayer->pos.y - 30 <= pEnemy2->pos.y + 30)
		//{
		//	pPlayer->bUse = false;
		//}

		//画面外チェック
		if (g_PosPlayer.pos.y < (0 + 150 / 2))				//上端
		{
			g_PosPlayer.pos.y = (0 + 150 / 2);
		}

		if (g_PosPlayer.pos.x < (0 + 200 / 2))				//左端
		{
			//g_PosPlayer.pos.x = ( 0 +100 / 2);
			g_PosPlayer.pos.x = (0 + 200 / 2);
			//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
		}

		if (g_PosPlayer.pos.y > (SCREEN_HEIGHT - 300 / 2))	//下端
		{
			g_PosPlayer.move.y = 0.0f;						//地面の高さに戻す
			g_PosPlayer.pos.y = (SCREEN_HEIGHT - 300 / 2);
		}

		if (g_PosPlayer.pos.x > (SCREEN_WIDTH - 100 / 2))	//右端
		{
			//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			//g_PosPlayer.pos.x = (0 + 100 / 2);
		}

		pVtx[0].pos.x = g_PosPlayer.pos.x + sinf(g_rotPlayer.z - g_fAnglePlayer)*g_fLengthPlayer;
		pVtx[0].pos.y = g_PosPlayer.pos.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_PosPlayer.pos.x - sinf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
		pVtx[1].pos.y = g_PosPlayer.pos.y - cosf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_PosPlayer.pos.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.y = g_PosPlayer.pos.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_PosPlayer.pos.x - sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.y = g_PosPlayer.pos.y - cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

	}
	g_pVtxBuffPlayer->Unlock();	//アンロック
}

//==================
//プレイヤーの描画処理
//==================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *pPlayer;
	pPlayer = &g_PosPlayer;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (pPlayer->bUse == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

PLAYER * GetPlayer(void)
{
	return &g_PosPlayer;
}

