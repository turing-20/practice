/*
 * @lc app=leetcode id=2 lang=cpp
 *
 * [2] Add Two Numbers
 */

// @lc code=start
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
class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int carry = 0;
        ListNode *Head = new ListNode();
        ListNode *temp = Head;
        while (l1->next && l2->next)
        {
            int a = l1->val + l2->val;
            temp->val = (a + carry) % 10;
            carry = (a + carry) / 10;
            l1 = l1->next;
            l2 = l2->next;
            temp->next = new ListNode();
            temp = temp->next;
        }
        if (carry > 0)
        {
            temp->val = carry;
            temp->next = new ListNode();
        }

        return Head;
    }
};
// @lc code=end
