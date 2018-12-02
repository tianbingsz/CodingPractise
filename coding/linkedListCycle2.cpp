/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

Note: Do not modify the linked list.

Solution: Two Pointers
1. slow and fast, slow move one step, fast move two steps,
if slow meet with fast, there is a cycle
2. slow = head, fast = meeting point
   slow and fast move one step and will meet at the position where cycle starts
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
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr || head->next == nullptr) return nullptr;
        auto slow = head;
        auto fast = head;
        bool cycle = false;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                cycle = true; break;
            }
        }
        if (!cycle) return nullptr;
        slow = head; // cycle meet at fast
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
