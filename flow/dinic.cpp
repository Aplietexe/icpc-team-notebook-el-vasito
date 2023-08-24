// Min cut: nodes with dist>=0 vs nodes with dist<0
// Matching MVC: left nodes with dist<0 + right nodes with dist>0
struct Dinic
{
    ll nodes, src, dst;
    struct edge
    {
        ll to, rev;
        ll f, cap;
    };
    vector<vector<edge>> g;
    vector<ll> dist, q, work;
    Dinic(ll x) : nodes(x), g(x), dist(x), q(x), work(x) {}
    void add_edge(ll s, ll t, ll cap)
    {
        g[s].pb((edge){t, SZ(g[t]), 0, cap});
        g[t].pb((edge){s, SZ(g[s]) - 1, 0, 0});
    }
    bool dinic_bfs()
    {
        fill(all(dist), -1);
        dist[src] = 0;
        ll qt = 0;
        q[qt++] = src;
        for (ll qh = 0; qh < qt; qh++)
        {
            ll u = q[qh];
            fori(i, 0, SZ(g[u]))
            {
                edge &e = g[u][i];
                ll v = g[u][i].to;
                if (dist[v] < 0 && e.f < e.cap)
                    dist[v] = dist[u] + 1, q[qt++] = v;
            }
        }
        return dist[dst] >= 0;
    }
    ll dinic_dfs(ll u, ll f)
    {
        if (u == dst)
            return f;
        for (ll &i = work[u]; i < SZ(g[u]); i++)
        {
            edge &e = g[u][i];
            ll v = e.to;
            if (e.cap <= e.f)
                continue;
            if (dist[v] == dist[u] + 1)
            {
                ll df = dinic_dfs(v, min(f, e.cap - e.f));
                if (df > 0)
                {
                    e.f += df;
                    g[v][e.rev].f -= df;
                    return df;
                }
            }
        }
        return 0;
    }
    ll max_flow(ll _src, ll _dst)
    {
        src = _src;
        dst = _dst;
        ll result = 0;
        while (dinic_bfs())
        {
            fill(all(work), 0);
            while (ll delta = dinic_dfs(src, INF))
                result += delta;
        }
        return result;
    }
};
