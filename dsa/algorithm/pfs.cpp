template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater)
{
    priority(s) = 0;
    status(s) = VISITED; 
    parent(s) = -1;
    while(1)
    {
        for(int w = firstNbr(s); -1 < w; w = nextNbr(s, w))
            prioUpdater(this, s, w);
        for(int shortest = INT_MAX, w = 0; w < n; w++)
        {
            if( UNDISCOVERED == status(w))
                if( shortest > priority(w))
                {
                    shortest = priority(w);
                    s = w;
                }
        }
        if (VISITED == status(s)) break;
        status(s) = VISITED; type(parent(s), s) = TREE;
    }
}