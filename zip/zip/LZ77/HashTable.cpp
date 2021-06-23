#include "HashTable.h"

HashTable::HashTable(ush size)
: _prev(new ush[size * 2])
, _head(_prev + size)
{
	memset(_prev, 0, 2 * size *sizeof(ush));
}

HashTable::~HashTable()
{
	delete _prev;
	_prev = nullptr;
	_head = nullptr;
}


// hashAddr: ��һ���ַ���������Ĺ�ϣ��ַ
// ch����ǰ�ַ�
// ���εĹ�ϣ��ַ����ǰһ�ι�ϣ��ַ�����ϣ��ٽ�ϵ�ǰ�ַ�ch���������
// HASH_MASKΪWSIZE-1��&��������Ҫ��Ϊ�˷�ֹ��ϣ��ַԽ��
void HashTable::HashFunc(ush& hashAddr, uch ch) {
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK;
}
ush HashTable::H_SHIFT()
{
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}

// hashaddr:ǰ�����ֽڵĹ�ϣ��ַ
// ch����ʾ��ǰ�����ֽڵĵ�����
// pos: ��ʾ�����ֽ����ֽ��ڴ��ڵ��±�
// matchHead����ʾ�ڹ�ϣ�����ҵ���ƥ������ͷ
void HashTable::Insert(ush& hashaddr, uch ch, ush pos, ush& matchHead)
{
	// �����ϣ��ַ
	HashFunc(hashaddr, ch);

	// ��ƥ���ͷ����
	matchHead = _head[hashaddr];
	_prev[pos & HASH_MASK] = _head[hashaddr];
	_head[hashaddr] = pos;
}

ush HashTable::GetNext(ush& matchHead)
{
	return _prev[matchHead & HASH_MASK];
}

// �����л�����С����С�Ļ�����ʱ�������ݻᱻ����
// ���Դ�ʱ��Ҫ���¹�ϣ���б�����±�
void HashTable::UpdateHashTable()
{
	for (ush i = 0; i < HASH_SIZE; ++i)
	{
		if (_head[i] <= WSIZE)
			_head[i] = 0;
		else
			_head[i] -= WSIZE;
	}

	for (ush i = 0; i < HASH_SIZE; ++i)
	{
		if (_prev[i] <= WSIZE)
			_prev[i] = 0;
		else
			_prev[i] -= WSIZE;
	}
}