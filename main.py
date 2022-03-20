#! /usr/local/bin/python3

import json

fp = open("tmp.json", "r")
x = fp.read()
fp.close()
a = str(x).strip("'<>() ")
y = json.loads(a)

test1 = y["data"]
c = json.dumps(test1)
d = json.loads(c)
test2 = d["children"]
lenoflist = len(test2)

bp = open("imagelist", "w")

u = 0
while u < lenoflist:
    e = json.dumps(test2[u])
    f = json.loads(e)
    test3 = f["data"]
    g = json.dumps(test3)
    h = json.loads(g)
    try:
        test4 = h["url_overridden_by_dest"]
        bp.write(test4 + "\n")
        u = u + 1
    except:
        u = u + 1

bp.close()

