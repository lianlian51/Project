//class Solution {
//public:
//	int hammingDistance(int x, int y) {
//		x = x^y;
//		int count = 0;
//		while (x)
//		{
//			if (x & 1)
//			{
//				count++;
//			}
//			x >>= 1;
//		}
//		return count;
//	}
//};

//#include <stdio.h>
//#include <string.h>
//#
//
//int main()
//{
//	char buff[30];
//	gets(buff);
//
//	char* p = strtok(buff, " ");
//	while (p != NULL)
//	{
//		printf("%s ", p);
//		p = strtok(NULL, " ");
//	}
//	return 0;
//}

//#include <stdio.h>
//
//union s
//{
//	int a;
//	char b;
//};
//
//int main()
//{
//	s c;
//	c.a = 1;
//	if (c.b == 1)
//	{
//		printf("小\n");
//	}
//	else
//	{
//		printf("大\n");
//	}
//	return 0;
//}

//#include <stdio.h>
//int main()
//{
//	char a = -1;
//	signed char b = -1;
//	unsigned char c = -1;
//	printf("a=%d,b=%d,c=%d", a, b, c);
//	return 0;
//}

/* strerror example : error list */
//#include <stdio.h> 
//#include <string.h> 
//#include <errno.h>//必须包含的头文件
//
//int main()
//{
//	FILE * pFile;
//	pFile = fopen("unexist.ent", "r");
//	if (pFile == NULL)
//		printf("Error opening file unexist.ent: %s\n", strerror(errno));
//	//errno: Last error number 
//	return 0;
//}

//#include <stdio.h>
//#include <ctype.h>
//#include <iostream>
//using namespace std;
//
//int main()
//{
//	char str[22] = "123";
//	if (isalnum(str))
//		cout << "shi" << endl;
//	else
//		cout << "bushi" << endl;
//
//	return 0;
//}
//
//#include <stdio.h>
//
//int main()
//{
//	char arr[20];
//	//scanf("%s\n", &arr);
//	gets(arr);
//	printf("%s\n", arr);
//	return 0;
//}
//#include <iostream>
//using namespace std;
//typedef struct Node
//{
//	int data;
//	struct Node* next;
//}Node;
//
//int main()
//{
//	cout << sizeof(Node) << endl;
//	return 0;
//}

#include <stdio.h>
struct A {
	int _a : 2;
	int _b : 5;
	int _c : 10;
	int _d : 30;
};

struct S {
	char a : 3;
	char b : 4;
	char c : 5;
	char d : 4;
};

int main()
{
	printf("%d\n", sizeof(struct S));
	return 0;
}

