/**
 * Nicholas Colonna
 */
#include "std_lib_facilities.h"

bool isPalindrome(string s)
{
    string original;
    for(int i=0; i<s.length(); i++){        //this loop creates a string with only the letters (in lower case) and numbers
        if(s[i] > 64 && s[i] < 91){     //capital letters
            original += (s[i] + 32);    //save as lower case in string
        }else if(s[i] > 96 && s[i] < 123){  //lower case letters
            original += (s[i]);
        }else if(s[i] > 47 && s[i] < 58){   //numbers
            original += (s[i]);
        }
    }

    string flipped;
    for(int i=original.length()-1; i>=0; i--){  //loop through original backwards, saving to flipped
        flipped += original[i];
    }

    for(int i=0; i<original.length(); i++){
        if(original[i] != flipped[i]){      //if they aren't the same at any given point, return false
            return false;
        }
    }
    return true;
}

int main()
{
    cout << "Task 1:" << '\n';

    cout << "This should return true: " << (isPalindrome("Rats live on no evil star") ? "true" : "false") << '\n';

    cout << "This should return false: " << (isPalindrome("To be or not to be") ? "true" : "false") << '\n';

    cout<<"\n";

    //My True Test Cases
    cout << "This should return true: " << (isPalindrome("A man, a plan, a canal, Panama!") ? "true" : "false") << '\n';
    cout << "This should return true: " << (isPalindrome("Was it a car or a cat I saw?") ? "true" : "false") << '\n';
    cout << "This should return true: " << (isPalindrome("1100110011") ? "true" : "false") << '\n';

    //My False Test Cases
    cout << "This should return false: " << (isPalindrome("This is not a palindrome.") ? "true" : "false") << '\n';
    cout << "This should return false: " << (isPalindrome("1234567") ? "true" : "false") << '\n';
    cout << "This should return false: " << (isPalindrome("This is my midterm") ? "true" : "false") << '\n';

    keep_window_open();

    return 0;
}
