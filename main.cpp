/******************************************************************************
 * Name:      Monte Carlo Simulator
 * File:      main.cpp
 * Purpose:   Simulator for european financial options
 * Author:    Artur Wojcik (xartii@gmail.com)
 * Created:   2011-11-18
 * Copyright: Artur Wojcik
 * License:   GNU GPL v3
 *
 * This file is part of Monte Carlo Simulator.
 *
 * Monte Carlo Simulator is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
 #include "wx/wx.h"
 #include "windows.h"
 #include "main.h"

 IMPLEMENT_APP(MainApp)


bool MainApp::OnInit()
{
    MainWnd* hWnd = new MainWnd(_("European financial options simualtor"), wxPoint(0,0),  wxDefaultSize);
    hWnd->Fill(hWnd);
    hWnd->Show(true);
    SetTopWindow(hWnd);
    return true;
}

