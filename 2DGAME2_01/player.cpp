//======================
//
//player�̏���
//Author:uneno rui
//
//======================
//�C���N���[�h�t�@�C��
//====================
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy2.h"

//==============
//�}�N����`
//==============
#define PLAYER_WIDTH (100)			//��
#define PLAYER_HEIGHT (150)			//�c

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���A�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�̃|�C���^
PLAYER g_PosPlayer;
D3DXVECTOR3 g_rotPlayer;
float g_fLengthPlayer;		//�Ίp���̒���
float g_fAnglePlayer;		//�Ίp���̊p�x

//====================
//�v���C���[�̏���������
//====================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player000.png", &g_pTexturePlayer);

	//�ϐ�������
	g_PosPlayer.nCnterAnim = 0;
	g_PosPlayer.nPatternAnim = 0;
	g_PosPlayer.nPatternnSeatAnim = 0;
	g_PosPlayer.pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	g_PosPlayer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosPlayer.bUse = true;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�v���C���[�̏����ʒu
	g_PosPlayer.pos = D3DXVECTOR3(100,600, 0.0f);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(PLAYER_WIDTH - 50, PLAYER_HEIGHT - 50, 0.0f);	//�Ō�2D��0.0�Œ�
	pVtx[1].pos = D3DXVECTOR3(PLAYER_WIDTH - 50, PLAYER_HEIGHT + 50, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PLAYER_WIDTH + 50, PLAYER_HEIGHT - 50, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PLAYER_WIDTH + 50, PLAYER_HEIGHT + 50, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//==================
//�v���C���[�̏I������
//==================
void UninitPlayer(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//====================
//�v���C���[�̍X�V����
//====================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;
	pPlayer = &g_PosPlayer;

	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	ENEMY2 *pEnemy2;
	pEnemy2 = GetEnemy2();

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);	//���b�N

	if(pPlayer->bUse == true)
	{
	g_PosPlayer.nCnterAnim;				//�A�j���[�V�����J�E���^�[�X�V

	//�Ίp���̒���
	g_fLengthPlayer = sqrtf(30 * 30 + 60 * 60);

	//�Ίp���̊p�x
	g_fAnglePlayer = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);

	//if (g_PosPlayer.bUse == false)
	//{
		//�E������
		if (GetKeyboardPress(DIK_D) == true)
		{
			//�ړ���
			g_PosPlayer.move.x += 4.0f;
			if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W) == true)
			{
				pVtx[0].tex = D3DXVECTOR2(0.25f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.50f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.50f, 0.0f);
			}
			else
			{	
				//�A�j���[�V����
				if((g_PosPlayer.nCnterAnim % 5) == 0)
				g_PosPlayer.nPatternAnim = (g_PosPlayer.nPatternAnim + 1) % 5;

				pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 0.0f);
			}
		}

		//��������
		if (GetKeyboardPress(DIK_A) == true)
		{
			//�ړ���
			g_PosPlayer.move.x += -4.0f;
			if (GetKeyboardPress(DIK_A) && GetKeyboardPress(DIK_W) == true)
			{
				pVtx[0].tex = D3DXVECTOR2(0.25f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f, 0.5f);
				pVtx[2].tex = D3DXVECTOR2(0.50f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.50f, 0.5f);
			}
			else
			{
				//�A�j���[�V����
				if ((g_PosPlayer.nCnterAnim % 5) == 0)
				{
					g_PosPlayer.nPatternAnim = (g_PosPlayer.nPatternAnim + 1) % 5;

					pVtx[0].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(0.0f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
					pVtx[2].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(0.25f + 0.25f*g_PosPlayer.nPatternAnim, 0.5f);
				}
			}
		}

		//�W�����v
		if (GetKeyboardTrigger(DIK_W) == true && g_PosPlayer.pos.y >= 600)
		{
			//�ړ���
			g_PosPlayer.move.y -= 25.0f;
			//if (GetKeyboardPress(DIK_W) == true)	//��������
			//{
			//	g_PosPlayer.move.y -= 2.0f;
			//}
		}

		//������
		if (GetKeyboardTrigger(DIK_LEFT) == true)
		{
			D3DXVECTOR3 move;
			move = D3DXVECTOR3(-8.0f, 0.0f, 0.0f);
			SetBullet(g_PosPlayer.pos, move, 10);
		}

		//�E����
		if (GetKeyboardTrigger(DIK_RIGHT) == true)
		{
			D3DXVECTOR3 move;
			move = D3DXVECTOR3(8.0f, 0.0f, 0.0f);
			SetBullet(g_PosPlayer.pos, move, 10);
		}

		//�㔭��
		if (GetKeyboardTrigger(DIK_UP) == true)
		{
			D3DXVECTOR3 move;
			move = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
			SetBullet(g_PosPlayer.pos, move, 10);
		}

		//�d��
		g_PosPlayer.move.y += 1.0f;

		////�ʒu�X�V
		g_PosPlayer.pos.x += g_PosPlayer.move.x;
		g_PosPlayer.pos.y += g_PosPlayer.move.y;

		//�ړ��ʂ̌���
		g_PosPlayer.move.x += (0.0f - g_PosPlayer.move.x) *0.5f;

		//�d�Ȃ�����I���
		if (pPlayer->pos.x +30 >= pEnemy->pos.x -30 &&
			pPlayer->pos.x -30 <= pEnemy->pos.x +30 &&
			pPlayer->pos.y + 30 >= pEnemy->pos.y - 30 &&
			pPlayer->pos.y - 30 <= pEnemy->pos.y + 30)
		{
			pPlayer->bUse = false;
		}

		//if (pPlayer->pos.x + 30 >= pEnemy2->pos.x - 30 &&
		//	pPlayer->pos.x - 30 <= pEnemy2->pos.x + 30 &&
		//	pPlayer->pos.y + 30 >= pEnemy2->pos.y - 30 &&
		//	pPlayer->pos.y - 30 <= pEnemy2->pos.y + 30)
		//{
		//	pPlayer->bUse = false;
		//}

		//��ʊO�`�F�b�N
		if (g_PosPlayer.pos.y < (0 + 150 / 2))				//��[
		{
			g_PosPlayer.pos.y = (0 + 150 / 2);
		}

		if (g_PosPlayer.pos.x < (0 + 200 / 2))				//���[
		{
			//g_PosPlayer.pos.x = ( 0 +100 / 2);
			g_PosPlayer.pos.x = (0 + 200 / 2);
			//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
		}

		if (g_PosPlayer.pos.y > (SCREEN_HEIGHT - 300 / 2))	//���[
		{
			g_PosPlayer.move.y = 0.0f;						//�n�ʂ̍����ɖ߂�
			g_PosPlayer.pos.y = (SCREEN_HEIGHT - 300 / 2);
		}

		if (g_PosPlayer.pos.x > (SCREEN_WIDTH - 100 / 2))	//�E�[
		{
			//g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			g_PosPlayer.pos.x = (SCREEN_WIDTH - 100 / 2);
			//g_PosPlayer.pos.x = (0 + 100 / 2);
		}

		pVtx[0].pos.x = g_PosPlayer.pos.x + sinf(g_rotPlayer.z - g_fAnglePlayer)*g_fLengthPlayer;
		pVtx[0].pos.y = g_PosPlayer.pos.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[0].pos.z = 0.0f;

		pVtx[1].pos.x = g_PosPlayer.pos.x - sinf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
		pVtx[1].pos.y = g_PosPlayer.pos.y - cosf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
		pVtx[1].pos.z = 0.0f;

		pVtx[2].pos.x = g_PosPlayer.pos.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.y = g_PosPlayer.pos.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[2].pos.z = 0.0f;

		pVtx[3].pos.x = g_PosPlayer.pos.x - sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.y = g_PosPlayer.pos.y - cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
		pVtx[3].pos.z = 0.0f;

	}
	g_pVtxBuffPlayer->Unlock();	//�A�����b�N
}

//==================
//�v���C���[�̕`�揈��
//==================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *pPlayer;
	pPlayer = &g_PosPlayer;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	if (pPlayer->bUse == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

PLAYER * GetPlayer(void)
{
	return &g_PosPlayer;
}

