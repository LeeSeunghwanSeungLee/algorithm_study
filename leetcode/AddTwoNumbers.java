/* https://leetcode.com/problems/add-two-numbers/description/ */
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode addTwoNumbers(ListNode l1, ListNode l2) {
        // given
        int beforeComplement = 0;
        ListNode ans = null;
        ListNode head = null;
        // when
        while (l1 != null || l2 != null) {
            ListNode now = new ListNode(0);
            int firstValue = (l1 != null) ? l1.val : 0;
            int secondValue = (l2 != null) ? l2.val : 0;
            int tempResult = beforeComplement + firstValue + secondValue;
            beforeComplement = tempResult >= 10 ? 1 : 0;
            int result = tempResult - beforeComplement * 10;
            now.val = result;

            if (ans == null) {
                ans = now;
                head = now;
            } else {
                head.next = now;
                head = now;
            }
            l1 = (l1 != null) ? l1.next : null;
            l2 = (l2 != null) ? l2.next : null;
        }

        if (beforeComplement != 0) {
            head.next = new ListNode(1);
        }

        return ans;
    }
}
