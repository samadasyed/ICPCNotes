/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        //let's make a pointer 1 that moves two steps ahead
        //let's make another pointer 2 that moves only 1 step ahead
        //this would be like tortise and the hare 
        //I need help with the implementation

        ListNode* slow = head; 
        ListNode* fast = head; 

        while (fast != nullptr && fast->next != nullptr){
            slow = slow->next; 
            fast = fast->next->next; 
        }
        return slow;
    }
};

//Given the head of a singly linked list, return the middle node of the linked list.
//Input: head = [1,2,3,4,5]
//Output: [3,4,5]
//Explanation: The middle node of the list is node 3.
