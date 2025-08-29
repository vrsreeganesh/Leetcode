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

void foo(unordered_map<string, vector<string>>& stringtoneighbours,
         vector<string>                         pathsofar,
         bool&                                  foundpath,
         string                                 endGene,
         int&                                   finaloutput){
    
    // checking if the top of the stack has valid neighbours
    string top = pathsofar[pathsofar.size()-1];

    // checking if the current one is thef inal output
    if (top == endGene)
        finaloutput = finaloutput < pathsofar.size() ? finaloutput : pathsofar.size();

    // checking its possible next-states
    auto nextnodes = stringtoneighbours[top];

    // going depth-first
    for(auto x: nextnodes){

        // not considering if it is already in the path
        if(std::find(pathsofar.begin(), 
                     pathsofar.end(), 
                     x) != pathsofar.end()) continue;

        // updating path sof far
        auto pathsofar_temp = pathsofar;
        pathsofar_temp.push_back(x);

        // calling function do it
        foo(stringtoneighbours, pathsofar_temp, foundpath, endGene, finaloutput);
    }
}

// main-file ===================================================================
int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    string startGene        = "AACCGGTT";
    string endGene          = "AACCGGTA";
    vector<string> bank     = {"AACCGGTA"};
    
    // setup
    unordered_map<string, vector<string>> stringtoneighbours;

    // checking if endgene is in the bank
    if (std::find(bank.begin(), 
                  bank.end(), 
                  endGene) == bank.end())   {cout << format("finalOutput = -1\n");}

    // going through the bank and building neighbours
    bank.push_back(startGene);

    for(auto x: bank){

        // finding valid transactions with the other strings in the bank
        for(auto y: bank){

            // checking number of string differences between the two
            auto count = 0;
            for(int i =0; i<8; ++i) {if (x[i] != y[i]) ++count;}

            // checking count and adding to valid transactions
            if (count == 1)         {stringtoneighbours[x].push_back(y);}
        }

        // checking if this particular gene can jump to final gene
        // checking number of string differences between the two
        auto count = 0;
        for(int i =0; i<8; ++i) {if (x[i] != endGene[i]) ++count;}

        // checking count and adding to valid transactions
        if (count == 1)         {stringtoneighbours[x].push_back(endGene);}
    }

    // recursion
    vector<string>  pathsofar   {startGene};
    bool            foundpath   {false};
    int             finalOutput {-1};

    // calling the function
    foo(stringtoneighbours, pathsofar, foundpath, endGene, finalOutput);

    // returning the finaloutput
    if (finalOutput > -1) --finalOutput;

    // printing final output
    cout << format("finalOutput = {}\n", finalOutput);

    // return
    return(0);
    
}