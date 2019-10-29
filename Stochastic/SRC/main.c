#include <stdio.h>
#include <stdlib.h>
#include "run.h"

#define FILEIN "input.txt"
#define FILEOUT "output.csv"

/*! \brief Opens the output file and starts run();
*/
int main()
{

    FILE *op = fopen(FILEOUT, "w");

	run(FILEIN, op);

	fclose(op);

	return 0;
}
