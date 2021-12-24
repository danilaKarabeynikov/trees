class Node:
    def __init__(self, data=None, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return 'Node ['+str(self.data)+']'

# класс, описывающий само дерево */


class Tree:
    def __init__(self):
        self.root = None  # корень дерева

# /* функция для добавления узла в дерево */
    def newNode(self, data):
        return Node(data, None, None)

    def height(self, node):
        if node == None:
            return 0
        else:
            lheight = self.height(node.left)
            rheight = self.height(node.right)

            if lheight > rheight:
                return lheight + 1
            else:
                return rheight + 1

    def lookup(self, node, target):
        if node == None:
            return 0
        else:
            if target == node.data:
                return 1
            else:
                if target < node.data:
                    return self.lookup(node.left, target)
                else:
                    return self.lookup(node.right, target)

    def printGivenLevel(self, Root, level):
        if Root == None:
            return
        if level == 1:
            print("%d " % Root.data)
        elif level > 1:
            self.printGivenLevel(Root.left, level - 1)
            self.printGivenLevel(Root.right, level - 1)

        # /* функция для распечатки дерева */

    def printLevelorder(self, root):
        h = self.height(self.root)
        i = 1
        while i <= h:
            self.printGivenLevel(self.root, i)
            i += 1

    def in_order(self, node):
        if node:
            self.in_order(node.left)
            print(node.value)
            self.in_order(node.right)
