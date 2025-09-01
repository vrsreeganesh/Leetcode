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

// recursion function
void foo(int                horizontalindex,
         int                verticalindex,
         string             digits,
         string             runningstring,
         vector<string>&    finalOutput,
         unordered_map<char, vector<string>>& charToLetter)
{
    
    // adding current to running sum
    runningstring += charToLetter[digits[verticalindex]][horizontalindex];
    
    // sending it back
    if (verticalindex == digits.size()-1)   {finalOutput.push_back(runningstring); return;}
    
    // running recursion on different sub-paths
    for(int j = 0; j < charToLetter[digits[verticalindex+1]].size(); ++j)
        foo(j, verticalindex+1,digits, runningstring, finalOutput, charToLetter);
    
    // returning
    return;
}

int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    auto digits  {string("23")};

    // trivial case
    if (digits.size()==0) {
        cout << format("final-output = {}\n", vector<string>({}));
        return 0;
    }

    // setup
    unordered_map<char, vector<string>> charToLetter;
    charToLetter['2'] = vector<string>({"a", "b", "c"});
    charToLetter['3'] = vector<string>({"d", "e", "f"});
    charToLetter['4'] = vector<string>({"g", "h", "i"});
    charToLetter['5'] = vector<string>({"j", "k", "l"});
    charToLetter['6'] = vector<string>({"m", "n", "o"});
    charToLetter['7'] = vector<string>({"p", "q", "r", "s"});
    charToLetter['8'] = vector<string>({"t", "u", "v"});
    charToLetter['9'] = vector<string>({"w", "x", "y", "z"});
        
    // going throguh each character on top level
    vector<string> finalOutput;
    for(int i = 0; i<charToLetter[digits[0]].size(); ++i)
        foo(i, 0, digits, "", finalOutput, charToLetter);

    // returning 
    cout << format("final-output = {}\n", finalOutput);

    // return
    return(0);
    
}