#pragma once
#include "afxwin.h"
#include <atlimage.h>
#include "Include.h"
#include "Undo.h"

// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	 afx_msg void OnListBox();
	 afx_msg void OnDropFiles(HDROP hDropInfo);
	 void	Horizontal_Scroll();
	 afx_msg void OnDestroy();
	 afx_msg void OnSaveData();
	 afx_msg void On_ComboDrop(); // 이거는 열리는거
	 afx_msg void On_ComboClose(); // 이거는 벽타입 닫는거
	 afx_msg void On_ComboStageDrop(); // 얘는 스테이지 콤보박스 열리는거 Drop이 열리는거임 
	 afx_msg void On_CloseStageUp(); // 얘는 스테이지 닫히는거

	 afx_msg void On_MapPath();
	 afx_msg void On_MapPathSave();
	 afx_msg void On_PathLoad();
	 afx_msg void OnStnClickedPicture();
	 afx_msg void On_EditGrid();
	 afx_msg void On_UndoButton();
	 afx_msg void On_SliderControll(NMHDR* pNMHDR, LRESULT* pResult);
	 afx_msg void On_SliderRange();
	 afx_msg void On_MapEditLoad();
	 afx_msg void On_EditChange();

public:

	//CListBox m_SliderRange;
	CListBox m_ListBox;
	CStatic m_Picture;

	map<CString, CImage*>	m_mapPngImg;
	int			m_iDrawID;
	int			m_iOptionID;
	int			m_BrushSize = 1;

	//bool		m_bGridButton;

	CSliderCtrl m_SliderControl;
	CButton m_GridButten;
	CButton m_Paint;

	CComboBox m_ComboList;
	CComboBox m_ComboStageList;
	
	CListBox m_PathListBox;
	list<IMGPATH*>		m_PathInfoList;
	
	CEdit m_SlidereditControl;

	int			m_StageNumber = 0;
	int			m_CombeIndex = 0;
	int			m_TempStage = 0;



	bool Get_bUndo() { return m_bUndo; }
	void Set_bUndo() { m_bUndo = false; }
private:
	bool m_bUndo = false;
	bool m_bMousePress = false;
public:
	afx_msg void On_BspButton();
//	afx_msg void On_Paint(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void On_Paint();
};
