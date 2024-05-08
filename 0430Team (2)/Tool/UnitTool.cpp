// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"


// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
	, m_strName(_T(""))
	, m_iAttack(0)
	, m_iHp(0)
	, m_strFindName(_T(""))
	, m_iLevel(0)
	, m_iDeffence(0)
	, m_iSpecialAttack(0)
	, m_iSpecialDeffence(0)
	, m_iCompatibility{}
	, m_strWeakness(_T(""))
	, m_strTolerance(_T(""))
	, m_strImmune(_T(""))
	, m_strTypeName{}
	, m_strComboPck(_T(""))
	, m_strComboDir(_T(""))
	, m_strComboState(_T(""))
	, m_tFrame{}
	, m_szFullPath(_T(""))
{
	m_strTypeName[PCK_NORMAL] = L"<노말>";
	m_strTypeName[PCK_FIRE] = L"<불꽃>";
	m_strTypeName[PCK_WATER] = L"<물>";
	m_strTypeName[PCK_GRASS] = L"<풀>";
	m_strTypeName[PCK_ELECTRIC] = L"<전기>";
	m_strTypeName[PCK_ICE] = L"<얼음>";
	m_strTypeName[PCK_FIGHT] = L"<격투>";
	m_strTypeName[PCK_POISON] = L"<독>";
	m_strTypeName[PCK_GROUND] = L"<땅>";
	m_strTypeName[PCK_FLYING] = L"<비행>";
	m_strTypeName[PCK_PSYCHIC] = L"<에스퍼>";
	m_strTypeName[PCK_BUG] = L"<벌레>";
	m_strTypeName[PCK_ROCK] = L"<바위>";
	m_strTypeName[PCK_GHOST] = L"<고스트>";
	m_strTypeName[PCK_DRAGON] = L"<드래곤>";
	m_strTypeName[PCK_DARK] = L"<악>";
	m_strTypeName[PCK_STEEL] = L"<강철>";
	m_strTypeName[PCK_FAIRY] = L"<페어리>";
}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_iAttack);
	DDX_Text(pDX, IDC_EDIT5, m_iHp);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Text(pDX, IDC_EDIT6, m_strFindName);
	DDX_Text(pDX, IDC_EDIT7, m_iLevel);
	DDX_Text(pDX, IDC_EDIT8, m_iDeffence);
	DDX_Text(pDX, IDC_EDIT9, m_iSpecialAttack);
	DDX_Text(pDX, IDC_EDIT10, m_iSpecialDeffence);
	DDX_Control(pDX, IDC_NORMAL, m_TypeCheck[PCK_NORMAL]);
	DDX_Control(pDX, IDC_FIRE, m_TypeCheck[PCK_FIRE]);
	DDX_Control(pDX, IDC_WATER, m_TypeCheck[PCK_WATER]);
	DDX_Control(pDX, IDC_GRASS, m_TypeCheck[PCK_GRASS]);
	DDX_Control(pDX, IDC_ELECTRIC, m_TypeCheck[PCK_ELECTRIC]);
	DDX_Control(pDX, IDC_ICE, m_TypeCheck[PCK_ICE]);
	DDX_Control(pDX, IDC_FIGHT, m_TypeCheck[PCK_FIGHT]);
	DDX_Control(pDX, IDC_POISON, m_TypeCheck[PCK_POISON]);
	DDX_Control(pDX, IDC_GROUND, m_TypeCheck[PCK_GROUND]);
	DDX_Control(pDX, IDC_FLYING, m_TypeCheck[PCK_FLYING]);
	DDX_Control(pDX, IDC_PSYCHIC, m_TypeCheck[PCK_PSYCHIC]);
	DDX_Control(pDX, IDC_BUG, m_TypeCheck[PCK_BUG]);
	DDX_Control(pDX, IDC_ROCK, m_TypeCheck[PCK_ROCK]);
	DDX_Control(pDX, IDC_GHOST, m_TypeCheck[PCK_GHOST]);
	DDX_Control(pDX, IDC_DRAGON, m_TypeCheck[PCK_DRAGON]);
	DDX_Control(pDX, IDC_DARK, m_TypeCheck[PCK_DARK]);
	DDX_Control(pDX, IDC_STEEL, m_TypeCheck[PCK_STEEL]);
	DDX_Control(pDX, IDC_FAIRY, m_TypeCheck[PCK_FAIRY]);
	DDX_Text(pDX, IDC_WEAKNESS, m_strWeakness);
	DDX_Text(pDX, IDC_TOLERANCE, m_strTolerance);
	DDX_Text(pDX, IDC_IMMUNE, m_strImmune);
	DDX_Control(pDX, IDC_PCKIMG, m_PocketmonImg);
	DDX_Control(pDX, IDC_LIST3, m_TextureListBox);
	DDX_Control(pDX, IDC_COMBO4, m_ComboPckList);
	DDX_Control(pDX, IDC_COMBO5, m_ComboDirList);
	DDX_Control(pDX, IDC_COMBO6, m_ComboStateList);
	DDX_CBString(pDX, IDC_COMBO4, m_strComboPck);
	DDX_CBString(pDX, IDC_COMBO5, m_strComboDir);
	DDX_CBString(pDX, IDC_COMBO6, m_strComboState);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnListBox)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnDelete)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnLoad)
	ON_EN_CHANGE(IDC_EDIT6, &CUnitTool::OnFind)
	ON_BN_CLICKED(IDC_NORMAL, &CUnitTool::OnBnClickedNormal)
	ON_BN_CLICKED(IDC_FIRE, &CUnitTool::OnBnClickedFire)
	ON_BN_CLICKED(IDC_WATER, &CUnitTool::OnBnClickedWater)
	ON_BN_CLICKED(IDC_GRASS, &CUnitTool::OnBnClickedGrass)
	ON_BN_CLICKED(IDC_ELECTRIC, &CUnitTool::OnBnClickedElectric)
	ON_BN_CLICKED(IDC_ICE, &CUnitTool::OnBnClickedIce)
	ON_BN_CLICKED(IDC_FIGHT, &CUnitTool::OnBnClickedFight)
	ON_BN_CLICKED(IDC_POISON, &CUnitTool::OnBnClickedPoison)
	ON_BN_CLICKED(IDC_GROUND, &CUnitTool::OnBnClickedGround)
	ON_BN_CLICKED(IDC_FLYING, &CUnitTool::OnBnClickedFlying)
	ON_BN_CLICKED(IDC_PSYCHIC, &CUnitTool::OnBnClickedPsychic)
	ON_BN_CLICKED(IDC_BUG, &CUnitTool::OnBnClickedBug)
	ON_BN_CLICKED(IDC_ROCK, &CUnitTool::OnBnClickedRock)
	ON_BN_CLICKED(IDC_GHOST, &CUnitTool::OnBnClickedGhost)
	ON_BN_CLICKED(IDC_DRAGON, &CUnitTool::OnBnClickedDragon)
	ON_BN_CLICKED(IDC_DARK, &CUnitTool::OnBnClickedDark)
	ON_BN_CLICKED(IDC_STEEL, &CUnitTool::OnBnClickedSteel)
	ON_BN_CLICKED(IDC_FAIRY, &CUnitTool::OnBnClickedFairy)
	ON_LBN_SELCHANGE(IDC_LIST3, &CUnitTool::OnTextureListBox)
	ON_WM_DROPFILES()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO4, &CUnitTool::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CUnitTool::OnCbnSelchangeCombo5)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CUnitTool::OnCbnSelchangeCombo6)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.


