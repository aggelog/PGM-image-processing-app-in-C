#include "ImageEdit.h"

IMAGE *RotateRight(IMAGE *image)
{
	IMAGE *RotatedRightImage;
	int i, j;

	RotatedRightImage = malloc(sizeof(IMAGE));

	RotatedRightImage->width    = image->height;
	RotatedRightImage->height   = image->width;
	RotatedRightImage->numelems = image->numelems;

	RotatedRightImage->pixels = (int **)malloc(RotatedRightImage->height * sizeof(int *));
	for(i = 0; i < RotatedRightImage->height; i++)
	{
		RotatedRightImage->pixels[i] = (int *)malloc(RotatedRightImage->width * sizeof(int));
	}

	for(i = 0; i < RotatedRightImage->height; i++)
	{
		for(j = 0; j < RotatedRightImage->width; j++)
		{
			RotatedRightImage->pixels[i][j] = image->pixels[RotatedRightImage->width-j-1][i];
		}
	}


	return RotatedRightImage;
}

IMAGE *RotateLeft(IMAGE *image)
{
	IMAGE *RotatedLeftImage;
	int i, j;

	RotatedLeftImage = malloc(sizeof(IMAGE));

	RotatedLeftImage->width    = image->height;
	RotatedLeftImage->height   = image->width;
	RotatedLeftImage->numelems = image->numelems;

	RotatedLeftImage->pixels = (int **)malloc(RotatedLeftImage->height * sizeof(int *));
	for(i = 0; i < RotatedLeftImage->height; i++)
	{
		RotatedLeftImage->pixels[i] = (int *)malloc(RotatedLeftImage->width * sizeof(int));
	}

	for(i = 0; i < RotatedLeftImage->height; i++)
	{
		for(j = 0; j < RotatedLeftImage->width; j++)
		{
			RotatedLeftImage->pixels[i][j] = image->pixels[j][RotatedLeftImage->height-i-1];
		}
	}

	return RotatedLeftImage;
}

IMAGE *FlipHorizontal(IMAGE *image)
{
	IMAGE *FlipedHorizontalImage;
	int i, j;

	FlipedHorizontalImage = malloc(sizeof(IMAGE));

	FlipedHorizontalImage->width    = image->width;
	FlipedHorizontalImage->height   = image->height;
	FlipedHorizontalImage->numelems = image->numelems;

	FlipedHorizontalImage->pixels = (int **)malloc(FlipedHorizontalImage->height * sizeof(int *));
	for(i = 0; i < FlipedHorizontalImage->height; i++)
	{
		FlipedHorizontalImage->pixels[i] = (int *)malloc(FlipedHorizontalImage->width * sizeof(int));
	}

	for(i = 0; i < FlipedHorizontalImage->height; i++)
	{
		for(j = 0; j < FlipedHorizontalImage->width; j++)
		{
			FlipedHorizontalImage->pixels[i][j] = image->pixels[i][FlipedHorizontalImage->width-j-1];
		}
	}

	return FlipedHorizontalImage;
}
IMAGE *FlipVertical(IMAGE *image)
{
	IMAGE *FlipedVerticalImage;
	int i, j;

	FlipedVerticalImage = malloc(sizeof(IMAGE));

	FlipedVerticalImage->width    = image->width;
	FlipedVerticalImage->height   = image->height;
	FlipedVerticalImage->numelems = image->numelems;

	FlipedVerticalImage->pixels = (int **)malloc(FlipedVerticalImage->height * sizeof(int *));
	for(i = 0; i < FlipedVerticalImage->height; i++)
	{
		FlipedVerticalImage->pixels[i] = (int *)malloc(FlipedVerticalImage->width * sizeof(int));
	}

	for(i = 0; i < FlipedVerticalImage->height; i++)
	{
		for(j = 0; j < FlipedVerticalImage->width; j++)
		{
			FlipedVerticalImage->pixels[i][j] = image->pixels[FlipedVerticalImage->height-i-1][j];
		}
	}

	return FlipedVerticalImage;
}

IMAGE *Negative(IMAGE *image)
{
	IMAGE *NegativeImage;
	int i, j;

	NegativeImage = malloc(sizeof(IMAGE));

	NegativeImage->width    = image->width;
	NegativeImage->height   = image->height;
	NegativeImage->numelems = image->numelems;

	NegativeImage->pixels = (int **)malloc(NegativeImage->height * sizeof(int *));
	for(i = 0; i < NegativeImage->height; i++)
	{
		NegativeImage->pixels[i] = (int *)malloc(NegativeImage->width * sizeof(int));
	}

	for(i = 0; i < image->height; i++)
	{
		for(j = 0; j < image->width; j++)
		{
			NegativeImage->pixels[i][j] = 255 - image->pixels[i][j];
		}
	}

	return NegativeImage;
}

