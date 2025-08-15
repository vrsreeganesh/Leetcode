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
        cout << format("[{},{}] \n", x.first, x.second);
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
    ListNode* l1    = new ListNode(2);
    l1->next        = new ListNode(4);
    l1->next->next  = new ListNode(3);

    ListNode* l2    = new ListNode(5);
    l2->next        = new ListNode(6);
    l2->next->next  = new ListNode(4);

    // setup
    ListNode* traveller_1   = l1;
    ListNode* traveller_2   = l2;
    ListNode* finalOutput   = new ListNode(-1);
    ListNode* traveller_fo  = finalOutput;

    int sum                 {0};
    int carry               {0};
    int value_1             {0};
    int value_2             {0};

    // moving through the two nodes
    while(traveller_1 != nullptr || traveller_2 != nullptr){

        // adding the two numbers
        value_1 = traveller_1 == nullptr ? 0 : traveller_1->val;
        value_2 = traveller_2 == nullptr ? 0 : traveller_2->val;

        // calculating sum
        sum     = value_1 + value_2 + carry;
        if (sum >= 10) [[unlikely]]     {sum -= 10; carry = 1;}
        else           [[likely]]       {carry = 0;}

        // creating node
        traveller_fo->next  = new ListNode(sum);
        traveller_fo        = traveller_fo->next;

        // updating the two pointers
        if(traveller_1 != nullptr) [[likely]]   {traveller_1 = traveller_1->next;}
        if(traveller_2 != nullptr) [[likely]]   {traveller_2 = traveller_2->next;}
    }

    // creating a final node if carry is non-zero 
    if (carry == 1) [[unlikely]] {
        traveller_fo->next = new ListNode(carry);
    }

    // printing the final output
    traveller_fo = finalOutput->next;
    cout << format("final-output = ");
    while(traveller_fo != nullptr){
        cout << traveller_fo->val << ", ";
        traveller_fo = traveller_fo->next;
    }
    cout << "\n";

    // return
    return(0);
    
}
































