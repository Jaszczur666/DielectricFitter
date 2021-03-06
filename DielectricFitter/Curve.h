#ifndef CURVE_H
#define CURVE_H
//#define ii std::complex <double>(0.0,1.0)
const double pi  =3.1415926535897932384626433;
#include <complex>
#include <vector>
#include "Eigen/Dense"
#include <ctime>
#include <limits>
//#include <boost/timer/timer.hpp>
//#include <boost/regex.hpp>
//#include <boost/regex.hpp>
using Eigen::MatrixXd;
//using namespace std;
class curve{
public:
	std::vector<double> Dataf;
	std::vector<double> Dataep;
	std::vector<double> Dataeb;
	double temperature;
	std::wstring filename;
	double en,de1,fp1,a1,de2,fp2,a2,de3,fp3,a3,s0,sj,n;
	double chi2;
	bool fitted;
	int funnum;
	void GuesstimateParameters(std::vector<double> Dataf, std::vector<double>Dataep, std::vector<double> Dataeb,MatrixXd &parameters);
	void FitLMGeneral(int type,MatrixXd &parameters);
	//void RegexHeader();
	curve()
	{
		fitted=false;
		en=1;
		de1=1;
		fp1=1;
		a1=0;
		de2=1;
		fp2=10;
		a2=0;
		de3=1;
		fp3=100;
		a3=0;
		s0=0;
		sj=0;
		n=1;
	}
};
std::complex<double> RelaxationFunction(int type,double frequency,const MatrixXd &parameters);
std::complex<double> SimpleColeDavidson(double frequency, double delta, double peakfreq, double alpha);
double chi2MatGeneral(std::vector<double>& dataf, std::vector<double>& dataep, std::vector<double>& dataeb,int type,MatrixXd parameters);
#endif