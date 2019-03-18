//TestForm.CPP - MFC

#include <afxwin.h>


class TestForm :public CFrameWnd
{
public:
    TestForm()
    {
        Create( NULL, TEXT("MFC TestForm") );

		//FastColoredTextBoxNS::IronyFCTB^  editorFCTB;

    }

};

class MyApp :public CWinApp
{
   TestForm *wnd; 
public:
   BOOL InitInstance()
   {
       wnd = new TestForm();
       m_pMainWnd = wnd;
       m_pMainWnd->ShowWindow(SW_SHOW);
       return TRUE;
   }
};

MyApp theApp
;
//End of program MFC Tutorial Part 1