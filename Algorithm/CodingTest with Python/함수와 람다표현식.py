"""
 파이썬 내의 함수의 종류
 - 내장함수: 기본 제공함수
 - 사용자 정의함수: 직접 정의하는 함수
    - 매개변수, 반환 값 --> def 함수명(매개변수):
                                실행할 소스코드
                                return 반환 값

 global 키워드
 - global 키워드로 변수를 지정하면 해당 함수에서는 지역변수를 만들지 않고,
 함수바깥에 선언된 변수를 바로 참조하게 된다.
 - 단순히 함수바깥의 변수를 사용하는 것은 오류가 없지만, 값을 수정할 때는 global 키워드로 변수를 지정해줘야한다.
    - 전역변수로 리스트가 선언되어있을 때에는 global 없이 사용가능하지만,
    동일한 변수명의 지역변수가 선언되면 함수 내부의 지역변수를 우선적으로 건들인다.

 여러개의 반환값
 - 파이썬에서 함수는 여러개의 반환값을 가질 수 있다. // C++에서는 별도 포인터 혹은 클래스, 구조체를 이용하지만...
 함수에서 여러개의 반환 값을 가지는 것을 packing이라고 하고, 별도의 변수에 넣어주는 것을 unpacking이라고 한다.
"""


def add(a, b):
    return a + b


def add2(a, b):
    print('함수의 결과:', a + b)


print(add(3, 7))
add2(b=3, a=7)

# Global 키워드
a = 0


def func():
    global a
    a += 1


for i in range(10):
    func()

print(a)

# 전역변수로 리스트
array = [1, 2, 3, 4, 5]


def func():
    array = [3, 4, 5]
    array.append(6)
    print(array)


func()
print(array)

"""
 람다표현식
 - 함수를 정의한 후, 함수를 불러 사용하는 것이 아니라, 한줄의 람다표현식을 이용하여...함수처럼 사용?
 - 함수를 한번 사용할 때 유용
"""
print((lambda a, b: a + b)(3, 7))

# 내장함수에서 자주 사용되는 람다함수
array = [('홍길동', 50), ('이순신', 32), ('아무개', 74)]


def my_key(x):
    return x[1]


print(sorted(array, key=my_key))
print(sorted(array, key=lambda x: x[1]))

list1 = [1, 2, 3, 4, 5]
list2 = [6, 7, 8, 9, 10]
result = map(lambda a, b: a + b, list1, list2)

print(list(result))
