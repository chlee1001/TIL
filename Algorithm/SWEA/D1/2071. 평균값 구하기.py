def avg():
    sums=0
    nums = list(map(int, input().split()))
    for i in range(len(nums)):
        sums=sums+nums[i]
    return sums/len(nums)

T = int(input())
for test_case in range(1, T + 1):
    print("#{0} {1}".format(test_case, round(avg())))