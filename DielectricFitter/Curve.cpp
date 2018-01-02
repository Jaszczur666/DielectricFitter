#define ii std::complex <double>(0.0,1.0)
//const double pi  =3.1415926535897932384626433;
#include <complex>
#include <vector>
#include "Eigen\Dense"
#include <ctime>
#include <limits>
#include <boost/timer/timer.hpp>
#include <boost/chrono.hpp>
#include <boost/tr1/regex.hpp>
#include "Curve.h"
//#include "Fitowanie.h"
using Eigen::MatrixXd;
void linearFit(std::vector <double>x, std::vector <double>y,double &a,double &b,double &r2);
void linearFit(MatrixXd x, MatrixXd y,double &a,double &b,double &r2);
std::complex<double> HNRelaxation(double frequency,MatrixXd parameters){
	std::complex <double> d;
	d=parameters(0)+parameters(1)/pow((1.0+pow(ii*frequency/parameters(2),parameters(3))),parameters(4));
	return d;
}

std::complex<double> DoubleColeDavidson(double frequency,MatrixXd parameters){
	std::complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)));
	return d;
}
std::complex<double> TripleColeDavidson(double frequency,MatrixXd parameters){
	std::complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)))+parameters(7)/(1.0+pow(ii*frequency/parameters(8),1-parameters(9)));
	return d;
}
std::complex<double> DoubleColeDavidsonWithConductivity(double frequency,MatrixXd parameters){
	std::complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*parameters(7);
	return d;
}
std::complex<double> TripleColeDavidsonWithConductivity(double frequency,MatrixXd parameters){
	std::complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)))+parameters(7)/(1.0+pow(ii*frequency/parameters(8),1-parameters(9)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*parameters(10);
	return d;
}

std::complex<double> SimpleColeDavidson(double frequency, double delta, double peakfreq, double alpha){
	std::complex <double> d;
	d=delta/(1.0+pow(ii*frequency/peakfreq,1-alpha));
	return d;
}

std::complex<double> RelaxationFunction(int type,double frequency,const MatrixXd &parameters){
	std::complex <double> d;
	int parsize;
	d=0;
	parsize=parameters.rows();
	//std::cout <<"Debug 4321 " <<parameters(0)<<" "<<parameters(1)<<" "<<parameters(2)<<" "<<parameters(3)<<std::endl;
	if (type==1)  d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)));
	if (type==2)  d=DoubleColeDavidson(frequency,parameters);
	if (type==3)  d=TripleColeDavidson(frequency,parameters);
	if (type==4)  d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*parameters(4);
	if (type==5)  d=DoubleColeDavidsonWithConductivity(frequency,parameters);
	if (type==6)  d=TripleColeDavidsonWithConductivity(frequency,parameters);
	if (type==7)  d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*(parameters(4)*pow(ii*2.0*pi*frequency,parameters(5)));
	//std::cout<<d<<std::endl;
	return d;
}



void linearFit(std::vector <double>x, std::vector <double>y,double &a,double &b,double &r2){
	int size;
	double s,sx,sy,sxx,sxy,syy,d;
	size=x.size();
	s=size;
	sx=sy=sxx=sxy=syy=d=0;
	for (int i=0;i<size;i++){
		sx+=x[i];
		sy+=y[i];
		sxx+=x[i]*x[i];
		sxy+=x[i]*y[i];
		syy+=y[i]*y[i];
	}
	d=s*sxx-sx*sx;
	a=(s*sxy-sx*sy)/d;
	b=(sxx*sy-sx*sxy)/d;
	r2=(s*sxy-sx*sy)/(sqrt((s*sxx-sx*sx)*(s*syy-sy*sy)));
}

void linearFit(MatrixXd x, MatrixXd y,double &a,double &b,double &r2){
	int size;
	double s,sx,sy,sxx,sxy,syy,d;
	size=x.size();
	s=size;
	sx=sy=sxx=sxy=syy=d=0;
	for (int i=0;i<size;i++){
		sx+=x(i);
		sy+=y(i);
		sxx+=x(i)*x(i);
		sxy+=x(i)*y(i);
		syy+=y(i)*y(i);
	}
	d=s*sxx-sx*sx;
	a=(s*sxy-sx*sy)/d;
	b=(sxx*sy-sx*sxy)/d;
	r2=(s*sxy-sx*sy)/(sqrt((s*sxx-sx*sx)*(s*syy-sy*sy)));
}
void CalculateCorrelation(std::vector<double> dataf, std::vector<double> dataep, std::vector<double> dataeb, int type, MatrixXd parameters)
{	
	int size,i;
	double pep,peb,a,b,r;
	std::complex <double> d;
	size=dataf.size();
	MatrixXd Theor(2*size,1);
	MatrixXd Exp(2*size,1);
	for (i=0;i<=size-1;i++)
	{
	d=RelaxationFunction(type,dataf[i],parameters);
	pep=std::real(d);
	peb=std::imag(d);
		Theor(i*2,0)=pep;
		Theor(i*2+1,0)=peb;
		Exp(2*i,0)=dataep[i];
		Exp(2*i+1,0)=dataeb[i];
	}
	a=0;
	b=0;
	r=0;
	linearFit(Exp,Theor,a,b,r);
	std::cout<<"a= "<<a<<" b= "<<b<<std::endl;
	std::cout<<"R2 = "<<r<<" 1-r^2 = "<<1-r <<std::endl;

}



