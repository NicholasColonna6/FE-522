/*
 * Nicholas Colonna
 * FE 522
 * Drill 9
 */

#include "std_lib_facilities.h"

int days_in_month(int m){
    int days_in_month = 0;

    if(m == 4 || m == 6 || m == 9 || m == 11){
        days_in_month = 30;
    }else if(m == 2){
        days_in_month = 28;
    }else{
        days_in_month = 31;
    }

    return days_in_month;
}

/**
 * Version 9.4.1
 */
//struct Date{
//    int y;
//    int m;
//    int d;
//};
//
//void init_day(Date& dd, int y, int m, int d){
//    //checks that date given is valid and initializes if true
//    if(y<0 || y>9999){
//        error("Invalid Year");
//    }
//    if(m<1 || m>12){
//        error("Invalid Month");
//    }
//    if(d<1 || d>days_in_month(m)){
//        error("Invalid Day");
//    }
//
//    dd.y = y;
//    dd.m = m;
//    dd.d = d;
//}
//
//void add_day(Date& dd, int n){
//    //increase the date dd by n days
//    if(n > 0){
//        for(int i=0; i < n; i++){
//            dd.d++;
//            if(dd.d > days_in_month(dd.m)){
//                dd.m++;
//                if(dd.m > 12){
//                    dd.m = 1;
//                    dd.y++;
//                }
//                dd.d = 1;
//            }
//        }
//    }else{
//        for(int i=0; i < n*-1; i++){
//            dd.d--;
//            if(dd.d < 1){
//                dd.m--;
//                if(dd.m < 1){
//                    dd.m = 12;
//                    dd.y--;
//                }
//                dd.d = days_in_month(dd.m);
//            }
//        }
//    }
//}

/**
 * Version 9.4.2
 */
//struct Date{
//    int y;
//    int m;
//    int d;
//    Date(int y, int m, int d);
//    void add_day(int n);
//};
//
//Date:: Date(int d_, int m_, int y_){
//    //error checks dates
//    if(y_<0 || y_>9999){
//        error("Invalid Year");
//    }
//    if(m_<1 || m_>12){
//        error("Invalid Month");
//    }
//    if(d_<1 || d_>days_in_month(m)){
//        error("Invalid Day");
//    }
//
//    y = y_;
//    m = m_;
//    d = d_;
//}
//
//void Date:: add_day(int n){
//    //increase the date dd by n days
//    if(n > 0){
//        for(int i=0; i < n; i++){
//            d++;
//            if(d > days_in_month(m)){
//                m++;
//                if(m > 12){
//                    m = 1;
//                    y++;
//                }
//                d = 1;
//            }
//        }
//    }else{
//        for(int i=0; i < n*-1; i++){
//            d--;
//            if(d < 1){
//                m--;
//                if(m < 1){
//                    m = 12;
//                    y--;
//                }
//                d = days_in_month(m);
//            }
//        }
//    }
//}

/**
 * Version 9.4.3
 */
//class Date {
//    int y;
//    int m;
//    int d;
//public:
//    Date (int d, int m, int y);
//    void add_day (int n);
//
//    int getYear(){
//        return y;
//    }
//    int getMonth(){
//        return m;
//    }
//    int getDay() {
//        return d;
//    }
//};
//
//Date:: Date(int d_, int m_, int y_){
//    //error checks dates
//    if(y_<0 || y_>9999){
//        error("Invalid Year");
//    }
//    if(m_<1 || m_>12){
//        error("Invalid Month");
//    }
//    if(d_<1 || d_>days_in_month(m)){
//        error("Invalid Day");
//    }
//
//    y = y_;
//    m = m_;
//    d = d_;
//}
//
//void Date:: add_day(int n){
//    //increase the date dd by n days
//    if(n > 0){
//        for(int i=0; i < n; i++){
//            d++;
//            if(d > days_in_month(m)){
//                m++;
//                if(m > 12){
//                    m = 1;
//                    y++;
//                }
//                d = 1;
//            }
//        }
//    }else{
//        for(int i=0; i < n*-1; i++){
//            d--;
//            if(d < 1){
//                m--;
//                if(m < 1){
//                    m = 12;
//                    y--;
//                }
//                d = days_in_month(m);
//            }
//        }
//    }
//}

