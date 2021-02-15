//======================
//
//titleの処理[main.cpp]
//Author:uneno rui
//
//======================
#include "title.h"
#include "fade.h"
#include "sound.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファのポインタ

//----------------------
//初期化処理
//----------------------
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg000.jpg", &g_pTextureTitle);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//左下
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//左上
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);	//右下
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);	//右上



	g_pVtxBuffTitle->Unlock();


	return S_OK;
}

//----------------------
//終了処理
//----------------------
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();

	//頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//テクスチャの開放
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}
}

//----------------------
//更新処理
//----------------------
void UpdateTitle(void)
{
	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{	
		//サウンドを再生
			PlaySound(SOUND_LABEL_SE_DECISION);

		if (nFade == FADE_IN)
		{
			SetFade(FADE_NONE, MODE_TITLE);
		}
		else if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_TUTORIAL);
		}
	}
}

//----------------------
//描画処理
//----------------------
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitle);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
