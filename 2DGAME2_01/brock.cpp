//======================
//
//brockの処理
//Author:uneno rui
//
//======================
//インクルードファイル
//====================
#include "brock.h"
#include "player.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureBrock = NULL;				//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBrock = NULL;			//頂点バッファのポインタ
BROCK g_aBrock[MAX_BROCKTYPE];							//敵の情報
D3DXVECTOR3 g_PosBrock;		//場所
D3DXVECTOR3 g_rotBrock;
D3DXVECTOR3 g_moveBrock;	//移動量

//================
//ブロックの初期化処理
//================
HRESULT InitBrock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block001.png", &g_pTextureBrock);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_BROCKTYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBrock,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	//敵の初期位置
	//g_PosBrock = D3DXVECTOR3(900, 800, 0.0f);

	for (int nCountBrock = 0; nCountBrock < MAX_BROCKTYPE; nCountBrock++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 50, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 50, g_aBrock[nCountBrock].pos.y - 50, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(20.0f, 1.0f);	//右下
		pVtx[3].tex = D3DXVECTOR2(20.0f, 0.0f);	//右上

		pVtx += 4;
	}
	g_pVtxBuffBrock->Unlock();

	return S_OK;
}

//----------------------
//ブロックの終了処理
//----------------------
void UninitBrock(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBrock != NULL)
	{
		g_pVtxBuffBrock->Release();
		g_pVtxBuffBrock = NULL;
	}

	//テクスチュアの開放
	if (g_pTextureBrock != NULL)
	{
		g_pTextureBrock->Release();
		g_pTextureBrock = NULL;
	}
}

//----------------------
//ブロックの更新処理
//----------------------
void UpdateBrock(void)
{
	BROCK *pBrock;
	pBrock = &g_aBrock[0];
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBrock = 0; nCountBrock < MAX_BROCKTYPE; nCountBrock++, pBrock++)
	{
		//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 1050, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 1050, g_aBrock[nCountBrock].pos.y - 50, 0.0f);

			//当たり判定
			//if (pBrock->pos.x + 400 >= pPlayer->pos.x - 40 &&
			//	pBrock->pos.x - 40 <= pPlayer->pos.x + 40 &&
			//	pBrock->pos.y + 40 >= pPlayer->pos.y - 40 &&
			//	pBrock->pos.y - 40 <= pPlayer->pos.y + 40)
			//{
			//	//if (pBrock->pos.y + 100 <= pPlayer->pos.y &&)	//sita
			//	//{
			//	g_PosBrock.y = (SCREEN_WIDTH - 250 / 2);
			//	/*	pPlayer->move.y = 0.0;*/
			//		//pPlayer->pos.y = pBrock->pos.y + 100;
			//		//pPlayer->pos.x = pBrock->pos.x + 100;
			//	}
				//if (pBrock->pos.y - 100 <= pPlayer->pos.y)	//上
				//{	
				//	pPlayer->move.y = 0.0;
				//	pPlayer->pos.y = pBrock->pos.y - 100;
				//	//pPlayer->pos.x = pBrock->pos.x - 100;
				//}

			//}

			//if (pBrock->pos.y + 50 >= pPlayer->pos.y - 50 &&
			//	pBrock->pos.y - 50 <= pPlayer->pos.y + 50)
			//{
			//	if (pBrock->pos.x - 100 <= pPlayer->pos.x)	//hidari
			//	{
			////		pPlayer->pos.x = pBrock->pos.x - 100;
			//pPlayer->pos.y = pBrock->pos.y + 100;
			//	}
			//	if (pBrock->pos.y + 100 <= pPlayer->pos.y)	//migi
			//	{
			////		pPlayer->pos.x = pBrock->pos.x + 100;
			//pPlayer->pos.y = pBrock->pos.y - 100;
			//	}
			//}
			
		pVtx += 4;
	}
	g_pVtxBuffBrock->Unlock();
}

//----------------------
//ブロックの描画処理
//----------------------
void DrawBrock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBrock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBrock);

	for (int nCountBrock = 0; nCountBrock < MAX_BROCKTYPE; nCountBrock++)
	{
		if (g_aBrock[nCountBrock].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountBrock,
				2);
		}
		nCountBrock += 4;
	}
}

void SetBrock(D3DXVECTOR3 pos, int nType)
{
	//弾の設定
	BROCK *pBrock;
	pBrock = &g_aBrock[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountENEMY = 0; nCountENEMY < MAX_BROCKTYPE; nCountENEMY++, pBrock++)
	{
		if (pBrock->bUse == false)
		{
			//位置を設定
			g_aBrock[nCountENEMY].pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x - 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y + 100, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x - 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y - 100, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x + 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x + 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y - 100, 0.0f);

			pBrock->bUse = true;
			break;
		}
		pVtx += 4;
	}
}