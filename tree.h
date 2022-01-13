#include <iostream>
#include <vector>
#include <exception>

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

class AVLTRee
{
    private:
    node *root{};
    size_t size{};
    size_t elementsCount{};

    node* copy(node *other);

    void clear(node *r);

    int getHeight(const node *n) const;

    int balanceFactor(node *n) const;

    node *rightRotation(node *imbalancedRoot);

    node *leftRotation(node *imbalancedRoot);

    node *insert(node *curr, const std::string _word, size_t _count);

    node* getNode(node *curr, const std::string word) const;

    public:

    AVLTRee() = default;

    AVLTRee(const AVLTRee &other);

    AVLTRee& operator=(AVLTRee other);

    ~AVLTRee();

    const size_t getSize() const;

    const size_t getElementsCount() const;

    const node* getRoot() const;

    void insert(const std::string &word, const size_t &count = 1);

    bool contains(const std::string &word) const;

    node *getNode(const std::string &word) const;

    std::vector<std::string> getAll() const;

    std::vector<node*> getNodes() const;

    std::vector<node*> getNodes(node *current) const;

    std::vector<std::string> getAll(const node *node) const;

};
#include "tree.inl"