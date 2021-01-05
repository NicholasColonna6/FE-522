/*
 * Nicholas Colonna
 * FE 522
 * Assignment 2
 * Problem 1
 */

#include "std_lib_facilities.h"
#include <vector>

class AmericanOption {
public:
    string type;
    double spot, strike, rate, vol, ttm;

    //default constructor
    AmericanOption(){ }

    //constructor
    AmericanOption(string t, double sp, double st, double r, double v, double m) : type(t), spot(sp), strike(st), rate(r), vol(v), ttm(m) { }

    //function calculates price of an American put or call option
    double getPrice(){
        int n = 3;      //set number of periods for the tree
        double dt = ttm / n;    //delta t (change in time for each period)
        double u = exp(vol * sqrt(dt));     // probability of up movement
        double d = exp(-vol * sqrt(dt));    // probability of down movement
        double q = (exp(rate * dt) - d) / (u-d);     //risk neutral probability

        //create binomial tree for stock price
        vector<vector<double>> binomialTree(n+1, vector<double>(n+1, 0));
        for(int i=0; i<n+1; i++){
            for(int j=0; j<=i; j++){
                binomialTree[i][j] = spot * pow(d, i-j) * pow(u, j);
            }
        }

        vector<vector<double>> valueTree(n+1, vector<double>(n+1, 0));  //create value tree storage

        if(type == "call" || type == "Call"){
            //create value tree for call
            for(int i=0; i<n+1; i++){
                valueTree[n][i] = max(binomialTree[n][i] - strike, 0.0);
            }

            //loop backward through tree to get value of call option
            for(int i=n-1; i>=0; i--){
                for(int j=0; j<=i; j++){
                    valueTree[i][j] = max(binomialTree[i][j] - strike, exp(-rate * dt) * (q*valueTree[i+1][j+1] + (1-q)*valueTree[i+1][j]));
                }
            }
        }else{
            //create value tree for put
            for(int i=0; i<n+1; i++){
                valueTree[n][i] = max(strike - binomialTree[n][i], 0.0);
            }

            //loop backward through tree to get value of put option
            for(int i=n-1; i>=0; i--){
                for(int j=0; j<=i; j++){
                    valueTree[i][j] = max(strike - binomialTree[i][j], exp(-rate * dt) * (q*valueTree[i+1][j+1] + (1-q)*valueTree[i+1][j]));
                }
            }
        }

        return valueTree[0][0];
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
        cout << "Enter the volatility (in %): ";
    }

    cout << "Enter the time to maturity (in years): ";
    while(cin >> ttm){
        if(ttm > 0){
            break;
        }
        cout << "Error: Time to maturity can't be negative.\n";
        cout << "Enter the time to maturity (in years): ";
    }

    AmericanOption* input = new AmericanOption(type, spot, strike, rate, vol, ttm);

    cout << "\nThe price of the American " << type << " option is: " << input->getPrice() << "\n";

    keep_window_open();
    return 0;
}
