import sys
input = sys.stdin.readline

n, m = map(int, input().split())
r, c, d = map(int, input().split())
count = 0
walllist = []
for _ in range(n):
    walllist.append(list(map(int, input().split())))

def cleaning(a, b):
    global count
    if walllist[a][b] == 0:
        walllist[a][b] = -1 # 청소 완료 표시
        count += 1

def cleancheck(a, b):
    # 주변 4칸 중 하나라도 0(청소 전)이 있는지 수동 체크
    if a + 1 < n and walllist[a+1][b] == 0: return True
    if a - 1 >= 0 and walllist[a-1][b] == 0: return True
    if b + 1 < m and walllist[a][b+1] == 0: return True
    if b - 1 >= 0 and walllist[a][b-1] == 0: return True
    return False

def process(a, b, d):
    while True:
        cleaning(a, b) # 1. 현재 위치 청소
        
        if cleancheck(a, b): # 2. 주변에 청소되지 않은 빈 칸이 있는 경우
            # 90도 반시계 회전하고 앞 확인 (이걸 한 세트로!)
            if d == 0: d = 3
            else: d -= 1
            
            # 회전 후 바라보는 방향의 앞쪽 칸 확인
            if d == 0: # 북쪽
                if walllist[a-1][b] == 0: a -= 1
            elif d == 1: # 동쪽
                if walllist[a][b+1] == 0: b += 1
            elif d == 2: # 남쪽
                if walllist[a+1][b] == 0: a += 1
            elif d == 3: # 서쪽
                if walllist[a][b-1] == 0: b -= 1
            # 주의: 이동했든 안 했든 다시 루프 처음으로 돌아가야 함!
            
        else: # 3. 주변에 청소되지 않은 빈 칸이 없는 경우 (후진 로직)
            can_back = False
            if d == 0: # 북 보고 있으면 남(a+1)으로 후진
                if walllist[a+1][b] != 1: a += 1; can_back = True
            elif d == 1: # 동 보고 있으면 서(b-1)로 후진
                if walllist[a][b-1] != 1: b -= 1; can_back = True
            elif d == 2: # 남 보고 있으면 북(a-1)으로 후진
                if walllist[a-1][b] != 1: a -= 1; can_back = True
            elif d == 3: # 서 보고 있으면 동(b+1)으로 후진
                if walllist[a][b+1] != 1: b += 1; can_back = True
            
            if not can_back: # 후진 못 하면 작동 중지
                print(count)
                return

process(r, c, d)