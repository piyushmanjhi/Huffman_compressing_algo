// Piyush Manjhi U10602103

#include "HuffmanTree.hpp"

// prefix code using pre-order traversal
void prefix_code(std::map<char, std::string> *map_prefix, HuffmanNode *node, std::string code)
{
    // Leaf node Validation
    if (!node->isLeaf())
    {
        prefix_code(map_prefix, node->left, code + '0');  // left child node = 0
        prefix_code(map_prefix, node->right, code + '1'); // right child node = 1
    }
    else
    {
        auto x = std::make_pair(node->getCharacter(), code); // auto since dataype not fixed, make_pair function for pairing
        map_prefix->insert(x);                               // mapping char value with code
    }

    return;
}

// input string
std::string HuffmanTree::compress(const std::string inputStr) // prefix code generator
{
    // Implement frequency counter
    std::map<char, int> frequency;

    for (unsigned int i = 0; i < inputStr.size(); i++)
    {
        // Validating Duplicate Key
        if (frequency.count(inputStr.at(i)) == 1)
            frequency.at(inputStr.at(i)) += 1; // increment count

        else
        {
            auto pair = std::make_pair(inputStr.at(i), 1); // creating new pair
            frequency.insert(pair);
        }
    }

    HeapQueue<HuffmanNode *, HuffmanNode::Compare> hq; // created heap
    auto a = frequency.begin();                        // declare iterator

    while (a != frequency.end())
    {
        HuffmanNode *newNode = new HuffmanNode(a->first, a->second);
        hq.insert(newNode);
        a++;
    }

    const char nc = '\0'; // null character

    // moving nodes down to one in the heap
    while (hq.size() != 1)
    {
        auto first_node = hq.min();
        hq.removeMin(); // removing the node
        auto second_node = hq.min();
        hq.removeMin(); // removing the node

        auto temp_frequency = (first_node->getFrequency() + second_node->getFrequency());
        HuffmanNode *temp_node = new HuffmanNode(nc, temp_frequency, nullptr, first_node, second_node);

        first_node->parent = temp_node;
        second_node->parent = temp_node;

        hq.insert(temp_node); // inserting the intermediate node back into the queue
    }

    // for last one pair left in Heap for base/root/parent data member
    baseNode = hq.min();

    std::string code_of_string = ""; // code of string will return the code

    std::map<char, std::string> map_prefix; // map containing the character and the found code

    // helper function insert code in map
    prefix_code(&map_prefix, baseNode, code_of_string);

    // comparing with char in string
    for (auto i : inputStr)
        code_of_string += map_prefix.at(i);

    return code_of_string;
}

// serialization:  letter code to the tree (post-order)
const std::string serialize_code(HuffmanNode *node)
{
    std::string serializedString = ""; // to store the serialized tree code

    // validating leaf, adding L
    if (node->isLeaf())
    {
        serializedString += "L";
        serializedString += node->getCharacter();
        return serializedString;
    }

    // validating branch adding L
    return (serialize_code(node->left) + serialize_code(node->right) + 'B');
}

std::string HuffmanTree::serializeTree() const
{
    return serialize_code(baseNode); // calling serialize_code
}

// deserialize: retreive original string
std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree)
{

    std::stack<HuffmanNode *> stack; //  stack to the characters

    for (unsigned int i = 0; i < serializedTree.length(); i++)
    {
        // for Lead
        if (serializedTree[i] == 'L')
        {
            i++;
            char a = serializedTree[i];
            HuffmanNode *huff_new = new HuffmanNode(a, 0);
            stack.push(huff_new);
        }

        else // for branch
        {
            HuffmanNode *right = stack.top();
            stack.pop();
            HuffmanNode *left = stack.top();
            stack.pop();
            HuffmanNode *parent = new HuffmanNode(0, 0, nullptr, left, right);
            stack.push(parent);
        }
    }

    // decompression
    HuffmanNode *base = stack.top();

    std::string message = ""; // itializing message to be returned by decompress function

    unsigned int j = 0; // iterator

    HuffmanNode *current; // the current node
    bool base_b = false;  // initialized to false

    while (j < inputCode.length())
    {
        if (base_b)
        {
            // if leaf
            if (current->isLeaf())
            {
                message = message + (current->getCharacter());
                base = base;
            }

            // for branch
            else
            {
                if (inputCode[j] == '1')
                    current = current->right; // 1 = right child

                else
                    current = current->left; // 0 = left child

                j++;
            }
        }
        // for root node
        else
        {
            current = base; // base node becomes the current node
            base_b = true;
        }
    }

    message = message + (current->getCharacter()); // add last char

    return message; // returning original string
}

// delete tree
void delete_node(HuffmanNode *node)
{
    // delete child node
    if (!node->isLeaf())
    {
        delete_node(node->left);  // left node
        delete_node(node->right); // right node
    }

    // delete final node
    delete node;
}

// destructor:
HuffmanTree::~HuffmanTree()
{
    delete_node(baseNode);
}
