#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
using namespace std;

struct chck
{
    int *flag;
};

struct chck2
{
    string key;
    int i;
};

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}
 
 vector<bool> getDocRel() {
	ifstream infile;
	string data[4];
	vector<bool> v;
	int count = 0;
	infile.open("../docRel.txt");
	if (infile.is_open()) {
		while (!(infile.eof() || count == 10)) {
			for (int i = 0; i < 4; i++) {
				infile >> data[i];
			}
			if (data[0] == "301") {
				count++;
				v.push_back(data[3] == "0" ? false : true);
			}
		}
	}
	infile.close();
	return v;
}


int isStopWord(string t)
{
    fstream infile("StopWord.txt");
    string line;
    while( getline (infile,line) )
    {
        istringstream iss(line);
    string word;
    while(iss >> word){
        if(word.compare(t)==0)
        {
            return 1;
        }
    }
    }
    return 0;
}

vector<string> files = vector<string>();
vector<string> files2= vector<string>();
map<string,struct chck>  v;
int ** temp;
map<string,int> query_map;
int nt=0;
float *res;
int query_no;
int filesCount;


float dot(int i)
{
    float f=0;
    int j=0;
    float q_temp=0;
    float d_temp=0;
for( map<string,int>::iterator ii=query_map.begin(); ii!=query_map.end(); ++ii)
{
        f+=((*ii).second) * temp[i][j];
        q_temp+=(*ii).second * (*ii).second;
        d_temp+=temp[i][j] * temp[i][j];
        j++;
}
return (f/(sqrt(q_temp) * sqrt(d_temp)));
}

void vec_dot()
{
    for(int i=0;i<filesCount;i++)
    {
        res[i]=dot(i);
    }
    cout<<files2.size()<<endl;
    for(int i=0;i<files2.size();i++)
        for(int j=0;j<files2.size()-1-i;j++)
    {
        if(res[j]>res[j+1])
        {
            float value = res[j];
            res[j] = res[j+1];
            res[j+1]=value;
            string fValue =files2[j];
            files2[j] = files2[j+1];
            files2[j+1]=fValue;
        }
    }
    cout<<endl;
   for(int i=0;i<filesCount;i++)
    {
        cout<<files2[i]<<" : ";
        cout<<res[i]<<endl;
    }

}



int main()
{
 string dir = string(".");

    getdir(dir,files);
    filesCount=0;
     for (unsigned int i = 0;i < files.size();i++) {
	if(files[i].substr(files[i].find_last_of(".") + 1) == "txt")
	{
	    if(files[i].compare("StopWord.txt") )
            {
                files2.push_back(files[i]);
                filesCount++;
            }
	}
     }
 cout<<filesCount<<endl;

    for(int i=0;i<files2.size();i++)
    {
        const char * c=files2[i].c_str();
		fstream infile(c);
        string line;
        while( getline (infile,line) )
		{

        istringstream iss(line);
    string word;
    while(iss >> word) {
            if(isStopWord(word))
            {
                    cout<<word <<" is stopword \n";
            }
            else
            {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
        if(v.find(word)==v.end())
        {
            struct chck t;
            t.flag=(int *)malloc(sizeof(int)*filesCount);
            for(int j=0;j<filesCount;j++)
                t.flag[j]=0;
            t.flag[i]+=1;
            v[word]=t;
        }
        else
        {
            v[word].flag[i]+=1;
        }
    }
    }
    }
    }
  //  map<string,int *> v2;
     temp=(int **)malloc(sizeof(int *)*filesCount);
    for(int i=0;i<filesCount;i++)
    {
        temp[i]=new int[v.size()];
    }

    int j=0;
    for( map<string,struct chck>::iterator ii=v.begin(); ii!=v.end(); ++ii)
   {
       cout << (*ii).first << ": " ;
       for(int i=0;i<filesCount;i++)
       {
            temp[i][j]=(*ii).second.flag[i];
           cout<<(*ii).second.flag[i];
       }
        j++;
       cout<<endl;
   }
for(int i=0;i<filesCount;i++)
{
    cout<<files2[i]<<": ";
    for(int j=0;j<v.size();j++)
    {
        cout<<temp[i][j];
    }
    cout<<endl<<endl;
}

   for(int i=0;i<filesCount;i++)
   {
       cout<<files2[i]<<endl;
   }

    string query;
    cout<<endl<<"Enter the query: ";
    getline(cin,query);
    cout<<"Query is :"<<query<<endl;

    istringstream iss(query);
    string word;

    int uq=0;
    query_no=-1;
        res=(float *)malloc(filesCount* sizeof(float));
    for(int i=0;i<filesCount;i++)
        res[i]=0;

    for( map<string,struct chck >::iterator ii=v.begin(); ii!=v.end(); ++ii)
    {
        query_map[(*ii).first]=0;
    }

    cout<<"\n\n";
    while(iss >> word){

             transform(word.begin(), word.end(), word.begin(), ::tolower);
             if(v.find(word)!=v.end())
            {


                    cout<<word<<" ";
                    query_map[word]+=1;
            }
            else
            {
                cout<<"Unrecognizing query\n";
                uq=1;
                break;
            }
    }
    if(uq==0)
    {

        cout<<"query_map : \n";
        for( map<string,int>::iterator ii=query_map.begin(); ii!=query_map.end(); ++ii)
        {
            cout<<(*ii).first<<" "<<(*ii).second<<endl;
        }
        vec_dot();

    }

    vector<bool> relVector;
	relVector = getDocRel();
	for (int i = 0; i < relVector.size(); i++) {
		cout << relVector[i] << endl;
	}
}

