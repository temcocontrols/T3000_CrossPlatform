
// MFCTestEditorDoc.cpp: implementación de la clase CMFCTestEditorDoc
//

#include "stdafx.h"
// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de búsqueda, y permiten compartir código de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "MFCTestEditor.h"
#endif

#include "MFCTestEditorDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCTestEditorDoc

IMPLEMENT_DYNCREATE(CMFCTestEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCTestEditorDoc, CDocument)
END_MESSAGE_MAP()


// Construcción o destrucción de CMFCTestEditorDoc

CMFCTestEditorDoc::CMFCTestEditorDoc()
{
	// TODO: agregar aquí el código de construcción único

}

CMFCTestEditorDoc::~CMFCTestEditorDoc()
{
}

BOOL CMFCTestEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: agregar aquí código de reinicio
	// (los documentos SDI volverán a utilizar este documento)

	return TRUE;
}




// Serialización de CMFCTestEditorDoc

void CMFCTestEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: agregar aquí el código de almacenamiento
	}
	else
	{
		// TODO: agregar aquí el código de carga
	}
}

#ifdef SHARED_HANDLERS

// Compatibilidad con miniaturas
void CMFCTestEditorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modifique este código para dibujar los datos del documento
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Compatibilidad con controladores de búsqueda
void CMFCTestEditorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Establezca contenido de búsqueda a partir de los datos del documento. 
	// Las partes de contenido deben ir separadas por ";"

	// Por ejemplo:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCTestEditorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Diagnósticos de CMFCTestEditorDoc

#ifdef _DEBUG
void CMFCTestEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCTestEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Comandos de CMFCTestEditorDoc
