// including header-files
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
    vector<int> nums    {13,16,49,4,56,64,83,35,20,73,53,67,73,73,17,28,20,16,55,16,20,66,13,46,9,14,52,70,46,66,40,21,5,88,48,21,21,44,27,56,75,58,57,15,27,4,51,77,17,21,65,17,62,84,71,78,10,67,49,8,47,55,41,86,43,48,69,58,62,27,38,24,12,82,38,62,82,32,29,27,38,37,78,9,74,90,64,16,37,22,37,46,20,47,31,16,81,28,82,39,86,59,11,78,12,13,71,49,69,1,37,24,79,32,25,67,42,30,16,23,51,66,72,20,11,90,34,81,10,86,51,68,10,62,59,33,49,30,81,69,80,79,54,78,87,44,40,47,78,44,30,23,41,89,35,6,88,79,14,10,27,54,83,36,78,82,51,1,48,28,72,34,41,32,47,32,42,3,25,78,28,37,27,77,32,83,29,56,86,80,50,59,44,51,25,41,18,83,62,4,16,80,72,7,34,21,81,15,20,35,15,46,55,81,2,36,70,87,52,19,76,18,27,81,19,78,36,6,84,32,27,7,70,67,87,90,37,75,80,72,60,68,6,72,12,90,83,20,42,36,62,45,49,45,56,51,66,48,30,49,58,9,4,56,53,30,22,7,43,23,89,46,81,61,37,78,30,9,55,43,76,65,68,64,31,1,80,39,72,45,37,88,54,23,89,13,68,26,75,86,82,69,15,25,57,38,89,70,47,4,7,11,57,64,10,73,15,16,58,5,39,60,86,50,1,85,7,40,37,58,57,52,2,13,14,73,83,29,35,76,24,55,52,75,74,38,59,73,36,90,66,61,74,74};
    int k               {77};

    // setup 
    unordered_map<int, int> histogram;
    int count   {0};

    // go through list
    for(int i = 0; i<nums.size(); ++i){
        
        // fetching current value
        int curr    {nums[i]};
        int comp    {k - curr};

        // updating histogram
        if (histogram.find(comp) == histogram.end() || histogram[comp] == 0)
        {
            // in case where complement hasn't even been entered
            if (histogram.find(curr) != histogram.end())    {++histogram[curr];}
            else                                            {histogram[curr] = 1;}
        }
        else if(histogram[comp] > 0) 
        {
            --histogram[comp];
            ++count;
        }
    }

    // printing the count
    cout << format("count = {} \n", count);

    // return
    return(0);
    
}
