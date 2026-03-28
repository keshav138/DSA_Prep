#include <bits/stdc++.h>
using namespace std;

// subsequence print all 

void sub(int left, vector<int>&arr, vector<int>&curr_lis){
      if(left >= arr.size()){
            for(auto i : curr_lis){
               cout<<i<<" ";
            }
            cout<<endl;
            return;
         }

      curr_lis.push_back(arr[left]);
      sub(left+1, arr, curr_lis);
      curr_lis.pop_back();
      sub(left+1, arr, curr_lis);
}


// / subsequence sum

void ssub(int left, int main_sum, int sum, vector<int>&arr, vector<int>&curr_list){
   if(left == arr.size()){
      if(main_sum == sum){
         for(auto i: curr_list){
            cout<<i<<" ";
         }
         cout<<endl;
      }
      return;
   }

   curr_list.push_back(arr[left]);
   sum += arr[left];

   ssub(left+1, main_sum, sum, arr, curr_list);

   curr_list.pop_back();
   sum -= arr[left];

   ssub(left+1, main_sum, sum, arr, curr_list);

}


// subsequence sum only first one

bool fssub(int idx, int main_sum , int curr_sum, vector<int>& arr, vector<int>&curr_list){
   // checking if index has reached the end
   if(idx == arr.size()){
      // checking if main sum and curr summ is the same
      if(curr_sum == main_sum){
         // iterate over it
         for(auto i: curr_list) cout<<i<<" ";
         cout<<endl;
         // return true
         return true;
      }
      // return false because sum didnt match and idx has reached arr length
      return false;
   }

   curr_list.push_back(arr[idx]);
   curr_sum += arr[idx];
   
   if(fssub(idx+1, main_sum, curr_sum, arr, curr_list) == true){
      return true;
   }

   curr_list.pop_back();
   curr_sum -= arr[idx];

   if(fssub(idx+1, main_sum, curr_sum, arr, curr_list) == true){
      return true;
   }

   return false;

}


int cssub(int idx, int main_sum, int curr_sum, vector<int>& arr,vector<int>&curr_list){

   if(idx == arr.size()){
      if(main_sum == curr_sum) return 1;
      return 0;
   }

   curr_list.push_back(arr[idx]);
   curr_sum += arr[idx];

   int taken = cssub(idx+1, main_sum, curr_sum, arr, curr_list);
   
   curr_list.pop_back();
   curr_sum -= arr[idx];

   int leftout = cssub(idx+1, main_sum, curr_sum, arr, curr_list);

   return taken + leftout;

   
}

int main(){
   vector<int> arr = {1,2,1};
   vector<int> curr_list;

   int main_sum = 2;

   // sub(left, arr, curr_lis);
   // ssub(0, main_sum, 0, arr, curr_list);
   // fssub(0, main_sum, 0, arr, curr_list);

   cout<<"Total subsequence's that satisfy the condition: "<< cssub(0, main_sum, 0, arr, curr_list);
   
}