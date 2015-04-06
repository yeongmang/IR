// Vector scale model

#include<stdio.h>
#include<string.h>
#include<math.h>

#define N 11
double db_mod[15];
typedef struct tab
{
	char token[100];
	int arr[12];
}table;

typedef struct qr
{
    char tok[100];
    int val;
}qd;

qd enq[1000];
table db[100000];
int count =-1;


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
				db[j].arr[iter]++;
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

int main()
{
int i,j,k;
char temp[100];
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	for(i=1;i<N;i++)
		create_tab(i);

//... Creatign each modulo

	for(i=1;i<11;i++)
    {
        for(j=0;j<=count;j++)
        {
            db_mod[i]+=db[j].arr[i]*db[j].arr[i];
        }
        db_mod[i]=sqrt(db_mod[i]);
        printf("db_mod[%d] = %lf\n",i,db_mod[i]);
    }


//.......................................
/*    for(i=0;i<=count;i++)
    {
        for(j=0;j<=count;j++)
        {
                if(strcmp(db[i].token,db[j].token)<0)
                {
                    strcpy(temp,db[i].token);
                    strcpy(db[i].token,db[j].token);
                    strcpy(db[j].token,temp);
                }

        }
    }
*/
    // Vector space Model

    FILE *qp;
    char inp[100];
    double query_mod,doc_mod;
    qp = fopen("input.txt","r");
    int qr_count=-1,flag=0;
    while(!feof(qp))
    {
        fscanf(qp,"%s",inp);
        flag =0;
        for(i=0;i<=qr_count;i++)
        {
            if(strcmp(inp,enq[i].tok)==0)
            {
                flag =1;
                enq[i].val++;
                break;
            }
        }
        if(!flag)
        {
            strcpy(enq[++qr_count].tok,inp);
            enq[qr_count].val=1;

        }
    }

    //printf("qr_count = %d and it si %s\n",qr_count, enq[qr_count].tok);
    int ans =0;
    for(i=0;i<=qr_count;i++)
    {
        ans += enq[i].val*enq[i].val;
    }
    query_mod = sqrt(ans);

    printf("query mod = %lf\n",query_mod);
    double sim[12];
    ans =0;
    for(i=1;i<11;i++)
    {    ans =0;
        for(j=0;j<=qr_count;j++)
        {
            for(k=0;k<=count;k++)
            {
                    if(strcmp(enq[j].tok,db[k].token)==0)
                    {
                        printf("here\n");
                        ans += enq[j].val*db[k].arr[i];
                    }
            }
        }
        printf("ans for %d = %d\n",i,ans);
        sim[i]=(ans/(query_mod*db_mod[i]));
    }

    for(i=1;i<11;i++)
        printf("sim = %lf\n",sim[i]);

    double temp1;
    int prior[12];
    for(i=1;i<11;i++)
        prior[i]=i;
    int temp2;
    for(i=1;i<11;i++)
        for(j=1;j<11;j++)
        {
            if(sim[i]>sim[j])
            {
                temp1 = sim[i];
                sim[i] = sim[j];
                sim[j] = temp1;

                temp2 = prior[i];
                prior[i] = prior[j];
                prior[j] = temp2;
            }
        }

    printf("Search result is as follow \n");


    for(i=1;i<11;i++)
        printf("sim = %lf\n",sim[i]);


    for(i=1;i<11;i++)
    {
        printf("Document %d\n",prior[i]);
    }
//	printf("count= %d\n",count);

//	printf("count= %d\n",count);

	return 0;
}
