/*
 * Nicholas Colonna
 * FE 522
 * Assignment 2
 * Problem 5
 */

#include "std_lib_facilities.h"

//function copies C-style string into memory it allocates on the free store
char* strdup(const char* q){
    int len=0;
    while(q[len]){  //loop to find length of C-string
        len++;
    }

    char *p = new char[len];
    for(int i=0; i<=len; i++){  //loop to copy C-string to memory
        p[i] = q[i];
    }
    return p;
}

//finds the first occurence of the C-style string x in s
char* findx(const char* s, const char* x) {
    const char *position = s;   //keep track of where search match started
    const char *val = x;    //make a copy of x for checking

    while (*s && *val) {    //while both strings are not at end
        if (*s == *val) {   //if both characters are equal, keep checking
            s++;
            val++;
        }else{  //else, move deeper into string s and reset search helpers
            s++;
            position = s;
            val = x;
        }
    }
    if (*s=='\0' && *val) {     //if at the end of string s and not end of val, didn't find x
        position = "C-style string x was not found in s.";     //string says its not found
    }

    return (char *)position;
}

//compares C-style strings. Returns negative number if s1 is lexicographically before s2,
// zero if s1 equals s2, and positive number if s1 is lexicographically after s2
int strcmp(const char* s1, const char* s2){
        while(*s1 == *s2 && *s1 != '\0' && *s2 != '\0'){    //loop until one of the strings reaches an end
            s1++;
            s2++;
        }

        if(*s1 == '\0' && *s2 == '\0'){     //zero if equal
            return 0;
        }else if(*s1 > *s2){    //positive s1 lexicographically after s2
            return 1;
        }else{
            return -1;   //negative s1 lexicographically before s2
        }
}

int main()
{
    //testing of strdup function
    const char q[] = "asdf";
    char* p = strdup(q);
    cout << "q: " << q << ", p: " << p << endl;

    //testing of findx function
    const char x[] = "spoon";
    const char s[] = "teaspoon";
    cout << "Test findx (true): " << findx(s, x) << endl;
    char* test = findx(x, s);
    cout << "Test findx (false): " << test << endl;

    //testing strcmp
    cout << "Test strcmp (equal): " << strcmp("abc", "abc") << endl;
    cout << "Test strcmp (before): " << strcmp("greater", "less") << endl;
    cout << "Test strcmp (after): " << strcmp("less", "greater") << endl;

    keep_window_open();
    return 0;
}
