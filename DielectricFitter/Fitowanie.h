#define ii std::complex <double>(0.0,1.0)
#include <complex>
#include <vector>
#include "Dense"
#include <ctime>
using Eigen::MatrixXd;

void CalculateResidue(double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb);
void CalculateResidue2(double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb);

double chi2Mat( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,MatrixXd parameters)
{
	complex <double> d;
	int i, size;
	double ep,eb;
	double chi2temp=0.0;
	size=dataf.size();
	for (i=0;i<=size-1;i++)
	{
		d=parameters(1)+(parameters(0)-parameters(1))/(1.0+pow(ii*dataf[i]/parameters(2),1-parameters(3)));
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp/2.0;
}

double chi2Mat2( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,MatrixXd parameters)
{
	complex <double> d;
	int i, size;
	double ep,eb;
	double chi2temp=0.0;
	size=dataf.size();
	for (i=0;i<=size-1;i++)
	{
		d=parameters(0)+parameters(1)/(1.0+pow(ii*dataf[i]/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*dataf[i]/parameters(5),1-parameters(6)));
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp/2.0;
}
void CalculateHessian(vector<double> dataf,vector<double> dataep,vector<double> dataeb, MatrixXd parameters,MatrixXd &Hess, MatrixXd &Grad, double &chi2)
{
	int i,size;

	MatrixXd delta(4,1);
	MatrixXd Hessian;
	double rp,rb,rsp,rsb,rnp,rnb,rfb,rfp,rap,rab;
	double eps;
	size=dataf.size();
	MatrixXd Jaco(2*size,4);
	MatrixXd Res(2*size,1);
	complex <double> d;
	eps=1e-7;
	chi2=0;
	for (i=0;i<=size-1;i++)
	{
		CalculateResidue(dataf[i],dataep[i],dataeb[i],parameters,rp,rb);
		delta<<eps,0,0,0;
		CalculateResidue(dataf[i],dataep[i],dataeb[i],parameters+delta,rsp,rsb);
		delta<<0,eps,0,0;
		CalculateResidue(dataf[i],dataep[i],dataeb[i],parameters+delta,rnp,rnb);
		delta<<0,0,eps,0;
		CalculateResidue(dataf[i],dataep[i],dataeb[i],parameters+delta,rfp,rfb);
		delta<<0,0,0,eps;
		CalculateResidue(dataf[i],dataep[i],dataeb[i],parameters+delta,rap,rab);
		Jaco(i*2,0)=(rsp-rp)/eps;
		Jaco(i*2+1,0)=(rsb-rb)/eps;
		Jaco(i*2,1)=(rnp-rp)/eps;
		Jaco(i*2+1,1)=(rnb-rb)/eps;
		Jaco(i*2,2)=(rfp-rp)/eps;
		Jaco(i*2+1,2)=(rfb-rb)/eps;
		Jaco(i*2,3)=(rap-rp)/eps;
		Jaco(i*2+1,3)=(rab-rb)/eps;
		Res(i*2,0)=rp;
		Res(i*2+1,0)=rb;
		chi2=chi2+0.5*(rp*rp+rb*rb);
//		cout << i<<" "<<rp<<" "<<" "<<rb<<endl;
	}
	Hess=Jaco.transpose()*Jaco;
/*	cout <<"-----------------------------------------------------------------"<<endl;
	cout << Jaco<<endl;
	cout <<"-----------------------------------------------------------------"<<endl; */
	Grad=Jaco.transpose()*Res;
}

void CalculateHessian2(vector<double> dataf,vector<double> dataep,vector<double> dataeb, MatrixXd parameters,MatrixXd &Hess, MatrixXd &Grad, double &chi2)
{
	int i,size;

	MatrixXd delta(7,1);
	MatrixXd Hessian;
	double rp,rb,rsp,rsb,rnp,rnb,rfb,rfp,rap,rab;
	double rdp2,rdb2,rfp2,rfb2,rab2,rap2;
	double eps;
	size=dataf.size();
	MatrixXd Jaco(2*size,7);
	MatrixXd Res(2*size,1);
	complex <double> d;
	eps=1e-7;
	chi2=0;
	for (i=0;i<=size-1;i++)
	{
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters,rp,rb);
		delta<<eps,0,0,0,0,0,0;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rsp,rsb);
		delta<<0,eps,0,0,0,0,0;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rnp,rnb);
		delta<<0,0,eps,0,0,0,0;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rfp,rfb);
		delta<<0,0,0,eps,0,0,0;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rap,rab);
		delta<<0,0,0,0,eps,0,0;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rdp2,rdb2);
		delta<<0,0,0,0,0,eps,0;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rfp2,rfb2);
		delta<<0,0,0,0,0,0,eps;
		CalculateResidue2(dataf[i],dataep[i],dataeb[i],parameters+delta,rap2,rab2);
		
		Jaco(i*2,0)=(rsp-rp)/eps;
		Jaco(i*2+1,0)=(rsb-rb)/eps;
		Jaco(i*2,1)=(rnp-rp)/eps;
		Jaco(i*2+1,1)=(rnb-rb)/eps;
		Jaco(i*2,2)=(rfp-rp)/eps;
		Jaco(i*2+1,2)=(rfb-rb)/eps;
		Jaco(i*2,3)=(rap-rp)/eps;
		Jaco(i*2+1,3)=(rab-rb)/eps;
		Jaco(i*2,4)=(rdp2-rp)/eps;
		Jaco(i*2+1,4)=(rdb2-rb)/eps;
		Jaco(i*2,5)=(rfp2-rp)/eps;
		Jaco(i*2+1,5)=(rfb2-rb)/eps;
		Jaco(i*2,6)=(rap2-rp)/eps;
		Jaco(i*2+1,6)=(rab2-rb)/eps;
		Res(i*2,0)=rp;
		Res(i*2+1,0)=rb;
		chi2=chi2+0.5*(rp*rp+rb*rb);
