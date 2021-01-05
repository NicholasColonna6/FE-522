# FE 522 Spring 2019 Midterm Exam Task 2 (30 points)

1. (10 points) Overload the plus operator (operator+) so that it can be used with the Matrix class. Create two new matrices in the main() funcion, one with the dimension of A and one with the dimension of B, and test the overloaded operator with these new matrices.

2. (20 points) Overload the multiplication operator (operator*) so that it correctly implements the multiplication of a matrix by another matrix. Test the overloaded operator with different matrices.

Hint 1: Since the position(i, j) is defined like the following:
    int& position(int row, int column);
(i.e. it returns a reference to an integer), one can actually modify the elements of a matrix through it. E.g.:
    M.position(5, 5) = 10

Hint 2: To create a vector of two dimensions NxM, you should do the following:
    vector<vector<int>> v(N, vector<int>(M));

Hint 3: You do not need to use any of the previous hints to successfully complete this task.
