#include <iostream>
#include <vector>

using std::vector;

constexpr size_t MAX_LEN = 100010;

size_t next[MAX_LEN] = { 0 };

vector<size_t> matches{};

void build_next(const char* m)
{
	memset(next, 0, sizeof(next));
	size_t len = strlen(m);

	for (int i = 1, now = next[0]; i < len;) // next[0] is, by definition 0
	{
		if (m[i] == m[now])
		{
			now++;
			next[i] = now;
			i++;
		}
		else if (now != 0)
		{
			now = next[now - 1];
		}
		else
		{
			i++;
			next[i] = now;
		}
	}
}

void match(const char* p, const char* m)
{
	size_t plen = strlen(p), mlen = strlen(m);
	for (size_t pi = 0, mi = 0; pi < plen;)
	{
		if (p[pi] == m[mi])
		{
			pi++; mi++;
		}
		else if (mi != 0)
		{
			mi = next[mi - 1];
		}
		else if (mi == 0)
		{
			pi++;
		}

		if (mi == mlen)
		{
			matches.push_back(pi - mlen);
			mi = next[mi - 1];
		}
	}
}

int main()
{
	auto p = "ababaabaabacababaabaabababaabaabac", m = "abaabac";
	build_next(m);
	match(p, m);
	for (auto m : matches)
	{
		std::cout << m << std::endl;
	}
	return 0;
}