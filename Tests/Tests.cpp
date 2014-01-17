// Tests.cpp : main project file.

#include "stdafx.h"

using namespace System;
#include "../DielectricFitter/Parser.h"
#include "../DielectricFitter/Fitowanie.h"

void TestInput(){
	curvesetrev cs1,cs2;
	wstring ws;
	String^ S;
	S="d:\\test.dat";
	ws=L"d:\\test2.dat";
	cs1.LoadTempProfFromFile(ws);
	cs1.LoadTempProfFromFile(S);
	cs2.LoadTempProfFromFile(ws);
	cs2.LoadTempProfFromFile(S);
	Console::WriteLine(cs1.f.size().ToString()+" files loaded using wstring");
	Console::WriteLine(cs1.f[0].ToString()+" freq "+cs1.ep[0].size().ToString());
	Console::WriteLine(cs2.f.size().ToString()+" files loaded using System::String");
	Console::WriteLine(cs2.f[0].ToString()+" freq "+cs2.ep[0].size().ToString());
	Console::WriteLine(cs1.IsSame(cs2)+" "+cs2.IsSame(cs1));
	Console::WriteLine(cs1==cs2);
}

int main(array<System::String ^> ^args)
{
	TestInput();
	return 0;
}
