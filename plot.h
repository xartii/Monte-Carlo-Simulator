#ifndef PLOT_H_INCLUDED
#define PLOT_H_INCLUDED
#include "mathplot.h"
#include "wx/wx.h"
#include "windows.h"
#include "simulation.h"

class CPlot
{
private:
    mpWindow *plotWnd;
    mpFXYVector *vector;
    mpScaleX *xaxis;
    mpScaleY *yaxis;
    mpInfoCoords *nfo;
public:
    CPlot(MainWnd* hWnd);
    ~CPlot();
    mpWindow* GetPlotPtr() { return plotWnd; }
    mpFXYVector* Draw(MainWnd* hWnd, mCarloResults *results, wxColor color);
    void RemoveVector(mpFXYVector*);
    void SetVisible(wxString , wxCommandEvent&);
};


#endif // PLOT_H_INCLUDED
