#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_
#include <stdlib.h>
/*
  IMPORTANT!

  As we stick to pure C, we cannot use templates. We will just asume
  some type T was previously defined.
*/

// -----------------------------------------------------------------------------
/**
 *  Linked list representation -- R2 Curs2 (Slide 8)
 */
typedef struct ListNode{
	Item elem; // Stored node value
	struct ListNode* next; // link to next node
	struct ListNode* prev; // link to prev node
} ListNode, DoubleListNode;

/**
 *  Double linked list representation -- desen Curs 3 (Slide 19)
 */
typedef struct List{
	DoubleListNode* first; // link to the first node
	DoubleListNode* last; // link to the last node
}List;
// -----------------------------------------------------------------------------

/**
 * Create a new node
 *  [input]: Item
 *  [output]: List*
 */
ListNode *createNodeDouble(Item elem) {
	// TODO: Cerinta 1a
	ListNode *node = (ListNode *) calloc(1,sizeof(ListNode));
	node->elem = elem;
	node->next = NULL;
	node->prev  = NULL;

	return node;
}

/**
 * Create a new (empty)  list  -- Silde-urile 13/14 Curs 2
 *  [input]: None
 *  [output]: List*
 */
List* createListDouble(void){
	// TODO: Cerinta 1a
	List *list = (List *) calloc(1,sizeof(List));
	list->first = NULL;
	list->last = NULL;

	return list;
}
// -----------------------------------------------------------------------------


/**
 * Determines if the list is empty
 *  [input]: List*
 *  [output]: 1 - empty/ 0 - not empty
 */
int isEmptyDouble(List *list){
	// TODO: Cerinta 1b
	if (list->first == NULL && list->last == NULL)
	{
		return 1;
	}

	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Determines if a list contains a specified element
 *  [input]: List*, Item
 *  [output]: int (1 - contains/ 0 - not contains)
 */
int containsDouble(List *list, Item elem){
	// TDOO: Cerinta 1c
	ListNode *head = list->first;
	while (head != NULL)
	{
		if (head->elem == elem)
		{
			return 1;
		}
		head = head->next;
	}
	return 0;
}
// -----------------------------------------------------------------------------


/**
 * Insert a new element in the list at the specified position.
 * Note: Position numbering starts with the position at index zero
 *  [input]: List*, Item, int
 *  [output]: void
 */
void insertAtDouble(List* list, Item elem, int pos){

	// Guard against young player errors
	if(list == NULL) return;

	// TODO: Cerinta 1d
	if(pos < 0) return;
	if (list->first == NULL && pos != 0) return;
	ListNode *head = list->first;
	int contor = 0;
	while (head != NULL)
	{
		head = head->next;
		contor++;
	}
	if (contor < pos) return;

	if (pos == 0)
	{
		head = list->first;
		
		list->first = createNodeDouble(elem);
		if (contor == 0)
		{
			list->last = list->first;
			return;
		}
		list->first->next = head;
		head->prev = list->first;
		return;
	}
	
	ListNode *toBeAdded = createNodeDouble(elem);

	if (contor == pos)
	{
		toBeAdded->prev = list->last;
		toBeAdded->next = NULL;
		list->last->next = toBeAdded;
		list->last = toBeAdded;
		return;
	}

	

	head = list->first;
	for (int i = 0; i < pos - 1; i++)
	{
		head = head->next;
	}
	
	toBeAdded->next = head->next;
	toBeAdded->prev = head;
	head->next->prev = toBeAdded;	
	head->next = toBeAdded;		

}
// -----------------------------------------------------------------------------


/**
 * Delete the first element instance form a list.
 *  [input]: List*, Item
 *  [output]: void
 */
void deleteOnceDouble(List *list, Item elem){
	// Guard against young player errors
	if(list == NULL) return;

	//TODO: Cerinta 1e
	if (list->first == NULL || list->last == NULL)
	{
		return;
	}
	
	if (list->first == list->last)
	{
		if (list->first->elem == elem)
		{
			free(list->first);
			list->first = NULL;
			list->last = NULL;
		}
		return;
	}
	ListNode *head = list->first;
	while (head != NULL && head->elem != elem)
	{
		head = head->next;
	}
	if (head == list->first)
	{
		head->next->prev = NULL;
		list->first = head->next;
		free(head);
		return;
	}
	if (head == list->last)
	{
		head->prev->next = head->next;
		list->last = head->prev;
		free(head);
		return;
	}
	
	if (head != NULL)
	{
		head->prev->next = head->next;
		head->next->prev = head->prev;
		free(head);
		return;
	}
	
}
// -----------------------------------------------------------------------------


/**
 * Compute list length
 *  [input]: List*
 *  [output]: int
 */
int lengthDouble(List *list){
	// Guard against young player errors
	if(list == NULL) return 0;

	// TODO: Cerinta 1f
	ListNode *head = list->first;
	int contor = 0;
	while (head!= NULL)
	{
		contor++;
		head = head->next;
	}
	
	return contor;
}
// -----------------------------------------------------------------------------



/**
 * Destroy a list.
 *  [input]: List*
 *  [output]: void
 */
List* destroyListDouble(List* list){
	// Guard against young player errors
	if(list == NULL) return NULL;

	//TODO: Cerinta 1g
	ListNode *head = list->first;
	while (head != NULL)
	{
		list->first = head;
		head = head->next;
		free(list->first);
	}
	free(list);
	
	return NULL;
}
// -----------------------------------------------------------------------------


#endif //_DOUBLE_LINKED_LIST_H_
