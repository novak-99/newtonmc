#include <iostream>
#include <vector>
#include <random>
#include "MLPP/NumericalAnalysis/NumericalAnalysis.hpp"

using namespace MLPP;

double function(double x){ // function to optimize
    return (x - 20) * (x - 20); 
}

int main(){
    // CONSTANTS
    const unsigned int N = 1e+6;
    const double root = 20; 
    const double margin_of_error = 1e-3;
    const double bet_amt = 10; // 10 USD

    srand(time(NULL)); 

    // TRACKING VARS FOR MEAN & VAR
    double net_gain = 0; // dollar amt lost or won by player
    int win_count = 0; 
    int loss_count = 0; 
    

    NumericalAnalysis numAn; // newton's method 

    for(int i = 0; i < N; i++){
        // Randomly generate x_0 (initial guess)
        double a = (rand()%2 == 0) ? -1000 : 1; 
        //std::cout << a << "\n";

        // Randomly generate k (number of iterations)
        double k = rand() % 20 + 1; 
        //std::cout << k << "\n";

        // perform newton's method 
        double soln = numAn.newtonRaphsonMethod(function, a, k);

        // calculate winnings (or losses)
        if(root - soln <= margin_of_error){ // money quadrupled
            net_gain += 4 * bet_amt; 

            win_count++; 
        } 
        else { // money lost
            net_gain -= bet_amt;  

            loss_count++;
        }

    }

    double mean = double(net_gain) / double(N);
    double var = ( win_count * (40 - mean)*(40 - mean) + loss_count * (-10 - mean) * (-10 - mean) ) / double(N);

    std::cout << "ESTIMATED MEAN:" << "\n";
    std::cout << mean << "\n";

    std::cout << "\n";

    std::cout << "ESTIMATED VAR:" << "\n";
    std::cout << var << "\n";


    return 0; 
}

