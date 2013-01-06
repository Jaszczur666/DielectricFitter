#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace System;
using namespace std;
void LoadDielectric(String^ Filename, vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb);
void MarshalString ( String ^ s, string& os ) {
	using namespace Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString ( String ^ s, wstring& os ) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars = 
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}


void LoadDielectric(String^ Filename, vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb)
{
	string name,str;
	vector<double> ldataf;
	vector<double> ldataep;
	vector<double> ldataeb;
	double f,ep,eb;
	int i=0,size;
	f=0;
	ep=0;
	eb=0;

	MarshalString(Filename,name);
	ifstream inpfile(name);
	getline(inpfile,str);
	getline(inpfile,str);
	getline(inpfile,str);

	while (!inpfile.eof())
	{
		getline(inpfile,str);
		i=1;
		//cout<<" "<<f <<" "<<ep<<" "<<eb<<" "<< str<<endl;
		istringstream ss( str );
		while (!ss.eof())
		{
			string x;               
			getline( ss, x, '\t' );  
			switch (i)
			{
			case 1:
				f=atof(x.c_str());
			case 2:
				ep=atof(x.c_str());
			case 3:
				eb=atof(x.c_str());
			}
			if (i ==3){
			ldataf.push_back (f);
			ldataep.push_back (ep);
			ldataeb.push_back (eb);
			//cout<<" "<<f <<" "<<ep<<" "<<eb<<" "<< endl;
			//cout<<"Rozmiar w funkcji = "<<ldataf.size()<<endl;
		}
		
			i++;
			//cout <<i<<" "<< x << endl;      
		}	
		
		if (i ==4){
			ldataf.push_back (f);
			ldataep.push_back (ep);
			ldataeb.push_back (eb);
			//cout<<" "<<f <<" "<<ep<<" "<<eb<<" "<< endl;
			//cout<<"Rozmiar w funkcji = "<<ldataf.size()<<endl;
		}

	}
	dataf.swap(ldataf);
	dataep.swap(ldataep);
	dataeb.swap(ldataeb);
	size=ldataf.size();
	for (i=1;i<=size-2;i++)
	{
		cout << i <<";"<<ldataep[i]<<endl;
	}
}

void Normalize(vector<double>& dataep,vector<double>& dataeb,double C0)
{
	int size,i;
	size=dataep.size();
	for (i=1;i<=size-2;i++)
{
	dataep[i]=dataep[i]/C0;
	dataeb[i]=dataeb[i]/C0;

	}
}