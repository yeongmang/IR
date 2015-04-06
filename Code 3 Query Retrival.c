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
	/*	sp = fopen("stop_word.txt","r");
		temp_val=0;
		while(!feof(sp))
	{

		fscanf(sp,"%s",temp);
		int cmp =1;
		cmp = strcmp(inp,temp);

		if(!cmp)
			temp_val=1;
	}
	  fclose(sp);*/


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
//		printf("%s\t %d\n",db[count].token,db[count].arr[iter]);
	}
	fclose(fp);
}

int main()
{
	int i;
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	for(i=1;i<N;i++)
		create_tab(i);

/*	for(i=0;i<=count;i++)
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

	char query[100],op[10];
	strlwr(query);
	int ans[12];
	for(i=0;i<11;i++)
		ans[i]=1;

	FILE *np;
	int j;
	np = fopen("input.txt","r");
	strcpy(op,"and");
	while(!feof(np))
	{
		fscanf(np,"%s",query);
		if(!strcmp(query,"and"))
			strcpy(op,"and");
		if(!strcmp(query,"or"))
			strcpy(op,"or");

		for(i=0;i<=count;i++)
		{
			if(!strcmp(db[i].token,query))
			{

				if(!strcmp(op,"and"))
				{
					for(j=1;j<11;j++)
						ans[j]=ans[j]&db[i].arr[j];
				}
				if(!strcmp(op,"or"))
				{
					for(j=1;j<11;j++)
						ans[j]=ans[j]|db[i].arr[j];
				}
				break;
			}

		}
	}
	fclose(np);

	for(i=1;i<11;i++)
	{
		if(ans[i])
			printf("D%d\t",i);
	}
//	printf("count= %d\n",count);
	return 0;
}
