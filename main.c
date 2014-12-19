#include <stdio.h>	/* printf, scanf, NULL */
#include <stdlib.h>	/* malloc, free, rand */
#include "ImageEdit.h"

int main()
{
	IMAGE *image,*image1,*image2,*image3,*image4,*image5,*image6,*image7,*image8;
	IMAGE *imageBonusFinal,*imageBonusA,*imageBonusB,*imageBonusC,*imageBonusD,*imageBonusE,*imageBonusF;

	image = ReadImage("casablanca.ascii.pgm");
	//image = ReadImage("x31_f18.ascii.pgm");
	image1 = ReadImage("x31_f18.ascii.pgm");
	//image1 = ReadImage("fractal_tree.ascii.pgm");

	WriteImage(image,"test_out_1.pgm");
	image2 = RotateRight(image);
	WriteImage(image2, "test_out_1_rotate_right.pgm");
	image3 = RotateLeft(image);
	WriteImage(image3, "test_out_1_rotate_left.pgm");

	image4 = FlipHorizontal(image);
	WriteImage(image4, "test_out_1_flip_horizontal.pgm");
	image5 = FlipVertical(image);
	WriteImage(image5, "test_out_1_flip_vertical.pgm");

	image6 = Negative(image);
	WriteImage(image6, "test_out_1_negative.pgm");

	image7 = MergeHorizontal(image,image1);
	WriteImage(image7, "test_out_1_merge_horizontal.pgm");
	image8 = MergeVertical(image, image1);
	WriteImage(image8, "test_out_1_merge_vertical.pgm");


	/* **************************************************** */
	/* ******************** BONUS PART ******************** */
	/* **************************************************** */

	imageBonusA = RotateRight(image);
	imageBonusB = FlipVertical(image);
	imageBonusC = Negative(imageBonusB);
	imageBonusD = Negative(image1);
	imageBonusE = MergeVertical(image1,imageBonusC);
	imageBonusF = MergeHorizontal(imageBonusA,imageBonusE);
	imageBonusFinal = MergeVertical(imageBonusF,imageBonusD);
	WriteImage(imageBonusFinal, "test_out_1_BONUS.pgm");

	
	free(image);
	free(image1);
	free(image2);
	free(image3);
	free(image4);
	free(image5);
	free(image6);
	free(image7);
	free(image8);

	free(imageBonusA);
	free(imageBonusB);
	free(imageBonusC);
	free(imageBonusD);
	free(imageBonusE);
	free(imageBonusF);
	free(imageBonusFinal);

	return 0;
}
