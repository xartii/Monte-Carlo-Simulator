#ifndef OPTIONTREE_H_INCLUDED
#define OPTIONTREE_H_INCLUDED
#include "simulation.h"
#include "wx/wx.h"
#include "wx/arrimpl.cpp"
#include "wx/dialog.h"
#include "wx/clrpicker.h"

WX_DECLARE_OBJARRAY(double, ArrayOfDoubles);
WX_DECLARE_OBJARRAY(wxTextCtrl*, ArrayOfTextCtrls);


//class for holding information about one option
class Option: public wxTreeItemData
{
    private:
        static int count;
        wxString Desc_;
      	double Value_;
        double Interest_;
        double RiskFree_;
        double Volatility_;
        double Time_;
      

    public:
        Option(const wxString &desc): Desc_(desc) {}
        Option(const wxString &desc,
                   const double &v,
                   const double &i,
                   const double &r,
                   const double &vt,
                   const double &t) : Desc_(desc), Value_(v), Interest_(i), RiskFree_(r), Volatility_(vt), Time_(t) {count++;}
	~Option() { count--; }	

        const wxString& GetDesc() const { return Desc_; }
        void SetTime(const double &t) { Time_  = t; }
        void SetVolatility(const double &v) { Volatility_ = v; }
        void SetRiskFree(const double &r) { RiskFree_ = r; }
        void SetInterest(const double &i) { Interest_ = i; }
        void SetValue(const double &v) { Value_ = v; }
        double GetValue() const { return Value_; }
        double GetInterest() const { return Interest_; }
        double GetRiskFree() const { return RiskFree_; }
        double GetVolatility() const { return Volatility_; }
        double GetTime() const { return Time_; }
	//function for adding simulation
	//returns pointer to calculated simulation
        Simulation* AddSimulation(int g, int o, int it, double s);
        void RemoveSimulation(const wxTreeItemId&);
	//returns number of options
        static int GetCount() { return count; }

};

//class for handling dialog window for getting needed data from user
class SimulationDialog : public wxDialog
{

   DECLARE_EVENT_TABLE()

    private:
        int genType;
        int optionType;
        long iterations;
        double frequency;
        wxColour color;
        wxString label;
        wxArrayString freq, type, gen;
        ArrayOfDoubles freqs;
	//internal use only: adds controls to dialog window
        void CreateControls();

    public:
        SimulationDialog(wxWindow* parent,
                         wxWindowID id = wxID_ANY,
                         const wxString& caption = wxT("Add Simulation"),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxSize(400, 300),
                         long style = wxCAPTION|wxSYSTEM_MENU,
                         int g = 0,
                         int o = 0,
                         long it = 0,
                         double f = 0.1,
                         wxString l = wxT(""),
                         wxColour c = *wxBLUE): wxDialog(parent, id, caption, pos, size, style), genType(g), optionType(o), iterations(it), frequency(f), label(l)
                         {color = c;
                          this->CreateControls();};	

	//functions for getting data from dialog window
        int GetGenType() const { return genType; }
        int GetIterations() const { return iterations; }
        int GetOptionType() const { return optionType; }
        double GetStep() const { return frequency; }
        wxString GetLabel() const { return label; }
	//function executed when user clicks OK button
        void OnOk(wxCommandEvent &WXUNUSED(event));
        wxColour GetColor() const { return color; }
};
//class for dialog window for user data about option
class OptionDialog : public wxDialog
{

   DECLARE_EVENT_TABLE()

    private:
        long Time;
        double Value;
        double Volatility;
        double RiskFree;
        double Interest;
        wxString label;
	//internal use only: adds controls to dialog window
        void CreateControls();
        ArrayOfTextCtrls Ctrls;

    public:
        OptionDialog(wxWindow* parent,
                         wxWindowID id = wxID_ANY,
                         const wxString& caption = wxT("Dodaj opcję"),
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxSize(500, 250),
                         long style = wxCAPTION|wxSYSTEM_MENU,
                         long t = 0,
                         double v = 0,
                         double vt = 0,
                         double r = 0,
                         double i = 0,
                         wxString l = wxT("")): wxDialog(parent, id, caption, pos, size, style), Time(t), Value(v), Volatility(vt), RiskFree(r), Interest(i), label(l)
                         {this->CreateControls();};
	//function for getting user data form dialog window
        double GetTime() const { return Time; }
        double GetValue() const { return Value; }
        double GetVolatility() const { return Volatility; }
        double GetRiskFree() const { return RiskFree; }
        double GetInterest() const { return Interest; }
        wxString GetLabel() const { return label; }
	//function execute when user clicks OK button
        void OnOk(wxCommandEvent &WXUNUSED(event));
	//function to replace "." with "," which makes numbers correctly interpreted as float
        void Replace(wxCommandEvent &event);
};


#endif // OPTIONTREE_H_INCLUDED
