#include <iostream>
#include "implementation.cpp"

int main()
{
    std::stringstream a("one two three four two one");
	std::stringstream b("two one four one one");

    Comparator c;
	ComparisonReport report = c.compare(a, b);

    std::cout<<(report.commonWords.countOfUniqueWords() == 3);
    std::cout<<(report.uniqueWords[0].countOfUniqueWords() == 2);
    std::cout<<(report.uniqueWords[1].countOfUniqueWords() == 1);
}