#include "FileOperate.h"

#include <iomanip>

using namespace std;

void FileOperate::GenToFPKM(string srcFile, string dstFile)
{
	//�����ļ���
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out);
	string str;
	vector<vector<string>>num;  // vector��������������ݣ�ÿһ������Ϊһ��vector����ͳһ��string�����ݶ�ȡ

	//  ���ж�ȡ�ļ�
	while (getline(inFile, str))
	{
		istringstream input(str);
		vector<string> tmp;  // vector�������ÿ������
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
		}
		num.push_back(tmp);
	}
	
	float sum[21] = { 0 }; // sum������������к�  ���ں���FPKM����
	for (int j = 0; j < sizeof(sum) / sizeof(sum[0]); j++)
	{
		for (int i = 1; i < num.size(); i++)
		{
			float aa =atof( num[i][j + 2].c_str());  // ��vector����������תΪfloat��
			sum[j] += aa;
		}
	}

	// �Գ���ͷ��������ݽ��в���
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 2; j < num[i].size(); j++)
		{   
			float a = atof(num[i][j].c_str());
			float lenNum = atof(num[i][1].c_str());
			float db2 = a * 1000 * 1000000 / (lenNum * sum[j - 2]);  // FPKM
			ostringstream oss;
			oss.setf(ios::fixed);  // ���̶��㷽ʽ��ʾ������
			oss.precision(20);  // ����20λС��
			
			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}
		
	}

	std::ofstream outFile;
	//  ���ļ�
	outFile.open(dstFile);
	//  ��vector������д���ı�
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
	vector<vector<string>>num;  // vector��������������ݣ�ÿһ������Ϊһ��vector����ͳһ��string�����ݶ�ȡ

	//  ���ж�ȡ�ļ�
	while (getline(inFile, str))
	{
		istringstream input(str);
		
		vector<string> tmp;  // ��ʱvector�������ÿ������
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
			oss.setf(ios::fixed);  // ���̶��㷽ʽ��ʾ������
			oss.precision(20);  // ����20λС��

			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}

	}



	std::ofstream outFile;
	//  ��д���ļ�������vector������д���ļ�
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
