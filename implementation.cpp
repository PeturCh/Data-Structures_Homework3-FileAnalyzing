#include "interface.h"
#include <vector>
#include <sstream>
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
	const size_t WordsMultiset::getUnique(const node *curr) const //TODO moje da se napravi prosto metod size na dyrvoto
    {
        if(!curr)
            return 0;
        
		return 1 + getUnique(curr->left) + getUnique(curr->right);
    }

	//ADD ON
	const size_t WordsMultiset::getSize() const
	{
		return wordsTree.getElementCount();
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
		ComparisonReport cr;
		tree stream1;
		tree stream2;
		std::string word;
		while (a >> word) //n*log(n)
		    stream1.insert(word);

		while (b >> word)
		    stream2.insert(word);

		std::vector<node*> stream1Nodes = stream1.getNodes();

		for (auto &&n : stream1Nodes)
		{
			if(auto n2 = stream2.getNode(n->word))
			{
				int diff = n->count - n2->count;
				if(diff > 0) 
					cr.uniqueWords[0].add(n->word,diff);

				cr.commonWords.add(n->word, std::min(n2->count, n->count));
			}
			else cr.uniqueWords[0].add(n->word,n->count);
		}

		std::vector<node*> stream2Nodes = stream2.getNodes();
		for (auto &&n : stream2Nodes)
		{
			if(auto n2 = stream1.getNode(n->word))
			{
				int diff = n->count - n2->count;
				if(diff > 0) 
					cr.uniqueWords[1].add(n->word,diff);

			}
			else cr.uniqueWords[1].add(n->word,n->count);
		}
		return cr;
	}

	// You can add additional members if you need to
