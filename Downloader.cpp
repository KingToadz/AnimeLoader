#include "stdafx.h"
#include "Downloader.h"
#include <iostream>
#include <urlmon.h>
#include <tchar.h>
#pragma comment(lib, "urlmon.lib")

Downloader::Downloader(void)
{
}

bool Downloader::Load()
{
	
	HRESULT hr = URLDownloadToFile ( NULL, _T("http://www.animecalendar.net/user/ical/10578/0376ab712a1ee9d85e4e81aeea2e0789"), _T("calendar"), 0, NULL );
	if( hr == 0 ){
		std::cout << "Downloaded file" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Downloaded FAILED" << std::endl;
		return false;
	}
}


Downloader::~Downloader(void)
{
}
