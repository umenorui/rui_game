//======================
//
//enemy�̏���
//Author:uneno rui
//
//======================
//�C���N���[�h�t�@�C��
//====================
#include "enemy.h"
//#include "sound.h"
#include "score.h"
#include "explosion.h"
#include "input.h"
#include "player.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;			//���_�o�b�t�@�̃|�C���^
ENEMY g_aEnemy[MAX_ENEMYTYPE];							//�G�̏��
D3DXVECTOR3 g_PosEnemy;		//�ꏊ
D3DXVECTOR3 g_rotEnemy;
D3DXVECTOR3 g_moveEnemy;	//�ړ���

//================
//�G�̏���������
//================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy001.png", &g_pTextureEnemy);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy002.png", &g_pTextureEnemy);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/enemy003.png", &g_pTextureEnemy);

	//enemyHP
	g_aEnemy[0].nLife = ENEMYLIFE1;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_ENEMYTYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̏����ʒu
	g_PosEnemy = D3DXVECTOR3(600, 665, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMYTYPE; nCountEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//----------------------
//�G�̏I������
//----------------------
void UninitEnemy(void)
{
	//�T�E���h�̒�~
	//StopSound();

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureEnemy != NULL)
	{
		g_pTextureEnemy->Release();
		g_pTextureEnemy = NULL;
	}
}

//----------------------
//�G�̍X�V����
//----------------------
void UpdateEnemy(void)
{
	ENEMY *pEnemy;

	pEnemy = &g_aEnemy[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		g_aEnemy[0].pos.x -= 1.0;	//����������

	g_PosEnemy = D3DXVECTOR3(700, 400, 0.0f);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMYTYPE; nCountEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pEnemy->nCnterAnim++;

			if ((pEnemy->nCnterAnim % 3) == 0)
			{
				pEnemy->nPatternAnim = (pEnemy->nPatternAnim + 1) % 3;
			}

			//���_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy->nPatternAnim, 1.0f);		//����
			pVtx[1].tex = D3DXVECTOR2(0.0f + 0.5f*pEnemy->nPatternAnim, 0.0f);		//����
			pVtx[2].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy->nPatternAnim, 1.0f);		//�E��
			pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f*pEnemy->nPatternAnim, 0.0f);		//�E��

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x - 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCountEnemy].pos.x + 50, g_aEnemy[nCountEnemy].pos.y - 50, 0.0f);

			if (g_PosEnemy.x < (0 + 200 / 2))				//���[
			{
				//g_PosPlayer.pos.x = ( 0 +100 / 2);
				g_PosEnemy.x = (SCREEN_WIDTH - 100 / 2);
				//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			}

			switch (g_aEnemy[0].state)
			{
			case ENEMYSTATE_DAMAGE:
				g_aEnemy[0].nCounterState--;
				if (g_aEnemy[0].nCounterState <= 0)
				{
					g_aEnemy[0].state = ENEMYSTATE_NORMAL;
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
	g_pVtxBuffEnemy->Unlock();
}

//----------------------
//�G�̕`�揈��
//----------------------
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEnemy);

	for (int nCountEnemy = 0; nCountEnemy < MAX_ENEMYTYPE; nCountEnemy++)
	{
		if (g_aEnemy[nCountEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountEnemy,
				2);
		}
		nCountEnemy += 4;
	}
}

void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	//�e�̐ݒ�
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountENEMY = 0; nCountENEMY < MAX_ENEMYTYPE; nCountENEMY++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//�ʒu��ݒ�
			g_aEnemy[nCountENEMY].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x - 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCountENEMY].pos.x + 50 + (40 * nCountENEMY), g_aEnemy[nCountENEMY].pos.y - 50, 0.0f);

			pEnemy->bUse = true;
			break;
		}
		pVtx += 4;
	}
}

ENEMY * GetEnemy(void)
{
	return &g_aEnemy[0];
}

bool HitEnemy(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nIdx].nLife -= nDamage;	//�̗͂����炷
	if (g_aEnemy[nIdx].nLife <= 0)		//�O�ȉ��ŉ��̏���������
	{
		//����
		SetExplosion(g_aEnemy->pos);

		//���ʉ�
		//PlaySound(SOUND_LABEL_SE_EXPLOSION);

		//�X�R�A�̉��Z
		AddScore(5000);

		//�G���g��Ȃ�
		g_aEnemy[nIdx].bUse = false;

		return true;
	}
	else
	{
	//	//���ʉ�
		//PlaySound(SOUND_LABEL_SE_HIT);

		//�_��
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 5;

		//�F
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		return false;
	}
	g_pVtxBuffEnemy->Unlock();
}