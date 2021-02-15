//======================
//
//main�̏���
//Author:uneno rui
//
//======================
//�C���N���[�h�t�@�C��
//====================
#include "main.h"		//���C��
#include "input.h"		//����
#include "player.h"		//���@
#include "bg.h"			//�w�i
#include "bullet.h"		//�e
#include "enemy.h"		//�G
//#include "enemy2.h"		//�G2
#include "fade.h"		//�t�F�[�h
//#include "sound.h"		//��
#include "brock.h"		//�u���b�N
#include "title.h"		//�^�C�g��
#include "tutorial.h"	//�`���[�g���A��
#include "game.h"		//�Q�[��
#include "result.h"		//���U���g
#include "allscore.h"	//�Ō�̃X�R�A
#include "timer.h"		//�^�C�}�[

//================
//�v���g�^�C�v�錾
//================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
//void DrawFPS(void);

//===============
//�O���[�o���ϐ�
//===============
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;				//�t�H���g�ւ̃|�C���^
int g_nCountFPS;						//FPS�J�E���^
MODE g_mode = MODE_TITLE;				//���[�h�̎��

//==========
//���C���֐�
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
		CLASS_NAME,		//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_EXCLAMATION),
	};
	HWND hWnd;
	MSG msg;

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̍쐬
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,				//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,			//�E�B���h�E�̖��O
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

	DWORD dwExecLastTime;	//�������s�ŏI����
	DWORD dwFPSLastTime;	//FPS�v���ŏI����
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwFrameCount;		//�t���[���J�E���g

	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
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
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime >= 500))
			{	//�O�D�T�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
		}
		if ((dwCurrentTime - dwExecLastTime) > (1000/60))
		{
		dwExecLastTime = dwCurrentTime;

		//�X�V����
		Update();

		//�`�揈��
		Draw();

		dwFrameCount++;
		}
	}

	//�I������
	Uninit();

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(
		CLASS_NAME,		//�E�B���h�E�N���X�̖��O
		wcex.hInstance);

	return (int)msg.wParam;
}

//======================
//�E�B���h�E�v���V�[�W��
//======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	switch (uMsg)
	{
	case WM_DESTROY:			//�E�B���h�E��j������
		PostQuitMessage(0);		//WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "�I�����܂����H", "�^�C�g��", MB_YESNOCANCEL | MB_ICONASTERISK);
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

	case WM_CLOSE:					//�~�{�^���Ŋm�F�\��
		nID = MessageBox(NULL, "�I�����܂����H", "�^�C�g��", MB_YESNOCANCEL | MB_ICONASTERISK);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//YES�����������
		}
		else
		{
			return 0;	//����ȊO�̓E�B���h�E�͕��Ȃ�
		}
		break;

	case WM_KEYDOWN:	//�L�[�������Ƃ��̃��b�Z�[�W
		switch (wParam)
		{
		case VK_UP:
			//�����̈�������I�ɔ���������
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_RIGHT:
			//nPosy++;
			//�����̈�������I�ɔ���������
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_ESCAPE://�G�X�P�[�v�L�[�ŕ\��
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
//����������
//----------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
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

	//Direct3D�f�o�C�X�̐���
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);				//�J�����O�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//�A���t�@�l�̍����̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//�\�[�X�̍������@�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//�f�X�e�B�l�[�V�����̍������@�̐ݒ�

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//�k�����@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//�g�厞�@���
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U�l�@�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//V�l�@�J��Ԃ�

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//�A���t�@�l�̍���
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DXCreateFont(g_pD3DDevice, 8, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&g_pFont);

	//�L�[�{�[�h�̏���������
	InitKeyboard(hInstance,hWnd);

	//�Q�[����ʂ̏���������
	SetMode(g_mode);

	//�t�F�[�h�̏���������
	InitFade(g_mode);

	//�T�E���h�̏���������
	//InitSound(hWnd);

	////�T�E���h���Đ�
	//PlaySound(SOUND_LABEL_BGM003);

	return S_OK;
}

//----------------------
//�I������
//----------------------
void Uninit(void)
{
	//�T�E���h�̏I������
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

	//�t�F�[�h�̊J��
	UninitFade();

	//�L�[�{�[�h�̊J��
	UninitKeyboard();

	//Direct�f�o�C�X�̊J��
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
//�X�V����
//----------------------
void Update(void)
{
	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�t�F�[�h�̍X�V����
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
//�`�揈��
//----------------------
void Draw(void)
{
	//�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),1.0f,0);

	//�`��̊J�n
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

		//�t�F�[�h�̕`�揈��
		DrawFade();

		////FPS�̕`��
		//DrawFPS();

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//void DrawFPS(void)
//{
//	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
//	char astr[256];
//
//	wsprintf(&astr[0], "FPS:%d\n", g_nCountFPS);
//
//	//�e�L�X�g�̕`��
//	g_pFont->DrawText(NULL, &astr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	//�f�o�C�X�̎擾
	return g_pD3DDevice;
}

//���[�h�̐ݒ�
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
