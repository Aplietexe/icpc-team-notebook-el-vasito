vi computeLCP(string &s, vi &sa) // lcp[i]=LCP(sa[i-1],sa[i])
{
    ll n = SZ(s), L = 0;
    vi lcp(n), plcp(n), phi(n);
    phi[sa[0]] = -1;
    fori(i, 1, n) phi[sa[i]] = sa[i - 1];
    fori(i, 0, n)
    {
        if (phi[i] < 0)
        {
            plcp[i] = 0;
            continue;
        }
        while (s[i + L] == s[phi[i] + L])
            L++;
        plcp[i] = L;
        L = max(L - 1, 0ll);
    }
    fori(i, 0, n) lcp[i] = plcp[sa[i]];
    return lcp;
}
