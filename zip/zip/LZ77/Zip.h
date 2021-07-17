#include "Common.h"
#include "HuffmanTree.hpp"
#include "HashTable.h"

struct ElemInfo
{
	ush _ch; // �ַ�
	ulg _appearCount; // ��ʾ�ַ����ִ���
	ush _len;
	ulg _chCode;

	ElemInfo(ulg appCount = 0)
		: _appearCount(appCount)
	{}

	ElemInfo operator+(const ElemInfo& c)
	{
		return ElemInfo(_appearCount + c._appearCount);
	}
	ElemInfo operator>(const ElemInfo& c)
	{
		return _appearCount > c._appearCount;
	}

	ElemInfo operator==(const ElemInfo& c)
	{
		return _appearCount == c._appearCount;
	}

	ElemInfo operator!=(const ElemInfo& c)
	{
		return _appearCount != c._appearCount;
	}

	ElemInfo operator<(const ElemInfo& c)
	{
		if ((_len < c._len) || (_len == c._len && _ch < c._ch))
		{
			return true;
		}
		return false;
	}
};


struct DecodeTable
{
	int _decodeLen; // ����λ��
	int _code;      // ���ַ�����
	ush _lenCount;  // ��ͬ���볤��
	ush _charIndex; // ��������
};

class Zip
{
public:
	Zip();
	~Zip();

public:
	void Deflate(const string& filePath);
	void unDeflate(const string& filePath);

private:
	void SaveLZ77Result(ush dist, uch length, uch& flag, uch& bitCount, const ulg lookahead);
	ush LongestMatch(ush matchHead, ush start, ush& curMatchDist);
	void FileDate(FILE* fIn, ulg& lookahead, ush& start);

	/////////////////////////////////////////////////////////////////////////////////////////
	void CompressBlock();
	void StatAppearCount();
	ush GetIntervalCodeIndex(uch len);
	ush GetIntervalCodeIndex(ush dist);
	void GenerateCodeLen(HuffmanTreeNode<ElemInfo>* root, vector<ElemInfo>& elemInfo);
	void GenerateCodeLen(HuffmanTreeNode<ElemInfo>* root, vector<ElemInfo>& elemInfo, ush len);
	void GenerateCode(vector<ElemInfo>& codeInfo);
	void WriteCodeLen();

	void CompressChar(ush ch, uch& bitInfo, uch& bitInfoCount);
	void CompressLengthDist(uch length, ush dist, uch& bitInfo, uch& bitInfoCount);
	void Compress(ulg chCode, ush codeLen, uch& bitInfo, uch& bitInfoCount);

	void GetDecodeLen(FILE* fIn);
	void GenerateDecodeTab(vector<ElemInfo>& codeInfo, vector<DecodeTable>& decTab);
	ush UNCompressSymbol(FILE* fIn, vector<ElemInfo>& codeInfo, vector<DecodeTable>& decTable, uch& ch, uch& bitCount);
	void GetNextBit(FILE* fIn, ush& code, uch& ch, uch& bitCount);

	void ClearPreBlockInfo();
	void GetLine(FILE* fIn, string& s);
private:
	uch* _pWin;
	HashTable _ht;

	// ��������LZ77�Ľ��
	vector<uch> _byteLenData;
	vector<ush> _distData;
	vector<uch> _flagData;

	bool _isLast; // �ж��Ƿ�Ϊ���һ����
	FILE* fOut;

	// ��������Huffman���Լ�����
	vector<ElemInfo> _byteLenInfo;
	vector<ElemInfo> _distInfo;

	const static ush MIN_LOOKAHEAD = MIN_MATCH + MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
	const static ush BUFF_SIZE = 0X8000;
};