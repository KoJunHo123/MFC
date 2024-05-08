#pragma once
#include "afxwin.h"

#include "Include.h"
#include "TextureMgr.h"

// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

// Ž�� : ���ڿ��� �Է����� ���, �ش� ���ڿ��� ��ġ�ϴ� ����Ʈ �ڽ� ����� ���õǸ� ���� ������ �ݿ�
// ���� : ����Ʈ �ڽ��� �ִ� ���ڿ��� ���콺�� Ŭ���Ͽ� �����ϰ� �� ����, ������ư�� ���� �����͸� ����
// ����, �ҷ����� : ��ư�� ���� ���, ����Ʈ �ڽ��� �ִ� �����͸� �����ϰų� �Ǵ� �ҷ����� ��ư�� ���� ��� �����͸� �о�鿩 ����Ʈ �ڽ� ��Ͽ� �����͸� �ҷ�����

