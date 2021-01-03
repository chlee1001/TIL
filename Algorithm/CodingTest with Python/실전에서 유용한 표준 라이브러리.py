"""
 내장함수: 기본 입출력 함수부터 정렬함수까지 기본적인 함수제공
    - sum(), min(), max(), eval()-사람의 입장으로 작성된 수식 ...
    - sorted(), key 속성(주로 lambda 사용)으로 정렬가능
"""
"""
 itertools: 파이썬에서 반복되는 형태의 데이터를 처리하기 위한 유용한 기능 제공
    - 특히 순열과 조합 라이브러리는 코딩테스트에서 자주사용 (완전탐색 유형에서 유용)
        - 순열: 서로 다른 n개에서 서로 다른 r개를 선택하여 일렬로 나열하는 것 (순서고려O)
        - 조합: 서로 다른 n개에서 순서에 상관없이 서로 다른 r개를 선택하는 것
"""
# 순열과 조합
from itertools import permutations, combinations, product, combinations_with_replacement

data = ['A', 'B', 'C']  # 데이터 준비
resultP = list(permutations(data, 3))  # 모든 순열 구하기
print(resultP)

resultC = list(combinations(data, 2))  # 2개를 뽑는 모든 조합 구하기
print(resultC)

# # 중복 순열과 중복 조합
resultPR = list(product(data, repeat=2))  # 2개를 뽑는 모든 순열 구하기 (중복허용)
print(resultPR)

resultCR = list(combinations_with_replacement(data, 2))  # 2개를 뽑는 모든 조합 구하기 (중복허용)
print(resultCR)

"""
 collections: 덱(deque), 카운터(counter) 등의 유용한 자료구조를 포함
"""
# Counter - 리스트와 같은 반복가능한 객체가 주어졌을 때 내부의 원소가 몇 번씩 등장했는지를 알려줌
from collections import Counter

counter = Counter(['red', 'blue', 'red', 'green', 'blue', 'blue'])
print(counter['blue'])  # 'blue'가 등장한 횟수 출력
print(counter['green'])  # 'green'이 등장한 횟수 출력
print(dict(counter))  # 사전 자료형으로 반환

"""
 math: 필수적인 수학적 기능 제공
    -  팩토리얼, 제곱근, 최대공약수(GCD), 삼각함수 관련 함수부터 파이(pi)와 같은 상수를 포함
"""
import math


# 최소공배수 (LCM)를 구하는 함수
def lcm(a, b):
    return a * b // math.gcd(a, b)


a = 21
b = 14
print(math.gcd(21, 14))  # 최대공약수(GCD) 계산
print(lcm(21, 14))  # 최소공배수(LCM))계산

"""
 heapq: 힙(Heap) 자료구조 제공
    - 일반적으로 우선순위 큐 기능을 구현하기 위해 사용 (dijkstra와 같은 최단경로 알고리즘에 활용)

 bisect: 이진탐색(Binary Search) 기능 제공
"""
