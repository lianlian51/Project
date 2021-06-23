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


// hashAddr: 上一个字符串计算出的哈希地址
// ch：当前字符
// 本次的哈希地址是在前一次哈希地址基础上，再结合当前字符ch计算出来的
// HASH_MASK为WSIZE-1，&上掩码主要是为了防止哈希地址越界
void HashTable::HashFunc(ush& hashAddr, uch ch) {
	hashAddr = (((hashAddr) << H_SHIFT()) ^ (ch)) & HASH_MASK;
}
ush HashTable::H_SHIFT()
{
	return (HASH_BITS + MIN_MATCH - 1) / MIN_MATCH;
}

// hashaddr:前三个字节的哈希地址
// ch：表示当前三个字节的第三个
// pos: 表示三个字节首字节在窗口的下标
// matchHead：表示在哈希表中找到的匹配链的头
void HashTable::Insert(ush& hashaddr, uch ch, ush pos, ush& matchHead)
{
	// 计算哈希地址
	HashFunc(hashaddr, ch);

	// 将匹配的头带出
	matchHead = _head[hashaddr];
	_prev[pos & HASH_MASK] = _head[hashaddr];
	_head[hashaddr] = pos;
}

ush HashTable::GetNext(ush& matchHead)
{
	return _prev[matchHead & HASH_MASK];
}

// 当先行缓冲区小于最小的缓冲区时，左窗数据会被丢弃
// 所以此时需要更新哈希表中保存的下标
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