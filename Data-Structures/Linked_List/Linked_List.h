// linked_list/linked_list.h
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

// ---------------------------
// 구조체 정의
// ---------------------------
typedef struct ListNode {
    int item;
    struct ListNode *next;
} ListNode;

typedef struct LinkedList {
    ListNode *head;
    int size;
} LinkedList;

// ---------------------------
// 함수 프로토타입 선언
// ---------------------------

// 초기화
void list_init(LinkedList *ll);

// 노드 삽입 (index 위치에 item 삽입)
int insertNode(LinkedList *ll, int index, int item);

// 노드 삭제 (index 위치 삭제)
int removeNode(LinkedList *ll, int index);

// 인덱스로 노드 찾기
ListNode *findNode(LinkedList *ll, int index);

// 홀수 아이템 뒤로 보내기
void moveOddItemsToBack(LinkedList *ll);

// 짝수 아이템 뒤로 보내기
void moveEvenItemsToBack(LinkedList *ll);

// 삽입하면서 정렬
int insertSortedLL(LinkedList *ll, int item);

// pivot 기준으로 나누기
void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList);

// 최대값을 맨 앞으로 보내기
int moveMaxToFront(ListNode **ptrHead);

// 재귀를 통한 뒤집기
void RecursiveReverse(ListNode **ptrHead);

// 교차로 병합
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

// 디버그용 출력 (선택 사항)
void printList(LinkedList *ll);

void removeAllItems(LinkedList *ll);

#endif // LINKED_LIST_H