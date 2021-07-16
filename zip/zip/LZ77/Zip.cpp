#include "Zip.h"
#include <iostream>
using namespace std;
#include <assert.h>
#include <map>

struct IntervalSolution
{
	ush code;         // 区域编号
	uch extraBit;     // 扩展码
	ush interval[2];  // 该区间中包含多少个数字
};

/*************************************************************/
// 距离区间码
static IntervalSolution distInterval[] = {
	{ 0, 0, { 1, 1 } },
	{ 1, 0, { 2, 2 } },
	{ 2, 0, { 3, 3 } },
	{ 3, 0, { 4, 4 } },
	{ 4, 1, { 5, 6 } },
	{ 5, 1, { 7, 8 } },
	{ 6, 2, { 9, 12 } },
	{ 7, 2, { 13, 16 } },
	{ 8, 3, { 17, 24 } },
	{ 9, 3, { 25, 32 } },
	{ 10, 4, { 33, 48 } },
	{ 11, 4, { 49, 64 } },
	{ 12, 5, { 65, 96 } },
	{ 13, 5, { 97, 128 } },
	{ 14, 6, { 129, 192 } },
	{ 15, 6, { 193, 256 } },
	{ 16, 7, { 257, 384 } },
	{ 17, 7, { 385, 512 } },
	{ 18, 8, { 513, 768 } },
	{ 19, 8, { 769, 1024 } },
	{ 20, 9, { 1025, 1536 } },
	{ 21, 9, { 1537, 2048 } },
	{ 22, 10, { 2049, 3072 } },
	{ 23, 10, { 3073, 4096 } },
	{ 24, 11, { 4097, 6144 } },
	{ 25, 11, { 6145, 8192 } },
	{ 26, 12, { 8193, 12288 } },
	{ 27, 12, { 12289, 16384 } },
	{ 28, 13, { 16385, 24576 } },
	{ 29, 13, { 24577, 32768 } }
};

// 长度区间码
static IntervalSolution lengthInterval[] = {
	{ 257, 0, { 3, 3 } },
	{ 258, 0, { 4, 4 } },
	{ 259, 0, { 5, 5 } },
	{ 260, 0, { 6, 6 } },
	{ 261, 0, { 7, 7 } },
	{ 262, 0, { 8, 8 } },
	{ 263, 0, { 9, 9 } },
	{ 264, 0, { 10, 10 } },
	{ 265, 1, { 11, 12 } },
	{ 266, 1, { 13, 14 } },
	{ 267, 1, { 15, 16 } },
	{ 268, 1, { 17, 18 } },
	{ 269, 2, { 19, 22 } },
	{ 270, 2, { 23, 26 } },
	{ 271, 2, { 27, 30 } },
	{ 272, 2, { 31, 34 } },
	{ 273, 3, { 35, 42 } },
	{ 274, 3, { 43, 50 } },
	{ 275, 3, { 51, 58 } },
	{ 276, 3, { 59, 66 } },
	{ 277, 4, { 67, 82 } },
	{ 278, 4, { 83, 98 } },
	{ 279, 4, { 99, 114 } },
	{ 280, 4, { 115, 130 } },
	{ 281, 5, { 131, 162 } },
	{ 282, 5, { 163, 194 } },
	{ 283, 5, { 195, 226 } },
	{ 284, 5, { 227, 257 } },
	{ 285, 0, { 258, 258 } } };
/******************************************************************/


Zip::Zip()
: _pWin(new uch[2 * WSIZE])
, _ht(WSIZE)
, _isLast(false)
{
	_byteLenData.reserve(BUFF_SIZE);
	_distData.reserve(BUFF_SIZE);
	_flagData.reserve(BUFF_SIZE / 8);

	_byteLenInfo.resize(256 + 1 + 29);
	for (ush i = 0; i < _byteLenInfo.size(); ++i)
	{
		_byteLenInfo[i]._ch = i;
		_byteLenInfo[i]._appearCount = 0;
		_byteLenInfo[i]._len = 0;
		_byteLenInfo[i]._chCode = 0;
	}

	_distInfo.resize(30);
	for (ush i = 0; i < _distInfo.size(); ++i)
	{
		_distInfo[i]._ch = i;
		_distInfo[i]._appearCount = 0;
		_distInfo[i]._len = 0;
		_distInfo[i]._chCode = 0;
	}
}

