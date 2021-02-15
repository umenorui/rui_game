//======================
//
//score�̏���
//Author:uneno rui
//
//======================
#include"main.h"
#include"score.h"
#include"enemy.h"
#include"enemy2.h"

//====================
//�O���[�o���ϐ�
//====================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			//�e�N�X�`���A�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�̃|�C���^
int g_nScore;										//�X�R�A
SCORE g_aSCORE[MAX_SCORE];							//score�̏��

//----------------------
//����������
//----------------------
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	g_nScore = 0;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_pTextureScore);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountScore = 0; nCountScore < MAX_SCORE; nCountScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(50.0f + 70.0f*nCountScore, 70.0, 0);
		pVtx[1].pos = D3DXVECTOR3(50.0f + 70.0f*nCountScore, 30.0, 0);
		pVtx[2].pos = D3DXVECTOR3(100.0f + 70.0f*nCountScore, 70.0, 0);
		pVtx[3].pos = D3DXVECTOR3(100.0f + 70.0f*nCountScore, 30.0, 0);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);	//����
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);	//����
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);//�E��
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);//�E��

		pVtx += 4;
	}
	g_pVtxBuffScore->Unlock();
	return S_OK;
}

//----------------------
//�I������
//----------------------
void UninitScore(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//�e�N�X�`���A�̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//----------------------
//�X�V����
//----------------------
void UpdateScore(void)
{

}

//----------------------
//�`�揈��
//----------------------
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾	
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (int nCountScore = 0; nCountScore < MAX_SCORE; nCountScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountScore * 4,
			2);
	}
}

void AddScore(int nValue)
{
	int nData = 10000000;
	int aNumber[8];
	g_nScore += nValue;

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// �X�R�A���i�[
	for (int nCount = 0; nCount < MAX_SCORE; nCount++)
	{
		aNumber[nCount] = g_nScore / nData % 10;
		nData /= 10;

		pVtx[0].tex = D3DXVECTOR2(0.0f + 0.1f * aNumber[nCount], 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0f + 0.1f * aNumber[nCount], 0.0);
		pVtx[2].tex = D3DXVECTOR2(0.1f + 0.1f * aNumber[nCount], 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.1f + 0.1f * aNumber[nCount], 0.0);

		pVtx += 4;
	}
	g_pVtxBuffScore->Unlock();
}