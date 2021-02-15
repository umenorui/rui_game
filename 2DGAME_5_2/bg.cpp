//======================
//
//bg�̏���
//Author:uneno rui
//
//======================
#include "bg.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureBg = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//���_�o�b�t�@�̃|�C���^

//================
//�w�i�̏���������
//================
HRESULT InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg001.jpg", &g_pTextureBg);

	//���_�o�b�t�@�̐���
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

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0,800,0);
		pVtx[1].pos = D3DXVECTOR3(0,0,0);
		pVtx[2].pos = D3DXVECTOR3(1000,800,0);
		pVtx[3].pos = D3DXVECTOR3(1000,0,0);

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

	g_pVtxBuffBg->Unlock();

	return S_OK;
}

//----------------------
//�w�i�̏I������
//----------------------
void UninitBg(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureBg != NULL)
	{
		g_pTextureBg->Release();
		g_pTextureBg = NULL;
	}
}

//----------------------
//�w�i�̍X�V����
//----------------------
void UpdateBg(void)
{
}

//----------------------
//�w�i�̕`�揈��
//----------------------
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBg);

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

