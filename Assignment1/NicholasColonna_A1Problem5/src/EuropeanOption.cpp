/*
 * Nicholas Colonna
 * FE 522
 * Assignment 1
 * Problem 5
 */

#include "std_lib_facilities.h"

class EuropeanOption {
public:
    string type;
    double spot, strike, rate, vol, ttm;

    //default constructor
    EuropeanOption(){ }

    //constructor
    EuropeanOption(string t, double sp, double st, double r, double v, double m) : type(t), spot(sp), strike(st), rate(r), vol(v), ttm(m) { }


    //returns the CDF of the standard normal distribution
    double N(double num){
        return 0.5 * erfc(-num * sqrt(0.5));   //cumulative distribution implementation found on StackOverflow
    }


    //function calculates price of a put or call option
    double getPrice(){
        double d1 = (1/(vol * sqrt(ttm))) * (log(spot/strike) + (rate + (pow(vol, 2) / 2)) * ttm);
        double d2 = d1 - (vol * sqrt(ttm));

        if(type == "put"){
            return (N(-d2) * strike * exp(-rate * ttm)) - (N(-d1) * spot);
        }else{
            return (N(d1) * spot) - (N(d2) * strike * exp(-rate * ttm));
        }
    }
};

int main()
{
    string type;
    double spot, strike, rate, vol, ttm;

    cout << "Enter the type of option (put or call): ";
    while(cin>>type){
        if(type=="put" || type=="call" || type=="Put" || type=="Call"){
            break;
        }
        cout << "Error: Option type can only be 'put' or 'call'\n";
        cout << "Enter the type of option (put or call): ";
    }

    cout << "Enter the spot price: ";
    while(cin >> spot){
        if(spot >= 0){
            break;
        }
        cout << "Error: Spot price can't be negative.\n";
        cout << "Enter the spot price: ";
    }

    cout << "Enter the strike price: ";
    while(cin >> strike){
        if(strike >= 0){
            break;
        }
        cout << "Error: Strike price can't be negative.\n";
        cout << "Enter the strike price: ";
    }

    cout << "Enter the interest rate (in %): ";
    while(cin >> rate){
        if(rate >= 0 && rate <= 100){
            rate = rate / 100;
            break;
        }else if(rate < 0){
            cout << "Error: Interest rate can't be negative.\n";
        }else if(rate > 100){
            cout << "Error: Interest rate can't be greater than 100%\n";
        }
        cout << "Enter the interest rate (in %): ";
    }

    cout << "Enter the volatility (in %): ";
    while(cin >> vol){
        if(vol >= 0) {
            vol = vol / 100;
            break;
        }
        cout << "Error: Volatility can't be negative.\n";
        cout << "Enter the interest rate (in %): ";
    }

    cout << "Enter the time to maturity (in years): ";
    while(cin >> ttm){
        if(ttm > 0){
            break;
        }
        cout << "Error: Time to maturity can't be negative.\n";
        cout << "Enter the time to maturity (in years): ";
    }

    EuropeanOption* input = new EuropeanOption(type, spot, strike, rate, vol, ttm);

    cout << "\nThe price of the option is: " << input->getPrice() << "\n";

    keep_window_open();
    return 0;
}
