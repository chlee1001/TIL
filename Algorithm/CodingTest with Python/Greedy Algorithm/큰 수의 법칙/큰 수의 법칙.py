n, m, k = map(int, input().split())
data = list(map(int, input().split()))

data.sort()
firstMax = data[n - 1]
secondMax = data[n - 2]

result = 0

while True:
    for _ in range(k):
        if m == 0:
            break
        result += firstMax
        m -= 1
    if m == 0:
        break
    result += secondMax
    m -= 1

print(result)
