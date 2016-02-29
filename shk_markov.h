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

/* USAGE EXAMPLE:

    #include "shk_randgen.h" // Has RandGen class (https://github.com/saiedhk/RandGenCPP)
    #include "markov.h"
    MarkovChain markov(5,A,0,randgen);

        The above call creates a Markov chain called 'markov' with 5 states.
        It starts at initial state = 0.
        It uses randgen object to generate random transitions.
        A is a two dimensional array of type float of size 5x5 which holds transition 
        probabilities and should be filled in advance with the state transition 
        probabilities. A[i][j] is the probability of transition to state j given state i.
        Now you can call getNextState(). This function causes the markov chain to make a
        random transition to a new random state. It returns the new state of the process.

    markov.getNextState();

        Also you can force the state to go to a particular state. 
    
    markov.resetState(5);  // set to state 5
*/

#include "../shk_randgen/shk_randgen.h" // Obtain from https://github.com/saiedhk/RandGenCPP

namespace shk
{

class MarkovChain
{
    public:
        // constructor
        MarkovChain(int nstate, float** transmatrix, int initstate, RandGen* rand);

        // destructor
        ~MarkovChain();

        // function to cause a transition to the next random state
        int getNextState(void);

        // resets state of Markov chain to given new state
        void resetState(int newstate);

    private:
        int N;              // number of states
        int state;          // current state
        float** matrix;     // transition probability matrix
        RandGen* randgen;   // pointer to external RandGen object
};

} // namespace shk
