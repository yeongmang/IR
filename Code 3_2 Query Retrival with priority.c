#include<stdio.h>
#include<string.h>

#define N 11

typedef struct tab
{
	char token[100];
	int arr[12];
}table;

table db[100000];
int count =-1,temp[12];

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
		sprintf(file,"AP890321-00%d.txt",iter);
	else
		sprintf(file,"AP890321-000%d.txt",iter);


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

	int ans[12];

int *getval(char *query)
{
	int i;
	for(i=0;i<=count;i++)
	{
		if(!strcmp(db[i].token,query))
			return db[i].arr;
	}
}

int * calculate(int *query1, int *query2,char *op)
{
	int i,j;
	if(!strcmp(op,"and"))
	{
		for(j=1;j<11;j++)
			temp[j]=query1[j]&query2[j];
	}
	if(!strcmp(op,"or"))
	{
		for(j=1;j<11;j++)
			temp[j]=query1[j]|query2[j];
	}
	if(!strcmp(op,"but"))
	{
		for(j=1;j<11;j++)
			temp[j]=query1[j]&(1-query2[j]);
	}
	return temp;


}

int main()
{
	int i;
	freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	for(i=1;i<N;i++)
		create_tab(i);
/*
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
*/
	//Query dekho bhai

	char query1[100],query2[100],inp[100],op1[10],op2[10],no[1];
	int *ans1,*ans2;
	//strlwr(query);

	for(i=0;i<11;i++)
		ans[i]=1;

	FILE *np;
	int j;
	np = fopen("input.txt","r");
	fscanf(np,"%s",query1);

	ans1 = getval(query1);
	strcpy(op1,"none");
	//strcpy(op2,"none");
	while(!feof(np))
	{
		fscanf(np,"%s",inp);
		fscanf(np,"%s",query2);
		if(feof(np))
			break;
		//printf("inp = %s\n",inp);
		if(!strcmp(inp,"and"))
		{
			//printf("inp = %s\n",inp);

			if(!strcmp(op1,"none"))
			{
				ans1 = calculate(ans1,getval(query2),"and");
			}
			else
			{
				ans2 = calculate(getval(query2),ans2,"and");
				int j;
				/*for(j=1;j<11;j++)
				{

					printf("%d\t",ans2[j]);
				}
				printf("\n");*/
			}

		}
		else if(!strcmp(inp,"or"))
		{
			//fscanf(np,"%s",query2);
			if(!strcmp(op1,"or"))
			{
				ans1=  calculate(ans1,ans2,"or");
				ans2 = getval(query2);
			}
			else if(!strcmp(op1,"none"))
			{
				strcpy(op1,"or");
				ans2 = getval(query2);


			}
		}
		else if(!strcmp(inp,"but"))
		{
			//fscanf(np,"%s",query2);
			if(!strcmp(op1,"none"))
			{
				ans1 = calculate(ans1,getval(query2),"but");
			}
			else
			{
				ans2 = calculate(ans2,getval(query2),"but");
			}
		}

	}
	if(!strcmp(op1,"or"))
	{
		ans1= calculate(ans1,ans2,"or");
	}
	fclose(np);

	for(i=1;i<11;i++)
	{
		if(ans1[i])
			printf("D%d\t",i);
	}
	printf("\n");
//	printf("count= %d\n",count);

	return 0;
}
