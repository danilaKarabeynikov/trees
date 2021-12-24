#pragma once

template<typename T>
struct Node
{
	Node(T data)
		: _data(data), _left(nullptr), _right(nullptr)
	{}

	T _data;
	Node* _left = nullptr;
	Node* _right = nullptr;
};

template<typename T>
void addDotNode(std::string& dotStr, Node<T>* key, Node<T>* value)
{
	std::ostringstream oss, vss;
	oss << key->_data;
	dotStr += oss.str();
	dotStr.append(" -> ");
	vss << value->_data;
	if (key->_left == value)
	{
		vss << " [ color = red ]";
	}
	else
	{
		vss << " [ color = blue ]";
	}*
	dotStr += vss.str();
	dotStr.append(" ;\n");
}

template<typename T>
class OptimumTree
{
public:
	OptimumTree(T* k, int keyCount, int* p, int pCount, int* q);
	struct MatrixElem
	{
		T key;
		int length;
		int sumWeight;
	};

	~OptimumTree();

	Node<T>* searchNode(T key);
	void printTree();
	void graphVizTraversal(std::string& odtStr);
	std::string treeToStr();
	
private:
	Node<T>* _root;
	int _keyCount;
	MatrixElem** _matrix;

private:
	void remove(Node<T>*& root);
	void setIJElem(int i, int j, int* p, int * q);
	void setMatrix(T* k, int keyCount, int* p, int pCount, int* q);
	void addNodes(Node<T>* curNode, T* k, int leftBegin, int leftEnd, int rightBegin, int rightEnd);
	void printNode(Node<T>*& root, int currentLevel);
	void nodeToStr(Node<T>*& node, std::string& treeStr);
	Node<T>* search(Node<T>*& root, T& key);
	void traversal(Node<T>* node, Node<T>* parentNode, std::string& odtStr);
};


template<typename T>
OptimumTree<T>::~OptimumTree()
{
	if (_root != nullptr)
		remove(_root);

	for (int i = 0; i < _keyCount; ++i)
		delete[] _matrix[i];

	delete[] _matrix;
}

template<typename T>
void OptimumTree<T>::remove(Node<T>*& root)
{
	if (root != nullptr)
	{
		remove(root->_left);
		remove(root->_right);
		delete root;
	}
}

template<typename T>
void OptimumTree<T>::setMatrix(T* k, int keyCount, int* p, int pCount, int* q)
{
	_matrix = new MatrixElem * [keyCount];
	_keyCount = keyCount;
	for (int i = 0; i < keyCount; ++i)
		_matrix[i] = new MatrixElem[keyCount];

	for (int i = 0; i < keyCount; ++i)
	{
		for (int j = 0; j < keyCount; ++j)
		{
			_matrix[i][j].key = i == j ? k[i] : 0;
			_matrix[i][j].length = 0;
			_matrix[i][j].sumWeight = i == j ? p[i] + q[i] + q[i+1] : 0;
		}
	}

	for (int j = 1; j < keyCount; ++j)
	{
		for (int i = 0; i + j < keyCount; ++i)
			setIJElem(i, i + j, p, q);
	}
}

template<typename T>
OptimumTree<T>::OptimumTree(T* k, int keyCount, int* p, int pCount, int* q)
{
	setMatrix(k, keyCount, p, pCount, q);
	int rootInd = 0;
	while (true)
	{
		if (k[rootInd] == _matrix[0][keyCount - 1].key)
			break;
		++rootInd;
	}
	_root = new Node<T>(_matrix[0][keyCount - 1].key);
	addNodes(_root, k, 0, rootInd - 1, rootInd + 1, keyCount - 1);
}

