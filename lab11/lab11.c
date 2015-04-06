#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

float centroid[3][2], dist[3];
float clust[3][1000][2];
int c[3], k = 3;

ED (float x1, float y1)
{
 	  int i, flag = 0;
 	  float min = 99999.0;
	  for(i=0; i<k; i++)
	  {
   	   		   dist[i] = sqrt((x1-centroid[i][0])*(x1-centroid[i][0]) + (y1-centroid[i][1])*(y1-centroid[i][1])); 
   	   		   if(dist[i] < min)
   	   		   {
  		   			  flag = i;
  		   			  min = dist[i];
	           }
	  }
	  
	  clust[flag][c[flag]][0] = x1;
	  clust[flag][c[flag]][1] = y1;
	  c[flag]++;
}
int main()
{
 	 FILE *fptr;
 	 fptr = fopen("k-means.txt", "r");
 	 
	 float x, y;
	 int i, j;
	 float temp[3][2], temp_x[3], temp_y[3];
	 int count[3] = {0}, change=0;	
	 for(i=0; i<k; i++)
	 {
	 	fscanf(fptr, "( %f , %f )\n", &centroid[i][0], &centroid[i][1]);
	 	printf("%f , %f\n", centroid[i][0], centroid[i][1]);
	 	temp[i][0] = centroid[i][0];
	 	temp[i][1] = centroid[i][1];
	 }
	 while(!feof(fptr))
	 {
	 	fscanf(fptr, "( %f , %f )\n", &x, &y);
	 	ED (x, y);
	 }
	 	 
	 for(i=0; i<k; i++)
	 {
	 	temp_x[i] = temp_y[i] = 0;
	 	for(j=0; j<c[i]; j++)
	 	{
	 		temp_x[i] += clust[i][j][0];
	 		temp_y[i] += clust[i][j][1];
 		}
	 	temp_x[i] /= c[i];
		temp_y[i] /= c[i];
		if(temp_x[i] != temp[i][0] || temp_y[i] != temp[i][1])
				  change = 1;
    }
    
    while(change == 1)
    {
    	
    	change = 0;
    	for(i=0; i<k; i++)
    	{
    		c[i] = 0;
    		temp[i][0] = temp_x[i];
    		temp[i][1] = temp_y[i];
    		centroid[i][0] = temp[i][0];
    		centroid[i][1] = temp[i][1];
    	}
    	fseek(fptr, 0, SEEK_SET);
        while(!feof(fptr))
	 	{
	          fscanf(fptr, "( %f , %f )\n", &x, &y);
	 		  ED (x, y);
		}
		for(i=0; i<k; i++)
	 	{
	        temp_x[i] = temp_y[i] = 0;
	 		for(j=0; j<c[i]; j++)
	 		{
 		         temp_x[i] += clust[i][j][0];
	 			 temp_y[i] += clust[i][j][1];
		    }
	 		temp_x[i] /= c[i];
			temp_y[i] /= c[i];
			if(temp_x[i] != temp[i][0] || temp_y[i] != temp[i][1])
				  change = 1;
	    }
    }
    if(change == 0)
    {
    	for(i=0; i<k; i++)
    			 printf("Centroid%d: (%f, %f)\n", i+1, centroid[i][0], centroid[i][1]);
    }
    fclose(fptr);
    return 0;
}
