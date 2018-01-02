#ifndef FITOWANIE_H
#define FITOWANIE_H
#define ii std::complex <double>(0.0,1.0)
//const double pi  =3.1415926535897932384626433;
#include <complex>
#include <vector>
#include "Eigen\Dense"
#include <ctime>
#include <limits>
#include <fstream> 
#include <boost/timer/timer.hpp>
#include <boost/regex.hpp>
#include "Curve.h"
#include "Parser.h"
using Eigen::MatrixXd;
using namespace System;
//using namespace std;

class experiment {
public:
	std::vector <curve> CurveSet;
	double c0;
	bool IsGeometrySpecified;
	bool IsGenerated;
	experiment()
	{
		IsGeometrySpecified = false;
		IsGenerated = false;
	}
};

class  curvesetrev {
public:
	std::vector<std::vector<double>> ep;
	std::vector<std::vector<double>> eb;
	std::vector<std::vector<double>> temp;
	std::vector<double> f;
	void LoadTempProfFromFile(String^ Filename);
	void LoadTempProfFromFile(std::wstring Filename);
	bool IsSame(curvesetrev compared);
	bool operator==(const curvesetrev &compared) const;
};

void curve::RegexHeader()
{
	std::string line;
	std::string name;
	double f, ep, eb;
	name = "d:\\DME0.txt";
	std::ifstream inpfile(name);
	inpfile.clear();
	std::cout << "Attempting to read from " << name << std::endl;
	while (getline(inpfile, line)) {
		boost::regex namedate("([A-Za-z0-9_]+), (\\d\\d\\.\\d\\d?.\\d\\d\\d\\d), (\\d\\d:\\d\\d)");
		boost::regex expr("Fixed value\\(s\\) :  Temp\\. \\[°C\\]=([-+]?[0-9]*\\.?[0-9]*)  AC Volt  \\[Vrms\\]=([-+]?[0-9]*\\.?[0-9]*)"); // Fixed value\(s\) :  Temp\. \[°C\]=(-?\d*(?:\.\d+)?)  AC Volt  \[Vrms\]=(-?\d*(?:\.\d+)?)
		boost::regex data("([- ]?\\d+(?:\\.\\d+)?(?:e(?:\\+|-)\\d+)?)\\t([- ]?\\d+(?:\\.\\d+)?(?:e(?:\\+|-)\\d+)?)\\t([- ]?\\d+(?:\\.\\d+)?(?:e(?:\\+|-)\\d+)?)");
		boost::smatch match;
		//std::cout<<"Line is "<<line<<std::endl;
		if (regex_search(line, match, namedate)) {
			std::string dots = match[1];
			std::string chars = match[2];
			std::cout << "Name " << match[1] << "  date: " << match[2] << " hour: " << match[3] << std::endl;
		}
		else
		{
			//std::cout <<"no match"<<std::endl;
		}
		if (regex_search(line, match, data)) {
			std::cout << "Data block found" << std::endl;
			break;
		}
		else
		{
			//	std::cout <<"no data match"<<std::endl;
		}
	}
	std::stringstream lineStream(line);
	lineStream >> f >> ep >> eb;
	std::cout << f << " i " << ep << " oraz " << eb << std::endl;
	while (getline(inpfile, line)) {
		std::stringstream lineStream(line);
		lineStream >> f >> ep >> eb;
		std::cout << f << " i " << ep << " oraz " << eb << std::endl;
	}
};
bool curvesetrev::IsSame(curvesetrev compared) {
	return ((this->f == compared.f) && (this->ep == compared.ep) && (this->eb == compared.eb) && (this->temp == compared.temp));
};
bool curvesetrev::operator==(const curvesetrev &compared) const {
	return ((this->f == compared.f) && (this->ep == compared.ep) && (this->eb == compared.eb) && (this->temp == compared.temp));
};
void curvesetrev::LoadTempProfFromFile(String^ Filename) {
	std::wstring name;
	std::string printname, line;
	double ep, eb, f, t;//,fp,fb;
	std::vector<double> vep, veb, vt;
	MarshalString(Filename, name);
	MarshalString(Filename, printname);
	std::cout << "Reading file " << printname << std::endl;
	std::ifstream inpfile(name);
	inpfile >> f;

	getline(inpfile, line);
	//std::cout<<f<<std::endl;
	while (getline(inpfile, line)) {
		std::stringstream lineStream(line);
		//while(inpfile >> t >> ep>>eb>>fp>>fb){
			//std::cout<<t<<" "<<ep<<" "<<eb<<std::endl;
		lineStream >> t >> ep >> eb;
		vt.push_back(t);
		vep.push_back(ep);
		veb.push_back(eb);
	};
	this->f.push_back(f);
	this->temp.push_back(vt);
	this->ep.push_back(vep);
	this->eb.push_back(veb);
};
void curvesetrev::LoadTempProfFromFile(std::wstring Filename) {
	std::wstring name;
	std::string printname, line;
	double ep, eb, f, t;//,fp,fb;
	std::vector<double> vep, veb, vt;
	name = Filename;
	printname = std::string(Filename.begin(), Filename.end());;
	std::cout << "Reading file " << printname << std::endl;
	std::ifstream inpfile(name);
	inpfile >> f;
	getline(inpfile, line);
	//std::cout<<f<<std::endl;
	//while(inpfile >> t >> ep>>eb>>fp>>fb){
		//std::cout<<t<<" "<<ep<<" "<<eb<<std::endl;
	while (getline(inpfile, line)) {
		std::stringstream lineStream(line);
		lineStream >> t >> ep >> eb;
		vt.push_back(t);
		vep.push_back(ep);
		veb.push_back(eb);
	};
	this->f.push_back(f);
	this->temp.push_back(vt);
	this->ep.push_back(vep);
	this->eb.push_back(veb);
};



double Correction(double temperature, double midjumptemp, double scalex, double jump)
{
	double corr;
	corr = 0.5*jump*(1 + tanh(scalex*(temperature - midjumptemp)));
	return corr;
}

#endif