template<typename T>
void OptimumTree<T>::addNodes(Node<T>* curNode, T* k, int leftBegin, int leftEnd, int rightBegin, int rightEnd)
{

	if (leftBegin >= 0 && leftEnd < _keyCount && leftBegin < _keyCount && leftEnd >= 0 && leftBegin <= leftEnd)
	{
		Node<T>* leftNode = new Node<T>(_matrix[leftBegin][leftEnd].key);
		curNode->_left = leftNode;
		int leftNodeInd = 0;
		while (true)
		{
			if (k[leftNodeInd] == _matrix[leftBegin][leftEnd].key)
				break;
			++leftNodeInd;
		}
		addNodes(leftNode, k, leftBegin, leftNodeInd - 1, leftNodeInd + 1, leftEnd);
	}

	if (rightBegin >= 0 && rightEnd < _keyCount && rightBegin < _keyCount && rightEnd >= 0 && rightBegin <= rightEnd)
	{
		Node<T>* rightNode = new Node<T>(_matrix[rightBegin][rightEnd].key);
		curNode->_right = rightNode;
		int rightNodeInd = 0;
		while (true)
		{
			if (k[rightNodeInd] == _matrix[rightBegin][rightEnd].key)
				break;
			++rightNodeInd;
		}
		addNodes(rightNode, k, rightBegin, rightNodeInd - 1, rightNodeInd + 1, rightEnd);
	}
}

template<typename T>
void OptimumTree<T>::setIJElem(int _i, int _j, int* p, int* q)
{
	int T = 0, minT = INT_MAX;
	for (int i = _i; i <= _j; ++i)
		_matrix[_i][_j].sumWeight += p[i] + q[i];

	_matrix[_i][_j].sumWeight += q[_j + 1];

	for (int curRoot = _i; curRoot <= _j; ++curRoot)
	{
		T = 0;
		if (curRoot > 0)
			T += _matrix[_i][curRoot-1].length + _matrix[_i][curRoot - 1].sumWeight;
		if (curRoot < _keyCount - 1)
			T += _matrix[curRoot + 1][_j].length + _matrix[curRoot + 1][_j].sumWeight;

		if (T < minT)
		{
			_matrix[_i][_j].key = _matrix[curRoot][curRoot].key;
			_matrix[_i][_j].length = T;
			minT = T;
		}	
	}
}


template<typename T>
std::string OptimumTree<T>::treeToStr()
{
	std::string treeStr;
	nodeToStr(_root, treeStr);
	return treeStr;
}
template<typename T>
void OptimumTree<T>::nodeToStr(Node<T>*& nodePtr, std::string& treeStr)
{
	if (!nodePtr)
		return;

	treeStr += nodePtr->_data + '0';
	nodeToStr(nodePtr->_left, treeStr);
	nodeToStr(nodePtr->_right, treeStr);
}

template<typename T>
void OptimumTree<T>::printTree()
{
	return this->printNode(_root, 0);
}

template<typename T>
void OptimumTree<T>::printNode(Node<T>*& nodePtr, int currentLevel)
{
	if (!nodePtr)
		return;

	std::string spaces(currentLevel * 3, ' ');
	++currentLevel;
	printNode(nodePtr->_right, currentLevel);
	std::cout << spaces << nodePtr->_data << std::endl;
	printNode(nodePtr->_left, currentLevel);
}

template<typename T>
Node<T>* OptimumTree<T>::searchNode(T key)
{
	return search(_root, key);
}

template<typename T>
Node<T>* OptimumTree<T>::search(Node<T>*& nodePtr, T& key)
{
	if (nodePtr == nullptr)
		return nodePtr;

	Node<T>* leftInd = nullptr;
	leftInd = search(nodePtr->_left, key);
	if (leftInd != nullptr)
		return leftInd;
	return nodePtr->_data == key ? nodePtr : search(nodePtr->_right, key);
}


template<typename T>
void OptimumTree<T>::traversal(Node<T>* node, Node<T>* parentNode, std::string& odtStr)
{
	if (!node)
		return;

	if (parentNode != nullptr)
		addDotNode<T>(odtStr, parentNode, node);

	traversal(node->_left, node, odtStr);
	traversal(node->_right, node, odtStr);
}

template<typename T>
void OptimumTree<T>::graphVizTraversal(std::string& odtStr)
{
	this->traversal(_root, nullptr, odtStr);
}