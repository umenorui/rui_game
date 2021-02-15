//======================
//
//explosion�̏���
//Author:uneno rui
//
//======================
#include "explosion.h"

#define MAX_EXPLOSION (256)	//�G�̎��

//====================
//�����̍\����
//====================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	int nCnterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;	//�A�j���[�V�����p�^�[��NO.
	bool bUse;			//�g�p���Ă��邩�ǂ���
}EXPLOSION;

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureExplosion =NULL;			//�e�N�X�`���A�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;		//���_�o�b�t�@�̃|�C���^
EXPLOSION g_aExplosion[MAX_EXPLOSION];					//�����̏��

//----------------------
//�����̏���������
//----------------------
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/explosion000.png", &g_pTextureExplosion);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		g_aExplosion[nCountExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCountExplosion].nCnterAnim = 0;
		g_aExplosion[nCountExplosion].nPatternAnim = 0;
		g_aExplosion[nCountExplosion].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 25, g_aExplosion[nCountExplosion].pos.y + 25, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 25, g_aExplosion[nCountExplosion].pos.y - 25, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 25, g_aExplosion[nCountExplosion].pos.y + 25, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 25, g_aExplosion[nCountExplosion].pos.y - 25, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);		//����
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);		//����
		pVtx[2].tex = D3DXVECTOR2(0.125f, 1.0f);	//�E��
		pVtx[3].tex = D3DXVECTOR2(0.125f, 0.0f);	//�E��

		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();

	return S_OK;
}

//----------------------
//�����̏I������
//----------------------
void UninitExplosion(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//----------------------
//�����̍X�V����
//----------------------
void UpdateExplosion(void)
{
	EXPLOSION *pExplosion;
	pExplosion = &g_aExplosion[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++,pExplosion++)
	{
		if (pExplosion->bUse == true)
		{
			pExplosion->nCnterAnim++;

			if ((pExplosion->nCnterAnim % 3) == 0)
			{
				pExplosion->nPatternAnim = (pExplosion->nPatternAnim + 1) % 8;
			}

			//���_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*pExplosion->nPatternAnim, 1.0f);		//����
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*pExplosion->nPatternAnim, 0.0f);		//����
				pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*pExplosion->nPatternAnim, 1.0f);		//�E��
				pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*pExplosion->nPatternAnim, 0.0f);		//�E��

			//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 330, pExplosion[nCntExplosion].pos.y + 130, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 330, pExplosion[nCntExplosion].pos.y - 130, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 530, pExplosion[nCntExplosion].pos.y + 130, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(pExplosion[nCntExplosion].pos.x + 530, pExplosion[nCntExplosion].pos.y - 130, 0.0f);
	
				if (pExplosion->nPatternAnim == 7)
				{
					pExplosion->bUse = false;
				}
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}

//----------------------
//�����̕`�揈��
//----------------------
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountExplosion * 4,
				2);
		}
	}
}

void SetExplosion(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountExplosion = 0; nCountExplosion < MAX_EXPLOSION; nCountExplosion++)
	{
		if (g_aExplosion[nCountExplosion].bUse == false)
		{
			//�ʒu��ݒ�
			g_aExplosion[nCountExplosion].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 20, g_aExplosion[nCountExplosion].pos.y + 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x - 20, g_aExplosion[nCountExplosion].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 20, g_aExplosion[nCountExplosion].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCountExplosion].pos.x + 20, g_aExplosion[nCountExplosion].pos.y - 20, 0.0f);

			g_aExplosion[nCountExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}
