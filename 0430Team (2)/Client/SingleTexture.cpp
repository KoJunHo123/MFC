#include "stdafx.h"
#include "SingleTexture.h"
#include "Device.h"

CSingleTexture::CSingleTexture()
	: m_pTexInfo(nullptr)
{
}

CSingleTexture::~CSingleTexture()
{
	Release();
}

HRESULT CSingleTexture::Insert_Texture(const TCHAR * pFilePath,
										const TCHAR * pStateKey, 
										const int & iCount)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	// D3DXGetImageInfoFromFile : ������ �̹��� ���Ͽ� ���� ������ ���� D3DXIMAGE_INFO ����ü�� ����ϴ� �Լ�
	
	if (FAILED(D3DXGetImageInfoFromFile(pFilePath, &(m_pTexInfo->tImgInfo))))
	{
		Safe_Delete(m_pTexInfo);

		ERR_MSG(pFilePath);
		return E_FAIL;
	}

	// D3DPOOL_DEFAULT		: ���� ������ �޸𸮿� ����(�׷��� ī�� �޸�)
	// D3DPOOL_MANAGED		: DX�� ���� �ڿ��� �����ϰ� �׷��� �޸𸮸� ��������� �̸� RAM�� ���
	// D3DPOOL_SYSTEMMEM	: RAM�� �ڿ��� ����
	// D3DPOOL_SCRATCH		: RAM�� ���������� DX ��ġ�� �������� ����
	
	// D3DXCreateTextureFromFileEx : �̹��� ��� com ��ü�� �����ϴ� �Լ�
	if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(), 
		pFilePath, 
		m_pTexInfo->tImgInfo.Width,
		m_pTexInfo->tImgInfo.Height, 
		m_pTexInfo->tImgInfo.MipLevels, 
		0,		// 0�� �⺻���� �ؽ�ó ����, D3DUSAGE_RENDERTARGET : ���� Ÿ�ٿ� �ؽ�ó
		m_pTexInfo->tImgInfo.Format,		// �ؽ�ó�� �ȼ� ����
		D3DPOOL_MANAGED,		// �޸� POOL ���
		D3DX_DEFAULT,		// �̹��� ���͸� ���, �̹��� Ȯ��, ��� �� �ȼ��� ���ڶ�ų� ���� �� ��� �� ���ΰ�
		D3DX_DEFAULT,		// �Ӹ� �̿� �� �̹��� Ȯ��, ��� �� �ȼ��� ���ڶ�ų� ���� �� ��� �� ���ΰ�
		0,					// ������ ����, 0�� �ָ� �÷�Ű ��ȿȭ
		nullptr,			// m_pTexInfo->tImgInfo ���� ���
		nullptr,			// �ȷ�Ʈ(8��Ʈ ���� ARGB ���� ǥ���ϱ� ���� ����ü) �̹��� ���� �ּ�
		&(m_pTexInfo->pTexture))))
	{
		Safe_Delete(m_pTexInfo);

		ERR_MSG(L"Single Texture Load Failed");
		return E_FAIL;
	}
	
	return S_OK;
}

void CSingleTexture::Release()
{
	Safe_Release(m_pTexInfo->pTexture);
	Safe_Delete(m_pTexInfo);
}
