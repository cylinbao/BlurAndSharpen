#include "bmp.h"

#define kern_size 9

int filters[2][9][9] = {                                                    
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

int max_weight[2] = {9993, -128};

void conv(BMP *bmp, BMP *blurbmp, int filter)
{
	int i, j, k, l, weight;
	int acc[3], idx[3];
	int kern_len = kern_size/2;
	Pixel *pixel;

	for(i = 0; i < bmp->height; i++){
		for(j = 0; j < bmp->width; j++){
			acc[0] = 0; acc[1] = 0; acc[2] = 0;
			weight = max_weight[filter];
      for(k = 0; k < kern_size; k++){                                          
        for(l = 0; l < kern_size; l++){                                        
          idx[1] = j - kern_len + l;                                             
          idx[2] = i - kern_len + k;                                             
					idx[0] = idx[2]*bmp->width + idx[1];
          if((idx[1] >= 0) && (idx[2] >=0) && 
						(idx[1] < bmp->width) && (idx[2] < bmp->height)){
            pixel = (Pixel *) &bmp->data[idx[0]*sizeof(Pixel)];
						acc[0] += filters[filter][k][l] * (pixel->R - 0);
						acc[1] += filters[filter][k][l] * (pixel->G - 0);
						acc[2] += filters[filter][k][l] * (pixel->B - 0);
					}
					else
						weight -= filters[filter][k][l];
        }                                                                        
      }		
			pixel = (Pixel *) &blurbmp->data[(i*blurbmp->width + j)*sizeof(Pixel)];
			acc[0] = acc[0]/weight;
			acc[1] = acc[1]/weight;
			acc[2] = acc[2]/weight;
			if(acc[0] < 0)
				acc[0] = 0;
			else if(acc[0] > 255)
				acc[0] = 255;
			if(acc[1] < 0)
				acc[1] = 0;
			else if(acc[1] > 255)
				acc[1] = 255;
			if(acc[2] < 0)
				acc[2] = 0;
			else if(acc[2] > 255)
				acc[2] = 255;
			pixel->R = acc[0];
			pixel->G = acc[1];
			pixel->B = acc[2];
		}
	}
}

int main(int argc, char *argv[]) {
		char *input[3] = {
			"Images/lake.bmp",
			"Images/maple.bmp",
			"Images/tree.bmp"
		};
		char *output[2][3] = {
			"Output/lake_b.bmp",
			"Output/maple_b.bmp",
			"Output/tree_b.bmp",

			"Output/lake_s.bmp",
			"Output/maple_s.bmp",
			"Output/tree_s.bmp"
		};

		BMP bmp, blurbmp;
		int i, j;

		for(i = 0; i < 3; i++) {
			for(j = 0; j < 2; j++) {
				bmpLoad(&bmp, input[i]);
				blurbmp = bmp;
				conv(&bmp, &blurbmp, j);
				bmpSave(&blurbmp, output[j][i]);
			}
		}

    return 0;
}
