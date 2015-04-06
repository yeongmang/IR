// AP and MAP
#include<stdio.h>
#include<stdlib.h>

int arr[600];

typedef struct tab
{
    int arr,rel;
    double ap;

}table;

table t[600];


void relDocs()
{
    FILE *fp,*fa;
    fp = fopen("1.txt","r");
    fa = fopen("2_mod.txt","w");
    int qid,d,r;
    char inp[50];
    while(!feof(fp))
    {
        fscanf(fp,"%d%d%s%d",&qid,&d,inp,&r);
        if(r && t[qid].arr)
            fprintf(fa,"%d %s\n",qid,inp);
    }
    fclose(fp);
    fclose(fa);
}

void relHash()
{
    FILE *fp;
    int qid1,qid2,rnk;
    char doc1[50],doc2[50];char gbag[100];
    fp = fopen("2.txt","r");
    while(!feof(fp))
    {
            fscanf(fp,"%d%s%s%d%s%s",&qid1,gbag,doc1,&rnk,gbag,gbag);
            t[qid1].arr=1;
    }
    fclose(fp);
}

void nrel()
{
    FILE *fp;
    int a;
    char b[50];
    fp = fopen("2_mod.txt","r");
    while(!feof(fp))
    {
        fscanf(fp,"%d%s",&a,b);
        t[a].rel++;
    }
    fclose(fp);
}
int main()
{

    int i;
    for(i=0;i<600;i++)
    {
        arr[i]=0;
    }
    relHash();
    relDocs();
    nrel();

    FILE *fp,*fq;

    //fq = fopen("2_mod.txt","r");

    int qid1,qid2;
    char doc1[50],doc2[50];char gbag[100];
    double inp,ap1=0,ap2=0,mean_ap=0;
    int a = 0,nq = 0,rnk,nr=0,nw=0,prev_q=0,flag =0;


    fp = fopen("2.txt","r");
    prev_q = 451;
    int alfa =0;
    while(!feof(fp))
    {
       // printf("Entered 1\n");
        fscanf(fp,"%d%s%s%d%s%s",&qid1,gbag,doc1,&rnk,gbag,gbag);
        fq=fopen("2_mod.txt","r");
        flag=0;
        alfa =0;
        while(!feof(fq))
        {

            fscanf(fq,"%d%s",&qid2,doc2);

            if(qid1==qid2)
            {
                //if(qid1==545)
                {
                    //printf("doc2=%s\n",doc2);
                    //getch();
                }
                if(!strcmp(doc1,doc2))
                {
                    alfa++;
                    if(alfa<=rnk)
                    {

                        ap1 = (double)alfa/(rnk+1);
                    }
                    else
                    {
                        ap1=(double)1/(rnk+1);
                        flag=1;
                    }
                    t[qid1].ap +=ap1;
                    break;
                }

            }

        }
        fclose(fq);
        if(prev_q!=qid1)
        {
            nq++;
           // printf("alfa = %d\n",alfa);
            printf("For query %d\tap = %lf\n",prev_q,t[prev_q].ap/t[prev_q].rel);
            mean_ap += (t[prev_q].ap/t[prev_q].rel);
            if(flag)
                alfa=1;
            else
                alfa=0;
            //getch();
            prev_q = qid1;
        }
    }

   // printf("finished\n");

    printf("mean average = %lf\n",mean_ap/nq);
    fclose(fp);
    return 0;
}
