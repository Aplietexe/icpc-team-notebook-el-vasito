typedef long double td;
typedef vector<ll> vi;
typedef vector<td> vd;
const td INF = 1e100;                      // for maximum set INF to 0, and negate costs
bool zero(td x) { return fabs(x) < 1e-9; } // change to x==0, for ints/ll
struct Hungarian
{
    ll n;
    vector<vd> cs;
    vi L, R;
    Hungarian(ll N, ll M) : n(max(N, M)), cs(n, vd(n)), L(n), R(n)
    {
        fori(x, 0, N) fori(y, 0, M) cs[x][y] = INF;
    }
    void set(ll x, ll y, td c) { cs[x][y] = c; }
    td assign()
    {
        ll mat = 0;
        vd ds(n), u(n), v(n);
        vi dad(n), sn(n);
        fori(i, 0, n) u[i] = *min_element(all(cs[i]));
        fori(j, 0, n)
        {
            v[j] = cs[0][j] - u[0];
            fori(i, 1, n) v[j] = min(v[j], cs[i][j] - u[i]);
        }
        L = R = vi(n, -1);
        fori(i, 0, n) fori(j, 0, n) if (R[j] == -1 && zero(cs[i][j] - u[i] - v[j]))
        {
            L[i] = j;
            R[j] = i;
            mat++;
            break;
        }
        for (; mat < n; mat++)
        {
            ll s = 0, j = 0, i;
            while (L[s] != -1)
                s++;
            fill(all(dad), -1);
            fill(all(sn), 0);
            fori(k, 0, n) ds[k] = cs[s][k] - u[s] - v[k];
            for (;;)
            {
                j = -1;
                fori(k, 0, n) if (!sn[k] && (j == -1 || ds[k] < ds[j])) j = k;
                sn[j] = 1;
                i = R[j];
                if (i == -1)
                    break;
                fori(k, 0, n) if (!sn[k])
                {
                    auto new_ds = ds[j] + cs[i][k] - u[i] - v[k];
                    if (ds[k] > new_ds)
                    {
                        ds[k] = new_ds;
                        dad[k] = j;
                    }
                }
            }
            fori(k, 0, n) if (k != j && sn[k])
            {
                auto w = ds[k] - ds[j];
                v[k] += w, u[R[k]] -= w;
            }
            u[s] += ds[j];
            while (dad[j] >= 0)
            {
                ll d = dad[j];
                R[j] = R[d];
                L[R[j]] = j;
                j = d;
            }
            R[j] = s;
            L[s] = j;
        }
        td value = 0;
        fori(i, 0, n) value += cs[i][L[i]];
        return value;
    }
};
