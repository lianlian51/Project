#include "LZ77.h"

#include <iostream>
using namespace std;
#include <assert.h>



LZ77::LZ77()
: _pWin(new uch[2*WSIZE])
, _ht(WSIZE)
{}


LZ77::~LZ77()
{
	delete[] _pWin;
	_pWin = nullptr;
}

void LZ77::CompressLZ77(const string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "��ѹ���ļ�·������" << endl;
		return;
	}


	// �ļ�̫Сʱ�򲻽���ѹ��-----�ļ�С��3���ֽ���ѹ��
	fseek(fIn, 0, SEEK_END);
	ulg fileSize = ftell(fIn);
	fseek(fIn, 0, SEEK_SET);
	if (fileSize <= MIN_MATCH)
	{
		cout << "�ļ�̫С�ˣ�С��3���ֽڲ�ѹ��" << endl;
		fclose(fIn);
		return;
	}

	// ��ȡһ�����ڵ�����
	ulg lookahead = fread(_pWin, 1, 2 * WSIZE, fIn);

	// ��Ϊ��ϣ��ַ--�����ַ�һ�������м����
	// ��Insert���洫���ch�������ַ��еĵ�����
	// �������ʽѹ��ǰ����Ҫ��ʹ��ǰ2���ֽ�Ԥ��hashAddr
	ush hashAddr = 0;
	ush matchHead = 0;
	for (ush i = 0; i < MIN_MATCH - 1; i++)
	{
		_ht.Insert(hashAddr, _pWin[i], i, matchHead);
	}


	FILE* fOut = fopen("111.txt", "wb");

	// ���ļ�������д��ѹ��ʱ����Ҫ�õ��ı����Ϣ��
	FILE* fFlag = fopen("temp.txt", "wb");

	ush start = 0;
	
	uch ch = 0;
	uch bitCount = 0;
	
	while (lookahead)
	{
		ush curMatchLength = 0;
		ush curMatchDist = 0;

		// �������ַ�һ�� ����ϣͰ�н��в���
		_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);

		// �ڲ���֮��matchHead�Ὣ���һ������������һ��ƥ���λ�ô�����
		if (matchHead)
		{
			// ���ƥ����
			curMatchLength = LongestMatch(matchHead, start, curMatchDist);  // <���ȣ�����>
		}

		if (curMatchLength < MIN_MATCH)
		{
			// �������ֽ�֮ǰû�г��ֹ�
			// ����ǰstartλ�õ��ֽ�ԭ�ⲻ����д�뵽ѹ���ļ���
			fputc(_pWin[start], fOut);
			start++;
			lookahead--;

			WriteFlag(fFlag, false, ch, bitCount);
		}
		else
		{
			// ����<���ȣ�����>��д�뵽ѹ���ļ���
			fputc(curMatchLength - 3, fOut);
			fwrite(&curMatchDist, 2, 1, fOut);

			WriteFlag(fFlag, true, ch, bitCount);

			lookahead -= curMatchLength;

			// ��Ҫ��ƥ�����������ֽ�һ������ϣ�����ܲ���
			curMatchLength -= 1;   // ��Ϊstartλ�ÿ�ʼ���ֽ��Ѿ�������
			while (curMatchLength)
			{
				++start;
				_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
				curMatchLength--;
			}

			++start;
		}

		// lookahead�������л�������ʣ��Ĵ�ѹ���ֽڵĸ���
		if (lookahead <= MIN_LOOKAHEAD)
			FillDate(fIn, lookahead, start);
	}

	if (bitCount > 0 && bitCount < 8)
	{
		ch <<= (8 - bitCount);
		fputc(ch, fFlag);
	}

	fclose(fIn);
	fclose(fFlag);

	// �������ļ��ϲ���һ���ļ�
	MergeFile(fOut, fileSize);
	fclose(fOut);
}

void LZ77::FillDate(FILE* fIn, ulg& lookahead, ush& start)
{
	if (start > MAX_DIST)
	{
		// ���д����е����ݰ��Ƶ���
		memcpy(_pWin, _pWin + WSIZE, WSIZE);
		start -= WSIZE;

		// ע�⣺���¹�ϣ��
		_ht.UpdateHashTable();

		// ��Ҫ���Ҵ����в�������
		if (!feof(fIn))
			lookahead += fread(_pWin + WSIZE, 1, WSIZE, fIn);
	}
}

