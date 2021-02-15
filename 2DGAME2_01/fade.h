#pragma once
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//----------------------
//�\����
//----------------------
typedef enum
{
	FADE_NONE = 0,	//�������Ă��Ȃ�
	FADE_IN,		//�t�F�[�h�C��
	FADE_OUT,		//�t�F�[�h�A�E�g
	FADE_MAX
}FADE;

//----------------------
//�v���g�^�C�v�錾
//----------------------
HRESULT InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade, MODE modeNext);
FADE GetFade(void);

#endif
