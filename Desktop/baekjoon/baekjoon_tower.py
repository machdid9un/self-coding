import sys

input= sys.stdin.readline

k= int(input())
numlist=list(map(int,input().split()))
length=len(numlist)

answerlist=[]
stack=[]
for i in range(length):
    
    while stack:
        if stack[-1][0]< numlist[i]:
            stack.pop()
        
        else:
            answerlist.append(stack[-1][1]+1)
            break
    
    if not stack:
        answerlist.append(0)
    stack.append((numlist[i],i))



for item in answerlist:
    print(item, end=' ')

    

