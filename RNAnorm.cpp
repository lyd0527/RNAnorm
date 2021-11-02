
#include "FileOperate.h"
#include <string.h>
using namespace std;


void ShowUsage()
{
    cout << "Usage   : Trans_arg <--name=your name> [name]" << endl;
    cout << "Name :" << endl;
    cout << " --inputData=your file name                  this name is your orignal data." << endl;
    cout << " --outputFPKM=your file name      this is your file name to be saved after FPKM calculate ,at the same time,it will be used as the orignal data for TPM calculate ." << endl;
    cout << " --outputTPM=your file name                             this is your file name to be saved after TPM calculate." << endl;

    return;
}

int main(int argc, char* argv[])
{
	//¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
	if(argc < 2)
	{
		cout << "No arguments,you must give two arguments at least!" << endl;
		ShowUsage();
		return -1;
	}


        int Index=1;
	string strOrgData;
	string strDataFPKM;
	string strDataTPM;

	while(Index < argc)
	{
		// ¿¿¿¿¿¿¿¿¿
        	if (strncmp(argv[Index], "--inputData=", 12) == 0)
        	{
            		strOrgData = &argv[Index][12];
        	}
        	// ¿¿¿FPKM¿¿¿¿¿¿¿¿¿¿
        	else if (strncmp(argv[Index], "--outputFPKM=", 13) == 0)
        	{
            		strDataFPKM = &argv[Index][13];
        	}
        	else if (strncmp(argv[Index], "--outputTPM=", 12) == 0)
        	{
            		strDataTPM = &argv[Index][12];
            	
        	}
		else
		{
			cout << " Name "<< argv[Index] << "not valid. Run" << argv[0] << "for details." << endl;
			return -1;
		}
		Index++;

	}
	FileOperate fileOpenrate;  //  ´´½¨ÎÄ¼þ²Ù×÷¶ÔÏó

	//  FPKM¼ÆËã
	fileOpenrate.GenToFPKM(strOrgData,strDataFPKM);
	//  TPM¼ÆËã
	fileOpenrate.GenToTPM(strDataFPKM,strDataTPM);

	return 0;
};
