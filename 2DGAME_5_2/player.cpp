//======================
//
//player�̏���
//Author:uneno rui
//
//======================
#include "player.h"
#include "sound.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���A�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�̃|�C���^
D3DXVECTOR3 g_PosPlayer;
D3DXVECTOR3 g_rotPlayer;
D3DXVECTOR3 g_movePlayer;	//�ړ���
int g_nCounterAnim;			//�A�j���[�V�����̃J�E���^�[
int g_nPatternAnim;			//�A�j���[�V�����̃p�^�[��
int g_nseetAnim;
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
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player001.png", &g_pTexturePlayer);

	//�ϐ�������
	g_nCounterAnim = 0;
	g_nPatternAnim = 0;
	g_nseetAnim = 0;

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
	g_PosPlayer = D3DXVECTOR3(500, 650, 0.0f);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(200, 712, 0.0f);	//�Ō�2D��0.0�Œ�
	pVtx[1].pos = D3DXVECTOR3(200, 200, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(712, 712, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(712, 200, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

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

	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	g_nCounterAnim++;				//�A�j���[�V�����J�E���^�[�X�V
	//if ((g_nCounterAnim % 6) == 0)
	//{
	//g_nPatternAnim = (g_nPatternAnim + 1) % 8;

	//g_nseetAnim = (g_nseetAnim + 1) % 10;

	//pVtx[0].tex = D3DXVECTOR2(0.0f + 0.125f*g_nPatternAnim, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f + 0.125f*g_nPatternAnim, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.125f + 0.125f*g_nPatternAnim, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(0.125f + 0.125f*g_nPatternAnim, 0.0f);
	//}

	//�Ίp���̒���
	g_fLengthPlayer = sqrtf(20 * 20 + 60 * 60);
	//�Ίp���̊p�x
	g_fAnglePlayer = atan2f(150, 150);

	if (GetKeyboardPress(DIK_D) == true)
	{
		g_movePlayer.x += sinf(D3DX_PI*0.5f) * 1.0f;
	}

	////�E������
	//if (GetKeyboardPress(DIK_D) == true)
	//{
	//	//�ړ���
	//	g_movePlayer.x += sinf(D3DX_PI)*0.5f;
	//	g_PosPlayer.z += 0.0f;

	//	//�㉟����
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{
	//		//�ړ���
		//	g_PosPlayer.y += cosf(D3DX_PI) * -0.5f;
		//	g_PosPlayer.x += sinf(D3DX_PI) * 0.5f;
		//	g_PosPlayer.z += 0.0f;
		//}
		////��������
		//if (GetKeyboardPress(DIK_S) == true)
		//{
		//	//�ړ���
		//	g_PosPlayer.x += sinf(D3DX_PI) * -0.5f;
		//	g_PosPlayer.y += cosf(D3DX_PI) * 0.5f;
		//	g_PosPlayer.z += 0.0f;
		//}
	//}

	//��������
	if (GetKeyboardPress(DIK_A) == true)
	{
		//�ړ���
		g_movePlayer.x += -sinf(D3DX_PI*0.5f) * 1.0f;
	}

	//�㉟����
	if (GetKeyboardPress(DIK_W) == true)
	{	//�����ƈړ�
		//�ړ���
		g_movePlayer.y += -sin(D3DX_PI*0.5f)* 0.5f;
	}

	//��������
	if (GetKeyboardPress(DIK_S) == true)
	{	//�����ƈړ�
		//�ړ���
		g_movePlayer.y += sin(D3DX_PI*0.5f) * 0.5f;
	}

	////��]
	//if (GetKeyboardPress(DIK_K) == true)
	//{
	//	g_rotPlayer.z += (D3DX_PI / 18);
	//	if (g_rotPlayer.z > D3DX_PI)
	//	{
	//		g_rotPlayer.z -= D3DX_PI*2.0f;
	//	}
	//}

	//����
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		PlaySound(SOUND_LABEL_SE_SHOT);
		D3DXVECTOR3 move;
		move = D3DXVECTOR3(0.0f, cosf(D3DX_PI) * 6.5f, 0.0f);
		SetBullet(g_PosPlayer, move, 100);
	}

	pVtx[0].pos.x = g_PosPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer)*g_fLengthPlayer;
	pVtx[0].pos.y = g_PosPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_PosPlayer.x - sinf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
	pVtx[1].pos.y = g_PosPlayer.y - cosf(g_rotPlayer.z + g_fAnglePlayer)*g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_PosPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.y = g_PosPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_PosPlayer.x - sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].pos.y = g_PosPlayer.y - cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	//�ʒu�X�V
	g_PosPlayer.x += g_movePlayer.x;
	g_PosPlayer.y += g_movePlayer.y;

	//�ړ��ʂ̌���
	g_movePlayer.x += (0.0f - g_movePlayer.x) *0.05f;
	g_movePlayer.y += (0.0f - g_movePlayer.y) *0.05f;

	//��ʊO�`�F�b�N
	if (g_PosPlayer.y < (0 + 150 / 2))				//��[
	{
		g_PosPlayer.y = (0 + 150 / 2);
	}

	if (g_PosPlayer.x < (0 + 100 / 2))				//���[
	{
		g_PosPlayer.x = (0 + 100 / 2);
	}

	if (g_PosPlayer.y > (SCREEN_HEIGHT - 150 / 2))	//���[
	{
		g_PosPlayer.y = (SCREEN_HEIGHT - 150 / 2);
	}

	if (g_PosPlayer.x > (SCREEN_WIDTH - 100 / 2))	//�E�[
	{
		g_PosPlayer.x = (SCREEN_WIDTH - 100 / 2);
	}

	g_pVtxBuffPlayer->Unlock();
}

//==================
//�v���C���[�̕`�揈��
//==================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}