IMAGE *MergeHorizontal(IMAGE *image1, IMAGE *image2)
{
	IMAGE *MergedHorizontalImage;
	int i, j, z = 0, w = 0, c = 0;
	int flagRaise = 0;

	MergedHorizontalImage = malloc(sizeof(IMAGE));


	if(image1->height == image2->height)
	{
		MergedHorizontalImage->width    = image1->width + image2->width;
		MergedHorizontalImage->height   = image1->height;
		MergedHorizontalImage->numelems = MergedHorizontalImage->width * MergedHorizontalImage->height;
	}
	else
	{
		MergedHorizontalImage->width    = image1->width + image2->width;
		MergedHorizontalImage->height   = max(image1->height,image2->height);
		MergedHorizontalImage->numelems = MergedHorizontalImage->width * MergedHorizontalImage->height;
	}

	MergedHorizontalImage->pixels = (int **)malloc(MergedHorizontalImage->height * sizeof(int *));
	for(i = 0; i < MergedHorizontalImage->height; i++)
	{
		MergedHorizontalImage->pixels[i] = (int *)malloc(MergedHorizontalImage->width * sizeof(int));
	}

	for(i = 0; i < MergedHorizontalImage->height; i++)
	{
		z=0;
		c=0;
		for(j = 0; j < MergedHorizontalImage->width; j++)
		{
			if(z < image1->width && (image1->height >= image2->height) )
			{
				MergedHorizontalImage->pixels[i][j] = image1->pixels[i][z];
				z++;
			}
			else if((z >= image1->width) && (i >= (image1->height - image2->height)) && (image1->height >= image2->height) )
			{
				MergedHorizontalImage->pixels[i][j] = image2->pixels[w][c];
				c++;
				flagRaise = 1;
			}
			else if ((z >= image1->width) && (i < (image1->height - image2->height)) && (image1->height >= image2->height))
			{
				MergedHorizontalImage->pixels[i][j] = 0;
			}
			else if((i >= (image2->height - image1->height)) && (c < image1->width) && (image2->height > image1->height))
			{
				MergedHorizontalImage->pixels[i][j] = image1->pixels[w][c];
				c++;
				flagRaise = 1;
			}
			else if((j >= image1->width) && (image2->height > image1->height))
			{
				MergedHorizontalImage->pixels[i][j] = image2->pixels[i][z];
				z++;
			}
			else if((i < (image2->height - image1->height)) && (image2->height > image1->height))
			{
				MergedHorizontalImage->pixels[i][j] = 0;
			} 
		}
		if(flagRaise == 1)
		{
			w++;
			flagRaise = 0;
		}
	}

	return MergedHorizontalImage;
}

IMAGE *MergeVertical(IMAGE *image1, IMAGE *image2)
{
	IMAGE *MergedVerticalImage;
	int i, j, z = 0, w = 0, c = 0;
	int flagRaise = 0;

	MergedVerticalImage = malloc(sizeof(IMAGE));

	if(image1->width == image2->width)
	{
		MergedVerticalImage->width    = image1->width;
		MergedVerticalImage->height   = image1->height + image2->height;
		MergedVerticalImage->numelems = MergedVerticalImage->width * MergedVerticalImage->height;
	}
	else
	{
		MergedVerticalImage->width    = max(image1->width,image2->width);
		MergedVerticalImage->height   = image1->height + image2->height;max(image1->height,image2->height);
		MergedVerticalImage->numelems = MergedVerticalImage->width * MergedVerticalImage->height;
	}

	MergedVerticalImage->pixels = (int **)malloc(MergedVerticalImage->height * sizeof(int *));
	for(i = 0; i < MergedVerticalImage->height; i++)
	{
		MergedVerticalImage->pixels[i] = (int *)malloc(MergedVerticalImage->width * sizeof(int));
	}

	for(i = 0; i < MergedVerticalImage->height; i++)
	{
		z=0;
		c=0;
		for(j = 0; j < MergedVerticalImage->width; j++)
		{
			if((i < image1->height) && (image1->width >= image2->width))
			{
				MergedVerticalImage->pixels[i][j] = image1->pixels[i][j];
			}
			else if((i >= image1->height) && (z < image2->width) && (image1->width >= image2->width))
			{
				MergedVerticalImage->pixels[i][j] = image2->pixels[w][z];
				z++;
				flagRaise = 1;
			}
			else if((i >= image1->height) && (z >= image2->width) && (image1->width >= image2->width))
			{
				MergedVerticalImage->pixels[i][j] = 0;
			}
			else if((i < image1->height) && (j < image1->width) && (image1->width < image2->width))
			{
				MergedVerticalImage->pixels[i][j] = image1->pixels[i][j];
			}
			else if((i >= image1->height) && (image1->width < image2->width))
			{
				MergedVerticalImage->pixels[i][j] = image2->pixels[w][z];
				z++;
				flagRaise = 1;
			}
			else if((j >= image1->width) && (i <= image1->height) && (image1->width < image2->width))
			{
				MergedVerticalImage->pixels[i][j] = 0;
			}
		}
		if(flagRaise == 1)
		{
			w++;
			flagRaise = 0;
		}
	}

	return MergedVerticalImage;
}
