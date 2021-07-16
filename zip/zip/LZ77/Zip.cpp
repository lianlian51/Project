#include "Zip.h"
#include <iostream>
using namespace std;
#include <assert.h>
#include <map>

struct IntervalSolution
{
	ush code;         // ������
	uch extraBit;     // ��չ��
	ush interval[2];  // �������а������ٸ�����
};

/*************************************************************/
// ����������
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

// ����������
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
	// 1. �򿪴�ѹ���ļ�
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		std::cout << "��ѹ���ļ�����" << std::endl;
		return;
	}

	// 2.�����ļ��Ĵ�С��С�������ֽڲ�ѹ��
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	if (fileSize <= MIN_MATCH)
	{
		std::cout << "�ļ�̫С����ѹ��" << std::endl;
		fclose(fIn);
		return;
	}

	// 3.��ȡһ�����ڵ����ݣ���ǰ�����ֽ����ݹ�ϣ��ַ���뵽��ϣͰ��
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);

	ush hashAddr = 0;
	ush matchHead = 0;
	for (ush i = 0; i < MIN_MATCH - 1; ++i)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}

	// ��ѹ��������ļ���Դ�ļ�������ͬ
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
		// 4.�������ֽڼ�������Ĺ�ϣ��ַ���뵽��ϣͰ��
		// ���ƥ������ͷ��0�Ļ�����ô�������ֽھ��ǵ�һ�γ��֣���д�뵽ѹ���ļ���
		_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);

		if (matchHead)
		{
			// �ҵ����ƥ��
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

			// ����LZ77�ĳ��Ⱦ���ԣ�����Huffman������ѹ��
			lookahead -= curMatchLength;

			SaveLZ77Result(curMatchDist, curMatchLength - 3, ch, bitCount, lookahead);
			// ��Ҫ��ƥ�䵽����������ϣ����в���
			curMatchLength -= 1;
			while (curMatchLength)
			{
				++start;
				_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
				curMatchLength--;
			}
			++start;
		}
		
		// Lookahead�������л�������ʣ��Ĵ�ѹ���ֽڵĸ���
		if (lookahead <= MIN_LOOKAHEAD)
		{
			FileDate(fIn, lookahead, start);
		}
	}

	if (_byteLenData.size() > 0 && _byteLenData.size() < BUFF_SIZE)
	{
		// ���һ���鲻��BUFF_SIZE������û��ѹ��
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
		// �����ݴ��Ҵ����Ƶ���
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		start -= WSIZE;

		// ���¹�ϣ��
		_ht.UpdateHashTable();

		// ���Ҵ���������
		if (!feof(fIn))
			lookahead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
}

