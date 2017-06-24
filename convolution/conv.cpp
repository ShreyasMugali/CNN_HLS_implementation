// matrix dot product and summation
#include "conv.h"
//
#include <stdio.h>
//
/*void conv(data_t (&a)[11][11], data_t (&b)[11][11], data_t* c)
{
	data_t sum = 0;
//	data_t temp[11];
	for(int i=0; i<11; i++)
	{
		//temp[i]=0;
		for(int j=0; j<11; j++)
		{
			//temp[i]=temp[i]+*a[i][j]*b[i][j];
			sum += a[i][j] * b[i][j];
			//sum += (*(a+11*i+j)) * (*(b+11*i+j));
		}
	}
	*c = sum;
}*/

// Convolve the whole image to generate output feature map
void conv_layer1(data_t (&conv1)[55][55][96], data_t (&image)[227][227][3], data_t (&convKernels)[11][11][3][96],
		data_t (&bias)[1][1][1][96], data_t CONV_KERNEL_LENGTH, data_t CONV_STRIDE)
{
	int M=96;
	int Wout=55, Hout=55, wStart, hStart;

	//int conv1[55][55][96]=0;
	// for each output featuremap, for each output pixel in that Fmap compute
	// Lets say each output feature map is of size Wout X Hout
	for(int w=0; w<Wout; w++){
		for(int h=0; h<Hout; h++){
			wStart=w*CONV_STRIDE;
			//wEnd=wStart+CONV_KERNEL_LENGTH-1;
			hStart=h*CONV_STRIDE;
            //hEnd=hStart+CONV_KERNEL_LENGTH-1;
			// Now for each of the output feature map ( total o/p feature maps=M)
			for(int m=0; m<M; m++){
				conv1[w][h][m]=mult_acc(image, wStart, hStart, CONV_KERNEL_LENGTH,convKernels, m );
			}
		}
	}
}
// Convolves weights and input feature maps for the given point in output Feature map
data_t mult_acc (data_t (&image)[227][227][3],data_t wStart, data_t hStart, data_t CONV_KERNEL_LENGTH, data_t (&convKernels)[11][11][3][96], int m )
{
	data_t sum=0;
	int i,j;
	for(int n=0;n<3;n++)
    {
        i=0;j=0;
        // interchanging hStart wStart loops should give same result, take care of i,j incrementing accordingly
        for(int w=wStart; w<wStart+CONV_KERNEL_LENGTH; w++)
        {
            for(int h=hStart; h<hStart+CONV_KERNEL_LENGTH; h++)
            {
       //         printf("element of O/P FM at = %f \n",convKernels[i][j][n][m]);
                sum += image[w][h][n]*convKernels[i][j][n][m];
                j=j+1;
            }
            i=i+1;
 //       printf("element of O/P FM at = %f \n",sum);
        }
//        printf("element of O/P FM at = %f \n",sum);

    }


	return sum;
}
