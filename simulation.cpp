#include "simulation.h"


void Simulation::calculate(const double Time_,
                           const double Value_,
                           const double Volatility_,
                           const double RiskFree_,
                           const double Interest_)
{
	double Sum = 0;
	double temp;
	double time;
	results.ymax=0;
	results.x.erase(results.x.begin(), results.x.end());
	results.y.erase(results.y.begin(), results.y.end());


	for(time = 0 ; time < Time_ ; time += step)
	{
    Sum = 0;
	for(int i = 0 ; i < iterations ; i++)
	{
	temp = Value_*RiskFree_*time + Value_*Volatility_*random(genType)*sqrt(time);
	if(optionType == CALL)
	{
		if(temp+Value_ > Interest_)
			Sum += Value_+temp - Interest_;
	}
	else
	{
		if(Interest_ > temp+Value_)
			Sum += Interest_ - (temp+Value_);
	}
	}

	Sum /= iterations;
	Sum = exp(-(RiskFree_*time))*Sum;
	results.y.push_back(Sum);
	results.x.push_back(time*365.25);
	results.xmax=time*365.25;
	if(Sum > results.ymax) results.ymax = Sum;
	}
}

double Simulation::random(int n = 0)
{
    double temp;
	switch(n)
	{
    case 0:
		temp = rand()%200001;
		temp -= 100000;
		temp /= 100000;
		break;

	case 1:
		int hFile;
		unsigned int buf;

		hFile = open("/dev/urandom", O_RDONLY);
		read(hFile, &buf, sizeof(buf));
		close(hFile);

		temp = buf%200001;
		temp -= 100000;
		temp /= 100000;
		break;

    case 2:
        static boost::mt19937 gen(static_cast<unsigned int>(time(0)));
        boost::normal_distribution<double> dist(0.0, 1.0);
        boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > BoostGen(gen, dist);
        temp = BoostGen();
        break;

	}

	return temp;
}
