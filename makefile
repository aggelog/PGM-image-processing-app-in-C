all:
	gcc -o aout main.c Image.c ImageEdit.c

Image.o: Image.c Image.h
	gcc -c Image.c
ImageEdit.o: ImageEdit.c ImageEdit.h
	gcc -c ImageEdit.c
clean:
	rm -rf *.o *.c~ *.h~ *.h.gch aout makefile~
