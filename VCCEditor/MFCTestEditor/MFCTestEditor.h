
// MFCTestEditor.h: archivo de encabezado principal para la aplicación MFCTestEditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluir 'stdafx.h' antes de incluir este archivo para PCH"
#endif

#include "resource.h"       // Símbolos principales


// CMFCTestEditorApp:
// Consulte la sección MFCTestEditor.cpp para obtener información sobre la implementación de esta clase
//

class CMFCTestEditorApp : public CWinAppEx
{
public:
	CMFCTestEditorApp();


// Reemplazos
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementación
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCTestEditorApp theApp;
