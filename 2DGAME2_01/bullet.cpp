//======================
//
//bullet�̏���
//Author:uneno rui
//
//====================
//�C���N���[�h�t�@�C��
//====================
#include "bullet.h"
#include "enemy.h"
#include "enemy2.h"
#include "explosion.h"
//#include "sound.h"
#include "score.h"

//================
//�e�̍\����
//================
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ�
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
	BULLETTYPE type;	//���
} BULLET;

//================
//�O���[�o���ϐ�
//================
LPDIRECT3DTEXTURE9 g_pTextureBullet[MAX_BULLETTIPE] = {};	//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�̃|�C���^
BULLET g_aBullet[MAX_BULLET];								//�e�̏��

//================
//�e�̏���������
//================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet002.png", &g_pTextureBullet[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet001.png", &g_pTextureBullet[1]);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		g_aBullet[nCountBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCountBullet].nLife;
		g_aBullet[nCountBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10, g_aBullet[nCountBullet].pos.y + 10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 10, g_aBullet[nCountBullet].pos.y - 10, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10, g_aBullet[nCountBullet].pos.y + 10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 10, g_aBullet[nCountBullet].pos.y - 10, 0.0f);

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

		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
	return S_OK;
}

//----------------------
//�e�̏I������
//----------------------
void UninitBullet(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	//�e�N�X�`���A�̊J��
	for (int nCountBullet = 0; nCountBullet < MAX_BULLETTIPE; nCountBullet++)
	{
		if (g_pTextureBullet[nCountBullet] != NULL)
		{
			g_pTextureBullet[nCountBullet]->Release();
			g_pTextureBullet[nCountBullet] = NULL;
		}
	}
}

//----------------------
//�e�̍X�V����
//----------------------
void UpdateBullet(void)
{
	BULLET *pBullet;
	ENEMY *pEnemy;
	ENEMY2 *pEnemy2;
	pBullet = &g_aBullet[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			//�ʒu�̍X�V
			g_aBullet[nCountBullet].pos += pBullet->move;

			//�G�̓����蔻��
			pEnemy = GetEnemy();
			for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY; nCountEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{
					if (pEnemy->pos.y + 50 >= pBullet->pos.y &&
						pEnemy->pos.y - 50 <= pBullet->pos.y &&
						pEnemy->pos.x + 50 >= pBullet->pos.x &&
						pEnemy->pos.x - 50 <= pBullet->pos.x)
					{
						////�X�R�A�̉��Z
						AddScore(1000);

						//�e�̔j��
						pBullet->bUse = false;

						//�e�̃_���[�W
						HitEnemy(nCountEnemy, BULLETDAMAGE);
					}
				}
			}

			pEnemy2 = GetEnemy2();
			for (int nCountEnemy2 = 0; nCountEnemy2 < MAX_ENEMY; nCountEnemy2++, pEnemy++)
			{
				if (pEnemy2->bUse == true)
				{
					if (pEnemy2->pos.y + 50 >= pBullet->pos.y &&
						pEnemy2->pos.y - 50 <= pBullet->pos.y &&
						pEnemy2->pos.x + 50 >= pBullet->pos.x &&
						pEnemy2->pos.x - 50 <= pBullet->pos.x)
					{
						//�e�̔j��
						pBullet->bUse = false;

						////�X�R�A�̉��Z
						//AddScore(2000);

						//�e�̃_���[�W
						HitEnemy2(nCountEnemy2, BULLETDAMAGE);
					}
				}
			}

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 20, g_aBullet[nCountBullet].pos.y + 20, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 20, g_aBullet[nCountBullet].pos.y - 20, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 20, g_aBullet[nCountBullet].pos.y + 20, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 20, g_aBullet[nCountBullet].pos.y - 20, 0.0f);

			//�����`�F�b�N
			pBullet->nLife = 50;
		}
		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock();
}

//----------------------
//�e�̕`�揈��
//----------------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	for (int nCountBullet = 0; nCountBullet < MAX_BULLETTIPE; nCountBullet++)
	{
		pDevice->SetTexture(0, g_pTextureBullet[nCountBullet]);
	}

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++)
	{
		if (g_aBullet[nCountBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountBullet * 4,
				2);
		}
	}
}

//----------------
//�e�̐ݒ�
//----------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	VERTEX_2D *pVtx;

	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBullet = 0; nCountBullet < MAX_BULLET; nCountBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//�ʒu��ݒ�
			g_aBullet[nCountBullet].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 15, g_aBullet[nCountBullet].pos.y + 15, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x - 15, g_aBullet[nCountBullet].pos.y - 15, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 15, g_aBullet[nCountBullet].pos.y + 15, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCountBullet].pos.x + 15, g_aBullet[nCountBullet].pos.y - 15, 0.0f);

			//�ړ��ʂ�ݒ�
			pBullet->move = move;

			//������ݒ�
			pBullet->nLife = nLife;

			pBullet->bUse = true;

			break;
		}
		pVtx += 4;
	}
}

//==================
//�e�̒��_���W�̐ݒ�
//==================
void SetVertexBullet(int nIdx)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(60, 80, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(60, 20, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(120, 80, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(120, 20, 0.0f);

	g_pVtxBuffBullet->Unlock();
}