Zip::~Zip()
{
	delete[] _pWin;
	_pWin = nullptr;
}

void Zip::Deflate(const std::string& filePath)
{
	// 1. 打开待压缩文件
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		std::cout << "待压缩文件出错" << std::endl;
		return;
	}

	// 2.计算文件的大小，小于三个字节不压缩
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	if (fileSize <= MIN_MATCH)
	{
		std::cout << "文件太小，不压缩" << std::endl;
		fclose(fIn);
		return;
	}

	// 3.读取一个窗口的数据，将前两个字节数据哈希地址插入到哈希桶中
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);

	ush hashAddr = 0;
	ush matchHead = 0;
	for (ush i = 0; i < MIN_MATCH - 1; ++i)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}

	// 让压缩结果的文件与源文件名字相同
	string fileName;
	fileName = filePath.substr(0, filePath.rfind('.'));
	fileName += ".bzp";
	
	fOut = fopen(fileName.c_str(), "wb");

	string strFilePost(filePath.substr(filePath.rfind("." + 1)));
	strFilePost += "\n";
	fputs(strFilePost.c_str(), fOut);

	ush start = 0;
	uch ch = 0;
	uch bitCount = 0;

	while (lookahead)
	{
		ush curMatchLength = 0;
		ush curMatchDist = 0;
		// 4.将三个字节计算出来的哈希地址插入到哈希桶中
		// 如果匹配链的头是0的话，那么这三个字节就是第一次出现，则写入到压缩文件中
		_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);

		if (matchHead)
		{
			// 找到最长的匹配
			curMatchLength = LongestMatch(matchHead, start, curMatchDist);
		}
		if (curMatchLength < MIN_MATCH)
		{
			lookahead--;
			SaveLZ77Result(0, _pWin[start], ch, bitCount, lookahead);
			start++;
		}
		else
		{
			lookahead -= curMatchDist;

			// 保存LZ77的长度距离对，交给Huffman树进行压缩
			lookahead -= curMatchLength;

			SaveLZ77Result(curMatchDist, curMatchLength - 3, ch, bitCount, lookahead);
			// 需要将匹配到的内容往哈希表格中插入
			curMatchLength -= 1;
			while (curMatchLength)
			{
				++start;
				_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
				curMatchLength--;
			}
			++start;
		}
		
		// Lookahead就是先行缓冲区中剩余的待压缩字节的个数
		if (lookahead <= MIN_LOOKAHEAD)
		{
			FileDate(fIn, lookahead, start);
		}
	}

	if (_byteLenData.size() > 0 && _byteLenData.size() < BUFF_SIZE)
	{
		// 最后一个块不足BUFF_SIZE，导致没有压缩
		if (bitCount > 0 && bitCount < 8)
		{
			ch <<= (8 - bitCount);
			_flagData.push_back(ch);
		}
		_isLast = true;
		CompressBlock();
	}


	fclose(fIn);
	fclose(fOut);
}

