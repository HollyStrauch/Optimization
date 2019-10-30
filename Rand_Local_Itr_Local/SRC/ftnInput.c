#include <stdio.h>
#include <stdlib.h>
#include "ftnInput.h"

/*! \brief Initializes the struct ftnInput with data read from a file.  Data is
            dynamically allocated.

	\param *filename the name of the file being read in from

	\return pointer to initialized struct.
*/
ftnInput *getInput(const char *filename){
	ftnInput *in = (ftnInput *)calloc(1, sizeof(ftnInput));
	FILE *fp;
	int i;

    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr, "No such file: getInput\n");
        exit(-1);
    }

    //scan for how many trials and dimensions
    fscanf(fp, "%d", &in->itr);
	fscanf(fp, "%d", &in->trials);
    fscanf(fp, "%d", &in->numDim);

    //create array for dimensions and scan in
	in->dimensions = (int *)calloc(in->numDim, sizeof(int));
		if (in->dimensions == NULL){
			fprintf(stderr, "Out of memory: ftnInput dimensions\n");
		}
	for (i = 0; i <in->numDim; i++){
		fscanf(fp, "%d", &in->dimensions[i]);
	}

    //scan in number of functions
	fscanf(fp, "%d", &in->numFtns);

    //create array and scan in functions and their bounds
	in->ftnBounds = (double *)calloc(in->numFtns * 4, sizeof(double));
		if (in->ftnBounds == NULL){
			fprintf(stderr, "Out of memory: ftnInput ftnBounds\n");
		}

	for (i = 0; i < (in->numFtns * 4); i++){
		fscanf(fp, "%lf", &in->ftnBounds[i]);
	}

	fclose(fp);
	return in;
}
