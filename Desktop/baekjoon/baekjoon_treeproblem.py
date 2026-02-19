import sys

# 1. 빠른 입력을 위해 sys.stdin.readline 사용
input = sys.stdin.read
data = input().split()

n = int(data[0])
m = int(data[1])
tree = list(map(int, data[2:]))
def height(k):
    sum=0
    for item in tree:
        if k<item:
            sum+= item-k
    return sum

l=0
h= max(tree)
ans=0
half=(l+h)//2
while l<=h:
    half=(l+h)//2
    if height(half)>=m:
        ans=half
        l=half+1
    else:
        h=half-1
    
print(ans)
