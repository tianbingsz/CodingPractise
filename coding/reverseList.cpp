/*
Reverse a singly linked list.

Example:

Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
Follow up:

A linked list can be reversed either iteratively or recursively. Could you implement both?
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// O(N), 4 ms, 100%
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr;
        ListNode *cur = head;
        while (cur) {
            auto next = cur->next;
            cur->next = prev; // connect cur to prev
            prev = cur; cur = next;
        }
        return prev;
    }
};

// O(N), 4 ms, 100%
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *tail = nullptr;
        auto h = head;
        while (h) {
            auto node = new ListNode(h->val);
            node->next = tail;
            tail = node;
            h = h->next;
        }
        return tail;
    }
};

// O(N), 4 ms, 100%, Recursive
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto p = reverseList(head->next);
        // tail of reverseList is head->next
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
};
