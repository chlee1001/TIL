# N, M, K를 공백으로 구분하여 입력받기
n, m, k = map(int, input().split())
# N개의 수를 공백으로 구분하여 입력받기
data = list(map(int, input().split()))

data.sort()  # 입력받은 수 정력
firstMax = data[n - 1]  # 가장 큰 수
secondMax = data[n - 2]  # 두 번째로 큰 수

# 가장 큰 수가 더해지는 횟수 계싼
count = int(m / (k + 1)) * k
count += m % (k + 1)

result = 0
result += count * firstMax  # 가장 큰 수 더하기
result += (m - count) * secondMax  # 두 번째로 큰 수 더하기

print(result)

"""
반복되는 수열 파악
- 수열은 K+1로 M/(K+1)번 반복된다. M(K+1)에 K를 곱해주면 가장 큰 수의 등장횟수가 된다.
- 이 때 M이 (K+1)로 나누어떨어지지 않는 경우도 고려하여, M/(k+1)의 나머지만큼 가장 큰 수가 추가로 더해진다.
--> 즉, 가장 큰 수가 더해지는 횟수는 'int(m / (k + 1)) * k + m % (k + 1)'
"""