#define ii std::complex <double>(0.0,1.0)
#include <complex>
#include <vector>
double chi2( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double es,double en, double fp, double a )
{
complex <double> d;
int i, size;
double chi2temp=0.0;
double ep,eb;
size=dataf.size();
//cout <<es <<" "<<en <<" "<<fp <<" "<<a <<endl;
//cout << size<<endl;
	for (i=1;i<=size-2;i++)
{
	d=en+(es-en)/(1.0+pow(ii*dataf[i]/fp,1-a));
	ep= std::real(d);
	eb=-std::imag(d);
//	cout<<i<<" " << ep<<" "<<dataep[i] <<";" <<eb<<" "<<dataeb[i]<<" "<<chi2temp<<endl;
	chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp;
}

void Fit( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a )
{
complex <double> d;
int i;
const double eps=1e-5;
double chi0,chies,chien,chif,chia;
double dfdes,dfden,dfdfp,dfda,krok,chigrad;
cout << es<<" "<<en<<" "<<fp<<" "<<a<<endl;
for (i=1;i<100;i++){
chi0=chi2( dataf,dataep,dataeb,es,en,fp,a);
chies=chi2( dataf,dataep,dataeb,es+eps,en,fp,a);
dfdes=(chies-chi0)/eps;
chi0=chi2( dataf,dataep,dataeb,es,en,fp,a);
chien=chi2( dataf,dataep,dataeb,es,en+eps,fp,a);
dfden=(chien-chi0)/eps;
chi0=chi2( dataf,dataep,dataeb,es,en,fp,a);
chif=chi2( dataf,dataep,dataeb,es,en,fp+eps,a);
dfdfp=(chif-chi0)/eps;
chi0=chi2( dataf,dataep,dataeb,es,en,fp,a);
chia=chi2( dataf,dataep,dataeb,es,en,fp,a+eps);
dfda=(chia-chi0)/eps;
chigrad=chi2( dataf,dataep,dataeb,es-eps*dfdes,en-eps*dfden,fp-eps*dfdfp,a);
krok=-chi0/((chigrad-chi0)/eps);
chigrad=chi2(dataf,dataep,dataeb,es-krok*dfdes,en-krok*dfden,fp-krok*dfdfp,a);
cout << es<<" "<<en<<" "<<fp<<" "<<a<< " "<<chi0 <<endl;
if (chigrad<=chi0){
es=es-krok*dfdes;
en=en-krok*dfden;
fp=fp-krok*dfdfp;
//cout << "debug df po dfp " <<krok*dfdfp<<endl; 
//a=a-krok*dfda;
}
}
//cout<<chi0<<" "<<(chigrad-chi0)/eps<<" "<<krok	 <<endl;
//cout<< chi2(dataf,dataep,dataeb,es-krok*dfdes,en-krok*dfden,fp-krok*dfdfp,a-krok*dfda);

//cout << dfdes<<" "<<dfden<<" "<<dfdfp<<" "<<dfda<<endl;
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
