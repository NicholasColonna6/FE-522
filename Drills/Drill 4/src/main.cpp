/*
 * Nicholas Colonna
 * FE 522
 * Drill 4
 * "I pledge my honor that I have abided by the Stevens Honor System." -ncolonna
 */

#include "std_lib_facilities.h"

int main()
{
    bool first_time = true, valid_units = true;
    const double mTOcm = 100;
    const double inTOcm = 2.54;
    const double ftTOin = 12;
    double smallest = 0, largest = 0;
    double new_num, converted, sum;
    int counter = 0;
    string unit;
    vector<double> values;

    while(cin >> new_num >> unit){
        //convert everything to meters or flags bad value
        if (unit == "m") {
            converted = new_num;
        }else if (unit == "cm") {
            converted = new_num / mTOcm;
        }else if (unit == "in") {
            converted = inTOcm * new_num / mTOcm;
        }else if (unit == "ft") {
            converted = ftTOin * inTOcm * new_num / mTOcm;
        }else{
            valid_units = false;
        }


        if(valid_units == true){
            cout << new_num << unit << "\n";

            values.push_back(converted);  //adds new value to vector of values
            sum += converted;   //adds new value to sum
            counter++;      //increments counter by 1

            if(first_time == true) {    //if its the first time through the loop, assign largest and smallest to value
                first_time = false;
                smallest = converted;
                largest = converted;
            }else if(converted < smallest){   //print when new number is smallest
                cout << "The smallest so far. \n";
                smallest = converted;
            }else if (converted > largest) {      //print when new number is largest
                cout << "The largest so far. \n";
                largest = converted;
            }
        }else{
            cout << "Invalid units entered. \n";
            valid_units = true;
        }
    }

    //prints the smallest, largest, number of values and sum of values
    cout << "Smallest number: " << smallest << "m \n";
    cout << "Largest number: " << largest << "m \n";
    cout << "Number of Values: " << counter << "\n";
    cout << "Sum: " << sum << "m \n";

    sort(values.begin(), values.end());     //sorts vector of values
    cout << "All Values Entered: ";
    for(int i=0; i<values.size(); i++){     //loops through vector of values and prints
        cout << values[i] << "m ";
    }
    cout << "\n\n";

    keep_window_open();
    return 0;
}