void CUnitTool::OnAdd()
{
	UpdateData(TRUE);

	UNITDATA* pUnit = new UNITDATA;

	pUnit->strName = m_strName;
	pUnit->iAttack = m_iAttack;
	pUnit->iHp = m_iHp;
	pUnit->iDeffence = m_iDeffence;
	pUnit->iSpecialAttack = m_iSpecialAttack;
	pUnit->iSpecialDeffence = m_iSpecialDeffence;
	pUnit->iLevel = m_iLevel;

	pUnit->iType = 0x00;

	pUnit->iType = m_iType;
	// AddString : 매개 변수에 해당하는 문자열을 리스트 박스 목록에 추가하는 함수

	if (m_mapUnitData.end() == m_mapUnitData.find(pUnit->strName))
	{
		m_mapUnitData.insert({ pUnit->strName, pUnit });
		m_ListBox.AddString(pUnit->strName);
	}
	else
	{
		delete pUnit;
		pUnit = nullptr;
	}

	UpdateData(FALSE);
}

void CUnitTool::OnListBox()
{
	UpdateData(TRUE);

	CString		strFindName;

	// GetCurSel : 선택된 리스트 박스 셀의 인덱스를 반환(인덱스는 0부터 시작)
	int		iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	// GetText : 인덱스에 해당하는 리스트 박스의 문자열을 얻어오는 함수
	m_ListBox.GetText(iIndex, strFindName);

	auto	iter = m_mapUnitData.find(strFindName);

	if (iter == m_mapUnitData.end())
		return;

	m_strName = iter->second->strName;

	m_iLevel = iter->second->iLevel;
	m_iHp = iter->second->iHp;

	m_iAttack = iter->second->iAttack;
	m_iDeffence = iter->second->iDeffence;
	m_iSpecialAttack = iter->second->iSpecialAttack;
	m_iSpecialDeffence = iter->second->iSpecialDeffence;

	m_iType = iter->second->iType;

	for (int i = 0; i < size(m_TypeCheck); ++i)
	{
		m_TypeCheck[i].SetCheck(BST_UNCHECKED);
	}

	Set_Type_Check();


	UpdateData(FALSE);
}

