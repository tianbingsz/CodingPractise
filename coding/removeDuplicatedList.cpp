/*
Given a sorted linked list, delete all duplicates such that each element appear only once.

Example 1:

Input: 1->1->2
Output: 1->2
Example 2:

Input: 1->1->2->3->3
Output: 1->2->3

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// O(N), 8 ms, 98.40%
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto prev = head;
        auto cur = head->next;
        while (cur) {
            auto next = cur->next;
            if (prev->val == cur->val) {
                prev->next = next;
                delete(cur);
            } else { prev = cur; }
            cur = next;
        }
        return head;
    }
};
