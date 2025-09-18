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
int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    auto p1      {vector<int>{0, 0}};
    auto p2      {vector<int>{5, 0}};
    auto p3      {vector<int>{5, 5}};
    auto p4      {vector<int>{0, 5}};
    
    // setup
    auto finaloutput    {false};
    auto center     = [&p1](auto p){
        return vector<int>{p[0] - p1[0], p[1] - p1[1]};
    };
    auto addvectors = [](auto p00, auto p01){
        return vector<int>{p00[0] + p01[0], p00[1] + p01[1]};
    };

    // changing the coordinate
    auto p1_centered    {center(p1)};
    auto p2_centered    {center(p2)};
    auto p3_centered    {center(p3)};
    auto p4_centered    {center(p4)};

    // checking if its parallelogram 
    auto parallelogram_check    {false};
    vector<int> first_arm, second_arm;
    if (p4_centered == addvectors(p2_centered, p3_centered))        {
        parallelogram_check = true;
        first_arm           = p2_centered;
        second_arm          = p3_centered;
    }
    else if (p3_centered == addvectors(p2_centered, p4_centered))   {
        parallelogram_check = true;
        first_arm           = p2_centered;
        second_arm          = p4_centered;
    }
    else if (p2_centered == addvectors(p3_centered, p4_centered))   {
        parallelogram_check = true;
        first_arm           = p3_centered;
        second_arm          = p4_centered;
    }

    // perpendicular check
    auto perpendicular_check    {false};
    auto inner_product  = std::inner_product(first_arm.begin(), first_arm.end(),
                                            second_arm.begin(),
                                            0);
    perpendicular_check     = inner_product == 0 ? true : false;

    // length check
    auto length_check           {false};
    auto first_arm_length   {std::accumulate(first_arm.begin(),
                                            first_arm.end(),
                                            0,
                                            [](auto acc, auto argx){ return acc + argx * argx;})};
    auto second_arm_length   {std::accumulate(second_arm.begin(),
                                            second_arm.end(),
                                            0,
                                            [](auto acc, auto argx){ return acc + argx * argx;})};
    length_check    = first_arm_length == second_arm_length ? true : false;
    if (first_arm_length == 0)  {length_check = false;}

    // performing final output
    if (parallelogram_check && perpendicular_check && length_check) {finaloutput = true;}


    // printing
    cout << format("parallelogram_check = {}\n", parallelogram_check);
    cout << format("perpendicular_check = {}\n", perpendicular_check);
    cout << format("length_check        = {}\n", length_check);   
    cout << format("final-output        = {}\n", finaloutput);

    // return
    return(0);
    
}