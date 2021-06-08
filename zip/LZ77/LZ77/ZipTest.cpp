#include "LZ77.h"

int main()
{
	LZ77 lz;
	lz.CompressLZ77("1.txt");
	lz.UNCompressLZ77("111.txt");
	return 0;
}