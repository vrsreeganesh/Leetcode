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
void foo(const vector<vector<char>>&                  board,
         const int                                      p,
         const int                                      curr_tid,
         const string&                                  targetword,
         bool&                                          found,
         vector<int>                                    pathsofar,
         std::function<int(const int&, const int&)>     tid,
         std::function<int(const int)>                  row,
         std::function<int(const int)>                  col){

    // if found is done
    if (found == true)                                                                      {return;}                   

    // returning if tid is beyond the bounds
    if (curr_tid >= (board.size() * board[0].size()) )                                         {return;}

    // calculating curr-row and col
    const auto rowcurr    {row(curr_tid)};  if (rowcurr < 0 || rowcurr >= board.size())     {return;}
    const auto colcurr    {col(curr_tid)};  if (colcurr < 0 || colcurr >= board[0].size())  {return;}

    // check: duplicate tid in path
    if (std::find(pathsofar.begin(), pathsofar.end(), curr_tid) != pathsofar.end())         {return;}

    // check: target-char vs curr-char
    char curr_char              {board[rowcurr][colcurr]};
    char charweresearchingfor   {targetword[p]};
    if (curr_char != charweresearchingfor)                                                  {return;}

    // adding to path
    pathsofar.push_back(curr_tid);                                              

    // checking if we've reached the end
    if (pathsofar.size() == targetword.size())    {found = true; return;}

    // moving into the neighbours
    foo(board, p+1, tid(rowcurr, colcurr+1), targetword, found, pathsofar, tid, row, col);  // moving right
    foo(board, p+1, tid(rowcurr-1, colcurr), targetword, found, pathsofar, tid, row, col);  // moving up
    foo(board, p+1, tid(rowcurr, colcurr-1), targetword, found, pathsofar, tid, row, col);  // moving left
    foo(board, p+1, tid(rowcurr+1, colcurr), targetword, found, pathsofar, tid, row, col);  // moving down

    // returning 
    return;
}


int main(){

    // starting timer
    Timer timer;
    
    // setup
    vector<vector<char>> board  {
        {'a','b','c'},
        {'a','e','d'},
        {'a','f','g'}
    };


    vector<string> words  {"abcdefg","gfedcbaaa","eaabcdgfa","befa","dgc","ade"};
    
    // setup
    std::function<int(const int&, const int&)>  tid = [&board](const int row, const int col) {
        if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size())    {return std::numeric_limits<int>::max();}
        return row* static_cast<int>(board[0].size()) + col ;
    };
    std::function<int(const int)>               row = [&board](const int tid){
        if (tid < 0 || tid > board.size() * board[0].size())                       {return std::numeric_limits<int>::max();}
        return tid/static_cast<int>(board[0].size()); 
    };
    std::function<int(const int)>               col = [&board](const int tid){
        if (tid < 0 || tid > board.size() * board[0].size())                        {return std::numeric_limits<int>::max();}
        return tid%static_cast<int>(board[0].size());
    };

    // printing
    vector<string> finaloutput;
    for(const auto& targetword: words){
        
        // flag for finding the word
        bool found  {false};
        
        // launching from every coordinate
        for(int i = 0; i<board.size() && found == false; ++i){
            for(int j = 0; j<board[0].size() && found == false; ++j){
                vector<int> pathsofar;
                foo(board, 0, tid(i, j), targetword, found, pathsofar, tid, row, col);
            }
        }    

        // adding to final output
        if (found)  {finaloutput.push_back(targetword);}
    }

    // printing the final-output
    PRINTSPACE
    cout << format("finaloutput = {}\n", finaloutput);

    // return
    return(0);
    
}