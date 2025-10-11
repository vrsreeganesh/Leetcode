// including header-files
#include <algorithm>
#include <unordered_set>
#include <bitset>
#include <climits>
#include <cstddef>
#include <iostream>
#include <limits>
#include <map>
#include <new>
#include <stdlib.h>
#include <unordered_map>
#include <vector>
#include <set>
#include <numeric>
#include <functional>


// hash-deinfes
#define PRINTSPACE  std::cout << "\n\n\n\n" << std::endl;
#define PRINTLINE   std::cout << "==============================================" << std::endl;

// borrowing from namespace std
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::unordered_map;
using std::map;
using std::format;
using std::deque;
using std::pair;
using std::min;
using std::max;

// vector printing function
template<typename T>
void fPrintVector(vector<T> input){
    for(auto x: input) cout << x << ",";
    cout << endl;
}

template<typename T>
void fpv(vector<T> input){
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

template<typename T, typename T1>
void fPrintHashmap(unordered_map<T, T1> input){
    for(auto x: input){
        cout << format("[{},{}] | ", x.first, x.second);
    }
    cout <<endl;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void fPrintBinaryTree(TreeNode* root){
    // sending it back
    if (root == nullptr) return;
    
    // printing
    PRINTLINE
    cout << "root->val = " << root->val << endl;
    
    // calling the children
    fPrintBinaryTree(root->left);
    fPrintBinaryTree(root->right);
    
    // returning
    return;
    
}

void fPrintLinkedList(string    prefix,
                      ListNode* root){
    if (root == nullptr) return;
    cout << prefix;
    std::function<void(ListNode*)> runlinkedlist = [&runlinkedlist](ListNode* root){
        if (root == nullptr) return;
        cout << root->val << " -> ";
        runlinkedlist(root->next);
    };
    runlinkedlist(root);
    cout << "|" << endl;
    return;
}

template<typename T>
void fPrintContainer(T input){
    for(auto x: input) cout << x << ", ";
    cout << endl;
    return;
}

struct Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> startpoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> endpoint;
    std::chrono::duration<long long, std::nano>                 duration;
    
    // constructor
    Timer()         {startpoint = std::chrono::high_resolution_clock::now();}
    void start()    {startpoint = std::chrono::high_resolution_clock::now();}
    void stop()     {endpoint   = std::chrono::high_resolution_clock::now(); fetchtime();}
    
    void fetchtime(){
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endpoint - startpoint);
        cout << format("{}  nanoseconds \n", duration.count());
    }
    void fetchtime(string stringarg){
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endpoint - startpoint);
        cout << format("{} took {}  nanoseconds \n", stringarg, duration.count());
    }
    void measure(){
        auto temp = std::chrono::high_resolution_clock::now();
        auto nsduration  = std::chrono::duration_cast<std::chrono::nanoseconds>(temp - startpoint);
        auto msduration  = std::chrono::duration_cast<std::chrono::microseconds>(temp - startpoint);
        auto sduration   = std::chrono::duration_cast<std::chrono::seconds>(temp - startpoint);
        cout << format("{} nanoseconds | {} microseconds | {} seconds \n", 
            nsduration.count(), msduration.count(), sduration.count());
    }
    ~Timer(){
        measure();
    }
};

