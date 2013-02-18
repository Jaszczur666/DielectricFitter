void FitA( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& es,double& en, double& fp, double& a );
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


double chi2MatLog( vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,MatrixXd parameters)
{
	complex <double> d;
	int i, size;
	double ep,eb;
	double chi2temp=0.0;
	size=dataf.size();
	for (i=0;i<=size-1;i++)
	{
		d=parameters(1)+(parameters(0)-parameters(1))/(1.0+pow(ii*dataf[i]/pow(10,parameters(2)),1-parameters(3)));
		ep= std::real(d);
		eb=-std::imag(d);
		chi2temp=chi2temp+pow(dataep[i]-ep,2.0)+pow(dataeb[i]+eb,2.0);
	}
	return chi2temp/2.0;
}

void CalculateResidueLog(double f,double ep,double eb, MatrixXd parameters,double &rp,double&rb)
{
	double pep,peb;
	complex <double> d;
	d=parameters(1)+(parameters(0)-parameters(1))/(1.0+pow(ii*f/pow(10,parameters(2)),1-parameters(3)));
	pep=std::real(d);
	peb=std::imag(d);
	rp=ep-pep;
	rb=eb-peb;
}




void CalculateHessianLog(vector<double> dataf,vector<double> dataep,vector<double> dataeb, MatrixXd parameters,MatrixXd &Hess, MatrixXd &Grad, double &chi2)
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
		CalculateResidueLog(dataf[i],dataep[i],dataeb[i],parameters,rp,rb);
		delta<<eps,0,0,0;
		CalculateResidueLog(dataf[i],dataep[i],dataeb[i],parameters+delta,rsp,rsb);
		delta<<0,eps,0,0;
		CalculateResidueLog(dataf[i],dataep[i],dataeb[i],parameters+delta,rnp,rnb);
		delta<<0,0,eps,0;
		CalculateResidueLog(dataf[i],dataep[i],dataeb[i],parameters+delta,rfp,rfb);
		delta<<0,0,0,eps;
		CalculateResidueLog(dataf[i],dataep[i],dataeb[i],parameters+delta,rap,rab);
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


void FitLMLog(vector<double> Dataf, vector<double>Dataep, vector<double> Dataeb,MatrixXd &parameters)
{
	int i;
	double lambda;
	double chi2,chi2n,chi2c;
	bool growing;
	MatrixXd Hessian,Hessiandiag, Grad, newParams;
	growing=false;
	lambda=1/1024.0;
	chi2=0;
	clock_t start, end;
	start=clock();
	for(i=1;i<100;i++)
	{
		chi2c=chi2;
		CalculateHessianLog(Dataf,Dataep,Dataeb,parameters, Hessian, Grad,chi2);
		Hessiandiag=Hessian.diagonal().asDiagonal();
		newParams=parameters-((Hessian+lambda*Hessiandiag).inverse()*Grad);
		chi2n=chi2MatLog(Dataf,Dataep,Dataeb,newParams);
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
		if (parameters(3)<0) parameters(3)=0;
		if (parameters(3)>1) parameters(3)=0;
	}
	end=clock();
	cout <<(double(end - start) / CLOCKS_PER_SEC)<<" "<< CLOCKS_PER_SEC<<endl;
	return;
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 					 //chart1->Series["Series1"]->Points->Clear();
					 //chart2->Series["Series1"]->Points->Clear();
					 //chart1->Series["Series2"]->Points->Clear();
					 //chart2->Series["Series2"]->Points->Clear();
					 //chart1->Series["Series3"]->Points->Clear();
					 //chart1->Series["Series4"]->Points->Clear();
			 					 //LoadDielectric(openFileDialog1->FileName,SingleCurve.Dataf,SingleCurve.Dataep,SingleCurve.Dataeb,SingleCurve.temperature);
					 //GuesstimateParameters(SingleCurve.Dataf,SingleCurve.Dataep,SingleCurve.Dataeb,parameters);
					 //es=parameters(0,0);
					 //textBox2->Text=es.ToString();
					 //en=parameters(1,0);
					 //textBox3->Text=en.ToString();
					 //fp=parameters(2,0);
					 //textBox4->Text=fp.ToString();
					 //a=parameters(3,0);
					 //textBox5->Text=a.ToString();
				/*	 for (i=0;i<=size-1;i++)
					 {
						 chart1->Series["Series1"]->Points->AddXY(log10(SingleCurve.Dataf[i]),SingleCurve.Dataep[i]);
						 chart1->Series["Series2"]->Points->AddXY(log10(SingleCurve.Dataf[i]),-SingleCurve.Dataeb[i]);
						 chart2->Series["Series1"]->Points->AddXY(SingleCurve.Dataep[i],-SingleCurve.Dataeb[i]);

					 }*/
					 //button3->PerformClick();
		 }