repeatnum= int(input())
tuplist=[]
for i in range(repeatnum):
    word=str(input())
    length=len(word)
    tup=(length,word)
    if tup in tuplist:
        continue
    tuplist.append(tup)

tuplist.sort()
for item in tuplist:
    print(item[1])