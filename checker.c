#include "bmp.h"

BMP bmp1, bmp2;

void check()
{
	Pixel *pixel1, *pixel2;
	int i, j, idx;
	int diffCount = 0;

	for(i = 0; i < bmp1.height; i++){
		for(j = 0; j < bmp1.width; j++){
			idx = i*bmp1.width + j;	
			pixel1 = (Pixel *) &bmp1.data[idx*sizeof(Pixel)];
			pixel2 = (Pixel *) &bmp2.data[idx*sizeof(Pixel)];
			if((pixel1->R != pixel2->R) || (pixel1->G != pixel2->G) || 
				 (pixel1->B != pixel2->B)){
				//printf("pixel(%d, %d) is diff.!\n", j, i);
				diffCount++;
			}
			if(pixel1->R != pixel2->R) 
				printf("pixel(%d, %d) R is diff.!\n", j, i);
		  if(pixel1->G != pixel2->G)
				printf("pixel(%d, %d) G is diff.!\n", j, i);
		  if(pixel1->B != pixel2->B)
				printf("pixel(%d, %d) B is diff.!\n", j, i);
		}
	}
	float diff = diffCount/(bmp1.height*bmp1.width);
	printf("Diff. count = %d\n", diffCount);
	printf("They have %f\% difference!\n", diff*100);
}

int main()
{
	bmpLoad(&bmp1, "./Output/sharpMaple.bmp");
	bmpLoad(&bmp2, "./Compare/sharpMapleRZ.bmp");

	check();

	return 0;
}
