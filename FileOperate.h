#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string>
using namespace std;
class FileOperate
{
public:
	//FTPM
	void GenToFPKM(string srcFile, string dstFile);
	//TPM
	void GenToTPM(string srcFile, string dstFile);
	
};
