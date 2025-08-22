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
};


// function to calculate number of non-space characters
int fCalcLengthOfTempWithoutSpaces(std::vector<std::string> temp){
    int num_nonspaces = 0;
    for(auto x: temp) num_nonspaces += x.size();
    return num_nonspaces;
}

// function to calculate words formed with temp
int fCalcLengthOfTempWithSpaces(std::vector<std::string> temp){
    int num_nonspaces = 0;
    for(auto x: temp) num_nonspaces += 1+ x.size();
    return num_nonspaces-1;
}

// printing temp
void fPrintTemp(std::vector<std::string> temp){
    // printing temp
    std::cout << "temp = ";
    for(auto x: temp) std::cout << x << ",";
    std::cout << std::endl;
}

// main-file ===================================================================
int main(){
    
    // input- configuration
    auto words      = vector<string>({"This", "is", "an", "example", "of", "text", "justification."});
    auto maxWidth   {16};
    
        // setup
    std::vector<std::string> finalOutput;

    // going through strings
    int acc = 0;
    int numwords = 0;
    int currwidth = 0;
    std::vector<std::string> temp;

    for(int i = 0; i<words.size(); ++i){

        // updating temp
        temp.push_back(words[i]);       // updating words in temp

        // checking if width has been crossed
        if (fCalcLengthOfTempWithSpaces(temp) >= maxWidth || i == words.size()-1){

            // condition temp based on length
            if(fCalcLengthOfTempWithSpaces(temp)>maxWidth){
                temp.pop_back();        // last words gotta go
                --i;                    // making sure its taken care of in next iteration
            }

            // finding length of characters in temp
            int num_nonspaces = fCalcLengthOfTempWithoutSpaces(temp);

            // finding number of spaces to add
            int numspacestofill = maxWidth - num_nonspaces;

            // calculating numspots
            int numspots = temp.size()-1;

            // calculating ideal number of spaces 
            int idealnumspacesperspot;
            int remainders;
            if (numspots!=0){
                idealnumspacesperspot   = numspacestofill/numspots;
                remainders              = numspacestofill%numspots;
            }
            else{
                idealnumspacesperspot   = numspacestofill/1;
                remainders              = numspacestofill%1;
            }

            // constructing candidate string
            std::string candidate;

            // adding each word in temp to the candidate
            for(int j = 0; j < temp.size(); ++j){

                // fetching word
                auto x = temp[j];

                // adding word to candidate
                candidate += x;

                // adding spaces
                if (j!=temp.size()-1)
                    for(int var00 = 0; var00 < idealnumspacesperspot; ++var00)
                        candidate += " ";
                
                // checking if there is any remainder left
                if (remainders > 0){
                    candidate += " ";                                           // adding another space
                    --remainders;                                               // subtracting
                }
            }

            // checking if there are remaindeers
            while (remainders > 0){
                candidate += " ";                                               // adding another space
                --remainders;                                                   // subtracting
            }

            while (candidate.size()!=maxWidth)  {candidate += " ";}             // adding another space

            // appending candidate to final output
            finalOutput.push_back(candidate);

            // getting rid of everything
            if (i != words.size()-1)    {temp.clear();}
        }
    }

    // making function left justified
    std::string lastline;
    for(int i = 0; i<temp.size(); ++i){
        lastline += temp[i];
        if (i!=temp.size()-1)   {lastline += " ";}
    }

    // adding spaces until end
    while(lastline.size()!=maxWidth) {lastline += " ";}

    // replacing last line
    finalOutput[finalOutput.size()-1] = lastline;

    // return
    return(0);
    
}