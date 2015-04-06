#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define N 10

typedef struct cluster
{
	char str[12];
	int flag;
}clust;
float dist[N][N], p[N][2];

void ED()
{
	int i, j, k;
	float temp;
	for(i=0; i<N; i++)
	{
		for(j=i; j<N; j++)
		{
			if(i == j)
			{
				dist[i][j] = 0.0;
				continue;
			}
			dist[i][j] = ((p[i][0]-p[j][0])*(p[i][0]-p[j][0]) + (p[i][1]-p[j][1])*(p[i][1]-p[j][1]));
			dist[j][i] = dist[i][j];
		}
	}
}

int main()
{

	FILE *fp;
	clust c[10];
	fp =fopen("lab12input.txt", "r");
	int i, j, k, count=1, l, m, n;
	float min=99999.0;
	for(i=0; i<N; i++)
	{
		fscanf(fp, "%f %f\n",&p[i][0], &p[i][1]);
		c[i].str[0] = i+'0';
		c[i].str[1] = '\0';
		c[i].flag = 1;
		//printf("%s\n", c[i].str);
	}
	ED();
	for(i=0; i<N; i++)
	{
		printf("%d ", i);
		for(j=0; j<N; j++)
			printf("%.4f	", dist[i][j]);
		printf("\n\n\n");
	}
	printf("\nSingle Linkage Clustering\n\n");
	while(count<N)
	{
		min = 99999.0;
		count++;
		for(i=0; i<N; i++)
		{
			if(c[i].flag)
			for(j=0; j<N; j++)
			if(c[j].flag)
			{
				if(i==j)
					continue;
				if(dist[i][j] < min)
				{
					min = dist[i][j];
					k = i;
					l = j;
				}
			}
		}
		m = (k<l)?k:l;
		n = (k<l)?l:k;
		for(i=0; i<N; i++)
		{
			 if(dist[m][i] > dist[n][i])
				dist[m][i] = dist[n][i];
		}
		strcat(c[m].str, c[n].str);
		c[n].flag = 0;
		printf("Iteration %d\n", count-1);
	    /*for(i=0; i<N; i++)
		{	printf("%d ", i);
			for(j=0; j<N; j++)
			printf("%.4f	", dist[i][j]);
			printf("\n\n");
		}*/
		for(i=0; i<N; i++)
		{
			if(c[i].flag)
			printf("%s  ", c[i].str);
		}
		printf("\n");
	}
	printf("\nComplete Linkage Clustering\n\n");
	for(i=0; i<N; i++)
	{
		fscanf(fp, "%f %f\n",&p[i][0], &p[i][1]);
		c[i].str[0] = i+'0';
		c[i].str[1] = '\0';
		c[i].flag = 1;
		//printf("%s\n", c[i].str);
	}
	ED();
	count = 1;
	while(count<N)
	{
		min = 99999.0;
		count++;
		for(i=0; i<N; i++)
		{
			if(c[i].flag)
			for(j=0; j<N; j++)
			if(c[j].flag)
			{
				if(i==j)
					continue;
				if(dist[i][j] < min)
				{
					min = dist[i][j];
					k = i;
					l = j;
				}
			}
		}
		m = (k<l)?k:l;
		n = (k<l)?l:k;
		for(i=0; i<N; i++)
		{
            if(dist[m][i]==0 || dist[n][i]==0)
                dist[m][i]=0;
            else if(dist[m][i] < dist[n][i])
				dist[m][i] = dist[n][i];
		}
		strcat(c[m].str, c[n].str);
		c[n].flag = 0;
		printf("Iteration %d\n", count-1);
		for(i=0; i<N; i++)
		{
			if(c[i].flag)
			printf("%s  ", c[i].str);
		}
		printf("\n");
        /*for(i=0; i<N; i++)
		{	printf("%d  ", i);
			for(j=0; j<N; j++)
			printf("%.4f  ", dist[i][j]);
			printf("\n\n");
		}*/
	}

	fclose(fp);
	return 0;
}
