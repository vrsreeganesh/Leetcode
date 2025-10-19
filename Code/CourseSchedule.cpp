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
    auto numCourses {3};
    vector<vector<int>> prerequisites   {
        {1,0},
        {1,2},
        {0,1}
    };

    // setup
    auto    isStartingNode      {std::vector<bool>(numCourses, true)};
    auto    finaloutput         {false};

    // building dependency tree
    unordered_map<int, std::vector<int> > dmap;
    for(const   auto&    x: prerequisites){
        // creating source-to-destination connection
        if (dmap.find(x[1]) == dmap.end())  {dmap[x[1]] = std::vector<int>({x[0]});}
        else                                {dmap[x[1]].push_back(x[0]);}

        // updating 
        isStartingNode[x[0]]    =   false;
    }

    // printing
    cout << format("isStartingNode = {}\n", isStartingNode);

    // launching seach from all non-prerequisite courses
    auto    visited     {std::vector<bool>(numCourses, false)}; 
    auto    pipe        {std::deque<int>()};

    // lambda to check if all are true
    auto    fCheckIfAllAreTrue = [&visited](){
        return std::all_of(visited.begin(), 
                           visited.end(),
                           [](const auto& argx){return argx;});
    };

    cout<< format("fCheckIfAllAreTrue = {}\n", fCheckIfAllAreTrue());
    cout << format("isStartingNode = {}\n", isStartingNode);

    // going through each course
    for(int i  = 0; i < numCourses && fCheckIfAllAreTrue() == false; ++i){
        // checking if this has prerequisites
        if (isStartingNode[i] == true){

            // creating pipe 
            pipe.clear();
            pipe.push_back(i);

            // running bfs
            while(pipe.size() != 0){

                // popping the front
                const   auto    front_value     {pipe.front()};
                pipe.pop_front();

                // printing
                cout << format("front-value = {} | pipe = {}\n", front_value, pipe);

                // checking if we've already marked this
                if (visited[front_value])       {continue;}

                // marking current node as visited
                visited[front_value]    =   true;

                // adding children to the pipe
                for(const   auto&   x: dmap[front_value])
                    pipe.push_back(x);

            }
        }
    }

    // returning 


    
    // // setup
    // vector<bool> visited(numCourses, false);
    // vector<bool> hasPrerequisite(numCourses, false);
    // unordered_map<int, vector<int>> hmap;

    // // build prerequisite list
    // for(const auto x: prerequisites){

    //     // pickign things out
    //     auto curr   {x[0]};
    //     auto prereq {x[1]};

    //     // setting the flag for non
    //     hasPrerequisite[curr]   = true;

    //     // adding to the hashmap
    //     if(hmap.find(prereq) == hmap.end())     {hmap[prereq] = vector<int>{curr};}
    //     else                                    {hmap[prereq].push_back(curr);}

    // }

    // // find no-prerequisite course
    // std::deque<int> indiceswithnoprerequisites;
    // for(int i = 0; i<numCourses;++i)
    //     if (hasPrerequisite[i]==false)  
    //         indiceswithnoprerequisites.push_back(i);

    // // start from there and flag the  
    // std::deque<int>  prev;
    // while(indiceswithnoprerequisites.size()!=0 && prev != indiceswithnoprerequisites){

    //     // storing for later comparison
    //     prev = indiceswithnoprerequisites;

    //     // popping the front
    //     auto front  {indiceswithnoprerequisites.front()};
    //     indiceswithnoprerequisites.pop_front();

    //     // launching search from "front"
    //     if (hmap.find(front) == hmap.end()) {
    //         visited[front] = true;
    //         continue;
    //     }
    //     else {
    //         visited[front] = true;
    //         auto& bruh  {hmap[front]};
    //         for(const auto& x: bruh)    {
    //             if (visited[x] == false)  {indiceswithnoprerequisites.push_back(x);}
    //             visited[x] = true;
    //         }
    //     }
    // }


    // // finalizing output
    // auto finaloutput    {true};
    // for(int i = 0; i<visited.size(); ++i)   {finaloutput = finaloutput&&visited[i];}
    // cout << format("final-output = {}\n", finaloutput);

    // return
    return(0);
    
}