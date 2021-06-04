#include "LZ77.h"
#include <iostream>

LZ77::LZ77()
: _pWin(new uch[2 * WSIZE])
, _ht(WSIZE)
{}

LZ77::~LZ77()
{
	delete _pWin;
	_pWin = nullptr;
}

void LZ77::CompressLZ77(const std::string& filePath)
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
	if (fileSize < MIN_MATCH)
	{
		std::cout << "�ļ�̫С����ѹ��" << std::endl;
		fclose(fIn);
		return;
	}

	// 3.��ȡһ�����ڵ����ݣ���ǰ�����ֽ����ݹ�ϣ��ַ���뵽��ϣͰ��
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);

	ush hashAddr = 0;
	ush matchHead = 0;
	for (int i = 0; i < MIN_MATCH - 1; ++i)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}

	FILE* fOut = fopen("111.txt", "wb");
	// ������¼�����Ϣ
	FILE* fFlag = fopen("temp.txt", "wb");


	ush start = 0;
	ush curMatchLength = 0;
	ush curMatchDist = 0;
	
	uch ch = 0;
	uch bitCount = 0;

	while (lookahead)
	{
		// 4.�������ֽڼ�������Ĺ�ϣ��ַ���뵽��ϣͰ��
		// ���ƥ������ͷ��0�Ļ�����ô�������ֽھ��ǵ�һ�γ��֣���д�뵽ѹ���ļ���
		_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
		if (0 == matchHead)
		{
			fputc(_pWin[start], fOut);
			start++;
			lookahead -= 1;

			WriteFlag(fFlag, false, ch, bitCount);
		}
		else
		{
			// �ҵ����ƥ��
			curMatchLength = LongestMatch(matchHead, start, curMatchDist);

			// ��<���ȣ�����>д�뵽�ļ���
			fputc(curMatchLength - 3, fOut);
			fwrite(&curMatchDist, 2, 1, fOut);

			WriteFlag(fFlag, true, ch, bitCount);

			lookahead -= curMatchLength;

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

	}

	if (bitCount > 0 && bitCount < 8)
	{
		ch <<= (8 - bitCount);
		fputc(ch, fFlag);
	}


	fclose(fIn);

	MergeFile(fOut, fileSize);
	fclose(fOut);
	fclose(fFlag);
}

ush LZ77::LongestMatch(ush matchHead, ush start, ush& curMatchDist)
{
	int maxLength = 0;
	
	// ��ֹ�ɻ�
	uch maxMatchCount = 255;
	do
	{
		uch* pScan = _pWin + matchHead;
		uch* pEnd = pScan + MAX_MATCH;
		uch* pStart = _pWin + start;

		uch curLength = 0;
		uch curDist = 0;

		while (pScan < pStart && *pScan == *pStart)
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

	} while ((matchHead = _ht.GetNext(matchHead)) && maxMatchCount--);

	return maxLength;
}


void LZ77::WriteFlag(FILE* temp, bool flag, uch& ch, uch& bitCount)
{
	ch <<= 1;
	if (flag)
		ch |= 1;

	++bitCount;
	if (8 == bitCount)
	{
		fputc(ch, temp);
		bitCount = 0;
		ch = 0;
	}
}


void LZ77::MergeFile(FILE* fOut, ulg fileSize)
{
	FILE* fFlag = fopen("temp.txt", "rb");
	assert(fFlag);

	uch readBuffer[1024];
	size_t flagSize = 0;
	while (true)
	{
		size_t rdSize = fread(readBuffer, 1, 1024, fFlag);
		if (rdSize == 0)
			break;

		flagSize += rdSize;
		fwrite(readBuffer, 1, rdSize, fOut);
	}

	fwrite(&flagSize, sizeof(flagSize), 1, fOut);
	fwrite(&fileSize, sizeof(fileSize), 1, fOut);
	fclose(fFlag);

	remove("temp.txt");
}