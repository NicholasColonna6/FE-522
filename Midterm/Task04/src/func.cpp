//
// Created by colon on 3/27/2019.
//
/**
 * Nicholas Colonna
 */

#include <vector>
#include <algorithm>
using namespace std;

//calculates the expected value of the vector
double expected_value(vector<double> vec){
    double sum = 0;
    for(int i=0; i<vec.size(); i++){
        sum += vec[i];          //loop through array and sum values
    }
    return sum / vec.size();    //divide the sum by number of elements for mean
}

//calculates the median of the vector
double median(vector<double> vec){
    sort(vec.begin(), vec.end());       //sort vector first
    int n = vec.size();
    double median = 0;
    if(n % 2 == 0){
        median = (vec[(n/2) - 1] + vec[(n/2)]) / 2;         //case if even number of elements
    }else{
        median = vec[(n+1)/2 - 1];          //case if odd number of elements
    }
    return median;
}
