////队列的声明
//#pragma once
//
//typedef int QDataType;
//
//typedef struct QNode{
//	struct QNode* next;
//	QDataType val;
//}QNode;
//
//typedef struct Queue{
//	struct QNode* head;
//	struct QNode* rear;
//	QDataType _size;//记录有效元素的个数
//}Queue;
//
////队列的实现
//
//
//#include <stdio.h>
//#include <stdbool.h>
//#include <malloc.h>
//#include <assert.h>
//#include <stdlib.h>
//
//QNode* BuyNode(int val)
//{
//	QNode* newNode = (QNode*)malloc(sizeof(QNode));
//	if (NULL == newNode)
//	{
//		assert(0);
//		return NULL;
//	}
//
//	newNode->next = NULL;
//	newNode->val = val;
//
//	return newNode;
//}
//
////队列初始化
//void QueueInit(Queue* q)
//{
//	assert(q);
//	q->head = BuyNode(0);
//	q->rear = q->head;
//	q->_size = 0;
//}
//
////队列入
//void QueuePush(Queue* q, QDataType val)
//{
//	assert(q);
//	QNode* newNode = BuyNode(val);
//	q->rear->next = newNode;
//	q->rear = newNode;
//	q->_size++;
//}
//
////判断队列是否为空
//int QueueEmpty(Queue* q)
//{
//	assert(q);
//	//if (q->head >= q->rear)
//	//{
//	//    return true;
//	//}
//
//	//return false
//	return 0 == q->_size;
//}
//
////队列出
//void QueuePop(Queue* q)
//{
//	QNode* pdelNode = NULL;
//	if (QueueEmpty(q))
//		return;
//
//	pdelNode = q->head->next;
//	q->head->next = pdelNode->next;
//	free(pdelNode);
//	q->_size--;
//
//
//	//如果此时队列为空
//	if (q->_size == 0)
//		q->rear = q->head;
//}
//
////有效元素的个数
//int QueueSize(Queue* q)
//{
//	assert(q);
//	return q->_size;
//}
//
////获取队头元素
//QDataType QueueFront(Queue* q)
//{
//	assert(!QueueEmpty(q));
//	return q->head->next->val;
//}
//
////获取队尾元素
//QDataType QueueBack(Queue* q)
//{
//	assert(q);
//	return q->rear->val;
//}
//
//
////测试代码
//void QueueTest()
//{
//	Queue q;
//	QueueInit(&q);
//
//	QueuePush(&q, 1);
//	QueuePush(&q, 2);
//	QueuePush(&q, 3);
//	QueuePush(&q, 4);
//	QueuePush(&q, 5);
//	QueuePush(&q, 6);
//	printf("Size:%d\n", QueueSize(&q));
//	printf("Front:%d\n", QueueFront(&q));
//	printf("Back:%d\n", QueueBack(&q));
//
//	QueuePop(&q);
//	QueuePop(&q);
//	QueuePop(&q);
//	printf("Size:%d\n", QueueSize(&q));
//	printf("Front:%d\n", QueueFront(&q));
//	printf("Back:%d\n", QueueBack(&q));
//
//	QueuePop(&q);
//	QueuePop(&q);
//	QueuePop(&q);
//	printf("Size:%d\n", QueueSize(&q));
//	//printf("Front:%d\n", QueueFront(&q));
//	printf("Back:%d\n", QueueBack(&q));
//
//}
//
//int main()
//{
//	QueueTest();
//	system("pause");
//	return 0;
//}



