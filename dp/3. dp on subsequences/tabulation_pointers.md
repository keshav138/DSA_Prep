When moving from Memoization (Recursive) to Tabulation (Iterative), the logic is the same, but the **implementation details** are where most bugs happen.

Here are the specific "Gotchas" to look out for, based on the errors we just fixed.

### 1. Initialization: The "First Row" Trap

In recursion, your base case is usually `if(index == 0)`. In tabulation, this translates to manually filling the **0-th row** of your table.

* **The Trap:** Trying to write complex logic inside the loop for `i=0`.
* **The Fix:** Handle `i=0` **before** the main loop starts.
* **The "Safe" Pattern:**
1. Initialize the whole table with your default value (0 or false).
2. Set `dp[0] = true` (or 1) because a sum of 0 is always possible.
3. Manually handle `arr[0]` logic carefully.



### 2. Default Values: -1 vs. 0 vs. False

* **Memoization:** We use `-1` to represent "Unvisited state."
* **Tabulation:** We **never** use `-1`.
* **Counting (Ways):** Initialize with `0`. (Because initially, you have found 0 ways).
* **Reachability (True/False):** Initialize with `false`.
* **Min/Max:** Initialize with `1e9` (Infinity) or `-1e9`.



### 3. The "Index Out of Bounds" Crash

This is the most common crash in Tabulation.

* **The Code:** `dp[i-1][target - arr[i]]`
* **The Danger:** If `arr[i] > target`, then `target - arr[i]` is negative. Accessing a negative index crashes C++.
* **The Fix:** You **MUST** wrap the "Take" logic in an `if` statement:
```cpp
// BAD
int pick = dp[i-1][target - arr[i]]; 

// GOOD
int pick = 0;
if (arr[i] <= target) { // ALWAYS CHECK THIS
    pick = dp[i-1][target - arr[i]];
}

```



### 4. Space Optimization: The "Backwards" Rule

If you compress your 2D array `dp[n][target]` into a 1D array `dp[target]`, the direction of your inner loop matters.

* **Infinite Items (Unbounded Knapsack):** Loop **Forwards** (`0` to `Target`).
* **Single Item Use (0/1 Knapsack):** Loop **Backwards** (`Target` down to `0`).
* *Why?* If you loop forwards, you might use the item at index `i` to create sum 5, and then immediately use that "new" sum 5 to create sum 10. You end up using the same item twice. Looping backwards prevents this "double counting."



### 5. The "Target 0" Edge Case

In "Count Subsets" problems, zeros in the input array (`arr = [0, 5]`) mess up standard logic.

* **Standard Logic:** `dp[0] = 1`.
* **The Bug:** If you have zeros, `dp[target]` might need to be updated multiple times or initialized differently (e.g., `pow(2, count_of_zeros)`).
* **The Fix:** Ensure your logic adds to the existing value (`+=`) rather than overwriting it (`=`), so that multiple paths to the same sum (via zeros) accumulate correctly.

### 6. Modulo Arithmetic

For counting problems, the numbers get huge instantly.

* **The Trap:** Applying modulo at the very end `return dp[n][k] % MOD`.
* **The Fix:** Apply modulo **at every addition**.
```cpp
dp[i][target] = (pick + notPick) % MOD;

```


* *Note:* If you ever subtract (e.g., `dp[i] - dp[j]`), you must handle negative results: `(dp[i] - dp[j] + MOD) % MOD`.



### Summary Checklist for Interview

Before submitting Tabulation code, ask yourself:

1. **Grid:** Did I alloc `target + 1` columns? (Common off-by-one error).
2. **Base:** Did I handle row 0 safely?
3. **Bounds:** strictly checking `if (arr[i] <= target)`?
4. **Types:** Am I adding `int`s that might overflow? (Use `long long` for intermediate sums if needed).