// Piyush Manjhi

#ifndef _HUFFMAN_HPP_
#define _HUFFMAN_HPP_

#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

#include <iostream>
#include <string>
#include <map>
#include <stack>

class HuffmanTree
{
private:
    HuffmanNode *baseNode; // parent/root/base node of the tree

public:
    // the following are the functions which are told to be defined in the given word document:
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);

    // defining a constructor HuffmanTree:
    HuffmanTree()
    {
        baseNode = new HuffmanNode('\0', 0); // initializing (character, frequency)
    }

    // declaring a destructor HuffmanTree (it is defined in the cpp file)
    ~HuffmanTree();
};

// below are the helper/additional functions which we are defining for our program:

// declaring the function which is used in destructor to delete nodes
void delete_node(HuffmanNode *node);

// will use pre-order traversal in the following function (used for compression function):
void prefix_code(std::map<char, std::string> *map_prefix, HuffmanNode *node, std::string code);

// will use post-order traversal in the following function (used for serialization function):
const std::string serialize_code(HuffmanNode *node);

#endif