//typedef int HPDataType;
//
//int Less(int left, int right);
//int Great(int left, int right);
//
//typedef int(*PCOM)(int left, int right);
//
//typedef struct Heap{
//	HPDataType* array;
//	int capacity;
//	int size;
//	PCOM Compare;
//}Heap;
//
//
//
//
//
//#include <stdio.h>
//#include <malloc.h>
//#include <assert.h>
//#include <string.h>
//
//int HeapEmpty(Heap* hp);
//int Less(int left, int right)
//{
//	return left < right;
//}
//
//int Great(int left, int right)
//{
//	return left > right;
//}
//
////交换两个数字
//void Swap(HPDataType* left, HPDataType* right)
//{
//	*left ^= *right;
//	*right ^= *left;
//	*left ^= *right;
//}
//
//void CheckCapacity(Heap* hp)
//{
//	assert(hp);
//	//判断是否越界
//	if (hp->size >= hp->capacity)
//	{
//		int newCapacity = hp->capacity * 2;
//		//一般扩容都是两倍
//		HPDataType* newhp = (HPDataType*)malloc(sizeof(HPDataType)*newCapacity);
//
//		//申请空间成功
//		if (newhp == NULL)
//		{
//			assert(0);
//			return;
//		}
//
//		//将元素拷贝进去
//		memcpy(newhp, hp->array, hp->size*sizeof(HPDataType));
//
//		//释放旧空间
//		free(hp->array);
//		hp->array = newhp;
//		hp->capacity = newCapacity;
//	}
//}
//
//void AdjustDown(Heap* hp, int parent)
//{
//	int child = parent * 2 + 1;
//	while (child<hp->size)
//	{
//		//用child标记孩子中小的
//		//Compare可以进行比较，在上面的Less 和 Great函数替换
//		if (child + 1 < hp->size && hp->Compare(hp->array[child + 1], hp->array[child]))
//			child += 1;
//		//父母和孩子进行比较,小的话就进行交换
//		if (hp->Compare(hp->array[child], hp->array[parent]))
//		{
//			Swap(&hp->array[child], &hp->array[parent]);
//			parent = child;
//			child = parent * 2 + 1;
//		}
//		else
//		{
//			return;
//		}
//	}
//}
//
////插入时：向上调整
//void AdjustUp(Heap* hp, int child)
//{
//	int parent = (child - 1) >> 1;
//	while (child)
//	{
//		if (hp->Compare(hp->array[child], hp->array[parent]))
//		{
//			Swap(&hp->array[child], &hp->array[parent]);
//
//			child = parent;
//			parent = (child - 1) >> 1;
//		}
//		else
//		{
//			return;
//		}
//	}
//}
//
//
////创建堆
//void CreatHeap(Heap* hp, HPDataType arr[], int size, PCOM Compare)
//{
//	assert(hp);
//	hp->array = (HPDataType*)malloc(sizeof(HPDataType)*size);
//	//判断是否申请成功
//	if (NULL == hp->array)
//	{
//		assert(0);
//		return;
//	}
//
//	//接收数据
//	hp->capacity = size;
//	memcpy(hp->array, arr, sizeof(HPDataType)*size);
//	hp->size = size;
//	hp->Compare = Compare;
//
//	//调整元素的位置
//	for (int root = (size - 2) >> 1; root >= 0; root--)
//	{
//		AdjustDown(hp, root);
//	}
//}
//
////堆的插入
//void HeapPush(Heap* hp, HPDataType data)
//{
//	assert(hp);
//	//检测空间是否需要扩容
//	CheckCapacity(hp);
//	hp->array[hp->size++] = data;
//	AdjustUp(hp, hp->size - 1);
//}
//
////堆的删除
//void HeapPop(Heap* hp)
//{
//	assert(hp);
//	if (HeapEmpty(hp))
//		return;
//
//	//交换元素，Size--，最后调整元素
//	Swap(&hp->array[0], &hp->array[hp->size - 1]);
//	hp->size--;
//	AdjustDown(hp, 0);
//}
//
////获取堆顶元素
//HPDataType HeapTop(Heap* hp)
//{
//	assert(hp);
//	assert(!HeapEmpty(hp));
//	return hp->array[0];
//}
//
////有效元素个数
//int HeapSize(Heap* hp)
//{
//	assert(hp);
//	return hp->size;
//}
//
////判断堆是否为空
//int HeapEmpty(Heap* hp)
//{
//	assert(hp);
//	return 0 == hp->size;
//}
//
////堆的销毁
//void HeapDestroy(Heap* hp)
//{
//	assert(hp);
//	if (hp->array)
//	{
//		free(hp->array);
//		hp->array = NULL;
//		hp->capacity = 0;
//		hp->size = 0;
//	}
//}
//
/////
////测试
//void HeapTest()
//{
//	int array[] = { 5, 3, 8, 4, 2, 7, 6, 1, 0 };
//	Heap Hp;
//	CreatHeap(&Hp, array, sizeof(array) / sizeof(array[0]), Great);
//
//	printf("size = %d\n", HeapSize(&Hp));
//	printf("top = %d\n", HeapTop(&Hp));
//
//	HeapPop(&Hp);
//	printf("size = %d\n", HeapSize(&Hp));
//	printf("top = %d\n", HeapTop(&Hp));
//
//	HeapPush(&Hp, 9);
//	printf("size = %d\n", HeapSize(&Hp));
//	printf("top = %d\n", HeapTop(&Hp));
//
//	HeapPush(&Hp, 0);
//	printf("size = %d\n", HeapSize(&Hp));
//	printf("top = %d\n", HeapTop(&Hp));
//}
//
//
//
//#include <stdlib.h>
//
//int main()
//{
//	HeapTest();
//	system("pause");
//	return 0;
//}

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;



bool wordBreak(string s, vector<string>& wordDict) {
	unordered_set<string> word_set;
	for (auto & word : wordDict)
	{
		word_set.insert(word);
	}
	int len = s.size();

	int i = 0;
	while (i < len)
	{
		int index = 1;
		while (index < len)
		{
			string str = s.substr(i, index);
			if (word_set.count(str))
			{
				i += index;
				break;
			}
			index++;
		}
		if (index >= len)
			break;
	}
}


int main()
{
	string a = "leetcode";
	vector<string> aa{ "leet", "code" };
	if (wordBreak(a, aa))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}