double chi2MatGeneral(std::vector<double>& dataf, std::vector<double>& dataep, std::vector<double>& dataeb,int type,MatrixXd parameters)
{
	std::complex <double> d;
	int i, size;
	double ep,eb;
	double chi2temp=0.0;
	size=dataf.size();
	for (i=0;i<=size-1;i++)
	{
		d=RelaxationFunction(type,dataf[i],parameters);
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp/2.0;
}

void CalculateResidueGeneral(int type,double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb)
{
	double pep,peb;
	std::complex <double> d;
	d=RelaxationFunction(type,f,parameters);
	pep=std::real(d);
	peb=std::imag(d);
	rp=ep-pep;
	rb=eb-peb;
}
void CalculateHessianGeneral(std::vector<double> dataf, std::vector<double> dataep, std::vector<double> dataeb, int type, MatrixXd parameters,MatrixXd &Hess, MatrixXd &Grad, double &chi2)
{
	int i,j,size,parsize;
	MatrixXd Hessian;
	double rp,rb,rsp,rsb;
	double eps;
	size=dataf.size();
	parsize=parameters.rows();
	MatrixXd delta(parsize,1);
	MatrixXd Jaco(2*size,parsize);
	MatrixXd Res(2*size,1);
	std::complex <double> d;
	eps=1e-7;
	chi2=0;
	for (i=0;i<=size-1;i++)
	{
		CalculateResidueGeneral(type,dataf[i],dataep[i],dataeb[i],parameters,rp,rb);
		for (j=0;j<parsize;j++){
			delta=MatrixXd::Zero(parsize,1);
			delta(j,0)=eps;
			CalculateResidueGeneral(type,dataf[i],dataep[i],dataeb[i],parameters+delta,rsp,rsb);
			Jaco(i*2,j)=(rsp-rp)/eps;
			Jaco(i*2+1,j)=(rsb-rb)/eps;
		}
		Res(i*2,0)=rp;
		Res(i*2+1,0)=rb;
		chi2=chi2+0.5*(rp*rp+rb*rb);
	}
	Hess=Jaco.transpose()*Jaco;
	Grad=Jaco.transpose()*Res;
}
void curve::GuesstimateParameters(std::vector<double> Dataf, std::vector<double>Dataep, std::vector<double> Dataeb,MatrixXd &parameters)
{
	int i,size;
	double maxeb,maxep,minep,maxebf;
	maxebf=-1;
	size=Dataf.size();
	maxeb=Dataeb[0];
	maxep=Dataep[0];
	minep=maxep;
	for (i=0;i<size;i++)
	{
		if (Dataeb[i]<maxeb) 
		{
			maxeb=Dataeb[i];
			maxebf=Dataf[i];
		}
		if (Dataep[i]>maxep) maxep=Dataep[i];
		if (Dataep[i]<minep) minep=Dataep[i];
	}
	parameters<<maxep,minep,maxebf,0.5+maxeb/(maxep-minep);
	std::cout <<maxebf<<" "<<maxep<<" "<<minep<<std::endl;
}
void curve::FitLMGeneral(int type,MatrixXd &parameters)
{
	int i,size,size2;
	double lambda;
	double chi2,chi2n;//,chi2c;
	//	bool growing;
	MatrixXd Hessian,Hessiandiag, Grad, newParams,error;
	//	growing=false;
	lambda=1/1024.0;
	chi2=0;
	//clock_t start, end;
	//start=clock();
	boost::timer::cpu_timer timer;
	for(i=1;i<100;i++)
	{
		//chi2c=chi2;
		CalculateHessianGeneral(this->Dataf,this->Dataep,this->Dataeb,type,parameters, Hessian, Grad,chi2);
		Hessiandiag=Hessian.diagonal().asDiagonal();
		newParams=parameters-((Hessian+lambda*Hessiandiag).inverse()*Grad);
		chi2n=chi2MatGeneral(this->Dataf,this->Dataep,this->Dataeb,type,newParams);
		if (chi2n<chi2){
			parameters=newParams;
			lambda=lambda*sqrt(2.0);
		}
		else
		{
			lambda=lambda/sqrt(2.0);
		}
	}
	CalculateCorrelation(this->Dataf,this->Dataep,this->Dataeb,type,parameters);
	size=parameters.rows();
	size2=Dataf.size();
	error=(Hessiandiag.inverse().diagonal()*chi2/(size2-size));
	for (i=0;i<size;i++) error(i)=sqrt(error(i));
	//std::cout<<error<<std::endl<< "----------------------------------------------------- "<<std::endl;
	std::cout <<chi2<<std::endl;
	this->chi2=chi2;
	boost::timer::cpu_times elapsed = timer.elapsed();
	//end=clock();
	//std::cout <<(double(end - start) / CLOCKS_PER_SEC) <<" s"<<std::endl;//<<" "<< CLOCKS_PER_SEC<<std::endl;
	std::cout << "Type: "<< type<<std::endl;
	std::cout << "Fitting took " << elapsed.wall / 1e9 << " seconds"<< std::endl;
	return;
}
