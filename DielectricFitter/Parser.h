#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace System;
using namespace std;

//void LoadDielectric(String^ Filename, vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb);
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


void LoadDielectric(String^ Filename, vector<double>& dataf,vector<double>& dataep,vector<double>& dataeb,double& temperature)
{
	wstring name;
	string str;
	vector<double> ldataf;
	vector<double> ldataep;
	vector<double> ldataeb;
	double f,ep,eb;
	int i=0,temppos;
	f=0;
	ep=0;
	eb=0;
	MarshalString(Filename,name);
	ifstream inpfile(name);
	getline(inpfile,str);
	//cout <<str<<endl;
	getline(inpfile,str);
	cout <<str<<endl;
	temppos=str.find("Temp");
	cout<<temppos <<endl;
	if (temppos !=string::npos) str=str.substr(temppos);
	temppos=str.find("=");
	if (temppos !=string::npos) str=str.substr(temppos);
	temppos=str.find(" ");
	str=str.substr(1,temppos);
	cout<<str <<endl;
	temperature=atof(str.c_str());
	getline(inpfile,str);
	//	cout <<str<<endl;
	while (!inpfile.eof())
	{
		getline(inpfile,str);
		i=1;
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
			}

			i++;
		}	
		//	inpfile.close();

		/*		if (i ==4){
		ldataf.push_back (f);
		ldataep.push_back (ep);
		ldataeb.push_back (eb);
		}
		*/
	}
	dataf.swap(ldataf);
	dataep.swap(ldataep);
	dataeb.swap(ldataeb);
	//	size=dataf.size();
	/*	for (i=0;i<=size-1;i++)
	{
	cout << i <<";"<<dataf[i]<<endl;
	}*/
}

void Normalize(vector<double>& dataep,vector<double>& dataeb,double C0)
{
	int size,i;
	size=dataep.size();
	for (i=0;i<=size-1;i++)
	{
		dataep[i]=dataep[i]/C0;
		dataeb[i]=-dataeb[i]/C0;

	}
}

void NormalizeCapacity(vector<double>& dataep,vector<double>& dataeb,double C0)
{
	int size,i;
	size=dataep.size();
	for (i=0;i<=size-1;i++)
	{
		dataep[i]=dataep[i]/C0;
		dataeb[i]=dataeb[i]/C0;

	}
}
#endif