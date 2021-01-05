/*
 * Nicholas Colonna
 * FE 522
 * Assignment 1
 * Problem 6
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
    ifstream input("../../input/options_data.txt");
    if (input.fail()) {
        cerr << "Error: Unable to load file\n";
    }
    vector<vector<string>> data;
    string line;
    while (getline(input, line)) {
        stringstream ss(line);
        vector<string> row;
        string item;
        while(getline(ss, item, '\t')) {
            row.push_back(item);
        }
        data.push_back(row);
    }

    vector<EuropeanOption> options;
    vector<double> prices;
    for(int i=1; i<data.size(); i++){
        string t = data[i][0];

        stringstream ssp(data[i][1]);
        double sp;
        ssp >> sp;

        stringstream sst(data[i][2]);
        double st;
        sst >> st;

        stringstream sr(data[i][3]);
        double r;
        sr >> r;

        stringstream sv(data[i][4]);
        double v;
        sv >> v;

        stringstream stt(data[i][5]);
        double tt;
        stt >> tt;

        EuropeanOption *option = new EuropeanOption(t, sp, st, r/100, v/100, tt);

        options.push_back(*option);
        prices.push_back(option->getPrice());
    }

    vector<vector<string>> output_vec;
    for(int i=0; i<data.size(); i++){
        vector<string> help;
        for(int j=0; j<data[i].size()+1; j++) {
            if (j == data[i].size()) {
                if (i == 0) {
                    help.push_back("Price");
                } else {
                    ostringstream oss;
                    oss << prices[i - 1];
                    help.push_back(oss.str());
                }
            }else if(j == data[i].size() - 1){
                if(i == 0){
                    help.push_back(data[i][j].substr(0, data[i][j].size()-1));
                }else{
                    stringstream ss(data[i][j]);
                    double dbl;
                    ss >> dbl;

                    ostringstream oss;
                    oss << dbl;
                    help.push_back(oss.str());
                }
            }else{
                help.push_back(data[i][j]);
            }
        }
        output_vec.push_back(help);
    }

    ofstream output;
    output.open("../../output/results.txt");
    for(int i=0; i<output_vec.size(); i++){
        for(int j=0; j<output_vec[i].size(); j++){
            output << output_vec[i][j] << "\t";
        }
        output << "\n";
    }
    output.close();

    keep_window_open();
    return 0;
}
