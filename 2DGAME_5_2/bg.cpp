//======================
//
//bgの処理
//Author:uneno rui
//
//======================
#include "bg.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureBg = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//頂点バッファのポインタ

//================
//背景の初期化処理
//================
HRESULT InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg001.jpg", &g_pTextureBg);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0,800,0);
		pVtx[1].pos = D3DXVECTOR3(0,0,0);
		pVtx[2].pos = D3DXVECTOR3(1000,800,0);
		pVtx[3].pos = D3DXVECTOR3(1000,0,0);

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

	g_pVtxBuffBg->Unlock();

	return S_OK;
}

//----------------------
//背景の終了処理
//----------------------
void UninitBg(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}

	//テクスチュアの開放
	if (g_pTextureBg != NULL)
	{
		g_pTextureBg->Release();
		g_pTextureBg = NULL;
	}
}

//----------------------
//背景の更新処理
//----------------------
void UpdateBg(void)
{
}

//----------------------
//背景の描画処理
//----------------------
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBg);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

