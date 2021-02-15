//======================
//
//bulletの処理
//Author:uneno rui
//
//====================
//インクルードファイル
//====================
#include "bullet.h"
#include "enemy.h"
#include "enemy2.h"
#include "explosion.h"
//#include "sound.h"
#include "score.h"

//================
//弾の構造体
//================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動
	int nLife;			//寿命
	bool bUse;			//使用しているかどうか
	BULLETTYPE type;	//種類
} BULLET;

//================
//グローバル変数
//================
LPDIRECT3DTEXTURE9 g_pTextureBullet[MAX_BULLETTIPE] = {};	//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//頂点バッファのポインタ
BULLET g_aBullet[MAX_BULLET];								//弾の情報

//================
//弾の初期化処理
//================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet002.png", &g_pTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &g_pTextureBullet[1]);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		g_aBullet[nCountBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].nLife;
		g_aBullet[nCountBullet].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10, g_aBullet[nCountBullet].pos.y + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10, g_aBullet[nCountBullet].pos.y - 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10, g_aBullet[nCountBullet].pos.y + 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10, g_aBullet[nCountBullet].pos.y - 10, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//左下
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//左上
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);		//右下
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);		//右上

		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//----------------------
//弾の終了処理
//----------------------
void UninitBullet(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//テクスチュアの開放
	for (int nCountBullet = 0; nCountBullet < MAX_BULLETTIPE; nCountBullet++)
	{
		if (g_pTextureBullet[nCountBullet] != NULL)
		{
			g_pTextureBullet[nCountBullet]->Release();
			g_pTextureBullet[nCountBullet] = NULL;
		}
	}
}

//----------------------
//弾の更新処理
//----------------------
void UpdateBullet(void)
{
	BULLET *pBullet;
	ENEMY *pEnemy;
	ENEMY2 *pEnemy2;
	pBullet = &g_aBullet[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			//位置の更新
			g_aBullet[nCountBullet].pos += pBullet->move;

			//敵の当たり判定
			pEnemy = GetEnemy();
			for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY; nCountEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					if (pEnemy->pos.y + 50 >= pBullet->pos.y &&
						pEnemy->pos.y - 50 <= pBullet->pos.y &&
						pEnemy->pos.x + 50 >= pBullet->pos.x &&
						pEnemy->pos.x - 50 <= pBullet->pos.x)
					{
						////スコアの加算
						AddScore(1000);

						//弾の破棄
						pBullet->bUse = false;

						//弾のダメージ
						HitEnemy(nCountEnemy, BULLETDAMAGE);
					}
				}
			}

			pEnemy2 = GetEnemy2();
			for (int nCountEnemy2 = 0; nCountEnemy2 < MAX_ENEMY; nCountEnemy2++, pEnemy++)
			{
				if (pEnemy2->bUse == true)
				{
					if (pEnemy2->pos.y + 50 >= pBullet->pos.y &&
						pEnemy2->pos.y - 50 <= pBullet->pos.y &&
						pEnemy2->pos.x + 50 >= pBullet->pos.x &&
						pEnemy2->pos.x - 50 <= pBullet->pos.x)
					{
						//弾の破棄
						pBullet->bUse = false;

						////スコアの加算
						//AddScore(2000);

						//弾のダメージ
						HitEnemy2(nCountEnemy2, BULLETDAMAGE);
					}
				}
			}

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 20, g_aBullet[nCountBullet].pos.y + 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 20, g_aBullet[nCountBullet].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 20, g_aBullet[nCountBullet].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 20, g_aBullet[nCountBullet].pos.y - 20, 0.0f);

			//寿命チェック
			pBullet->nLife = 50;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}

//----------------------
//弾の描画処理
//----------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	for (int nCountBullet = 0; nCountBullet < MAX_BULLETTIPE; nCountBullet++)
	{
		pDevice->SetTexture(0, g_pTextureBullet[nCountBullet]);
	}

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountBullet * 4,
				2);
		}
	}
}

//----------------
//弾の設定
//----------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	VERTEX_2D *pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//位置を設定
			g_aBullet[nCountBullet].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 15, g_aBullet[nCountBullet].pos.y + 15, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 15, g_aBullet[nCountBullet].pos.y - 15, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 15, g_aBullet[nCountBullet].pos.y + 15, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 15, g_aBullet[nCountBullet].pos.y - 15, 0.0f);

			//移動量を設定
			pBullet->move = move;

			//寿命を設定
			pBullet->nLife = nLife;

			pBullet->bUse = true;

			break;
		}
		pVtx += 4;
	}
}

//==================
//弾の頂点座標の設定
//==================
void SetVertexBullet(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(60, 80, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(60, 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(120, 80, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(120, 20, 0.0f);

	g_pVtxBuffBullet->Unlock();
}