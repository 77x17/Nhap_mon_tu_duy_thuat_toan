#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, totalSolutions = 0;
vector<vector<string>> solutions;

vector<bool> c, d1, d2; // columns, diagonal

void solveNQueens(int row, vector<int> &board) {
    if (row == n) {
        ++totalSolutions;
        vector<string> solution;
        solution.assign(n, string(n, '.'));
        for (int i = 0; i < n; ++i) {
            solution[i][board[i]] = 'Q';
        }
        solutions.push_back(solution);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (!c[col]&& !d1[row - col + n - 1] && !d2[row + col]) {
            board[row] = col;

            c [col]               = true;
            d1[row - col + n - 1] = true;
            d2[row + col]         = true;

            solveNQueens(row + 1, board);

            c [col]               = false;  
            d1[row - col + n - 1] = false;
            d2[row + col]         = false;
        }
    } 
} 

int main() {
    cin >> n;
    c .assign(n, false);
    d1.assign(2 * n - 1, false);
    d2.assign(2 * n - 1, false);

    vector<int> board(n, -1);
    solveNQueens(0, board);
    
    cout << totalSolutions << '\n';
    for (int i = 0; i < totalSolutions; ++i) { 
        for (const string &r : solutions[i]) {
            cout << r << '\n';
        }
        cout << '\n';
    }
    return 0;
}

