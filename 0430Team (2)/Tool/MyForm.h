#pragma once

#include "UnitTool.h"
#include "MapTool.h"
#include "PathFind.h"

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnUnitTool();
	afx_msg void OnMapTool();
	afx_msg void OnPathFind();

private:
	CFont		m_Font;

public:
	CUnitTool	m_UnitTool;
	CMapTool	m_MapTool;
	CPathFind	m_PathFind;

public:
	virtual void OnInitialUpdate();

};


