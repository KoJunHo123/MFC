#pragma once

#include "Include.h"

class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static	CString		ConvertRelativePath(CString strFullPath);
	
	
	static	void		DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList, bool _pck);

	//static	void		DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList);

	static	void		DirMapInfo(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList);

	static int			DirFileCount(const wstring& wstrPath);
	static int			DirMapTileFileCount(int* Cnt, const wstring& wstrPath);
};

