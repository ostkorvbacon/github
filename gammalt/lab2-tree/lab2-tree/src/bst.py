#!/usr/bin/env python3
import copy
import bt
import sys
import logging

log = logging.getLogger(__name__)

class BST(bt.BT):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(BST(), BST())

    def is_member(self, v):
        '''
        Returns true if the value `v` is a member of the tree.
        '''
        if self.is_empty()==True:
            return False
        if v==self.value():
            return True
        if self.lc().is_member(v)==True:
            return True
        if self.rc().is_member(v)==True:
            return True
        return False

    def size(self):
        '''
        Returns the number of nodes in the tree.
        '''
        if self.is_empty()==True:
            return 0
        return 1+self.lc().size()+self.rc().size()

        return 0

    def height(self):
        if self.value() is None:
            return 0

        else:
        # Compute the depth of each subtree
            lDepth = self.lc().height()
            rDepth = self.rc().height()

        # Use the larger one
        if (lDepth > rDepth):
            return lDepth+1
        else:
            return rDepth+1

    def preorder(self):
        '''
        Returns a list of all members in preorder.
        '''
        if self.is_empty():
            return []
        return [self.value()] + self.lc().preorder() + self.rc().preorder()

    def inorder(self):
        '''
        Returns a list of all members in inorder.
        '''
        if self.is_empty():
            return []
        return  self.lc().inorder() + [self.value()] + self.rc().inorder()

    def postorder(self):
        '''
        Returns a list of all members in postorder.
        '''
        if self.is_empty():
            return []
        return  self.lc().postorder() + self.rc().postorder() + [self.value()]

    def bfs_help(self,node,i,arr):
        if node.value()==None:
            arr.append('None')
            return []
        if i==0:
            arr.append(node.value())
        else:
            if node.lc().value()==None:
                node.add('lc')

            self.bfs_help(node.lc(),i-1,arr)

            if node.rc().value()==None:
                node.add('rc')

            self.bfs_help(node.rc(),i-1,arr)

        return []

    def bfs_order_star(self):
        '''
        Returns a list of all members in breadth-first search* order, which
        means that empty nodes are denoted by "stars" (here the value None).
        For example, consider the following tree `t`:
                    10
              5           15
           *     *     *     20
        The output of t.bfs_order_star() should be:
        [ 10, 5, 15, None, None, None, 20 ]
        '''
        arr =[]
        i=0
        node=copy.deepcopy(self)
        height=self.height()
        while i<height:
            self.bfs_help(node,i,arr)
            i=i+1

        return arr

    def add(self, v):
        '''
        Adds the value `v` and returns the new (updated) tree.  If `v` is
        already a member, the same tree is returned without any modification.
        '''
        if self.is_empty():
            self.__init__(value=v)
            return self
        if v=='lc':
            return self.cons(self.lc().add('None'), self.rc())
        if v=='rc':
            return self.cons(self.lc(), self.rc().add('None'))


        if v < self.value():
            return self.cons(self.lc().add(v), self.rc())
        if v > self.value():
            return self.cons(self.lc(), self.rc().add(v))
        return self

    def find_member(self, v):
        '''
        Returns location if the value `v` is a member of the tree.
        '''
        if self.value()==None:
            print("Empty")
            return False

        if v==self.lc().value() or v==self.rc().value():
            return self

        if self.lc().is_member(v)==True:
            return self.lc().find_member(v)

        if self.rc().is_member(v)==True:
            return self.rc().find_member(v)

        if self.value() == v:
            print("Value is root")
            return self.value()

    def min_right(self):
        if self.lc().value() == None:
            print("min_right: ", end='')
            print(self.value())
            return self
        else:
            return self.lc().min_right()

    def delete(self, v):
        '''
        Removes the value `v` from the tree and returns the new (updated) tree.
        If `v` is a non-member, the same tree is returned without modification.
        '''
        parent=self.find_member(v)

        if parent.lc().value() == v: #kollar om noden som ska bort är ett höger eller vänsterlöv
            node=parent.lc()
        else:
            node=parent.rc()

        if node.lc().value() == None and node.rc().value() == None: #Lövnod
            node.set_lc(None)
            node.set_rc(None)
            node.set_value(None)
            return self
            node.set_lc(None)
            node.set_rc(None)
            node.set_value(None)
            return self

        elif node.lc().value() != None and node.rc().value() == None: # om noden som ska bort bara har vänsterbarn
            if parent.lc().value() == v:
                parent.set_lc(node.lc())
            else:
                parent.set_rc(node.lc())
            return self

        elif node.lc().value() == None and node.rc().value() != None: # om noden som ska bort bara har högerbarn
            if parent.lc().value() == v:
                parent.set_lc(node.rc())
            else:
                parent.set_rc(node.rc())
            return self

        else: # Om noden som ska bort har höger och vänsterbarn
            swap = node.rc().min_right() #hittar noden som ska läggas in där noden som försvinner var
            if swap.lc().value() == None and swap.rc().value() == None: #om noden som ska läggas in är en lövnod tas den bara bort
                swap.set_lc(None)
                swap.set_rc(None)
                swap.set_value(None)
            else: #om noden som ska läggas in har barn kallas delete med denna nod som värde.
                self.delete(swap.value())

            node.set_value(swap.value())

            return self

    if __name__ == "__main__":
        log.critical("module contains no main module")
        sys.exit(1)
