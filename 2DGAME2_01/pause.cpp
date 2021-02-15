//======================
//
//�|�[�Y�̏���
//Author:uneno rui
//
//======================
#include "Pause.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;			//�e�N�X�`���A�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//���_�o�b�t�@�̃|�C���^

HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg003.jpg", &g_pTexturePause);

	//���_�o�b�t�@�̐���
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
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//����
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//����
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);		//�E��
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);		//�E��

	g_pVtxBuffPause->Unlock();

	return S_OK;
}

void UninitPause(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	//�e�N�X�`���A�̊J��
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

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}