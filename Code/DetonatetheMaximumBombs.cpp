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
    vector<vector<int>> bombs   {
        {1,2,3},
        {2,3,1},
        {3,4,2},
        {4,5,3},
        {5,6,4}
    };

    // setup
    unordered_map<int, vector<int>> treemap;

    auto checkOverlap   = [&treemap](const vector<int>& source,
                                    const vector<int>& destination,
                                    const int& source_index,
                                    const int& destination_index){

        auto relative_vector        {vector<double>{static_cast<double>(source[0] - destination[0]), 
                                                 static_cast<double>(source[1] - destination[1])}};
        auto dist_between_centers   {std::sqrt(std::inner_product(relative_vector.begin(),
                                                                  relative_vector.end(),
                                                                  relative_vector.begin(),
                                                                  0.00))};
        // dist_between_centers = std::sqrt(dist_between_centers);

        // adding to hashmap
        if (dist_between_centers <= source[2]){
            if (treemap.find(source_index) == treemap.end())        {treemap[source_index] = vector<int>{destination_index};}
            else                                                    {treemap[source_index].push_back(destination_index);}    
        }
        if(dist_between_centers <= destination[2]){
            if (treemap.find(destination_index) == treemap.end())   {treemap[destination_index] = vector<int>{source_index};}
            else                                                    {treemap[destination_index].push_back(source_index);}
        }
        
        return;

    };

    // going through the combinations
    for(int i = 0; i<bombs.size(); ++i){
        for(int j = i+1; j<bombs.size(); ++j){
            checkOverlap(bombs[i], bombs[j], i, j);
        }
    }

    // building dfs
    int finaloutput    {-1};
    std::function<void(vector<int>&, int, int&)> 
    dfs   = [&dfs,
            &treemap](vector<int>&    pathsofar,
                    int            currindex,
                    int&           finaloutput)
    {


        // sending it back if its already visited
        if (std::find(pathsofar.begin(), pathsofar.end(), currindex) != pathsofar.end())    {return;}

        // adding current-element to path
        pathsofar.push_back(currindex);
        finaloutput = finaloutput > (int)pathsofar.size() ? finaloutput : (int)pathsofar.size();

        // movign to the rest 
        for(const auto& x: treemap[currindex])  {dfs(pathsofar, x, finaloutput);}

        // returning
        return;

    };


    // calling the function
    for(int i = 0; i<bombs.size(); ++i) {
        vector<int> temp;
        dfs(temp, i, finaloutput);
    }

    // printing the final-output
    cout << format("final-output = {}\n",finaloutput);

    // return
    return(0);
    
}