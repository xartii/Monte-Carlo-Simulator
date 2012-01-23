#include "plot.h"

CPlot::~CPlot()
{
    plotWnd->DelAllLayers(true, true);
    /*delete xaxis;
    delete yaxis;
    delete nfo;
    delete plotWnd;*/
}

CPlot::CPlot(MainWnd* hWnd)
{
    plotWnd = new mpWindow(hWnd, -66, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER);
    plotWnd->Fit();


    xaxis = new mpScaleX(wxT("Czas [dni]"), mpALIGN_BOTTOM, true, mpX_NORMAL);
    yaxis = new mpScaleY(wxT("Wartość [zł]"), mpALIGN_LEFT, true);
    nfo = new mpInfoCoords(wxRect(700, 0, 0, 0));
    nfo->SetName(wxT("Very Long name, so it won't be reapeted"));
    nfo->ShowName(false);
    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);
    plotWnd->LockAspect(false);
    //plotWnd->DelAllLayers(false, true);
    plotWnd->SetMargins(40, 40, 50, 50);
    plotWnd->AddLayer(xaxis);
    plotWnd->AddLayer(yaxis);
    plotWnd->AddLayer(nfo);
    xaxis->SetTicks(false);
    yaxis->SetTicks(false);
    plotWnd->UpdateAll();
    plotWnd->EnableDoubleBuffer(true);
    plotWnd->SetMPScrollbars(false);
}

mpFXYVector* CPlot::Draw(MainWnd* hWnd,mCarloResults *results, wxColor color)
{

    //xaxis->SetTicks(true);

   // plotWnd->SetPos(0,0);
    //plotWnd->SetScaleX(results->xmax);
    //plotWnd->SetScaleY(results->ymax);
    vector = new mpFXYVector();
    vector->SetData(results->x, results->y);
    vector->SetContinuity(true);
    vector->SetMaxX(results->xmax);
    vector->SetMaxY(results->ymax);

    wxPen vectorPen(color, 1, wxSOLID);
    vector->SetPen(vectorPen);
    vector->SetDrawOutsideMargins(false);
    plotWnd->AddLayer(vector);

    plotWnd->Fit();
    return vector;
}

void CPlot::RemoveVector(mpFXYVector *tmp)
{
    plotWnd->DelLayer(tmp);
    delete tmp;
}

void CPlot::SetVisible(wxString label, wxCommandEvent &event)
{
    plotWnd->SetLayerVisible(label, event.IsChecked());
}
