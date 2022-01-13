#include <iostream>
#include <fstream>
#include "implementation.hpp"

int main()
{
    Comparator c;
    std::string file1Path;
    std::string file2Path;

    std::ifstream file1;
    std::ifstream file2;

    do
    {
        if(!file2.good() || !file1.good())
            std::cout<<"Incorrect path! Insert again:\n";

        std::cout<<"Enter first file's path: ";
        std::cin>>file1Path;
        std::cout<<"Enter second file's path: ";
        std::cin>>file2Path;

        file1.open(file1Path);
        file2.open(file2Path); 

    } while(!file1.is_open() || !file2.is_open());

    ComparisonReport report = c.compare(file1, file2);
    
    std::cout<<"The common words between the files are: " << report.commonWords.getWordsCount() << " . They are:\n";
    report.commonWords.print();
    std::cout<<"The unique words to the first file (in the first but not in the second) are: " << report.uniqueWords[0].getWordsCount() << " . They are:\n";
    report.uniqueWords[0].print();
    std::cout<<"The unique words to the second file (in the second but not in the first) are: " << report.uniqueWords[1].getWordsCount() << " . They are:\n";
    report.uniqueWords[1].print();
}