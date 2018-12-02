/*
Given a singly linked list L: L0→L1→…→Ln-1→Ln,
reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…

You may not modify the values in the list's nodes, only nodes itself may be changed.

Example 1:

Given 1->2->3->4, reorder it to 1->4->2->3.
Example 2:

Given 1->2->3->4->5, reorder it to 1->5->2->4->3.

Solution: L = {L0, L1, L2, L3}
1. find mid to partition the list into left [L0 L1] and [L2, L3]
2. reverse(right)  = [L3, L2]
3. merge(left, right) alternatively = {L0 L3 L1 L2}
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 0 ms, 100%
class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return;
        auto mid = getMiddle(head);
        auto right = reverse(mid->next);
        mid->next = nullptr;
        merge(head, right);
    }

private:
    /*{L0, L1} merge {L3, L2} => L0 L3 L1 L2*/
    void merge(ListNode *h1, ListNode *h2) {
        if (h1 == nullptr || h2 == nullptr) return;
        ListNode dumy(INT_MIN);
        auto tail = &dumy;
        bool flip = false;
        while (h1 && h2) {
            if (!flip) {
                tail->next = h1; tail = h1;
                h1 = h1->next;
            } else {
                tail->next = h2; tail = h2;
                h2 = h2->next;
            }
            flip = !flip;
        }
        tail->next = h1 ? h1 : h2;
    }

    ListNode *getMiddle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto slow = head;
        auto fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode *reverse(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto right = reverse(head->next);
        head->next->next = head;
        head->next = nullptr;
        return right;
    }
};
