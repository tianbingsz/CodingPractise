/*
Given a linked list, determine if it has a cycle in it.
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 4 ms, 100%
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return false;
        auto slow = head;
        auto fast = head->next;
        while (fast && fast->next) {
            if (slow == fast) return true;
            slow = slow ->next;
            fast = fast->next->next;
        }
        return false;
    }
};
