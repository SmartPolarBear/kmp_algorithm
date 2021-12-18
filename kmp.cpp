#include <iostream>

using namespace std;
static inline constexpr size_t PATTERN_LEN = 128;

namespace DFA
{
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
	for (; i < text.length() && j < pattern.length(); i++)
	{
		j = dfa[text.at(i)][j];
	}

	if (j == pattern.length())
	{
		return i - pattern.length();
	}

	return text.length();
}

void test()
{
	std::string m = "ABABCAAABABABCA";// 2 11

	construct("ABC");

	int pos = match("ABC", m, 0);
	while (pos < m.length())
	{
		std::cout << pos << std::endl;
		pos = match("ABC", m, pos + 1);
	}
}

}

namespace NFA
{
int nfa[PATTERN_LEN]{};

void construct(const std::string& pattern)
{
	int j = 0;
	for (int i = 1; i < pattern.length(); i++)
	{
		nfa[i] = j;

		while (j > 0 && pattern[i] != pattern[j])
		{
			j = nfa[j];
		}

		if (pattern[i] == pattern[j])
		{
			j++;
		}
	}
}

int match(const std::string& pattern, const std::string& text, int pos)
{
	int i = pos, j = 0;
	for (; i < text.length() && j < pattern.length(); i++)
	{
		while (j > 0 && text[i] != pattern[j])
		{
			j = nfa[j];
		}

		if (text[i] == pattern[j])
		{
			j++;
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
	memset(nfa, 0, sizeof(nfa));

	construct("AAAAB");
	for (int i = 0; i < 5; i++)
	{
		cout << nfa[i] << " ";
	}
	cout << endl;

	memset(nfa, 0, sizeof(nfa));


	std::string m = "ABABCAAABABABCA";// 2 11

	construct("ABC");

	int pos = match("ABC", m, 0);
	while (pos < m.length())
	{
		std::cout << pos << std::endl;
		pos = match("ABC", m, pos + 1);
	}
}
}