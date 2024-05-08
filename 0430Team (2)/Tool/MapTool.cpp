// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"
#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"
//#include "Undo.h"
// CMapTool ��ȭ �����Դϴ�.

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


// CMapTool �޽��� ó�����Դϴ�.

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
		// isdigit : �Ű� ������ ���޹��� ���ڰ� ���� ������ �������� ���� ���� �������� �Ǻ����ִ� �Լ�
		// ����, ���� ������ ������ ��� 0�� �ƴ� ���� ��ȯ

		if (0 != isdigit(strFindName[i]))
			break;
	}

	// Delete(index, count) : index���� count ��ŭ ���ڸ� �����ϴ� �Լ�
	strFindName.Delete(0, i);

	// _tstoi : ���ڸ� ���������� ��ȯ�ϴ� �Լ�
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

	// DragQueryFile : ��ӵ� ������ ������ ������ �Լ�

	// 0xffffffff(-1) : ��ӵ� ������ ���� ��ȯ �ɼ�
	int		iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for (int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);

		// PathFindFileName : ���� �̸��� ����� �Լ�

		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());
		//?
		// Ȯ���ڸ��� �����ϴ� �Լ�
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

	//		����Ʈ �ڽ� ���� DC����̱� ������ GetDC�� DC�� ��� �� �� ����
	CDC*	pDC = m_PathListBox.GetDC();

	// GetCount : ���� ����Ʈ �ڽ� ����� ������ ��ȯ
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		// GetText : ���� �ε����� �ش��ϴ� ����� ���ڿ��� ����
		m_ListBox.GetText(i, strName);
		
		// GetTextExtent : �Ű� ������ �ش��ϴ� ���ڿ��� ���̸� �ȼ� ������ ��ȯ
		size = pDC->GetTextExtent(strName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : ����Ʈ �ڽ��� ���η� ��ũ�� �� �� �ִ� �ִ� ������ ������ �Լ�
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
	CFileDialog		Dlg(FALSE,		//  false : �ٸ� �̸����� ����, true : �ҷ�����
		L"dat",		// default Ȯ���ڸ�
		L"*.dat",	// ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б� ���� üũ�ڽ� ����) | OFN_OVERWRITEPROMPT(�ߺ� ���� ���� ��, ��� �޼��� ���)
		L"Data Files(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ���� "�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this);	// �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	// ���� ������Ʈ ��θ� �������� �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);

	// ��ü ��� �� ���� �̸��� �߶󳻴� �Լ�
	// ��� �� ���ϸ��� ���� ��쿡�� ���� ���� �������� �߶�
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : ��ȭ ���� ���� �Լ�
	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : ���õ� ��θ� ��ȯ�ϴ� �Լ�
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
		m_ComboList.AddString(_T("Ÿ��"));
		m_ComboList.AddString(_T("��"));
		m_ComboList.AddString(_T("����"));
		m_ComboList.SetCurSel(0);
	}

	

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTool::On_MapPathSave()
{

	wofstream		fout;

	fout.open(L"../Data/ImgPath.txt", ios::out);

	// ���� ����
	if (!fout.fail())
	{
		for (auto& pImgPath : m_PathInfoList)
		{
			fout << pImgPath->wstrObjKey << L"|" << pImgPath->wstrStateKey << L"|" << pImgPath->iCount << L"|" << pImgPath->wstrPath << endl;
		}
		fout.close();
	}
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTool::On_PathLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
			// getline : '|' ������ ���ڿ��� ��� �о����
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
		m_ComboStageList.AddString(_T("1��������"));
		m_ComboStageList.AddString(_T("2��������"));
		m_ComboStageList.AddString(_T("3��������"));
		m_ComboStageList.AddString(_T("4��������"));
		m_ComboStageList.SetCurSel(0);
	}

	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTool::OnStnClickedPicture()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapTool::On_MapEditLoad()
{
	UpdateData(TRUE);


	CFileDialog		Dlg(TRUE,//  false : �ٸ� �̸����� ����, true : �ҷ�����
		L"dat",		// default Ȯ���ڸ�
		L"*.dat",	// ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б� ���� üũ�ڽ� ����) | OFN_OVERWRITEPROMPT(�ߺ� ���� ���� ��, ��� �޼��� ���)
		L"Data Files(*.dat)|*.dat||",	// ��ȭ ���ڿ� ǥ�õ� ���� ���� "�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||
		this);	// �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	// ���� ������Ʈ ��θ� �������� �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);

	// ��ü ��� �� ���� �̸��� �߶󳻴� �Լ�
	// ��� �� ���ϸ��� ���� ��쿡�� ���� ���� �������� �߶�
	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szPath;

	// DoModal : ��ȭ ���� ���� �Լ�
	if (IDOK == Dlg.DoModal())
	{

		// GetPathName : ���õ� ��θ� ��ȯ�ϴ� �Լ�
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
		// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
	UpdateData(FALSE);
}


void CMapTool::On_SliderRange()
{

	//m_SliderRange.GetText(m_SliderControl.GetPos(), NULL);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMapTool::On_EditChange()
{
	UpdateData(TRUE);
	CDialog::OnInitDialog();
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	
//	*pResult = 0;
//}


void CMapTool::On_Paint()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