void Zip::FileDate(FILE* fIn, ulg& lookahead, ush& start)
{
	if (start > MAX_DIST)
	{
		// 将数据从右窗搬移到左窗
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		start -= WSIZE;

		// 更新哈希表
		_ht.UpdateHashTable();

		// 给右窗补充数据
		if (!feof(fIn))
			lookahead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
}

ush Zip::LongestMatch(ush matchHead, ush start, ush& curMatchDist)
{
	ush maxLength = 0;
	ush limit = start > MAX_DIST ? start - MAX_DIST : 0;
	// 防止成环
	uch maxMatchCount = 255;
	do
	{
		uch* pScan = _pWin + matchHead;
		uch* pEnd = pScan + MAX_MATCH;
		uch* pStart = _pWin + start;

		ush curLength = 0;
		ush curDist = 0;

		while (pScan < pEnd && *pScan == *pStart)
		{
			++pScan;
			++pStart;
			++curLength;
		}

		curDist = start - matchHead;

		if (curLength > maxLength)
		{
			maxLength = curLength;
			curMatchDist = curDist;
		}

	} while (((matchHead = _ht.GetNext(matchHead)) > limit) && maxMatchCount--);

	return maxLength;
}

// LZ77每一步的结果:都可能是原字符，也可能是长度距离对
void Zip::SaveLZ77Result(ush dist, uch length, uch& flag, uch& bitCount, const ulg lookahead)
{
	// 如果dist为0，表示length是原字符
	// 如果dist不等于0，<length, dist>构成一个长度距离对
	flag <<= 1;
	_byteLenData.push_back(length);

	if (dist)
	{
		flag |= 1;
		// length表示长度
		_distData.push_back(dist);
	}
	++dist;
	if (8 == bitCount)
	{
		_flagData.push_back(flag);
		flag = 0;
		bitCount = 0;
	}

	// 注意：真正的zip不是等LZ77整个文件完成之后，对结果数据进行Huffman树
	// 而是进行分块压缩(因为buffer会非常大，导致字符种类多，Huffman树叶子节点非常大，平均编码会变长)
	
	if (_byteLenData.size() == BUFF_SIZE)
	{
		if (lookahead == 0)
		{
			_isLast = true;
		}
		CompressBlock();
	}
}

void Zip::ClearPreBlockInfo()
{
	for (ush i = 0; i < _byteLenInfo.size(); ++i)
	{
		_byteLenInfo[i]._appearCount = 0;
		_byteLenInfo[i]._len = 0;
		_byteLenInfo[i]._chCode = 0;
	}

	for (ush i = 0; i < _distInfo.size(); ++i)
	{
		_distInfo[i]._appearCount = 0;
		_distInfo[i]._len = 0;
		_distInfo[i]._chCode = 0;
	}
}

void Zip::CompressBlock()
{
	// 清除上次块中压缩的频次信息
	ClearPreBlockInfo();

	// 1.统计每个元素出现的次数
	StatAppearCount();

	// 2.构建Huffman树
	HuffmanTree<ElemInfo> byteLenTree;
	byteLenTree.CreateHuffmanTree(_byteLenInfo, ElemInfo());

	HuffmanTree<ElemInfo> distTree;
	distTree.CreateHuffmanTree(_distInfo, ElemInfo());

	// 3.根据范式Huffman树来生成编码
	GenerateCodeLen(byteLenTree.GetRoot(), _byteLenInfo);
	GenerateCode(_byteLenInfo);

	GenerateCodeLen(distTree.GetRoot(), _distInfo);
	GenerateCode(_distInfo);

	// 4.保存解压缩需要用到的位长信息
	WriteCodeLen();

	// 5.压缩
	// 取出原字符或长度距离对，找出响应的编码进行压缩
	uch flag = 0;
	uch bitCount = 0;
	ush flagIdx = 0;
	ush distIdx = 0;
	uch bitInfo = 0;
	uch bitInfoCount = 0;
	for (ush i = 0; i < _byteLenData.size(); i++)
	{
		if (0 == bitCount)
		{
			flag = _flagData[flagIdx++];
			bitCount = 8;
		}

		if (flag & 0x80)
		{
			// 长度距离对
			CompressLengthDist(_byteLenData[i], _distData[distIdx++], bitInfo, bitInfoCount);
		}
		else
		{
			// 原字符
			CompressChar(_byteLenData[i], bitInfo, bitInfoCount);
		}

		flag <<= 1;
		bitCount--;
	}

	// 上述for循环压缩的是LZ77的有效数据
	// 最后位置压缩一个256作为块的标记
	CompressChar(256, bitInfo, bitInfoCount);

	if (bitInfoCount > 0 && bitInfoCount < 8)
	{
		bitInfo <<= (8 - bitInfoCount);
		fputc(bitInfo, fOut);
	}

	// 清空：LZ77 的结果的buff
	_byteLenData.clear();
	_distData.clear();
	_flagData.clear();
}

void Zip::StatAppearCount()
{
	size_t index = 0;
	size_t distIdx = 0;
	uch flag = 0;
	uch bitCount = 0;
	for (ush i = 0; i < _byteLenData.size(); ++i)
	{
		if (0 == bitCount)
		{
			flag = _flagData[index++];
			bitCount = 8;
		}

		if (flag & 0x80)
		{
			// 找到对应的长度区间码
			_byteLenInfo[GetIntervalCodeIndex(_byteLenData[i])]._appearCount++;
			_distInfo[GetIntervalCodeIndex(_distData[distIdx++])]._appearCount++;
		}
		else
		{
			_byteLenInfo[_byteLenData[i]]._appearCount++;
		}

		flag <<= 1;
		bitCount--;
	}

	// 块结束标记----256
	_byteLenInfo[256]._appearCount = 1;
}

ush Zip::GetIntervalCodeIndex(uch len)
{
	ush length = len + 3;
	uch size = sizeof(lengthInterval) / sizeof(lengthInterval);
	for (uch i = 0; i < size; ++i)
	{
		if (length >= lengthInterval[i].interval[0] && length <= lengthInterval[i].interval[1])
		{
			return i + 257;
		}
	}
	assert(false);
	return 0;
}
ush Zip::GetIntervalCodeIndex(ush dist)
{
	uch size = sizeof(distInterval) / sizeof(distInterval[0]);
	for (uch i = 0; i < size; ++i)
	{
		if (dist >= distInterval[i].interval[0] && dist <= distInterval[i].interval[1])
			return i;
	}
	assert(false);
	return 0;
}


void Zip::GenerateCodeLen(HuffmanTreeNode<ElemInfo>* root, vector<ElemInfo>& elemInfo)
{
	ush len = 0;
	GenerateCodeLen(root, elemInfo, len);
}
void Zip::GenerateCodeLen(HuffmanTreeNode<ElemInfo>* root, vector<ElemInfo>& elemInfo, ush len)
{
	if (nullptr == root)
		return;
	if (nullptr == root->_left && nullptr == root->_right)
	{
		elemInfo[root->_weight._ch]._len = len;
		return;
	}
	++len;
	GenerateCodeLen(root->_left, elemInfo, len);
	GenerateCodeLen(root->_right, elemInfo, len);
}

void Zip::GenerateCode(vector<ElemInfo>& codeInfo)
{
	// 1.按照编码位长为第一关键字，元素大小为第二关键字排升序
	vector<ElemInfo> temp(codeInfo);
	sort(temp.begin(), temp.end());

	// 找到第一个编码位长不等于0的元素
	ush index = 0;
	while (index < temp.size())
	{
		if (temp[index]._len)
			break;
		index;
	}
	// 2.按照范式Huffman树的规则来计算编码
	codeInfo[temp[index++]._ch]._chCode = 0;
	size_t elemCount = 1;
	while (index < temp.size())
	{
		if (temp[index]._len == temp[index - 1]._len)
		{
			codeInfo[temp[index]._ch]._chCode = codeInfo[temp[index - 1]._ch]._chCode + 1;
			elemCount++;
		}
		else
		{
			codeInfo[temp[index]._ch]._chCode = (codeInfo[temp[index - elemCount]._ch]._chCode + elemCount) << (codeInfo[temp[index]._ch]._len - codeInfo[temp[index - 1]._ch]._len);
			elemCount = 1;
		}
		++index;
	}
}

void Zip::WriteCodeLen()
{
	if (_isLast)
		fputc(1, fOut);
	else
		fputc(0, fOut);

	for (auto& e : _byteLenInfo)
	{
		fputc(e._len, fOut);
	}

	for (auto& e : _distInfo)
	{
		fputc(e._len, fOut);
	}
}

void Zip::CompressChar(ush ch, uch& bitInfo, uch& bitInfoCount)
{
	// 必须找到ch的编码
	ulg chCode = _byteLenInfo[ch]._chCode;
	ush codeLen = _byteLenInfo[ch]._len;

	Compress(chCode, codeLen, bitInfo, bitInfoCount);
}
void Zip::CompressLengthDist(uch length, ush dist, uch& bitInfo, uch& bitInfoCount)
{
	// 压缩长度
	size_t index = GetIntervalCodeIndex(length);
	ulg  chCode = _byteLenInfo[index]._chCode;
	ush codeLen = _byteLenInfo[index]._len;
	Compress(chCode, codeLen, bitInfo, bitInfoCount);

	// 压缩length多对应的额外扩展码
	chCode = length + 3 - lengthInterval[index - 257].interval[0];
	codeLen = lengthInterval[index - 257].extraBit;
	Compress(chCode, codeLen, bitInfo, bitInfoCount);

	// 压缩距离
	index = GetIntervalCodeIndex(dist);
	chCode = _distInfo[distInterval[index].code]._chCode;
	codeLen = _distInfo[distInterval[index].code]._len;
	Compress(chCode, codeLen, bitInfo, bitInfoCount);

	chCode = dist - distInterval[index].interval[0];
	codeLen = distInterval[index].extraBit;
	Compress(chCode, codeLen, bitInfo, bitInfoCount);
}
void Zip::Compress(ulg chCode, ush codeLen, uch& bitInfo, uch& bitInfoCount)
{
	// 将ch的编码的chCode往压缩文件中写去
	chCode <<= (64 - codeLen);

	for (ush i = 0; i < codeLen; ++i)
	{
		bitInfo <<= 1;
		if (chCode & 0x8000000000000000)
			bitInfo |= 1;

		bitInfoCount++;
		if (8 == bitInfoCount)
		{
			fputc(bitInfo, fOut);
			bitInfo = 0;
			bitInfoCount = 0;
		}

		chCode <<= 1;
	}
}

void Zip::unDeflate(const std::string& filePath)
{
	if (filePath.substr(filePath.rfind(".") + 1) != ".bzp")
	{
		cout << "压缩文件格式不对，无法解压缩" << endl;
		return;
	}

	// 1.打开文件
	FILE* fIn = fopen(filePath.c_str(), "rb");

	string fileName(filePath.substr(0, filePath.rfind(".")));
	fileName += "_d.";
	
	string strFilePost;
	GetLine(fIn, strFilePost);
	fileName += strFilePost;

	fOut = fopen(fileName.c_str(), "wb");
	FILE* f = fopen(fileName.c_str(), "rb");
	_isLast = false;
	while (true)
	{
		if (fgetc(fIn) == 1)
			_isLast = true;
		// 1.获取编码位长
		GetDecodeLen(fIn);

		// 2. 生成解码表
		vector<DecodeTable> byteLenDecTab;
		GenerateDecodeTab(_byteLenInfo, byteLenDecTab);

		vector<DecodeTable> distDecTab;
		GenerateDecodeTab(_distInfo, distDecTab);

		// 3.解码
		uch ch = 0;
		uch bitCount = 0;
		while (true)
		{
			ush data = UNCompressSymbol(fIn, _byteLenInfo, byteLenDecTab, ch, bitCount);
			if (data < 256)
			{
				fputc(data, fOut);
				fflush(fOut);
			}
			else if (data == 256)
			{
				break;
			}
			else
			{
				ush length = lengthInterval[data - 257].interval[0];
				uch extraBitCount = lengthInterval[data - 257].extraBit;
				ush code = 0;
				ush extraData = 0;
				while (extraBitCount--)
				{
					GetNextBit(fIn, code, ch, bitCount);
					extraData <<= 1;
					if (code & 0x01)
						extraData |= 1;
				}
				length += extraData;

				// 解压缩距离
				ush distIdx = UNCompressSymbol(fIn, _distInfo, distDecTab, ch, bitCount);
				ush dist = distInterval[distIdx].interval[0];

				extraBitCount = distInterval[distIdx].extraBit;
				extraData = 0;
				code = 0;
				while (extraBitCount--)
				{
					GetNextBit(fIn, code, ch, bitCount);
					extraData <<= 1;
					if (code & 0x01)
						extraData |= 1;
				}

				dist += extraData;

				/////////////////////////
				// 按照LZ77方式还原结果
				fflush(fOut);
				fseek(f, 0 - dist, SEEK_END);
				while (length--)
				{
					uch ch = fgetc(f);
					fputc(ch, fOut);
					fflush(fOut);
				}
			}
		}
		if (_isLast)
			break;
	}
	fclose(fIn);
	fclose(fOut);
	fclose(f);
}

void Zip::GetDecodeLen(FILE* fIn)
{
	_byteLenInfo.clear();
	for (ush i = 0; i < 286; ++i)
	{
		uch len = fgetc(fIn);
		if (0 != len)
		{
			ElemInfo e;
			e._ch = i;
			e._len = len;
			_byteLenInfo.push_back(e);
		}
	}

	_distInfo.clear();
	for (ush i = 0; i < 30; ++i)
	{
		uch len = fgetc(fIn);
		if (0 != len)
		{
			ElemInfo e;
			e._ch = i;
			e._len = len;
			_distInfo.push_back(e);
		}
	}
}

void Zip::GenerateDecodeTab(vector<ElemInfo>& codeInfo, vector<DecodeTable>& decTab)
{
	// 1. 统计相同位长字符个数
	map<uch, ush> m;
	for (auto& e : codeInfo)
		m[e._len]++;

	// 2. 对读取到的位长信息进行排序
	sort(codeInfo.begin(), codeInfo.end());

	size_t index = 0;
	for (auto e : m)
	{
		DecodeTable dec;
		dec._decodeLen = e.first;
		dec._lenCount = e.second;
		if (0 == index)
		{
			dec._code = 0;
			dec._charIndex = 0;
		}
		else
		{
			DecodeTable& prev = decTab.back();
			dec._charIndex = prev._charIndex + prev._lenCount;
			dec._code = (prev._code + prev._lenCount) << (dec._decodeLen - prev._decodeLen);
		}

		decTab.push_back(dec);
		index++;
	}
}

ush Zip::UNCompressSymbol(FILE* fIn, vector<ElemInfo>& codeInfo, vector<DecodeTable>& decTable, uch& ch, uch& bitCount)
{
	ush i = 0;
	ush codeLen = decTable[0]._decodeLen;
	ush code = 0;
	while(codeLen--)
	{
		GetNextBit(fIn, code, ch, bitCount);
	}

	ush num = 0;
	while ((num = code - decTable[i]._code) >= decTable[i]._lenCount)
	{
		i++;
		ush lenGap = decTable[i]._decodeLen - decTable[i - 1]._decodeLen;
		while (lenGap--)
		{
			GetNextBit(fIn, code, ch, bitCount);
		}
	}
	num += decTable[i]._charIndex;
	return codeInfo[num]._ch;
}

void Zip::GetNextBit(FILE* fIn, ush& code, uch& ch, uch& bitCount)
{
	if (0 == bitCount)
	{
		ch = fgetc(fIn);
		bitCount = 8;
	}

	code <<= 1;
	if (ch & 0x80)
		code |= 1;

	ch <<= 1;
	bitCount--;
}


void Zip::GetLine(FILE* fIn, string& s)
{
	uch ch;
	while (!feof(fIn))
	{
		ch = fgetc(fIn);
		if ('\n' == ch)
			break;

		s += ch;
	}
}