void CUnitTool::OnDestroy()
{
	CDialog::OnDestroy();

	for_each(m_mapUnitData.begin(), m_mapUnitData.end(), [&](auto& MyPair)
		{
			if (MyPair.second)
			{
				delete MyPair.second;
				MyPair.second = nullptr;
			}
		});

	for_each(m_PathInfoList.begin(), m_PathInfoList.end(), [](auto& elem)
		{
			if (elem)
			{
				auto pckElem = static_cast<PCKIMGPATH*>(elem);
				delete pckElem;
				pckElem = nullptr;
			}

		});

	if (!m_Image.IsNull())
		m_Image.Destroy();

	m_mapUnitData.clear();
	m_PathInfoList.clear();
	KillTimer(1);
}

BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	CWnd::SetTimer(1, 500, NULL);
	//HBITMAP		hBitmap = (HBITMAP)LoadImage(nullptr, L"../Texture/JusinLogo1.bmp", IMAGE_BITMAP, 100, 50, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	return TRUE;
}


void CUnitTool::Check_Compatibility()
{
	UpdateData(TRUE);
	m_strTolerance = L"";
	m_strWeakness = L"";
	m_strImmune = L"";

	for (int i = 0; i < size(m_iCompatibility); ++i)
	{
		if (m_iCompatibility[i] > 0 && m_iCompatibility[i] < 900)
			m_strTolerance += m_strTypeName[i];
		else if (m_iCompatibility[i] < 0)
			m_strWeakness += m_strTypeName[i];
		else if (m_iCompatibility[i] > 900)
			m_strImmune += m_strTypeName[i];
	}

	UpdateData(FALSE);
}

void CUnitTool::OnDelete()
{
	UpdateData(TRUE);

	CString	strFindName = L"";

	int	iIndex = m_ListBox.GetCurSel();

	if (LB_ERR == iIndex)
		return;

	m_ListBox.GetText(iIndex, strFindName);

	auto& iter = m_mapUnitData.find(strFindName);

	if (iter == m_mapUnitData.end())
		return;

	Safe_Delete(iter->second);
	m_mapUnitData.erase(strFindName);

	// DeleteString : 리스트 박스에 해당 목록 문자열을 삭제
	m_ListBox.DeleteString(iIndex);


	UpdateData(FALSE);
}

