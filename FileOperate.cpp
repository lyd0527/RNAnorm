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
			float aa =(float)atof( num[i][j + 2].c_str());  // 将vector读到的数据转为float型
			sum[j] += aa;
		}
	}

	// 对除表头以外的数据进行操作
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 2; j < num[i].size(); j++)
		{   
			float a = (float)atof(num[i][j].c_str());
			float lenNum = (float)atof(num[i][1].c_str());
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
		//tmp.push_back("MAD\tCV");
		num.push_back(tmp);	
	}

	
	float sum[21];
	for (int i = 0; i < sizeof(sum) / sizeof(sum[0]); i++)
	{
		sum[i] = 0;
	}

	for (int j = 0; j < sizeof(sum) / sizeof(sum[0]); j++)
	{
		for (int i = 1; i < num.size(); i++)
		{
			float aa = (float)atof(num[i][j + 1].c_str());
			sum[j] += aa;
		}
	}

	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 1; j < num[i].size(); j++)
		{
			float a =(float) atof(num[i][j].c_str());
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

	inFile.close();
	outFile.close();
}

/*靠靠�
 *1. 靠靠靠靠靠tmpArrayMed靠
 *2. 靠MAD緾V�
 *3. 靠靠縯mpArrayMed靠
 *4. 靠MAD緾V靠靠靠靠靠靠靠�-1
 *5. 縯mpArrayMed靠靠靠靠-1靠靠靠�*/
void FileOperate::DataFilter(string srcFile, string dstFile, string op,float val)
{
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out | ios::app);
	string str;  // 靠靠靠靠
	vector<vector<string>>num;  // vector容器用来存放数据（每一行数据为一个vector），统一按string型数据读取
	vector<vector<float>>array(49);
	vector<vector<float>>arraySort(49);
	vector<vector<string>>store; //靠靠靠靠靠靠�
	for(int i=0;i<arraySort.size();i++)
	{
		arraySort[i].resize(23);
		array[i].resize(23);
	}
	int genNum[49] = { 0 };  // 统计基因数量
	//  按行读取文件
	while (getline(inFile, str))
	{
		for(char &c : str)
		{
			if(c=='\t')
			{
				c==' ';
			}
		}
		str.erase(0,str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" "+1));	
		istringstream input(str);
		vector<string> tmp;  // 临时vector用来存放每行数据
		vector<string>tmp1;
		string a;
		while (input >> a)
		{	
			tmp.push_back(a);
		//	tmp1.push_back(a);
		}
		if (op == "MAD")
		{
			tmp.push_back("MAD");
		//	tmp1.push_back("MAD");

		}
		else if (op == "CV")
		{
			tmp.push_back("CV");
		//	tmp1.push_back("CV");

		}

		num.push_back(tmp);
		store.push_back(tmp);
	}

	for(int i=1;i<num.size();i++)
	{
		
		for(int j=1;j<num[0].size();j++)
		{
			arraySort[i][j]=(float)atof(num[i][j].c_str());
			array[i][j]=(float)atof(num[i][j].c_str());
			genNum[i]++;
		}
	}

	for(int i=1;i<arraySort.size();i++)
	{
		sort(arraySort[i].begin(),arraySort[i].end()-1);
	}


	float median[49] = { 0 };  // 存放源数据中位数及最后所求绝对中位差的中位数
	////CV值
	float cv[49] = { 0 };
	float avg[49] = { 0 };  // 存放源数据平均数
	float sd[49] = { 0 };  // 标准偏差 
	float sum[49] = { 0 };


	/*********************MAD计算*********************/
	// 求源数据的中位数.
	for (int i = 1; i < arraySort.size();i++)
	{
		int n = genNum[i]+1;
		if (n < 2)
		{
			median[i] = arraySort[i][1];
			
		}
		if (n % 2 == 0)
		{
			
			median[i] = (arraySort[i][n/2]+arraySort[i][n/2+1])/2;
			
		}
		else
		{
			median[i] = arraySort[i][n/2];
			
		}

	}
	// 求源数据的绝对中位差
	for (int i = 1; i <array.size();i++ )
	{
		for (int j = 1; j < array[i].size();j++)
		{
			float aa = array[i][j];
			float tmpMedian = (float)abs(aa - median[i]);  
			arraySort[i][j]=tmpMedian;
		}
		// 计算MAD：绝对中位差的中间数
		sort(arraySort[i].begin(),arraySort[i].end()-1);
		int n = genNum[i]+1 ;
		if (n < 2)
		{
			median[i] = arraySort[i][1];

		}
		if (n % 2 == 0)
		{

			median[i] = (arraySort[i][n/2]+arraySort[i][n/2+1])/2;

		}
		else
		{
			median[i] = arraySort[i][n/2];

		}
	}
	/********************计算CV**********************/
	float sd1[49] = { 0 };
	for (int i = 1; i < array.size();i++)
	{
		for (int j = 1; j < array[i].size();j++)
		{
			sum[i] += array[i][j];
		}
		avg[i] = sum[i] / (genNum[i]-1);

		for (int j = 1; j < (genNum[i]); j++)
		{
			sd1[i] +=(float) pow(array[i][j]-avg[i],2);
		}
		sd[i] = sqrt(sd1[i] / (genNum[i] - 2))/avg[i];
		if(avg[i]==0)
		{
			sd[i]=-1;
		}
	}
	
	for (int i = 1; i < array.size();i++)
	{
		for (int j = genNum[i]; j < array[i].size();j++)
		{
			if (op=="MAD")
			{
				array[i][j]=median[i];
			}
			else
			{
				array[i][j]=sd[i];
			}
		}
	}
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 1; j < num[i].size(); j++)
		{
			
			ostringstream oss;
			oss.precision(20);  
			if (op == "MAD")
			{
				if (j == genNum[i])
				{
					oss.precision(2);

					if (array[i][j]<val)
					{
						num[i][0] = "-1";

					}
				}
			}
			else if(op=="CV")
			{
				if (j == genNum[i])
				{
					oss.precision(2);

					if (array[i][j]<val)
					{
						num[i][0] = "-1";

					}
				}
			}
			float db2 = array[i][j];
			oss.setf(ios::fixed); 
			oss << db2;
			string str(oss.str());
			num[i][j] = str;
			//store[i][j]=str;
		}
	}
	std::ofstream outFile;
	//  打开写入文件名，将vector中数据写入文件
	outFile.open(dstFile);
	int tag=0;
	int size=store.size();
	vector<string>tmpStore;
	for(int i=0;i<num.size();i++)
	{
		for(int j=0;j<num[i].size();j++)
		{
			if(num[i][0]=="-1")
			{
				cout<<"num"<<i<<"="<<"-1"<<endl;;
				tag++;
				size--;
				break;
			}
			else
			{
				cout<<"num"<<i<<j<<"="<<num[i][j]<<endl;
				store[i-tag].push_back(num[i][j]);
			}
			

		}
		cout<<store[i-tag].size()<<endl;	
	}
	cout<<endl<<endl;
	/*for(int i=0;i<size;i++)
	{
		for(int j=0;j<store[i].size();j++)
		{
			cout<<store[i][j]<<"\t";
		}
		cout<<endl;
	}*/

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < store[i].size()-23; j++)
		{	
	
			outFile << store[i][j+23] << "\t";

		}

		outFile << endl;
	}

	inFile.close();
	outFile.close();
}
