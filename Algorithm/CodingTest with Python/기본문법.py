"""
 리스트 자료형
"""

# # 리스트에서 특정 값을 가지는 원소를 모두 제거하기

a = [1, 2, 3, 4, 5, 5, 5]
remove_set = {3, 5}  # 집합 자료형

# remove_set에 포함되지 않은 값만을 저장
result = [i for i in a if i not in remove_set]
print(result)

"""
 문자열 자료형
"""
print("-" * 10 + "문자열 자료형" + "-" * 10)
# # 문자열 자료형
data = 'Hello World'
print(data)

data = "Don't you know \"Python\"?"
print(data)

# # 문자열 연산
a = "Hello"
b = "World"
print(a + " " + b)

a = "String"
print(a * 3)

a = "ABCDEF"
print(a[2:4])

"""
 튜플 자료형
 - 한번 선언된 값을 변경할 수 없다. --> 특정 index의 값을 변경하고자 하면 오류
 - 리스트는 대괄호[]를 이용하지만, 튜플은 소괄호()를 이용한다
 - 튜플은 리스트보다 공간효율적이다.
 
 장점
 - 서로 다른 성질의 데이터를 묶어서 관리해야할 때 - 최단 경로 알고리즘 (비용, 노드번호), 학생 정보
 - 데이터 나열을 해싱의 키 값으로 사용해야할 때 (튜플은 변경이 불가능하기 떄문에 사용될 수 있다.)
 - 리스트보다 메모리를 효율적으로 사용해야 할 때
"""
print("-" * 10 + "튜플 자료형" + "-" * 10)
a = (1, 2, 3, 4, 5, 6, 7, 8, 9)

# 네 번째 원소만 출력
print(a[3])

# 두 번째 원소부터 네 번째 원소까지
print(a[1:4])

"""
 사전 자료형
 - 키와 값의 쌍을 데이터로 가지는 자료형
 - 변경 불가능한 자료형을 키로 사용할 수 있다.
 - 해시 테이블을 이용하므로 데이터의 조회 및 수정에 있어서 O(1)의 시간에 처리가능
 
 관련 메소드
 - 키 데이터만 뽑아서 리스트로 이용할 때: keys()함수
 - 값 데이터만 뽑아서 리스트로 이용할 때: values()함수
"""
print("-" * 10 + "사전 자료형" + "-" * 10)
data = dict()
data['사과'] = 'Apple'
data['바나나'] = 'Banana'
data['코코넛'] = 'Coconut'

print(data)
data2 = {
    '사과': 'Apple',
    '바나나': 'Banana',
    '코코넛': 'Coconut',
}
print(data2)

if '사과' in data:
    print("\'사과\'를 키로 가지는 데이터가 존재합니다.")

# 키 데이터만 담은 리스트
key_list = data.keys()
print(key_list)
print(list(key_list))

# 값 데이터만 담은 리스트
value_list = data.values()
print(value_list)

#  각 키에 따른 값을 하나씩 출력
for key in key_list:
    print(data[key])

"""
 집합 자료형
 - 중복을 허용하지 않음
 - 순서가 없음
 - 리스트 혹은 문자열을 이용하여 초기화 할 수 있다. - set()함수 이용
 - 데이터의 조회 및 수정에 있어서 O(1)의 시간에 처리할 수 있다.
 
 연산
 - 합집합, 교집합, 차집합 등...
 
 관련 함수
 - 새로운 원소 추가: add
 - 새로운 원소 여러개 추가: update
 - 특정한 값을 갖는 원소 삭제: remove
"""
print("-" * 10 + "집합 자료형" + "-" * 10)
# 집합 자료형 초기화 방법 1
data = set([1, 1, 2, 3, 4, 4, 5])
print(data)

# 집합 자료형 초기화 방법 2
data = {1, 1, 2, 3, 4, 4, 5}
print(data)

# # 집합 자료형의 연산
a = {1, 2, 3, 4, 5}
b = {3, 4, 5, 6, 7}
# 합집합
print(a | b)
# 교집합
print(a & b)
# 차집합
print(a - b)

# # 집합 자료형 관련 함수
data = {1, 2, 3}
print(data)
# 새로운 원소 추가
data.add(4)
print(data)
# 새로운 원소 여러 개 추가
data.update([5, 6])
print(data)
# 특정한 값을 갖는 원소 삭제
data.remove(3)
print(data)

"""
 사전 자료형과 집합 자료형의 특징
 - 리스트나 튜플을 순서가 있기 때문에 인덱싱을 통해 자료형의 값을 얻을 수 있다.
 - 사전 자료형과 집합 자료형은 순서가 없기 때문에 인덱싱으로 값을 얻을 수 없다.
    - 사전의 key 혹은 집합의 element를 이용해 O(1)의 시간 복잡도로 조회한다.
"""