//======================
//
//scoreの処理
//Author:uneno rui
//
//======================
#include"main.h"
#include"score.h"
#include"enemy.h"
#include"enemy2.h"

//====================
//グローバル変数
//====================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//テクスチュアのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//頂点バッファのポインタ
int g_nScore;										//スコア
SCORE g_aSCORE[MAX_SCORE];							//scoreの情報

//----------------------
//初期化処理
//----------------------
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nScore = 0;

	//デバイスの取得	
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureScore);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountScore = 0; nCountScore < MAX_SCORE; nCountScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(50.0f + 70.0f*nCountScore, 70.0, 0);
		pVtx[1].pos = D3DXVECTOR3(50.0f + 70.0f*nCountScore, 30.0, 0);
		pVtx[2].pos = D3DXVECTOR3(100.0f + 70.0f*nCountScore, 70.0, 0);
		pVtx[3].pos = D3DXVECTOR3(100.0f + 70.0f*nCountScore, 30.0, 0);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//左下
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//左上
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);//右下
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);//右上

		pVtx += 4;
	}
	g_pVtxBuffScore->Unlock();
	return S_OK;
}

//----------------------
//終了処理
//----------------------
void UninitScore(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//テクスチュアの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//----------------------
//更新処理
//----------------------
void UpdateScore(void)
{

}

//----------------------
//描画処理
//----------------------
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得	
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (int nCountScore = 0; nCountScore < MAX_SCORE; nCountScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountScore * 4,
			2);
	}
}

void AddScore(int nValue)
{
	int nData = 10000000;
	int aNumber[8];
	g_nScore += nValue;

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// スコアを格納
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		aNumber[nCount] = g_nScore / nData % 10;
		nData /= 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * aNumber[nCount], 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0f + 0.1f * aNumber[nCount], 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.1f + 0.1f * aNumber[nCount], 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * aNumber[nCount], 0.0);

		pVtx += 4;
	}
	g_pVtxBuffScore->Unlock();
}