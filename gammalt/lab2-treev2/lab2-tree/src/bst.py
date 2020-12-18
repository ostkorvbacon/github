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
        logging.info("TODO@src/bst.py: implement size()")
        return 0

    def height(self):
        '''
        Returns the height of the tree.
        '''
        if self.is_empty()==True:
            return 0
        return 1+max(self.lc().height(),self.rc().height())



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




    def delete(self, v):
        arr=self.preorder()
        arr.remove(v)

        self.__init__(arr[0])
        i=1
        while i<len(arr):
            self.add(arr[i])
            i=i+1

        return self




        #log.info("TODO@src/bst.py: implement delete()")


    if __name__ == "__main__":
        log.critical("module contains no main module")
        sys.exit(1)
