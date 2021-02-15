//======================
//
//enemyの処理
//Author:uneno rui
//
//======================
//インクルードファイル
//====================
#include "enemy.h"
//#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "input.h"
#include "player.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//頂点バッファのポインタ
ENEMY g_aEnemy[MAX_ENEMYTYPE];							//敵の情報
D3DXVECTOR3 g_PosEnemy;		//場所
D3DXVECTOR3 g_rotEnemy;
D3DXVECTOR3 g_moveEnemy;	//移動量

//================
//敵の初期化処理
//================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &g_pTextureEnemy);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_pTextureEnemy);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy003.png", &g_pTextureEnemy);

	//enemyHP
	g_aEnemy[0].nLife = ENEMYLIFE1;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_ENEMYTYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//敵の初期位置
	g_PosEnemy = D3DXVECTOR3(600, 665, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMYTYPE; nCountEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//----------------------
//敵の終了処理
//----------------------
void UninitEnemy(void)
{
	//サウンドの停止
	//StopSound();

	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	//テクスチュアの開放
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
}

//----------------------
//敵の更新処理
//----------------------
void UpdateEnemy(void)
{
	ENEMY *pEnemy;

	pEnemy = &g_aEnemy[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[0].pos.x -= 1.0;	//動かしたい

	g_PosEnemy = D3DXVECTOR3(700, 400, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMYTYPE; nCountEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pEnemy->nCnterAnim++;

			if ((pEnemy->nCnterAnim % 3) == 0)
			{
				pEnemy->nPatternAnim = (pEnemy->nPatternAnim + 1) % 3;
			}

			//頂点情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy->nPatternAnim, 1.0f);		//左下
			pVtx[1].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy->nPatternAnim, 0.0f);		//左上
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy->nPatternAnim, 1.0f);		//右下
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy->nPatternAnim, 0.0f);		//右上

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);

			if (g_PosEnemy.x < (0 + 200 / 2))				//左端
			{
				//g_PosPlayer.pos.x = ( 0 +100 / 2);
				g_PosEnemy.x = (SCREEN_WIDTH - 100 / 2);
				//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			}

			switch (g_aEnemy[0].state)
			{
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[0].nCounterState--;
				if (g_aEnemy[0].nCounterState <= 0)
				{
					g_aEnemy[0].state = ENEMYSTATE_NORMAL;
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
	g_pVtxBuffEnemy->Unlock();
}

//----------------------
//敵の描画処理
//----------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureEnemy);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMYTYPE; nCountEnemy++)
	{
		if (g_aEnemy[nCountEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountEnemy,
				2);
		}
		nCountEnemy += 4;
	}
}

void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	//弾の設定
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountENEMY = 0; nCountENEMY < MAX_ENEMYTYPE; nCountENEMY++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//位置を設定
			g_aEnemy[nCountENEMY].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y - 50, 0.0f);

			pEnemy->bUse = true;
			break;
		}
		pVtx += 4;
	}
}

ENEMY * GetEnemy(void)
{
	return &g_aEnemy[0];
}

bool HitEnemy(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nIdx].nLife -= nDamage;	//体力を減らす
	if (g_aEnemy[nIdx].nLife <= 0)		//０以下で下の処理をする
	{
		//爆発
		SetExplosion(g_aEnemy->pos);

		//効果音
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);

		//スコアの加算
		AddScore(5000);

		//敵を使わない
		g_aEnemy[nIdx].bUse = false;

		return true;
	}
	else
	{
	//	//効果音
		//PlaySound(SOUND_LABEL_SE_HIT);

		//点滅
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 5;

		//色
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		return false;
	}
	g_pVtxBuffEnemy->Unlock();
}