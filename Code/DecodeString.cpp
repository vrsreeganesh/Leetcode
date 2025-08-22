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

// hash-deinfes
#define PRINTSPACE  std::cout << "\n\n\n\n" << std::endl;
#define PRINTLINE   std::cout << "-----------------" << std::endl;

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

void fPrintLinkedList(ListNode* root){
    if (root == nullptr) return;
    cout << root->val << ", ";
    fPrintLinkedList(root);
    return;
}

template<typename T>
void fPrintContainer(T input){
    for(auto x: input) cout << x << ", ";
    cout << endl;
    return;
}

struct StopWatch
{
    std::chrono::time_point<std::chrono::high_resolution_clock> startpoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> endpoint;
    std::chrono::duration<long long, std::nano>                 duration;
    
    // constructor
    StopWatch()     {startpoint = std::chrono::high_resolution_clock::now();}
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
};


// main-file ===================================================================
int main(){
    
    // input- configuration
    string s    {"100[leetcode]"};

    // running
    std::stack<char>    mystack;                                                        // stack
    string              temp;                                                           // temporary string used for decoding
    int                 repcount    {1};                                                // used for decoding

    // going through the inputs
    for(int i = 0; i<s.size(); ++i){

        if(s[i] != ']')     {mystack.push(s[i]);}                                       // pushing characters to stack until we arrive at "]"
        else{
            temp = "";                                                                  // initializing temporary string
            while(mystack.top() != '[') {                                               // expanding mini-string until we arrive at "["
                temp = mystack.top() + temp;
                mystack.pop();                                                      
            }

            mystack.pop();                                                              // removing "["
            
            // calculating the repcount
            string numberasstring = "";
            while(mystack.size() != 0 && 
                  mystack.top() - '0' >= 0 && '9' - mystack.top() >= 0) 
            {
                numberasstring = mystack.top() + numberasstring;
                mystack.pop();
            }
            repcount = std::stoi(numberasstring);

            // mini-decoding
            int multitempsize = repcount * temp.size();                                 // calculating size after multiplication
            for(int j = 0; j<multitempsize; ++j) {                                      // filling up the stack with decoded content
                mystack.push(temp[j%temp.size()]);
            }
        }
    }
    
    // creating the final output
    string finaloutput;
    while(mystack.size()){
        finaloutput = mystack.top() + finaloutput; 
        mystack.pop();
    }

    // printing the final output 
    cout << format("finaloutput = {}\n", finaloutput);

    // return
    return(0);
    
}