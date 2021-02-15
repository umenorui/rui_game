//======================
//
//enemy2の処理
//Author:uneno rui
//
//======================
//インクルードファイル
//====================
#include "enemy2.h"
//#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "input.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureEnemy2 = NULL;				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy2 = NULL;			//頂点バッファのポインタ
ENEMY2 g_aEnemy2[MAX_ENEMY2TYPE];							//敵の情報
D3DXVECTOR3 g_PosEnemy2;		//場所
D3DXVECTOR3 g_rotEnemy2;
D3DXVECTOR3 g_moveEnemy2;	//移動量

//================
//敵の初期化処理
//================
HRESULT InitEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_pTextureEnemy2);

	//enemyHP
	g_aEnemy2[0].nLife = ENEMY2LIFE1;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_ENEMY2TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy2,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	//敵の初期位置
	g_PosEnemy2 = D3DXVECTOR3(600, 465, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY2TYPE; nCountEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//左下
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//左上
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);	//右下
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);	//右上

		pVtx += 4;
	}
	g_pVtxBuffEnemy2->Unlock();

	return S_OK;
}

//----------------------
//敵の終了処理
//----------------------
void UninitEnemy2(void)
{
	//サウンドの停止
	//StopSound();

	//頂点バッファの開放
	if (g_pVtxBuffEnemy2 != NULL)
	{
		g_pVtxBuffEnemy2->Release();
		g_pVtxBuffEnemy2 = NULL;
	}

	//テクスチュアの開放
	if (g_pTextureEnemy2 != NULL)
	{
		g_pTextureEnemy2->Release();
		g_pTextureEnemy2 = NULL;
	}
}

//----------------------
//敵の更新処理
//----------------------
void UpdateEnemy2(void)
{
	ENEMY2 *pEnemy2;
	pEnemy2 = &g_aEnemy2[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy2[0].pos.x -= 2.0;						//動かし

	g_PosEnemy2 = D3DXVECTOR3(700, 400, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY2TYPE; nCountEnemy++, pEnemy2++)
	{
		if (pEnemy2->bUse == true)
		{
			pEnemy2->nCnterAnim++;

			if ((pEnemy2->nCnterAnim % 3) == 0)
			{
				pEnemy2->nPatternAnim = (pEnemy2->nPatternAnim + 1) % 3;
			}

			//頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy2->nPatternAnim, 1.0f);		//左下
			pVtx[1].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy2->nPatternAnim, 0.0f);		//左上
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy2->nPatternAnim, 1.0f);		//右下
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy2->nPatternAnim, 0.0f);		//右上

																					//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);

			if (g_PosEnemy2.x < (0 + 200 / 2))				//左端
			{
				//g_PosPlayer.pos.x = ( 0 +100 / 2);
				g_PosEnemy2.x = (SCREEN_WIDTH - 100 / 2);
				//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			}

			switch (g_aEnemy2[0].state)
			{
			case ENEMY2STATE_DAMAGE:
				g_aEnemy2[0].nCounterState--;
				if (g_aEnemy2[0].nCounterState <= 0)
				{
					g_aEnemy2[0].state = ENEMY2STATE_NORMAL;
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy2->Unlock();
}

//----------------------
//敵の描画処理
//----------------------
void DrawEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy2, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEnemy2);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY2TYPE; nCountEnemy++)
	{
		if (g_aEnemy2[nCountEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountEnemy,
				2);
		}
		nCountEnemy += 4;
	}
}

void SetEnemy2(D3DXVECTOR3 pos, int nType)
{
	//弾の設定
	ENEMY2 *pEnemy2;
	pEnemy2 = &g_aEnemy2[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountENEMY = 0; nCountENEMY < MAX_ENEMY2TYPE; nCountENEMY++, pEnemy2++)
	{
		if (pEnemy2->bUse == false)
		{
			//位置を設定
			g_aEnemy2[nCountENEMY].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y - 50, 0.0f);

			pEnemy2->bUse = true;
			break;
		}
		pVtx += 4;
	}
}

ENEMY2 * GetEnemy2(void)
{
	return &g_aEnemy2[0];
}

bool HitEnemy2(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy2[nIdx].nLife -= nDamage;	//体力を減らす
	if (g_aEnemy2[nIdx].nLife <= 0)		//０以下で下の処理をする
	{
		//爆発
		SetExplosion(g_aEnemy2->pos);

		//効果音
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);

		//スコアの加算
		AddScore(8);

		//敵を使わない
		g_aEnemy2[nIdx].bUse = false;

		return true;
	}
	else
	{
		//効果音
		//PlaySound(SOUND_LABEL_SE_HIT);

		//点滅
		g_aEnemy2[nIdx].state = ENEMY2STATE_DAMAGE;
		g_aEnemy2[nIdx].nCounterState = 5;

		//色
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		return false;
	}
	g_pVtxBuffEnemy2->Unlock();
}