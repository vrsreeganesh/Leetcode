// including header-files
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
#include <set>
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

/* ====================================================

==================================================== */ 


// function to convert char to integer
int fConvert(char x){
    if (x == '.') return -1;
    else {
        return static_cast<int>(x - '0');
    }
}


// main-file
int main(){

    // input-configuration
    vector< vector<char> > board;
    board.push_back({'5','3','.','.','7','.','.','.','.'});
    board.push_back({'6','.','.','1','9','5','.','.','.'});
    board.push_back({'.','9','8','.','.','.','.','6','.'});
    board.push_back({'8','.','.','.','6','.','.','.','3'});
    board.push_back({'4','.','.','8','.','3','.','.','1'});
    board.push_back({'7','.','.','.','2','.','.','.','6'});
    board.push_back({'.','6','.','.','.','.','2','8','.'});
    board.push_back({'.','.','.','4','1','9','.','.','5'});
    board.push_back({'.','.','.','.','8','.','.','7','9'});



    // basic method
    int xoffset,    yoffset;
    int row_local,  col_local;
    
    // checking row and column entries
    for(int i = 0; i < 9; ++i){

        // register for each jumn
        vector<int> rowRegister(9, 0);
        vector<int> colRegister(9, 0);
        vector<int> blockRegister(9,0);

        // going through each jumn
        for(int j = 0; j<9; ++j){

            // along the row
            int var00   = fConvert(board[i][j]);
            if (var00   != -1){
                if (++rowRegister[var00-1] > 1) cout << "FALSE! \n";
            }
            
            // down the column
            var00       = fConvert(board[j][i]);
            if (var00   !=-1){
                if (++colRegister[var00-1] > 1) cout << "FALSE! \n";
            }

            // checking block
            row_local   = j / 3;
            col_local   = j % 3;
            xoffset     = i / 3;
            yoffset     = i % 3;

            // calculating registers
            var00 = fConvert(board[3*xoffset + row_local][col_local+3*yoffset]);
            if (var00!=-1){
                // checking count
                if (++blockRegister[var00]>1) cout << "false \n";
            }
        }
    }



    



    // return
    return(0);
}