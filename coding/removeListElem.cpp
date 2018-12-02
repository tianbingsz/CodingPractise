/*
Remove all elements from a linked list of integers that have value val.

Example:

Input:  1->2->6->3->4->5->6, val = 6
Output: 1->2->3->4->5

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 16 ms, 100%
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr) return nullptr;
        ListNode dumy(INT_MIN);
        dumy.next = head;
        auto prev = &dumy;
        auto cur = head;
        while (cur) {
            auto next = cur->next;
            if (cur->val == val) {
                prev->next = next;
                delete(cur);
            } else { prev = cur; }
            cur = next;
        }
        return dumy.next;
    }
};
