#include <bits/stdc++.h> 
using namespace std;

bool binarySearch(vector<int> sortedArray, int target) {
	
	int left = 0; 
	int right = sortedArray.size()-1; 
	
	while (left <= right) {
        int mid = left + (right - left) /2; //make sure this is in the loop
		if (sortedArray[mid] == target) {
			return true; 
		}
		else if (sortedArray[mid] > target) {
			right = mid;
		}
		else { //sortedArray[mid] < target
			left = mid; 
		}		
	}
	return false; 		
}

int main () {
	int target = 7;
	vector<int> sortedArray = {1, 3, 4, 6, 7, 10, 11};
	bool isthere = binarySearch(sortedArray, target);
    if (isthere) {
        return 1; 
    }
    else {
        return 0; 
    }
}