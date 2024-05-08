#include "stdafx.h"
#include "MultiTexture.h"
#include "Device.h"

CMultiTexture::CMultiTexture()
	
{
}

CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::Get_Texture(const TCHAR * pStateKey, const int & iCount)
{
	auto	iter = find_if(m_mapMultiTex.begin(), m_mapMultiTex.end(), [&](auto& MyPair)->bool
	{
		if (pStateKey == MyPair.first)
			return true;

		return false;

	});

	if (iter == m_mapMultiTex.end())
		return nullptr;

	return iter->second[iCount];
}

HRESULT CMultiTexture::Insert_Texture(const TCHAR * pFilePath,
										const TCHAR * pStateKey, 
										const int & iCount)
{
	// ����� ���̴� 520 byte�� ���� �� ����
	TCHAR		szFullPath[MAX_PATH] = L"";
	
	for (int i = 0; i < iCount; ++i)
	{
		swprintf_s(szFullPath, pFilePath, i);

		 TEXINFO* pTexInfo = new TEXINFO;
		 ZeroMemory(pTexInfo, sizeof(TEXINFO));

		// D3DXGetImageInfoFromFile : ������ �̹��� ���Ͽ� ���� ������ ���� D3DXIMAGE_INFO ����ü�� ����ϴ� �Լ�

		if (FAILED(D3DXGetImageInfoFromFile(szFullPath, &(pTexInfo->tImgInfo))))
		{
			Safe_Delete(pTexInfo);

			ERR_MSG(szFullPath);
			return E_FAIL;
		}

		// D3DPOOL_DEFAULT		: ���� ������ �޸𸮿� ����(�׷��� ī�� �޸�)
		// D3DPOOL_MANAGED		: DX�� ���� �ڿ��� �����ϰ� �׷��� �޸𸮸� ��������� �̸� RAM�� ���
		// D3DPOOL_SYSTEMMEM	: RAM�� �ڿ��� ����
		// D3DPOOL_SCRATCH		: RAM�� ���������� DX ��ġ�� �������� ����

		// D3DXCreateTextureFromFileEx : �̹��� ��� com ��ü�� �����ϴ� �Լ�
		if (FAILED(D3DXCreateTextureFromFileEx(CDevice::Get_Instance()->Get_Device(),
			szFullPath,
			pTexInfo->tImgInfo.Width,
			pTexInfo->tImgInfo.Height,
			pTexInfo->tImgInfo.MipLevels,
			0,		// 0�� �⺻���� �ؽ�ó ����, D3DUSAGE_RENDERTARGET : ���� Ÿ�ٿ� �ؽ�ó
			pTexInfo->tImgInfo.Format,		// �ؽ�ó�� �ȼ� ����
			D3DPOOL_MANAGED,		// �޸� POOL ���
			D3DX_DEFAULT,		// �̹��� ���͸� ���, �̹��� Ȯ��, ��� �� �ȼ��� ���ڶ�ų� ���� �� ��� �� ���ΰ�
			D3DX_DEFAULT,		// �Ӹ� �̿� �� �̹��� Ȯ��, ��� �� �ȼ��� ���ڶ�ų� ���� �� ��� �� ���ΰ�
			0,					// ������ ����, 0�� �ָ� �÷�Ű ��ȿȭ
			nullptr,			// m_pTexInfo->tImgInfo ���� ���
			nullptr,			// �ȷ�Ʈ(8��Ʈ ���� ARGB ���� ǥ���ϱ� ���� ����ü) �̹��� ���� �ּ�
			&(pTexInfo->pTexture))))
		{
			Safe_Delete(pTexInfo);

			ERR_MSG(L"Multi Texture Load Failed");
			return E_FAIL;
		}

		m_mapMultiTex[pStateKey].push_back(pTexInfo);
	}

	
	
	return S_OK;
}

void CMultiTexture::Release()
{
	for_each(m_mapMultiTex.begin(), m_mapMultiTex.end(), [](auto& MyPair)
	{
		for_each(MyPair.second.begin(), MyPair.second.end(), Safe_Delete<TEXINFO*>);
		MyPair.second.clear();
	});

	m_mapMultiTex.clear();	
}
