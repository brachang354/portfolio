#Bradley Chang CS302 Program #4/5
#This file contains the implementation of the BST

#Node class. All BST methods will be implemented in one class
class node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.val = data
    
    def get_left(self):
        return self.left
    def get_right(self):
        return self.right
    
    def set_left(self, new_left):
        self.left = new_left
    def set_right(self, new_right):
        self.right = new_right

    def get_data(self):
        return self.val
    
    def display_node(self):
        print(self.data)

    """
    def insert(root, data):
        if root is None:
            return node(data)
        else:
            if root.val < data:
                root.left = node.insert(root.left, data)
            else:
                root.right = node.insert(root.right, data)

        return root
    
    def display(root):
        if root:
            node.display(root.left)
            print(root.val)
            node.display(root.right) """

#BST Class to implement insert, display all, remove all
class bst:
    
    #initialization of root
    def __init__(self):
        self.root = None

    #Insert Wrapper
    def insert(self, data):
        if self.root == None:
            self.root = node(data)
            return
        else:
            self.root = self._insert(self.root, data)
            return
    
    #Insert recursive call
    def _insert(self, root, data):
        if root == None:
            root = node(data)
            return root
        if(data < root.val):
            root.set_left(self._insert(root.get_left(), data))
            return root
        else:
            root.set_right(self._insert(root.get_right(), data))
            return root
    
    def display(self):
        if self.root != None:
            self._display(self.root)

    def _display(self, root):
        if root == None:
            return
        self._display(root.left)
        print(root.val)
        self._display(root.right)

        



    """
    #Insert into BST function
    def insert(self, root, data):
        if root is None:        #If root is null, then we insert a new node
            root = node(data)
            return root
        
        if data < root.get_data(): #Else we traverse
            self.insert(root.get_left(), data)
        else:
            self.insert(root.get_right(), data)


    def display(self, root):
        if root == None:
            return
        self.display(root.get_left())

        root.display_node()

        self.display(root.get_right())

        return
    """
        



"""
        if (self.value):
            self.left = bst()
            self.right = bst()
        else:
            self.left = None
            self.right = None

    def is_empty(self):
        return (self.value == None)
"""