import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

def score(a, b, match_score=2, mismatch_score=1):
    return match_score if a == b else mismatch_score

def DP(left, right, gap_penalty=-1):
    m, n = len(left), len(right)
    dp = np.zeros((m+1, n+1), dtype=int)
    for i in range(1, m+1):
        for j in range(1, n+1):
            match = dp[i-1, j-1] + score(left[i-1], right[j-1])
            delete = dp[i-1, j] + gap_penalty
            insert = dp[i, j-1] + gap_penalty
            dp[i, j] = max(0, match, delete, insert)
    return dp

def optimizedDP(left, right, maxInsertLength=1, gap_penalty=-1):
    m, n = len(left), len(right)
    dp = np.zeros((m+1, n+1), dtype=int)
    for i in range(1, m+1):
        for j in range(max(1, i - maxInsertLength), min(n, i + maxInsertLength) + 1):
            match = dp[i-1, j-1] + score(left[i-1], right[j-1])
            delete = dp[i-1, j] + gap_penalty
            insert = dp[i, j-1] + gap_penalty
            dp[i, j] = max(0, match, delete, insert)
    return dp

left = "ACGTTC"
right = "ACGGTTC"

dp_result = DP(left, right)
opt_dp_result = optimizedDP(left, right)

fig, axs = plt.subplots(1, 2, figsize=(12, 6))

# Custom colormap
cmap = mcolors.LinearSegmentedColormap.from_list("my_colormap", ['white', 'red'])

cax1 = axs[0].matshow(dp_result, cmap=cmap)
fig.colorbar(cax1, ax=axs[0])
axs[0].set_title('DP')
axs[0].set_xticks(np.arange(len(right)+1)-.5, minor=True)
axs[0].set_yticks(np.arange(len(left)+1)-.5, minor=True)
axs[0].grid(which="minor", color="w", linestyle='-', linewidth=3)
axs[0].tick_params(which="minor", size=0)
axs[0].set_xticklabels(['']+[''] + list(right), fontsize=12)
axs[0].set_yticklabels(['']+[''] + list(left), fontsize=12)

cax2 = axs[1].matshow(opt_dp_result, cmap=cmap)
fig.colorbar(cax2, ax=axs[1])
axs[1].set_title('Optimized DP')
axs[1].set_xticks(np.arange(len(right)+1)-.5, minor=True)
axs[1].set_yticks(np.arange(len(left)+1)-.5, minor=True)
axs[1].grid(which="minor", color="w", linestyle='-', linewidth=3)
axs[1].tick_params(which="minor", size=0)
axs[1].set_xticklabels(['']+[''] + list(right), fontsize=12)
axs[1].set_yticklabels(['']+[''] + list(left), fontsize=12)

plt.savefig('comparison.plot.pdf')

