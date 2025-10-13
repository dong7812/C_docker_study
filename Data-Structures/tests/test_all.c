// tests/test_all.c
#include <stdio.h>
#include <string.h>
#include "../test.h"
#include "../Linked_List/Linked_List.h" // 공개 헤더

void list_init(LinkedList *ll) {
    ll->head = NULL;
    ll->size = 0;
}

static void build_list(LinkedList *ll, const int *arr, int n) {
    list_init(ll);
    for (int i = 0; i < n; i++) {
        ASSERT_EQ_INT(0, insertNode(ll, ll->size, arr[i]));
    }
}

static void assert_list_equals(LinkedList *ll, const int *arr, int n) {
    ASSERT_EQ_INT(n, ll->size);
    ListNode *cur = ll->head;
    for (int i = 0; i < n; i++) {
        ASSERT_NE_NULL(cur);
        ASSERT_EQ_INT(arr[i], cur->item);
        cur = cur->next;
    }
    ASSERT_TRUE(cur == NULL); // 정확히 n개여야 함
}

// ---------- tests ----------

// 1) init
TEST(list_init_should_set_empty_state) {
    LinkedList ll;
    ll.head = (ListNode*)0x1;
    ll.size = 123;
    list_init(&ll);
    ASSERT_EQ_INT(0, ll.size);
    ASSERT_TRUE(ll.head == NULL);
}

// 2) insert: head/middle/tail & size
TEST(insert_at_head_middle_tail) {
    LinkedList ll; list_init(&ll);

    ASSERT_EQ_INT(0, insertNode(&ll, 0, 2));       // [2]
    ASSERT_EQ_INT(0, insertNode(&ll, 1, 5));       // [2,5]
    ASSERT_EQ_INT(0, insertNode(&ll, 1, 3));       // [2,3,5]
    ASSERT_EQ_INT(0, insertNode(&ll, 0, 1));       // [1,2,3,5]
    ASSERT_EQ_INT(0, insertNode(&ll, ll.size, 8));// [1,2,3,5,8]

    int expect[] = {1,2,3,5,8};
    assert_list_equals(&ll, expect, 5);
}

// 3) remove: head/middle/tail & boundary
TEST(remove_head_middle_tail_and_bounds) {
    LinkedList ll; int arr[] = {10,20,30,40};
    build_list(&ll, arr, 4);                       // [10,20,30,40]

    ASSERT_EQ_INT(-1, removeNode(&ll, -1));
    ASSERT_EQ_INT(-1, removeNode(&ll, 4));

    ASSERT_EQ_INT(0, removeNode(&ll, 0));          // rm head -> [20,30,40]
    int e1[] = {20,30,40};  assert_list_equals(&ll, e1, 3);

    ASSERT_EQ_INT(0, removeNode(&ll, 1));          // rm middle(30) -> [20,40]
    int e2[] = {20,40};     assert_list_equals(&ll, e2, 2);

    ASSERT_EQ_INT(0, removeNode(&ll, ll.size-1));  // rm tail(40) -> [20]
    int e3[] = {20};        assert_list_equals(&ll, e3, 1);

    ASSERT_EQ_INT(0, removeNode(&ll, 0));          // -> []
    ASSERT_EQ_INT(0, ll.size);
    ASSERT_TRUE(ll.head == NULL);
}

// 4) findNode out-of-range
TEST(findNode_out_of_range_should_return_null) {
    LinkedList ll; list_init(&ll);
    ASSERT_TRUE(findNode(&ll, 0) == NULL);
    int arr[] = {1,2,3}; build_list(&ll, arr, 3);
    ASSERT_TRUE(findNode(&ll, -1) == NULL);
    ASSERT_TRUE(findNode(&ll, 3) == NULL);
    ASSERT_TRUE(findNode(&ll, 2) != NULL);
}

// 5) insertSortedLL: ordered insert & no-dup
TEST(insertSortedLL_behaviour) {
    LinkedList ll; list_init(&ll);
    // 빈 리스트 삽입 → 맨앞
    ASSERT_EQ_INT(0, insertSortedLL(&ll, 5));      // [5]
    // 앞/중간/끝 삽입
    ASSERT_EQ_INT(0, insertSortedLL(&ll, 1));      // [1,5]
    ASSERT_EQ_INT(1, insertSortedLL(&ll, 3));      // [1,3,5]
    ASSERT_EQ_INT(3, insertSortedLL(&ll, 9));      // [1,3,5,9]
    // 중복 차단
    ASSERT_EQ_INT(-1, insertSortedLL(&ll, 5));     // unchanged

    int expect[] = {1,3,5,9};
    assert_list_equals(&ll, expect, 4);
}

