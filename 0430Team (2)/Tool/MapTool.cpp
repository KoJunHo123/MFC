// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"
//#include "Undo.h"
// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent), m_iDrawID(0)
{
}

CMapTool::~CMapTool()
{

}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_LIST2, m_PathListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_COMBO1, m_ComboList);
	DDX_Control(pDX, IDC_COMBO3, m_ComboStageList);
	DDX_Control(pDX, IDC_CHECK1, m_GridButten);
	DDX_Control(pDX, IDC_SLIDER3, m_SliderControl);
	//DDX_Control(pDX, IDC_LIST3, m_SliderRange);
	DDX_Control(pDX, IDC_EDIT1, m_SlidereditControl);
	DDX_Control(pDX, IDC_CHECK2, m_Paint);
}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveData)
	ON_CBN_DROPDOWN(IDC_COMBO1, &CMapTool::On_ComboDrop)
	ON_CBN_CLOSEUP(IDC_COMBO1, &CMapTool::On_ComboClose)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMapTool::On_MapPath)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTool::On_MapPathSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTool::On_PathLoad)
	ON_CBN_DROPDOWN(IDC_COMBO3, &CMapTool::On_ComboStageDrop)
	ON_CBN_CLOSEUP(IDC_COMBO3, &CMapTool::On_CloseStageUp)
	ON_STN_CLICKED(IDC_PICTURE, &CMapTool::OnStnClickedPicture)
	ON_BN_CLICKED(IDC_CHECK1, &CMapTool::On_EditGrid)
	ON_BN_CLICKED(IDC_BUTTON7, &CMapTool::On_MapEditLoad)
	ON_BN_CLICKED(IDC_BUTTON9, &CMapTool::On_UndoButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CMapTool::On_SliderControll)
	ON_LBN_SELCHANGE(IDC_LIST3, &CMapTool::On_SliderRange)
	ON_EN_CHANGE(IDC_EDIT1, &CMapTool::On_EditChange)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTool::On_BspButton)
	//ON_NOTIFY(BCN_DROPDOWN, IDC_CHECK2, &CMapTool::On_Paint)
	ON_BN_CLICKED(IDC_CHECK2, &CMapTool::On_Paint)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMapTool::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.

void CMapTool::On_MapPath()
{
	UpdateData(TRUE);

	CString		Path;

	int PathIndex = m_PathListBox.GetCurSel();


	auto& iter = m_PathInfoList.begin();

	if (iter == m_PathInfoList.end())
		return;

	for (int i = 0;i < PathIndex;i++)
	{
		iter++;
	}
	
	m_PathListBox.GetText(PathIndex, Path);

	//m_Picture.SetBitmap(*(iter->second));


	UpdateData(FALSE);
}

void CMapTool::OnListBox()
{
	UpdateData(TRUE);

	CString		strFindName;

	int iIndex = m_ListBox.GetCurSel();

	m_ListBox.GetText(iIndex, strFindName);

	auto iter = m_mapPngImg.find(strFindName);

	if (iter == m_mapPngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));
	
	int i(0);

	for (; i < strFindName.GetLength(); ++i)
	{
		// isdigit : 매개 변수로 전달받은 글자가 문자 형태의 글자인지 숫자 형태 글자인지 판별해주는 함수
		// 만약, 숫자 형태의 글자인 경우 0이 아닌 값을 반환

		if (0 != isdigit(strFindName[i]))
			break;
	}

	// Delete(index, count) : index부터 count 만큼 문자를 삭제하는 함수
	strFindName.Delete(0, i);

	// _tstoi : 문자를 정수형으로 변환하는 함수
	m_iDrawID = _tstoi(strFindName);
	if (m_CombeIndex == 1)
	{
		m_iOptionID = 1;
	}
	else
	{
		m_iOptionID = 0;
	}
	UpdateData(FALSE);
}

