repeat=int(input())
path=[]
maxlist=[]
for _ in range(repeat):
    jm=list(map(int,input().split()))
    path.append(jm)       
maxlist=[-1]*(repeat+1)
maxlist[1]=path[0][0]
if repeat>1:
    maxlist[2]=[path[0][0]+path[1][0],path[0][0]+path[1][1]] 
for i in range(repeat+1):
    if i>2:
        answer=[]
        for j in range(i):
            if j==0:
                answer.append(maxlist[i-1][0]+path[i-1][j])
            elif j==i-1:
                answer.append(maxlist[i-1][i-2]+path[i-1][j])
            else:
                answer.append(path[i-1][j]+ max(maxlist[i-1][j],maxlist[i-1][j-1]))
            maxlist[i]=answer
if repeat>1:            
    item=maxlist[-1]
    print(max(item))
else:
    print(path[0][0])
            