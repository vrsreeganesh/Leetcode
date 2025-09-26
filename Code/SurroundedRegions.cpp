// including header-files
#include <algorithm>
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
    
    // input- configuration
    auto board  {std::vector<std::vector<char>>{
        {'X','X','X','X'},
        {'X','O','O','X'},
        {'X','X','O','X'},
        {'X','O','X','X'}
    }};
    
    // setup
    std::deque<vector<int>> pipe;

    // going from left to right
    for(int col = 0; col < board[0].size(); ++col)
        if(board[0][col] == 'O')    {pipe.push_back({0, col});}

    // going from top to bottom
    for(int row = 0; row < board.size(); ++row)
        if(board[row][board[0].size()-1] == 'O')   
            pipe.push_back({row, static_cast<int>(board[0].size())-1});

    // going from right to left 
    for(int col = board[0].size()-1; col >= 0 && board.size() > 1; --col)
        if(board[board.size()-1][col] == 'O')
            pipe.push_back({static_cast<int>(board.size())-1, col});

    // going from top to bottom
    for(int row = board.size()-1; row >= 0; --row)
        if(board[row][0] == 'O')    {pipe.push_back({row, 0});}
    
    // writing the visited places
    vector<vector<int>> registerVector;

    // 
    while(pipe.size() != 0){

        // fetching the front
        auto    front_value     {pipe.front()}; pipe.pop_front();
        const   auto&   row     {front_value[0]};
        const   auto&   col     {front_value[1]};

        // checking bounds
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size())    {continue;}

        // checking if the token is already in register
        if (std::find(registerVector.begin(),
                    registerVector.end(),
                    front_value)  != registerVector.end())    {continue;}

        // checking if current-point is an X
        if(board[row][col] == 'X')                              {continue;}

        // adding to register
        registerVector.push_back(front_value);

        // adding the neighbours
        pipe.push_back({row, col+1});
        pipe.push_back({row-1, col});
        pipe.push_back({row, col-1});
        pipe.push_back({row+1, col});
        
    }

    // creating a board of full ones
    for(auto row = 0; row < board.size(); ++row)
        std::for_each(board[row].begin(),
                        board[row].end(),
                        [](auto& argx){argx= 'X';});
    
    // filling it with zeros
    for(const auto& argx: registerVector)
        board[argx[0]][argx[1]]    = 'O';

    // printing the matrix
    fPrintMatrix(board);

    // return
    return(0);
    
}