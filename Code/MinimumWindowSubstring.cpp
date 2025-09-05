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
// function to convert letter to index
int fCharToIndex(char x){
    if (x >= 65 && x <=90)          {return x - 65;}
    else if (x >= 97 && x <= 122)   {return (x - 97 + (90-65+1));}
    else                            {std::cerr<<"this shouldn't happen"; return -1;}
}

// compare histograms
template<typename T>
bool fCompareHist(const vector<T>& t_hist, const vector<T>& runninghist){
    
    // going throguh the list
    for(int i = 0; i<t_hist.size(); ++i)
        if (t_hist[i] > runninghist[i])
            return false;
        
    // in case all conditions are met
    return true;
}
int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    auto s  {string("ADOBECODEBANC")};
    auto t  {string("ABC")};

    // setup
    int p1  {0};
    int p2  {0};
    vector<int> finalOutputBoundaries(2, -1);
    vector<int> t_hist(52, 0); t_hist.reserve(t_hist.size());
    vector<int> runninghist(52, 0); runninghist.reserve(runninghist.size());
    auto minlength  {std::numeric_limits<int>::max()};
    
    // setting up t-hist
    for(const auto x: t)    {++t_hist[fCharToIndex(x)];}
    
    // moving through the string
    while(p1 <= p2 && p2<s.size()){    
        
        // adding current character
        if (p2<s.size())    {++runninghist[fCharToIndex(s[p2])];}
        
        // checking if the two histograms are comparable
        while(p1<=p2 && fCompareHist(t_hist, runninghist)){
            
            auto currstringsize     {p2-p1+1};

            if (currstringsize>0 && currstringsize < minlength){
                finalOutputBoundaries   = vector<int>({p1, p2});
                minlength               = currstringsize;
            }
            
            --runninghist[fCharToIndex(s[p1])];
            ++p1;
        }
        
        // incrementing p2;
        ++p2;
        
    }
    
    // printing the final output
    string finalOutput {string(s.begin()+finalOutputBoundaries[0], s.begin() + finalOutputBoundaries[1]+1)};

    // returning
    if (finalOutputBoundaries[0] == -1 || finalOutputBoundaries[1] == -1)   {finalOutput = "";}

    // printing the final-output
    cout << format("final-output = {}\n", finalOutput);

    // return
    return(0);
    
}