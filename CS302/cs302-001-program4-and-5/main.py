#Bradley Chang
#CS 302 Program #4 
#This file contains the main where the game will be ran.

from game   import *
from bst    import *
def main():
    print("Welcome")

    #testing BST with ints
    bst_obj = bst()

    bst_obj.insert(50)
    bst_obj.insert(30)
    bst_obj.insert(20)
    bst_obj.insert(40)
    bst_obj.insert(70)
    bst_obj.insert(60)
    bst_obj.insert(80)

    bst_obj.display()



    """
    root = node(0)
    root = node.insert(root, 10)
    root = node.insert(root, 5)
    root = node.insert(root, 15)

    node.display(root)
    """


    


if __name__ == "__main__":
    main()