ush Zip::LongestMatch(ush matchHead, ush start, ush& curMatchDist)
{
	ush maxLength = 0;
	ush limit = start > MAX_DIST ? start - MAX_DIST : 0;
	// ��ֹ�ɻ�
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

// LZ77ÿһ���Ľ��:��������ԭ�ַ���Ҳ�����ǳ��Ⱦ����
void Zip::SaveLZ77Result(ush dist, uch length, uch& flag, uch& bitCount, const ulg lookahead)
{
	// ���distΪ0����ʾlength��ԭ�ַ�
	// ���dist������0��<length, dist>����һ�����Ⱦ����
	flag <<= 1;
	_byteLenData.push_back(length);

	if (dist)
	{
		flag |= 1;
		// length��ʾ����
		_distData.push_back(dist);
	}
	++dist;
	if (8 == bitCount)
	{
		_flagData.push_back(flag);
		flag = 0;
		bitCount = 0;
	}

	// ע�⣺������zip���ǵ�LZ77�����ļ����֮�󣬶Խ�����ݽ���Huffman��
	// ���ǽ��зֿ�ѹ��(��Ϊbuffer��ǳ��󣬵����ַ�����࣬Huffman��Ҷ�ӽڵ�ǳ���ƽ�������䳤)
	
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
	// ����ϴο���ѹ����Ƶ����Ϣ
	ClearPreBlockInfo();

	// 1.ͳ��ÿ��Ԫ�س��ֵĴ���
	StatAppearCount();

	// 2.����Huffman��
	HuffmanTree<ElemInfo> byteLenTree;
	byteLenTree.CreateHuffmanTree(_byteLenInfo, ElemInfo());

	HuffmanTree<ElemInfo> distTree;
	distTree.CreateHuffmanTree(_distInfo, ElemInfo());

	// 3.���ݷ�ʽHuffman�������ɱ���
	GenerateCodeLen(byteLenTree.GetRoot(), _byteLenInfo);
	GenerateCode(_byteLenInfo);

	GenerateCodeLen(distTree.GetRoot(), _distInfo);
	GenerateCode(_distInfo);

	// 4.�����ѹ����Ҫ�õ���λ����Ϣ
	WriteCodeLen();

	// 5.ѹ��
	// ȡ��ԭ�ַ��򳤶Ⱦ���ԣ��ҳ���Ӧ�ı������ѹ��
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
			// ���Ⱦ����
			CompressLengthDist(_byteLenData[i], _distData[distIdx++], bitInfo, bitInfoCount);
		}
		else
		{
			// ԭ�ַ�
			CompressChar(_byteLenData[i], bitInfo, bitInfoCount);
		}

		flag <<= 1;
		bitCount--;
	}

	// ����forѭ��ѹ������LZ77����Ч����
	// ���λ��ѹ��һ��256��Ϊ��ı��
	CompressChar(256, bitInfo, bitInfoCount);

	if (bitInfoCount > 0 && bitInfoCount < 8)
	{
		bitInfo <<= (8 - bitInfoCount);
		fputc(bitInfo, fOut);
	}

	// ��գ�LZ77 �Ľ����buff
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
			// �ҵ���Ӧ�ĳ���������
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

	// ��������----256
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
	// 1.���ձ���λ��Ϊ��һ�ؼ��֣�Ԫ�ش�СΪ�ڶ��ؼ���������
	vector<ElemInfo> temp(codeInfo);
	sort(temp.begin(), temp.end());

	// �ҵ���һ������λ��������0��Ԫ��
	ush index = 0;
	while (index < temp.size())
	{
		if (temp[index]._len)
			break;
		index;
	}
	// 2.���շ�ʽHuffman���Ĺ������������
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
	// �����ҵ�ch�ı���
	ulg chCode = _byteLenInfo[ch]._chCode;
	ush codeLen = _byteLenInfo[ch]._len;

	Compress(chCode, codeLen, bitInfo, bitInfoCount);
}
void Zip::CompressLengthDist(uch length, ush dist, uch& bitInfo, uch& bitInfoCount)
{
	// ѹ������
	size_t index = GetIntervalCodeIndex(length);
	ulg  chCode = _byteLenInfo[index]._chCode;
	ush codeLen = _byteLenInfo[index]._len;
	Compress(chCode, codeLen, bitInfo, bitInfoCount);

	// ѹ��length���Ӧ�Ķ�����չ��
	chCode = length + 3 - lengthInterval[index - 257].interval[0];
	codeLen = lengthInterval[index - 257].extraBit;
	Compress(chCode, codeLen, bitInfo, bitInfoCount);

	// ѹ������
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
	// ��ch�ı����chCode��ѹ���ļ���дȥ
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
		cout << "ѹ���ļ���ʽ���ԣ��޷���ѹ��" << endl;
		return;
	}

	// 1.���ļ�
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
		// 1.��ȡ����λ��
		GetDecodeLen(fIn);

		// 2. ���ɽ����
		vector<DecodeTable> byteLenDecTab;
		GenerateDecodeTab(_byteLenInfo, byteLenDecTab);

		vector<DecodeTable> distDecTab;
		GenerateDecodeTab(_distInfo, distDecTab);

		// 3.����
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

				// ��ѹ������
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
				// ����LZ77��ʽ��ԭ���
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
	// 1. ͳ����ͬλ���ַ�����
	map<uch, ush> m;
	for (auto& e : codeInfo)
		m[e._len]++;

	// 2. �Զ�ȡ����λ����Ϣ��������
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