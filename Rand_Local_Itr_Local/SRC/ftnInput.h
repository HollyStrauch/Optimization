typedef struct _ftnInput {
	int itr;
	int trials;
	int numDim;
	int *dimensions;
	int numFtns;
	double *ftnBounds;
} ftnInput;

ftnInput *getInput(const char *filename);
