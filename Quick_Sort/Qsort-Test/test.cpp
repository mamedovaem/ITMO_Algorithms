#include "pch.h"
#include "../../Quick_Sort/Quick_Sort/Qsort.h"
#include <random>
#include <string>


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TestQsort, SortIntAscending)
{
	srand(0);
	int vec[10000];

	for (int i = 0; i < 10000; i++)
	{
		vec[i] = ((double)rand() / RAND_MAX) * 200 - 100;
	}

	EXPECT_NO_THROW(qsort(vec, 10000, [](int a, int b) { return a < b; }));
	for (int i = 0; i < 10000 - 1; i++)
	{
		EXPECT_LE(vec[i], vec[i + 1]);
	}
}

TEST(TestQsort, SortIntDescending)
{
	srand(0);
	int vec[10000];

	for (int i = 0; i < 10000; i++)
	{
		vec[i] = ((double)rand() / RAND_MAX) * 200 - 100;
	}

	EXPECT_NO_THROW(qsort(vec, 10000, [](int a, int b) { return a > b; }));

	for (int i = 0; i < 10000 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}


TEST(TestQsort, SortIntEqual)
{
	int vec[10000];

	for (int i = 0; i < 10000; i++)
	{
		vec[i] = 0;
	}

	EXPECT_NO_THROW(qsort(vec, 10000, [](int a, int b) { return a > b; }));

	for (int i = 0; i < 10000 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}

TEST(TestQsort, SortStringAscending)
{
	std::string vec[]{"adswefjorgndjvskvsvdlkmld",
				"adssfkjs;;kfjwqijhsclchjkscd",
				"sdfewjaoiefao;ighag;ijoaghija",
				"poweorijwpfjslkdnkldsfal",
				"zxcsdjv:avja;ajkzlmnjsvklsdvlsdv" };

	EXPECT_NO_THROW(qsort(vec, 5, [](std::string a, std::string b) { return a < b; }));

	for (int i = 0; i < 5 - 1; i++)
	{
		EXPECT_LE(vec[i], vec[i + 1]);
	}
}

TEST(TestQsort, SortStringDescending)
{
	std::string vec[]{ "adswefjorgndjvskvsvdlkmld",
				"adssfkjs;;kfjwqijhsclchjkscd",
				"sdfewjaoiefao;ighag;ijoaghija",
				"poweorijwpfjslkdnkldsfal",
				"zxcsdjv:avja;ajkzlmnjsvklsdvlsdv" };

	EXPECT_NO_THROW(qsort(vec, 5, [](std::string a, std::string b) { return a > b; }));

	for (int i = 0; i < 5 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}

TEST(TestQsort, SortStringEqual)
{
	std::string vec[]{ "adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld" };

	EXPECT_NO_THROW(qsort(vec, 5, [](std::string a, std::string b) { return a > b; }));

	for (int i = 0; i < 5 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}

TEST(TestInsertSort, SortIntAscending)
{
	srand(0);
	int vec[10000];

	for (int i = 0; i < 10000; i++)
	{
		vec[i] = ((double)rand() / RAND_MAX) * 200 - 100;
	}

	EXPECT_NO_THROW(insert_sort(vec, 10000, [](int a, int b) { return a < b; }));
	for (int i = 0; i < 10000 - 1; i++)
	{
		EXPECT_LE(vec[i], vec[i + 1]);
	}
}

TEST(TestInsertSort, SortIntDescending)
{
	srand(0);
	int vec[10000];

	for (int i = 0; i < 10000; i++)
	{
		vec[i] = ((double)rand() / RAND_MAX) * 200 - 100;
	}

	EXPECT_NO_THROW(insert_sort(vec, 10000, [](int a, int b) { return a > b; }));

	for (int i = 0; i < 10000 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}


TEST(TestInsertSort, SortIntEqual)
{
	int vec[10000];

	for (int i = 0; i < 10000; i++)
	{
		vec[i] = 0;
	}

	EXPECT_NO_THROW(insert_sort(vec, 10000, [](int a, int b) { return a > b; }));

	for (int i = 0; i < 10000 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}

TEST(TestInsertSort, SortStringAscending)
{
	std::string vec[]{ "adswefjorgndjvskvsvdlkmld",
				"adssfkjs;;kfjwqijhsclchjkscd",
				"sdfewjaoiefao;ighag;ijoaghija",
				"poweorijwpfjslkdnkldsfal",
				"zxcsdjv:avja;ajkzlmnjsvklsdvlsdv" };

	EXPECT_NO_THROW(insert_sort(vec, 5, [](std::string a, std::string b) { return a < b; }));

	for (int i = 0; i < 5 - 1; i++)
	{
		EXPECT_LE(vec[i], vec[i + 1]);
	}
}

TEST(TestInsertSort, SortStringDescending)
{
	std::string vec[]{ "adswefjorgndjvskvsvdlkmld",
				"adssfkjs;;kfjwqijhsclchjkscd",
				"sdfewjaoiefao;ighag;ijoaghija",
				"poweorijwpfjslkdnkldsfal",
				"zxcsdjv:avja;ajkzlmnjsvklsdvlsdv" };

	EXPECT_NO_THROW(insert_sort(vec, 5, [](std::string a, std::string b) { return a > b; }));

	for (int i = 0; i < 5 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}

TEST(TestInsertSort, SortStringEqual)
{
	std::string vec[]{ "adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld",
				"adswefjorgndjvskvsvdlkmld" };

	EXPECT_NO_THROW(insert_sort(vec, 5, [](std::string a, std::string b) { return a > b; }));

	for (int i = 0; i < 5 - 1; i++)
	{
		EXPECT_GE(vec[i], vec[i + 1]);
	}
}
