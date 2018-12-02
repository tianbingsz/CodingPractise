/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6

Solution: Binary Search
sort lists[s, m] and lists[m+1, e]
merge the two resulting sorted lists
*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// O(MN), beat 99.98%
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return mergeHelper(lists, 0, lists.size() - 1);
    }

        if (s > e) return nullptr;
        if (s == e) return lists[s];
        int m = s + (e - s) / 2;
        auto left = mergeHelper(lists, s, m);
        auto right = mergeHelper(lists, m + 1 , e);
        return merge(left, right);
    }

    ListNode *merge(ListNode *left, ListNode *right) {
        auto l = left, r = right;
        ListNode dumy(INT_MIN);
        auto res =  &dumy;
        while (l && r) {
            if (l->val < r->val) {
                res->next = l; l = l->next;
            } else {
                res ->next = r; r = r->next;
            }
            res = res->next;
        }
        if (l == nullptr) res->next = r;
        if (r == nullptr) res->next = l;
        return dumy.next;
    }

    // compare to merge, code is elegent, but slower
    ListNode *mergeRec(ListNode *left, ListNode *right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        ListNode * head = nullptr;
        if (left->val < right->val) {
            head = left; head->next = mergeRec(left->next, right);
        } else {
            head = right; head->next = mergeRec(left, right->next);
        }
        return head;
    }
};
