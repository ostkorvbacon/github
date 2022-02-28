import sys
import codecs
import binascii
from binascii import unhexlify



def strxor(a, b): # x o r two s t r i n g s of d i f f e r e n t l e n g t h s
    if len(a) > len(b):
        return "".join([chr(ord(x) ^ ord(y)) for(x,y) in zip(a[:len(b)], b)])
    else:
        return "".join([chr(ord(x) ^ ord(y)) for(x, y) in zip(a, b[:len(a)])])


def bxor(b1, b2): # use xor for bytes
    parts = []
    for b1, b2 in zip(b1, b2):
        parts.append(bytes([b1 ^ b2]))
    return b''.join(parts)


def main(): # riktig
    prntlater = "Error"
    fp = open("attachment.txt", "r")
    arr = fp.read().strip().splitlines()
    guess = "The secret message is: When using a stream cipher, never use the key more than once" # Sista medelandet
    testguess = ["We can factor the number 15 with", # Alla andra medelanden.
                "Euler would probably enjoy that now his theorem becomes a corner stone",
                "The nice thing about Keeyloq is n",
                "The ciphertext produced by a weak encryption",
                "You don't want to buy a set of car keys from a guy who specializes",
                "There are two types of cryptography",
                "There are two types of cyptography: one that allows the Government to use brute force to break the code, and one that requires the Government to use brute force to break you",
                "We can see the point where the chip",
                "A (private-key)  encryption scheme states 3 algorithms"]

    for i in range(9):
        cyph1 = unhexlify(arr[i])
        cyph2 = unhexlify(arr[10])

        new = bxor(cyph1, cyph2)
        print(strxor(new.decode(), guess))

    for i in range(9):
        cyph1 = unhexlify(arr[i])
        cyph2 = unhexlify(arr[10])

        new = bxor(cyph1, cyph2)

        prntlater = "\ntest: message nr " + str(i+1) + "\n" + strxor(new.decode(), testguess[i])
        print(prntlater)




main()
