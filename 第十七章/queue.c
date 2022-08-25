#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

static void CopyToNode(Item item, Node* pn);
static void CopyToItem(Node* pn, Item* pi);


void InitializeQueue(Queue* pq)
{
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull(Queue* pq)
{
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(Queue* pq)
{
	return pq->items == 0;
}

int QueueItemCount(Queue* pq)
{
	return pq->items;
}

bool EnQueue(Item item, Queue* pq)
{
	Node* pnew;

	if (QueueIsFull(pq))
		return false;
	pnew = (Node*)(malloc(sizeof(Node)));

	if (pnew == NULL)
	{
		fprintf(stderr, "Unble to allocate memory!\n");
		exit(1);
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew;
	else
		pq->rear->next = pnew;
	pq->rear = pnew;
	pq->items++;

	return true;
}

bool DeQueue(Item* pitem, Queue* pq)
{
	Node* pt;

	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;

	return 0;
}

void EmptyTheQueue(Queue* pq) {
	Item dummy;
	while (!QueueIsEmpty(pq))
		Dequeue(&dummy, pq);
}


static void CopyToNode(Item item, Node* pn)
{
	pn->item = item;
}

static void CopyToItem(Node* pn, Item* pi)
{
	*pi = pn->item;
}
