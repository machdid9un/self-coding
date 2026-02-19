import heapq
repeat=int(input())
numlist=[]
answer=0
for _ in range(repeat):
    k=int(input())
    heapq.heappush(numlist,k)

if len(numlist)>=2:
    a=heapq.heappop(numlist)
    b=heapq.heappop(numlist)
    sum=a+b  
    answer+=sum 
    heapq.heappush(numlist,sum)    
    while len(numlist)>1:       
        a=heapq.heappop(numlist)
        b=heapq.heappop(numlist)
        sum=a+b  
        answer+=sum 
        heapq.heappush(numlist,sum) 
else:
    answer=0

print(answer)    
    