#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<dirent.h>
#include<string.h>
#include<vector>
#include <sstream>

using namespace std;

typedef struct relevant
{
	int docno;
	int rdoc[30];
}relv;

vector <relv> r;


void check_Relevant()
{
	ifstream infile;
	double recall,precision;
	infile.open("relative_doc_2.txt");
	ofstream outfile("output.txt");
	int temp1,temp2,temp3,i=0;
	string temp;
	int start=301;

	int n=0;
	while(infile>>temp1>>temp2>>temp>>temp3)
	{

		if(i==0)
		{
			r.push_back(relv());
			r[n].docno=temp1;

		}

		if((i<30)&&temp1==start)
		{
			r[n].rdoc[i]=temp3;
			i++;
		}
        else if(i==30)
		{
				start++;
				n++;
				i=0;
		}

	}

        int relas=20;

        for(i=0;i<n;i++)
        {
			outfile<<"Document Number : "<<r[i].docno<<" ***************************************************\n";
			int t,m=1,o;

			//this is for judge 1;
            outfile<<"Judge 1 : "<<endl;
            for(int j=0;j<10;j++)
            {

				 t=r[i].rdoc[j];
            	 if(t==1)
            		m++;

            	 recall=(m*(j+1))/20;
            	 precision=(m*(j+1))/(i+1);
                outfile<<"P-"<<precision<<" "<<"\t";
            	outfile<<"R-"<<recall<<" "<<"\t";


            double fscore=(2*precision*recall)/(precision+recall);
            if(precision+recall==0) fscore=0;
            outfile<<fscore<<"  "<<endl;

            }

            //this is for judge 2;
             outfile<<"\nJudge 2 : "<<endl;
            for(int j=10;j<20;j++)
            {

				 t=r[i].rdoc[j];
            	 if(t==1)
            		m++;

            	 recall=(m*(j+1))/20;
            	 precision=(m*(j+1))/(i+1);
            	outfile<<"P-"<<precision<<" "<<"\t";
            	outfile<<"R-"<<recall<<" "<<"\t";

            double fscore=(2*precision*recall)/(precision+recall);
            if(precision+recall==0) fscore=0;
            outfile<<fscore<<"  "<<endl;

            }

            //this is for judge 3;
             outfile<<"\nJudge 3 : "<<endl;
            for(int j=20;j<29;j++)
            {

				 t=r[i].rdoc[j];
            	 if(t==1)
            		m++;

            	 recall=(m*(j+1))/20;
            	 precision=(m*(j+1))/(i+1);
            	outfile<<"P-"<<precision<<" "<<"\t";
            	outfile<<"R-"<<recall<<" "<<"\t";


            double fscore=(2*precision*recall)/(precision+recall);
            if(precision+recall==0) fscore=0;
           outfile<<fscore<<"  "<<endl;

            }
            outfile<<endl<<endl;
			m=0;
        }

}


int main()
{

      //
        string str,word;

        check_Relevant();

    return 0;
}

