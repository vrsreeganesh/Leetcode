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
#include <unordered_set>


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
    string beginWord            {"hit"};
    string endWord              {"cog"};
    vector<string> wordList     {
        "hot","dot","dog","lot","log"
    };
    
    // returning error if endword is not in wordhlist
    if (std::find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
        cout << format("final-output = 0\n");
        return 0;
    }

    // setup
    unordered_map<string, std::set<string> > neighbours;

    auto calculatedistances = [](const string a, const string b){
        auto numdiffs   {0};
        for(int i = 0; i<a.size(); ++i) {if (a[i] != b[i])   {++numdiffs;}}
        if (numdiffs == 0)              {return 0;}
        else if (numdiffs == 1)         {return 1;}
        else                            {return std::numeric_limits<int>::max();}
    };

    // starting again
    vector<string> candidates   {beginWord};
    for(const auto x: wordList) {if (x!=endWord) candidates.push_back(x);}
    vector<string> nextgencandidates    {};

    vector<string> recruiters           {{endWord}};
    vector<string> nextgenrecruiters    {};

    // going through the loop
    auto count   {1};
    auto runningcondition   {true};
    auto foundpath          {false};
    
    while(runningcondition){
        // increasing count
        ++count;

        // comparing distance between candidates and recruiters
        for(const auto candidate: candidates){

            auto shortestpath   {std::numeric_limits<int>::max()};
            for(const auto& recruiter: recruiters)
                shortestpath    = std::min(shortestpath, calculatedistances(candidate, recruiter));

            // adding to next-generation of recruiters if diff == 1
            if (shortestpath == 1){
                nextgenrecruiters.push_back(candidate);         // adding to next gen
                if (candidate == beginWord) {foundpath = true; runningcondition = false;}
            }
            else if (shortestpath == std::numeric_limits<int>::max()){
                nextgencandidates.push_back(candidate);
            }
        }

        // rewriting history
        int prevnumcandidates   = candidates.size();
        int nexnumcandidates    = nextgencandidates.size();
        candidates  = nextgencandidates; nextgencandidates.clear();
        recruiters  = nextgenrecruiters; nextgenrecruiters.clear();

        // evaluating running condition
        if (prevnumcandidates == nexnumcandidates)  {runningcondition = false;}

    }

    // setting up final output
    if (!foundpath)  {count = 0;}
    
    // printing final-output
    cout << format("final-output = {}\n", count);
    

    // return
    return(0);
    
}