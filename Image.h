#ifndef IMAGE_
#define IMAGE_
#include <stdio.h>	/* printf, scanf, ... */
#include <stdlib.h>	/* malloc, free, ... */

typedef struct image_{
	int **pixels;
	int width;
	int height;
	int numelems;
}IMAGE;

IMAGE *ReadImage(char *filename);
void WriteImage(IMAGE *image, char *filename);

#endif
