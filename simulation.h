#ifndef MCARLO_H_INCLUDED
#define MCARLO_H_INCLUDED
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>
#include <fcntl.h>
#include <vector>
#include <boost/random.hpp>
#include "wx/treectrl.h"
#include "mathplot.h"

using namespace std;

typedef struct
{
    std::vector<double> x;
    std::vector<double> y;
    double ymax, xmax;
} mCarloResults;

#define CALL  0
#define PUT   1
#define GEN_CSTDLIB 0
#define GEN_DEVRAND 1
#define GEN_BOOST   2

class Simulation : public wxTreeItemData
{
private:
    int genType;
    int optionType;
    int iterations;
    bool visible;
    double step;
	double random(int n);
	wxString desc;
	mCarloResults results;
	mpFXYVector *vector;

public:
    Simulation(const int &g, const int &o, const int &it, const double &s): genType(g), optionType(o), iterations(it), visible(true), step(s) {srand(time(NULL));}
    Simulation(): visible(true) { srand(time(NULL)); }
    
    const wxString& GetDesc() { return desc; }

	void calculate(const double Time_,
                   const double Value_,
                   const double Volatility_,
                   const double RiskFree_,
                   const double Interest_);

	void setGenType(int n = GEN_CSTDLIB){ genType = n; }
	void setOptionType(int n = CALL) { optionType = n; }
	void setIterations(int n) { iterations = n; }
	void setStep(double s) { step = s; }
	void setDesc(wxString d) { desc = d; }
	mCarloResults* GetResults() { return &results; }
	void SetResults(mCarloResults *r) { results = *r;}
	int GetGenType() const { return genType; }
	int GetIterations() const { return iterations; }
	int GetOptionType() const { return optionType; }
	double GetStep() const { return step; }
	mpFXYVector* GetVector() const { return vector; }
	void SetVector(mpFXYVector *tmp) { vector = tmp; }
	bool IsVisible() { return visible; }
	void ToggleVis() { visible = !visible; }


};



#endif // MCARLO_H_INCLUDED
