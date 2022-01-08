#include "interface.h"
#include <vector>
///
/// Represents a multiset of words
///
/// If you need to see how it is intended to be used,
/// check out the corresponding unit tests
///
/// Implement all methods of this class
/// 
	/// Adds times occurences of word to the container
	///
	/// For example, add("abc") adds the word "abc" once,
	/// while add("abc", 4) adds 4 occurrances.
	void WordsMultiset::add(const std::string& word, size_t times)
    {
        wordsTree.insert(word, times);
    }

	/// Checks whether word is contained in the container
	bool WordsMultiset::contains(const std::string& word) const
    {
		return wordsTree.contains(word);
    }   

	/// Number of occurrances of word 
	size_t WordsMultiset::countOf(const std::string& word) const
    {
		auto wordNode = wordsTree.getNode(word);
		return wordNode ? wordNode->count : 0;
    }

	//ADD ON
	size_t WordsMultiset::getUnique(const node *curr) const
    {
        if(!curr)
            return 0;
        
		return 1 + getUnique(curr->left) + getUnique(curr->right);
    }
	
	/// Number of unique words in the container
	size_t WordsMultiset::countOfUniqueWords() const
    {
        return getUnique(wordsTree.getRoot());
    }
	
	//ADD ON


	/// Returns a multiset of all words in the container
	std::multiset<std::string> WordsMultiset::words() const
    {
		std::vector<std::string> allWords = wordsTree.getAll();
		return std::multiset<std::string>(allWords.begin(), allWords.end());	
    }
	
	// You can add additional members if you need to
	ComparisonReport Comparator::compare(std::istream& a, std::istream& b)
	{
		
	}

	// You can add additional members if you need to
