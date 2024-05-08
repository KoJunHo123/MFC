#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;
	D3DXVECTOR3		vDir;
	D3DXVECTOR3		vLook;
	D3DXVECTOR3		vSize;

	D3DXMATRIX		matWorld;
}INFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;   // �� ��ü

	D3DXIMAGE_INFO			tImgInfo;	// ����ü

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3	vPos;			// Ÿ���� ���� ��ǥ
	D3DXVECTOR3 vSize;			// Ÿ���� ����, ���� ������

	
	BYTE		byOption;		// 0, 1��(��ֹ�)
	BYTE		byDrawID;		// �� �� Ÿ�� �̹���

	int			iStageID;

	int			UndoiIndex = 0;
	int			iIndex = 0;			// ���� Ÿ�� �ε��� ����
	int			iParentIdx = 0;		// ���� Ÿ�� �ε��� ����


}TILE;


typedef	struct tagFrame
{
	float		fFrame; // �������� ���� ���� ����
	float		fMax;	// �ִ� �̹����� ������ ��

}FRAME;

typedef	struct tagUnitData
{
#ifndef _AFX
	wstring		strName;

#else
	CString	strName;
#endif

	int		iLevel;
	int		iHp;
	int		iAttack;
	int		iDeffence;
	int		iSpecialAttack;
	int		iSpecialDeffence;
	int		iType;

}UNITDATA;

typedef struct tagTexturePath
{
	wstring		wstrObjKey		= L"";
	wstring		wstrStateKey	= L"";
	wstring		wstrPath		= L"";
	int			iCount			= 0;

}IMGPATH;


typedef struct tagPocketmonTexturePath : public IMGPATH
{
	wstring wstrPckKey = L"";
}PCKIMGPATH;


static D3DXVECTOR3		Get_Mouse()
{
	POINT	Pt{};

	GetCursorPos(&Pt);
	ScreenToClient(g_hWnd, &Pt);

	return D3DXVECTOR3((float)Pt.x, (float)Pt.y, 0.f);
}