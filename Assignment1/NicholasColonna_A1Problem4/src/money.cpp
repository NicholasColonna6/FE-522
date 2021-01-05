/*
 * Nicholas Colonna
 * FE 522
 * Assignment 1
 * Problem 4
 */

#include "std_lib_facilities.h"

class Money{
public:
    long cents;
    string currency;

    //default constructor
    Money(){ }

    //constructor
    Money(long num_cents, string curr) : cents(num_cents), currency(curr) { }

    //overload addition operator for Money addition
    Money operator +(Money &second){
        if(currency != second.currency){       //if currencies are different, give error and return -1 cents
            cout << "Cannot add different currencies together.\n";
            return Money(-1, "None");
        }
        return Money(cents + second.cents, currency);       //else do the addition
    }

    //overload subtraction operator for Money subtraction
    Money operator -(Money &second){
        if(currency != second.currency){    //if currencies are different, give error and return -1 cents
            cout << "Cannot subtract different currencies from each other.\n";
            return Money(-1, "None");
        }
        return Money(cents - second.cents, currency);       //else do the subtraction
    }

    //overload multiplication operator where value is an integer
    Money operator *(int second){
        if(second <= 0){        //give error if the value multiplying by is 0 or negative, return -1 cents
            cout << "Cannot multiply by 0 or a negative number.\n";
            return Money(-1, "None");
        }
        return Money(cents * second, currency);     //else do the multiplication
    }

    //overload multiplication operator where value is a double
    Money operator *(double second){
        if(second <= 0){      //give error if the value multiplying by is 0 or negative, return -1 cents
            cout << "Cannot multiply by 0 or a negative number.\n";
            return Money(-1, "None");
        }
        return Money(round(cents * second), currency);  //else do the multiplication and round
    }

    //overload divsion operator where divisor is an integer
    Money operator /(int second){
        if(second <= 0){        //give error if denominator is 0 or negative, return -1 cents
            cout << "Cannot divide by 0 or a negative number.\n";
            return Money(-1, "None");
        }
        return Money(round(cents / second), currency);      //else do the division and round
    }

    //overload division operator where divisor is a double
    Money operator /(double second) {
        if (second <= 0) {       //give error if denominator is 0 or negative, return -1 cents
            cout << "Cannot divide by 0 or a negative number.\n";
            return Money(-1, "None");
        }
        return Money(round(cents / second), currency);      //else do the division and round
    }

};

//definition of input operator to take dollars and convert to cents
istream &operator >>(istream &input, Money &val){
    double dollars;
    input >> val.currency >> dollars;   //takes input and saves currency and dollars entered
    val.cents = dollars * 100;      //converts dollars to cents
    return input;
}

//definition of output operator to convert cents to dollars and format output
ostream &operator <<(ostream &output, Money &val){
    long dollars = val.cents / 100;     //finds amount of whole dollars
    long cents = val.cents - (dollars * 100);      //finds amount of remaining cents
    if(cents == -1){    //if there was an error
        output << val.currency << " -" << dollars << "." << setw(2) << setfill('0') << abs(cents);
    }else{  //if everything ran fine
        output << val.currency << " " << dollars << "." << setw(2) << setfill('0') << abs(cents);        //formats output to be 'curency xx.xx'
    }
    return output;
}

//main function to prompt user for inputs
int main()
{
    //creates test Money variables
    Money entry1(0, "USD");
    Money entry2(0, "USD");

    //prompts user for input and saves
    cout << "Entry 1: Enter the currency and dollar amount: ";
    cin >> entry1;
    cout << "Entry 2: Enter the currency and dollar amount: ";
    cin >> entry2;

    //prints user input back to user
    cout << "\nEntry1: " << entry1 << "\n";
    cout << "Entry2: " << entry2 << "\n\n";

    //tests and prints all of operator tests
    Money add = entry1 + entry2;
    cout << "Entry1 + Entry2 = " << add << "\n";

    Money subtract = entry1 - entry2;
    cout << "Entry1 - Entry2 = " << subtract << "\n";

    Money int_mult = entry1 * 2;
    cout << "Entry1 *  2 = " << int_mult << "\n";

    Money double_mult = entry2 * 1.5;
    cout << "Entry1 * 1.5 = " << double_mult << "\n";

    Money int_div = entry1 / 2;
    cout << "Entry1 / 2 = " << int_div << "\n";

    Money double_div = entry2 / 1.5;
    cout << "Entry1 / 1.5 = " << double_div << "\n";


    keep_window_open();
    return 0;
}
