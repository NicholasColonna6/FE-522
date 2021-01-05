/*
 * Nicholas Colonna
 * FE 522
 * Drill 3
 * "I pledge my honor that I have abided by the Stevens Honor System." -ncolonna
 */

#include "std_lib_facilities.h"

int main()
{
    cout << "Enter the name of the person you want to write to:\n";
    string first_name;
    cin>>first_name;
    cout << "Enter the name of the friend you want to reference:\n";
    string friend_name;
    cin>>friend_name;
    char friend_sex = 0;
    cout << "Enter an 'm' if the friend is male and an 'f' if the friend is female.\n";
    cin >> friend_sex;
    int age;
    cout << "Enter the age of the recipient:\n";
    cin>>age;

    cout<<"Dear "<<first_name<<",\n";
    cout<<"    How are you? I am fine. I miss you. ";
    cout<<"I am writing this for my programming assignment. ";
    cout<<"I hope to hear back from you soon.\n";
    cout << "Have you seen "<<friend_name<<" lately? ";

    if(friend_sex == 'm') {
        cout << "If you see " << friend_name << " please ask him to call me.\n";
    }if(friend_sex == 'f'){
        cout << "If you see " << friend_name << " please ask her to call me.\n";
    }

    cout << "I hear you just had a birthday and you are " << age << " years old. ";

    if(age <= 0 || age >= 110) {
        simple_error("you're kidding!");
    }else if(age < 12) {
        cout << "Next year you will be " << age + 1 << ".\n";
    }else if(age == 17) {
        cout << "Next year you will be able to vote.\n";
    }else if(age > 70){
        cout << "I hope you are enjoying retirement.\n";
    }else{
        cout << "\n";
    }

    cout<<"Yours sincerely,\n\n\nNicholas Colonna\n";


    keep_window_open();
    return 0;
}
