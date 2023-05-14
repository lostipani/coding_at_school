import binarytree as bt
from binarytree import build
from binarytree import bst

depth = 3
nodes = [3,51,6,7,None]

root_bin = build(nodes)
root_bst = bst(depth, is_perfect=True)


print('Binary tree sample: ', root_bin)
print('BST random tree sample: ', root_bst)
