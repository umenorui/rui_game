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
#include "score.h"
#include "bg.h"
#include "explosion.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "Pause.h"

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

	//�v���C���[�̏���������
	InitPlayer();

	//�G�̏���������
	InitEnemy();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�X�R�A�̏���������
	InitScore();

	//�G�̏o���ꏊ
	SetEnemy(D3DXVECTOR3(100, 200, 0), 0);

	//�|�[�Y�̏���������
	InitPause();

	//�T�E���h���Đ�
	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//----------------------
//�Q�[����ʂ̏I������
//----------------------
void UninitGame(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�|�[�Y�̏I������
	UninitPause();

	//�X�R�A�̏I������
	UninitScore();

	//�����̏I������
	UninitExplosion();

	//�e�̏I������
	UninitBullet();

	//�G�̏I������
	UninitEnemy();

	//�v���C���[�̏I������
	UninitPlayer();

	//�w�i�̏I������
	UninitBg();
}

//----------------------
//�Q�[����ʂ̍X�V����
//----------------------
void UpdateGame(void)
{
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

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

		//�v���C���[�̍X�V����
		UpdatePlayer();

		//�G�̍X�V����
		UpdateEnemy();

		//�e�̍X�V����
		UpdateBullet();

		//�����̍X�V����
		UpdateExplosion();

		//�X�R�A�̍X�V����
		UpdateScore();

		//�t�F�[�h�̍X�V����
		if (pEnemy->bUse == false)
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

	//�v���C���[�̕`�揈��
	DrawPlayer();

	//�G�̕`�揈��
	DrawEnemy();
	
	//�e�̕`�揈��
	DrawBullet();

	//�����̕`�揈��
	DrawExplosion();

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
