
double getBest(int dim, ftnInput * input, int index, double *bestSolution);
double randWalk(ftnInput * input);
void localSearch(ftnInput *input, int trials);
double bestNeighbor(ftnInput *input, int dim, int index, double *xVect, double xResult);
void itrLocSearch(ftnInput *input);