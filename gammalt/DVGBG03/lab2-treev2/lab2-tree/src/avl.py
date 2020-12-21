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

    def add(self, v):
        '''
        Example which shows how to override and call parent methods.  You
        may remove this function and overide something else if you'd like.
        '''
        bst.BST.add(self, v)
        log.debug("calling bst.BST.add() explicitly from child")
        #self.balance() # TODO: apply this method correctly for add/delete
        return self

    def balance(self):
        '''
        AVL-balances around the node rooted at `self`.  In other words, this
        method applies one of the following if necessary: slr, srr, dlr, drr.
        '''
        #self.set_lc(self.lc().dlr()) # TODO: apply these methods correctly
        count = 0
        self.is_balanced(self.height(), count)

        return self

    def is_balanced(self, h, count):

        if self.lc() == None and self.rc() == None:
            if (h - count) > 1:
                return False
            else:
                return True
        else:
            self.lc().is_balanced(h, (count+1))
            self.rc().is_balanced(h, (count+1))


    def rotate_node():
        if self.lc().value() == None and self.rc().value() == None:
            print("value test2: ", self.value())
            return self.value()

        if self.lc().height() > self.rc().height():
            return self.lc().is_balanced()
        else:
            return self.rc().is_balanced()


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