// main-file ===================================================================
int main(){

    // starting timer
    Timer timer;
    
    // input-configuration
    auto    heights     {std::vector<std::vector<int>>{
        {1,2,2,3,5},
        {3,2,3,4,4},
        {2,4,5,3,1},
        {6,7,1,4,5},
        {5,1,1,2,4}
    }};

    // setup
    std::vector<int>    tidList;
    auto    finaloutput     {std::vector<std::vector<int>>()};

    // lambda for calculating tid
    auto    fetchtid    =   [&heights](const int row, const int col){
        if (row < 0 || col < 0) throw std::runtime_error("row, col < 0");
        return col + row * heights[0].size();
    };

    // building marking table
    auto    visitingTable   {std::vector<std::vector<int>>(
        heights.size(),
        std::vector<int>(heights[0].size(), 0)
    )};

    // beginning search from pacific
    auto    pacific_pipe    {std::deque<std::vector<int>>()};

    // adding to pacific pipe before running bfs
    for(auto row = 0; row < heights.size(); ++row){
        pacific_pipe.push_back(std::vector<int>({row, 0}));
    }   
    for(auto col = 1; col < heights[0].size(); ++col){
        pacific_pipe.push_back(std::vector<int>(   {0, col}  ));
    }

    auto    checkIfUpstream =   [&heights](
        const   auto&   curr_row,
        const   auto&   curr_col,
        const   auto&   next_row,
        const   auto&   next_col){

        // checking if either coordinates are valid
        if (curr_row < 0 || curr_row >= heights.size())     {return false;}
        if (curr_col < 0 || curr_col >= heights[0].size())  {return false;}
        if (next_row < 0 || next_row >= heights.size())     {return false;}
        if (next_col < 0 || next_col >= heights[0].size())  {return false;}

        // checking difference in value
        return heights[next_row][next_col]  >=  heights[curr_row][curr_col];
    };

    // running bfs from 
    while(pacific_pipe.size()!=0)
    {
        // popping front
        auto    curr    {pacific_pipe.front()}; pacific_pipe.pop_front();
        auto&   row     {curr[0]};
        auto&   col     {curr[1]};

        // ERROR-CHECK: checking if it is already visited
        const   auto    tid     {fetchtid(row, col)};
        if(std::find(tidList.begin(),
                     tidList.end(),
                     tid) != tidList.end())               {continue;}

        // adding to visit-list
        tidList.push_back(tid);

        // marking to dptable
        visitingTable[row][col] +=  1;

        // adding the neighbours to the list
        if(checkIfUpstream(row, col, row, col+1))   {pacific_pipe.push_back(std::vector<int>({row, col+1}));}
        if(checkIfUpstream(row, col, row-1, col))   {pacific_pipe.push_back(std::vector<int>({row-1, col}));}
        if(checkIfUpstream(row, col, row, col-1))   {pacific_pipe.push_back(std::vector<int>({row, col-1}));}
        if(checkIfUpstream(row, col, row+1, col))   {pacific_pipe.push_back(std::vector<int>({row+1, col}));}
    }


    // creating atlantic pipe
    auto&   atlantic_pipe   {pacific_pipe}; pacific_pipe.clear();
    tidList.clear();

    // filling up atlantic pipe
    for(auto    row = 0; row < heights.size(); ++row)
        atlantic_pipe.push_back({row, static_cast<int>(heights[0].size() - 1)});
    for(auto    col = 0; col < heights[0].size(); ++col)
        atlantic_pipe.push_back({static_cast<int>(heights.size()-1), col});

    // running bfs
    while(atlantic_pipe.size() != 0)
    {
        // popping front
        auto curr   {atlantic_pipe.front()}; atlantic_pipe.pop_front();
        auto&   row     {curr[0]};
        auto&   col     {curr[1]};

        // checking if visited
        const   auto    tid     {fetchtid(row, col)};
        if (std::find(tidList.begin(),
                      tidList.end(),
                      tid) != tidList.end())    {continue;}

        // adding to tid
        tidList.push_back(tid);

        // marking the table
        visitingTable[row][col] += 2;

        // adding to final output
        if (visitingTable[row][col] == 3)
            finaloutput.push_back(std::vector<int>({row, col}));

        // adding the neighbours to the list
        if(checkIfUpstream(row, col, row, col+1))   {atlantic_pipe.push_back(std::vector<int>({row, col+1}));}
        if(checkIfUpstream(row, col, row-1, col))   {atlantic_pipe.push_back(std::vector<int>({row-1, col}));}
        if(checkIfUpstream(row, col, row, col-1))   {atlantic_pipe.push_back(std::vector<int>({row, col-1}));}
        if(checkIfUpstream(row, col, row+1, col))   {atlantic_pipe.push_back(std::vector<int>({row+1, col}));}

    }

    // printing the markes
    cout << format("final-output = {}\n", finaloutput);

    // return
    return(0);
    
}