void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);

	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_PATH] = L"";

	// DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수

	// 0xffffffff(-1) : 드롭된 파일의 수를 반환 옵션
	int		iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);

		// PathFindFileName : 파일 이름만 남기는 함수

		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());
		//?
		// 확장자명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_mapPngImg.find(strFileName);

		if (iter == m_mapPngImg.end())
		{
			CImage* pPngImg = new CImage;
			pPngImg->Load(strRelative);

			m_mapPngImg.insert({strFileName, pPngImg });
			m_ListBox.AddString(strFileName);
		}

	}

	Horizontal_Scroll();

	UpdateData(FALSE);

}

void CMapTool::Horizontal_Scroll()
{
	CString		strName;
	CSize		size;

	int	iWidth(0);

	//		리스트 박스 또한 DC기반이기 때문에 GetDC로 DC를 얻어 올 수 있음
	CDC*	pDC = m_PathListBox.GetDC();

	// GetCount : 현재 리스트 박스 목록의 개수를 반환
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		// GetText : 현재 인덱스에 해당하는 목록의 문자열을 얻어옴
		m_ListBox.GetText(i, strName);
		
		// GetTextExtent : 매개 변수에 해당하는 문자열의 길이를 픽셀 단위로 변환
		size = pDC->GetTextExtent(strName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : 리스트 박스가 가로로 스크롤 할 수 있는 최대 범위를 얻어오는 함수
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);
}

void CMapTool::OnDestroy()
{
	CDialog::OnDestroy();

	for_each(m_mapPngImg.begin(), m_mapPngImg.end(), [](auto& MyPair)
	{
		MyPair.second->Destroy();
		Safe_Delete(MyPair.second);
	});

	m_mapPngImg.clear();
}

