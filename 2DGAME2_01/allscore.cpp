//======================
//
//�Ō�̃X�R�A�̏���
//Author:uneno rui
//
//======================
#include "allscore.h"
#include "score.h"
#include "fade.h"
#include "input.h"
//#include "sound.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureAllscore = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAllscore = NULL;		//���_�o�b�t�@�̃|�C���^

//----------------------
//����������
//----------------------
HRESULT InitAllscore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	////�e�L�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg002.jpg", &g_pTextureAllscore);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAllscore,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffAllscore->Lock(0, 0, (void**)&pVtx, 0);

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

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//����
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//����
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);		//�E��
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);		//�E��

	g_pVtxBuffAllscore->Unlock();

	////�T�E���h���Đ�
	//PlaySound(SOUND_LABEL_BGM004);

	return S_OK;
}

//----------------------
//�I������
//----------------------
void UninitAllscore(void)
{
	////�T�E���h�̏I������
	//UninitSound();

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffAllscore != NULL)
	{
		g_pVtxBuffAllscore->Release();
		g_pVtxBuffAllscore = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureAllscore != NULL)
	{
		g_pTextureAllscore->Release();
		g_pTextureAllscore = NULL;
	}
}

//----------------------
//�X�V����
//----------------------
void UpdateAllscore(void)
{
	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (nFade == FADE_IN)
		{
			SetFade(FADE_NONE, MODE_ALLSCORE);
		}
		else if (nFade == FADE_NONE)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//----------------------
//�`�揈��
//----------------------
void DrawAllscore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffAllscore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureAllscore);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}