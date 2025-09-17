// including header-files
#include <bitset>
#include <climits>
#include <cstddef>
#include <iostream>
#include <algorithm>
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
    string word1    {"cabbba"};
    string word2    {"abbccc"};

    // setup
    bool finaloutput    {false};

    // building histogram 
    unordered_map<char, int> histogram1, histogram2;
    for(const auto x: word1){
        if(histogram1.find(x) == histogram1.end())      {histogram1[x] = 1;}
        else                                            {++histogram1[x];}
    }
    for(const auto x: word2){
        if(histogram2.find(x) == histogram2.end())      {histogram2[x] = 1;}
        else                                            {++histogram2[x];}
    }

    // checking if one can be obtained from the other just using shuffling
    if (histogram1 == histogram2) {
        finaloutput = true;
        cout << format("(same histogram) finaloutput = {}\n", finaloutput);
        return 0;
    }

    // if number of keys are different
    if (histogram1.size() != histogram2.size()){
        finaloutput = false;
        cout << format("(different number of keys) finaloutput = {}\n", finaloutput);
        return 0;
    }


    // checking if keys match
    bool keysmatch  {true};
    {
        auto it_histogram1 = histogram1.begin();
        auto it_histogram2 = histogram2.begin();
        vector<char> keys1, keys2;
        while(it_histogram1 != histogram1.end()){
            keys1.push_back(it_histogram1->first);
            keys2.push_back(it_histogram2->first);
            ++it_histogram1;
            ++it_histogram2;
        }
        std::sort(keys1.begin(), keys1.end());
        std::sort(keys2.begin(), keys2.end());
        if (keys1 == keys2) {keysmatch = true;}
        else                {keysmatch = false;}
    }

    // checking if counts match
    bool countsmatch    {false};
    {
        vector<int> counts1, counts2;
        for(const auto& x: histogram1)  {counts1.push_back(x.second);}
        for(const auto& x: histogram2)  {counts2.push_back(x.second);}
        sort(counts1.begin(), counts1.end());
        sort(counts2.begin(), counts2.end());
        if (counts1 == counts2) {countsmatch = true;}
    }

    // producing the final output
    if (keysmatch && countsmatch)   {finaloutput = true;}
    else                            {finaloutput = false;}    

    // return
    return(0);
    
}
