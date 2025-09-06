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
string vectortostring(const vector<int>& pathsofar){
    auto temp   {string("")};
    for(int i = 0; i<pathsofar.size(); ++i)     {temp += std::to_string(pathsofar[i]);}
    return temp;
}

void foo(vector<int>            pathsofar,
         const int&             n,
         int                    curr, 
         int&                   leafcount,
         const int&             k,
         string&                finaloutput,
         bool&                  found){

    // sending it back 
    if (found == true)  {return;}

    // adding current number to pathsofar
    if (std::find(pathsofar.begin(), pathsofar.end(), curr) != pathsofar.end())  {return;}

    // adding to the path
    pathsofar.push_back(curr);

    // checking if we've reached a leaf
    if (pathsofar.size() == n)  {
        ++leafcount;
        if (leafcount == k) {
            finaloutput = vectortostring(pathsofar);
            found = true;
        }
        return;
    }

    // calling on the others
    for(int i = 1; i<=n; ++i)   {foo(pathsofar, n, i, leafcount, k, finaloutput, found);}
}

int main(){

    // starting timer
    Timer timer;
    
    // input- configuration    
    auto n  {8};
    auto k  {29805};
    
    // setup
    auto finaloutput    {string("")};
    auto found          {false};

    // building the directing block
    auto directionalblocks {vector<int>(n-1, 1)};
    for(int i = directionalblocks.size()-2; i >= 0; --i)
        directionalblocks[i] = directionalblocks[i+1] * (directionalblocks.size()-i);

    // printing
    auto startingpoint  {k/directionalblocks[0]};
    startingpoint = std::max(startingpoint, 1);

    // printing the leaf
    auto leafcount      {directionalblocks[0] * (startingpoint-1)};

    // running
    for(int i = startingpoint; i<=n; ++i){
        vector<int> pathsofar;
        foo(pathsofar, n, i, leafcount, k, finaloutput, found);
    }

    // printing the final-output 
    cout << format("final-output = {}\n", finaloutput);

    // return
    return(0);    
}