#include <bits/stdc++.h>
#include <iostream>
using namespace std;


class Solution{
    public:

    void helper(int idx, int target, vector<int>&arr, vector<int>&curr, vector<vector<int>>&answer){
        if(idx == arr.size()){
            if(target == 0){
                answer.push_back(curr);
            }
            return;
        }

        if(arr[idx] <= target){
            curr.push_back(arr[idx]);
            helper(idx, target - arr[idx],arr,  curr, answer);
            curr.pop_back();
        }

        helper(idx+1, target, arr, curr, answer);

    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target){
        vector<vector<int>> answer;
        vector<int> curr;
        
        helper(0, target, candidates, curr, answer);
        return answer;
    }

};

int main(){
    vector<int> arr = {2,3,6,7};
    int target = 7;

    Solution obj;
    vector<vector<int>> answer = obj.combinationSum(arr, target);

    for (const auto& row : answer) {
        cout << "[ ";
        for (int num : row) {
            cout << num << " ";
        }
        cout << "]\n";
    }

}