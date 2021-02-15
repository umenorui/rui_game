//======================
//
//enemy2�̏���
//Author:uneno rui
//
//======================
//�C���N���[�h�t�@�C��
//====================
#include "enemy2.h"
//#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "input.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureEnemy2 = NULL;				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy2 = NULL;			//���_�o�b�t�@�̃|�C���^
ENEMY2 g_aEnemy2[MAX_ENEMY2TYPE];							//�G�̏��
D3DXVECTOR3 g_PosEnemy2;		//�ꏊ
D3DXVECTOR3 g_rotEnemy2;
D3DXVECTOR3 g_moveEnemy2;	//�ړ���

//================
//�G�̏���������
//================
HRESULT InitEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_pTextureEnemy2);

	//enemyHP
	g_aEnemy2[0].nLife = ENEMY2LIFE1;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_ENEMY2TYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy2,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̏����ʒu
	g_PosEnemy2 = D3DXVECTOR3(600, 465, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY2TYPE; nCountEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//����
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//����
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);	//�E��
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);	//�E��

		pVtx += 4;
	}
	g_pVtxBuffEnemy2->Unlock();

	return S_OK;
}

//----------------------
//�G�̏I������
//----------------------
void UninitEnemy2(void)
{
	//�T�E���h�̒�~
	//StopSound();

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy2 != NULL)
	{
		g_pVtxBuffEnemy2->Release();
		g_pVtxBuffEnemy2 = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureEnemy2 != NULL)
	{
		g_pTextureEnemy2->Release();
		g_pTextureEnemy2 = NULL;
	}
}

//----------------------
//�G�̍X�V����
//----------------------
void UpdateEnemy2(void)
{
	ENEMY2 *pEnemy2;
	pEnemy2 = &g_aEnemy2[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy2[0].pos.x -= 2.0;						//������

	g_PosEnemy2 = D3DXVECTOR3(700, 400, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY2TYPE; nCountEnemy++, pEnemy2++)
	{
		if (pEnemy2->bUse == true)
		{
			pEnemy2->nCnterAnim++;

			if ((pEnemy2->nCnterAnim % 3) == 0)
			{
				pEnemy2->nPatternAnim = (pEnemy2->nPatternAnim + 1) % 3;
			}

			//���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy2->nPatternAnim, 1.0f);		//����
			pVtx[1].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy2->nPatternAnim, 0.0f);		//����
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy2->nPatternAnim, 1.0f);		//�E��
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy2->nPatternAnim, 0.0f);		//�E��

																					//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x - 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy2[nCountEnemy].pos.x + 50, g_aEnemy2[nCountEnemy].pos.y - 50, 0.0f);

			if (g_PosEnemy2.x < (0 + 200 / 2))				//���[
			{
				//g_PosPlayer.pos.x = ( 0 +100 / 2);
				g_PosEnemy2.x = (SCREEN_WIDTH - 100 / 2);
				//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			}

			switch (g_aEnemy2[0].state)
			{
			case ENEMY2STATE_DAMAGE:
				g_aEnemy2[0].nCounterState--;
				if (g_aEnemy2[0].nCounterState <= 0)
				{
					g_aEnemy2[0].state = ENEMY2STATE_NORMAL;
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy2->Unlock();
}

//----------------------
//�G�̕`�揈��
//----------------------
void DrawEnemy2(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy2, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEnemy2);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMY2TYPE; nCountEnemy++)
	{
		if (g_aEnemy2[nCountEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountEnemy,
				2);
		}
		nCountEnemy += 4;
	}
}

void SetEnemy2(D3DXVECTOR3 pos, int nType)
{
	//�e�̐ݒ�
	ENEMY2 *pEnemy2;
	pEnemy2 = &g_aEnemy2[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountENEMY = 0; nCountENEMY < MAX_ENEMY2TYPE; nCountENEMY++, pEnemy2++)
	{
		if (pEnemy2->bUse == false)
		{
			//�ʒu��ݒ�
			g_aEnemy2[nCountENEMY].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy2[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy2[nCountENEMY].pos.y - 50, 0.0f);

			pEnemy2->bUse = true;
			break;
		}
		pVtx += 4;
	}
}

ENEMY2 * GetEnemy2(void)
{
	return &g_aEnemy2[0];
}

bool HitEnemy2(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy2->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy2[nIdx].nLife -= nDamage;	//�̗͂����炷
	if (g_aEnemy2[nIdx].nLife <= 0)		//�O�ȉ��ŉ��̏���������
	{
		//����
		SetExplosion(g_aEnemy2->pos);

		//���ʉ�
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);

		//�X�R�A�̉��Z
		AddScore(8);

		//�G���g��Ȃ�
		g_aEnemy2[nIdx].bUse = false;

		return true;
	}
	else
	{
		//���ʉ�
		//PlaySound(SOUND_LABEL_SE_HIT);

		//�_��
		g_aEnemy2[nIdx].state = ENEMY2STATE_DAMAGE;
		g_aEnemy2[nIdx].nCounterState = 5;

		//�F
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		return false;
	}
	g_pVtxBuffEnemy2->Unlock();
}