void CUnitTool::OnSave()
{
	// CFileDialog : 파일 열기 또는 저장 작업에 필요한 대화상자를 생성하는 객체

	CFileDialog		Dlg(FALSE,		//  false : 다른 이름으로 저장, true : 불러오기
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기 전용 체크박스 숨김) | OFN_OVERWRITEPROMPT(중복 파일 저장 시, 경고 메세지 띄움)
		L"Data Files(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식 "콤보 박스에 출력된 문자열 | 실제 사용할 필터링 문자열 ||
		this);	// 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트 경로를 가져오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);

	// 전체 경로 중 파일 이름만 잘라내는 함수
	// 경로 상에 파일명이 없을 경우에는 제일 말단 폴더명을 잘라냄
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : 대화 상자 실행 함수
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : 선택된 경로를 반환하는 함수
		CString		str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();


		HANDLE	hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte(0);
		DWORD dwStrByte(0);

		for (auto& MyPair : m_mapUnitData)
		{
			// key 값 저장
			dwStrByte = sizeof(TCHAR) * (MyPair.first.GetLength() + 1);
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
			WriteFile(hFile, MyPair.first.GetString(), dwStrByte, &dwByte, nullptr);

			// value 값 저장
			WriteFile(hFile, &(MyPair.second->iLevel), sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &(MyPair.second->iHp), sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &(MyPair.second->iAttack), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(MyPair.second->iDeffence), sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &(MyPair.second->iSpecialAttack), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(MyPair.second->iSpecialDeffence), sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &(MyPair.second->iType), sizeof(int), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}

void CUnitTool::OnLoad()
{
	UpdateData(TRUE);


	CFileDialog		Dlg(TRUE,		//  false : 다른 이름으로 저장, true : 불러오기
		L"dat",		// default 확장자명
		L"*.dat",	// 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기 전용 체크박스 숨김) | OFN_OVERWRITEPROMPT(중복 파일 저장 시, 경고 메세지 띄움)
		L"Data Files(*.dat)|*.dat||",	// 대화 상자에 표시될 파일 형식 "콤보 박스에 출력된 문자열 | 실제 사용할 필터링 문자열 ||
		this);	// 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트 경로를 가져오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);

	// 전체 경로 중 파일 이름만 잘라내는 함수
	// 경로 상에 파일명이 없을 경우에는 제일 말단 폴더명을 잘라냄
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : 대화 상자 실행 함수
	if (IDOK == Dlg.DoModal())
	{

		for (auto& MyPair : m_mapUnitData)
			delete MyPair.second;

		m_mapUnitData.clear();

		// ResetContent : 기존의 list 목록도 초기화한다.
		m_ListBox.ResetContent();

		// GetPathName : 선택된 경로를 반환하는 함수
		CString		str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE	hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD dwByte(0);
		DWORD dwStrByte(0);
		UNITDATA	tData{};

		while (true)
		{
			// key 값 저장
			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR* pName = new TCHAR[dwStrByte];
			WriteFile(hFile, pName, dwStrByte, &dwByte, nullptr);

			// value 값 저장
			// value 값 저장
			WriteFile(hFile, &(tData.iLevel), sizeof(int), &dwByte, nullptr);

			WriteFile(hFile, &(tData.iHp), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(tData.iAttack), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(tData.iDeffence), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(tData.iSpecialAttack), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(tData.iSpecialDeffence), sizeof(int), &dwByte, nullptr);
			WriteFile(hFile, &(tData.iType), sizeof(int), &dwByte, nullptr);

			if (0 == dwByte)
			{
				delete[]pName;
				break;
			}

			UNITDATA* pUnit = new UNITDATA;

			pUnit->strName = pName;
			delete[]pName;

			pUnit->iLevel = tData.iLevel;
			pUnit->iHp = tData.iHp;
			pUnit->iAttack = tData.iAttack;
			pUnit->iDeffence = tData.iDeffence;
			pUnit->iSpecialAttack = tData.iSpecialAttack;
			pUnit->iSpecialDeffence = tData.iSpecialDeffence;
			pUnit->iType = tData.iType;

			m_mapUnitData.insert({ pUnit->strName, pUnit });

			m_ListBox.AddString(pUnit->strName);
		}

		CloseHandle(hFile);
	}

	UpdateData(FALSE);
}

void CUnitTool::OnFind()
{
	UpdateData(TRUE);

	auto& iter = m_mapUnitData.find(m_strFindName);

	if (iter == m_mapUnitData.end())
		return;

	// FindString : 0번 인덱스부터 매개 변수에 해당하는 문자열을 찾아 그 해당 셀의 인덱스 반환

	int		iIndex = m_ListBox.FindString(0, m_strFindName);

	if (LB_ERR == iIndex)
		return;

	//SetCurSel : 인덱스 값에 해당하는 리스트 박스 셀을 선택
	m_ListBox.SetCurSel(iIndex);

	m_strName = iter->second->strName;

	m_iLevel = iter->second->iLevel;
	m_iHp = iter->second->iHp;

	m_iAttack = iter->second->iAttack;
	m_iDeffence = iter->second->iDeffence;
	m_iSpecialAttack = iter->second->iSpecialAttack;
	m_iSpecialDeffence = iter->second->iSpecialDeffence;

	m_iType = iter->second->iType;

	for (int i = 0; i < size(m_TypeCheck); ++i)
	{
		m_TypeCheck[i].SetCheck(BST_UNCHECKED);
	}

	Set_Type_Check();

	UpdateData(FALSE);
}

void CUnitTool::OnTextureListBox()
{

}

void CUnitTool::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);
	CDialog::OnDropFiles(hDropInfo);


	// 경로 저장용 TCHAR
	TCHAR		szFullPath[MAX_PATH] = L"";

	// 0xffffffff-> 드롭된 파일의 수를 반환하는 옵션
	int		iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		// 윈도우로 드래고 된 파일 정보를 호출하는 함수
		// 인자의 핸들, 몇번째 파일을 쓸 것인가, 파일 경로(배열 시작 주소), 배열의 크기
		// 받아온 파일 정보를 배열에 할당해줌.
		DragQueryFile(hDropInfo, i, szFullPath, MAX_PATH);

		// 전달받은 파일의 내부 이미지 경로들을 리스트에 저장
		CFileInfo::DirInfoExtraction(szFullPath, m_PathInfoList, true);
	}

	// m_ListBox.ResetContent();

	wstring		wstrCombined = L"";
	TCHAR		szBuf[MAX_STR] = L"";

	// swprintf_s(szFullPath, pFilePath, i);

	for (auto& pImgPath : m_PathInfoList)
	{
		// _itow_s : 정수를 유니코드 문자열로 변환(숫자 10은 10진수로 변환하겠다는 의미)
		_itow_s(pImgPath->iCount, szBuf, 10);
		wstring wstrPckKey = static_cast<PCKIMGPATH*>(pImgPath)->wstrPckKey;
		wstrCombined = wstrPckKey + L"|" + pImgPath->wstrObjKey + L"|" + pImgPath->wstrStateKey + L"|" + szBuf + L"|" + pImgPath->wstrPath;


		m_TextureListBox.AddString(wstrCombined.c_str());

		if (LB_ERR == m_ComboPckList.FindString(-1, wstrPckKey.c_str()))
			m_ComboPckList.AddString(wstrPckKey.c_str());

		if (LB_ERR == m_ComboDirList.FindString(-1, pImgPath->wstrObjKey.c_str()))
			m_ComboDirList.AddString(pImgPath->wstrObjKey.c_str());

		if (LB_ERR == m_ComboStateList.FindString(-1, pImgPath->wstrStateKey.c_str()))
			m_ComboStateList.AddString(pImgPath->wstrStateKey.c_str());
	}

	Horizontal_Scroll();

	UpdateData(FALSE);
}

