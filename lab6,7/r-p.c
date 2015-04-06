#include<stdio.h>
#include<math.h>
#include<string.h>

int main()
{
	FILE *fptr;
	fptr = fopen("RelevanceDoc.txt", "r");
	int k=0, rel = 15, ret=10, total = 30, tp=0, tn=0, fp=0, fn=0, c=0, parity[6], p=0;
	char docid[5], relval[2];
	while(!feof(fptr))
	{
		fscanf(fptr, "%s", docid);
		fscanf(fptr, "%s", relval);
			c++;
			if(!strcmp(relval, "1"))
				p++;
			if(c%10 == 0)
			{
				parity[k] = p;
				k++;
				p=0;		
			}	
	}
	float recall[6]={0}, precision[6]={0}, f_score[6]={0};
	int i, j;
	for(i=0; i<6; i++)
	{
		tp = parity[i];
		tn = ret - parity[i];
		fn = rel - parity[i];
		fp = (total - rel) - (ret - parity[i]);
		precision[i] = (float)tp/(tp + fp);
		recall[i] = (float)tp/(tp+fn);
		f_score[i] = 2.0 * precision[i] * recall[i]/(precision[i] + recall[i]);	
		printf("System %d: Parity = %d, Precision = %f, Recall = %f, F-score = %f\n", i+1, parity[i], precision[i], recall[i], f_score[i]);
	}
	return 0;
}
