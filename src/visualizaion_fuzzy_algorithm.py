import matplotlib.pyplot as plt
import time

match_score = 2
mismatch_score = 1
gap_penalty = -1

def score(a, b):
    return match_score if a == b else mismatch_score

def opt_DP(left_unit, right_unit, insertion):
    m = len(left_unit)
    n = len(right_unit)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    max_score = 0
    end_pos_right = 0
    for i in range(1, m + 1):
        start_j = max(1, end_pos_right)
        end_j = min(n, end_pos_right + insertion + 1)
        for j in range(start_j, end_j + 1):
            match = dp[i - 1][j - 1] + score(left_unit[i - 1], right_unit[j - 1])
            delete_ = dp[i - 1][j] + gap_penalty
            insert = dp[i][j - 1] + gap_penalty
            dp[i][j] = max(0, match, delete_, insert)
            if dp[i][j] > max_score:
                max_score = dp[i][j]
                end_pos_right = j
    return dp

def DP(left_unit, right_unit):
    m = len(left_unit)
    n = len(right_unit)
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    max_score = 0
    end_pos_right = 0
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            match = dp[i - 1][j - 1] + score(left_unit[i - 1], right_unit[j - 1])
            delete_ = dp[i - 1][j] + gap_penalty
            insert = dp[i][j - 1] + gap_penalty
            dp[i][j] = max(0, match, delete_, insert)
            if dp[i][j] > max_score:
                max_score = dp[i][j]
                end_pos_right = j
    return dp

def visualize(left_unit, right_unit, dp_matrix1, title1, dp_matrix2, title2, filename):
    fig, axes = plt.subplots(1, 2, figsize=(12, 6))

    cax1 = axes[0].imshow(dp_matrix1, cmap='viridis')
    axes[0].set_title(title1)
    axes[0].set_xticks(range(1, len(right_unit) + 1))
    axes[0].set_xticklabels(right_unit)
    axes[0].set_yticks(range(1, len(left_unit) + 1))
    axes[0].set_yticklabels(left_unit)

    cax2 = axes[1].imshow(dp_matrix2, cmap='viridis')
    axes[1].set_title(title2)
    axes[1].set_xticks(range(1, len(right_unit) + 1))
    axes[1].set_xticklabels(right_unit)
    axes[1].set_yticks(range(1, len(left_unit) + 1))
    axes[1].set_yticklabels(left_unit)

    fig.colorbar(cax1, ax=axes[0], location='right', label='Score')
    fig.colorbar(cax2, ax=axes[1], location='right', label='Score')

    plt.tight_layout() # 用于确保标签的可见性
    plt.savefig(filename, format='pdf')
    plt.close()


if __name__ == '__main__':
    left_unit = "ATCGCGAGC"
    right_unit = "ATCGCGAAGC"
    ins = 2

    start_time_opt = time.perf_counter_ns()
    for i in range(10000):
        opt_DP(left_unit, right_unit, ins)
    end_time_opt = time.perf_counter_ns()

    start_time_dp = time.perf_counter_ns()
    for i in range(10000):
        DP(left_unit, right_unit)
    end_time_dp = time.perf_counter_ns()

    print("Time taken by opt_DP:", (end_time_opt - start_time_opt) / 1e3, "microseconds")
    print("Time taken by DP:", (end_time_dp - start_time_dp) / 1e3, "microseconds")

    dp_matrix_opt = opt_DP(left_unit, right_unit, ins)
    dp_matrix_dp = DP(left_unit, right_unit)

    visualize(left_unit, right_unit, dp_matrix_opt, 'opt_DP', dp_matrix_dp, 'DP', 'comparison.pdf')
