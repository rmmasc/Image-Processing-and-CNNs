/*Name: Royston Marian Mascarenhas 
   Submission date: 22nd January, 2019*/
// This sample code reads in image data from a RAW image file and 
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

const int width = 600;
const int height = 400;
const int n = 2;

struct Arrstruct
{
	unsigned char ar[height][width][1];
};

struct Arrstruct2
{
		unsigned char ear[height+(2*n)][width+(2*n)][1];
};

Arrstruct2 ExtendBoundary(Arrstruct imi) 
{
	int eheight, ewidth, BytesPerPixel = 1;
	Arrstruct2 arf;
	int i,j;
	for (i=n;i<height+n;i++)
	{
		for(j=n;j<width+n;j++)
		{
			//cout<<imi.ar[i][j][0];
			arf.ear[i][j][0] = imi.ar[i-2][j-2][0];
		}
	}
	
	cout<<"**********Before boundary**********"<<endl;
	for (i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			//cout<<imi.ar[i][j][0];
			cout<<(int)imi.ar[i][j][0]<<"  ";
		}
		cout<<endl;
	}
	cout<<"**********After boundary**********"<<endl;
	for (i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			//cout<<imi.ar[i][j][0];
			cout<<(int)arf.ear[i][j][0]<<"  ";
		}
		cout<<endl;
	}

	return arf;	

}

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int Size = 256;
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "pro2gram_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			Size = atoi(argv[4]);
		}
	}
	
	// Allocate image data array
	unsigned char Imagedata[height][width][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(Imagedata, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);

	///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
 	int n = 2;
 	unsigned char b;
	int err;
	unsigned char imageout [height][width][BytesPerPixel];
	 	cout<<"11";
	short Imagedata1 [height+(2*n)][width+(2*n)][BytesPerPixel];
	//unsigned char imageout1 [height][width][BytesPerPixel];
	Arrstruct2 arr2;
 	int i,j,k,l;
 	float floydM1[9] = {0,0,0,0,0,7/16.0,3/16.0,5/16.0,1/16.0};
 	float floydM2[9] = {0,0,0,7/16.0,0,0,1/16.0,5/16.0,3/16.0};
 	float *floydp1 = floydM1;
 	float *floydp2 = floydM2;

 	/*for (i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			//cout<<imi.ar[i][j][0];
			cout<<floydM1[i][j]<<"  ";
		}
		cout<<endl;
	}*/
 	
 	
 	Arrstruct arr1;
 	cout<<"****************Imagedata"<<endl;
	for (i=390;i<400;i++)
	{
		for(j=590;j<600;j++)
		{
			//cout<<imi.ar[i][j][0];
			cout<<(int)Imagedata[i][j][0]<<"  ";
		}
		cout<<endl;
	}
	//cout<<"dfdd";
 	for (i=0;i<height;i++)
 	{
 		for(j=0;j<width;j++)
 		{
 			arr1.ar[i][j][0] = Imagedata[i][j][0];
		}
	}
	//cout<<"dfd1";
	//extend image boundaries. The padding of rows on any side is modified by changing the global 'n' parameter at the top
	arr2 = ExtendBoundary(arr1);
	//cout<<"dfd";
	for (i=n;i<height+n;i++)
 	{
 		for(j=n;j<width+n;j++)
 		{
 			Imagedata1[i][j][0] = (short)arr2.ear[i][j][0];
		}
	}

	//**************************************IMPLEMENTATION OF FLOYD STEINBERG**************************************************************
	//roster scan
	/*for (i=n;i<height+n;i++)
 	{
 		for(j=n;j<width+n;j++)
 		{
 			int fij = (int(arr2.ear[i][j][0]));
 			if(fij>127)
 			{
 				b = 255;
			}
			else
			{
				b = 0;
			}
			arr2.ear[i][j][0] = b;
			err = fij - b;
			//*floydp = floydM1[0];
			for (k=i-1;k<=i+1;k++)
			{
				for(l=j-1;l<=j+1;l++)
				{
					arr2.ear[k][l][0] = (unsigned char)(int)(int(arr2.ear[k][l][0]) + ((*floydp1) * err));
					floydp1++;
				}
			}
			floydp1 = floydp1 - 9;	
		}
	}*/
	
	for (i=n;i<height+n;i++)
 	{
 		cout<<"df";
 		if (i%2==0)
 		{
	 		for(j=n;j<width+n;j++)
	 		{
	 			//cout<<"1";
	 			short fij = Imagedata1[i][j][0];
	 			if(fij>127)
	 			{
	 				b = (unsigned char)255;
				}
				else
				{
					b = (unsigned char)0;
				}
				Imagedata1[i][j][0] = (short)b;
				//imageout1[i][j][0] = b;
				err = fij - b;
				//*floydp = floydM1[0];
				for (k=i-1;k<=i+1;k++)
				{
					for(l=j-1;l<=j+1;l++)
					{
						Imagedata1[k][l][0] = Imagedata1[k][l][0]  + short(((*floydp1) * err)+0.5);
						floydp1++;
					}
				}
				floydp1 = floydp1 - 9;	
			}
		}
		if (i%2!=0)
		{
			for(j=width+n-1;j>=n;j--)
	 		{
	 			//cout<<"2";
	 			short fij = Imagedata1[i][j][0];
	 			if(fij>127)
	 			{
	 				b = (unsigned char)255;
				}
				else
				{
					b = (unsigned char)0;
				}
				Imagedata1[i][j][0] = (short)b;
				//imageout1[i][j][0] = b;
				err = fij - b;
				//*floydp = floydM1[0];
				for (k=i-1;k<=i+1;k++)
				{
					for(l=j-1;l<=j+1;l++)
					{
						Imagedata1[k][l][0] = Imagedata1[k][l][0]  + short(((*floydp2) * err)+0.5);
						floydp2++;
					}
				}
				floydp2 = floydp2 - 9;	
			}			
		}
	}
	
	
	//**********************crop to the output image size (remove boundary extensions)***************************
	for (i=n;i<height+n;i++)
 	{
 		for(j=n;j<width+n;j++)
 		{
 			imageout[i-2][j-2][0] = (unsigned char)Imagedata1[i][j][0];
		}
	}
	//***********************************************************************************************************
	
	cout<<"END****************"<<endl;
	/*for (i=394;i<404;i++)
	{
		for(j=594;j<604;j++)
		{
			//cout<<imi.ar[i][j][0];
			cout<<(int)arr2.ear[i][j][0]<<"  ";
		}
		cout<<endl;
	}*/
	for (i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			//cout<<imi.ar[i][j][0];
			cout<<(int)imageout[i][j][0]<<"  ";
		}
		cout<<endl;
	}
	cout<<"adf";
	int count = 0;
	for (i=2;i<height;i++)
 	{
 		for(j=2;j<width;j++)
 		{
 			if ((int(imageout[i][j][0])!=0) and (int(imageout[i][j][0])!=255))
 			{
 				//cout<<"HEY WRONG!!!!";
 				count++;
			 }
		}
	}
	cout<<endl<<"count "<<count;
	cout<<endl<<height<<"  "<<width<<"  "<<BytesPerPixel<<"  "<<n<<"  ";
	// Write image data (filename specified by second argument) from image data matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(imageout, sizeof(unsigned char), height*width*BytesPerPixel, file);
	fclose(file);


	return 0;
}


