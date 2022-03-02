# Based on code from: https://reqbin.com/req/nfilsyk5/get-request-example

#Runtime ca 10 min

import requests
from requests.structures import CaseInsensitiveDict
import time

array=["0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"]

url = "http://dart.cse.kau.se:12345/auth/30/<KAUID>/"
padd="000000000000000000000000000000"
headers = CaseInsensitiveDict()
headers["Accept"] = "*/*"
timer=time.time()
test=1
while len(url)<75:
    
    for i in array:
        for j in array:

            start = time.time()
            resp = requests.get(url+i+j+padd, headers=headers)
            proc_time=time.time()-start
        

            if proc_time>0.03*test:
                print(resp.status_code)
                print(proc_time)
                url=url+i+j
                print(padd)
                padd=padd[1:]
                padd=padd[1:]
                print(padd)
                print(i+j)
                print(url)
                print(time.time()-timer)
                print()
                break

        else: 
            continue
        break
    test=test+1
    print(test)
    
print(time.time()-timer)
