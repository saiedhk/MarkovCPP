// Program to demo and test MarkovChain class
#include "../shk_randgen/shk_randgen.h"
#include "shk_markov.h"

#include <iostream>
using namespace std;
using namespace shk;

const int N = 3, M = 10000;
RandGen randgen;  // we need a random generator

int main()
{
    float** A = new float*[N];
    for (int k = 0; k<N; k++)
        A[k] = new float[N];

    A[0][0] = 0.2f;
    A[0][1] = 0.7f;
    A[0][2] = 0.1f;
    A[1][0] = 0.6f;
    A[1][1] = 0.3f;
    A[1][2] = 0.1f;
    A[2][0] = 0.25f;
    A[2][1] = 0.10f;
    A[2][2] = 0.65f;

    MarkovChain markov(N, A, 0, &randgen);

    for (int i=0; i<M; i++)
    {
        cout << markov.getNextState() << "\n";
    }

    return 0;

}



