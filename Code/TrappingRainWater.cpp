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
};


// main-file ===================================================================
int main(){
    
    // input- configuration
    vector<int> height  {0,1,0,2,1,0,1,3,2,1,2,1};

    // setup
    vector<int> leftmaxes(height.size(), 0);                                    // vector holding biggest-height to left
    vector<int> rightmaxes(height.size(), 0);                                   // vector holding biggest-height to the right
    int forwardindex    {0};                                                    // for maintaining forward-index
    int backwardindex   {0};                                                    // for maintaining backward-index
    int maxleft         {-1};                                                   // keeping record of biggest left
    int maxright        {-1};                                                   // keeping record of biggest right
    int finaloutput {0};                                                        // storing final output

    // building left-max
    for(int i = 1; i<height.size(); ++i){

        // calculating indices
        forwardindex    = i;                                                    // forward-index
        backwardindex   = height.size()-1-i;                                    // backward-index

        // calculating maxleft
        maxleft     = height[forwardindex-1] > maxleft ?                        
                      height[forwardindex-1] : maxleft;                         // running max-left
        leftmaxes[forwardindex]  = maxleft;                                     // storing to vector

        // calculating max right
        maxright    = height[backwardindex+1] > maxright ? 
                      height[backwardindex+1] : maxright;                       // running max-right
        rightmaxes[backwardindex] = maxright;                                   // storing to vector
    }

    // going through the array to calculate maxvolume held by each column
    for(int i = 0; i < height.size(); ++i){
        
        // finding max-height of the current column
        auto minheight      = std::min({leftmaxes[i], rightmaxes[i]});          // finding max-height of borders
        auto columnheight   = minheight - height[i];                            // subtracting to find space
        columnheight        = columnheight > 0 ? columnheight : 0;              // in case curr-height > max-height
        finaloutput         += columnheight;                                    // accumlating to water content
    }

    // printing the final output
    cout << format("finaloutput = {}\n", finaloutput);

    // return
    return(0);
    
}