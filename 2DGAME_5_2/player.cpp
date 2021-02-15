//======================
//
//playerの処理
//Author:uneno rui
//
//======================
#include "player.h"
#include "sound.h"

//==============
//グローバル変数
//==============
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチュアのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファのポインタ
D3DXVECTOR3 g_PosPlayer;
D3DXVECTOR3 g_rotPlayer;
D3DXVECTOR3 g_movePlayer;	//移動量
int g_nCounterAnim;			//アニメーションのカウンター
int g_nPatternAnim;			//アニメーションのパターン
int g_nseetAnim;
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
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player001.png", &g_pTexturePlayer);

	//変数初期化
	g_nCounterAnim = 0;
	g_nPatternAnim = 0;
	g_nseetAnim = 0;

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
	g_PosPlayer = D3DXVECTOR3(500, 650, 0.0f);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(200, 712, 0.0f);	//最後2Dは0.0固定
	pVtx[1].pos = D3DXVECTOR3(200, 200, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(712, 712, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(712, 200, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

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

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	g_nCounterAnim++;				//アニメーションカウンター更新
	//if ((g_nCounterAnim % 6) == 0)
	//{
	//g_nPatternAnim = (g_nPatternAnim + 1) % 8;

	//g_nseetAnim = (g_nseetAnim + 1) % 10;

	//pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*g_nPatternAnim, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*g_nPatternAnim, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*g_nPatternAnim, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*g_nPatternAnim, 0.0f);
	//}

	//対角線の長さ
	g_fLengthPlayer = sqrtf(20 * 20 + 60 * 60);
	//対角線の角度
	g_fAnglePlayer = atan2f(150, 150);

	if (GetKeyboardPress(DIK_D) == true)
	{
		g_movePlayer.x += sinf(D3DX_PI*0.5f) * 1.0f;
	}

	////右押した
	//if (GetKeyboardPress(DIK_D) == true)
	//{
	//	//移動量
	//	g_movePlayer.x += sinf(D3DX_PI)*0.5f;
	//	g_PosPlayer.z += 0.0f;

	//	//上押した
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{
	//		//移動量
		//	g_PosPlayer.y += cosf(D3DX_PI) * -0.5f;
		//	g_PosPlayer.x += sinf(D3DX_PI) * 0.5f;
		//	g_PosPlayer.z += 0.0f;
		//}
		////下押した
		//if (GetKeyboardPress(DIK_S) == true)
		//{
		//	//移動量
		//	g_PosPlayer.x += sinf(D3DX_PI) * -0.5f;
		//	g_PosPlayer.y += cosf(D3DX_PI) * 0.5f;
		//	g_PosPlayer.z += 0.0f;
		//}
	//}

	//左押した
	if (GetKeyboardPress(DIK_A) == true)
	{
		//移動量
		g_movePlayer.x += -sinf(D3DX_PI*0.5f) * 1.0f;
	}

	//上押した
	if (GetKeyboardPress(DIK_W) == true)
	{	//ずっと移動
		//移動量
		g_movePlayer.y += -sin(D3DX_PI*0.5f)* 0.5f;
	}

	//下押した
	if (GetKeyboardPress(DIK_S) == true)
	{	//ずっと移動
		//移動量
		g_movePlayer.y += sin(D3DX_PI*0.5f) * 0.5f;
	}

	////回転
	//if (GetKeyboardPress(DIK_K) == true)
	//{
	//	g_rotPlayer.z += (D3DX_PI / 18);
	//	if (g_rotPlayer.z > D3DX_PI)
	//	{
	//		g_rotPlayer.z -= D3DX_PI*2.0f;
	//	}
	//}

	//発射
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		PlaySound(SOUND_LABEL_SE_SHOT);
		D3DXVECTOR3 move;
		move = D3DXVECTOR3(0.0f, cosf(D3DX_PI) * 6.5f, 0.0f);
		SetBullet(g_PosPlayer, move, 100);
	}

	pVtx[0].pos.x = g_PosPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer)*g_fLengthPlayer;
	pVtx[0].pos.y = g_PosPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_PosPlayer.x - sinf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
	pVtx[1].pos.y = g_PosPlayer.y - cosf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_PosPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.y = g_PosPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_PosPlayer.x - sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].pos.y = g_PosPlayer.y - cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//位置更新
	g_PosPlayer.x += g_movePlayer.x;
	g_PosPlayer.y += g_movePlayer.y;

	//移動量の減衰
	g_movePlayer.x += (0.0f - g_movePlayer.x) *0.05f;
	g_movePlayer.y += (0.0f - g_movePlayer.y) *0.05f;

	//画面外チェック
	if (g_PosPlayer.y < (0 + 150 / 2))				//上端
	{
		g_PosPlayer.y = (0 + 150 / 2);
	}

	if (g_PosPlayer.x < (0 + 100 / 2))				//左端
	{
		g_PosPlayer.x = (0 + 100 / 2);
	}

	if (g_PosPlayer.y > (SCREEN_HEIGHT - 150 / 2))	//下端
	{
		g_PosPlayer.y = (SCREEN_HEIGHT - 150 / 2);
	}

	if (g_PosPlayer.x > (SCREEN_WIDTH - 100 / 2))	//右端
	{
		g_PosPlayer.x = (SCREEN_WIDTH - 100 / 2);
	}

	g_pVtxBuffPlayer->Unlock();
}

//==================
//プレイヤーの描画処理
//==================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}