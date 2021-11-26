
#include "FileOperate.h"
#include <string.h>
#include <unistd.h>
#include <getopt.h>
using namespace std;


void ShowUsage()
{
        cout << "\nUsage: RNAnorm <OPTION>\n" << endl;
        cout << "Option:\n" << endl;
        cout << "\t-i \traw count maxtrix from featureCount or HTSeq" << endl;
        cout << "\t-o \toutput prefix"<< endl;
        cout << "\t-f \tfiltering or not [off]" << endl;
	cout << "\t-v \tminimum threshold value of MAD or CV [0.01]" << endl;
	cout << "\t-m \tmethod: CV or MAD [CV]\n" << endl;
    return;
}

int main(int argc, char* argv[])
{
	if(argc < 4)
	{
		ShowUsage();
		cout<<"\tCase1: RNAnorm -i count.input -o output_prefix"<<endl;
		cout<<"\tCase2: RNAnorm -i count.input -o output_prefix -f -v 0.01 -m CV"<<endl;
		cout<<"\tCase3: RNAnorm -i count.input -o output_prefix -f -v 0.01 -m MAD\n"<<endl;
		return -1;
	}

	static struct option long_options[]={
		{"input",required_argument,NULL,'i'},
		{"output",required_argument,NULL,'o'},
		{"filter",required_argument,NULL,'f'},
		{"value",required_argument,NULL,'v'},
		{"method",required_argument,NULL,'m'},
		{0,0,0,0}
	};
	static char* const short_options=(char *)"i:o:fv:m:";
	int option_index=0;

	string strInput;  // 存储输入文件名
	//char * tmp=new char[6];
	const char * tmpC;  //临时存储筛选临界值value
	//const char * tmpM;
	float fltTmp=0;  // 将筛选临界值value转为float型，以便于函数调用 
	string strOutputFPKM,strOutputTPM,strOutputOpFPKM,strOutputOpTPM;  // 输出文件名
	int in=0;
	string o,m,str; // 临时存储输入文件前缀，筛选方式以及筛选临界阈值
	int ref=0;  // 筛选标志，当ref=1时开启筛选选项，否则为默认
	while((in=getopt_long(argc,argv,short_options,long_options,&option_index)) != -1)
	{
		
		ostringstream oss;
		switch(in){
			case 'i':
				strInput=optarg;
     				break;
			case 'o':
				o = optarg;
				strOutputFPKM=o+".FPKM";
				strOutputTPM=o+".TPM";
	     			break;
			case 'f':
				ref=1;

				strOutputOpFPKM=o+".CV0.01.FPKM";
                                strOutputOpTPM=o+".CV0.01.TPM";
				break;
		       	case 'v':
				tmpC=optarg;
				oss<<tmpC;
				str=oss.str();
				fltTmp=atof(str.c_str());
				break;
			case 'm':
				m = optarg;
				if(m=="CV")
				{
					strOutputOpFPKM=(((o+".")+m)+str)+".FPKM";
					strOutputOpTPM=o+"."+m+str+".TPM";
					break;
				}
				else if(m=="MAD")
				{
					strOutputOpFPKM=(((o+".")+m)+str)+".FPKM";
                                        strOutputOpTPM=o+"."+m+str+".TPM";

					break;
				}
				else
				{
					cout<<"Error!!"<<endl;
				}
				break;
			case '?':
				cout<<"unknown command"<<endl;
				break;
			}
	}
	FileOperate fileOperate;
	fileOperate.GenToFPKM(strInput,strOutputFPKM);  // 调用标准化函数
	fileOperate.GenToTPM(strOutputFPKM,strOutputTPM);
	if(ref==1)  // 以有参形式调用筛选函数
	{
                fileOperate.DataFilter(strOutputFPKM,strOutputOpFPKM,m,fltTmp);
                fileOperate.DataFilter(strOutputTPM,strOutputOpTPM,m,fltTmp);

	}
	else  // 以默认参数调用筛选函数
	{
                fileOperate.DataFilter(strOutputFPKM,o+".CV0.01.FPKM");
                fileOperate.DataFilter(strOutputTPM,o+".CV0.01.TPM");
	}
	cout<<"Finshed!!"<<endl;
	return 0;
};