void CMapTool::OnSaveData()
{
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
		const TCHAR*	pGetPath = str.GetString();


		HANDLE	hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView*		pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

		CTerrain*		pTerrain = pMainView->m_pTerrain;
		vector<TILE*>&	vecTile = pTerrain->Get_VecTile();

		if (vecTile.empty())
			return;
		
		DWORD dwByte(0);

		for (auto& pTile : vecTile)
		{
			WriteFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}

void CMapTool::On_ComboDrop()
{

	if (m_ComboList.GetCount() == 0)
	{
		m_ComboList.AddString(_T("타일"));
		m_ComboList.AddString(_T("벽"));
		m_ComboList.AddString(_T("함정"));
		m_ComboList.SetCurSel(0);
	}

	

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMapTool::On_ComboClose()
{

	CFileFind		FindFolder;

	TCHAR		szFullPath[MAX_PATH] = L"";
	TCHAR		szFullimgPath[MAX_PATH] = L"";

	CString	strFileName = PathFindFileName(L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Walls/*.*");


	if (m_CombeIndex != m_ComboList.GetCurSel())
	{
		m_ListBox.ResetContent();
		for_each(m_mapPngImg.begin(), m_mapPngImg.end(), [](auto& MyPair)
			{
				MyPair.second->Destroy();
				Safe_Delete(MyPair.second);
			});

		m_mapPngImg.clear();
		m_CombeIndex = m_ComboList.GetCurSel();
	}


	if (m_StageNumber == 0)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Walls/*.*";
		}
	}
	if (m_StageNumber == 1)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Walls/*.*";
		}
	}
	if (m_StageNumber == 2)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Walls/*.*";
		}
	}
	if (m_StageNumber == 3)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Walls/*.*";
		}
	}


	bool Working = FindFolder.FindFile(strFileName);

	while (Working)
	{
		Working = FindFolder.FindNextFile();

		if (FindFolder.IsDirectory() || FindFolder.IsDots())
			continue;
		
		CString strimgName = PathFindFileName(strFileName);

		//strFileName = PathFindFileName(strFileName);

		lstrcpy(szFullPath, strFileName.GetString());

		strFileName = FindFolder.GetFileTitle();
		strimgName = FindFolder.GetFilePath();

		//PathRemoveExtension(szFullPath);

		//strFileName = szFullPath;

		auto	iter = m_mapPngImg.find(strFileName);

		if (iter == m_mapPngImg.end())
		{
			CImage* pPngImg = new CImage;
			pPngImg->Load(strimgName);

			m_mapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(strFileName);
		}
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMapTool::On_MapPathSave()
{

	wofstream		fout;

	fout.open(L"../Data/ImgPath.txt", ios::out);

	// 개방 성공
	if (!fout.fail())
	{
		for (auto& pImgPath : m_PathInfoList)
		{
			fout << pImgPath->wstrObjKey << L"|" << pImgPath->wstrStateKey << L"|" << pImgPath->iCount << L"|" << pImgPath->wstrPath << endl;
		}
		fout.close();
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMapTool::On_PathLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	wifstream		fin;

	fin.open(L"../Data/ImgPath.txt", ios::in);

	if (!fin.fail())
	{
		TCHAR		szObjKey[MAX_STR] = L"";
		TCHAR		szStateKey[MAX_STR] = L"";
		TCHAR		szCount[MAX_STR] = L"";
		TCHAR		szPath[MAX_PATH] = L"";

		wstring		wstrCombined = L"";

		m_PathListBox.ResetContent();

		while (true)
		{
			// getline : '|' 단위로 문자열을 끊어서 읽어들임
			fin.getline(szObjKey, MAX_STR, '|');
			fin.getline(szStateKey, MAX_STR, '|');
			fin.getline(szCount, MAX_STR, '|');
			fin.getline(szPath, MAX_PATH);

			if (fin.eof())
				break;

			wstrCombined = wstring(szObjKey) + L"|" + szStateKey + L"|" + szCount + L"|" + szPath;

			m_PathListBox.AddString(wstrCombined.c_str());
		}
		fin.close();
	}
	UpdateData(FALSE);
}

void CMapTool::On_ComboStageDrop()
{
	if (m_ComboStageList.GetCount() == 0)
	{
		m_ComboStageList.AddString(_T("1스테이지"));
		m_ComboStageList.AddString(_T("2스테이지"));
		m_ComboStageList.AddString(_T("3스테이지"));
		m_ComboStageList.AddString(_T("4스테이지"));
		m_ComboStageList.SetCurSel(0);
	}

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMapTool::On_CloseStageUp()
{
	CFileFind		FindFolder;

	TCHAR		szFullPath[MAX_PATH] = L"";
	TCHAR		szFullimgPath[MAX_PATH] = L"";

	CString	strFileName = PathFindFileName(L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Ground/*.*");
	

	if (m_StageNumber != m_ComboStageList.GetCurSel())
	{
		m_ListBox.ResetContent();
		for_each(m_mapPngImg.begin(), m_mapPngImg.end(), [](auto& MyPair)
			{
				MyPair.second->Destroy();
				Safe_Delete(MyPair.second);
			});

		m_mapPngImg.clear();
		m_StageNumber = m_ComboStageList.GetCurSel();
	}

	if (m_StageNumber == 0)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor0/Walls/*.*";
		}
	}
	if (m_StageNumber == 1)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor1/Walls/*.*";
		}
	}
	if (m_StageNumber == 2)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor2/Walls/*.*";
		}
	}
	if (m_StageNumber == 3)
	{
		strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Ground/*.*";
		if (m_ComboList.GetCurSel() == 1)
		{
			strFileName = L"../Texture/Stage/Terrain/PoketmonTile/Floor3/Walls/*.*";
		}
	}


		bool Working = FindFolder.FindFile(strFileName);

		while (Working)
		{
			//CString strimgName = strFileName.GetFilePath();

			Working = FindFolder.FindNextFile();

			if (FindFolder.IsDirectory() || FindFolder.IsDots())
				continue;

			CString strimgName = PathFindFileName(strFileName);
			lstrcpy(szFullimgPath, strimgName.GetString());

			lstrcpy(szFullPath, strFileName.GetString());

			strFileName = FindFolder.GetFileTitle();
			strimgName = FindFolder.GetFilePath();
			//PathRemoveExtension(szFullPath);

			//strFileName = szFullPath;
					
			auto	iter = m_mapPngImg.find(strFileName);

			if (iter == m_mapPngImg.end())
			{
				CImage* pPngImg = new CImage;
				pPngImg->Load(strimgName);

				m_mapPngImg.insert({ strFileName, pPngImg });
				m_ListBox.AddString(strFileName);
			}
		}

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMapTool::OnStnClickedPicture()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapTool::On_EditGrid()
{

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	pMainView->UpdateUndo();
	if (m_GridButten.GetCheck())
	{
		pMainView->m_pTerrain->Set_Grid(true);
	}
	else
	{
		pMainView->m_pTerrain->Set_Grid(false);
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapTool::On_MapEditLoad()
{
	UpdateData(TRUE);


	CFileDialog		Dlg(TRUE,//  false : 다른 이름으로 저장, true : 불러오기
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
		CString	str = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = str.GetString();

		HANDLE	hFile = CreateFile(pGetPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if(INVALID_HANDLE_VALUE == hFile)
			return;

		CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

		CTerrain* pTerrain = pMainView->m_pTerrain;
		vector<TILE*>& vecTile = pTerrain->Get_VecTile();

		if (vecTile.empty())
			return;

		DWORD dwByte(0);

		for (auto& pTile : vecTile)
		{
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
		}

		CloseHandle(hFile);

		UpdateData(FALSE);
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	}
}

void CMapTool::On_UndoButton()
{
	UpdateData(TRUE);

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	
	pMainView->UpdateUndo();
	
	pMainView->m_pTerrain->Undo_TerrainList();
	m_bUndo = true;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
}


void CMapTool::On_SliderControll(NMHDR* pNMHDR, LRESULT* pResult)
{
	UpdateData(TRUE);
	CDialog::OnInitDialog();
	m_SliderControl.SetRange(1, 5);
	m_BrushSize = m_SliderControl.GetPos();
	SetDlgItemInt(IDC_EDIT1, m_SliderControl.GetPos());
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);


	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	UpdateData(FALSE);
}


void CMapTool::On_SliderRange()
{

	//m_SliderRange.GetText(m_SliderControl.GetPos(), NULL);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMapTool::On_EditChange()
{
	UpdateData(TRUE);
	CDialog::OnInitDialog();
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(FALSE);
}


void CMapTool::On_BspButton()
{
	UpdateData(TRUE);
	

	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
	
	pMainView->m_pTerrain->Stack_NewTerrainList(pMainView->m_pTerrain);


	pMainView->m_pTerrain->BSP(m_StageNumber);
	pMainView->Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
	
	UpdateData(FALSE);
}


//void CMapTool::On_Paint(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	
//	*pResult = 0;
//}


void CMapTool::On_Paint()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	if (m_Paint.GetCheck())
	{
		pMainView->m_pTerrain->Set_Paint(true);
	}
	else
	{
		pMainView->m_pTerrain->Set_Paint(false);
	}
}


void CMapTool::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
	CToolView* pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	CMiniView* pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

	if (0 == m_StageNumber)
		pMainView->m_pTerrain->Set_Tile_Stage1();
	else if (1 == m_StageNumber)
		pMainView->m_pTerrain->Set_Tile_Stage2();
	else if (2 == m_StageNumber)
		pMainView->m_pTerrain->Set_Tile_Stage3();
	else if (3 == m_StageNumber)
		pMainView->m_pTerrain->Set_Tile_Stage4();

	pMainView->Invalidate(FALSE);
	pMiniView->Invalidate(FALSE);
	
}
