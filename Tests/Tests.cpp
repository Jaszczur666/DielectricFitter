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
    Console::WriteLine(L"Hello World");
    return 0;
}
