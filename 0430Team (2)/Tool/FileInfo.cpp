#include "stdafx.h"
#include "FileInfo.h"


CFileInfo::CFileInfo()
{
}


CFileInfo::~CFileInfo()
{
}

CString CFileInfo::ConvertRelativePath(CString strFullPath)
{
	TCHAR		szRelativePath[MAX_PATH] = L"";
	TCHAR		szCurDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szCurDirPath);
	// PathRelativePathTo : szCurDirPath ���� strFullPath�� ���� ��� ��θ� ���ؼ� szRelativePath�� ����
	//						��, ���� ����̺� �ȿ����� ���� ����

	PathRelativePathTo(szRelativePath, 
		szCurDirPath, FILE_ATTRIBUTE_DIRECTORY, 
		strFullPath.GetString(), FILE_ATTRIBUTE_DIRECTORY);
	return CString(szRelativePath);
}



void CFileInfo::DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList, bool _pck = false)
{
	// CFileFind : ���� �� ���� ��� ���� ���� mfc Ŭ����

	CFileFind		Find;

	wstring	wstrFilePath = wstrPath + L"\\*.*";

	// FindFile : �Ű� ������ ���޵� ��ο� ������ �ִ��� ������ Ȯ���ϴ� �Լ�, �������� ������ FALSE, �����ϸ� TRUE�� ����

	BOOL	bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		// FindNextFile : ���� ��� �ȿ��� ���� ���ϵ��� ã�Ƴ�����. ���̻� ã���� ���ų� ������ ����� ��� 0�� ��ȯ
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		else if (Find.IsDirectory())
		{
			// GetFilePath : ���� ������ ã�� ��θ� ��ȯ�ϴ� �Լ�
			DirInfoExtraction(wstring(Find.GetFilePath()), rPathInfoList, _pck);
		}

		else
		{
			if (Find.IsSystem())
				continue;

			IMGPATH* pImgPath(nullptr);

			if(_pck)
				pImgPath = new PCKIMGPATH;
			else
				pImgPath = new IMGPATH;

			TCHAR		szPathBuf[MAX_PATH] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());

			PathRemoveFileSpec(szPathBuf);
			// szPathBuf = 0x0115e0b0 L"D:\\����ȯ\\145��\\Frame145\\Texture\\Stage\\Effect\\BossMultiAttack"

			pImgPath->iCount = DirFileCount(szPathBuf);

			// GetFileTitle : ������ ���� �̸��� ������ �Լ�
			wstring	wstrTextureName = Find.GetFileTitle().GetString();
			// wstrTextureName = L"BossMultiAttack0"

			// substr(����, ��) : ���ۿ��� ���� �ش��ϴ� ���ڿ��� ������ �Լ�
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d.png";
			// wstrTextureName = L"BossMultiAttack%d.png"

			// PathCombine(dst, src1, src2) : src1�� src2�� �̾�ٿ� �ϼ��� ��θ� dst�� ����, src1�� src2 ���̿� '\\'�� �ڵ����� ���Ե� ä �����
			PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());
			// szPathBuf = 0x0115e0b0 L"D:\\����ȯ\\145��\\Frame145\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			pImgPath->wstrPath = CFileInfo::ConvertRelativePath(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			PathRemoveFileSpec(szPathBuf);
			// PathFindFileName : ���ϸ��� ã�ų� ������ �������� ã�Ƴ�
			pImgPath->wstrStateKey = PathFindFileName(szPathBuf);

			PathRemoveFileSpec(szPathBuf);
			// PathFindFileName : ���ϸ��� ã�ų� ������ �������� ã�Ƴ�
			pImgPath->wstrObjKey = PathFindFileName(szPathBuf);

			if(_pck)
			{
				PathRemoveFileSpec(szPathBuf);
				static_cast<PCKIMGPATH*>(pImgPath)->wstrPckKey = PathFindFileName(szPathBuf);
			}

			rPathInfoList.push_back(pImgPath);

			bContinue = 0;
		}
	}
}

