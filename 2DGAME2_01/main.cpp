//======================
//
//mainの処理
//Author:uneno rui
//
//======================
//インクルードファイル
//====================
#include "main.h"		//メイン
#include "input.h"		//入力
#include "player.h"		//自機
#include "bg.h"			//背景
#include "bullet.h"		//弾
#include "enemy.h"		//敵
//#include "enemy2.h"		//敵2
#include "fade.h"		//フェード
//#include "sound.h"		//音
#include "brock.h"		//ブロック
#include "title.h"		//タイトル
#include "tutorial.h"	//チュートリアル
#include "game.h"		//ゲーム
#include "result.h"		//リザルト
#include "allscore.h"	//最後のスコア
#include "timer.h"		//タイマー

//================
//プロトタイプ宣言
//================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
//void DrawFPS(void);

//===============
//グローバル変数
//===============
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;				//フォントへのポインタ
int g_nCountFPS;						//FPSカウンタ
MODE g_mode = MODE_TITLE;				//モードの種類

//==========
//メイン関数
//==========
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_EXCLAMATION),
		LoadCursor(NULL,IDC_HAND),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,		//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_EXCLAMATION),
	};
	HWND hWnd;
	MSG msg;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの作成
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,				//ウィンドウクラスの名前
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	DWORD dwExecLastTime;	//処理実行最終時刻
	DWORD dwFPSLastTime;	//FPS計測最終時刻
	DWORD dwCurrentTime;	//現在時刻
	DWORD dwFrameCount;		//フレームカウント

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime >= 500))
			{	//０．５秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
		}
		if ((dwCurrentTime - dwExecLastTime) > (1000/60))
		{
		dwExecLastTime = dwCurrentTime;

		//更新処理
		Update();

		//描画処理
		Draw();

		dwFrameCount++;
		}
	}

	//終了処理
	Uninit();

	//ウィンドウクラスの登録解除
	UnregisterClass(
		CLASS_NAME,		//ウィンドウクラスの名前
		wcex.hInstance);

	return (int)msg.wParam;
}

//======================
//ウィンドウプロシージャ
//======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:			//ウィンドウを破棄する
		PostQuitMessage(0);		//WM_QUITメッセージを返す
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "終了しますか？", "タイトル", MB_YESNOCANCEL | MB_ICONASTERISK);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
		}
		break;

	case WM_CLOSE:					//×ボタンで確認表示
		nID = MessageBox(NULL, "終了しますか？", "タイトル", MB_YESNOCANCEL | MB_ICONASTERISK);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//YESだったら閉じる
		}
		else
		{
			return 0;	//それ以外はウィンドウは閉じない
		}
		break;

	case WM_KEYDOWN:	//キー押したときのメッセージ
		switch (wParam)
		{
		case VK_UP:
			//無効領域を強制的に発生させる
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_RIGHT:
			//nPosy++;
			//無効領域を強制的に発生させる
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_ESCAPE://エスケープキーで表示
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//----------------------
//初期化処理
//----------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//アルファ値の合成の設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ソースの合成方法の設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//デスティネーションの合成方法の設定

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値　繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V値　繰り返し

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//アルファ値の合成
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DXCreateFont(g_pD3DDevice, 8, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&g_pFont);

	//キーボードの初期化処理
	InitKeyboard(hInstance,hWnd);

	//ゲーム画面の初期化処理
	SetMode(g_mode);

	//フェードの初期化処理
	InitFade(g_mode);

	//サウンドの初期化処理
	//InitSound(hWnd);

	////サウンドを再生
	//PlaySound(SOUND_LABEL_BGM003);

	return S_OK;
}

//----------------------
//終了処理
//----------------------
void Uninit(void)
{
	//サウンドの終了処理
	//UninitSound();

	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	}

	//フェードの開放
	UninitFade();

	//キーボードの開放
	UninitKeyboard();

	//Directデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	if (g_pFont != NULL)
	{
		g_pFont-> Release();
		g_pFont = NULL;
	}
}

//----------------------
//更新処理
//----------------------
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();

	//フェードの更新処理
	UpdateFade();

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;
	case MODE_TUTORIAL:
		UpdateTutorial();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateResult();
		break;
	//case MODE_ALLSCORE:
	//	UpdateAllscore();
	//	break;
	}
}

//----------------------
//描画処理
//----------------------
void Draw(void)
{
	//バックバッファ&Zバッファのクリア（画面のクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),1.0f,0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		//case MODE_ALLSCORE:
		//	DrawAllscore();
		//	break;
		}

		//フェードの描画処理
		DrawFade();

		////FPSの描画
		//DrawFPS();

		//描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//void DrawFPS(void)
//{
//	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	char astr[256];
//
//	wsprintf(&astr[0], "FPS:%d\n", g_nCountFPS);
//
//	//テキストの描画
//	g_pFont->DrawText(NULL, &astr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	//デバイスの取得
	return g_pD3DDevice;
}

//モードの設定
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	//case MODE_ALLSCORE:
	//	UninitAllscore();
	//	break;
	}

	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	//case MODE_ALLSCORE:
	//	InitAllscore();
	//	break;
	}
	g_mode = mode;
}

MODE GetMode(void)
{
	return MODE();
}
