//======================
//
//explosionの処理
//Author:uneno rui
//
//======================
#include "explosion.h"

#define MAX_EXPLOSION (256)	//敵の種類

//====================
//爆発の構造体
//====================
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	int nCnterAnim;		//アニメーションカウンター
	int nPatternAnim;	//アニメーションパターンNO.
	bool bUse;			//使用しているかどうか
}EXPLOSION;

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureExplosion =NULL;			//テクスチュアのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//頂点バッファのポインタ
EXPLOSION g_aExplosion[MAX_EXPLOSION];					//爆発の情報

//----------------------
//爆発の初期化処理
//----------------------
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &g_pTextureExplosion);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		g_aExplosion[nCountExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCountExplosion].nCnterAnim = 0;
		g_aExplosion[nCountExplosion].nPatternAnim = 0;
		g_aExplosion[nCountExplosion].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 25, g_aExplosion[nCountExplosion].pos.y + 25, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 25, g_aExplosion[nCountExplosion].pos.y - 25, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 25, g_aExplosion[nCountExplosion].pos.y + 25, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 25, g_aExplosion[nCountExplosion].pos.y - 25, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//左下
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//左上
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);	//右下
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.0f);	//右上

		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();

	return S_OK;
}

//----------------------
//爆発の終了処理
//----------------------
void UninitExplosion(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	//テクスチュアの開放
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//----------------------
//爆発の更新処理
//----------------------
void UpdateExplosion(void)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++,pExplosion++)
	{
		if (pExplosion->bUse == true)
		{
			pExplosion->nCnterAnim++;

			if ((pExplosion->nCnterAnim % 3) == 0)
			{
				pExplosion->nPatternAnim = (pExplosion->nPatternAnim + 1) % 8;
			}

			//頂点情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*pExplosion->nPatternAnim, 1.0f);		//左下
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*pExplosion->nPatternAnim, 0.0f);		//左上
				pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*pExplosion->nPatternAnim, 1.0f);		//右下
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*pExplosion->nPatternAnim, 0.0f);		//右上

			//頂点座標の設定
				pVtx[0].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 330, pExplosion[nCntExplosion].pos.y + 130, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 330, pExplosion[nCntExplosion].pos.y - 130, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 530, pExplosion[nCntExplosion].pos.y + 130, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 530, pExplosion[nCntExplosion].pos.y - 130, 0.0f);
	
				if (pExplosion->nPatternAnim == 7)
				{
					pExplosion->bUse = false;
				}
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//----------------------
//爆発の描画処理
//----------------------
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountExplosion * 4,
				2);
		}
	}
}

void SetExplosion(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == false)
		{
			//位置を設定
			g_aExplosion[nCountExplosion].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 20, g_aExplosion[nCountExplosion].pos.y + 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 20, g_aExplosion[nCountExplosion].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 20, g_aExplosion[nCountExplosion].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 20, g_aExplosion[nCountExplosion].pos.y - 20, 0.0f);

			g_aExplosion[nCountExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}
