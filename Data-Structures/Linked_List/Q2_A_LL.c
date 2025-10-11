//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll1, ll2;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll1.head = NULL;
	ll1.size = 0;

	//Initialize the linked list 2 as an empty linked list
	ll2.head = NULL;
	ll2.size = 0;

	printf("1: Insert an integer to the linked list 1:\n");
	printf("2: Insert an integer to the linked list 2:\n");
	printf("3: Create the alternate merged linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list 1: ");
			scanf("%d", &i);
			j = insertNode(&ll1, ll1.size, i);
			printf("Linked list 1: ");
			printList(&ll1);
			break;
		case 2:
			printf("Input an integer that you want to add to the linked list 2: ");
			scanf("%d", &i);
			j = insertNode(&ll2, ll2.size, i);
			printf("Linked list 2: ");
			printList(&ll2);
			break;
		case 3:
		    printf("The resulting linked lists after merging the given linked list are:\n");
			alternateMergeLinkedList(&ll1, &ll2); // You need to code this function
			printf("The resulting linked list 1: ");
			printList(&ll1);
			printf("The resulting linked list 2: ");
			printList(&ll2);
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		case 0:
			removeAllItems(&ll1);
			removeAllItems(&ll2);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
{
    if (ll1 == NULL || ll2 == NULL) return;                 // ✨ 추가
    if (ll2->head == NULL) return;                          // ✨ 추가 (ll2 비어있으면 할 일 없음)

    LinkedList temp;
    temp.head = NULL;
    temp.size = 0;

    int size1 = ll1->size;
    int size2 = ll2->size;
    int k = (size1 < size2) ? size1 : size2;  // min(size1, size2)

    // 공통 루프: 교차로 k쌍 삽입
    for (int i = 0; i < k; i++) {
        int base = 2 * i; // temp에서 (a,b) 쌍이 차지할 시작 인덱스
        insertNode(&temp, base,     findNode(ll1, i)->item);
        insertNode(&temp, base + 1, findNode(ll2, i)->item);
    }

    // ll1이 더 길면 남은 ll1을 뒤에 붙임
    for (int i = k; i < size1; i++) {
        insertNode(&temp, temp.size, findNode(ll1, i)->item); // append
    }

    // 최종 대치 (ll1 <- temp)
    ll1->head = temp.head;
    ll1->size = temp.size;

    //  여기부터 최소 수정 포인트: ll2를 문제 요구대로 정리
    if (size1 >= size2) {
        // ll1이 더 길거나 같으면 ll2는 비워야 함
        ll2->head = NULL;
        ll2->size = 0;
    } else {
        // ll2가 더 길면, 앞의 k개는 사용됐고 나머지 tail만 남김
        // ll2의 head를 k번째 노드로 당김
        ListNode *newHead = findNode(ll2, k);    // k는 0..size2-1 범위에서 안전
        ll2->head = newHead;
        ll2->size = size2 - k;                   // 남은 개수로 사이즈 갱신
    }
}

//////////////////////////////////////////////////////////////////////////////////

// void alternateMergeLinkedList(LinkedList *ll1, LinkedList *ll2)
// {
// 	int j;
// 	LinkedList temp;
// 	temp.head = NULL;
// 	temp.size = 0;

// 	if (ll2 == NULL){
// 		return;
// 	}
// 	else
// 	{
// 		if (ll1->size == ll2->size){
// 			for(int i = 0; i < ll1->size; i++){
// 			j = insertNode(&temp, i, findNode(ll1, i)->item);
// 			j = insertNode(&temp, i+1, findNode(ll2, i)->item);
// 			}
// 			ll1->head = temp.head;
// 			ll1->size = temp.size;

// 			ll2->head = NULL;
// 			ll2->size = 0;
// 		}
// 		else if(ll1->size > ll2->size){
// 			for(int i = 0; i < ll2->size; i++){
// 				j = insertNode(&temp, i, findNode(ll1, i)->item);
// 				j = insertNode(&temp, i+1, findNode(ll2, i)->item);
// 			}

// 			for(int i = ll2->size; i<ll1->size; i++){
// 				j = insertNode(&temp, i, findNode(ll1, i)->item);
// 			}
// 			ll1->head = temp.head;
// 			ll1->size = temp.size;

// 			ll2->head = NULL;
// 			ll2->size = 0;
// 		}
// 		else{
// 			for(int i = 0; i < ll1->size; i++){
// 				j = insertNode(&temp, i, findNode(ll1, i)->item);
// 				j = insertNode(&temp, i+1, findNode(ll2, i)->item);

// 				removeNode(ll2, i);
// 			}

// 			ll1->head = temp.head;
// 			ll1->size = temp.size;
// 		}
// 	}
// }

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
