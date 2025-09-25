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
    ~Timer(){
        measure();
    }
};

// main-file ===================================================================
int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    vector<vector<int>> points{
        {10,16},
        {2,8},
        {1,6},
        {7,12}
    };

    // setup
    vector< vector<int> > intersections;

    // sorting intervals in case they aren't
    std::sort(points.begin(), \
            points.end(), \
            [](const vector<int>& a, const vector<int>& b){
                return a[0]<b[0];});

    // pushing the first interval to the intersections list
    intersections.push_back(points[0]);
    int finaloutput = 0;

    // going through arrays one by one
    for(int i = 1; i<points.size(); ++i){

        // fetching reference to running intersection
        auto& runningInterval = intersections[intersections.size()-1];

        // fetching incoming interval
        auto incomingInterval = points[i];

        // finding intersections
        if (runningInterval[1] < incomingInterval[0]){
            // no intersection, 
            ++finaloutput; intersections.push_back(incomingInterval);
        }
        else{
            // calculating max of start-point
            runningInterval[0] = max(runningInterval[0], incomingInterval[0]);

            // calculating min of end-poitns  
            runningInterval[1] = min(runningInterval[1], incomingInterval[1]);
        }
    }

    // returning results
    cout << format("final-output = {}\n", intersections.size());

    // return
    return(0);
    
}