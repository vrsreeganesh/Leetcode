// including header-files
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <locale>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <vector>

// hash-deinfes
#define PRINTSPACE  std::cout << "\n\n\n\n" << std::endl;
#define PRINTLINE   std::cout << "----------------------------------------------" << std::endl;

// borrowing from namespace std
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using std::format;

// vector printing function
template<typename T>
void fPrintVector(vector<T> input){
    for(auto x: input) cout << x << ",";
    cout << endl;
}

template<typename T>
void fPrintMatrix(vector<T> input){
    for(auto x: input){
        for(auto y: x){
            cout << y << ",";
        }
        cout << endl;
    }
}


/* ====================================================

==================================================== */ 


int fRules(vector< vector<int> >& board, 
           int row, int col){

    //setup
    int row_curr;
    int col_curr;
    int num_live_neighbours = 0;
    int selfstatus = board[row][col];

    for(int i = -1; i <=1; ++i){
        for(int j = -1; j<= 1; ++j){

            // finding current row and column
            row_curr = row +i;
            col_curr = col +j;

            // continuing if same element
            if (row_curr == row && col_curr == col) continue;

            // continueing for edge cases
            if (row_curr <0                 || \
                row_curr >= board.size()    ||\
                col_curr < 0                || \
                col_curr >= board[0].size()) continue;

            // 

            // checking if neighbour is live or not
            if (board[row_curr][col_curr] == 1)
                ++num_live_neighbours;
        }
    }

    // the wild case where the current cell is dead and numneighbrs = 3
    if (selfstatus == 0 && num_live_neighbours == 3)        return 1;
    if (selfstatus == 0) return 0;

    // checking life-rule conditions
    if (selfstatus == 1 && num_live_neighbours < 2)         return 0;
    else if (selfstatus == 1 && num_live_neighbours < 4)    return 1;
    else if (selfstatus == 1 && num_live_neighbours > 3)    return 0;

}


// main-file
int main(){

    // input-configuration
    vector< vector<int> > board;
    board.push_back({0,1,0});
    board.push_back({0,0,1});
    board.push_back({1,1,1});
    board.push_back({0,0,0});
    

    // setup
    auto x = board;
    int statustoadd;

    // going through the elements
    for(int i = 0; i<board.size(); ++i){
        for(int j = 0; j<board[0].size(); ++j){

            // updating cell based on rules
            statustoadd = fRules(board, i, j);

            // adding status to x
            x[i][j] = statustoadd;
        }
    }

    // copying results back
    std::copy(x.begin(), x.end(), board.begin());




    // return
    return(0);
}