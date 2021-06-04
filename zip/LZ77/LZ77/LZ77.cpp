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
	if (fileSize < MIN_MATCH)
	{
		std::cout << "文件太小，不压缩" << std::endl;
		fclose(fIn);
		return;
	}

	// 3.读取一个窗口的数据，将前两个字节数据哈希地址插入到哈希桶中
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);

	ush hashAddr = 0;
	ush matchHead = 0;
	for (int i = 0; i < MIN_MATCH - 1; ++i)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}

	FILE* fOut = fopen("111.txt", "wb");
	// 用来记录标记信息
	FILE* fFlag = fopen("temp.txt", "wb");


	ush start = 0;
	ush curMatchLength = 0;
	ush curMatchDist = 0;
	
	uch ch = 0;
	uch bitCount = 0;

	while (lookahead)
	{
		// 4.将三个字节计算出来的哈希地址插入到哈希桶中
		// 如果匹配链的头是0的话，那么这三个字节就是第一次出现，则写入到压缩文件中
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
			// 找到最长的匹配
			curMatchLength = LongestMatch(matchHead, start, curMatchDist);

			// 将<长度，距离>写入到文件中
			fputc(curMatchLength - 3, fOut);
			fwrite(&curMatchDist, 2, 1, fOut);

			WriteFlag(fFlag, true, ch, bitCount);

			lookahead -= curMatchLength;

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
	
	// 防止成环
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