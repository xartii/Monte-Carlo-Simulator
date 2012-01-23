#include "option.h"

WX_DEFINE_OBJARRAY(ArrayOfDoubles)
WX_DEFINE_OBJARRAY(ArrayOfTextCtrls);

BEGIN_EVENT_TABLE(SimulationDialog, wxDialog)
    EVT_BUTTON(wxID_OK, SimulationDialog::OnOk)
END_EVENT_TABLE()

int Option::count = 0;
Simulation* Option::AddSimulation(int g, int o, int it, double s)
{
    Simulation *tmp = new Simulation(g,o,it,s);
    tmp->calculate(Time_/365.25, Value_, Volatility_, RiskFree_, Interest_);
    return tmp;
}


void SimulationDialog::CreateControls()
{
    color.Set(0,0,0);
    new wxStaticText(this, wxID_STATIC, wxT("Podaj parametry niezbędne do przeprowadzenia symulacji:"),
                                           wxPoint(5,5), wxDefaultSize);
    new wxStaticText(this, wxID_STATIC, wxT("Etykieta:"), wxPoint(5,43), wxDefaultSize, wxALIGN_LEFT);
    (new wxTextCtrl(this, -10, label, wxPoint(70, 40), wxSize(250, -1), wxTE_RIGHT))->SetFocus();
    new wxStaticText(this, wxID_STATIC, wxT("Wybierz kolor wykresu:"), wxPoint(5, 73), wxDefaultSize);
    new wxColourPickerCtrl(this, -666, color, wxPoint(160, 67), wxSize(100, 30));

    new wxStaticText(this, wxID_STATIC, wxT("Częstość próbkowania: "), wxPoint(5,105), wxDefaultSize);

    freq.Add(wxT("0.1"));
    freq.Add(wxT("0.01"));
    freq.Add(wxT("0.001"));
    freq.Add(wxT("0.0001"));
    freq.Add(wxT("0.00001"));
    freq.Add(wxT("0.000001"));

    freqs.Add(0.1);
    freqs.Add(0.01);
    freqs.Add(0.001);
    freqs.Add(0.0001);
    freqs.Add(0.00001);
    freqs.Add(0.000001);
    wxString tmp;
    tmp << frequency;
    tmp.Replace(wxT(","), wxT("."));
    new wxComboBox(this, -6, tmp, wxPoint(160,100), wxSize(100, -1), freq, wxCB_READONLY);
    new wxStaticText(this, wxID_STATIC, wxT("Rodzaj opcji: "), wxPoint(5,130), wxDefaultSize);

    type.Add(wxT("Kupno"));
    type.Add(wxT("Sprzedaż"));

    new wxComboBox(this, -7, type.Item(optionType), wxPoint(160,125), wxSize(100,-1), type, wxCB_READONLY);
    new wxStaticText(this, wxID_STATIC, wxT("Generator losowości: "), wxPoint(5,155), wxDefaultSize);


    gen.Add(wxT("cstdlib"));
    gen.Add(wxT("/dev/rand"));
    gen.Add(wxT("Mersenne Twister"));

    new wxComboBox(this, -8, gen.Item(genType), wxPoint(160,150), wxSize(100,-1), gen, wxCB_READONLY);
    new wxStaticText(this, wxID_STATIC, wxT("Ilość iteracji na punkt: "), wxPoint(5,185), wxDefaultSize);
    tmp = wxT("");
    tmp << iterations;
    new wxTextCtrl(this, -9, tmp, wxPoint(160,180), wxSize(100, -1), wxTE_RIGHT);
    new wxButton(this, wxID_OK, wxT("Oblicz"), wxPoint(210,230), wxSize(80,30));
    new wxButton(this, wxID_CANCEL, wxT("Anuluj"), wxPoint(300, 230), wxSize(80,30));

}

