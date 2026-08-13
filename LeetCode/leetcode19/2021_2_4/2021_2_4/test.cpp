// 请实现一个函数用来匹配包含'. '和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（含0次）。
// 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配


bool isMatchCore(char* s, char* p)
{
	// s，p都为空时，返回true
	if (*p == '\0' && *s == '\0')
		return true;
	// s不为空，p为空时返回true
	if (*s != '\0' && *p == '\0')
		return false;
	// p+1等于*时，两种匹配方式
	if (*(p + 1) == '*')
	{
		// 三种情况
		if (*p != *s && *p != '.')
			return isMatchCore(s, p + 2);
		if (*p == '.' && *s != '\0')
			return isMatchCore(s, p + 2) || isMatchCore(s + 1, p);
		else if (*p == '.' && *s == '\0')
			return isMatchCore(s, p + 2);
		if (*p == *s)
			return isMatchCore(s + 1, p) || isMatchCore(s, p + 2);
	}

	// 对于s不为空，并且相等的情况
	if ((*p == '.' && *s != '\0') || *p == *s)
		return isMatchCore(s + 1, p + 1);
	return false;
}


bool isMatch(char* s, char* p){
	if (p == NULL && s == NULL)
		return false;
	return isMatchCore(s, p);
}