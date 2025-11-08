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