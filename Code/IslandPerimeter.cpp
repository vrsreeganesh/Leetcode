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
bool fCheckCellValidity(const vector<vector<int>>&      nums,
                        const vector<vector<bool>>&     flags,
                        vector<int>                     currposition,
                        const std::deque<vector<int>>&  pipe){

    // splitting tid into row and column
    auto& rowcurr    {currposition[0]};
    auto& colcurr    {currposition[1]};

    // checking validity
    if (rowcurr < 0 || rowcurr >= nums.size())      {return false;}
    if (colcurr < 0 || colcurr >= nums[0].size())   {return false;}

    // checking visiters register
    if (flags[rowcurr][colcurr] == true)            {return false;}

    // checking if this position is an island or water
    if (nums[rowcurr][colcurr]  == 0)               {return false;}

    // returning false if the currposition is already in the pipe
    if (std::find(pipe.begin(), 
                  pipe.end(), 
                  currposition) != pipe.end())      {return false;}

    // returning true
    return true;

}
bool fCheckBounds(const vector<vector<int>>&        nums,
                  const int                         rowcurr, 
                  const int                         colcurr){
    
    // checking validity
    if (rowcurr < 0 || rowcurr >= nums.size())      {return false;}
    if (colcurr < 0 || colcurr >= nums[0].size())   {return false;}

    // returning true
    return true;

}
void foo(const vector<vector<int>>&     nums,
         vector<vector<bool>>&          flags,
         vector<int>                    currposition,
         int&                           runningperimeter,
         std::deque<vector<int>>        pipe){

    // splitting tid into row and column
    auto rowcurr    {currposition[0]};
    auto colcurr    {currposition[1]};

    // checking if current cell has already been visited
    if (nums[rowcurr][colcurr] == 0 || flags[rowcurr][colcurr] == true) {return;}

    // setting the current to true
    flags[rowcurr][colcurr]     = true;

    // visiteds result in reduced boundaries
    auto amounttosubtract   {0};
    if(fCheckBounds(nums, rowcurr, colcurr+1) && flags[rowcurr][colcurr+1] == true)   {++amounttosubtract;}
    if(fCheckBounds(nums, rowcurr-1, colcurr) && flags[rowcurr-1][colcurr] == true)   {++amounttosubtract;}
    if(fCheckBounds(nums, rowcurr, colcurr-1) && flags[rowcurr][colcurr-1] == true)   {++amounttosubtract;}
    if(fCheckBounds(nums, rowcurr+1, colcurr) && flags[rowcurr+1][colcurr] == true)   {++amounttosubtract;}

    // unvisited cells add to boundary
    auto amounttoadd        {0};
    if(fCheckBounds(nums, rowcurr, colcurr+1) == false || (fCheckBounds(nums, rowcurr, colcurr+1) && flags[rowcurr][colcurr+1] == false) )   {++amounttoadd;}
    if(fCheckBounds(nums, rowcurr-1, colcurr) == false || (fCheckBounds(nums, rowcurr-1, colcurr) && flags[rowcurr-1][colcurr] == false) )   {++amounttoadd;}
    if(fCheckBounds(nums, rowcurr, colcurr-1) == false || (fCheckBounds(nums, rowcurr, colcurr-1) && flags[rowcurr][colcurr-1] == false) )   {++amounttoadd;}
    if(fCheckBounds(nums, rowcurr+1, colcurr) == false || (fCheckBounds(nums, rowcurr+1, colcurr) && flags[rowcurr+1][colcurr] == false) )   {++amounttoadd;}

    // updating the running perimeter
    runningperimeter += amounttoadd - amounttosubtract;

    // // if next is one, has not been visited, we add to the stack 
    if(fCheckCellValidity(nums, flags, {rowcurr, colcurr+1}, pipe))  {pipe.push_back({rowcurr, colcurr+1});}
    if(fCheckCellValidity(nums, flags, {rowcurr-1, colcurr}, pipe))  {pipe.push_back({rowcurr-1, colcurr});}
    if(fCheckCellValidity(nums, flags, {rowcurr, colcurr-1}, pipe))  {pipe.push_back({rowcurr, colcurr-1});}
    if(fCheckCellValidity(nums, flags, {rowcurr+1, colcurr}, pipe))  {pipe.push_back({rowcurr+1, colcurr});}

    // sending it back if thing is empty
    if (pipe.size() == 0)   {return;}

    // popping one from the middle
    auto frontentry = pipe.front(); pipe.pop_front();

    // calling the function on the next
    foo(nums,
        flags, 
        frontentry,
        runningperimeter,
        pipe);

}

int main(){

    // starting timer
    Timer timer;
    
    // input- configuration
    vector<vector<int>> nums    {
        {0,1,0,0},
        {1,1,1,0},
        {0,1,0,0},
        {1,1,0,0}
    };

    // setup
    vector<vector<bool>> flags(nums.size(), 
                               vector<bool>(nums[0].size(), 
                                            false));
    auto runningperimeter   {0};
    std::deque<vector<int>> pipe;

    // setup
    for(int i = 0; i<nums.size(); ++i){
        
        // finding where the number one is 
        auto it     {std::find(nums[i].begin(),
                               nums[i].end(),
                               1)};

        // continuing if there is no ones here
        if (it == nums[i].end())    {continue;}

        // finding the starting point
        int startingcol    = std::distance(nums[i].begin(), it);

        // launching a search
        foo(nums,
            flags, 
            {i,startingcol},
            runningperimeter,
            pipe);

        // breaking
        break;
    }

    // printing the final output
    cout << format("final-output = {}\n", runningperimeter);

    // return
    return(0);
    
}