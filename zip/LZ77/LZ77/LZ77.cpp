#include "LZ77.h"
#include <iostream>

LZ77::LZ77()
: _pWin(new uch[2 * WSIZE])
, _ht(WSIZE)
{}

LZ77::~LZ77()
{
	delete[] _pWin;
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

	FILE* fOut = fopen("111.txt", "wb");
	// ������¼�����Ϣ
	FILE* fFlag = fopen("temp.txt", "wb");


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
			fputc(_pWin[start], fOut);
			start++;
			lookahead--;

			WriteFlag(fFlag, false, ch, bitCount);
		}
		else
		{
			// ��<���ȣ�����>д�뵽�ļ���
			fputc(curMatchLength - 3, fOut);
			fwrite(&curMatchDist, 2, 1, fOut);

			WriteFlag(fFlag, true, ch, bitCount);

			lookahead -= curMatchLength;

			// ��Ҫ��ƥ�䵽����������ϣ�����в���
			curMatchLength -= 1;
			while (curMatchLength)
			{
				++start;
				_ht.Insert(hashAddr, _pWin[start + 2], start, matchHead);
				curMatchLength--;
			}
			++start;
		}
		
		if (lookahead <= MIN_LOOKAHEAD)
		{
			FileData(fIn, lookahead, start);
		}
	}

	if (bitCount > 0 && bitCount < 8)
	{
		ch <<= (8 - bitCount);
		fputc(ch, fFlag);
	}


	fclose(fIn);
	fclose(fFlag);

	MergeFile(fOut, fileSize);
	fclose(fOut);
}

void LZ77::FileData(FILE* fIn, ulg& lookahead, ush& start)
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

ush LZ77::LongestMatch(ush matchHead, ush start, ush& curMatchDist)
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
	//if (fFlag == nullptr)
	//{
	//	std::cout << "���ļ�ʧ��" << std::endl;
	//	return;
	//}

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

void LZ77::UNCompressLZ77(const std::string& filePath)
{
	// 1.���ļ�
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		std::cout << "����ѹ���ļ�����" << std::endl;
		//fclose(fIn);
		return;
	}

	// 2.��ȡԴ�ļ���С�ͱ�Ǵ�С
	fseek(fIn, 0 - sizeof(ulg), SEEK_END);
	ulg fileSize = 0;
	fread(&fileSize, sizeof(fileSize), 1, fIn);

	size_t flagSize = 0;
	fseek(fIn, 0 - sizeof(fileSize)-sizeof(flagSize), SEEK_END);
	fread(&flagSize, sizeof(flagSize), 1, fIn); // �����temp�ļ�û�رգ����¶�ȡ������Ϊ��

	fseek(fIn, 0, SEEK_SET);

	// fFlag ��ȡ��ǣ�fIn��ȡԴ�ļ���fOut����ȡ������д��222��
	FILE* fFlag = fopen(filePath.c_str(), "rb");
	fseek(fFlag, 0 - sizeof(fileSize)-sizeof(flagSize)-flagSize, SEEK_END);

	FILE* fOut = fopen("222.txt", "wb");

	FILE* fRead = fopen("222.txt", "rb");

	size_t i = 0;
	uch ch = 0;
	uch bitCount = 0;
	uch chData = 0;
	ulg compressCount = 0;
	while (compressCount < fileSize)
	{
		if (bitCount == 0)
		{
			ch = fgetc(fFlag);
			bitCount = 8;
			++i;
		}

		// ���ñ���λ��0����1
		if (ch & 0x80)
		{
			// ���Ⱦ����
			ush matchLength = fgetc(fIn) + 3;
			ush matchDist = 0;

			fread(&matchDist, sizeof(matchDist), 1, fIn);

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
	fclose(fRead); // ���fRead��fIn��һ�ݿ�������fInû�д򿪣����ùر�
}
