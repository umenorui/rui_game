#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_
#define DIRECIINPUT_VERSION (0x0800)
//�C���N���[�h�t�@�C��
#include <windows.h>
#include "d3dx9.h"						//�`�揈���ɕK�v
#include "dinput.h"						//���͏����ɕK�v
#include "xaudio2.h"					//�T�E���h�Đ��ɕK�v

//----------------------
//���C�u�����̃����N
//----------------------
#pragma comment(lib, "d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")		//�g�����C�u����
#pragma comment(lib, "dxguid.lib")		//�R���|�[�l���g�g�p�ɕK�v

//���C�u�����t�@�C��
#pragma comment(lib,"dinput8.lib")		//���͏����ɕK�v
#pragma comment(lib,"winmm.lib")

//----------------------
//�}�N����`
//----------------------
#define SCREEN_WIDTH (1000)			//��
#define SCREEN_HEIGHT (800)			//�c
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME	"WINDOWCLASS"	//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME	"wind"			//�E�C���h�E�̖��O
#define WINDOW_POS_X (100)			//X�n�_
#define WINDOW_POS_Y (100)			//Y�n�_
#define ID_TIMER (121)				//�^�C�}�[
#define TIMER_INTERVAL (1000/60)	//�^�C�}�[�����Ԋu
#define nNumber (3)					//
#define ID_BUTTON000 (101)			

//----------------------
//�\����
//----------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//�P�D�O�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

//----------------------
//���[�h�̐ݒ�
//----------------------
typedef enum
{
	MODE_TITLE = 0,	//�^�C�g�����
	MODE_TUTORIAL,	//�`���[�g���A�����
	MODE_GAME,		//�Q�[�����
	MODE_RESULT,	//���U���g���
	MODE_MAX
}MODE;

//----------------------
//�v���g�^�C�v�錾
//----------------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif
