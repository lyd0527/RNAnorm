#include "FileOperate.h"

#include <iomanip>

using namespace std;

void FileOperate::GenToFPKM(string srcFile, string dstFile)
{
	//创建文件流
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out);
	string str;
	vector<vector<string>>num;  // vector容器用来存放数据（每一行数据为一个vector），统一按string型数据读取

	//  按行读取文件
	while (getline(inFile, str))
	{
		istringstream input(str);
		vector<string> tmp;  // vector用来存放每行数据
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
		}
		num.push_back(tmp);
	}
	
	float sum[21] = { 0 }; // sum数组用来存放列和  便于后续FPKM计算
	for (int j = 0; j < sizeof(sum) / sizeof(sum[0]); j++)
	{
		for (int i = 1; i < num.size(); i++)
		{
			float aa =atof( num[i][j + 2].c_str());  // 将vector读到的数据转为float型
			sum[j] += aa;
		}
	}

	// 对除表头以外的数据进行操作
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 2; j < num[i].size(); j++)
		{   
			float a = atof(num[i][j].c_str());
			float lenNum = atof(num[i][1].c_str());
			float db2 = a * 1000 * 1000000 / (lenNum * sum[j - 2]);  // FPKM
			ostringstream oss;
			oss.setf(ios::fixed);  // 按固定点方式显示浮点数
			oss.precision(20);  // 保留20位小数
			
			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}
		
	}

	std::ofstream outFile;
	//  打开文件
	outFile.open(dstFile);
	//  将vector中数据写入文本
	for (int i = 0; i < num.size(); i++)
	{
		for (int j = 0; j < num[i].size(); j++)
		{
			if (j != 1)
			{
				outFile << num[i][j] << "\t";
			}
		}
		outFile << endl;
	}

	inFile.close();
	outFile.close();
}
void FileOperate::GenToTPM(string srcFile, string dstFile)
{
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out);
	string str;
	vector<vector<string>>num;  // vector容器用来存放数据（每一行数据为一个vector），统一按string型数据读取

	//  按行读取文件
	while (getline(inFile, str))
	{
		istringstream input(str);
		
		vector<string> tmp;  // 临时vector用来存放每行数据
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
		}
		num.push_back(tmp);
	}
	float sum[21]={0};
	for (int j = 0; j < sizeof(sum) / sizeof(sum[0]); j++)
	{
		for (int i = 1; i < num.size(); i++)
		{
			float aa = atof(num[i][j + 1].c_str());
			sum[j] += aa;
		}
	}
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 1; j < num[i].size(); j++)
		{
			float a = atof(num[i][j].c_str());
			float db2 = a * 1000000 / (sum[j - 1]);  // TPM

			ostringstream oss;
			oss.setf(ios::fixed);  // 按固定点方式显示浮点数
			oss.precision(20);  // 保留20位小数

			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}

	}



	std::ofstream outFile;
	//  打开写入文件名，将vector中数据写入文件
	outFile.open(dstFile);
	for (int i = 0; i < num.size(); i++)
	{
		for (int j = 0; j < num[i].size(); j++)
		{

			outFile << num[i][j] << "\t";

		}
		outFile << endl;
	}
	//inFile.close();
	//outFile.close();
}
