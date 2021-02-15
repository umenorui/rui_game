//======================
//
//ポーズの処理
//Author:uneno rui
//
//======================
#include "Pause.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;			//テクスチュアのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//頂点バッファのポインタ

HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg003.jpg", &g_pTexturePause);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0, 800, 0);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
	pVtx[2].pos = D3DXVECTOR3(1000, 800, 0);
	pVtx[3].pos = D3DXVECTOR3(1000, 0, 0);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//左下
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//左上
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);		//右下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);		//右上

	g_pVtxBuffPause->Unlock();

	return S_OK;
}

void UninitPause(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	//テクスチュアの開放
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}
}

void UpdatePause(void)
{
}

void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}