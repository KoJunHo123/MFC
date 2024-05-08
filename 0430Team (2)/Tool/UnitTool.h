#pragma once
#include "afxwin.h"

#include "Include.h"
#include "TextureMgr.h"

// CUnitTool 대화 상자입니다.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnAdd();
	afx_msg void OnListBox();
	afx_msg void OnDestroy();
	afx_msg void OnDelete();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnFind();

	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedNormal();
	afx_msg void OnBnClickedFire();
	afx_msg void OnBnClickedWater();
	afx_msg void OnBnClickedGrass();
	afx_msg void OnBnClickedElectric();
	afx_msg void OnBnClickedIce();
	afx_msg void OnBnClickedFight();
	afx_msg void OnBnClickedPoison();
	afx_msg void OnBnClickedGround();
	afx_msg void OnBnClickedFlying();
	afx_msg void OnBnClickedPsychic();
	afx_msg void OnBnClickedBug();
	afx_msg void OnBnClickedRock();
	afx_msg void OnBnClickedGhost();
	afx_msg void OnBnClickedDragon();
	afx_msg void OnBnClickedDark();
	afx_msg void OnBnClickedSteel();
	afx_msg void OnBnClickedFairy();
	afx_msg void OnTextureListBox();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	IMGPATH* Get_ImgPath();

private:
	void Set_Type_Check();
	void Check_Compatibility();
	void	Horizontal_Scroll();

public:	// value
	CString m_strName;
	CString m_strFindName;
	int		m_iLevel;
	int		m_iHp;
	int		m_iAttack;
	int		m_iDeffence;
	int		m_iSpecialAttack;
	int		m_iSpecialDeffence;

	CString m_strWeakness;
	CString m_strTolerance;
	CString m_strImmune;

	CString m_strComboPck;
	CString m_strComboDir;
	CString m_strComboState;
public:	// control
	CListBox	m_ListBox;
	CButton		m_TypeCheck[18];
	CStatic		m_PocketmonImg;
	CListBox	m_TextureListBox;

	CComboBox	m_ComboPckList;
	CComboBox	m_ComboDirList;
	CComboBox	m_ComboStateList;
public:
	map<CString, UNITDATA*>		m_mapUnitData;
	list<IMGPATH*>				m_PathInfoList;
	CImage						m_Image;

	int							m_iType;
	int							m_iCompatibility[18];
	FRAME						m_tFrame;

	CString						m_strTypeName[18];
	TCHAR						m_szFullPath[MAX_PATH];


	afx_msg void OnCbnSelchangeCombo4();
	afx_msg void OnCbnSelchangeCombo5();
	afx_msg void OnCbnSelchangeCombo6();
};

// 탐색 : 문자열을 입력했을 경우, 해당 문자열과 일치하는 리스트 박스 목록이 선택되며 유닛 데이터 반영
// 삭제 : 리스트 박스에 있는 문자열을 마우스를 클릭하여 선택하고 그 이후, 삭제버튼을 눌러 데이터를 삭제
// 저장, 불러오기 : 버튼을 누를 경우, 리스트 박스에 있는 데이터를 저장하거나 또는 불러오기 버튼을 누를 경우 데이터를 읽어들여 리스트 박스 목록에 데이터를 불러와줌

