#include "Common.h"

#include "HashTable.h"

class LZ77
{
public:
	LZ77();
	~LZ77();

	void CompressLZ77(const std::string& filePath);
	void UNCompressLZ77(const std::string& filePath);

	
private:
	ush LongestMatch(ush matchHead, ush start, ush& curMatchDist);
	void WriteFlag(FILE* temp, bool flag, uch& ch, uch& bitCount); 
	void MergeFile(FILE* fOut, ulg fileSize);
	void FileData(FILE* fIn, ulg& lookahead, ush& start);
private:
	uch* _pWin;

	HashTable _ht;

	const static ush MIN_LOOKAHEAD = MIN_MATCH + MAX_MATCH + 1;
	const static ush MAX_DIST = WSIZE - MIN_LOOKAHEAD;
};