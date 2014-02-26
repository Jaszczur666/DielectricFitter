#define ii std::complex <double>(0.0,1.0)
const double pi  =3.1415926535897932384626433;
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
	wstring filename;
	double en,de1,fp1,a1,de2,fp2,a2,de3,fp3,a3,s0;
	double chi2;
	bool fitted;
	int funnum;
	void GuesstimateParameters(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters);
	void FitLMGeneral(int type,MatrixXd &parameters);
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
	}
};
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

bool curvesetrev::IsSame(curvesetrev compared){
return ((this->f==compared.f)&&(this->ep==compared.ep)&&(this->eb==compared.eb)&&(this->temp==compared.temp));
};
bool curvesetrev::operator==(const curvesetrev &compared) const {
    return ((this->f==compared.f)&&(this->ep==compared.ep)&&(this->eb==compared.eb)&&(this->temp==compared.temp));
  };
void curvesetrev::LoadTempProfFromFile(String^ Filename){
	wstring name;
	string printname,line;
	double ep,eb,f,t,fp,fb;
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
	double ep,eb,f,t,fp,fb;
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

void curve::GuesstimateParameters(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters)
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
std::complex<double> DoubleColeDavidsonWithConductivity(double frequency,MatrixXd parameters){
	complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*parameters(7);
	return d;
}
std::complex<double> TripleColeDavidsonWithConductivity(double frequency,MatrixXd parameters){
	complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*frequency/parameters(5),1-parameters(6)))+parameters(7)/(1.0+pow(ii*frequency/parameters(8),1-parameters(9)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*parameters(10);
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
	if (type==4)  d=parameters(0)+parameters(1)/(1.0+pow(ii*frequency/parameters(2),1-parameters(3)))+1.0/(ii*2.0*pi*frequency*8.85e-12)*parameters(4);
	if (type==5)  d=DoubleColeDavidsonWithConductivity(frequency,parameters);
	if (type==6)  d=TripleColeDavidsonWithConductivity(frequency,parameters);
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

void linearFit(vector <double>x, vector <double>y,double &a,double &b,double &r2);
void linearFit(MatrixXd x, MatrixXd y,double &a,double &b,double &r2);

void CalculateCorrelation(vector<double> dataf,vector<double> dataep,vector<double> dataeb, int type, MatrixXd parameters)
{	
	int size,i;
	double pep,peb,a,b,r;
	complex <double> d;
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
	cout<<"R2 = "<<r<<" 1-r^2 = "<<1-r <<endl;

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
	//cout<<error<<endl<< "----------------------------------------------------- "<<endl;
	cout <<chi2<<endl;
	this->chi2=chi2;
	boost::timer::cpu_times elapsed = timer.elapsed();
	//end=clock();
	//cout <<(double(end - start) / CLOCKS_PER_SEC) <<" s"<<endl;//<<" "<< CLOCKS_PER_SEC<<endl;
	std::cout << "Fitting took " << elapsed.wall / 1e9 << " seconds"<< std::endl;
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