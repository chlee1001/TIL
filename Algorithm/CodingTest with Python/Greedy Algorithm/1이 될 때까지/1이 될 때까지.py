n, k = map(int, input().split())  # n, k를 공백을 기준으로 구분하여 입력받기
result = 0

while n >= k:  # n이 k보다 크거나 같을 때까지 반복
    while n % k != 0:  # n이 k로 나누어 떨어질 때까지 n에서 1씩 빼기
        n -= 1
        result += 1
    # (n이 K 이상이라면 k로 나누기)
    n //= k
    result += 1

# 마지막 남은 수가 1이 될 때까지 1씩 빼기
while n > 1:
    n -= 1
    result += 1

print(result)