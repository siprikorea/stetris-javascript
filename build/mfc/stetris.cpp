#include "stdafx.h"
#include "stetris.h"
#include "stetrisdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/************************************************************
 *	@brief		Message
 ************************************************************/
BEGIN_MESSAGE_MAP(CSTetrisApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CSTetrisApp theApp;

/************************************************************
 *	@brief		Constructor
 *	@retval		Nothing
 ************************************************************/
CSTetrisApp::CSTetrisApp()
{
}

/************************************************************
 *	@brief		Initialize instance
 *	@retval		Nothing
 ************************************************************/
BOOL CSTetrisApp::InitInstance()
{
	CWinApp::InitInstance();

	SetRegistryKey(_T("siprikorea"));

	CSTetrisDlg dlg;
	dlg.DoModal();

	return FALSE;
}
