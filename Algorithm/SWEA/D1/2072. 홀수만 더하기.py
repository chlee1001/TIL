T = int(input())
for i in range(T):
    sum = 0
    nums = list(map(int, input().split()))
    for j in range(len(nums)):
        if nums[j] % 2 == 1:
            sum += nums[j]
    print("#{0} {1}".format(i + 1, sum))


