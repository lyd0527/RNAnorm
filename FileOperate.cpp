#include "FileOperate.h"

#include <iomanip>

using namespace std;

void FileOperate::GenToFPKM(string srcFile, string dstFile)
{
	//´´½¨ÎÄ¼şÁ÷
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out);
	string str;
	vector<vector<string>>num;  // vectorÈİÆ÷ÓÃÀ´´æ·ÅÊı¾İ£¨Ã¿Ò»ĞĞÊı¾İÎªÒ»¸övector£©£¬Í³Ò»°´stringĞÍÊı¾İ¶ÁÈ¡

	//  °´ĞĞ¶ÁÈ¡ÎÄ¼ş
	while (getline(inFile, str))
	{
		istringstream input(str);
		vector<string> tmp;  // vectorÓÃÀ´´æ·ÅÃ¿ĞĞÊı¾İ
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
		}
		num.push_back(tmp);
	}
	
	float sum[21] = { 0 }; // sumÊı×éÓÃÀ´´æ·ÅÁĞºÍ  ±ãÓÚºóĞøFPKM¼ÆËã
	for (int j = 0; j < sizeof(sum) / sizeof(sum[0]); j++)
	{
		for (int i = 1; i < num.size(); i++)
		{
			float aa =(float)atof( num[i][j + 2].c_str());  // ½«vector¶Áµ½µÄÊı¾İ×ªÎªfloatĞÍ
			sum[j] += aa;
		}
	}

	// ¶Ô³ı±íÍ·ÒÔÍâµÄÊı¾İ½øĞĞ²Ù×÷
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 2; j < num[i].size(); j++)
		{   
			float a = (float)atof(num[i][j].c_str());
			float lenNum = (float)atof(num[i][1].c_str());
			float db2 = a * 1000 * 1000000 / (lenNum * sum[j - 2]);  // FPKM
			ostringstream oss;
			oss.setf(ios::fixed);  // °´¹Ì¶¨µã·½Ê½ÏÔÊ¾¸¡µãÊı
			oss.precision(20);  // ±£Áô20Î»Ğ¡Êı
			
			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}
		
	}

	std::ofstream outFile;
	//  ´ò¿ªÎÄ¼ş
	outFile.open(dstFile);
	//  ½«vectorÖĞÊı¾İĞ´ÈëÎÄ±¾
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
	vector<vector<string>>num;  // vectorÈİÆ÷ÓÃÀ´´æ·ÅÊı¾İ£¨Ã¿Ò»ĞĞÊı¾İÎªÒ»¸övector£©£¬Í³Ò»°´stringĞÍÊı¾İ¶ÁÈ¡

	//  °´ĞĞ¶ÁÈ¡ÎÄ¼ş
	while (getline(inFile, str))
	{
		istringstream input(str);
		
		vector<string> tmp;  // ÁÙÊ±vectorÓÃÀ´´æ·ÅÃ¿ĞĞÊı¾İ
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
			oss.setf(ios::fixed);  // °´¹Ì¶¨µã·½Ê½ÏÔÊ¾¸¡µãÊı
			oss.precision(20);  // ±£Áô20Î»Ğ¡Êı

			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}
		
	}

	std::ofstream outFile;
	//  ´ò¿ªĞ´ÈëÎÄ¼şÃû£¬½«vectorÖĞÊı¾İĞ´ÈëÎÄ¼ş
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

/*¿¿¿¿¿
 *1. ¿¿¿¿¿¿¿¿¿¿tmpArrayMed¿¿
 *2. ¿¿MAD¿CV¿
 *3. ¿¿¿¿¿tmpArrayMed¿¿
 *4. ¿¿MAD¿CV¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿-1
 *5. ¿tmpArrayMed¿¿¿¿¿¿¿¿-1¿¿¿¿¿¿¿*/
void FileOperate::DataFilter(string srcFile, string dstFile, string op,float val)
{
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out | ios::app);
	string str;  // ¿¿¿¿¿¿¿¿
	vector<vector<string>>num;  // vectorÈİÆ÷ÓÃÀ´´æ·ÅÊı¾İ£¨Ã¿Ò»ĞĞÊı¾İÎªÒ»¸övector£©£¬Í³Ò»°´stringĞÍÊı¾İ¶ÁÈ¡
	vector<vector<float>>array(49);
	vector<vector<float>>arraySort(49);
	vector<vector<string>>store; //¿¿¿¿¿¿¿¿¿¿¿¿¿
	for(int i=0;i<arraySort.size();i++)
	{
		arraySort[i].resize(23);
		array[i].resize(23);
	}
	int genNum[49] = { 0 };  // Í³¼Æ»ùÒòÊıÁ¿
	//  °´ĞĞ¶ÁÈ¡ÎÄ¼ş
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
		vector<string> tmp;  // ÁÙÊ±vectorÓÃÀ´´æ·ÅÃ¿ĞĞÊı¾İ
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


	float median[49] = { 0 };  // ´æ·ÅÔ´Êı¾İÖĞÎ»Êı¼°×îºóËùÇó¾ø¶ÔÖĞÎ»²îµÄÖĞÎ»Êı
	////CVÖµ
	float cv[49] = { 0 };
	float avg[49] = { 0 };  // ´æ·ÅÔ´Êı¾İÆ½¾ùÊı
	float sd[49] = { 0 };  // ±ê×¼Æ«²î 
	float sum[49] = { 0 };


	/*********************MAD¼ÆËã*********************/
	// ÇóÔ´Êı¾İµÄÖĞÎ»Êı.
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
	// ÇóÔ´Êı¾İµÄ¾ø¶ÔÖĞÎ»²î
	for (int i = 1; i <array.size();i++ )
	{
		for (int j = 1; j < array[i].size();j++)
		{
			float aa = array[i][j];
			float tmpMedian = (float)abs(aa - median[i]);  
			arraySort[i][j]=tmpMedian;
		}
		// ¼ÆËãMAD£º¾ø¶ÔÖĞÎ»²îµÄÖĞ¼äÊı
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
	/********************¼ÆËãCV**********************/
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
			store[i][j]=str;
		}
	}
	std::ofstream outFile;
	//  ´ò¿ªĞ´ÈëÎÄ¼şÃû£¬½«vectorÖĞÊı¾İĞ´ÈëÎÄ¼ş
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
				tag++;
				size--;
				break;
			}
			else
			{
				
				store[i-tag].push_back(num[i][j]);
			}
			

		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < store[i].size(); j++)
		{	
	
			outFile << store[i][j] << "\t";

		}

		outFile << endl;
	}

	inFile.close();
	outFile.close();
}
