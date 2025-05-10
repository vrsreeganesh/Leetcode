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


// main-file
int main(){

    // setting up input
    std::vector< std::vector<int> > matrix;
    matrix.push_back(std::vector<int>{0, 1, 2, 0});
    matrix.push_back(std::vector<int>{3, 4, 5, 2});
    matrix.push_back(std::vector<int>{1, 3, 1, 5});

    // setup
    vector<bool> rowregister(matrix.size(), false);
    vector<bool> colregister(matrix.size(), false);

    // going through matrix to put them to zeros
    for(int i = 0; i<matrix.size(); ++i){
        for(int j = 0; j < matrix[0].size(); ++j){
            // checking if current eleemnt is zero
            if (matrix[i][j] == 0){
                rowregister[i] = true;
                colregister[j] = true;
            }
        }
    }

    // filling it up with zeros
    for(int i = 0; i<matrix.size(); ++i){
        for(int j = 0; j < matrix[0].size(); ++j){
            // checking if either are zero
            if (rowregister[i]==true || colregister[j] == true)
                matrix[i][j] = 0;
        }
    }



    // return
    return(0);
}