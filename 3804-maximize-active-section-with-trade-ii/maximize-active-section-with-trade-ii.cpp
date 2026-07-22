class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string str, vector<vector<int>>& queries) {     int n = str.size();
        // Prework1：    Prefix sum
        int a[n+10];    memset(a, 0, sizeof(a));
        int s[n+10];    memset(s, 0, sizeof(s));
        for (int i = 1; i <= n; i++) a[i] = (str[i-1]-'0'), s[i] = s[i-1] + a[i];

        // Prework2：    Retrieve all segments (with their 0/1 values and sizes)
        int K = 0, m = 0;
        int idx[n+10], pos[n+10];  
        int buf[n+10], siz[n+10];   memset(buf, 0, sizeof(buf)); memset(siz, 0xcf, sizeof(siz));
        int kth[n+10], rnk[n+10];   memset(kth, 0, sizeof(kth)); memset(rnk, 0x3f, sizeof(rnk));
        for (int l = 1, r = 1; l <= n; l = r) {    ++K, buf[K] = a[l], siz[K] = 0;
            for (r = l; r <= n && a[r]==a[l]; r++) idx[r] = K, pos[r] = ++siz[K];
            if (buf[K] == 1) ++m, kth[m] = K, rnk[K] = m;
        }

        // Prework3:     Sparse Table for Range Maximum Query (increment)
        int T = m ? log2(m) : 0;
        int f[m+10][T+10];  
        memset(f, 0, sizeof(f));

        for (int i = 1; i <= m; i++) f[i][0] = siz[kth[i]-1] + siz[kth[i]+1];
        for (int t = 1; t <= T; t++) {
            for (int i = 1; i+(1<<t)-1 <= m; i++) f[i][t] = max(f[i][t-1], f[i+(1<<t-1)][t-1]);
        }        

        auto ask = [&](int l, int r) -> int { int k = log2(r-l+1); return max(f[l][k], f[r-(1<<k)+1][k]); };


        vector<int> ans;
        for (auto& e : queries) {                   int l = e[0]+1, r = e[1]+1;
            int i = rnk[idx[l] + (a[l]^1)];         // Position of the first '1' 
            int j = rnk[idx[r] - (a[r]^1)];         // Position of the last '1' 
            if (j > m) j = 0;                       // Boundary adjustment 

            // Case Analysis
            int val = s[n];
            if (i+1 < j)                            val = max(val, s[n] + ask(i+1, j-1));
            if (a[l] == 0 && i < j)                 val = max(val, s[n] + (siz[kth[i]-1]-pos[l]+1) + siz[kth[i]+1]);
            if (a[r] == 0 && i < j)                 val = max(val, s[n] + siz[kth[j]-1] + pos[r]);
            if (a[l] == 0 && a[r] == 0 && i == j)   val = max(val, (r-l+1) + (s[l-1] + s[n]-s[r])); 
            ans.push_back(val);
        }
        return ans;
    }
};

