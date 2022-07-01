#include "FileOperate.h"

#include <iomanip>

using namespace std;




void FileOperate::GenToFPKM(string srcFile, string dstFile)
{
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out);
	string str;
	vector<vector<string>>num;  // vector¿¿¿4´¿¿¾¿¨ÿ¿¿¿¾¿ª¿¸¿¿tor£©£¬¿¿°´string¿¿¾¿¡

	while (getline(inFile, str))
	{
		istringstream input(str);
		vector<string> tmp;  // vector¿4´¿ÿ¿¿¾
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
		}
		num.push_back(tmp);
	}

	float *sum=new float[num.size()];//[SUMARRSIZE] = { 0 }; 
	for (int i =2; i < num[i].size(); i++)
	{
		for (int j = 1; j < num.size(); j++)
		{
			float aa = (float)atof(num[j][i].c_str());  // ½«vector¶u½µ¿¿¿ªfloat¿
			sum[i-2] += aa;
		}
	}

	// ¶¿¿¿¿¿¿¾¿¿¿¿
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 2; j < num[i].size(); j++)
		{
			float a = (float)atof(num[i][j].c_str());
			float lenNum = (float)atof(num[i][1].c_str());
			float db2 = a * 1000 * 1000000 / (lenNum * sum[j - 2]);  // FPKM
			ostringstream oss;
			oss.setf(ios::fixed);  // °´¹¿¨µ¿¿¿¿¸¡µ¿
			oss.precision(20);  // ±£´20¿¿¿

			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}

	}

	std::ofstream outFile;
	//  ´¿¿¿þ
	outFile.open(dstFile);
	//  ½«vector¿¿¾¿´¿¿±¾
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
void FileOperate::GenToTPM(string srcFile, string dstFile )
{
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out);
	string str;
	vector<vector<string>>num;  // vectorÈÝÆ÷ÓÃÀ´´æ·ÅÊý¾Ý£¨Ã¿Ò»ÐÐÊý¾ÝÎªÒ»¸övector£©£¬Í³Ò»°´stringÐÍÊý¾Ý¶ÁÈ¡

	//  °´ÐÐ¶ÁÈ¡ÎÄ¼þ
	while (getline(inFile, str))
	{
		istringstream input(str);

		vector<string> tmp;  // ÁÙÊ±vectorÓÃÀ´´æ·ÅÃ¿ÐÐÊý¾Ý
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
		}
		//tmp.push_back("MAD\tCV");
		num.push_back(tmp);
	}


	float *sum=new float [num[0].size()];//[SUMARRSIZE];
	/*for (int i = 0; i < sizeof(sum) / sizeof(sum[0]); i++)
	{
		sum[i] = 0;
	}*/
	/*for(int i=0;i<num.size();i++)
	{
		for(int j=0;j<num[i].size();j++)
		{
			cout<<num[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	for (int j = 1; j < num[j].size();j++)//sizeof(sum) / sizeof(sum[0]); j++)
	{
		for (int i = 1; i < num.size(); i++)
		{
			float aa = (float)atof(num[i][j].c_str());
			sum[j-1] += aa;
		}
	}

	/*for(int i=0;i<sizeof(sum);i++)
	{
		cout<<i<<"="<<sum[i]<<endl;
	}*/
	for (int i = 1; i < num.size(); i++)
	{
		for (int j = 1; j < num[i].size(); j++)
		{
			float a = (float)atof(num[i][j].c_str());
			float db2 = a * 1000000 / (sum[j - 1]);  // TPM
			ostringstream oss;
			oss.setf(ios::fixed);  // °´¹Ì¶¨µã·½Ê½ÏÔÊ¾¸¡µãÊý
			oss.precision(20);  // ±£Áô20Î»Ð¡Êý

			oss << db2;

			string str(oss.str());
			num[i][j] = str;
		}

	}

	std::ofstream outFile;
	//  ´ò¿ªÐ´ÈëÎÄ¼þÃû£¬½«vectorÖÐÊý¾ÝÐ´ÈëÎÄ¼þ
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
void FileOperate::DataFilter(string srcFile, string dstFile, string op, float val)
{
	ifstream inFile;
	inFile.open(srcFile, ios::in | ios::out | ios::app);
	string str;  // ¿¿¿¿¿¿¿¿
	vector<vector<string>>num;  //¿¿¿¿
	vector<vector<float>>array;// (49);
	vector<vector<float>>arraySort;// (49);//¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
	vector<vector<string>>store; // ¿¿¿¿¿¿¿¿¿¿¿
	
	//int genNum[49] = { 0 };  // Í³¼Æ»ùÒòÊýÁ¿
	//int genNum[] = { 0 };  // Í³¼Æ»ùÒòÊýÁ¿

	//  °´ÐÐ¶ÁÈ¡ÎÄ¼þ
	while (getline(inFile, str))
	{
		for (char& c : str)
		{
			if (c == '\t')
			{
				c == ' ';
			}
		}
		str.erase(0, str.find_first_not_of(" "));
		str.erase(str.find_last_not_of(" " + 1));
		istringstream input(str);
		vector<string> tmp;  // ÁÙÊ±vectorÓÃÀ´´æ·ÅÃ¿ÐÐÊý¾Ý
		vector<string>tmp1;
		string a;
		while (input >> a)
		{
			tmp.push_back(a);
			//      tmp1.push_back(a);
		}
		if (op == "MAD")
		{
			tmp.push_back("MAD");
			//      tmp1.push_back("MAD");

		}
		else if (op == "CV")
		{
			tmp.push_back("CV");
			//      tmp1.push_back("CV");

		}

		num.push_back(tmp);
		store.push_back(tmp);
	}
	int *genNum=new int [num.size()];
	for(int i=0;i<sizeof(genNum);i++)
	{
		genNum[i]=0;
	}
	arraySort.resize(num.size()-1);
	array.resize(num.size()-1);
	for (int i = 0; i < arraySort.size(); i++)
	{
		arraySort[i].resize(num[i].size()-1);
		array[i].resize(num[i].size()-1);
	}
	/*for(int i=0;i<num.size();i++)
	{
		cout<<i<<endl;
		for(int j=0;j<num[i].size();j++)
		{
			cout<<num[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	for (int i = 0; i < array.size(); i++)
	{

		for (int j = 0; j < array[i].size(); j++)
		{
			/*if(num[i+1][j+1]!="")
			{
				genNum[i]++;
				//cout<<i<<"="<<genNum[i]<<"\t";
			}*/

			//cout<<num[i][j]<<"\t";
			arraySort[i][j] = (float)atof(num[i+1][j+1].c_str());
			array[i][j] = (float)atof(num[i+1][j+1].c_str());
		}
		//cout<<endl;

	}

	for (int i = 0; i < arraySort.size(); i++)
	{
		//sort(arraySort[i].begin(), arraySort[i].end() - 1);

		for(int j=0;j<arraySort[i].size();j++)
		{
			//cout<<arraySort[i][j]<<"\t";
			if(arraySort[i][j] or arraySort[i][j]==0)
			{
				genNum[i]++;
				//cout<<i<<"="<<genNum[i]<<"\t";
			}

		}
		//cout<<endl;
		//cout<<i<<"="<<genNum[i]<<endl;
		sort(arraySort[i].begin(), arraySort[i].end() - 1);
	}

	int m = num.size();
	float* median = new float[m];//[49] = { 0 };  // ´æ·ÅÔ´Êý¾ÝÖÐÎ»Êý¼°×îºóËùÇó¾ø¶ÔÖÐÎ»²îµÄÖÐÎ»Êý
	//CVÖµ
	float *cv = new float[m];//[49] = { 0 };
	float *avg = new float[m];//[49] = { 0 };  // ´æ·ÅÔ´Êý¾ÝÆ½¾ùÊý
	float *sd = new float[m];//[49] = { 0 };  // ±ê×¼Æ«²î 
	float *sum = new float[m];//[49] = { 0 };
	
	 for(int i=0;i<sizeof(median);i++)
        {
                median[i]=0;
        	cv[i]=0;
		avg[i]=0;
		sd[i]=0;
	}
	 for(int i=0;i<sizeof(sum);i++)
	 {
		 sum[i]=0;
	 }




	//*********************MAD¼ÆËã********************
	// ÇóÔ´Êý¾ÝµÄÖÐÎ»Êý.
	for (int i = 0; i < arraySort.size(); i++)
	{
		int n = genNum[i] - 1;
		//cout<<i<<"="<<genNum[i+1]<<endl;
		if (n < 2)
		{
			median[i] = arraySort[i][0];
		}
		if (n % 2 == 0)
		{

			// median[i] = arraySort[i][n / 2-1];

			median[i] = (arraySort[i][n / 2-1] + arraySort[i][n / 2 ]) / 2;

		}
		else
		{
			//median[i] = (arraySort[i][n / 2-1] + arraySort[i][n / 2 ]) / 2;

			median[i] = arraySort[i][n / 2];
		}

		//cout<<median[i]<<endl;
	}
	// ÇóÔ´Êý¾ÝµÄ¾ø¶ÔÖÐÎ»²î
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < array[i].size(); j++)
		{
			float aa = array[i][j];
			float tmpMedian = (float)abs(aa - median[i]);
			arraySort[i][j] = tmpMedian;
		}
	}
	/*for(int i=0;i<arraySort.size();i++)
        {
                for (int j=0;j<arraySort[i].size();j++)
                {
                        cout<<arraySort[i][j]<<"\t";
                }
                cout<<endl;
        }*/

	for(int i=0;i<array.size();i++)
	{

		sort(arraySort[i].begin(), arraySort[i].end() - 1);
		int n = genNum[i] - 1;
		if (n < 2)
		{
			median[i] = arraySort[i][0];

		}
		if (n % 2 == 0)
		{
			//median[i] = arraySort[i][n / 2-1];

			median[i] = (arraySort[i][n / 2-1] + arraySort[i][n / 2 ]) / 2;

		}
		else
		{
			//median[i] = (arraySort[i][n / 2-1] + arraySort[i][n / 2 ]) / 2;
			median[i] = arraySort[i][n / 2];

		}
		//cout<<median[i]<<endl;
	}
	/*for(int i=0;i<arraySort.size();i++)
	{
		for (int j=0;j<arraySort[i].size();j++)
		{
			cout<<arraySort[i][j]<<"\t";
		}
		cout<<endl;
	}*/
	
	float* sd1 = new float[num.size()];//[49] = { 0 };
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < array[i].size(); j++)
		{
			sum[i] += array[i][j];
		}
		//cout<<sum[i]<<endl;
		avg[i] = sum[i] / (genNum[i]-1);
		//cout<<genNum[i]<<endl;
		//cout<<avg[i]<<endl;
		for (int j = 0; j < (genNum[i]-1); j++)
		{
			sd1[i] += (float)pow(array[i][j] - avg[i], 2);
		}

		//sd[i] = sqrt(sd1[i] / (genNum[i] -1)) / avg[i];
		if (avg[i] == 0)
		{
			sd[i] = -1;
			//cout<<"ERROR!!!"<<endl;
		}
		else
		{
			sd[i] = sqrt(sd1[i] / (genNum[i] -2)) / avg[i];

		}
	}


	for (int i = 0; i < array.size(); i++)
	{
		//cout<<i<<"="<<array[i].size()<<endl;
		for (int j = genNum[i]-1; j < array[i].size(); j++)
		{
			if (op == "MAD")
			{
				array[i][j] = median[i];
			}
			else
			{
				array[i][j] = sd[i];
			}
		}
	}

	/*for(int i=0;i<array.size();i++)
        {
                for (int j=0;j<array[i].size();j++)
                {
                        cout<<array[i][j]<<"\t";
                }
                cout<<endl;
        }*/

	for (int i=0;i<array.size();i++)
	{
		if(array[i][array[i].size()-1]<val)
		{
			num[i+1][0]="-1";
			store[i+1][0]="-1";
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

					if (array[i-1][j-1] < val)
					{
						num[i][0] = "-1";
						store[i][0]="-1";
					}
				}
				float db2 = array[i-1][j-1];
                        	oss.setf(ios::fixed);
                        	oss << db2;
                       		string str(oss.str());
                        	num[i][j] = str;
                        	store[i][j]=str;

			}
			else if (op == "CV")
			{
				 //cout<<"here  CV"<<endl;
				//cout<<"genNum"<<i<<"="<<genNum[i]<<endl;
				if (j == genNum[i])
				{
					oss.precision(2);
	
					if (array[i-1][j-1] < val)
					{
						num[i][0] = "-1";
						store[i][0]="-1";
					}
				}
				float db2 = array[i-1][j-1];
                        	oss.setf(ios::fixed);
                       		oss << db2;
                        	string str(oss.str());
                	        num[i][j] = str;
				store[i][j]=str;
	
			}
		}
	}

	
	std::ofstream outFile;
	//  ´ò¿ªÐ´ÈëÎÄ¼þÃû£¬½«vectorÖÐÊý¾ÝÐ´ÈëÎÄ¼þ
	outFile.open(dstFile);
	int tag = 0;
	int size=store.size();
	for (int i = 0; i < num.size(); i++)
	{
		for (int j = 0; j < num[i].size(); j++)
		{
			if (num[i][0] == "-1")
			{
				//cout << "num" << i << "=" << "-1" << endl;;
				tag++;
				size--;
				break;
			}
			else
			{
				//store[i-tag][j]=num[i][j];
				//cout << "num" << i << j << "=" << num[i][j] << endl;
				store[i - tag].push_back(num[i][j]);
			}


		}
		//cout << store[i - tag].size() << endl;
	}
	cout << endl << endl;
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<store[i].size()-num[i].size();j++)
		{
			cout<<store[i][j+num[i].size()]<<"\t";
		}
		cout<<endl;
	}
	for (int i = 0; i < size; i++)
	{
	//	if(store[i][0]!="-1")
		{


			for (int j = 0; j < store[i].size()-num[i].size() ; j++)
			{

				outFile << store[i][j +num[i].size()] << "\t";
			}
		}

		outFile << endl;
	}
	delete[] cv;
	delete[] avg;
	delete[] sd;
	delete[] sd1;
	delete[] sum;
	delete[]genNum;
	inFile.close();
	outFile.close();
	//	cout<<"break"<<endl;
}
