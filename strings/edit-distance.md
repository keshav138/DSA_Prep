So the edit distance prob, we can do three operations, delete, replace or insert to get from one word to another.
We do this using 2d dp.

We create the 2d matrix of the two words, word1 and word2, with one additional column and row(for our base cases).
Cell at dp[i][j], represents the min steps to get from first i characters of word1 to first j characters of word2.

At each step we have two possibilities, the character matches, hurray, no operation, just carry forward the last best case.
The characters didnt match, we have to do one operation, so that 1 + min_last_step_taking_char_right_before_this, that is our direct diagonal, my top and my left.

The first column and row are base cases. They represent transforming a word into a empty list, which is by removeign all letters, therefore, that many number of operations, or building a string from a empty string, which is inserting that many number of characters.

[!edit-distance.png]

-----CODE-----PYTHON

class Solution(object):
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """

        m, n = len(word1), len(word2)

        dp = [[0] * (n+1) for _ in range(m+1)]

        for i in range(n+1):
            dp[0][i] = i

        for i in range(m+1):
            dp[i][0] = i

        for i in range(1, m+1):
            for j in range(1, n+1):

                if word1[i-1] == word2[j-1]:
                    dp[i][j] = dp[i-1][j-1]

                else:
                    dp[i][j] = 1 + min(
                        dp[i-1][j],
                        dp[i][j-1],
                        dp[i-1][j-1]
                    )

        return dp[m][n]    