// 6) moveOddItemsToBack: mixed/all-even/all-odd/empty/single
TEST(moveOddItemsToBack_various_cases) {
    // mixed
    {
        LinkedList ll; int a[] = {2,3,4,7,15,18};
        build_list(&ll, a, 6);
        moveOddItemsToBack(&ll); // expect evens then odds (상대 순서 보존)
        int e[] = {2,4,18,3,7,15};
        assert_list_equals(&ll, e, 6);
    }
    // all even (변화 없음)
    {
        LinkedList ll; int a[] = {2,8,18};
        build_list(&ll, a, 3);
        moveOddItemsToBack(&ll);
        int e[] = {2,8,18};
        assert_list_equals(&ll, e, 3);
    }
    // all odd (변화 없음 or 동일 순서)
    {
        LinkedList ll; int a[] = {3,5,7};
        build_list(&ll, a, 3);
        moveOddItemsToBack(&ll);
        int e[] = {3,5,7};
        assert_list_equals(&ll, e, 3);
    }
    // empty
    {
        LinkedList ll; list_init(&ll);
        moveOddItemsToBack(&ll);
        ASSERT_EQ_INT(0, ll.size);
        ASSERT_TRUE(ll.head == NULL);
    }
    // single
    {
        LinkedList ll; int a[] = {9};
        build_list(&ll, a, 1);
        moveOddItemsToBack(&ll);
        int e[] = {9};
        assert_list_equals(&ll, e, 1);
    }
}

// 7) moveEvenItemsToBack: mixed/all-even/all-odd
TEST(moveEvenItemsToBack_various_cases) {
    // 이 함수가 구현되어 있어야 합니다.
    extern void moveEvenItemsToBack(LinkedList *ll);

    // mixed
    {
        LinkedList ll; int a[] = {2,3,4,7,15,18};
        build_list(&ll, a, 6);
        moveEvenItemsToBack(&ll); // expect odds then evens
        int e[] = {3,7,15,2,4,18};
        assert_list_equals(&ll, e, 6);
    }
    // all even
    {
        LinkedList ll; int a[] = {2,4,6};
        build_list(&ll, a, 3);
        moveEvenItemsToBack(&ll);
        int e[] = {2,4,6};
        assert_list_equals(&ll, e, 3);
    }
    // all odd
    {
        LinkedList ll; int a[] = {1,3,5};
        build_list(&ll, a, 3);
        moveEvenItemsToBack(&ll);
        int e[] = {1,3,5};
        assert_list_equals(&ll, e, 3);
    }
}

// 8) removeAllItems: idempotent
TEST(removeAllItems_is_idempotent) {
    LinkedList ll; int a[] = {1,2,3,4};
    build_list(&ll, a, 4);
    removeAllItems(&ll);
    ASSERT_EQ_INT(0, ll.size);
    ASSERT_TRUE(ll.head == NULL);
    // 다시 호출해도 문제 없어야 함
    removeAllItems(&ll);
    ASSERT_EQ_INT(0, ll.size);
    ASSERT_TRUE(ll.head == NULL);
}

// 9) stability under sequence of ops
TEST(sequence_stability) {
    LinkedList ll; list_init(&ll);
    // add 0..9 at tail
    for (int i = 0; i < 10; ++i) ASSERT_EQ_INT(0, insertNode(&ll, ll.size, i));
    // remove even indices repeatedly until 5 elements left
    for (int k = 0; k < 5; ++k) {
        ASSERT_EQ_INT(0, removeNode(&ll, 0)); // remove head each time
    }
    // now should have [5,6,7,8,9]
    int e1[] = {5,6,7,8,9};
    assert_list_equals(&ll, e1, 5);

    // insert in middle
    ASSERT_EQ_INT(0, insertNode(&ll, 2, 42)); // [5,6,42,7,8,9]
    int e2[] = {5,6,42,7,8,9};
    assert_list_equals(&ll, e2, 6);

    // remove tail
    ASSERT_EQ_INT(0, removeNode(&ll, ll.size-1)); // [5,6,42,7,8]
    int e3[] = {5,6,42,7,8};
    assert_list_equals(&ll, e3, 5);
}

// 10) size consistency after many ops
TEST(size_consistency_many_ops) {
    LinkedList ll; list_init(&ll);
    const int N = 50;
    for (int i = 0; i < N; ++i) ASSERT_EQ_INT(0, insertNode(&ll, i, i));
    ASSERT_EQ_INT(N, ll.size);
    // remove every 3rd element
    int removed = 0;
    for (int i = 0; i < ll.size; ) {
        ASSERT_EQ_INT(0, removeNode(&ll, i));
        removed++;
        i += 2; // 다음 2개 건너뛰고 다시 제거 (원래 3번째 제거의 효과)
        if (i < 0) break; // 방어
    }
    ASSERT_EQ_INT(N - removed, ll.size);
}

// ---------- runner ----------
int main(void) {
    RUN_TEST(list_init_should_set_empty_state);
    RUN_TEST(insert_at_head_middle_tail);
    RUN_TEST(remove_head_middle_tail_and_bounds);
    RUN_TEST(findNode_out_of_range_should_return_null);
    RUN_TEST(insertSortedLL_behaviour);
    RUN_TEST(moveOddItemsToBack_various_cases);
    RUN_TEST(moveEvenItemsToBack_various_cases);
    RUN_TEST(removeAllItems_is_idempotent);
    RUN_TEST(sequence_stability);
    RUN_TEST(size_consistency_many_ops);
    return test_summary();
}