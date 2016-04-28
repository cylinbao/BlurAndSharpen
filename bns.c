#include <time.h>
#include "bmp.h"

#define kernSize 9
#define numInput 3
#define numFilter 2

int filters[numFilter][kernSize][kernSize] = {
   8,  18,  34,  50,  56,  50,  34,  18,  8,
  18,  44,  82, 119, 135, 119,  82,  44, 18,
  34,  82, 153, 223, 253, 223, 153,  82, 34,
  50, 119, 223, 325, 368, 325, 223, 119, 50,
  56, 135, 253, 368, 417, 368, 253, 135, 56,
  50, 119, 223, 325, 368, 325, 223, 119, 50,
  34,  82, 153, 223, 253, 223, 153,  82, 34,
  18,  44,  82, 119, 135, 119,  82,  44, 18,
   8,  18,  34,  50,  56,  50,  34,  18,  8,

	 0,   1,   1,   2,   2,   2,   1,   1,  0,
	 1,   2,   4,   5,   5,   5,   4,   2,  1,
	 1,   4,   5,   3,   0,   3,   5,   4,  1,
	 2,   5,   3, -20, -36, -20,   3,   5,  2,
	 2,   5,   0, -36, -88, -36,   0,   5,  2,
	 2,   5,   3, -20, -36, -20,   3,   5,  2,
	 1,   4,   5,   3,   0,   3,   5,   4,  1,
	 1,   2,   4,   5,   5,   5,   4,   2,  1,
	 0,   1,   1,   2,   2,   2,   1,   1,  0
};

int weights[numFilter] = {9993, -128};

char *inputNames[numInput] = {
	"Images/lake.bmp",
	"Images/maple.bmp",
	"Images/tree.bmp"
};

char *outputNames[numFilter][numInput] = {
	"Output/blurLake.bmp",
	"Output/blurMaple.bmp",
	"Output/blurTree.bmp",
	"Output/sharpLake.bmp",
	"Output/sharpMaple.bmp",
	"Output/sharpTree.bmp"
};

BMP bmpFiles[numInput];
BYTE *data[numInput];
BYTE *results[numFilter][numInput];

void loadImages()
{
	int i;
	
	for(i = 0; i < numInput; i++){
		bmpLoad(&bmpFiles[i], inputNames[i]);
	}

	int size = bmpFiles[0].width * bmpFiles[0].height * 3;

	for(i = 0; i < numInput; i++){
		data[i] = malloc(size * sizeof(BYTE));
		memcpy(data[i], bmpFiles[i].data, size * sizeof(BYTE));
	}
}

void saveImages()
{
	BMP bmpTemp;
	int i, j;

	bmpTemp = bmpFiles[0];

	for(i = 0; i < numFilter; i++){
		for(j = 0; j < numInput; j++){
			bmpTemp.data = results[i][j];	
			bmpSave(&bmpTemp, outputNames[i][j]);
		}
	}
}

void initialResults()
{
	int i, j;
	int size = bmpFiles[0].width * bmpFiles[0].height * 3;

	for(i = 0; i < numFilter; i++)
		for(j = 0; j < numInput; j++)
			results[i][j] = malloc(size * sizeof(BYTE));
}

void freeMem()
{
	int i, j;

	for(i = 0; i < numInput; i++)
		free(data[i]);

	for(i = 0; i < numFilter; i++)
		for(j = 0; j < numInput; j++)
			free(results[i][j]);
}

void checkPixelValue(int *arr, int weight)
{
	int i;

	for(i = 0; i < 3; i++){
		arr[i] = arr[i] / weight;
		if(arr[i] < 0)
			arr[i] = 0;
		else if(arr[i] > 255)
			arr[i] = 255;
	}
}

void cross2DConv()
{
	int i, j, k, l;
	int height, width, weight, kernLen;
	int filIdx, inIdx;
	int acc[3], idx[3];
	Pixel *pixelPtr;

	height = bmpFiles[0].height;
	width = bmpFiles[0].width;
	kernLen = kernSize/2;

	for(filIdx = 0; filIdx < numFilter; filIdx++){
		for(inIdx = 0; inIdx < numInput; inIdx++){
			for(i = 0; i < height; i++){
				for(j = 0; j < width; j++){
					acc[0] = 0; acc[1] = 0; acc[2] = 0;
					weight = weights[filIdx];
					for(k = 0; k < kernSize; k++){
						for(l = 0; l < kernSize; l++){
							idx[1] = j - kernLen + l;
							idx[2] = i - kernLen + k;
							idx[0] = idx[2]*width + idx[1];
							if((idx[1] >= 0) && (idx[2] >=0) && 
								 (idx[1] < width) && (idx[2] < height)){
								pixelPtr = (Pixel *) &data[inIdx][idx[0]*sizeof(Pixel)];
								acc[0] += filters[filIdx][k][l] * (pixelPtr->R - 0);
								acc[1] += filters[filIdx][k][l] * (pixelPtr->G - 0);
								acc[2] += filters[filIdx][k][l] * (pixelPtr->B - 0);
							}
							else
								weight -= filters[filIdx][k][l];
						}
					}		
					checkPixelValue(acc, weight);

					pixelPtr = (Pixel *) &results[filIdx][inIdx][(i*width + j)*sizeof(Pixel)];
					pixelPtr->R = acc[0]; 
					pixelPtr->G = acc[1]; 
					pixelPtr->B = acc[2];
				}
			}
		}
	}
}

int main(int argc, char *argv[]) {
	clock_t clkStart, clkEnd;
	float exeTime;

	clkStart = clock();

	loadImages();
	initialResults();
	cross2DConv();
	saveImages();
	freeMem();

	clkEnd = clock();
	exeTime = (float) (clkEnd - clkStart) / CLOCKS_PER_SEC;

	printf("Execution time: %f\n", exeTime);
  return 0;
}
