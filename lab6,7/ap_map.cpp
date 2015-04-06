#include<stdio.h>
#include<math.h>
#include<string.h>

int main()
{
	FILE *fptr;
	fptr = fopen("RelevanceDoc.txt", "r");
	if(fptr == NULL)
		printf("here\n");
	int k=0, val=0, i=0, j=0;
	char docid[5], relval[2];
	float ap[6] = {0}, map = 0, t=0, rel = 10;
	while(!feof(fptr))
	{
		fscanf(fptr, "%s", docid);
		fscanf(fptr, "%s", relval);
		if(!strcmp(relval, "1"))
			i++;
		k++;
		t += ((1.0 * i)/k);
		if(k%10==0)
		{
			ap[j] = t/rel;
			j++;
			k=0;
			i=0;
			t=0;
		}
	}
	for(i=0; i<6; i++)
	{
		printf("AP for system %d = %f\n", i+1, ap[i]);
		map += ap[i];
	}
	map /= 6;
	printf("MAP = %f\n", map);
	fclose(fptr);
	return 0;
}
