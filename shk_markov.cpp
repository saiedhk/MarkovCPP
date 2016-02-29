/**********************************************************************
   Project: C++ Class for Finite Markov Chain

   Language: C++ 2007	   
   Author: Saied H. Khayat
   Date:   Nov 2014
   URL: https://github.com/saiedhk/MarkovCPP
   
   Copyright Notice: Free use of this library is permitted under the
   guidelines and in accordance with the MIT License (MIT).
   http://opensource.org/licenses/MIT

**********************************************************************/

#include <iostream>
#include "shk_markov.h"
using namespace std;

namespace shk
{

// Constructor
MarkovChain::MarkovChain(int nstate,
                        float** transmatrix,
                        int initstate,
                        RandGen* rand)
{
    // Check number of states. It cannot be less than 2.
    if (nstate<2)
    {
        cerr << "fatal error: MarkovChain::MarkovChain(): invalid number of states!\n";
        exit(1);
    }

    // Check initial state. It cannot be <0 or >=nstate.
    if (initstate<0 || initstate>=nstate)
    {
        cerr << "fatal error: MarkovChain::MarkovChain(): invalid init state!\n";
        exit(1);
    }

    // Check transition matrix.
    // Every entry must be >=0 and <=1.
    // Sum of each row must not exceed 1.
    bool error = false;
    for (int i=0; i<nstate; i++)
    {
        float sum = 0.0f;
        for (int j=0; j<nstate; j++)
        {
            if (transmatrix[i][j]<0.0f || transmatrix[i][j]>1.0f) error = true;
            sum += transmatrix[i][j];
        }
        if (sum<0.0f || sum>1.0f) error = true;
    }
    if (error)
    {
        cerr << "fatal error: MarkovChain::MarkovChain(): invalid transition matrix!\n";
        exit(1);
    }

    N = nstate;
    state = initstate;
    randgen = rand;
    matrix = new float*[N] ;
    for (int k=0; k<N; k++)
        matrix[k]= new float[N];
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            matrix[i][j] = transmatrix[i][j];
};


// Destructor
MarkovChain::~MarkovChain()
{
    for (int k=0; k<N; k++) delete[] matrix[k];
    delete[] matrix;
};


// Function to cause state transition to a random next state.
// It return the new state.
int MarkovChain::getNextState(void)
{
    int newstate;
    float y = 0.;
    float x = (float) randgen->rand_double();
    for (int j=0; j<N; j++)
    {
        y += matrix[state][j];
        if (x < y)  { newstate = j;  break; }
        if (j==N-1) { newstate = N-1; }
    }
    state = newstate;
    return state;
};


// resets state of Markov chain to new state
void MarkovChain::resetState(int newstate)
{
    if (newstate<0 || newstate>=N)
    {
        cerr << "fatal error: MarkovChain::resetState(): invalid newstate!\n";
        exit(1);
    }
    state = newstate;
};


} // namespace shk
