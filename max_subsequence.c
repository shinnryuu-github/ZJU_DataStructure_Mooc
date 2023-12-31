#include <stdio.h>

int max(int nums[], int K)
{
    int max = 0, now = 0;
    for (int i = 0; i < K; i++)
    {
        now += nums[i];
        if (now > max)
        {
            max = now;
        }
        if (now < 0)
        {
            now = 0;
        }
    }
    return max;
}

int main()
{
    int K;
    scanf("%d", &K);
    int nums[K];
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &nums[i]);
    }
    int m = max(nums, K);
    printf("%d", m);
}