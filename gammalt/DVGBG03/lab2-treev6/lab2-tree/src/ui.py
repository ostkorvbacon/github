#!/usr/bin/env python3

import bst
import avl
import logging
import bst as fl

log = logging.getLogger(__name__)

class TerminalUI:
    def __init__(self, mode):
        '''
        Select BST mode by passing "bst" as argument; otherwise select AVL mode.
        '''
        if mode == "bst":
            logging.info("running in BST mode")
            self._tree = bst.BST()
        else:
            logging.info("running in AVL mode")
            self._tree = avl.AVL()

    def run(self):
        '''
        Provides a terminal-based UI to perform tree operations.
        '''
        self.display_menu()
        while True:
            opt, err = self.get_choice()
            if err is not None:
                self.display_error(err)
                continue

            if opt == "m":
                self.display_menu()
            elif opt == "t":
                self.display_tree()
            elif opt == "a":
                self.add_value()
            elif opt == "d":
                self.delete_value()
            elif opt == "f":
                self.is_member()
            elif opt == "q":
                break
            else:
                log.error("menu case '{}' is missing, aborting".format(opt))
                return 1

    def display_menu(self):
        '''
        Shows a menu which is encapsulated between a top rule and a bottom rule.
        '''
        print(self.menu_rule("top", self.menu_width()))
        for opt in self.menu_options():
            print("\t{}".format(opt))
        print(self.menu_rule("bot", self.menu_width()))

    def display_error(self, err):
        '''
        Shows an error message.
        '''
        print("error> {}".format(err))

    def display_tree(self):
        '''
        Shows the tree's structure and content.
        '''
        if self._tree.is_empty():
            print("\n  Tree is empty\n")
            return

        self.show_2d()
        print("")
        print("Size:      {}".format(self._tree.size()))
        print("Height:    {}".format(self._tree.height()))
        print("Inorder:   {}".format(self._tree.inorder()))
        print("Preorder:  {}".format(self._tree.preorder()))
        print("Postorder: {}".format(self._tree.postorder()))
        print("BFS star:  {}".format([
            v if v is not None else "*" for v in self._tree.bfs_order_star()
        ]))
        print("")

    def add_value(self):
        '''add_value:
        Prompts the user for an integer which is added to the tree.
        '''
        value, err = self.get_int("Enter value to be added")
        if err is not None:
            self.display_error(err)
            return
        self._tree = self._tree.add(value)

    def delete_value(self):
        '''delete_value:
        Prompts the user for an integer which is removed from the tree.
        '''
        value, err = self.get_int("Enter value to be deleted")
        if err is not None:
            self.display_error(err)
            return
        self._tree = self._tree.delete(value)

    def is_member(self):
        '''is_member:
        Prompts the user for a value that is checked for membership in the tree.
        '''
        value, err = self.get_int("Enter search value")
        if err is not None:
            self.display_error(err)
            return

        print("\n  {} is a {}member\n".format(
            value,
            "" if self._tree.is_member(value) is True else "non-"),
        )

    def menu_rule(self, pos, width):
        '''
        Returns a horizontal line using stars or tildes.
        '''
        return ("*" if pos == "top" else "~") * width

    def menu_width(self):
        '''
        Returns the menu width.
        '''
        return 32

    def menu_options(self):
        '''
        Returns a list of printable menu options.  Blank entries will be interpreted
        as new lines, and single characters before the colon as hotkeys.
        '''
        return [
            "m: menu",
            "t: display tree",
            "",
            "a: add value",
            "d: delete value",
            "f: test membership",
            "",
            "q: quit",
        ]
    def menu_hotkeys(self):
        '''
        Returns a list of symbols that the menu defined as valid hotkeys.
        '''
        opts = self.menu_options()
        return [ o.split(":")[0] for o in opts if len(o.split(":")[0]) == 1 ]

    def get_choice(self):
        '''
        Attempts to read a valid menu option from the user.  Caller should look
        for errors by comparing the second return value against ``not None''.
        '''
        buf = input("menu> ")
        if len(buf) != 1:
            return None, "input must be a a single character"
        if buf[0] not in self.menu_hotkeys():
            return None, "invalid choice"
        return buf[0], None

    def get_int(self, message):
        '''
        Writes a message to stdout and waits for an integer from stdin.
        '''
        buf = input("{}> ".format(message))
        try:
            return int(buf), None
        except ValueError:
            return None, "invalid input (not an integer)"

    def arr3_help(self, arr, arr2,size,height): #hjälp funktion för justering av avstånd för
        j=0                                     #negativa värden då de är bredare änn positiva.
        arr3=[]
        k=0
        while k<height:
            arr3.append(0)
            k=k+1
        while j<size:
            if type(arr[j])==int:
                if arr[j]<0:
                    k=0
                    while k<height-1:
                        if j<arr2[k+1]:
                            arr3[k]=arr3[k]+1
                            break
                        k=k+1
            j=j+1
        return arr3

    def show_2d(self):
        '''
        Shows a pretty 2D tree based on the output of bfs_order_star(). None
        values are are replaced by stars ("*").
        '''
        i=0
        j=0
        level=0
        arr=[]
        arr2=[]
        arr3=[]
        k=0
        height=self._tree.height()
        while j<height:
            arr2.append(pow(2, j)-1)
            j=j+1
        arr=self._tree.bfs_order_star()
        size=len(arr)
        j=0
        while j<size:
            neg=0
            if arr[j]=='None':
                arr[j]='*'
            j=j+1

        arr3=self.arr3_help(arr,arr2,size,height)
        while i<size:
            j=0
            while j<height:
                if i==arr2[j]:
                    print("")
                    space=(pow(2,height))/2-arr2[j]-arr3[j]
                    level=level+1
                    k=0
                    while k<space:
                        print(" ",end='')
                        k=k+1
                j=j+1
            print(arr[i],"",end='')
            i=i+1

if __name__ == "__main__":
    logging.critical("ui contains no main module")
    sys.exit(1)
