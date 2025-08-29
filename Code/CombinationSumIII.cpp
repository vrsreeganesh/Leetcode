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

void fTraverse(std::vector<int> numberPath, \
                int target, \
                int k, \
                std::vector< std::vector<int> >& finalOutput){

    // checking if length is too much
    if (numberPath.size() > k) return;

    // calculating sum so far
    int sumsofar = std::accumulate(numberPath.begin(), numberPath.end(),0);

    // number to fill
    int sumtofill = target - sumsofar;

    // if this is zero, we can add it to list and just sendn it back
    if (sumtofill == 0){
        if (numberPath.size() == k){
            if (std::find(finalOutput.begin(), 
                          finalOutput.end(), 
                          numberPath) == finalOutput.end())
                finalOutput.push_back(numberPath);                              // add if it doesn't already exist
        }
            
        return;
    } 

    // valid candidates 
    std::vector<int> candidates;
    int biggest_number = 1;
    if (numberPath.size()!=0){
        auto iter = std::max_element(numberPath.begin(), numberPath.end());
        biggest_number = *iter;
    }

    sumtofill = std::min(sumtofill, 9);
    for(int i = biggest_number; i<=sumtofill; ++i){
        // add if no on th epath so far
        if (std::find(numberPath.begin(), 
                      numberPath.end(), 
                      i) == numberPath.end())   {candidates.push_back(i);}       
    }

    // if there are no candidates, we're going back
    if (candidates.size() == 0) return;

    // trying each candidate
    std::vector<int> numberPath_local;
    for(auto x: candidates){
        // sending down each candidate route
        numberPath_local = numberPath;
        numberPath_local.push_back(x);
        fTraverse(numberPath_local, target, k, finalOutput);
    }

    // returning
    return;
}

int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    auto k  {3};
    auto n  {7};
    
    // setup
    std::vector< std::vector<int> > finalOutput;
    std::vector<int> numberPath;

    // recursion
    fTraverse(numberPath, n, k, finalOutput);
    
    // printing
    cout << format("final-output = {}\n", finalOutput);
    
    // return
    return(0);
    
}