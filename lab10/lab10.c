#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	freopen("output.txt", "r",stdin);
	int x, y, xmin_c1, xmax_c1, ymin_c1, ymax_c1, test_x, test_y, div;
	int xmin_c2, xmax_c2, ymin_c2, ymax_c2, count_c1, count_c2, clas, total;
	char ch;
	count_c1 = count_c2 = total = 0;
	xmax_c1 = xmax_c2 = ymax_c1 = ymax_c2 = -99999;
	xmin_c1 = xmin_c2 = ymin_c1 = ymin_c2 = 99999;
	while(1)
	{
		scanf("(%d,%d)%c", &x, &y, &ch);
		if(ch == '\n')
		{
			test_x = x;
			test_y = y;
			break;
		}
		else
		{
			scanf("C%d\n", &clas);
			//printf("%d %d : %d\n",x,y,clas);
			if(clas == 1)
			{
				count_c1++;
				if(x > xmax_c1)
					xmax_c1 = x;
				if(x < xmin_c1)
					xmin_c1 = x;
				if(y > ymax_c1)
					ymax_c1 = y;
				if(y < ymin_c1)
					ymin_c1 = y;
			}
			else if(clas == 2)
			{
				count_c2++;
				if(x > xmax_c2)
					xmax_c2 = x;
				if(x < xmin_c2)
					xmin_c2 = x;
				if(y > ymax_c2)
					ymax_c2 = y;
				if(y < ymin_c2)
					ymin_c2 = y;
			}
		}
	}
	printf("Class 1\nx-min:%d, x-max:%d, y-min:%d, y-max:%d\n\n", xmin_c1, xmax_c1, ymin_c1, ymax_c1);
	printf("Class 2\nx-min:%d, x-max:%d, y-min:%d, y-max:%d\n\n", xmin_c2, xmax_c2, ymin_c2, ymax_c2);
	printf("Test data\nx:%d, y:%d\n\n", test_x, test_y);
	
	int i, j, k, n=10, count1=0, count2=0, flag1=0, flag2=0;
	float P1, P2, p1, p2, xdiv1, ydiv1, xdiv2, ydiv2, x11, x12, y11, y12, x21, x22, y21, y22;
	P1 = (1.0*count_c1)/(count_c1 + count_c2);
	P2 = (1.0*count_c2)/(count_c1 + count_c2);
	xdiv1 = ((xmax_c1-xmin_c1)*1.0)/n;
	ydiv1 = (1.0*(ymax_c1-ymin_c1))/n;
	x11 = xmin_c1*1.0;
	x12 = x11 + xdiv1;
	while(x12<=xmax_c1*1.0)
	{
		if(test_x>=x11 && test_x<=x12)
		{
			flag1 += 1;
			break;
		}
		x11 += xdiv1;
		x12 += xdiv1;
	}//printf("here\n");
	
	
	y11 = ymin_c1*1.0;
	y12 = y11 + ydiv1;
	while(y12<=ymax_c1*1.0)
	{
		if(test_y>=y11 && test_y<=y12)
		{
			flag1 += 1;
			break;
		}
		y11 += ydiv1;
		y12 += ydiv1;
	}
	xdiv2 = ((xmax_c2-xmin_c2)*1.0)/n;
	ydiv2 = (1.0*(ymax_c2-ymin_c2))/n;
	x21 = xmin_c2*1.0;
	x22 = x21 + xdiv2;
	while(x22<=xmax_c2*1.0)
	{
		if(test_x>=x21 && test_x<=x22)
		{
			flag2 += 1;
			break;
		}
		x21 += xdiv2;
		x22 += xdiv2;
	}
	y21 = ymin_c2*1.0;
	y22 = y21 + ydiv2;
	while(y22<=ymax_c2*1.0)
	{
		if(test_y>=y21 && test_y<=y22)
		{
			flag2 += 1;
			break;
		}
		y21 += ydiv2;
		y22 += ydiv2;
	}
	
	printf("\nx11:%f, x12:%f, y11:%f, y12:%f\nx21:%f, x22:%f, y21:%f, y22:%f\n", x11, x12, y11, y12, x21, x22, y21, y22);
	FILE *fptr;
	fptr = fopen("output.txt", "r");
	
	while(1)
	{
		fscanf(fptr, "(%d,%d)%c", &x, &y, &ch);
		//printf("%d %d %c\n", x, y, ch);
		//break;
		if(ch == '\n')
		{
			break;
		}
		else
		{
			fscanf(fptr, "C%d\n", &clas);
			//printf("%d %d : %d\n",x,y,clas);
			if(clas == 1 && flag1 == 2)
			{
				if(x>=x11 && x<=x12)
				{
					if(y>=y11 && y<=y12)
					{
						count1++;
					}
				}
			}
			else if(clas == 2 && flag2 == 2)
			{
				if(x>=x21 && x<=x22)
				{
					if(y>=y21 && y<=y22)
					{
						count2++;
					}
				}
			}
		}
	}
	
	p1 = (count1*1.0)/count_c1;
	p2 = (count2*1.0)/count_c2;
	printf("P1:%f, P2:%f\np1:%f, p2:%f\n", P1, P2, p1, p2);
	printf("P1*p1:%f\tP2*p2:%f\n", P1*p1, P2*p2);
	
	if(p1*P1 > p2*P2)
		clas = 1;
	else if (p1*P1 < p2*P2)
		clas = 2;
	else
		clas = 0;
	printf("\n\nClass of test data:%d\n", clas);
	return 0;
}
