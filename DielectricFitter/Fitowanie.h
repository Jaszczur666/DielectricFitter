#define ii std::complex <double>(0.0,1.0)
#include <complex>
#include <vector>
double chi2( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double es,double en, double lfp, double a )
{
	complex <double> d;
	int i, size;
	double chi2temp=0.0;
	double ep,eb,fp;
	fp=pow(10,lfp);
	size=dataf.size();
	for (i=1;i<=size-2;i++)
	{
		d=en+(es-en)/(1.0+pow(ii*dataf[i]/fp,1-a));
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp;
}

void Fit( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a )
{
	complex <double> d;
	int i,j;
	const double eps=3e-6;
	double chi0,chies,chien,chif,chia;
	double dfdes,dfden,dfdfp,dfda,krok,chigrad,lfp;
	lfp=log10(fp);
	cout << es<<" "<<en<<" "<<fp<<" "<<lfp<<" "<<a<<endl;
	for (i=1;i<30;i++){
		chi0=chi2( dataf,dataep,dataeb,es,en,lfp,a);
		chies=chi2( dataf,dataep,dataeb,es+eps,en,lfp,a);
		chien=chi2( dataf,dataep,dataeb,es,en+eps,lfp,a);
		chif=chi2( dataf,dataep,dataeb,es,en,lfp+eps,a);
		chia=chi2( dataf,dataep,dataeb,es,en,lfp,a+eps);
		dfdes=(chies-chi0)/eps;
		dfden=(chien-chi0)/eps;
		dfdfp=(chif-chi0)/eps;
		dfda=(chia-chi0)/eps;
		cout << es<<" "<<en<<" "<<fp<<" "<<lfp<<" "<<a<<" "<<chi0<<endl;
		for (j=1;j<3;j++){
			chi0=chi2( dataf,dataep,dataeb,es,en,lfp,a);
			chigrad=chi2( dataf,dataep,dataeb,es-eps*dfdes,en-eps*dfden,lfp,a);
			krok=-chi0/((chigrad-chi0)/eps);
			chigrad=chi2(dataf,dataep,dataeb,es-krok*dfdes,en-krok*dfden,lfp,a);
			//cout << "Debug "<<j<<" " << krok<<endl;
			if (chigrad<=chi0){
				es=es-krok*dfdes;
				en=en-krok*dfden;
				//lfp=lfp-krok*dfdfp;
				fp=pow(10,lfp);}
		}
	}
	
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
	double chi0,fpf,as;
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