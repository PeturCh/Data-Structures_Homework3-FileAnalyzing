#include <iostream>
#include <vector>

struct node
{
    std::string word{};
    size_t count{};
    node *left{};
    node *right{};
    int height{};

    node(const std::string &_word, size_t &_count,  int _height, node *_left = nullptr, node *_right = nullptr)
            : word(_word), count(_count), left(_left), right(_right), height(_height)
    {}
};

class tree
{
    private:
    node *root{};
    size_t size{};

    node* copy(node *other)
    {
        return other ? new node(other->word, other->count, other->height, copy(other->left), copy(other->right)) : other;
    }

    void clear(node *r)
    {
        if (r)
        {
            clear(r->left);
            clear(r->right);
            delete r;
        }
    }

    int getHeight(const node *n) const
    {
        return n ? n->height : 0;
    }

    int balanceFactor(node *n) const
    {
       return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    node *rightRotation(node *imbalancedRoot)
    {
        auto leftChild = imbalancedRoot->left;
        auto rightSubtree = leftChild->right;

        leftChild->right = imbalancedRoot;
        imbalancedRoot->left = rightSubtree;

        imbalancedRoot->height = std::max(getHeight(imbalancedRoot->left), getHeight(imbalancedRoot->right) + 1);
        leftChild->height = std::max(getHeight(leftChild->left), getHeight(leftChild->right) + 1);
        
        return leftChild;
    }

    node *leftRotation(node *imbalancedRoot)
    {
        auto rightChild = imbalancedRoot->right;
        auto leftSubtree = rightChild->left;

        rightChild->left = imbalancedRoot;
        imbalancedRoot->right = leftSubtree;

        imbalancedRoot->height = std::max(getHeight(imbalancedRoot->left), getHeight(imbalancedRoot->right) + 1);
        rightChild->height = std::max(getHeight(rightChild->left), getHeight(rightChild->right) + 1);
        
        return rightChild;
    }

    node *insert(node *curr, const std::string _word, size_t _count)
    {
        if (!curr)
        {
            size++;
            return new node(_word, _count, 1);
        }

        if(curr->word == _word)
        {
            curr->count += _count;
            return curr;
        }

        if (curr->word < _word)
        {
            curr->right = insert(curr->right, _word, _count);
        }
        else if (curr->word > _word)
        {
            curr->left = insert(curr->left, _word, _count);
        }
        else
        {
            return curr;
        }

        curr->height = std::max(getHeight(curr->left), getHeight(curr->right)) + 1;

        int balance = balanceFactor(curr);

        if (balance > 1)
        {
            int balance_left = balanceFactor(curr->left);
            if (balance_left > 0)
            {
                return rightRotation(curr);
            }
            else
            {
                curr->left = leftRotation(curr->left);
                return rightRotation(curr);
            }
        }
        else if (balance < -1)
        {
            int balance_right = balanceFactor(curr->right);
            if (balance_right > 0)
            {
                curr->right = rightRotation(curr->right);
                return leftRotation(curr);
            }
            else
            {
                return leftRotation(curr);
            }
        }
        return curr;
    }

    node* getNode(node *curr, const std::string word) const
    {
        if(!curr)
            return nullptr;
        
        if(curr->word == word)
            return curr;

        if(curr->word > word)
            return getNode(curr->left, word);
        
        else return getNode(curr->right, word);
    }

    public:

    tree() = default;

    tree(const tree &other)
    {
        root = copy(other.root);
    }

    tree& operator=(tree other)
    {
        std::swap(this->root, other.root);
        return *this;
    }

    ~tree()
    {   
        clear(root);
    }

    const size_t getSize() const
    {
        return size;
    }

    const node* getRoot() const
    {
        return root;
    }

    void insert(const std::string &word, const size_t &count = 1)
    {
        root = insert(root, word, count);
    }

    bool contains(const std::string &word) const
    {
        return getNode(root, word) ? true : false;
    }

    node *getNode(const std::string &word) const
    {
        return getNode(root, word);
    }       

    std::vector<std::string> getAll() const
    {
        return getAll(root);
    }

    std::vector<node*> getNodes() const
    {
        return getNodes(root);
    }


    std::vector<node*> getNodes(node *current) const
    {
        std::vector<node*> words;

        if(!current)
            return words;

        if (current->left)
            words = getNodes(current->left);

        words.push_back(current);
        
        if (current->right)
        {
            auto rightWords = getNodes(current->right);
            words.insert(words.end(), rightWords.begin(), rightWords.end());
        }
        return words;
    }

    std::vector<std::string> getAll(const node *node) const
    {
        std::vector<std::string> words;

        if(!node)
            return words;

        if (node->left)
            words = getAll(node->left);

        for (size_t i = 0; i < node->count; i++)
            words.push_back(node->word);
        
        if (node->right)
        {
            auto rightWords = getAll(node->right);
            words.insert(words.end(), rightWords.begin(), rightWords.end());
        }
        return words;
    }

};