#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED
#include "wx/wx.h"
#include "wx/treectrl.h"
#include "wx/arrimpl.cpp"
#include "wx/filedlg.h"
#include "wx/textfile.h"
#include "option.h"
#include <fstream>

WX_DECLARE_OBJARRAY(wxStaticText*, ArrayOfCaptions);


enum
{
    ID_Quit = 1,
};
class CPlot;

class MainWnd: public wxFrame
{
private:
    ArrayOfCaptions Caption;
    wxBoxSizer *BoxSizer, *SideSizer;
    wxPanel *SidePanel;
    wxTreeCtrl *tree;
    wxTreeItemId Root;
     CPlot *Plot;

public:
    MainWnd(const wxString &title, const wxPoint &position, const wxSize &size);
    void OnQuit(wxCommandEvent &event);
    void Fill(MainWnd* hWnd);
    void OnClick(wxCommandEvent &WXUNUSED(event));
    void ShowInfo(wxTreeEvent &WXUNUSED(event));
    void PopUp(wxTreeEvent &event);
    void OptRen(wxCommandEvent &WXUNUSED(event));
    void SimDel(wxCommandEvent &WXUNUSED(event));
    void SimChn(wxCommandEvent &WXUNUSED(event));
    void SimVis(wxCommandEvent &event);
    void SimCal(wxCommandEvent &WXUNUSED(event));
    void SimSav(wxCommandEvent &WXUNUSED(event));
    void OptChn(wxCommandEvent &WXUNUSED(event));
    void OptDel(wxCommandEvent &WXUNUSED(event));
    void OptSav(wxCommandEvent &WXUNUSED(event));
    void OptLoad(wxCommandEvent &WXUNUSED(event));

    DECLARE_EVENT_TABLE()
};



#endif // WINDOWS_H_INCLUDED
