#pragma once
#include "Undo.h"

class UndoCareTake
{
public:
	void addUndo(Undo* _AddUndo) { m_vUndoList.push_back(_AddUndo); }
	Undo* getUndo(int index) const { return m_vUndoList[index]; }

	Undo* rollback()
	{
		Undo* ret = m_vUndoList.back();
		m_vUndoList.pop_back();
		return ret;
	}
private:
	vector<Undo*> m_vUndoList;
};

