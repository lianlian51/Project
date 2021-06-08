#include "HTCompress.h"
//#include "HuffmanTree.hpp"

#include <iostream>
using namespace std;

#include <string>


HTCompress::HTCompress()
{
	_charInfo.resize(256);
	for (size_t i = 0; i < 256; ++i)
	{
		_charInfo[i]._ch = i;
		_charInfo[i]._appearCount = 0;
	}
}

void HTCompress::CompressFile(const std::string& filePath)
{
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "���򿪵��ļ�����" << endl;
		return;
	}

	// 1.�����ַ����ֵĴ���
	uch readBuffer[1024];
	while (true)
	{
		size_t  rdsize = fread(readBuffer, 1, 1024, fIn);
		if (rdsize == 0)
			break;

		for (size_t i = 0; i < rdsize; ++i)
		{
			_charInfo[readBuffer[i]]._appearCount++;
		}
	}

	// 2.��charInfo�Ĵ���ΪȨֵ������������
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo, CharInfo(0));

	// 3.��ȡ�ַ���Huffman����
	GeneteCode(ht.GetRoot());

	// �����ļ�ָ���λ��
	rewind(fIn);

	// fOut����дѹ�������
	FILE* fOut = fopen("compresResult.txt", "wb");

	WriteHeadInfo(fOut, filePath);
	// 4.�û�ȡ���ı����Դ�ļ���ÿ���ַ�����д��
	uch chData = 0;
	ulg biteCount = 0;
	while (true)
	{
		size_t rdsize = fread(readBuffer, 1, 1024, fIn);
		if (rdsize == 0)
		{
			break;
		}

		for (size_t i = 0; i < rdsize; ++i)
		{
			string& strCode = _charInfo[readBuffer[i]]._strCode;

			for (size_t j = 0; j < strCode.size(); ++j)
			{
				chData <<= 1;
				if (strCode[j] == '1')
					chData |= 1;
				biteCount++;
				if (biteCount == 8)
				{
					// �����ֽ�д�뵽ѹ���ļ���
					fputc(chData, fOut);
					biteCount = 0;
					chData = 0;
				}
			}
		}
	}

	// ����û��д���˸�����λ�����
	if (biteCount > 0 && biteCount < 8)
	{
		chData <<= (8 - biteCount);
		fputc(chData, fOut);
	}

	fclose(fIn);
	fclose(fOut);
}


void HTCompress::GeneteCode(HuffmanTreeNode<CharInfo>* root)
{
	if (nullptr == root)
		return;

	GeneteCode(root->_left);
	GeneteCode(root->_right);

	if (root->_left == nullptr && root->_right == nullptr)
	{
		HuffmanTreeNode<CharInfo>* cur = root;
		HuffmanTreeNode<CharInfo>* parent = cur->_parent;

		string& strCode = _charInfo[cur->_weight._ch]._strCode;
		while (parent)
		{
			if (cur == parent->_left)
				strCode += '0';
			else
				strCode += '1';

			cur = parent;
			parent = cur->_parent;
		}

		reverse(strCode.begin(), strCode.end());
	}
}


void HTCompress::WriteHeadInfo(FILE* fOut, const string& filePath)
{
	// 1.��ȡ�ļ���׺
	string filePostFix = filePath.substr(filePath.find("."));
	filePostFix += "\n";

	// 2.�ֽڳ��ֵ�������
	size_t szCount = 0;

	// 3.�ֽڣ��ַ��Ĵ���---ÿ��ռһ��
	string chAppear;
	for (size_t i = 0; i < 256; ++i)
	{
		if (0 != _charInfo[i]._appearCount)
		{
			chAppear += _charInfo[i]._ch;
			chAppear += ",";
			chAppear += to_string(_charInfo[i]._appearCount);
			chAppear += "\n";
			szCount++;
		}
	}

	fwrite(filePostFix.c_str(), 1, filePostFix.size(), fOut);

	string strCount = to_string(szCount);
	strCount += "\n";
	fwrite(strCount.c_str(), 1, strCount.size(), fOut);

	fwrite(chAppear.c_str(), 1, chAppear.size(), fOut);
}

void HTCompress::UNCompressFile(const std::string& filePath)
{
	// ��ȡ�ļ�
	FILE* fIn = fopen(filePath.c_str(), "rb");
	if (nullptr == fIn)
	{
		cout << "ѹ���ļ�·������" << endl;
		return;
	}

	// Դ�ļ���ѹ������
	string fileName = "2";
	string s;
	GetLine(fIn, s);
	fileName += s;

	s = "";
	GetLine(fIn, s);
	size_t szCount = atoi(s.c_str());

	// ��ȡÿ�е���Ϣ
	for (size_t i = 0; i < szCount; ++i)
	{
		s = "";
		GetLine(fIn, s);

		// ���ڻ��У���������
		if (s == "")
		{
			s += "\n";
			GetLine(fIn, s);
		}
		_charInfo[(uch)s[0]]._appearCount = atoi(s.c_str() + 2);
	}

	// ��ԭHuffman��
	HuffmanTree<CharInfo> ht;
	ht.CreateHuffmanTree(_charInfo, CharInfo(0));

	// ��ѹ��
	FILE* fOut = fopen(fileName.c_str(), "wb");

	HuffmanTreeNode<CharInfo>* cur = ht.GetRoot();
	uch bitCount = 8;
	uch chBit;
	ulg fileSize = cur->_weight._appearCount;
	uch readBuff[1024];

	while (true)
	{
		size_t rdsize = fread(readBuff, 1, 1024, fIn);
		if (0 == rdsize)
		{
			break;
		}

		for (size_t i = 0; i < rdsize; ++i)
		{
			bitCount = 8;
			chBit = readBuff[i];
			while (bitCount)
			{
				if (chBit & 0x80)
				{
					cur = cur->_right;
				}
				else
				{
					cur = cur->_left;
				}

				if (nullptr == cur->_left && nullptr == cur->_right)
				{
					// �ߵ���Ҷ�ӽڵ㣬�ͽ�ѹ����һ���ַ�
					fputc(cur->_weight._ch, fOut);
					cur = ht.GetRoot();

					// �������һ���ֽڲ���8������λ�����
					fileSize--;
					if (0 == fileSize)
						break;
				}

				bitCount--;
				chBit <<= 1;
			}
		}
	}

	fclose(fIn);
	fclose(fOut);
}

void HTCompress::GetLine(FILE* fIn, std::string &s)
{
	uch ch;
	while (!feof(fIn))
	{
		ch = fgetc(fIn);
		if (ch == '\n')
			break;
		s += ch;
	}
}
