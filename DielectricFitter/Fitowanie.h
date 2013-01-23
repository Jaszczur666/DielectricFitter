#define ii std::complex <double>(0.0,1.0)
#include <complex>
#include <vector>
#include "Dense"
using Eigen::MatrixXd;
void FitA( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a );
void CalculateResidue(double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb);
double chi2( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double es,double en, double lfp, double a )
{
	complex <double> d;
	int i, size;
	double chi2temp=0.0;
	double ep,eb,fp;
	fp=pow(10,lfp);
	size=dataf.size();
	for (i=0;i<=size-2;i++)
	{
		d=en+(es-en)/(1.0+pow(ii*dataf[i]/fp,1-a));
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp;
}
double chi2Mat( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,MatrixXd parameters)
{
	complex <double> d;
	int i, size;
	double ep,eb,f;
	double chi2temp=0.0;
	size=dataf.size();
	for (i=1;i<=size-2;i++)
	{
		d=parameters(1)+(parameters(0)-parameters(1))/(1.0+pow(ii*dataf[i]/parameters(2),1-parameters(3)));
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp;
}
void Fit( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a )
{
	complex <double> d;
	int i;
	const double eps=1e-5;
	double gamma=1e-1;
	double chi0,chies,chien,chif,chia;
	double dfdes,dfden,dfdfp,dfda,lfp;
	double nes,nen,nlfp,na,chin;
	lfp=log10(fp);
	//cout << es<<" "<<en<<" "<<fp<<" "<<lfp<<" "<<a<<endl;
	for (i=1;i<1000;i++){
		chi0=chi2( dataf,dataep,dataeb,es,en,lfp,a);
		chies=chi2( dataf,dataep,dataeb,es+eps,en,lfp,a);
		chien=chi2( dataf,dataep,dataeb,es,en+eps,lfp,a);
		chif=chi2( dataf,dataep,dataeb,es,en,lfp+eps,a);
		chia=chi2( dataf,dataep,dataeb,es,en,lfp,a+eps);
		dfdes=(chies-chi0)/eps;
		dfden=(chien-chi0)/eps;
		dfdfp=(chif-chi0)/eps;
		dfda=(chia-chi0)/eps;
		nes=es-dfdes*gamma;
		nen=en-dfden*gamma;
		nlfp=lfp-2e-3*dfdfp*gamma;
		na=a;//-3e-3*dfda*gamma;
		if (chi0<1e-3) break;
		chin=chi2( dataf,dataep,dataeb,nes,nen,nlfp,na);
		if (chin <chi0) {
			es=nes;
			en=nen;
			lfp=nlfp;
			//a=na;
			cout <<i<<" "<< es<<" "<<en<<" "<<lfp<<" "<<a<<endl;
		}
		else
		{
			gamma=gamma/pow(10,0.5);
			if (gamma<1e-12) break;
			//cout<<i<<" " << gamma <<endl;
		}
	}
	fp=pow(10,lfp);
	return;
}


void TestFit( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a ){
	double chi0,fpf;
	int i;
	for (i=1;i<100;i++)
	{
		fpf=pow(10,(6.*i/100));
		chi0=chi2( dataf,dataep,dataeb,es,en,fpf,a);
		cout<<i<<" "<< fpf<<" "<<chi0<<endl;
	}
}

void TestFitF( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a ){
	double chi0;
	int i,j;
	for (i=1;i<100;i++)
	{
		for (j=1;j<100;j++){
			es=79+i/50.0;
			en=1+j/100.0;
			chi0=chi2( dataf,dataep,dataeb,es,en,log10(fp),a);
			cout<<" "<<en<<" "<<es<<" "<< " "<<chi0<<endl;
		}
	}
}

void FitA( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a ){
	double chi0,chi1;
	int i;
	for (i=1;i<100;i++)
	{
		chi0=chi2( dataf,dataep,dataeb,es,en,log10(fp),i/100.0);
		chi1=chi2( dataf,dataep,dataeb,es,en,log10(fp),(1+i)/100.0);
		if (chi0<chi1)  
		{
			a=i/100.;
			break;
		}
	}
}

void CalculateHessian(vector<double> dataf,vector<double> dataep,vector<double> dataeb, MatrixXd parameters,MatrixXd &Hess, MatrixXd &Grad, double &chi2)
{
	int i,size;
	
	MatrixXd delta(4,1);
	MatrixXd Hessian;
	double rp,rb,rsp,rsb,rnp,rnb,rfb,rfp,rap,rab;
	double eps;
	size=dataf.size();
	MatrixXd Jaco(2*(size-2),4);
	MatrixXd Res(2*(size-2),1);
	complex <double> d;
	eps=1e-6;
	chi2=0;
	for (i=1;i<=size-2;i++)
	{
	CalculateResidue(dataf[i-1],dataep[i-1],dataeb[i-1],parameters,rp,rb);
	delta<<1e-9,0,0,0;
	CalculateResidue(dataf[i-1],dataep[i-1],dataeb[i-1],parameters+delta,rsp,rsb);
	delta<<0,1e-9,0,0;
	CalculateResidue(dataf[i-1],dataep[i-1],dataeb[i-1],parameters+delta,rnp,rnb);
	delta<<0,0,1e-9,0;
	CalculateResidue(dataf[i-1],dataep[i-1],dataeb[i-1],parameters+delta,rfp,rfb);
	delta<<0,0,0,1e-9;
	CalculateResidue(dataf[i-1],dataep[i-1],dataeb[i-1],parameters+delta,rap,rab);
	Jaco((i-1)*2,0)=(rsp-rp)/1e-9;
	Jaco((i-1)*2+1,0)=(rsb-rb)/1e-9;
	Jaco((i-1)*2,1)=(rnp-rp)/1e-9;
	Jaco((i-1)*2+1,1)=(rnb-rb)/1e-9;
	Jaco((i-1)*2,2)=(rfp-rp)/1e-9;
	Jaco((i-1)*2+1,2)=(rfb-rb)/1e-9;
	Jaco((i-1)*2,3)=(rap-rp)/1e-9;
	Jaco((i-1)*2+1,3)=(rab-rb)/1e-9;
	Res((i-1)*2,0)=rp;
	Res((i-1)*2+1,0)=rb;
	chi2=chi2+0.5*(rp*rp+rb*rb);
	//cout <<i<<" "<< "resid="<<rp<< "' "<<rb<<"'' "<<std::endl;		
	}
//	cout <<Jaco;
	Hess=Jaco.transpose()*Jaco;
	Grad=Jaco.transpose()*Res;
	//cout << Hessian<<std::endl;
	//cout <<"------------------------------------"<<std::endl;
	//cout<<	Hessian.inverse();
//cout<<parameters;
}

void CalculateResidue(double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb)
{
		double pep,peb;
		complex <double> d;
		d=parameters(1)+(parameters(0)-parameters(1))/(1.0+pow(ii*f/parameters(2),1-parameters(3)));
		pep=std::real(d);
		peb=std::imag(d);
		rp=ep-pep;
		rb=eb-peb;
}

void FitLM(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters)
{
	int i;
	double lambda;
	double chi2,chi2n;
	MatrixXd Hessian,Hessiandiag, Grad, newParams;
	lambda=1;
	for(i=1;i<100;i++)
	{
		CalculateHessian(Dataf,Dataep,Dataeb,parameters, Hessian, Grad,chi2);
		Hessiandiag=Hessian.diagonal().asDiagonal();
//		cout<<Hessiandiag<<std::endl;
//		cout <<"--------------------------------------------------------"<<std::endl;

		newParams=parameters-((Hessian+lambda*Hessiandiag).inverse()*Grad);
		chi2n=chi2Mat(Dataf,Dataep,Dataeb,newParams);
		if (chi2n<chi2){
			parameters=newParams;
			lambda=lambda*8;
		}
		else
		{
		lambda=lambda/8.0;
		}
		cout <<chi2<<" " <<chi2n <<" "<<parameters.transpose() <<std::endl;
	}
	return;
}