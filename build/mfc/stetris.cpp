#include "stdafx.h"
#include "stetris.h"
#include "stetrisdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CSTetrisApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CSTetrisApp theApp;

CSTetrisApp::CSTetrisApp()
{
}

BOOL CSTetrisApp::InitInstance()
{
	CWinApp::InitInstance();

	CSTetrisDlg dlg;
	dlg.DoModal();

	return FALSE;
}
