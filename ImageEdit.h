#ifndef IMAGEEDIT_
#define IMAGEEDIT_
#include <stdio.h>	/* printf, scanf, ... */
#include <stdlib.h>	/* malloc, free, ... */
#include "Image.h"

#define max(a,b) ((a) > (b) ? a : b)
#define min(a,b) ((a) < (b) ? a : b)

IMAGE *RotateRight(IMAGE *image);
IMAGE *RotateLeft(IMAGE *image);

IMAGE *FlipHorizontal(IMAGE *image);
IMAGE *FlipVertical(IMAGE *image);

IMAGE *Negative(IMAGE *image);

IMAGE *MergeHorizontal(IMAGE *image1, IMAGE *image2);
IMAGE *MergeVertical(IMAGE *image1, IMAGE *image2);

#endif
