

        def genToBin(self): # konverterar från generellt träd till binary serch tree via två funktioner

            return arrayToBin(genToArray1(self)) #returnar binära trädet

        def genToArray1(self):
            arr = None
            if self == None
                return[]
            for j in range(0, len(self.children)): # loopar för alla barn i huvudnoden.
                arr.insert(self.children[j].value()) lägger
                arr = arr + self.genToArray2(self, i)
            arr.insert(self.value()) #lägger in värdet för rotnoden
            return arr.sort()

        def genToArray2(self, i):
            self = self.children[i]
            if self != None:
                for j in range(0, len(self.children)): # loopar för alla barn i en nod.
                    if self.children[j] != None:
                        arr.insert(self.children[j].value()) #lägger till alla värden för barnen i våran array
                        arr = arr + self.genToArray2(self, j) #kallar på funktionen för alla barn
            return arr #returnar alla noder förutom head och heads barn.



        def arrayToBin(self, array):
            for i in range(0, len(array)):
                binTree._tree = binTree._tree.add(array[array[i]]) # lägger till alla noder i arrayen till ett bin search tree

            return binTree
