#include<stdio.h>
#include<string.h>

void grep(char *a,int iter)
{
	FILE *f;
	char file[20];
	sprintf(file,"%d.txt",iter);
	f= fopen(file,"r");
	char inp[100000];
	int count=0,flag =0;
	printf("Searching for %s\n",a);
	int cmp=1;
	do
	{
		fscanf(f,"%s",inp);
	
		int len = strlen(inp);
		
//		printf("%d\n",len);
		
		if(inp[len] =='\0')
		{
			printf("%c",inp[len]);
			count++;
		}
		

//		printf("%s\n",inp);
//		printf("count = %d\n",count);
		cmp = strcmp(a,inp);	
		if(cmp==0)
		{
			flag = 1;
			printf("Word Match in file %d\tand word number  = %d\n",iter,count);
			
		}

	}while(!feof(f));
	
	if(!flag)
		printf("Word not found\n");
}

int main()
{
//	FILE *fp;
//	fp = fopen("1.txt","r");
	char ab[100];
	printf("Enter a string\n");
	scanf("%s",ab);
	int i;
	for(i=1;i<=10;i++)
		grep(ab,i);
	return 0;

}
