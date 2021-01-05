/**
 * Nicholas Colonna
 */
#include "Matrix.h"
#include "std_lib_facilities.h"

int main()
{
    cout << "Task 2:" << '\n';

    vector<vector<int>> A = {
        { 1, 5, 9, 4, 12 },
        { 7, 12, 3, 5, 8 },
        { 8, 4, 15, 9, 5 },
        { 6, 3, 12, 8, 1 }
    };

    vector<vector<int>> B = {
        { 3, 2, 9, 8 },
        { 1, 2, 3, 4 },
        { 9, 8, 7, 6 },
        { 2, 3, 4, 5 },
        { 9, 7, 5, 3 }
    };

    Matrix MA{ A };
    Matrix MB{ B };

    cout << MA << '\n' << '\n';
    cout << MB << '\n' << '\n';


    //My Two Matrices
    vector<vector<int>> myA = {     //made the matrix all '1' for the simplicity of seeing the addition
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 }
    };

    vector<vector<int>> myB = {    //made the matrix all '2' for the simplicity of seeing the addition
            { 2, 2, 2, 2 },
            { 2, 2, 2, 2 },
            { 2, 2, 2, 2 },
            { 2, 2, 2, 2 },
            { 2, 2, 2, 2 }
    };

    Matrix myMA{ myA};
    Matrix myMB{ myB};

    //More test vectors
    vector<vector<int>> t1 = {
            { 1, 2, 3},
            { 4, 5, 6}
    };

    vector<vector<int>> t2 = {
            { 7, 8},
            { 9, 10},
            { 11, 12}
    };

    Matrix test1{t1};
    Matrix test2{t2};




    //Testing addition
    cout << "A + myA = \n";
    Matrix A_add = MA + myMA;
    cout << A_add << '\n' << '\n';

    cout << "B + myB = \n";
    Matrix B_add = MB + myMB;
    cout << B_add << '\n' << '\n';

    //test to see if fail check works (addition)
    cout << "B + t1 = \n";
    Matrix fail_add = MB + test1;
    cout << fail_add << '\n';



    //Testing multiplication
    cout << "A * B = \n";
    Matrix A_B = MA * MB;
    cout << A_B << '\n' << '\n';

    cout << "myA * myB = \n";
    Matrix myA_myB = myMA * myMB;
    cout << myA_myB << '\n' << '\n';

    cout << "myA * B = \n";
    Matrix myA_B = myMA * MB;
    cout << myA_B << '\n' << '\n';

    cout << "A * myB = \n";
    Matrix A_myB = MA * myMB;
    cout << A_myB << '\n' << '\n';

    cout << "t1 * t2 = \n";
    Matrix test = test1 * test2;
    cout << test << '\n' << '\n';

    //test to see if fail check works (multiplication)
    cout << "t1 * A = \n";
    Matrix fail_mult = test1 * MA;
    cout << fail_mult << '\n';

    keep_window_open();

    return 0;
}
