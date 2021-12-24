#include "pch.h"
#include "..\PatriciaTree\PatriciaTree.h"
#include "..\PatriciaTree\GraphVizFunctions.h"
#include <locale>

#define fileName	"Graph.dot"

void printBinChar(char symb)
{
    setlocale(LC_ALL, "russian");
    int mask = 0x80;
    std::cout << symb << "     ";
    while (mask)
    {
        std::cout << (symb & mask ? '1' : '0');
        mask >>= 1;
    }
    std::cout << "     " << symb + 'a';
    std::cout << std::endl;
}


TEST(PatriciaTreeTests, SearchPrintTest)
{
    setlocale(LC_ALL, "russian");
    printBinChar('к');
    printBinChar('о');
    printBinChar('н');
    printBinChar('д');
    printBinChar('р');
    printBinChar('а');
    printBinChar('т');
    printBinChar('ь');
    printBinChar('е');
	printBinChar('в');

    PatriciaTree<char> tree;
    tree.addNode('к');
    tree.addNode('о');
    tree.addNode('н');
    tree.addNode('д');
    tree.addNode('р');
    tree.addNode('а');
    tree.addNode('т');
    tree.addNode('ь');
    tree.addNode('е');
	tree.addNode('в');

	GraphViz<char> graph(&tree, fileName);
    std::string str = tree.treeToStr();
    std::cout << str << std::endl;
	graph.drawGraph();

    Node<char>* node = tree.searchNode('а');
    EXPECT_EQ(node->_data, 'а');
    node = tree.searchNode('ф');
    EXPECT_EQ(node->_data, 0);
}
