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


    def addh(self, v):
        '''
        Adds the value `v` and returns the new (updated) tree.  If `v` is
        already a member, the same tree is returned without any modification.
        '''
        if self.is_empty():
            self.__init__(value=v)
            return self
        if v=='lc':
            return self.cons(self.lc().addh('None'), self.rc())
        if v=='rc':
            return self.cons(self.lc(), self.rc().addh('None'))


        if v < self.value():
            return self.cons(self.lc().addh(v), self.rc())
        if v > self.value():
            return self.cons(self.lc(), self.rc().addh(v))
        return self

    def add(self, v):
        '''
        Example which shows how to override and call parent methods.  You
        may remove this function and overide something else if you'd like.
        '''
        #  log.debug("calling bst.BST.add() explicitly from child")
        # return bst.BST.add(self, v)
        self.addh(v)


        # TODO: apply this method correctly for add/delete

        return self


    def bf(self):
        if self.lc()==None and self.rc()==None:
            return 0
        if self.lc().value()==None:
            return bst.BST.height(self.rc())
        if self.rc().value()==None:
            return bst.BST.height(self.lc())

        return bst.BST.height(self.lc())-bst.BST.height(self.rc())


    def test(self):
        if  abs(self.bf())<2:
            return False
        else:
            return True

    def balence2(self):
        node=self
        height=bst.BST.height(self)
        i=0
        while i<height:

            if node.lc().test()==True:
                node=node.lc()

            if node.lc().test()==True:
                node=node.rc()
            else:
                return node


                i=i+1

    def balance(self):
        '''
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        '''
         #  log.info("TODO@src/avl.py: implement balance()")
      #  self.slr().srr().dlr().drr() # TODO: apply these methods correctly

        n2=self.balence2()
        print("value rotate: ",n2.value())
        if n2.bf()<0:
            if n2.rc().bf()<0:
                print("höger-höger")
                subroot = n2.slr()
            else:
                subrot = n2.dlr()
                print("höger-vänster")
        else:
            if n2.lc().bf()<0:
                print("vänster-höger")
                subroot = n2.drr()

            else:
                print("vänster-vänster")
                subroot = n2.srr()

        print("subroot", subroot.value())
        return self.set_rc(subroot)

    def slr(self): # tar emot noden som ska roteras och skickar tillbaka noden som ska roteras
        '''
        Performs a single-left rotate around the node rooted at `self`.
        '''

        n1 = self.rc()
        self.set_rc(n1.lc())
        n1.set_lc(self)

        return n1

    def srr(self):
        '''
        Performs a single-right rotate around the node rooted at `self`.
        '''

        n1 = self.lc()
        self.set_lc(n1.rc())
        n1.set_rc(self)

        return n1

    def dlr(self):
        '''
        Performs a double-left rotate around the node rooted at `self`.
        '''
        self.set_lc(self.lc().slr())

        return self.srr()

    def drr(self):
        '''
        Performs a double-right rotate around the node rooted at `self`.
        '''
        self.set_rc(self.rc().srr())

        return self.srl()

if __name__ == "__main__":
    log.critical("module contains no main module")
    sys.exit(1)
