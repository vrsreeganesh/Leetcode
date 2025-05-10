// including header-files
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ios>
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

    // input-configuration
    vector< vector<int> > matrix;
    // matrix.push_back({5,1,9,11});
    // matrix.push_back({2,4,8,10});
    // matrix.push_back({13,3,6,7});
    // matrix.push_back({15,14,12,16});

    matrix.push_back({1, 2, 3});
    matrix.push_back({4, 5, 6});
    matrix.push_back({7, 8, 9});
    

    // matrix.push_back({2,29,20,26,16,28});
    // matrix.push_back({12,27,9,25,13,21});
    // matrix.push_back({32,33,32,2,28,14});
    // matrix.push_back({13,14,32,27,22,26});
    // matrix.push_back({33,1,20,7,21,7});
    // matrix.push_back({4,24,1,6,32,34});
    

    // printing matrix before
    cout << "matrix(before) = \n";
    fPrintMatrix(matrix);
    PRINTSPACE

    // setup
    int t_edge = 0;
    int b_edge = matrix.size()-1;
    int l_edge = 0;
    int r_edge = matrix[0].size() -1;
    int temp;

    // shifting layer by layer. 
    int numlayers = (matrix.size())/2;
    
    // shifting layer by layer
    for(int i = 0; i<numlayers; ++i){

        int currwidth = r_edge - l_edge + 1;

        // checking widths
        PRINTLINE
        cout << format("t_edge = {} \n", t_edge);
        cout << format("b_edge = {} \n", b_edge);
        cout << format("l_edge = {} \n", l_edge);
        cout << format("r_edge = {} \n", r_edge);
        
        for(int j = 0; j<currwidth-1; ++j){                        
            // shifting the four elements for each 
            temp                        = matrix[t_edge][l_edge+j];
            matrix[t_edge][l_edge+j]    = matrix[b_edge-j][l_edge]; 
            matrix[b_edge-j][l_edge]    = matrix[b_edge][r_edge-j];
            matrix[b_edge][r_edge-j]    = matrix[t_edge+j][r_edge];
            matrix[t_edge+j][r_edge]      = temp;
        }

        // updating edge-parameters based on the layer we're working with
        t_edge += 1; b_edge -= 1;
        l_edge += 1; r_edge -= 1;
    }

    // printing output
    PRINTSPACE
    cout << "matrix(after) = \n";
    fPrintMatrix(matrix);



    // return
    return(0);
}