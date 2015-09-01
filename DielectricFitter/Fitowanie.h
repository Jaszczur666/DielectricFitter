#ifndef FITOWANIE_H
#define FITOWANIE_H
#define ii std::complex <double>(0.0,1.0)
//const double pi  =3.1415926535897932384626433;
#include <complex>
#include <vector>
#include "Dense"
#include <ctime>
#include <limits>
#include <fstream> 
#include <boost/timer/timer.hpp>
#include <boost/tr1/regex.hpp>
#include "Curve.h"
#include "Parser.h"
using Eigen::MatrixXd;
using namespace System;
using namespace std;

class experiment{
public:
	vector <curve> CurveSet;
	double c0;
	bool IsGeometrySpecified;
	bool IsGenerated;
	experiment()
	{
		IsGeometrySpecified=false;
		IsGenerated=false;
	}
};

class  curvesetrev{
public:
	vector<vector<double>> ep;
	vector<vector<double>> eb;
	vector<vector<double>> temp;
	vector<double> f;
	void LoadTempProfFromFile(String^ Filename);
	void LoadTempProfFromFile(wstring Filename);
	bool IsSame(curvesetrev compared);
	bool operator==(const curvesetrev &compared) const;
};

void curve::RegexHeader()
{
	string line;
	string name;
	double f, ep, eb;
	name="d:\\DME0.txt";
	ifstream inpfile(name);
	inpfile.clear();
	cout << "Attempting to read from "<<name<<endl;
	while (getline(inpfile,line)){
	regex namedate("([A-Za-z0-9_]+), (\\d\\d\\.\\d\\d?.\\d\\d\\d\\d), (\\d\\d:\\d\\d)");
	regex expr("Fixed value\\(s\\) :  Temp\\. \\[°C\\]=([-+]?[0-9]*\\.?[0-9]*)  AC Volt  \\[Vrms\\]=([-+]?[0-9]*\\.?[0-9]*)"); // Fixed value\(s\) :  Temp\. \[°C\]=(-?\d*(?:\.\d+)?)  AC Volt  \[Vrms\]=(-?\d*(?:\.\d+)?)
	regex data("([- ]?\\d+(?:\\.\\d+)?(?:e(?:\\+|-)\\d+)?)\\t([- ]?\\d+(?:\\.\\d+)?(?:e(?:\\+|-)\\d+)?)\\t([- ]?\\d+(?:\\.\\d+)?(?:e(?:\\+|-)\\d+)?)");
	smatch match;
	//cout<<"Line is "<<line<<endl;
	if ( regex_search( line, match, namedate ) ) {
    string dots = match[1];
    string chars = match[2];
	cout <<"Name "<<match[1] <<"  date: "<<match[2]<<" hour: "<<match[3] <<endl;
    }
	else
	{
	//cout <<"no match"<<endl;
	}
	if ( regex_search( line, match, data) ) {
   cout<<"Data block found"<<endl;
   break;
    }
	else
	{
//	cout <<"no data match"<<endl;
	}
	}
	 stringstream lineStream(line);
	lineStream>>f>>ep>>eb;
	cout<<f<<" i " <<ep<<" oraz "<<eb<<endl;
	while (getline(inpfile,line)){
		 stringstream lineStream(line);
			lineStream>>f>>ep>>eb;
	cout<<f<<" i " <<ep<<" oraz "<<eb<<endl;
	}
};
bool curvesetrev::IsSame(curvesetrev compared){
return ((this->f==compared.f)&&(this->ep==compared.ep)&&(this->eb==compared.eb)&&(this->temp==compared.temp));
};
bool curvesetrev::operator==(const curvesetrev &compared) const {
    return ((this->f==compared.f)&&(this->ep==compared.ep)&&(this->eb==compared.eb)&&(this->temp==compared.temp));
  };
void curvesetrev::LoadTempProfFromFile(String^ Filename){
	wstring name;
	string printname,line;
	double ep,eb,f,t;//,fp,fb;
	vector<double> vep,veb,vt;
	MarshalString(Filename,name);
	MarshalString(Filename,printname);
	cout <<"Reading file "<<printname<<endl;
	ifstream inpfile(name);
	inpfile>>f;

	getline(inpfile,line);
	//cout<<f<<endl;
	while (getline(inpfile, line)){
    stringstream lineStream(line);
	//while(inpfile >> t >> ep>>eb>>fp>>fb){
		//cout<<t<<" "<<ep<<" "<<eb<<endl;
		lineStream>>t>>ep>>eb;
		vt.push_back(t);
		vep.push_back(ep);
		veb.push_back(eb);
	};
	this->f.push_back(f);
	this->temp.push_back(vt);
	this->ep.push_back(vep);
	this->eb.push_back(veb);
};
void curvesetrev::LoadTempProfFromFile(wstring Filename){
	wstring name;
	string printname,line;
	double ep,eb,f,t;//,fp,fb;
	vector<double> vep,veb,vt;
	name=Filename;
	printname=string( Filename.begin(), Filename.end() );;
	cout <<"Reading file "<<printname<<endl;
	ifstream inpfile(name);
	inpfile>>f;
		getline(inpfile,line);
	//cout<<f<<endl;
	//while(inpfile >> t >> ep>>eb>>fp>>fb){
		//cout<<t<<" "<<ep<<" "<<eb<<endl;
		while (getline(inpfile, line)){
    stringstream lineStream(line);
	lineStream>>t>>ep>>eb;
		vt.push_back(t);
		vep.push_back(ep);
		veb.push_back(eb);
	};
	this->f.push_back(f);
	this->temp.push_back(vt);
	this->ep.push_back(vep);
	this->eb.push_back(veb);
};



double Correction(double temperature,double midjumptemp, double scalex,double jump)
{
	double corr;
	corr=0.5*jump*(1+tanh(scalex*(temperature-midjumptemp)));
	return corr;
}

#endif