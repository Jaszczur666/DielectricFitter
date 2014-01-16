// Tests.cpp : main project file.

#include "stdafx.h"

using namespace System;
#include "../DielectricFitter/Parser.h"
#include "../DielectricFitter/Fitowanie.h"

int main(array<System::String ^> ^args)
{
	curvesetrev cs;
	wstring ws;
	ws=L"d:\\test.dat";
	cs.LoadTempProfFromFile(ws);
	Console::WriteLine(cs.f.size().ToString()+" files loaded");
	Console::WriteLine(cs.f[0].ToString()+" freq");
    return 0;
}
