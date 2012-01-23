/***************************************************************
 * Name:      opcje_finansoweApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Artur Wójcik (xartii@gmail.com)
 * Created:   2011-11-18
 * Copyright: Artur Wójcik ()
 * License:   copyleft
 **************************************************************/
 #include "wx/wx.h"
 #include "windows.h"
 #include "main.h"

 IMPLEMENT_APP(MainApp)


bool MainApp::OnInit()
{
    MainWnd* hWnd = new MainWnd(_("Kalkulator europejskich opcji finansowych"), wxPoint(0,0),  wxDefaultSize);
    hWnd->Fill(hWnd);
    hWnd->Show(true);
    SetTopWindow(hWnd);
    return true;
}

