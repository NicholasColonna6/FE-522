/*
 * Nicholas Colonna
 * FE 522
 * Assignment 2
 * Problem 2
 */

#include "std_lib_facilities.h"
const double pi = 3.1415926535897;

//BASE OPTION CLASS
class Option {
public:
    string type;
    double spot, strike, rate, vol, ttm;

    //default constructor
    Option(){ }

    //constructor
    Option(string t, double sp, double st, double r, double v, double m) : type(t), spot(sp), strike(st), rate(r), vol(v), ttm(m) { }

    //returns the CDF of the standard normal distribution
    double N(double num){
        return 0.5 * erfc(-num * sqrt(0.5));   //cumulative distribution implementation found on StackOverflow
    }

    //function calculates price of a put or call option
    virtual double getPrice(){
        //function is overwritten in European and American option classes
        return 0;
    }

    double getDelta(double bump){
        double temp = spot;
        double og = this->getPrice();
        spot = spot + bump;
        double bp = this->getPrice();
        spot = temp;
        return (bp - og) / bump;
    }

    double getRho(double bump){
        double temp = rate;
        double og = this->getPrice();
        rate = rate + bump;
        double bp = this->getPrice();
        rate = temp;
        return ((bp - og) / bump) / 100;
    }

    double getVega(double bump){
        double temp = vol;
        double og = this->getPrice();
        vol = vol + bump;
        double bp = this->getPrice();
        vol = temp;
        return ((bp - og) / bump) / 100;
    }

    double getTheta(double bump){
        double temp = ttm;
        double og = this->getPrice();
        ttm = ttm + bump;
        double bp = this->getPrice();
        ttm = temp;
        return -((bp - og) / bump) / 100;
    }

//    //calculates the delta of an option
//    double getDelta(){
//        double d1 = (1/(vol * sqrt(ttm))) * (log(spot/strike) + (rate + (pow(vol, 2) / 2)) * ttm);
//        if(type == "call" || type == "Call"){
//            return N(d1);
//        }else{
//            return N(d1) - 1;
//        }
//    }
//
//    //calculates the rho of an option
//    double getRho(){
//        double d1 = (1/(vol * sqrt(ttm))) * (log(spot/strike) + (rate + (pow(vol, 2) / 2)) * ttm);
//        double d2 = d1 - (vol * sqrt(ttm));
//        if(type == "call" || type == "Call"){
//            return (strike * ttm * exp(-rate*ttm) * N(d2)) / 100;
//        }else{
//            return (strike * ttm * exp(-rate*ttm) * N(-d2)) / 100;
//        }
//    }
//
//    //calculates the vega of an option
//    double getVega(){
//        double d1 = (1/(vol * sqrt(ttm))) * (log(spot/strike) + (rate + (pow(vol, 2) / 2)) * ttm);
//        return (spot * sqrt(ttm) * (exp(-(pow(d1,2) / 2)) / sqrt(2 * pi))) / 100;
//    }
//
//    //calculates the theta of an option
//    double getTheta(){
//        double d1 = (1/(vol * sqrt(ttm))) * (log(spot/strike) + (rate + (pow(vol, 2) / 2)) * ttm);
//        double d2 = d1 - (vol * sqrt(ttm));
//        if(type == "call" || type == "Call"){
//            return (1/(365*ttm)) * (-((spot*vol/(2*sqrt(ttm))) * (exp(-pow(d1, 2)/2)/sqrt(2*pi))) - rate*strike*exp(-rate*ttm)*N(d2));
//        }else{
//            return (1/(365*ttm)) * (-((spot*vol/(2*sqrt(ttm))) * (exp(-pow(d1, 2)/2)/sqrt(2*pi))) - rate*strike*exp(-rate*ttm)*N(-d2));
//
//        }
//    }


};

//EUROPEAN OPTION CLASS
class EuropeanOption : public Option{
public:
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

//AMERICAN OPTION CLASS
class AmericanOption : public Option{
public:
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

void getAllGreeks(Option& opt){
    cout << "The four Greeks for the option are:\n";
    cout << "Delta: " << opt.getDelta(1) << endl;
    cout << "Rho: " << opt.getRho(.01) << endl;
    cout << "Vega: " << opt.getVega(.01) << endl;
    cout << "Theta: " << opt.getTheta(.002739) << endl;
}

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

    //create european option
    EuropeanOption* european = new EuropeanOption();
    european->type = type;
    european->spot = spot;
    european->strike = strike;
    european->rate = rate;
    european->vol = vol;
    european->ttm = ttm;

    //create american option
    AmericanOption* american = new AmericanOption();
    american->type = type;
    american->spot = spot;
    american->strike = strike;
    american->rate = rate;
    american->vol = vol;
    american->ttm = ttm;

    //print price of European option and their greeks
    cout << "\nThe price of the European " << type << " option is: " << european->getPrice() << "\n";
    getAllGreeks(*european);
    cout << "\n";

    //print price of American option and their greeks
    cout << "The price of the American " << type << " option is: " << american->getPrice() << "\n";
    getAllGreeks(*american);

    //MY ANALYSIS:
    //Call vs. Put
        //For call options, delta, rho and vega are all positive and only theta is negative.
        //For put options, delta, rho and theta are negative, and vega is positive.
        //Vega is generally the same between calls and puts, while the others change

    //American vs. European
        //Delta is slightly higher for American options
        //Rho is slightly higher for European options
        //Vega is higher for American options
        //The magnitude of Theta is greater for American options
        //I would attribute all of these factors to the American option having a higher price due to early exercise ability

    keep_window_open();
    return 0;
}
