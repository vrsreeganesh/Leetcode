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
#define PRINTLINE   std::cout << "===================================================================" << std::endl;

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
        // auto temp = std::chrono::high_resolution_clock::now();
        // auto nsduration  = std::chrono::duration_cast<std::chrono::nanoseconds>(temp - startpoint);
        // auto msduration  = std::chrono::duration_cast<std::chrono::microseconds>(temp - startpoint);
        // auto sduration   = std::chrono::duration_cast<std::chrono::seconds>(temp - startpoint);
        // cout << format("{} nanoseconds | {} microseconds | {} seconds \n", 
        //     nsduration.count(), msduration.count(), sduration.count());

        auto temp = std::chrono::high_resolution_clock::now();
        auto nsduration  = std::chrono::duration_cast<std::chrono::nanoseconds>(temp - startpoint);
        auto msduration  = std::chrono::duration_cast<std::chrono::microseconds>(temp - startpoint);
        auto milliduration = std::chrono::duration_cast<std::chrono::milliseconds>(temp - startpoint);
        auto sduration   = std::chrono::duration_cast<std::chrono::seconds>(temp - startpoint);
        PRINTLINE
        cout << format("{} nanoseconds | {} microseconds | {} milliseconds | {} seconds \n", 
            nsduration.count(), msduration.count(), milliduration.count(), sduration.count());
    }
    ~Timer(){
        measure();
    }
};

// main-file ===================================================================
void foo(const vector<int>&         candidates,
         vector<int>                pathsofar,
         vector<vector<int>>&       finaloutput, 
         const int                  currindex,
         const int&                 target,
         const vector<int>&         cumsum){

    // adding to paths ofar
    if (std::find(pathsofar.begin(), 
                  pathsofar.end(), 
                  currindex) == pathsofar.end())    {pathsofar.push_back(currindex);}
    else    {return;}

    // 
    auto sumsofar       = std::accumulate(pathsofar.begin(), 
                                         pathsofar.end(),
                                         0,
                                         [&](auto acc, auto argx){return acc + candidates[argx];});
    auto complement     {target - sumsofar};

    // making decisions based on complement
    if (complement == 0)    {
        
        vector<int> valuessofar(pathsofar.size());
        
        std::transform(pathsofar.begin(),
                       pathsofar.end(),
                       valuessofar.begin(),
                       [&](auto argx){return candidates[argx];});

        // checking if top value is same
        if (std::find(finaloutput.begin(),
                      finaloutput.end(),
                      valuessofar) == finaloutput.end())    {finaloutput.push_back(valuessofar);}

        return;
    }
    else if(complement < 0) {return;}

    // checking if it is possible to go from here
    auto maxpotentialfromhere  {cumsum[currindex] - candidates[currindex]};
    if (complement > maxpotentialfromhere)  { return;}

    // going through the rest of the indices
    for(int nextindex = currindex + 1; nextindex < candidates.size(); ++nextindex){
        foo(candidates, pathsofar, finaloutput, nextindex, target, cumsum);
    }

}

int main(){

    // starting timer
    Timer timer;
    
    // input-configuration
    auto candidates     {vector<int>{10,1,2,7,6,1,5}};
    auto target         {8};
   
    // setup
    vector<vector<int>>   finaloutput;
    vector<int>             pathsofar;

    // sorting number
    std::sort(candidates.begin(), candidates.end(), std::greater<int>());

    // creating cumulative sums
    std::vector<int> cumsum(candidates.size(), 0);
    std::partial_sum(candidates.rbegin(), candidates.rend(), cumsum.rbegin());

    // calling the function
    for(int i = 0; i < candidates.size(); ++i){
        foo(candidates, 
            pathsofar, 
            finaloutput, 
            i, 
            target, 
            cumsum);
    }

    // printing finaloutput
    cout << format("finaloutput = {}\n", finaloutput);

    // return
    return(0);
    
}