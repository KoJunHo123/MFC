#include "stdafx.h"
#include "Device.h"

IMPLEMENT_SINGLETON(CDevice)

CDevice::CDevice() : m_pDevice(nullptr), m_pSDK(nullptr), m_pSprite(nullptr)
{
}

CDevice::~CDevice()
{
	Release();
}

HRESULT CDevice::Init_Device()
{
	m_pSDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	// GetDeviceCaps : ��ġ�� ���� ���� ������ �����Ͽ� ���� ������ �Լ�
	// D3DADAPTER_DEFAULT : ������ �������� �⺻ �׷��� ī�带 �ǹ�
	if (FAILED(m_pSDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		ERR_MSG(L"GetDeviceCaps Failed");
		return E_FAIL;
	}

	// ���ؽ� ���μ��� = ���� ��ȯ + ����(���) ����

	DWORD		vp(0);

	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	
	else
		vp |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	Set_Parameters(d3dpp);

	// CreateDevice : ��ġ�� ������ ��ü�� �����ϴ� �Լ�
	// CreateDevice(� �׷��� ī�带 ������ ���ΰ�, � ������ ��ġ�� ������ ���ΰ�, ��ġ�� ����� ������ �ڵ�, ���� ���, ��� ȯ��, ������ ��ü�� ���� ������)
	
	if (FAILED(m_pSDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pDevice)))
	{
		ERR_MSG(L"CreateDevice Failed");
		return E_FAIL;
	}

	// ��������Ʈ

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		ERR_MSG(L"CreateSprite Failed");
		return E_FAIL;
	}

	D3DXFONT_DESCW		tFontInfo;
	ZeroMemory(&tFontInfo, sizeof(D3DXFONT_DESCW));

	tFontInfo.Height = 7;
	tFontInfo.Width = 5;
	tFontInfo.Weight = FW_HEAVY;
	tFontInfo.CharSet = HANGEUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"�ü�");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		ERR_MSG(L"CreateFontIndirect Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::Render_Begin()
{
	m_pDevice->Clear(0,			// ��Ʈ�� ����
					nullptr,	// ��Ʈ �迭�� ù ��° �ּ�
					D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET,
					D3DCOLOR_ARGB(255, 0, 0, 255), // �� ������ ����
					1.f,	// ���� ������ �ʱ�ȭ ��
					0);		// ���ٽ� ������ �ʱ�ȭ ��

	m_pDevice->BeginScene();	// ���⼭���� �ĸ� ���ۿ� �׸��� ����
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

}

void CDevice::Render_End(HWND hWnd)
{
	m_pSprite->End();
	m_pDevice->EndScene();		// �ĸ� ���ۿ� �׸��Ⱑ ���� ����

	// �ĸ� ������ surface�� ���� ������ surface�� ��ȯ
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);

	// 1, 2 : D3DSWAPEFFECT_COPY ���� ����
	// 3 : null�� ��� Set_Parameters �Լ� �ȿ� ������ �ڵ�� �ڵ� ����
	// 4 : D3DSWAPEFFECT_COPY ���� ����
}

void CDevice::Release()
{	
	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
	Safe_Release(m_pSDK);
}

void CDevice::Set_Parameters(D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth  = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount  = 1;
	
	d3dpp.MultiSampleType    = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	// D3DSWAPEFFECT_DISCARD : ���� ü�� ���
	// D3DSWAPEFFECT_FLIP : ���� �ϳ��� �������鼭 ����ϴ� ���
	// D3DSWAPEFFECT_COPY : ���� ���۸��� ������ ���� ���
	
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// ��ġ�� ����� ������ �ڵ�
	d3dpp.hDeviceWindow = g_hWnd;

	d3dpp.Windowed = TRUE;	// â ��� �Ǵ� ��üȭ�� ��� ���� ����(TRUE : â ���)

	d3dpp.EnableAutoDepthStencil = TRUE;		// ���ٽ� ���ۿ� ���� ������ ���� ����
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	

	// ��ü ȭ�� ��� �� ����� ������� ���� ����
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

	// ������� �ÿ��� ���� ����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}