IMGPATH* CUnitTool::Get_ImgPath()
{
	for (auto& elem : m_PathInfoList)
	{
		CString strPCK = static_cast<PCKIMGPATH*>(elem)->wstrPckKey.c_str();
		if (m_strComboPck == strPCK
			&& m_strComboDir == elem->wstrObjKey.c_str()
			&& m_strComboState == elem->wstrStateKey.c_str())
		{
			return elem;
		}
	}
	return nullptr;
}

void CUnitTool::Horizontal_Scroll()
{
	CString		strName;
	CSize		size;

	int	iWidth(0);

	//		리스트 박스 또한 DC기반이기 때문에 GetDC로 DC를 얻어 올 수 있음
	CDC* pDC = m_TextureListBox.GetDC();

	// GetCount : 현재 리스트 박스 목록의 개수를 반환
	for (int i = 0; i < m_TextureListBox.GetCount(); ++i)
	{
		// GetText : 현재 인덱스에 해당하는 목록의 문자열을 얻어옴
		m_TextureListBox.GetText(i, strName);

		// GetTextExtent : 매개 변수에 해당하는 문자열의 길이를 픽셀 단위로 변환
		size = pDC->GetTextExtent(strName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_TextureListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : 리스트 박스가 가로로 스크롤 할 수 있는 최대 범위를 얻어오는 함수
	if (iWidth > m_TextureListBox.GetHorizontalExtent())
		m_TextureListBox.SetHorizontalExtent(iWidth);
}


#pragma region 포켓몬 타입 체크
void CUnitTool::Set_Type_Check()
{
	if (m_iType & NORMAL)
		m_TypeCheck[PCK_NORMAL].SetCheck(BST_CHECKED);

	if (m_iType & FIRE)
		m_TypeCheck[PCK_FIRE].SetCheck(BST_CHECKED);

	if (m_iType & WATER)
		m_TypeCheck[PCK_WATER].SetCheck(BST_CHECKED);

	if (m_iType & GRASS)
		m_TypeCheck[PCK_GRASS].SetCheck(BST_CHECKED);

	if (m_iType & ELECTRIC)
		m_TypeCheck[PCK_ELECTRIC].SetCheck(BST_CHECKED);

	if (m_iType & ICE)
		m_TypeCheck[PCK_ICE].SetCheck(BST_CHECKED);

	if (m_iType & FIGHT)
		m_TypeCheck[PCK_FIGHT].SetCheck(BST_CHECKED);

	if (m_iType & POISON)
		m_TypeCheck[PCK_POISON].SetCheck(BST_CHECKED);

	if (m_iType & GROUND)
		m_TypeCheck[PCK_GROUND].SetCheck(BST_CHECKED);

	if (m_iType & FLYING)
		m_TypeCheck[PCK_FLYING].SetCheck(BST_CHECKED);

	if (m_iType & PSYCHIC)
		m_TypeCheck[PCK_PSYCHIC].SetCheck(BST_CHECKED);

	if (m_iType & BUG)
		m_TypeCheck[PCK_BUG].SetCheck(BST_CHECKED);

	if (m_iType & ROCK)
		m_TypeCheck[PCK_ROCK].SetCheck(BST_CHECKED);

	if (m_iType & GHOST)
		m_TypeCheck[PCK_GHOST].SetCheck(BST_CHECKED);

	if (m_iType & DRAGON)
		m_TypeCheck[PCK_DRAGON].SetCheck(BST_CHECKED);

	if (m_iType & DARK)
		m_TypeCheck[PCK_DARK].SetCheck(BST_CHECKED);

	if (m_iType & STEEL)
		m_TypeCheck[PCK_STEEL].SetCheck(BST_CHECKED);

	if (m_iType & FAIRY)
		m_TypeCheck[PCK_FAIRY].SetCheck(BST_CHECKED);

}

void CUnitTool::OnBnClickedNormal()
{
	if (m_iType & NORMAL)
	{
		m_iType &= ~NORMAL;

		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_GHOST] -= 999;
	}
	else
	{
		m_iType |= NORMAL;

		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_GHOST] += 999;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedFire()
{
	if (m_iType & FIRE)
	{
		m_iType &= ~FIRE;
		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_ICE] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;
		m_iCompatibility[PCK_FAIRY] -= 1;

		m_iCompatibility[PCK_WATER] += 1;
		m_iCompatibility[PCK_GROUND] += 1;
		m_iCompatibility[PCK_ROCK] += 1;

	}
	else
	{
		m_iType |= FIRE;

		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_ICE] += 1;
		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_STEEL] += 1;
		m_iCompatibility[PCK_FAIRY] += 1;

		m_iCompatibility[PCK_WATER] -= 1;
		m_iCompatibility[PCK_GROUND] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;

	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedWater()
{
	if (m_iType & WATER)
	{
		m_iType &= ~WATER;

		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_WATER] -= 1;
		m_iCompatibility[PCK_ICE] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;

		m_iCompatibility[PCK_ELECTRIC] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
	}
	else
	{
		m_iType |= WATER;

		// 내성 : 불 물 얼음 강철
		// 약점 : 풀 전기
		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_WATER] += 1;
		m_iCompatibility[PCK_ICE] += 1;
		m_iCompatibility[PCK_STEEL] += 1;

		m_iCompatibility[PCK_ELECTRIC] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedGrass()
{
	if (m_iType & GRASS)
	{
		m_iType &= ~GRASS;

		m_iCompatibility[PCK_WATER] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_ELECTRIC] -= 1;
		m_iCompatibility[PCK_GROUND] -= 1;

		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_ICE] += 1;
		m_iCompatibility[PCK_POISON] += 1;
		m_iCompatibility[PCK_FLYING] += 1;
		m_iCompatibility[PCK_BUG] += 1;
	}
	else
	{
		m_iType |= GRASS;

		m_iCompatibility[PCK_WATER] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_ELECTRIC] += 1;
		m_iCompatibility[PCK_GROUND] += 1;

		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_ICE] -= 1;
		m_iCompatibility[PCK_POISON] -= 1;
		m_iCompatibility[PCK_FLYING] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;
	}


	// 내성 : 물 풀 전기 땅
	// 약점 : 불꽃 얼음 독 비행 벌래


	Check_Compatibility();
}

