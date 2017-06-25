#include <stdio.h>
#include <stdlib.h>
#include "conv.h"
// for random matrix generation
#include <iostream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
// To read data array
#include <fstream>
#include <sstream>
//
using namespace std;
void readToArray();
data_t data[33][1056];
data_t biasData[1][1][1][96];
data_t Conv1Kernel[11][11][3][96];
data_t pool1[27][27][96];
data_t image[227][227][3];
int main()
{
	data_t  conv1[55][55][96];
	// Read data from .dat files generated in matlab to an array
	// Image data is all ones now. In matlab I will give similar input image and get the results
	readToArray();
	std::cout << "Length of array = " << (sizeof(image)/sizeof(*image)) << std::endl;
//  conv(a,b,&c);
	conv_layer1(conv1, image, Conv1Kernel, biasData, 11, 4);

    max_pool(pool1, conv1, MAX_POOL_WIN1, MAX_POOL_STRIDE1);
    relu(data_t (&conv)[55][55][96], data_t (&relu)[55][55][96], data_t CONV_FMAP_WIDTH, data_t CONV_FMAPS );
    max_pool(data_t (&conv)[55][55][96], data_t FMAP_WIDTH, data_t FMAPS, data_t MAX_POOL_KERNEL_SIZE, data_t MAX_POOL_STRIDE);
/*
	for (int i = 0; i < 55; i++)
	{
		for (int j = 0; j < 55; j++)
		{
			for (int k = 0; k < 96; k++)
                printf("element of O/P FM at = %f \n",conv1[i][j][k]);
		}
	}
	*/
    printf("********************END***********************");
	//FMap1=conv_layer1(image,convKernels1,Bias);
return 0;
}


/// read data
void readToArray()
{	// reading kernel weights
	std::ifstream file("D:\\venky\\workdir\\designs\\convolution\\data\\conv1KernelWeights.dat");
	//std::ifstream file("/home/gunman/Downloads/summer17/alexnet/conv1KernelWeights.dat");
	//git/CNN_HLS_implementation/convolution/data/conv1kernels.dat");
	//("D:\\venky\\workdir\\designs\\convolution\\data\\conv1kernels.dat");
    int dim=3; // 3 kerners, one for each RGB
	for (int row = 0; row < 11*dim; ++row)
	{
		std::string line;
		std::getline(file, line);
		if (!file.good())
			break;
		std::stringstream iss(line);
		for (int col = 0; col < 1056; ++col)
		{
			std::string val;
			std::getline(iss, val, ',');

			std::stringstream convertor(val);
			convertor >> data[row][col];//data[dim][row][col];
		}
	}

//	file.close();
	// reading bias
/*	std::ifstream file1("/home/gunman/Downloads/summer17/alexnet/git/CNN_HLS_implementation/convolution/data/conv1Bias.dat");
	//("D:\\venky\\workdir\\designs\\convolution\\data\\conv1Bias.dat");
	for (int row = 0; row < 96; ++row)
	{
		std::string line;
		std::getline(file1, line);
		if (!file1.good())
			break;
		std::stringstream iss(line);
		iss >> biasData[1][1][1][row];
	}
*/
	for(int row = 0; row < 96; ++row)
	{
	biasData[1][1][1][row]=0;
	}

// converting kernel weights to proper Array Format
// Restructures array to make to easily usable with indexing
// we need weights in array of size 11 X 11 X 3 X 96 from 33 X 1056 format
for(int m=0; m<96; m++){
	for (int dim = 0; dim < 3; dim++)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				Conv1Kernel[i][j][dim][m] = data[i+(11*dim)][j+(11*m)];//[dim*i*11 + j][k];
//				printf("element of array at = %f \n",Conv1Kernel[i][j][dim][m]);
			}
		}
	}
	}
// making a dummy image all ones
	for (int i = 0; i < 227; i++)
	{
		for (int j = 0; j < 227; j++)
		{
			for (int k = 0; k < 3; k++)
            {
                image[i][j][k]=1;
     //           printf("element of O/P FM at = %f \n",image[i][j][k]);
            }
		}
	}
}
