// Compile it with:
//   g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

/**
 * Equity Research Tool
 * FE 522
 * By: Nicole Lange, Kristina Redmond, Nicholas Colonna
 */

#include <iostream>
#include "std_lib_facilities.h"
#include <sstream>
#include <fstream>
#include <typeinfo>

vector<double> returns(vector<double> prices) {
    int size = prices.size();
    vector<double> returns;
    for (int i = 1; i < size; ++i) {
        double current = prices[i];
        double past = prices[i - 1];
        double price_return = (current - past) / past;
        returns.push_back(price_return);
    }
    return returns;
}

double expected_return(vector<double> prices){
    double sum = 0;
    for(int i = 0; i < prices.size(); i++)
        sum = sum + prices[i];
    return sum / prices.size();
}

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

vector<double> monthly_returns(vector<double> prices) {
    int size = prices.size();
    vector<double> returns;
    for (int i = 23; i < size; i+=22) {
        double current = prices[i];
        double past = prices[i - 22];
        double price_return = (current - past) / past;
        returns.push_back(price_return);
    }
    return returns;
}

vector<double> annual_returns(vector<double> prices) {
    int size = prices.size();
    vector<double> returns;
    for (int i = 252; i < size; i+=251) {
        double current = prices[i];
        double past = prices[i - 251];
        double price_return = (current - past) / past;
        returns.push_back(price_return);
    }
    return returns;
}

double standard_deviation(vector<double> prices){
    double var;
    double sd;
    double mean = expected_return(prices);
    int size = prices.size();
    for (int i = 0; i < size; ++i){
        var = var + pow(prices[i] - mean, 2);
        double var2 = var / size;
        sd = sqrt(var2);
    }
    return sd;
}

double risk_free(vector<double> tbill){
    double mean = expected_return(tbill);
    double rf = mean/100;
    return rf;
}

double var95(vector<double> prices){
    vector<double> k = returns(prices);
    sort(k.begin(), k.end());
    int x = k.size() * (1-0.95);
    return k[x - 1];
}

double cvar95(vector<double> prices){
    double sum;
    vector<double> k = returns(prices);
    sort(k.begin(), k.end());
    int x = k.size() * (1-0.95);
    int y = x;  // copies value of x before it gets iterated down
    while (x != 0){
        sum += k[x - 1];
        x--;
    }
    return sum / y;
}

double monthly_cvar95(vector<double> prices){
    double sum;
    vector<double> k = monthly_returns(prices);
    sort(k.begin(), k.end());
    int x = k.size() * (1-0.95);
    int y = x;  // copies value of x before it gets iterated down
    while (x != 0){
        sum += k[x - 1];
        x--;
    }
    return sum / y;
}

double c_sharpe_ratio(vector<double> prices){
    vector<double> k = annual_returns(prices);
    double numerator = expected_return(k) - 0.024;
    return numerator / 12*monthly_cvar95(prices);
}

float mean(vector<double> prices)
{
    double sum = 0;
    for(int i = 0; i < prices.size(); i++)
        sum = sum + prices[i];
    return sum / prices.size();
}

double covariance(vector<double> v1, vector<double> v2)
{
    float sum = 0;
    for(int i = 0; i < v1.size(); i++)
        sum = sum + (v1[i] - mean(v1)) *
                    (v2[i] - mean(v2));
    return sum / (v1.size() - 1);
}

double variance(vector<double> v1){
    double var = 0;
    for(int i = 0; i < v1.size(); i++)
    {
        var = var +  (v1[i] - mean(v1)) * (v1[i] - mean(v1));
    }
    var = var/v1.size();
    return var;
}

double beta(vector<double> prices, vector<double> SP){
    vector<double> perc_change_stock;
    vector<double> perc_change_sp;
    double hold;
    for (int i = 1; i < prices.size(); i++){
        double temp = (prices[i] - prices[i-1])/prices[i-1];
        perc_change_stock.push_back(temp);
    }
    for (int i = 1; i < SP.size(); i++){
        double temp = (SP[i] - SP[i-1])/SP[i-1];
        perc_change_sp.push_back(temp);
    }
    double covar = covariance(perc_change_stock, perc_change_sp);
    double var = variance(perc_change_sp);
    hold = covar/var;
    return hold;
}

double volatility(vector<double> prices){
    double hold = sqrt(variance(prices));
    return hold;
}
double sharpe_ratio(vector<double> prices){
    double numerator = expected_return(annual_returns(prices)) - 0.024;
    double denominator = volatility(annual_returns(prices));
    return numerator / denominator;
}

