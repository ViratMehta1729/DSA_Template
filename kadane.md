# Kadane's Algorithm 

> Use when the task is: best contiguous segment (subarray/range) by some score.

Kadane reduces brute-force O(n^2) subarray checks to O(n) by asking at each index:

1. Extend previous best ending here
2. Restart from current element

---

## 1) Core DP State

```text
dp[i] = best subarray sum ending at i
dp[i] = max(a[i], dp[i-1] + a[i])
ans   = max(ans, dp[i])
```

Space-optimized form:

```text
curr = max(a[i], curr + a[i])
ans  = max(ans, curr)
```

---

## 2) Master C++ Template (Max Subarray Sum)

```cpp
long long kadane_max(const vector<long long>& a) {
	long long curr = a[0];
	long long best = a[0];

	for (int i = 1; i < (int)a.size(); i++) {
		curr = max(a[i], curr + a[i]);
		best = max(best, curr);
	}
	return best;
}
```

Note: Initializing with a[0] handles all-negative arrays correctly.

---

## 3) Generic Extend-vs-Restart Template

```text
curr = best ending here
curr = combine(previous, a[i]) OR start_new(a[i])
ans  = best_overall(ans, curr)
```

Common mapping:

| Problem Type | Combine | Global Best |
|---|---|---|
| Max sum | + | max |
| Min sum | + | min |
| Max product | * | max |
| XOR objective | ^ | depends on problem |

---

## 4) High-Value Variants

### 4.1 Print max-subarray indices

Keep `tempStart` when restart happens; update `[L, R]` when `best` improves.

```cpp
long long cur = a[0], best = a[0];
int tempStart = 0, L = 0, R = 0;

for (int i = 1; i < n; i++) {
	if (a[i] > cur + a[i]) {
		cur = a[i];
		tempStart = i;
	} else {
		cur += a[i];
	}

	if (cur > best) {
		best = cur;
		L = tempStart;
		R = i;
	}
}
```

### 4.2 Minimum subarray sum

```text
curr = min(a[i], curr + a[i])
ans  = min(ans, curr)
```

### 4.3 Circular max subarray (LC 918)

```text
maxSum = kadane_max(a)
minSum = kadane_min(a)
total  = sum(a)

if (maxSum < 0) return maxSum
return max(maxSum, total - minSum)
```

### 4.4 Maximum product subarray (LC 152)

Track both max and min ending at each index (sign flip case).

```cpp
int mx = a[0], mn = a[0], ans = a[0];
for (int i = 1; i < n; i++) {
	if (a[i] < 0) swap(mx, mn);
	mx = max(a[i], mx * a[i]);
	mn = min(a[i], mn * a[i]);
	ans = max(ans, mx);
}
```

### 4.5 Max sum with one deletion (LC 1186)

```text
dp0[i] = max sum ending at i, no deletion
dp1[i] = max sum ending at i, one deletion

dp0[i] = max(a[i], dp0[i-1] + a[i])
dp1[i] = max(dp0[i-1], dp1[i-1] + a[i])
```

### 4.6 2D Kadane (max-sum rectangle)

Fix `left`, expand `right`, compress rows to 1D, run Kadane.

Complexity: O(cols^2 * rows)

### 4.7 Two non-overlapping max subarrays

Build:

- `leftBest[i]` = best in prefix `[0..i]`
- `rightBest[i]` = best in suffix `[i..n-1]`

Combine split points.

---

## 5) Kadane vs Sliding Window

| Kadane | Sliding Window |
|---|---|
| Works well with negatives | Often needs monotonic or fixed-size constraints |
| Variable segment length | Usually fixed/controlled length |
| Restart when harmful | Shrink/expand window |

---

## 6) Recognition Checklist

Think Kadane if you see:

- contiguous segment/subarray/range
- maximize or minimize score
- local choice: extend vs restart
- linear-time target

---

## 7) Interview Edge Cases

1. All negatives
2. Single element
3. Zeros mixed with negatives
4. Circular array
5. Product with sign flips / zeros
6. One deletion allowed
7. At least K length constraint

---

## 8) Prefix-Sum Interpretation

Equivalent view:

```text
maxSubarray = max(prefix[j] - minPrefixBeforeJ)
```

Useful for advanced constraints (modulo, ordered structures, transformed scoring).

---

## 9) Practice Ladder

### Easy

1. LC 53 - Maximum Subarray
2. Print subarray indices
3. Minimum subarray sum

### Medium

1. LC 918 - Circular Sum
2. LC 152 - Maximum Product Subarray
3. Maximum Sum Increasing Subarray

### Hard

1. LC 1186 - Maximum Sum After One Deletion
2. 2D Kadane (LC 363 style)
3. Max sum of two non-overlapping subarrays

---

## 10) One-Line Mental Model

If previous contribution hurts future answer, discard it.