/**
 * Version 9.7.4
 */
class Date {
public:
    enum Month {
        January = 1, February, March, April, May, June, July, August,
        September, October, November, December
    };
    Date () : y(1996), m(December), d(15) {}
    Date (int y, Month m, int d);
    void add_day (int n);
    int getYear() const {
        return y;
    }
    Month getMonth() const {
        return m;
    }
    int getDay() const {
        return d;
    }
private:
    int y;
    Month m;
    int d;
};

int daysInMonth (Date::Month m) {
    int days_in_month = 0;

    if(m == Date::April || m == Date::June || m == Date::September || m == Date::November){
        days_in_month = 30;
    }else if(m == Date::February){
        days_in_month = 28;
    }else{
        days_in_month = 31;
    }

    return days_in_month;
}

Date:: Date(int d_, Date::Month m_, int y_){
    //error checks dates
    if(y_<0 || y_>9999){
        error("Invalid Year");
    }
    if(d_<1 || d_>daysInMonth(m_)){
        error("Invalid Day");
    }

    y = y_;
    m = m_;
    d = d_;
}

void Date:: add_day(int n){
    //increase the date dd by n days
    if(n > 0){
        for(int i=0; i < n; i++){
            d++;
            if(d > daysInMonth(m)){
                m = Month(m+1);
                if(m > December){
                    m = January;
                    y++;
                }
                d = 1;
            }
        }
    }else{
        for(int i=0; i < n*-1; i++){
            d--;
            if(d < 1){
                m = Month(m-1);
                if(m < 1){
                    m = December;
                    y--;
                }
                d = daysInMonth(m);
            }
        }
    }
}

//functions used by all

//prints month in words based on date given
void month(ostream &os, int n) {
    switch(n){
        case 1:
            os << "January";
            break;
        case 2:
            os << "February";
            break;
        case 3:
            os << "March";
            break;
        case 4:
            os << "April";
            break;
        case 5:
            os << "May";
            break;
        case 6:
            os << "June";
            break;
        case 7:
            os << "July";
            break;
        case 8:
            os << "August";
            break;
        case 9:
            os << "September";
            break;
        case 10:
            os << "October";
            break;
        case 11:
            os << "November";
            break;
        case 12:
            os << "December";
            break;
    }
}

//formats ending of day number to make sense
void ending (ostream &os, int n) {
    os << n;
    if (n==1 || n==21 || n==31) {
        os << "st";
    }else if (n==2 || n==22){
        os << "nd";
    }else if (n==3 || n==23) {
        os << "rd";
    }else{
        os << "th";
    }
}

//overload output operator to print the Date
//version 9.4.1, 9.4.2
//ostream & operator<< (ostream &os, const Date &dd) {
//    month(os,dd.m);
//    os << " ";
//    ending(os,dd.d);
//    os << ", " << dd.y << "\n";
//    return os;
//}

//version 9.4.3, 9.7.4
ostream & operator<< (ostream &os, Date &dd) {
    month(os,dd.getMonth());
    os << " ";
    ending(os,dd.getDay());
    os << ", " << dd.getYear() << "\n";
    return os;
}

int main()
{
//    //Version 9.4.1
//    Date today;
//    init_day(today, 1996, 12, 15);
//    Date tomorrow = today;
//    add_day(tomorrow, 1);

//    //Version 9.4.2
//    Date today(15, 12, 1996);
//    Date tomorrow = today;
//    tomorrow.add_day(1);

//    //Version 9.4.3
//    Date today(15, 12, 1996);
//    Date tomorrow = today;
//    tomorrow.add_day(1);

    //Version 9.7.4
    Date today(15, Date::December, 1996);
    Date tomorrow = today;
    tomorrow.add_day(1);

    cout << "Today: " << today;
    cout << "Tomorrow: " << tomorrow;

    keep_window_open();
    return 0;
}
