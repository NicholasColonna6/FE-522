/*
 * Nicholas Colonna
 * FE 522
 * Assignment 1
 * Problem 1
 */

#include "std_lib_facilities.h"

int main()
{
    //1,000 grains
    cout << "How many squares to give the inventor at least 1000 grains of rice? \n";
    int curr_square = 0;
    int rice_for_curr;
    int rice_total = 0;
    while(rice_total < 1000){
        rice_for_curr = pow(2, curr_square);
        curr_square++;
        rice_total += rice_for_curr;
        cout << "Square #" << curr_square << "\t\tRice on Current Square: " << rice_for_curr << "\t\tRice Total: " << rice_total << "\n";
    }

    //1,000,000 grains
    cout << "\n\nHow many squares to give the inventor at least 1,000,000 grains of rice? \n";
    curr_square = 0;
    rice_total = 0;
    while(rice_total < 1000000){
        rice_for_curr = pow(2, curr_square);
        curr_square++;
        rice_total += rice_for_curr;
        cout << "Square #" << curr_square << "\t\tRice on Current Square: " << rice_for_curr << "\t\tRice Total: " << rice_total << "\n";
    }

    //1,000,000,000 grains
    cout << "\n\nHow many squares to give the inventor at least 1,000,000,000 grains of rice? \n";
    curr_square = 0;
    rice_total = 0;
    while(rice_total < 1000000000){
        rice_for_curr = pow(2, curr_square);
        curr_square++;
        rice_total += rice_for_curr;
        cout << "Square #" << curr_square << "\t\tRice on Current Square: " << rice_for_curr << "\t\tRice Total: " << rice_total << "\n";
    }


    //calculate inventor's request using ints
    cout << "\n\nHow many grains of rice did the inventor ask for (64 squares using int)? \n";
    curr_square = 0;
    rice_total = 0;
    while(curr_square < 64){
        rice_for_curr = pow(2, curr_square);
        curr_square++;
        rice_total += rice_for_curr;
        cout << "Square #" << curr_square << "\t\tRice on Current Square: " << rice_for_curr << "\t\tRice Total: " << rice_total << "\n";
    }

    //calculate inventor's request using doubles
    cout << "\n\nHow many grains of rice did the inventor ask for (64 squares using double)? \n";
    curr_square = 0;
    double total_rice = 0;
    double curr_square_rice;
    while(curr_square < 64){
        curr_square_rice = pow(2, curr_square);
        curr_square++;
        total_rice += curr_square_rice;
        cout << "Square #" << curr_square << "\t\tRice on Current Square: " << curr_square_rice << "\t\tRice Total: " << total_rice << "\n";
    }


    //calculate max number using doubles
    cout << "\n\nHow many grains of rice can you max out, using a double? \n";
    curr_square = 0;
    total_rice = 0;
    while(curr_square < 1024){
        curr_square_rice = pow(2, curr_square);
        curr_square++;
        total_rice += curr_square_rice;
        cout << "Square #" << curr_square << "\t\tRice on Current Square: " << curr_square_rice << "\t\tRice Total: " << total_rice << "\n";
    }


    keep_window_open();
    return 0;
}
