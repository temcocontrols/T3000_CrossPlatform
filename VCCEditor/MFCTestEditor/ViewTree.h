
#pragma once

/////////////////////////////////////////////////////////////////////////////
// Ventana de CViewTree

class CViewTree : public CTreeCtrl
{
// Construcción
public:
	CViewTree();

// Invalidaciones
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementación
public:
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
};
