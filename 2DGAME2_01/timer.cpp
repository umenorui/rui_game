//======================
//
//timer�̏���
//Author:uneno rui
//
//======================
#include "timer.h"
#include "fade.h"

//===========
//�}�N����`
//===========
#define MAX_TYPE_TIMER (3)//�G�̎�ސ�
#define MAX_TIMER_SIZE (30)

//======================
//�O���[�o���ϐ�
//======================
LPDIRECT3DTEXTURE9 g_apTextureTimer = NULL;//�e�N�X�`���փ|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;//���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aTimer[MAX_TIMER];//�G�̏��
TIMER g_nTimer;//�X�R�A

HRESULT InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureTimer);

	g_nTimer.nTimer = 150;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		g_aTimer[nCntTimer] = D3DXVECTOR3(1390, 100, 0.0f);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x - MAX_TIMER_SIZE) + nCntTimer * 70, g_aTimer[nCntTimer].y + MAX_TIMER_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x - MAX_TIMER_SIZE) + nCntTimer * 70, g_aTimer[nCntTimer].y - MAX_TIMER_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x + MAX_TIMER_SIZE) + nCntTimer * 70, g_aTimer[nCntTimer].y + MAX_TIMER_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x + MAX_TIMER_SIZE) + nCntTimer * 70, g_aTimer[nCntTimer].y - MAX_TIMER_SIZE, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;	//4���_���Ƃ��炷
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

void UninitTimer(void)
{
	//�e�N�X�`���̊J��
	if (g_apTextureTimer != NULL)
	{
		g_apTextureTimer->Release();
		g_apTextureTimer = NULL;
	}


	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}
void UpdateTimer(void)
{
	VERTEX_2D *pVtx;

	int nNumber[8];

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	nNumber[5] = g_nTimer.nTimer % 1000 / 100;
	nNumber[6] = g_nTimer.nTimer % 100 / 10;
	nNumber[7] = g_nTimer.nTimer % 10 / 1;

	for (int nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x - MAX_TIMER_SIZE) + nCntTimer * 60, g_aTimer[nCntTimer].y + MAX_TIMER_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x - MAX_TIMER_SIZE) + nCntTimer * 60, g_aTimer[nCntTimer].y - MAX_TIMER_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x + MAX_TIMER_SIZE) + nCntTimer * 60, g_aTimer[nCntTimer].y + MAX_TIMER_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_aTimer[nCntTimer].x + MAX_TIMER_SIZE) + nCntTimer * 60, g_aTimer[nCntTimer].y - MAX_TIMER_SIZE, 0.0f);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.1f*nNumber[nCntTimer], 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f*nNumber[nCntTimer], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f*(nNumber[nCntTimer] + 1), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f*(nNumber[nCntTimer] + 1), 0.0f);

		if (g_nTimer.nTimer == 0)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}

		pVtx += 4;	//4���_���Ƃ��炷

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTimer->Unlock();
}

//==================
//�|���S���̕`�揈��
//==================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_apTextureTimer);

	//�|���S���̕`��
	for (int nCntTimer = 0; nCntTimer < MAX_TIMER; nCntTimer++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTimer * 4, 2);
	}

}

void AddTimer(int nValue)
{
	g_nTimer.nTimer += nValue;
}

TIMER *GetTimer(void)
{
	return &g_nTimer;
}