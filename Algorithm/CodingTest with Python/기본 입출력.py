"""
 표준 입력
 - input(): 한 줄의 문자열을 입력 받는 함수
 - map(): 리스트의 모든 원소에 각각 특정한 함수를 적용할 때
    - list(map(int, input().split()))
    - a, b, c = map(int, input().split())

-  빠르게 입력받기
    - sys 라이브러리에 정의되어 있는 sys.stdin.readline() 메서드 이용
        - 단, 입력 후 엔터(Enter)가 줄 바꿈 기호로 입력되므로 rstrip() 메서드를 함께 이용
        - 이진탐색, 정렬, 그래프 관련 문제에서 자주 사용
"""
# 데이터의 개수 입력
n = int(input())
# 각 데이터를 공백을 기준으로 구분하여 입력
data = list(map(int, input().split()))

data.sort(reverse=True)
print(data)

# 3개의 변수 지정해놓고 입력받기
a, b, c = map(int, input().split())
print(a, b, c)

# # 빠르게 입력받기
import sys

# 문자열 입력받기
data = sys.stdin.readline().rstrip()
print(data)

"""
 표준 출력
 - print()
    - 자동 줄바꿈
    - 자동 줄바꿈이 되지 않도록 end속성 이용: ,end=" "
    
 - f-string (파이썬3.6~)
    - 문자열 앞에 접두사 f를 붙여 사용
    - 중괄호 안에 변수명을 기입하여 간단히 문자열과 정수를 함께 넣을 수 있다.
"""
answer = 7
print("정답은 " + str(answer) + "입니다.")
print(f"정답은 {answer}입니다.")
