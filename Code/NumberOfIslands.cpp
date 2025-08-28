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
    vector<vector<string>> grid   {
        vector<string>({"1","1","1","1","0"}),
        vector<string>({"1","1","0","1","0"}),
        vector<string>({"1","1","0","0","0"}),
        vector<string>({"0","0","0","0","0"})
    };
    
    // setup
    std::vector< std::vector<bool> > didWeVisitThisPlace;
    for(int i = 0; i<grid.size(); ++i)
        didWeVisitThisPlace.push_back(std::vector<bool>(grid[0].size(), false));
    
    // lambda to check validity 
    auto fCheckValidityOfCoordinate = [&grid](
        std::vector<int> coords){

        // spreading it out
        auto row   {coords[0]};
        auto col   {coords[1]};

        // checking validity
        if (row >= 0            && 
            row < grid.size()   && 
            col >= 0            && 
            col <grid[0].size())
            if (grid[row][col] == "1")  {return true;}

        // in case the above condition is not met
        return false;

    };

    // traversal function
    std::function<void(int, int)> fMarkThemAll = [&fMarkThemAll, 
                                                  &grid, 
                                                  &didWeVisitThisPlace,
                                                  fCheckValidityOfCoordinate](
        int row_index,
        int col_index){

        // setting up coordinates
        std::vector<int> rightCoordinate({row_index,    col_index+1});
        std::vector<int> downCoordinate{row_index+1,    col_index};

        // marking the current coordinate as visited
        didWeVisitThisPlace[row_index][col_index] = true;

        // calling the function to the right
        if (fCheckValidityOfCoordinate(rightCoordinate) == true &&\
            didWeVisitThisPlace[rightCoordinate[0]][rightCoordinate[1]] == false)
                fMarkThemAll(rightCoordinate[0], rightCoordinate[1]);

        // calling the function for the ones below
        if (fCheckValidityOfCoordinate(downCoordinate) == true && \
            didWeVisitThisPlace[downCoordinate[0]][downCoordinate[1]] == false)
                fMarkThemAll(downCoordinate[0], downCoordinate[1]);
    };


    // going through the elements
    int count = 0;
    for(int row_index = 0; row_index < grid.size(); ++row_index){
        for(int col_index = 0; col_index < grid[0].size(); ++col_index){
            // starting an exploratory course if this point has not been visited
            if (didWeVisitThisPlace[row_index][col_index] == false && \
                grid[row_index][col_index]                == "1"){
                fMarkThemAll(row_index, col_index);
                ++count;
            }
        }
    }

    // return count
    cout << format("final-output = {}\n", count);
    
    // return
    return(0);
    
}