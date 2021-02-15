//======================
//
//game�̏���
//Author:uneno rui
//
//======================
#include "main.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy2.h"
#include "score.h"
//#include "sound.h"
#include "bg.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"
#include "pause.h"
#include "allscore.h"
#include "brock.h"
#include "timer.h"

//===============
//�O���[�o���ϐ�
//===============
bool g_bPause;			//�|�[�Y�����ǂ���

//----------------------
//�Q�[����ʂ̏���������
//----------------------
HRESULT InitGame(void)
{
	//�w�i�̏���������
	InitBg();

	//�u���b�N�̏�����
	InitBrock();

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�G�̏���������
	InitEnemy2();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�^�C�}�[�̏���������
	InitTimer();

	//�X�R�A�̏���������
	InitScore();

	//�u���b�N�̐ݒu�ꏊ
	SetBrock(D3DXVECTOR3(0, 750, 0), 0);

	//�G�̏o���ꏊ
	SetEnemy(D3DXVECTOR3(800, 665, 0), 0);

	//�G�̏o���ꏊ
	SetEnemy2(D3DXVECTOR3(800, 165, 0), 0);

	//�|�[�Y�̏���������
	InitPause();

	////�T�E���h���Đ�
	//PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//----------------------
//�Q�[����ʂ̏I������
//----------------------
void UninitGame(void)
{
	//�T�E���h�̒�~
	//StopSound();

	//�|�[�Y�̏I������
	UninitPause();

	//�X�R�A�̏I������
	UninitScore();

	//�^�C�}�[�̏I������
	UninitTimer();

	//�����̏I������
	UninitExplosion();

	//�e�̏I������
	UninitBullet();

	//�G�̏I������
	UninitEnemy();

	//�G�̏I������
	UninitEnemy2();

	//�v���C���[�̏I������
	UninitPlayer();

	//�u���b�N�̊J��
	UninitBrock();

	//�w�i�̏I������
	UninitBg();
}

//----------------------
//�Q�[����ʂ̍X�V����
//----------------------
void UpdateGame(void)
{
	ENEMY *pEnemy;
	ENEMY2 *pEnemy2;
	PLAYER *pPlayer;
	/*TIMER *pTimer;*/

	pEnemy = GetEnemy();
	pEnemy2 = GetEnemy2();

	pPlayer = GetPlayer();
	//pTimer = GetTimer();

	int nFade = GetFade();

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == true)
	{	//TRUE�Ȃ�|�[�Y
		UpdatePause();
	}
	else
	{	//FALSE�Ȃ�ʏ�ʂ�
		//�w�i�̍X�V����
		UpdateBg();

		//�u���b�N�̍X�V����
		UpdateBrock();

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�G�̍X�V����
		UpdateEnemy2();

		//�e�̍X�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateExplosion();

		//�^�C�}�[�̍X�V����
		UpdateTimer();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�t�F�[�h�̍X�V����
		if (pEnemy->bUse == false || pPlayer->bUse == false)
		{
			if (nFade == FADE_IN)
			{
				SetFade(FADE_NONE, MODE_GAME);
			}
			else if (nFade == FADE_NONE)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}
		}
	}
}

//----------------------
//�Q�[����ʂ̕`�揈��
//----------------------
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();

	//�u���b�N�̕`��
	DrawBrock();		

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();

	//�G2�̕`�揈��
	DrawEnemy2();

	//�e�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

	//�^�C�}�[�̕`�揈��
	DrawTimer();

	//�X�R�A�̕`�揈��
	DrawScore();

	//�|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}

void SetPause(bool bPause)
{
}