vector<double> load_new(vector<vector<string>> all, int position){
    vector<double> hello;
    for (int i = 1; i < all.size(); i++){
        hello.push_back(stod(all[i][position]));
    }
    return hello;
}
vector<double> calcs(vector<vector<string>> database, string ticker){
    int stock_position;
    for (int i = 1; i < database[0].size(); i++){
        if (database[0][i] == ticker){
            stock_position = i;
            break;
        }
    }
    vector<double> stock_specific = load_new(database, stock_position);
    vector<double> SP = load_new(database, 1);
    vector<double> ratios;
    double curr_price = stock_specific.back();
    double ret = expected_return(annual_returns(stock_specific));
    double x = beta(stock_specific, SP);
    double y = c_sharpe_ratio(stock_specific);
    double z = volatility(stock_specific);
    double a = cvar95(stock_specific);
    double b = var95(stock_specific);
    double c = sharpe_ratio(stock_specific);
    ratios = {curr_price, ret, x, z, c, y, b, a};
    return ratios;
}

string recommendation(vector<vector<string>> database, string ticker){
    int stock_position = -1;
    for (int i = 1; i < database[0].size(); i++){
        if (database[0][i] == ticker){
            stock_position = i;
            break;
        }
    }
    vector<double> stock_specific = load_new(database, stock_position);

    double avg_sharpe = 0;
    vector<double> annual_rets(database[0].size()-3);
    for (int i=2; i< database[0].size()-1; i++){
        vector<double> stock = load_new(database, i);
        avg_sharpe += sharpe_ratio(stock);
        annual_rets[i-2] = expected_return(annual_returns(stock));
    }
    avg_sharpe = avg_sharpe / (database[0].size() - 3);
    double median_rets = median(annual_rets);

    string rec;
    if(sharpe_ratio(stock_specific) >= avg_sharpe && expected_return(annual_returns(stock_specific)) >= median_rets){
        rec = "Buy";
    }else{
        rec = "Sell";
    }
    return rec;
}

int main() {
#define ABS(a) ((a) < 0 ? - (a) : (a))
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  FOR(i,0,n)


    vector<vector<string>> items;
    ifstream ifs("../../input/price_data.csv");
    if (ifs.fail()) {
        cerr << "error" << endl;
        return 0;
    }
    string line;
    while (getline(ifs, line)) {
        stringstream ss(line);
        vector<string> item;
        string tmp;
        while(getline(ss, tmp, ',')) {
            item.push_back(tmp);
        }
        items.push_back(item);
    }
    ifs.close();


    int repeatInt = 0;
    while(repeatInt==0) {
        cout << "What S&P 500 stock would you like to research?" << "\n";
        string tick;
        cin >> tick;

        vector<double> hold = calcs(items, tick);
        cout << "Ratios and Recommendations for " << tick << endl;
        for (int i = 0; i < hold.size(); i++) {
            if (i == 0) {
                cout << "Closing Price on " << items.back()[0] << ": $" << hold[i] << endl;
            }
            if (i == 1) {
                cout << "Average Annual Return: " << 100 * hold[i] << "%" << endl;
            }
            if (i == 2) {
                cout << "Beta: " << hold[i] << endl;
            }
            if (i == 3) {
                cout << "Volatility: " << hold[i] << endl;
            }
            if (i == 4) {
                cout << "Sharpe Ratio: " << hold[i] << endl;
            }
            if (i == 5) {
                cout << "C Sharpe Ratio: " << hold[i] << endl;
            }
            if (i == 6) {
                cout << "VAR: " << hold[i] << endl;
            }
            if (i == 7) {
                cout << "CVAR: " << hold[i] << endl;
            }
        }
        string rec = recommendation(items, tick);
        cout << "Recommendation for " << tick << " is: " << rec << endl;

        ofstream outfile("../../output/" + tick + ".txt");
        outfile << "Ratios and Recommendations for " << tick << endl;
        for (int i = 0; i < hold.size(); i++) {
            if (i == 0) {
                outfile << "Closing Price on " << items.back()[0] << ": $" << hold[i] << endl;
            }
            if (i == 1) {
                outfile << "Average Annual Return: " << 100 * hold[i] << "%" << endl;
            }
            if (i == 2) {
                outfile << "Beta: " << hold[i] << endl;
            }
            if (i == 3) {
                outfile << "Volatility: " << hold[i] << endl;
            }
            if (i == 4) {
                outfile << "Sharpe Ratio: " << hold[i] << endl;
            }
            if (i == 5) {
                outfile << "C Sharpe Ratio: " << hold[i] << endl;
            }
            if (i == 6) {
                outfile << "VAR: " << hold[i] << endl;
            }
            if (i == 7) {
                outfile << "CVAR: " << hold[i] << endl;
            }

        }
        outfile << "Recommendation for " << tick << " is: " << rec;
        outfile.close();
        cout << "Research report file " + tick + ".txt has been created.\n";

        cout << "\nWould you like to research another stock? (0 for Yes, 1 for No): ";
        cin >> repeatInt;
        cout << "\n";
    }

    return 1;
}