void CUnitTool::OnBnClickedElectric()
{
	if (m_iType & ELECTRIC)
	{
		m_iType &= ~ELECTRIC;

		m_iCompatibility[PCK_ELECTRIC] -= 1;
		m_iCompatibility[PCK_FLYING] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;

		m_iCompatibility[PCK_GROUND] += 1;

	}
	else
	{
		m_iType |= ELECTRIC;

		m_iCompatibility[PCK_ELECTRIC] += 1;
		m_iCompatibility[PCK_FLYING] += 1;
		m_iCompatibility[PCK_STEEL] += 1;

		m_iCompatibility[PCK_GROUND] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedIce()
{
	if (m_iType & ICE)
	{
		m_iType &= ~ICE;
		m_iCompatibility[PCK_ICE] -= 1;

		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_ROCK] += 1;
		m_iCompatibility[PCK_STEEL] += 1;

	}
	else
	{
		m_iType |= ICE;
		m_iCompatibility[PCK_ICE] += 1;

		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedFight()
{

	if (m_iType & FIGHT)
	{
		m_iType &= ~FIGHT;

		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;
		m_iCompatibility[PCK_DARK] -= 1;

		m_iCompatibility[PCK_FLYING] += 1;
		m_iCompatibility[PCK_PSYCHIC] += 1;
		m_iCompatibility[PCK_FAIRY] += 1;
	}
	else
	{
		m_iType |= FIGHT;

		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_ROCK] += 1;
		m_iCompatibility[PCK_DARK] += 1;

		m_iCompatibility[PCK_FLYING] -= 1;
		m_iCompatibility[PCK_PSYCHIC] -= 1;
		m_iCompatibility[PCK_FAIRY] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedPoison()
{
	if (m_iType & POISON)
	{
		m_iType &= ~POISON;

		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_POISON] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_FAIRY] -= 1;

		m_iCompatibility[PCK_GROUND] += 1;
		m_iCompatibility[PCK_PSYCHIC] += 1;
	}
	else
	{
		m_iType |= POISON;

		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_POISON] += 1;
		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_FAIRY] += 1;

		m_iCompatibility[PCK_GROUND] -= 1;
		m_iCompatibility[PCK_PSYCHIC] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedGround()
{
	if (m_iType & GROUND)
	{
		m_iType &= ~GROUND;

		m_iCompatibility[PCK_POISON] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;

		m_iCompatibility[PCK_WATER] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_ICE] += 1;

		m_iCompatibility[PCK_ELECTRIC] -= 999;
	}
	else
	{
		m_iType |= GROUND;

		m_iCompatibility[PCK_POISON] += 1;
		m_iCompatibility[PCK_ROCK] += 1;

		m_iCompatibility[PCK_WATER] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_ICE] -= 1;

		m_iCompatibility[PCK_ELECTRIC] += 999;
	}


	Check_Compatibility();
}

