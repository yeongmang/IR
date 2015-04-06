#include<stdio.h>
#include<string.h>

#define N 11

typedef struct tab
{
	char token[100];
	int arr[12];
}table;

table db[100000];
int count =-1;

char *strlwr(char *inp)
{
	int len = strlen(inp);
	int i;
	for(i=0;i<len;i++)
	{
		if(inp[i]>='A' && inp[i]<='Z')
			inp[i]+=32;
	}
	return inp;
}

int isStopword(char *inp)
{
	FILE *sp;
	sp = fopen("stop_word.txt","r");
	char temp[100];

	while(!feof(sp))
	{
		fscanf(sp,"%s",temp);
		int cmp =1;
		cmp = strcmp(inp,temp);

		if(!cmp)
		{
			fclose(sp);
			return 1;
		}

	}
	fclose(sp);
	return 0;
}

void create_tab(int iter)
{

	FILE *fp;
	char file[100],inp[100];
	char temp[100];
	if(iter==10)
	{
		sprintf(file,"AP890321-00%d.txt",iter);
//		sprintf(file,"%d.txt",iter);
	}
	else
	{
		sprintf(file,"AP890321-000%d.txt",iter);
//		sprintf(file,"%d.txt",iter);
	}

	fp = fopen(file,"r");

	int flag =0;
	int cmp =1;
	FILE *sp;
	int temp_val = 1;
	while(!feof(fp))
	{
		fscanf(fp,"%s",inp);
		strlwr(inp);
		int j,len;
		len = strlen(inp);
		int i;
		for(i=len-1;i>=0;i--)
		{
			if((inp[i]>='A' && inp[i]<='Z')||(inp[i]>='a'&&inp[i]<='z'))
			{
				break;
			}
			else
			{
				inp[i]='\0';
				len--;
			}
		}
		if(len==0 )
			continue;



		if(!isStopword(inp))
		{

		 cmp =1;
		flag =0;
		for(j=0;j<=count;j++)
		{
			cmp = strcmp(db[j].token,inp);
			if(cmp==0)
			{
				flag =1;
				db[j].arr[iter]=1;
			}

		}
		if(!flag)
		{
			count++;
			db[count].arr[iter] = 1;
			strcpy(db[count].token,inp);
		}
	   }
	}
	fclose(fp);
}

void DT_table(int count)
{
    int i,j;
    for(i=1;i<N;i++)
        create_tab(i);

    for(i=0;i<=count;i++)
	{
		printf("%s \t\t",db[i].token);
		int j;
		for(j=1;j<N;j++)
		{
			printf("%d\t",db[i].arr[j]);
		}
		printf("\n");
	}
}
int main()
{
	int i;
	//freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);

    DT_table(count);

	return 0;
}
