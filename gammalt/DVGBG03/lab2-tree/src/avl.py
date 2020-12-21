#!/usr/bin/env python3

import sys
import bst
import logging

log = logging.getLogger(__name__)

class AVL(bst.BST):
    def __init__(self, value=None):
        '''
        Initializes an empty tree if `value` is None, else a root with the
        specified `value` and two empty children.
        '''
        self.set_value(value)
        if not self.is_empty():
            self.cons(AVL(), AVL())

    def is_root(self):
        node=self

        height=bst.BST.height(self)
        i=0
        while i<height:
            if node.lc().test()==True:
                node=node.lc()

            if node.rc().test()==True:
                node=node.rc()

            else:
                return node.value()
            i=i+1

    def parent(self):
        node=self
        node2=[]
        node2.append(0)
        node2.append(0)

        height=bst.BST.height(self)
        i=0
        while i<height:
            if node.lc().test()==True:
                node2[0]=node
                node=node.lc()
                node2[1]=1

            if node.rc().test()==True:
                node2[0]=node
                node=node.rc()
                node2[1]=0
            else:
                return node2
            i=i+1

    def new_tree(self):
        node=self.parent()
        a=self.is_root()
        subroot=self.balance()

        if a==self.value():
            self=subroot
        else:
            if node[1]==1:
                node[0].set_lc(subroot)

            else:
                node[0].set_rc(subroot)

        return self

    def delete(self, v):
        self.deleteh(v)

        return self.new_tree()

    def add(self, v):
        '''
        Example which shows how to override and call parent methods.  You
        may remove this function and overide something else if you'd like.
        '''
        self.addh(v)
        if self.size()>2:
            return self.new_tree()

        return self

    def bf(self):
        if self.lc()==None and self.rc()==None:
            return 0
        if self.lc()==None:
            return bst.BST.height(self.rc())
        if self.rc()==None:
            return bst.BST.height(self.lc())

        return bst.BST.height(self.lc())-bst.BST.height(self.rc())

    def test(self):
        if  abs(self.bf())<2:
            return False
        else:
            return True

    def balence2(self):
        toggle1=1
        toggle2=0
        node=self
        height=bst.BST.height(self)

        while toggle1 or toggle2:
            if node.lc()!=None and node.lc().test()==True:
                toggle2=1
                toggle1=0
                node=node.lc()

            if node.rc()!=None and node.rc().test()==True:
                toggle2=1
                toggle1=0
                node=node.rc()
            else:
                toggle2=0

                return node

    def balance(self):
        '''
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        '''
        n2=self.balence2()
        if n2.bf()<0:
            if n2.rc().bf()<0:
                return  n2.slr()
            else:
                return n2.dlr()
        else:
            if n2.lc().bf()<0:
                return n2.drr()
            else:
                return n2.srr()

    def slr(self):
        '''
        Performs a single-left rotate around the node rooted at `self`.
        '''
        n1=self.rc()
        self.set_rc(n1.lc())
        n1.set_lc(self)
        return n1

    def srr(self):
        '''
        Performs a single-right rotate around the node rooted at `self`.
        '''
        n1=self.lc()
        self.set_lc(n1.rc())
        n1.set_rc(self)
        return n1

    def dlr(self):
        '''
        Performs a double-left rotate around the node rooted at `self`.
        '''
        self.set_rc(self.rc().srr())
        return self.slr()

    def drr(self):
        '''
        Performs a double-right rotate around the node rooted at `self`.
        '''
        self.set_lc(self.lc().slr())
        return self.srr()

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
