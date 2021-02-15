//======================
//
//brock�̏���
//Author:uneno rui
//
//======================
//�C���N���[�h�t�@�C��
//====================
#include "brock.h"
#include "player.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureBrock = NULL;				//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBrock = NULL;			//���_�o�b�t�@�̃|�C���^
BROCK g_aBrock[MAX_BROCKTYPE];							//�G�̏��
D3DXVECTOR3 g_PosBrock;		//�ꏊ
D3DXVECTOR3 g_rotBrock;
D3DXVECTOR3 g_moveBrock;	//�ړ���

//================
//�u���b�N�̏���������
//================
HRESULT InitBrock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/block001.png", &g_pTextureBrock);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_BROCKTYPE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBrock,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	//�G�̏����ʒu
	//g_PosBrock = D3DXVECTOR3(900, 800, 0.0f);

	for (int nCountBrock = 0; nCountBrock < MAX_BROCKTYPE; nCountBrock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 50, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 50, g_aBrock[nCountBrock].pos.y - 50, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(20.0f, 1.0f);	//�E��
		pVtx[3].tex = D3DXVECTOR2(20.0f, 0.0f);	//�E��

		pVtx += 4;
	}
	g_pVtxBuffBrock->Unlock();

	return S_OK;
}

//----------------------
//�u���b�N�̏I������
//----------------------
void UninitBrock(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBrock != NULL)
	{
		g_pVtxBuffBrock->Release();
		g_pVtxBuffBrock = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureBrock != NULL)
	{
		g_pTextureBrock->Release();
		g_pTextureBrock = NULL;
	}
}

//----------------------
//�u���b�N�̍X�V����
//----------------------
void UpdateBrock(void)
{
	BROCK *pBrock;
	pBrock = &g_aBrock[0];
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountBrock = 0; nCountBrock < MAX_BROCKTYPE; nCountBrock++, pBrock++)
	{
		//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x - 50, g_aBrock[nCountBrock].pos.y - 50, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 1050, g_aBrock[nCountBrock].pos.y + 50, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBrock[nCountBrock].pos.x + 1050, g_aBrock[nCountBrock].pos.y - 50, 0.0f);

			//�����蔻��
			//if (pBrock->pos.x + 400 >= pPlayer->pos.x - 40 &&
			//	pBrock->pos.x - 40 <= pPlayer->pos.x + 40 &&
			//	pBrock->pos.y + 40 >= pPlayer->pos.y - 40 &&
			//	pBrock->pos.y - 40 <= pPlayer->pos.y + 40)
			//{
			//	//if (pBrock->pos.y + 100 <= pPlayer->pos.y &&)	//sita
			//	//{
			//	g_PosBrock.y = (SCREEN_WIDTH - 250 / 2);
			//	/*	pPlayer->move.y = 0.0;*/
			//		//pPlayer->pos.y = pBrock->pos.y + 100;
			//		//pPlayer->pos.x = pBrock->pos.x + 100;
			//	}
				//if (pBrock->pos.y - 100 <= pPlayer->pos.y)	//��
				//{	
				//	pPlayer->move.y = 0.0;
				//	pPlayer->pos.y = pBrock->pos.y - 100;
				//	//pPlayer->pos.x = pBrock->pos.x - 100;
				//}

			//}

			//if (pBrock->pos.y + 50 >= pPlayer->pos.y - 50 &&
			//	pBrock->pos.y - 50 <= pPlayer->pos.y + 50)
			//{
			//	if (pBrock->pos.x - 100 <= pPlayer->pos.x)	//hidari
			//	{
			////		pPlayer->pos.x = pBrock->pos.x - 100;
			//pPlayer->pos.y = pBrock->pos.y + 100;
			//	}
			//	if (pBrock->pos.y + 100 <= pPlayer->pos.y)	//migi
			//	{
			////		pPlayer->pos.x = pBrock->pos.x + 100;
			//pPlayer->pos.y = pBrock->pos.y - 100;
			//	}
			//}
			
		pVtx += 4;
	}
	g_pVtxBuffBrock->Unlock();
}

//----------------------
//�u���b�N�̕`�揈��
//----------------------
void DrawBrock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBrock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBrock);

	for (int nCountBrock = 0; nCountBrock < MAX_BROCKTYPE; nCountBrock++)
	{
		if (g_aBrock[nCountBrock].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCountBrock,
				2);
		}
		nCountBrock += 4;
	}
}

void SetBrock(D3DXVECTOR3 pos, int nType)
{
	//�e�̐ݒ�
	BROCK *pBrock;
	pBrock = &g_aBrock[0];

	VERTEX_2D *pVtx;
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountENEMY = 0; nCountENEMY < MAX_BROCKTYPE; nCountENEMY++, pBrock++)
	{
		if (pBrock->bUse == false)
		{
			//�ʒu��ݒ�
			g_aBrock[nCountENEMY].pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x - 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y + 100, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x - 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y - 100, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x + 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y + 100, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBrock[nCountENEMY].pos.x + 100 + (40 * nCountENEMY), g_aBrock[nCountENEMY].pos.y - 100, 0.0f);

			pBrock->bUse = true;
			break;
		}
		pVtx += 4;
	}
}