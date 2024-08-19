#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>


class Solution
{
public:
    Solution()
    {
#ifdef ONLINE_JUDGE
        static const int _ = iosInit();
#endif  // ONLINE_JUDGE
        input();
        solve();
        output();
    }

private:
    static int iosInit()
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);
        std::setvbuf(stdin, nullptr, _IOFBF, 1 << 20);
        std::setvbuf(stdout, nullptr, _IOFBF, 1 << 20);
        return 0;
    }

    void input()
    {
        std::scanf("%d %d\n", &capacity, &n);

        for (int i = 1; i <= n; ++i)
        {
            std::scanf("%lld %lld %lld\n", &items[i][0], &items[i][1], &items[i][2]);
            k = std::max(k, items[i][2]);
        }
    }

    void solve()
    {
        std::sort(items.begin() + 1, items.begin() + 1 + n, [](const auto & a, const auto & b)
        {
            return a[2] < b[2];
        });

        // dp[g][w]:
        // Max value possible using items from groups [1...g] with weight <= w.
        // dp[g][w] = max(dp[g - 1][w], max(dp[g - 1][w - wi] for i in group g)).

        for (int start = 1, end = 2, g = 1; start <= n; ++g)
        {
            while (end <= n && items[end][2] == items[start][2])
            {
                ++end;
            }

            // start ... end-1 -> i组
            for (int w = 0; w <= capacity; ++w)
            {
                // arr[start...end-1]是当前组，组号一样
                // 其中的每一件商品枚举一遍
                dp[g][w] = dp[g - 1][w];

                for (int i = start; i < end; ++i)
                {
                    // k是组内的一个商品编号
                    if (0 <= w - items[i][0])
                    {
                        dp[g][w] = std::max(dp[g][w], dp[g - 1][w - items[i][0]] + items[i][1]);
                    }
                }
            }

            // start去往下一组的第一个物品
            // 继续处理剩下的组
            start = end;
            ++end;
        }

    }

    void output() const
    {
        std::printf("%lld\n", dp[k][capacity]);
    }

    static constexpr int kMaxCap = 1'010;
    static constexpr int kMaxN = 1'010;
    static constexpr int kMaxGroups = 110;

    int capacity = 0;
    int n = 0;
    long long k = 0LL;

    // weight, value, group.
    std::array<std::array<long long, 3>, kMaxN> items = {};
    std::array<std::array<long long, kMaxCap>, kMaxGroups> dp = {};
};


int main(int argc, char * argv[])
{
#ifndef ONLINE_JUDGE
    std::freopen("var/1.txt", "r", stdin);
#endif  // ONLINE_JUDGE

    Solution s;

    return EXIT_SUCCESS;
}
