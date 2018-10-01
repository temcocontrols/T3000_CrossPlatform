
// MFCTestEditor.cpp : define los comportamientos de las clases para la aplicación.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MFCTestEditor.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "MFCTestEditorDoc.h"
#include "MFCTestEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTestEditorApp

BEGIN_MESSAGE_MAP(CMFCTestEditorApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMFCTestEditorApp::OnAppAbout)
	// Comandos de documento estándar basados en archivo
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Comando de configuración de impresión estándar
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// Construcción de CMFCTestEditorApp

CMFCTestEditorApp::CMFCTestEditorApp()
{
	m_bHiColorIcons = TRUE;

	// admite Administrador de reinicio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Si la aplicación se compila  para ser compatible con Common Language Runtime (/clr):
	//     1) Esta configuración adicional es necesaria para que la compatibilidad con el Administrador de reinicio funcione correctamente.
	//     2) En el proyecto, debe agregar una referencia a System.Windows.Forms para poder compilarlo.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: reemplace la cadena de identificador de aplicación siguiente por una cadena de identificador único; el formato
	// recomendado para la cadena es NombreCompañía.NombreProducto.Subproducto.InformaciónDeVersión
	SetAppID(_T("MFCTestEditor.AppID.NoVersion"));

	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}

// El único objeto CMFCTestEditorApp

CMFCTestEditorApp theApp;


// Inicialización de CMFCTestEditorApp

BOOL CMFCTestEditorApp::InitInstance()
{
	// Windows XP requiere InitCommonControlsEx() si un manifiesto de
	// aplicación especifica el uso de ComCtl32.dll versión 6 o posterior para habilitar
	// estilos visuales. De lo contrario, se generará un error al crear ventanas.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Establecer para incluir todas las clases de control comunes que desee utilizar
	// en la aplicación.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Inicializar bibliotecas OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// Se necesita AfxInitRichEdit2() para usar el control RichEdit	
	// AfxInitRichEdit2();

	// Inicialización estándar
	// Si no utiliza estas características y desea reducir el tamaño
	// del archivo ejecutable final, debe quitar
	// las rutinas de inicialización específicas que no necesite
	// Cambie la clave del Registro en la que se almacena la configuración
	// TODO: debe modificar esta cadena para que contenga información correcta
	// como el nombre de su compañía u organización
	SetRegistryKey(_T("Aplicaciones generadas con el Asistente para aplicaciones local"));
	LoadStdProfileSettings(4);  // Cargar opciones de archivo INI estándar (incluidas las de la lista MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Registrar las plantillas de documento de la aplicación. Las plantillas de documento
	//  sirven como conexión entre documentos, ventanas de marco y vistas
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_MFCTestEditorTYPE,
		RUNTIME_CLASS(CMFCTestEditorDoc),
		RUNTIME_CLASS(CChildFrame), // Marco MDI secundario personalizado
		RUNTIME_CLASS(CMFCTestEditorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Crear ventana de marco principal MDI
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// Llamar a DragAcceptFiles sólo si existe un sufijo
	//  En una aplicación MDI, esto debe ocurrir inmediatamente después de establecer m_pMainWnd

	// Analizar línea de comandos para comandos Shell estándar, DDE, Archivo Abrir
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Enviar comandos especificados en la línea de comandos. Devolverá FALSE si
	// la aplicación se inició con los modificadores /RegServer, /Register, /Unregserver o /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// La ventana principal se ha inicializado; mostrarla y actualizarla
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CMFCTestEditorApp::ExitInstance()
{
	//TODO: controlar recursos adicionales que se hayan podido agregar
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// Controladores de mensaje de CMFCTestEditorApp


// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Comando de la aplicación para ejecutar el cuadro de diálogo
void CMFCTestEditorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Métodos para cargar o guardar personalizaciones de  CMFCTestEditorApp

void CMFCTestEditorApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CMFCTestEditorApp::LoadCustomState()
{
}

void CMFCTestEditorApp::SaveCustomState()
{
}

// Controladores de mensaje de CMFCTestEditorApp