void CFileInfo::DirMapInfo(const wstring& wstrPath, list<IMGPATH*>& rPathInfoList)
{

	// CFileFind : ���� �� ���� ��� ���� ���� mfc Ŭ����

	CFileFind		Find;

	wstring	wstrFilePath = wstrPath + L"\\*.*";

	// FindFile : �Ű� ������ ���޵� ��ο� ������ �ִ��� ������ Ȯ���ϴ� �Լ�, �������� ������ FALSE, �����ϸ� TRUE�� ����

	BOOL	bContinue = Find.FindFile(wstrFilePath.c_str());

	while (bContinue)
	{
		// FindNextFile : ���� ��� �ȿ��� ���� ���ϵ��� ã�Ƴ�����. ���̻� ã���� ���ų� ������ ����� ��� 0�� ��ȯ
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		else if (Find.IsDirectory())
		{
			// GetFilePath : ���� ������ ã�� ��θ� ��ȯ�ϴ� �Լ�
			DirMapInfo(wstring(Find.GetFilePath()), rPathInfoList);
		}

		else
		{
			if (Find.IsSystem())
				continue;

			IMGPATH* pImgPath = new IMGPATH;
			TCHAR		szPathBuf[MAX_PATH] = L"";

			lstrcpy(szPathBuf, Find.GetFilePath().GetString());

			PathRemoveFileSpec(szPathBuf);
			// szPathBuf = 0x0115e0b0 L"D:\\����ȯ\\145��\\Frame145\\Texture\\Stage\\Effect\\BossMultiAttack"

			pImgPath->iCount = DirFileCount(szPathBuf);

			// GetFileTitle : ������ ���� �̸��� ������ �Լ�
			wstring	wstrTextureName = Find.GetFileTitle().GetString();
			// wstrTextureName = L"BossMultiAttack0"

			// substr(����, ��) : ���ۿ��� ���� �ش��ϴ� ���ڿ��� ������ �Լ�
			wstrTextureName = wstrTextureName.substr(0, wstrTextureName.size() - 1) + L"%d";
			// wstrTextureName = L"BossMultiAttack%d.png"

			// PathCombine(dst, src1, src2) : src1�� src2�� �̾�ٿ� �ϼ��� ��θ� dst�� ����, src1�� src2 ���̿� '\\'�� �ڵ����� ���Ե� ä �����
			PathCombine(szPathBuf, szPathBuf, wstrTextureName.c_str());
			// szPathBuf = 0x0115e0b0 L"D:\\����ȯ\\145��\\Frame145\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			pImgPath->wstrPath = CFileInfo::ConvertRelativePath(szPathBuf);
			// pImgPath->wstrPath = L"..\\Texture\\Stage\\Effect\\BossMultiAttack\\BossMultiAttack%d.png"

			PathRemoveFileSpec(szPathBuf);
			// PathFindFileName : ���ϸ��� ã�ų� ������ �������� ã�Ƴ�
			pImgPath->wstrStateKey = PathFindFileName(szPathBuf);

			PathRemoveFileSpec(szPathBuf);
			// PathFindFileName : ���ϸ��� ã�ų� ������ �������� ã�Ƴ�
			pImgPath->wstrObjKey = PathFindFileName(szPathBuf);

			rPathInfoList.push_back(pImgPath);

			bContinue = 0;
		}

	}

}

int CFileInfo::DirFileCount(const wstring& wstrPath)
{
	CFileFind		Find;

	wstring	wstrFilePath = wstrPath + L"\\*.png*";

	// FindFile : �Ű� ������ ���޵� ��ο� ������ �ִ��� ������ Ȯ���ϴ� �Լ�, �������� ������ FALSE, �����ϸ� TRUE�� ����

	BOOL	bContinue = Find.FindFile(wstrFilePath.c_str());

	int		iFileCnt(0);

	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsSystem())
			continue;

		++iFileCnt;
	}

	return iFileCnt;
}

int CFileInfo::DirMapTileFileCount(int *Cnt, const wstring& wstrPath)
{
	CFileFind		Find;
	
	int		iFileCnt(0);


	//wstring	wstrTextureName = Find.GetFileTitle().GetString();
	// wstrTextureName = L"BossMultiAttack0"


	wstring	wstrFilePath = wstrPath + L"\*.*";

	// FindFile : �Ű� ������ ���޵� ��ο� ������ �ִ��� ������ Ȯ���ϴ� �Լ�, �������� ������ FALSE, �����ϸ� TRUE�� ����

	BOOL	bContinue = Find.FindFile(wstrFilePath.c_str());


	while (bContinue)
	{
		bContinue = Find.FindNextFile();

		if (Find.IsDots())
			continue;

		if (Find.IsSystem())
			continue;

		++iFileCnt;
	}
	//*Cnt = iFileCnt;
	return iFileCnt;
}
