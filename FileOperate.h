#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;
class FileOperate
{
public:
	//FTPM
	void GenToFPKM(string srcFile, string dstFile);
	//TPM
	void GenToTPM(string srcFile, string dstFile);
	//数据筛选（CV or MAD）默认CV  阈值=0.01  
	void DataFilter(string srcFile, string dstFile,string op="CV",float val=0.01);

	
};
