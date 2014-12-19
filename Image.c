#include "Image.h"

IMAGE *ReadImage(char *filename)
{
	FILE *fp;
	char c;
	int flagFormat = 0,flagWidth = 0,flagHeight = 0,flagMAXvalue = 0;
	char *width = NULL,*height = NULL,*MaxValue = NULL,*pixelValue = NULL;
	IMAGE *input;
	int count = 0,countRow = 0,countCol = 0;
	int i,j;

	if((fp = fopen((const char*)filename,"r")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}

	while((c = fgetc(fp)) != EOF)
	{
		if( c == '\n' || c == '\r' || c == ' ')
		{
			continue;
		}
		/* ***************************************************************** */
		/* Read and Import to struct the Width and Height of the given Image */
		/* ***************************************************************** */
		if(flagFormat == 1 && flagWidth == 0 && flagHeight == 0)
		{
			
			while(isdigit(c))
			{
				count++;
				width = realloc(width,(count*sizeof(char))+1);
				width[count-1] = c;
				width[count] = '\0';
				c= fgetc(fp);
				continue;
			}
			if( c == ' ' && flagWidth == 0)
			{
				if(width == NULL)
				{
					printf("This file format is not supported\n");
					exit(1);
				}
			
				input = malloc(sizeof(IMAGE));
				input->width = atoi(width);
				flagWidth = 1;
				free(width);
				count = 0;
				continue;
			}
		}
		else if(flagFormat == 1 && flagWidth == 1 && flagHeight == 0)
		{
			while(isdigit(c))
			{
				count++;
				height = realloc(height,(count*sizeof(char))+1);
				height[count-1] = c;
				height[count] = '\0';
				c = fgetc(fp);
				continue;
			}

			if(height == NULL)
			{
				printf("This file format is not supported\n");
				exit(1);
			}

			input->height = atoi(height);
			flagHeight = 1;
			free(height);
			count = 0;


			/* ************************************************************** */
			/* Allocate space for the 2d array in struct for the pixel values */
			/* ************************************************************** */

			input->pixels = (int **)malloc(input->height * sizeof(int *));
			for(i = 0; i < input->width; i++)
			{
				input->pixels[i] = (int *)malloc(input->width * sizeof(int));
			}

			input->numelems = input->width * input->height;			

			continue;
		}

		if( c == '#')
		{
			while( (c != '\n') && (c != '\r') )
			{
				c=fgetc(fp);
				continue;
			}
			continue;
		}
		/* ********************************************************************** */
		/* Read and check the Maximum Value of grey of the given Image ********** */
		/* ********************************************************************** */
		if(flagFormat == 1 && flagWidth == 1 && flagHeight == 1 && flagMAXvalue == 0)
		{
			while(isdigit(c))
			{
				count++;
				MaxValue = realloc(MaxValue,(count*sizeof(char))+1);
				MaxValue[count-1] = c;
				MaxValue[count] = '\0';
				c = fgetc(fp);
				continue;
			}

			if(MaxValue == NULL)
			{
				printf("This file format is not supported\n");
				exit(1);
			}
			
			if((atoi(MaxValue)) != 255)
			{
				printf("The application works only for 255 maximum value of grey.\n");
				exit(1);
			}

			flagMAXvalue = 1;
			free(MaxValue);
			count = 0;
			continue;
		}
		/* ******************************************************* */
		/* Read and Import to struct the pixels of the given Image */
		/* ******************************************************* */
		if(flagMAXvalue == 1)
		{
			while(isdigit(c))
			{
				count++;
				pixelValue = realloc(pixelValue,(count*sizeof(char))+1);
				pixelValue[count-1] = c;
				pixelValue[count] = '\0';
				c = fgetc(fp);
				continue;
			}

			if(pixelValue == NULL)
			{
				printf("This file format is not supported\n");
				exit(1);
			}
			
			
			if(countCol < input->width)
			{
				input->pixels[countRow][countCol] = atoi(pixelValue);
				count = 0;
				countCol++;
			}
			else
			{
				countCol = 0;
				countRow++;
				input->pixels[countRow][countCol] = atoi(pixelValue);
				countCol++;
				count = 0;
			}
			
			continue;
		}

		if(c == 'P' && (c=fgetc(fp)) == '2' && flagFormat == 0)
		{
			flagFormat = 1;
			continue;
		}
		else
		{
			printf("This file format is not supported\n");
			exit(1);
		}
	}

	fclose(fp);
	return input;
}

void WriteImage(IMAGE *image, char *filename)
{
	FILE *fp;
	int i,j,cntLine = 0;

	if((fp = fopen((const char*)filename,"w")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}

	fputs("P2\n",fp);
	fprintf(fp,"%d %d\n",image->width,image->height);
	fprintf(fp,"%d\n",255);

	for(i =0;i<image->height;i++)
	{
		for(j=0;j<image->width;j++)
		{
			if(image->pixels[i][j] < 10)
			{
				if(cntLine != 0)
				{
					fprintf(fp,"   ");
				}
				else
				{
					fprintf(fp,"  ");
				}
			}
			else if(image->pixels[i][j] >= 10 && image->pixels[i][j] < 100)
			{
				if(cntLine != 0)
				{
					fprintf(fp,"  ");
				}
				else
				{
					fprintf(fp," ");
				}
			}
			else
			{
				if(cntLine != 0)
				{
					fprintf(fp," ");
				}
			}
			fprintf(fp,"%d",image->pixels[i][j]);
			cntLine++;
			
			if(cntLine == 17){
				fprintf(fp," \n");
				cntLine = 0;
			}
		}
	}

	fclose(fp);
}
