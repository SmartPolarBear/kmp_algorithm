#include <iostream>

using namespace std;
static inline constexpr size_t PATTERN_LEN = 128;

int dfa[CHAR_MAX][PATTERN_LEN]{};

void construct(const std::string& pattern)
{
	dfa[pattern.at(0)][0] = 1;
	for (int i = 1, x = 0; i < pattern.length(); i++)
	{
		for (char c = 0; c < CHAR_MAX; c++)
		{
			dfa[c][i] = dfa[c][x];
		}

		dfa[pattern.at(i)][i] = i + 1;
		x = dfa[pattern.at(i)][x];
	}
}

int match(const std::string& pattern, const std::string& text, int pos)
{
	int i = pos, j = 0;

	bool e = false;
	for (; i < text.length() && j < pattern.length(); i++)
	{
		if (dfa[text.at(i)][j] <= j && j == pattern.length() - 1)
		{
			e = true;
			j++;
			i++;
			break;
		}
		else if (dfa[text.at(i)][j] <= j && i + 1 < text.length() && j + 1 < pattern.length() &&
				 text.at(i + 1) == pattern.at(j + 1) && !e)
		{
			e = true;
			j++;
		}
		else
		{
			j = dfa[text.at(i)][j];
		}
	}

	if (j == pattern.length())
	{
		return i - pattern.length();
	}

	return text.length();
}

int match(const std::string& pattern, const std::string& text, int pos, int e_allow)
{
	int i = pos, j = 0;

	int e = 0;
	for (; i < text.length() && j < pattern.length(); i++)
	{
		if (dfa[text.at(i)][j] <= j && e < e_allow)
		{

			int e_cnt = 0, ni = i, nj = j;
			while (ni < text.length() && nj < pattern.length() && text.at(ni) != pattern.at(nj) && e_cnt < e_allow)
			{
				ni++;
				nj++;
				e_cnt++;
			}

			if (ni < text.length() && nj < pattern.length() && text.at(ni) == pattern.at(nj))
			{
				i = ni - 1;
				j = nj;
				e = e_cnt;
			}
			else if (nj == pattern.length())
			{
				i = ni;
				j = nj;
				e = e_cnt;
				break;
			}
			else
			{
				j = dfa[text.at(i)][j];
			}
		}
		else
		{
			j = dfa[text.at(i)][j];
		}
	}

	if (j == pattern.length())
	{
		return i - pattern.length();
	}

	return text.length();
}


void test()
{
	std::string m = "afeabcabepppppaetrbcablcpl", p = "abc";

	construct(p);

	int pos = match(p, m, 0, 2);
	while (pos < m.length())
	{
		std::cout << pos << std::endl;
		pos = match(p, m, pos + 1, 2);
	}
}

int main()
{
	test();
	return 0;
}