void CUnitTool::OnBnClickedFlying()
{
	if (m_iType & FLYING)
	{
		m_iType &= ~FLYING;

		// 내성 : 풀 격투 벌레
		// 약점 : 전기 얼음 바위
		// 면역 : 땅
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;

		m_iCompatibility[PCK_ELECTRIC] += 1;
		m_iCompatibility[PCK_ICE] += 1;
		m_iCompatibility[PCK_ROCK] += 1;

		m_iCompatibility[PCK_GROUND] -= 999;
	}
	else
	{
		m_iType |= FLYING;

		// 내성 : 풀 격투 벌레
		// 약점 : 전기 얼음 바위
		// 면역 : 땅
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_BUG] += 1;

		m_iCompatibility[PCK_ELECTRIC] -= 1;
		m_iCompatibility[PCK_ICE] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;

		m_iCompatibility[PCK_GROUND] += 999;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedPsychic()
{
	if (m_iType & PSYCHIC)
	{
		m_iType &= ~PSYCHIC;

		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_PSYCHIC] -= 1;

		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_GHOST] += 1;
		m_iCompatibility[PCK_DARK] += 1;
	}
	else
	{
		m_iType |= PSYCHIC;

		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_PSYCHIC] += 1;

		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_GHOST] -= 1;
		m_iCompatibility[PCK_DARK] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedBug()
{
	if (m_iType & BUG)
	{
		m_iType &= ~BUG;

		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_GROUND] -= 1;

		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_FLYING] += 1;
		m_iCompatibility[PCK_ROCK] += 1;
	}
	else
	{
		m_iType |= BUG;

		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_GROUND] += 1;

		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_FLYING] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedRock()
{
	if (m_iType & ROCK)
	{
		m_iType &= ~ROCK;

		m_iCompatibility[PCK_NORMAL] -= 1;
		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_POISON] -= 1;
		m_iCompatibility[PCK_FLYING] -= 1;

		m_iCompatibility[PCK_WATER] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_GROUND] += 1;
		m_iCompatibility[PCK_STEEL] += 1;
	}
	else
	{
		m_iType |= ROCK;

		m_iCompatibility[PCK_NORMAL] += 1;
		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_POISON] += 1;
		m_iCompatibility[PCK_FLYING] += 1;

		m_iCompatibility[PCK_WATER] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_GROUND] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedGhost()
{
	if (m_iType & GHOST)
	{
		m_iType &= ~GHOST;

		m_iCompatibility[PCK_NORMAL] -= 999;
		m_iCompatibility[PCK_FIGHT] -= 999;

		m_iCompatibility[PCK_POISON] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;

		m_iCompatibility[PCK_GHOST] += 1;
		m_iCompatibility[PCK_DARK] += 1;
	}
	else
	{
		m_iType |= GHOST;

		m_iCompatibility[PCK_NORMAL] += 999;
		m_iCompatibility[PCK_FIGHT] += 999;

		m_iCompatibility[PCK_POISON] += 1;
		m_iCompatibility[PCK_BUG] += 1;

		m_iCompatibility[PCK_GHOST] -= 1;
		m_iCompatibility[PCK_DARK] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedDragon()
{
	if (m_iType & DRAGON)
	{
		m_iType &= ~DRAGON;

		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_WATER] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_ELECTRIC] -= 1;

		m_iCompatibility[PCK_ICE] += 1;
		m_iCompatibility[PCK_DRAGON] += 1;
		m_iCompatibility[PCK_FAIRY] += 1;
	}
	else
	{
		m_iType |= DRAGON;

		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_WATER] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_ELECTRIC] += 1;

		m_iCompatibility[PCK_ICE] -= 1;
		m_iCompatibility[PCK_DRAGON] -= 1;
		m_iCompatibility[PCK_FAIRY] -= 1;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedDark()
{

	if (m_iType & DARK)
	{
		m_iType &= ~DARK;

		m_iCompatibility[PCK_GHOST] -= 1;
		m_iCompatibility[PCK_DARK] -= 1;

		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_FAIRY] += 1;

		m_iCompatibility[PCK_PSYCHIC] -= 999;
	}
	else
	{
		m_iType |= DARK;

		m_iCompatibility[PCK_GHOST] += 1;
		m_iCompatibility[PCK_DARK] += 1;

		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_FAIRY] -= 1;

		m_iCompatibility[PCK_PSYCHIC] += 999;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedSteel()
{
	if (m_iType & STEEL)
	{
		m_iType &= ~STEEL;

		m_iCompatibility[PCK_NORMAL] -= 1;
		m_iCompatibility[PCK_GRASS] -= 1;
		m_iCompatibility[PCK_ICE] -= 1;
		m_iCompatibility[PCK_FLYING] -= 1;
		m_iCompatibility[PCK_PSYCHIC] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_ROCK] -= 1;
		m_iCompatibility[PCK_DRAGON] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;
		m_iCompatibility[PCK_FAIRY] -= 1;

		m_iCompatibility[PCK_FIRE] += 1;
		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_GROUND] += 1;

		m_iCompatibility[PCK_POISON] -= 999;
	}
	else
	{
		m_iType |= STEEL;

		m_iCompatibility[PCK_NORMAL] += 1;
		m_iCompatibility[PCK_GRASS] += 1;
		m_iCompatibility[PCK_ICE] += 1;
		m_iCompatibility[PCK_FLYING] += 1;
		m_iCompatibility[PCK_PSYCHIC] += 1;
		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_ROCK] += 1;
		m_iCompatibility[PCK_DRAGON] += 1;
		m_iCompatibility[PCK_STEEL] += 1;
		m_iCompatibility[PCK_FAIRY] += 1;

		m_iCompatibility[PCK_FIRE] -= 1;
		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_GROUND] -= 1;

		m_iCompatibility[PCK_POISON] += 999;
	}

	Check_Compatibility();
}

