// including header-files
#include <algorithm>
#include <bitset>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
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


/* ====================================================

==================================================== */ 


// main-file
int main(){

    // setting up input
    std::vector< std::vector<int> > matrix;
    // matrix.push_back(std::vector<int>{1,2,3,4});
    // matrix.push_back(std::vector<int>{5,6,7,8});
    // matrix.push_back(std::vector<int>{9,10,11,12});

    matrix.push_back(std::vector<int>{1,2,3});
    matrix.push_back(std::vector<int>{4,5,6});
    matrix.push_back(std::vector<int>{7,8,9});

 
    // setup
    int t_edge = 0;
    int b_edge = matrix.size()-1;
    int l_edge = 0;
    int r_edge = matrix[0].size()-1;
    int row;
    int col;
    vector<int> finalOutput;

    bool runcondition = true;
    while(runcondition){

        // printing top row
        row = t_edge;
        for(col = l_edge; col<=r_edge; ++col)
            finalOutput.push_back(matrix[row][col]);

        // cout << "\t (after top row)     = "; fPrintVector(finalOutput);

        // printing right column
        col = r_edge;
        for(row = t_edge+1; row <= b_edge-1; ++row)
            finalOutput.push_back(matrix[row][col]);
        
        // cout << "\t (after right col)   = "; fPrintVector(finalOutput);

        // printing bottom row (do this only if they're different)
        if (b_edge != t_edge){
            row = b_edge;
            for(col = r_edge; col >= l_edge; --col) 
                finalOutput.push_back(matrix[row][col]);
            
            // cout << "\t (after bottom row)  = "; fPrintVector(finalOutput);
        }
        

        // printing left column
        if (l_edge != r_edge){
            col = l_edge;
            for(row = b_edge-1; row >= t_edge+1; --row)
                finalOutput.push_back(matrix[row][col]);
            
            // cout << "\t (after left col)    = "; fPrintVector(finalOutput);
        }

        // updating boundaries
        ++t_edge; --b_edge; 
        ++l_edge; --r_edge;

        // checking if exitcondition has been met
        if (t_edge > b_edge || l_edge > r_edge)
            runcondition = false;

    }

    // printing finaloutput
    cout << "finalOutput = "; fPrintVector(finalOutput);




    // return
    return(0);
}