import sys
import codecs



def strxor(a, b): # x o r two s t r i n g s of d i f f e r e n t l e n g t h s
    if len(a) > len(b):
        return "".join([chr(ord(x) ^ ord(y)) for(x,y) in zip(a[:len(b)], b)])
    else:
        return "".join([chr(ord(x) ^ ord(y)) for(x, y) in zip(a, b[:len(a)])])

def xor(a,b):
    xored = []
    for i in range(max(len(a), len(b))):
        xored_value = ord(a[i%len(a)]) ^ ord(b[i%len(b)])
        xored.append(hex(xored_value)[2:])
    return ''.join(xored)
def main(): # test
    txt = "3b101c091d53320c000910"
    txt2 = "071d154502010a04000419"
    txt3 = xor(txt,txt2)
    print("Real: 3c0d094c1f523808000d09")
    print("Fals: " + txt3)
    if txt3 == "3c0d094c1f523808000d09":
        print("TRUE!")
    else:
        print("false")



def main2(): # riktig
    fp = open("attachment.txt", "r")
    arr = fp.read().strip().splitlines()
    s = "the".encode("utf-8").hex()


    for i in range(1):
        new = strxor(arr[0], arr[1])
        new2 = new.encode("utf-8").hex()
        for i2 in range(len(new2)):
            new3 = xor(new2[i2:len(s)+i2], s)
            new4 = strxor(new2[i2:len(s)+i2], s)

    #        print("str         :" + new3)

        #print(s)
        #print(new2)



main()
## 10 och 3 codecs.decode(s, "hex").decode('utf-8')
