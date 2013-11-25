#define ii std::complex <double>(0.0,1.0)
#include <complex>
#include <vector>
#include "Dense"
#include <ctime>
#include <limits>
#include <boost/timer/timer.hpp>
using Eigen::MatrixXd;

class curve{
public:
vector<double> Dataf;
vector<double> Dataep;
vector<double> Dataeb;
double temperature;
double en,de1,fp1,a1,de2,fp2,a2,de3,fp3,a3;
bool fitted;
bool twofunctions;
};

void GuesstimateParameters(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters)
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
	cout <<maxebf<<" "<<maxep<<" "<<minep<<endl;
}

double Correction(double temperature,double midjumptemp, double scalex,double jump)
{
	double corr;
	corr=0.5*jump*(1+tanh(scalex*(temperature-midjumptemp)));
	return corr;
}

std::complex<double> HNRelaxation(double frequency,MatrixXd parameters){
	complex <double> d;
	d=parameters(0)+parameters(1)/pow((1.0+pow(ii*frequency/parameters(2),parameters(3))),parameters(4));
	return d;
}

std::complex<double> DoubleColeDavidson(double frequency,MatrixXd parameters){
complex <double> d;
d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)));
return d;
}
std::complex<double> TripleColeDavidson(double frequency,MatrixXd parameters){
complex <double> d;
d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)))+parameters(7)/(1.0+pow(ii*frequency/parameters(8),1-parameters(9)));
return d;
}

std::complex<double> SimpleColeDavidson(double frequency, double delta, double peakfreq, double alpha){
complex <double> d;
d=delta/(1.0+pow(ii*frequency/peakfreq,1-alpha));
return d;
}

std::complex<double> RelaxationFunction(int type,double frequency,const MatrixXd &parameters){
	complex <double> d;
	int parsize;
	d=0;
	parsize=parameters.rows();
	//cout <<"Debug 4321 " <<parameters(0)<<" "<<parameters(1)<<" "<<parameters(2)<<" "<<parameters(3)<<endl;
	if (type==1)  d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)));
	if (type==2)  d=DoubleColeDavidson(frequency,parameters);
	if (type==3)  d=TripleColeDavidson(frequency,parameters);
	//cout<<d<<endl;
	return d;
}


void CalculateResidueGeneral(int type,double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb)
{
	double pep,peb;
	complex <double> d;
	d=RelaxationFunction(type,f,parameters);
	pep=std::real(d);
	peb=std::imag(d);
	rp=ep-pep;
	rb=eb-peb;
}

void CalculateHessianGeneral(vector<double> dataf,vector<double> dataep,vector<double> dataeb, int type, MatrixXd parameters,MatrixXd &Hess, MatrixXd &Grad, double &chi2)
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
	complex <double> d;
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


double chi2MatGeneral( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,int type,MatrixXd parameters)
{
	complex <double> d;
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

void FitLMGeneral(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,int type,MatrixXd &parameters)
{
	int i,size,size2;
	double lambda;
	double chi2,chi2n;//,chi2c;
//	bool growing;
	MatrixXd Hessian,Hessiandiag, Grad, newParams,error;
//	growing=false;
	lambda=1/1024.0;
	chi2=0;
	clock_t start, end;
	start=clock();
	boost::timer::cpu_timer timer;
	for(i=1;i<100;i++)
	{
		//chi2c=chi2;
		CalculateHessianGeneral(Dataf,Dataep,Dataeb,type,parameters, Hessian, Grad,chi2);
		Hessiandiag=Hessian.diagonal().asDiagonal();
		newParams=parameters-((Hessian+lambda*Hessiandiag).inverse()*Grad);
		chi2n=chi2MatGeneral(Dataf,Dataep,Dataeb,type,newParams);
		if (chi2n<chi2){
			parameters=newParams;
			lambda=lambda*sqrt(2.0);
		}
		else
		{
			lambda=lambda/sqrt(2.0);
		}
	}
	size=parameters.rows();
	size2=Dataf.size();
	error=(Hessiandiag.inverse().diagonal()*chi2/(size2-size));
	for (i=0;i<size;i++) error(i)=sqrt(error(i));
	//cout<<error<<endl<< "----------------------------------------------------- "<<endl;
	cout <<chi2<<endl;
	boost::timer::cpu_times elapsed = timer.elapsed();
	end=clock();
	cout <<(double(end - start) / CLOCKS_PER_SEC) <<" s"<<endl;//<<" "<< CLOCKS_PER_SEC<<endl;
	std::cout << " CPU TIME: " << (elapsed.user + elapsed.system) / 1e9 << " seconds" << " WALLCLOCK TIME: " << elapsed.wall / 1e9 << " seconds"<< std::endl;
	return;
}

void linearFit(vector <double>x, vector <double>y,double &a,double &b,double &r2){
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