void CUnitTool::OnBnClickedFairy()
{
	if (m_iType & FAIRY)
	{
		m_iType &= ~FAIRY;

		m_iCompatibility[PCK_FIGHT] -= 1;
		m_iCompatibility[PCK_BUG] -= 1;
		m_iCompatibility[PCK_DARK] -= 1;

		m_iCompatibility[PCK_POISON] += 1;
		m_iCompatibility[PCK_STEEL] += 1;

		m_iCompatibility[PCK_DRAGON] -= 999;
	}
	else
	{
		m_iType |= FAIRY;

		m_iCompatibility[PCK_FIGHT] += 1;
		m_iCompatibility[PCK_BUG] += 1;
		m_iCompatibility[PCK_DARK] += 1;

		m_iCompatibility[PCK_POISON] -= 1;
		m_iCompatibility[PCK_STEEL] -= 1;

		m_iCompatibility[PCK_DRAGON] += 999;
	}

	Check_Compatibility();
}
#pragma endregion


void CUnitTool::OnTimer(UINT_PTR nIDEvent)
{
	UpdateData(TRUE);
	CDialog::OnTimer(nIDEvent);

	// m_Image.Destroy();

	CString strPck(L""), strDir(L""), strState(L"");
	if (m_ComboPckList.GetCount() && m_ComboDirList.GetCount() && m_ComboStateList.GetCount())
	{
		if (CB_ERR != m_ComboPckList.GetCurSel())
			m_ComboPckList.GetLBText(m_ComboPckList.GetCurSel(), strPck);
		else
			m_ComboPckList.GetLBText(0, strPck);

		if (CB_ERR != m_ComboDirList.GetCurSel())
			m_ComboDirList.GetLBText(m_ComboDirList.GetCurSel(), strDir);
		else
			m_ComboDirList.GetLBText(0, strPck);

		if (CB_ERR != m_ComboStateList.GetCurSel())
			m_ComboStateList.GetLBText(m_ComboStateList.GetCurSel(), strState);
		else
			m_ComboStateList.GetLBText(0, strPck);
	}

	for (auto& elem : m_PathInfoList)
	{
		PCKIMGPATH* pckElem = static_cast<PCKIMGPATH*>(elem);

		if (strPck == pckElem->wstrPckKey.c_str()
			&& strDir == pckElem->wstrObjKey.c_str()
			&& strState == pckElem->wstrStateKey.c_str())
		{
			m_tFrame.fMax = (float)pckElem->iCount;


			const TCHAR* pFilePath = pckElem->wstrPath.c_str();
			swprintf_s(m_szFullPath, pFilePath, (int)m_tFrame.fFrame);

			if (!m_Image.IsNull())
				m_Image.Destroy();

			CClientDC dc(this);
			if (S_OK == m_Image.Load(m_szFullPath))
			{
				m_Image.StretchBlt(dc, 850, 150, 100, 100, SRCCOPY);
			}

			//m_PocketmonImg.SetBitmap(m_Image);
		}
	}
	m_tFrame.fFrame += 1.f;
	if (m_tFrame.fFrame > m_tFrame.fMax - 1.f)
		m_tFrame.fFrame = 0.f;

	UpdateData(FALSE);
}


void CUnitTool::OnCbnSelchangeCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_tFrame.fFrame = 0.f;
}


void CUnitTool::OnCbnSelchangeCombo5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_tFrame.fFrame = 0.f;

}


void CUnitTool::OnCbnSelchangeCombo6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_tFrame.fFrame = 0.f;

}
