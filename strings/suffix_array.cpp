#define RB(x) (x < n ? r[x] : 0)
void csort(vi &sa, vi &r, ll k)
{
    ll n = sa.size();
    vi f(max(255ll, n), 0), t(n);
    fori(i, 0, n) f[RB(i + k)]++;
    ll sum = 0;
    fori(i, 0, max(255ll, n)) f[i] = (sum += f[i]) - f[i];
    fori(i, 0, n) t[f[RB(sa[i] + k)]++] = sa[i];
    sa = t;
}
vi constructSA(string &s)
{ // O(n logn)
    ll n = s.size(), rank;
    vi sa(n), r(n), t(n);
    fori(i, 0, n) sa[i] = i, r[i] = s[i];
    for (ll k = 1; k < n; k *= 2)
    {
        csort(sa, r, k);
        csort(sa, r, 0);
        t[sa[0]] = rank = 0;
        fori(i, 1, n)
        {
            if (r[sa[i]] != r[sa[i - 1]] || RB(sa[i] + k) != RB(sa[i - 1] + k))
                rank++;
            t[sa[i]] = rank;
        }
        r = t;
        if (r[sa[n - 1]] == n - 1)
            break;
    }
    return sa;
}