ush LZ77::LongestMatch(ush matchHead, ush start, ush& curMatchDist)
{
	ush maxLen = 0;
	uch maxMatchCount = 255;
	ush limit = start > MAX_DIST ? start - MAX_DIST : 0;
	do 
	{
		uch* pScan = _pWin + matchHead;
		uch* pEnd = pScan + MAX_MATCH;
		uch* pStart = _pWin + start;

		ush curLength = 0;
		ush curDist = 0;

		// ��һ��ƥ��
		while (pScan < pEnd && *pScan == *pStart)
		{
			pScan++;
			pStart++;
			curLength++;
		}

		curDist = start - matchHead;

		// ȷ���ƥ��
		if (curLength > maxLen)
		{
			maxLen = curLength;
			curMatchDist = curDist;
		}

	} while (((matchHead = _ht.GetNext(matchHead)) > limit) && maxMatchCount--);

	return maxLen;
}

void LZ77::WriteFlag(FILE* temp, bool isDist, uch& ch, uch& bitCount)
{
	ch <<= 1;
	if (isDist)
		ch |= 1;

	bitCount++;
	if (8 == bitCount)
	{
		fputc(ch, temp);
		ch = 0;
		bitCount = 0;
	}
}

void LZ77::MergeFile(FILE* fOut, ulg fileSize)
{
	FILE* fFlag = fopen("temp.txt", "rb");
	assert(fFlag);

	uch readBuff[1024];
	size_t flagSize = 0;
	while (true)
	{
		size_t rdSize = fread(readBuff, 1, 1024, fFlag);
		if (0 == rdSize)
			break;

		flagSize += rdSize;
		fwrite(readBuff, 1, rdSize, fOut);
	}

	fwrite(&flagSize, sizeof(flagSize), 1, fOut);
	fwrite(&fileSize, sizeof(fileSize), 1, fOut);
	fclose(fFlag);
	remove("temp.txt");
}


void LZ77::UNCompressLZ77(const string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "��ѹ���ļ�·��������" << endl;
		return;
	}

	// ��ȡԴ�ļ��Ĵ�С
	fseek(fIn, 0 - sizeof(ulg), SEEK_END);
	ulg fileSize = 0;
	fread(&fileSize, sizeof(fileSize), 1, fIn);

	// ��ȡ��ǵĴ�С
	size_t flagSize = 0;
	fseek(fIn, 0 - sizeof(fileSize)-sizeof(flagSize), SEEK_END);
	fread(&flagSize, sizeof(flagSize), 1, fIn);

	fseek(fIn, 0, SEEK_SET);

	FILE* fFlag = fopen(filePath.c_str(), "rb");
	fseek(fFlag, 0 - sizeof(fileSize)-sizeof(flagSize) - flagSize, SEEK_END);

	// ��ѹ��
	FILE* fOut = fopen("222.txt", "wb");

	FILE* fRead = fopen("222.txt", "rb");

	uch ch = 0;
	uch bitCount = 0;
	size_t i = 0;
	uch chData = 0;
	ulg compressCount = 0;
	while (compressCount < fileSize)
	{
		if (0 == bitCount)
		{
			ch = fgetc(fFlag);
			bitCount = 8;
			i++;
		}

		// ���ñ���λ��0����1
		if (ch & 0x80)
		{
			// ���Ⱦ����
			ush matchLength = fgetc(fIn) + 3;
			ush matchDist = 0;
			fread(&matchDist, sizeof(matchDist), 1, fIn);

			// �мǣ���ѹ�����������ݿ��ܻ��ڻ�������
			fflush(fOut);

			fseek(fRead, 0 - matchDist, SEEK_END);
			compressCount += matchLength;

			while (matchLength)
			{
				chData = fgetc(fRead);
				fputc(chData, fOut);
				fflush(fOut);
				matchLength--;
			}
		}
		else
		{
			// ԭ�ַ�
			chData = fgetc(fIn);
			fputc(chData, fOut);
			compressCount++;
		}

		bitCount--;
		ch <<= 1;
	}

	fclose(fIn);
	fclose(fFlag);
	fclose(fOut);
	fclose(fRead);
}