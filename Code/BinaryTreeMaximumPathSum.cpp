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
    auto root           {new TreeNode(-10)};
    root->left          = new TreeNode(9);
    root->right         = new TreeNode(20);
    root->right->left   = new TreeNode(15);
    root->right->right  = new TreeNode(7);
    

    // setup
    auto finalresult    {std::numeric_limits<int>::min()};

    // creating lambda
    std::function<int(const TreeNode*)> fFindMaxPathSum = [&fFindMaxPathSum,
                                                           &finalresult](
        const TreeNode* root){

        // checking if leaf-node
        if(root->left   == nullptr && root->right  == nullptr){

            // checking the final-result with the leaf-node value
            finalresult = finalresult > root->val ? finalresult : root->val;

            // the potential from leaf-node
            return root->val;                       
        }
        else{

            // creating potentials-vector
            vector<int> potentials;
            if (root->left)                             {potentials.emplace_back(fFindMaxPathSum(root->left));}
            if (root->right)                            {potentials.emplace_back(fFindMaxPathSum(root->right));}

            // calculating sum of left and right
            auto leftplusright   {0}; 
            for(int i = 0; i<potentials.size(); ++i)    {leftplusright += potentials[i];}

            // calculating sum of path curr with either paths
            for(int i = 0; i<potentials.size(); ++i)    {potentials[i] += root->val;}
            
            // adding curr-value alone as a candidate
            potentials.push_back(root->val);                                        

            // sending the maximum-value back
            const auto maxelement = *(std::max_element(potentials.begin(), potentials.end()));

            // path from left-curr-right
            potentials.push_back(leftplusright + root->val);                                 

            // auto temp = *(std::max_element(potentials.begin(), potentials.end()));
            const auto comparitivemax = *(std::max_element(potentials.begin(), potentials.end()));
            
            // finalresult = std::max(finalresult, maxelement);
            finalresult = finalresult > comparitivemax ? finalresult : comparitivemax;
            
            // returning the max-potential from here
            return maxelement;
        }
    };

    
    // calculating the final-result
    fFindMaxPathSum(root);

    // printing
    cout << format("final-result = {}\n", finalresult);

    // return
    return(0);
    
}