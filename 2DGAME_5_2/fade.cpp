//======================
//
//fade�̏���
//Author:uneno rui
//
//======================
#include "fade.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;			//�e�N�X�`���A�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;		//���_�o�b�t�@�̃|�C���^
FADE g_fade;										//�t�F�[�h�̏��
MODE g_modeNext;									//���̃��[�h�i��ʁj
D3DXCOLOR g_colorFade;								//�t�F�[�h�F

//================
//����������
//================
HRESULT InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg000.jpg", &g_pTextureFade);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0, 800, 0);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
	pVtx[2].pos = D3DXVECTOR3(1000, 800, 0);
	pVtx[3].pos = D3DXVECTOR3(1000, 0, 0);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//����
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//����
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);		//�E��
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);		//�E��

	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//----------------------
//�I������
//----------------------
void UninitFade(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
}

//----------------------
//�X�V����
//----------------------
void UpdateFade(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (g_fade == FADE_NONE)
	{
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.025f;
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);
		if (g_colorFade.a <= 0.0f)
		{
			g_fade = FADE_NONE;
		}
	}
	else if (g_fade == FADE_OUT)
	{
		g_colorFade.a += 0.025f;
		pVtx[0].col = D3DXCOLOR(g_colorFade);
		pVtx[1].col = D3DXCOLOR(g_colorFade);
		pVtx[2].col = D3DXCOLOR(g_colorFade);
		pVtx[3].col = D3DXCOLOR(g_colorFade);
		if (g_colorFade.a >= 1.0f)
		{
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
	g_pVtxBuffFade->Unlock();
}

//----------------------
//�`�揈��
//----------------------
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}

FADE GetFade(void)
{
	return g_fade;
}
