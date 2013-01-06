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
	//cout << ep <<";" <<eb<<" "<<chi2temp<<endl;
	chi2temp=chi2temp+pow(dataep[i]-ep,2)+pow(dataeb[i]-eb,2);
	}
	return chi2temp;
}

void Fit( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a )
{
complex <double> d;
int i;
const double eps=1e-5;
double chi0,chies,chien,chif,chia;
double dfdes,dfden,dfdfp,dfda;

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
cout << es<<" "<<en<<" "<<fp<<" "<<a<<endl;
cout << dfdes<<" "<<dfden<<" "<<dfdfp<<" "<<dfda<<endl;
return;
}