void SimulationDialog::OnOk(wxCommandEvent &WXUNUSED(event))
{

    if(!static_cast<wxTextCtrl*>(FindWindow(-9))->GetValue().ToLong(&iterations))
    {
        wxMessageBox(wxT("Podana ilość iteracji nie jest liczbą całkowitą!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }
    if(static_cast<wxTextCtrl*>(FindWindow(-10))->GetValue().IsEmpty())
    {
        wxMessageBox(wxT("Nie podano etykiety!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }
    label = static_cast<wxTextCtrl*>(FindWindow(-10))->GetValue();

    color = static_cast<wxColourPickerCtrl*>(FindWindow(-666))->GetColour();

    int freqType = 0;
    freqType = static_cast<wxComboBox*>(FindWindow(-6))->GetCurrentSelection();
    if(freqType != -1)
    frequency = freqs.Item(freqType);

    int optType = 0;
    optType = static_cast<wxComboBox*>(FindWindow(-7))->GetCurrentSelection();
    if(optType != -1)
    optionType = optType;

    genType = static_cast<wxComboBox*>(FindWindow(-8))->GetCurrentSelection();
    if(genType == -1)
        genType = 0;
    EndModal(wxID_OK);
}

BEGIN_EVENT_TABLE(OptionDialog, wxDialog)
    EVT_BUTTON(wxID_OK, OptionDialog::OnOk)
    EVT_TEXT(wxID_ANY, OptionDialog::Replace)
END_EVENT_TABLE()

void OptionDialog::CreateControls()
{
    wxString tmp;
    if(label == wxT(""))
    {
        tmp = wxT("Opcja nr ");
        tmp << Option::GetCount()+1;
    }
    else
    {
        tmp = label;
    }

    new wxStaticText(this, wxID_STATIC, wxT("Podaj parametry niezbędne do utworzenia opcji:"), wxPoint(5,5), wxDefaultSize);

    new wxStaticText(this, wxID_STATIC, wxT("Etykieta:"), wxPoint(5,43), wxDefaultSize, wxALIGN_LEFT);
    Ctrls.Add(new wxTextCtrl(this, -25, tmp, wxPoint(70, 40), wxSize(250, -1), wxTE_RIGHT));

    tmp = wxT("");
    if(Value != 0) tmp << Value;
    //!wartość opcji
    new wxStaticText(this, wxID_STATIC, wxT("Wartość opcji:"), wxPoint(5,103), wxDefaultSize, wxALIGN_LEFT);
    Ctrls.Add(new wxTextCtrl(this, -20, tmp, wxPoint(100,100), wxSize(100, -1), wxTE_RIGHT));
    new wxStaticText(this, wxID_STATIC, wxT("zł"), wxPoint(200,103), wxDefaultSize, wxALIGN_LEFT);

    tmp = wxT("");
    if(Interest != 0) tmp << Interest;
    //!wartość wykupu
    new wxStaticText(this, wxID_STATIC, wxT("Wartość wykupu:"), wxPoint(250,103), wxDefaultSize, wxALIGN_LEFT);
    Ctrls.Add(new wxTextCtrl(this, -21, tmp, wxPoint(370,100), wxSize(100,-1), wxTE_RIGHT));
    new wxStaticText(this, wxID_STATIC, wxT("zł"), wxPoint(470,103), wxDefaultSize, wxALIGN_LEFT);

    tmp = wxT("");
    if(RiskFree != 0) tmp << RiskFree;
    //!stopa zwrotu
    new wxStaticText(this, wxID_STATIC, wxT("Stopa zwrotu:"), wxPoint(5, 133), wxDefaultSize, wxALIGN_LEFT);
    Ctrls.Add(new wxTextCtrl(this, -22, tmp, wxPoint(100, 130), wxSize(100, -1), wxTE_RIGHT));

    tmp = wxT("");
    if(Volatility != 0) tmp << Volatility;
    //!zmienność
    new wxStaticText(this, wxID_STATIC, wxT("Zmienność:"), wxPoint(250,133), wxDefaultSize, wxALIGN_LEFT);
    Ctrls.Add(new wxTextCtrl(this, -23, tmp, wxPoint(370, 130), wxSize(100,-1), wxTE_RIGHT));

    tmp = wxT("");
    if(Time != 0) tmp << Time;
    //!czas
    new wxStaticText(this, wxID_STATIC, wxT("Czas trwania:"), wxPoint(5,163), wxDefaultSize, wxALIGN_LEFT);
    Ctrls.Add(new wxTextCtrl(this, -24, tmp, wxPoint(100, 160), wxSize(100,-1), wxTE_RIGHT));
    new wxStaticText(this, wxID_STATIC, wxT("dni"), wxPoint(200,163), wxDefaultSize, wxALIGN_LEFT);

    (Time != 0)? tmp = wxT("Zmień"): tmp = wxT("Dodaj");
     new wxButton(this, wxID_OK, tmp, wxPoint(300,200), wxSize(80,30));
     new wxButton(this, wxID_CANCEL, wxT("Anuluj"), wxPoint(400, 200), wxSize(80,30));

     Centre();
     Ctrls.Item(1)->SetFocus();

}



void OptionDialog::OnOk(wxCommandEvent &WXUNUSED(event))
{
    if(!Ctrls.Item(1)->GetValue().ToDouble(&Value))
    {
        wxMessageBox(wxT("Podana wartość opcji nie jest liczbą!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }

    if(!Ctrls.Item(2)->GetValue().ToDouble(&Interest))
    {
        wxMessageBox(wxT("Podana wartość wykupu nie jest liczbą!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }

    if(!Ctrls.Item(3)->GetValue().ToDouble(&RiskFree))
    {
        wxMessageBox(wxT("Podana stopa zwrotu nie jest liczbą!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }

    if(!Ctrls.Item(4)->GetValue().ToDouble(&Volatility))
    {
        wxMessageBox(wxT("Podana zmienność nie jest liczbą!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }

    if(!Ctrls.Item(5)->GetValue().ToLong(&Time))
    {
        wxMessageBox(wxT("Podana ilość dni nie jest liczbą!"), wxT("Błąd"), wxICON_ERROR, this);
        return;
    }

    label = Ctrls.Item(0)->GetValue();
    EndModal(wxID_OK);
}

void OptionDialog::Replace(wxCommandEvent &event)
{
    wxTextCtrl *ctrl = (wxTextCtrl*)FindWindow(event.GetId());
    wxString tmp = ctrl->GetValue();
    tmp.Replace(wxT("."), wxT(","), true);
    ctrl->ChangeValue(tmp);
}
