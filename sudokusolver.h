#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <iostream>
#include <list>


class SudokuSolver
{
public:
    SudokuSolver(int origin[][9]);
    void printOutSudoku(int a [][9]);
    void setSQ(int input[][9], int number, int original [][9],bool state);
    bool isSolved(int a[][9]);
    void makeZero(int a[][9]);
    void solveMatrix(int input[][9]);
private:
    int copy[9][9];
    std::list<int> possi[9][9];

};

#endif // SUDOKUSOLVER_H
