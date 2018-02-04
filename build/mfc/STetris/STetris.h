#pragma once
#include "resource.h"

class CSTetrisApp : public CWinApp
{
public:
	// Constructor
	CSTetrisApp();

public:
	// Initalize instance
	virtual BOOL InitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};

extern CSTetrisApp theApp;
