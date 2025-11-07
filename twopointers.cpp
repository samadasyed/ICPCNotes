#include <bits/stdc++.h> 

int main () {
    //Two pointers in the same direction (slow and fast)
    class Solution {
    public:
    void moveZeroes(vector<int>& nums) {
        //two pointers in the same direction
      int slow = 0; 
      for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0){
            int slow_num = nums[slow]; //these three lines are a swap
            nums[slow] = nums[fast];
            nums[fast] = slow_num; 
            slow++; 
                }
            }
        
        }
    };
    //Move zeros
    //input : nums = [0, 1, 0, 3, 12]
    //output: [1, 3, 12, 0, 0]
    //////////////////////////////////////////////////////////////////

    //Two pointers, using opposite side pointers
    class Solution {
    public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int s = 0; 
        int b = numbers.size()-1;

        while (s < b) {
            int two_sum = numbers[s] + numbers[b];
            if (two_sum > target){
                b--; 
            }

            if (two_sum < target){ 
                s++; 
            }
            if (two_sum == target) {
                return {s+1,b+1}; 
            }
        }
        return {};
    }
};
    //Sorted two sum
    //input : nums = [2, 7, 11, 15], target = 9; 
    //output: [1, 2] sum of 2 and 7
    //////////////////////////////////////////////////////////////////



    return 0; 
}