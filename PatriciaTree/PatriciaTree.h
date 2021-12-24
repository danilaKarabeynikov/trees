#pragma once
#include <string>
#define CHARBITSIZE	8
template<typename T>
struct Node
{
	Node(T data)
		: _data(data), _checkNum(0), _left(this), _right(this)
	{}

	Node(T data, size_t checkNum)
		: _data(data), _checkNum(checkNum), _left(this), _right(this)
	{}
	T _data;
	size_t _checkNum = 0;
	Node* _left = this;
	Node* _right = this;
};


template<typename T>
class PatriciaTree
{
public:
	PatriciaTree();
	~PatriciaTree();
	void addNode(T key);
	Node<T>* searchNode(T key);
	void graphVizTraversal(std::string& odtStr);
	std::string treeToStr();

private:
	Node<T>* _root;

private:
	void remove(Node<T>*& node);
	Node<T>* search(Node<T>*& root, T& key, size_t prevNum);
	bool getNumDischarge(size_t num, T key);
	void insertNode(Node<T>* prev, Node<T>* node, Node<T>* next);

	void nodeToStr(Node<T>*& node, std::string& treeStr);
	void traversal(Node<T>* node, std::string& odtStr, std::string& treeStr);
	void addDotNode(std::string& dotStr, Node<T>* key, Node<T>* value);
};


template<typename T>
PatriciaTree<T>::PatriciaTree()
{
	_root = new Node<T>(0);
	_root->_left = _root;
	_root->_right = _root;
}

template<typename T>
void PatriciaTree<T>::addNode(T key)
{
	Node<T>* node = search(_root->_left, key, 0);
	size_t firstDifCharge = 1;
	while (getNumDischarge(firstDifCharge, key) == getNumDischarge(firstDifCharge, node->_data))
		++firstDifCharge;

	size_t prevNum = 0;
	Node<T> *prevNode =_root, *curNode = _root->_left;
	while (curNode->_checkNum <= firstDifCharge && prevNode->_checkNum < curNode->_checkNum)
	{
		prevNode = curNode;
		curNode = getNumDischarge(curNode->_checkNum, key) ? curNode->_right : curNode->_left;
	}

	Node<T>* addingNode = new Node<T>(key, firstDifCharge);
	insertNode(prevNode, addingNode, curNode);
}

template<typename T>
void PatriciaTree<T>::insertNode(Node<T>* prev, Node<T>* node, Node<T>* next)
{
	bool discharge = getNumDischarge(node->_checkNum, node->_data);
	if (prev == _root)
		_root->_left = node;
	else if (getNumDischarge(prev->_checkNum, node->_data))
		prev->_right = node;
	else
		prev->_left = node;

	if (discharge)
		node->_left = next;
	else
		node->_right = next;
}

template<typename T>
bool PatriciaTree<T>::getNumDischarge(size_t num, T key)
{
	return ( key >> (CHARBITSIZE - num) ) % 2;
}

template<typename T>
void PatriciaTree<T>::remove(Node<T>*& node)
{
	if (node->_data < node->_left->_data)
		remove(node->_left);
	if (node->_data < node->_right->_data)
		remove(node->_right);
	delete node;
}

template<typename T>
PatriciaTree<T>::~PatriciaTree()
{
	remove(_root);
}

template<typename T>
Node<T>* PatriciaTree<T>::searchNode(T key)
{
	Node<T>* node = search(_root->_left, key, 0);
	return node->_data == key ? node : _root;
}

template<typename T>
Node<T>* PatriciaTree<T>::search(Node<T>*& nodePtr, T& key, size_t prevNum)
{
	if (nodePtr->_checkNum <= prevNum)
		return nodePtr;

	return getNumDischarge(nodePtr->_checkNum, key) ? search(nodePtr->_right, key, nodePtr->_checkNum)
		: search(nodePtr->_left, key, nodePtr->_checkNum);
}

template<typename T>
std::string PatriciaTree<T>::treeToStr()
{
	std::string treeStr;
	treeStr += '0';
	nodeToStr(_root->_left, treeStr);
	return treeStr;
}

template<typename T>
void PatriciaTree<T>::nodeToStr(Node<T>*& nodePtr, std::string& treeStr)
{
	if (std::find(treeStr.begin(), treeStr.end(), nodePtr->_data) != treeStr.end())
		return;

	treeStr += nodePtr->_data;
	
	nodeToStr(nodePtr->_left, treeStr);
	nodeToStr(nodePtr->_right, treeStr);
}


template<typename T>
void PatriciaTree<T>::traversal(Node<T>* nodePtr, std::string& odtStr, std::string& treeStr)
{
	if (nodePtr == _root && std::find(treeStr.begin(), treeStr.end(), '0') != treeStr.end())
		return;

	if (std::find(treeStr.begin(), treeStr.end(), nodePtr->_data) != treeStr.end())
		return;

	treeStr += nodePtr == _root ? '0' : nodePtr->_data;
	addDotNode(odtStr, nodePtr, nodePtr->_left);
	addDotNode(odtStr, nodePtr, nodePtr->_right);
	traversal(nodePtr->_left, odtStr, treeStr);
	traversal(nodePtr->_right, odtStr, treeStr);
}

template<typename T>
void PatriciaTree<T>::graphVizTraversal(std::string& odtStr)
{
	std::string treeStr;
	traversal(_root, odtStr, treeStr);
}

template<typename T>
void PatriciaTree<T>::addDotNode(std::string& dotStr, Node<T>* key, Node<T>* value)
{
	setlocale(LC_ALL, "russian");
	char* res = new char();;
	std::ostringstream oss, vss;
	if (key == _root)
		oss << '0';
	else
		oss << key->_data + 'a';
	dotStr += oss.str();
	dotStr.append(" -> ");
	if (value == _root)
		vss << '0';
	else
		vss << value->_data + 'a';
	dotStr += vss.str();
	dotStr.append(" ;\n");
}


