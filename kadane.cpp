#include <bits/stdc++.h>

using namespace std;
int kadane(vector<int> &arr, int n)
{
    int best = INT_MIN;;
    int curr = 0;
    for(auto ele : arr)
    {
        curr+=ele;
        best = max(best, curr);
        if(curr < 0) curr = 0;
    }
    return best;

    // dp[i] = dp[i-1] , dp[i-1]+arr[i];
}

int main()
{
    vector<int> arr  = {-2, -1, -3, -4, -5, -6, -1, -10, -3, -4};
    cout<< kadane(arr, arr.size());
    return 0;
}