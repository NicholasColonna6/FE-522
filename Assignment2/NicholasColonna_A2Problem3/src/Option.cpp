/*
 * Nicholas Colonna
 * FE 522
 * Assignment 2
 * Problem 3
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

class Link {
public:
    Option value;

    Link(const Option& o, Link* p = 0, Link* s = 0) : value(o), prev(p), succ(s) { }

    Link* insert(Link* n);
    Link* add(Link* n);
    Link* addOrdered(Link* n);

    Link* get_next() const {
        return succ;
    }
    Link* get_previous() const {
        return prev;
    }
private:
    Link* prev;
    Link* succ;
};

//Adds n before this object
Link* Link::insert(Link* n){
    if (this==0) error("Error: called insert() with no object");
    if(n==0) {
        return this;
    }
    n->succ = this;  // n comes before this object
    if(prev) {
        prev->succ = n;
    }
    n->prev = prev;  //n's predecessor is now this object's predecessor
    prev = n;  //n is now this object's predecessor
    return n;
}

//Adds n after this object
Link* Link::add(Link* n){
    if (this==0){
        error("Error: called add() with no object");
    }
    if(n==0){
        return this;
    }
    n->prev = this;  //n goes after this object
    if(succ){
        succ->prev = n;
    }
    n->succ = succ;   //n's successor is now this object's successor
    succ = n;    //this object's predecessor is now n
    return n;
}

//inserts option in the right place
Link* Link::addOrdered(Link* n){
    if(this==0) {
        error("Error: called addOrdered() with no object");
    }
    if(n==0){   //if link is empty, return this
        return this;
    }

    Link* ptr = this;
    if(n->value.type < ptr->value.type){
        return this->insert(n);
    }
    while(true){
        if(ptr->succ==0 || n->value.type <= ptr->value.type){       //checks for option type of if at end of link
            if(ptr->succ==0){
                ptr->add(n);
                return this;
            }
            if(n->value.ttm < ptr->value.ttm){
                return this->insert(n);
            }
            while(true){
                if(ptr->succ==0 || n->value.ttm <= ptr->value.ttm){  //checks for option maturity of if at end of link
                    if(n->value.strike < ptr->value.strike){
                        return this->insert(n);
                    }
                    if(ptr->succ==0){
                        ptr->add(n);
                        return this;
                    }
                    while(true){
                        if(ptr->succ==0 || n->value.strike < ptr->value.strike){    //checks for option strike of if at end of link
                            ptr->add(n);
                            return this;
                        }
                        ptr = ptr->succ;
                    }
                }
                ptr = ptr->succ;
            }
        }
        ptr = ptr->succ;
    }
}

//prints the Link
void print_all(Link* p)
{
    cout << setw(15) << "Type" << setw(15) << "Spot" <<
         setw(15) << "Strike" << setw(15) << "Rate" << setw(15) << "Vol" << setw(15) << "TTM" << endl;
    while (p) {
        cout << setw(15) << p->value.type << setw(15) << p->value.spot << setw(15) << p->value.strike <<
             setw(15) << p->value.rate << setw(15) << p->value.vol << setw(15) << p->value.ttm << endl;
        p = p->get_next();
    }
    cout << endl;
}

int main()
{
    //create european options
    EuropeanOption* european1 = new EuropeanOption();
    european1->type = "call";
    european1->spot = 100;
    european1->strike = 100;
    european1->rate = .06;
    european1->vol = .20;
    european1->ttm = 1;

    EuropeanOption* european2 = new EuropeanOption();
    european2->type = "put";
    european2->spot = 50;
    european2->strike = 51;
    european2->rate = .03;
    european2->vol = .30;
    european2->ttm = 2;

    EuropeanOption* european3 = new EuropeanOption();
    european3->type = "call";
    european3->spot = 75;
    european3->strike = 70;
    european3->rate = .05;
    european3->vol = .40;
    european3->ttm = 1;

    EuropeanOption* european4 = new EuropeanOption();
    european4->type = "put";
    european4->spot = 25;
    european4->strike = 40;
    european4->rate = .04;
    european4->vol = .2;
    european4->ttm = 3;

    //create american option
    AmericanOption* american1 = new AmericanOption();
    american1->type = "call";
    american1->spot = 100;
    american1->strike = 100;
    american1->rate = .06;
    american1->vol = .20;
    american1->ttm = 1;

    AmericanOption* american2 = new AmericanOption();
    american2->type = "put";
    american2->spot = 65;
    american2->strike = 69;
    american2->rate = .04;
    american2->vol = .25;
    american2->ttm = 2;

    AmericanOption* american3 = new AmericanOption();
    american3->type = "put";
    american3->spot = 105;
    american3->strike = 100;
    american3->rate = .07;
    american3->vol = .45;
    american3->ttm = 2;

    AmericanOption* american4 = new AmericanOption();
    american4->type = "call";
    american4->spot = 75;
    american4->strike = 70;
    american4->rate = .03;
    american4->vol = .33;
    american4->ttm = 1;

    //create link of european options
    Link* euro = new Link(*european1);
    euro = euro->addOrdered(new Link(*european2));
    euro = euro->addOrdered(new Link(*european3));
    euro = euro->addOrdered(new Link(*european4));
    cout << "European Options Link:\n";
    print_all(euro);

    //create Link of american options
    Link* amer = new Link(*american1);
    amer = amer->addOrdered(new Link(*american2));
    amer = amer->addOrdered(new Link(*american3));
    amer = amer->addOrdered(new Link(*american4));
    cout << "American Options Link:\n";
    print_all(amer);


    keep_window_open();
    return 0;
}