//		cout << i<<" "<<rp<<" "<<" "<<rb<<endl;
	}
	Hess=Jaco.transpose()*Jaco;
/*	cout <<"-----------------------------------------------------------------"<<endl;
	cout << Jaco<<endl;
	cout <<"-----------------------------------------------------------------"<<endl; */
	Grad=Jaco.transpose()*Res;
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

void CalculateResidue2(double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb)
{
	double pep,peb;
	complex <double> d;
	d=parameters(0)+parameters(1)/(1.0+pow(ii*f/parameters(2),1-parameters(3)))+parameters(4)/(1.0+pow(ii*f/parameters(5),1-parameters(6)));
	pep=std::real(d);
	peb=std::imag(d);
	rp=ep-pep;
	rb=eb-peb;
}

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

void FitLM(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters)
{
	int i,size,size2;
	double lambda;
	double chi2,chi2n,chi2c;
	bool growing;
	MatrixXd Hessian,Hessiandiag, Grad, newParams,error;
	growing=false;
	lambda=1/1024.0;
	chi2=0;
	clock_t start, end;
	start=clock();
	for(i=1;i<100;i++)
	{
		chi2c=chi2;
		CalculateHessian(Dataf,Dataep,Dataeb,parameters, Hessian, Grad,chi2);
		Hessiandiag=Hessian.diagonal().asDiagonal();
		newParams=parameters-((Hessian+lambda*Hessiandiag).inverse()*Grad);
		chi2n=chi2Mat(Dataf,Dataep,Dataeb,newParams);
		if (chi2n<chi2){
			parameters=newParams;
			lambda=lambda*8;
			growing=false;
		}
		else
		{
			lambda=lambda/8.0;
			growing=true;
		}
		if (parameters(2)<0) parameters(2)=-parameters(2);
		if (parameters(3)<0) parameters(3)=0;
		if (parameters(3)>1) parameters(3)=0;
		//if ((abs((chi2c-chi2)/chi2) <1e-6)&&(!growing)) break;
		//cout << i <<" "<<(chi2c-chi2)/chi2 <<" "<<chi2<<" "<<parameters.transpose() <<endl;	//<<"|"<<newParams.transpose() <<std::endl;

	}
	size=parameters.rows();
	size2=Dataf.size();
	cout << "rozmiary ="<<size<<" "<<size2<<endl;
	error=(Hessiandiag.inverse().diagonal()*chi2/(size2-size));
	for (i=0;i<size;i++) error(i)=sqrt(error(i));
	/*cout<<Hessian.inverse()<<endl;
		cout <<"-----------------------------------------------------------------------"<<endl;
	cout<<error<<endl<< "----------------------------------------------------- "<<endl;
	cout <<chi2<<endl;
	*/end=clock();
	cout <<(double(end - start) / CLOCKS_PER_SEC)<<" "<< CLOCKS_PER_SEC<<endl;
	return;
}

void FitLM2(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters)
{
	int i,size,size2;
	double lambda;
	double chi2,chi2n,chi2c;
	bool growing;
	MatrixXd Hessian,Hessiandiag, Grad, newParams,error;
	growing=false;
	lambda=1/1024.0;
	chi2=0;
	clock_t start, end;
	start=clock();
	for(i=1;i<100;i++)
	{
		chi2c=chi2;
		CalculateHessian2(Dataf,Dataep,Dataeb,parameters, Hessian, Grad,chi2);
		Hessiandiag=Hessian.diagonal().asDiagonal();
		newParams=parameters-((Hessian+lambda*Hessiandiag).inverse()*Grad);
		chi2n=chi2Mat2(Dataf,Dataep,Dataeb,newParams);
		if (chi2n<chi2){
			parameters=newParams;
			lambda=lambda*8;
			growing=false;
		}
		else
		{
			lambda=lambda/8.0;
			growing=true;
		}
		if (parameters(2)<0) parameters(2)=-parameters(2);
		if (parameters(3)<0) parameters(3)=0;
		if (parameters(3)>1) parameters(3)=0;
		//if ((abs((chi2c-chi2)/chi2) <1e-6)&&(!growing)) break;
		//cout << i <<" "<<(chi2c-chi2)/chi2 <<" "<<chi2<<" "<<parameters.transpose() <<endl;	//<<"|"<<newParams.transpose() <<std::endl;

	}
	size=parameters.rows();
	size2=Dataf.size();
	cout << "rozmiary ="<<size<<" "<<size2<<endl;
	error=(Hessiandiag.inverse().diagonal()*chi2/(size2-size));
	for (i=0;i<size;i++) error(i)=sqrt(error(i));
	cout<<error<<endl<< "----------------------------------------------------- "<<endl;
	cout <<chi2<<endl;
	end=clock();
	cout <<(double(end - start) / CLOCKS_PER_SEC)<<" "<< CLOCKS_PER_SEC<<endl;
	return;
}

double Correction(double temperature)
{
if (temperature < -50) return 0;
if ((temperature > -50)&&(temperature<-45)  ) return 0.51*(temperature+50)/5;
if (temperature > -45) return 0.51;
}