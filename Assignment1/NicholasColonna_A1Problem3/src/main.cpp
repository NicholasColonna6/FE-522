/*
 * Nicholas Colonna
 * FE 522
 * Assignment 1
 * Problem 3
 */

#include "std_lib_facilities.h"

//calculates mean for an array of doubles
double calculateMean(double array[]){
    double sum = 0;
    for(int i=0; i<1000; i++){
        sum += array[i];
    }
    return sum / 1000;
}

//calculates stdev for an array of doubles
double calculateStdev(double array[], double mean){
    double stdev = 0;
    for(int i=0; i<1000; i++){
        stdev += pow(array[i] - mean, 2);
    }
    stdev = sqrt(stdev / 1000);
    return stdev;
}

int main()
{
    int num_obs = 1000;
    default_random_engine generator;

    //Distribution 1: Uniform
    uniform_real_distribution<double> uniform(0, 10);
    double uniform_dist[1000];
    for(int i=0; i<num_obs; i++){
        uniform_dist[i] = uniform(generator);
    }

    //Distribution 2: Bernoulli Binomial
    binomial_distribution<int> binomial(10, 0.5);
    double binomial_dist[1000];
    for(int i=0; i<num_obs; i++){
        binomial_dist[i] = binomial(generator);
    }

    //Distribution 3: Poisson Exponential
    exponential_distribution<double> exponential(5);
    double exponential_dist[1000];
    for(int i=0; i<num_obs; i++){
        exponential_dist[i] = exponential(generator);
    }

    //Distribution 4: Normal
    normal_distribution<double> normal(5, 2);
    double normal_dist[1000];
    for(int i=0; i<num_obs; i++){
        normal_dist[i] = normal(generator);
    }

    //Distribution 5: Bernoulli Geometric
    geometric_distribution<int> geometric(0.40);
    double geometric_dist[1000];
    for(int i=0; i<num_obs; i++){
        geometric_dist[i] = geometric(generator);
    }

    //Calculate means
    double u_mean = calculateMean(uniform_dist);
    double b_mean = calculateMean(binomial_dist);
    double e_mean = calculateMean(exponential_dist);
    double n_mean = calculateMean(normal_dist);
    double g_mean = calculateMean(geometric_dist);

    //calculate standard deviations
    double u_stdev = calculateStdev(uniform_dist, u_mean);
    double b_stdev = calculateStdev(binomial_dist, b_mean);
    double e_stdev = calculateStdev(exponential_dist, e_mean);
    double n_stdev = calculateStdev(normal_dist, n_mean);
    double g_stdev = calculateStdev(geometric_dist, g_mean);


    //create output text file and creates table
    ofstream outputFile;
    outputFile.open("../../output/randomResults.txt", ios::out);
    outputFile << "Distribution\t\tMean\t\t\tStandard Deviation\n";
    outputFile << "--------------------------------------------------------\n";
    outputFile << "Uniform\t\t\t" << u_mean << "\t\t" << u_stdev << "\n";
    outputFile << "Binomial\t\t\t" << b_mean << "\t\t\t" << b_stdev << "\n";
    outputFile << "Exponential\t\t" << e_mean << "\t\t" << e_stdev << "\n";
    outputFile << "Normal\t\t\t" << n_mean << "\t\t" << n_stdev << "\n";
    outputFile << "Geometric\t\t\t" << g_mean << "\t\t\t" << g_stdev << "\n";
    outputFile.close();

    keep_window_open();
    return 0;
}
