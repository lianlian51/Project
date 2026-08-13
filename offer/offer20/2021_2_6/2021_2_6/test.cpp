// 表示数值的字符串


bool scannumInt(char** ps)
{
	const char* before = *ps;

	while (**ps != '\0' && **ps >= '0' && **ps <= '9')
		++(*ps);

	return *ps > before;
}


bool numInt(char **s)
{
	if (**s == '+' || **s == '-')
		++(*s);
	return scannumInt(s);
}


bool isNumber(char* s)
{
	if (s == NULL)
		return false;

	while (*s == ' ')
		++s;
	bool numeric = numInt(&s);

	if (*s == '.')
	{
		++s;
		numeric = scannumInt(&s) || numeric;
	}

	if (*s == 'e' || *s == 'E')
	{
		++s;
		numeric = numeric && numInt(&s);
	}

	while (*s == ' ')
		++s;

	return numeric && *s == '\0';
}