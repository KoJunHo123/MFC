#pragma once
#include "Include.h"
//#include "Terrain.h"
//#include "MapTool.h"

class Undo
{
private:
	~Undo();
public:
	Undo(const vector<TILE*>& _vUndo) : m_vUndo(_vUndo) {}
	virtual const vector<TILE*>& Getstate() const { return m_vUndo; }
private:
	vector<TILE*>		m_vUndo;

	//-----------------------Caretake-------------/

public:
	void init();
};