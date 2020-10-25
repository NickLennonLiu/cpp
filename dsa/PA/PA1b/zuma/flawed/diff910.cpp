89d88
<     Rank lbound, rbound;
91d89
<     int decrease = 0;
111,113c109,129
<             decrease += dis - 1;
<             lbound = l;
<             rbound = r;
---
>             realn -= (dis - 1);
>             if (l.first == r.first) {
>                 int len = plen[r.first] - r.second;
>                 if (len > 0) {
>                     memmove(&p[l.first][l.second + 1], &p[r.first][r.second], len);
>                 }
>                 plen[l.first] -= (dis - 1);
>             } else {
>                 if (l.first >= 0) {
>                     plen[l.first] = l.second + 1;
>                 }
>                 if (r.first < pn) {
>                     int len = plen[r.first] - r.second;
>                     if (len > 0) {
>                         memmove(&p[r.first][0], &p[r.first][r.second], len);
>                     }
>                     plen[r.first] = len;
>                 }
>                 for (int i = l.first + 1; i < r.first; i++)
>                     plen[i] = 0;
>             }
114a131,132
>             r = l;
>             r.second += 1;
120,138d137
<     }
< 
<     if (decrease > 0) {
<         realn -= decrease;
<         l = lbound;
<         r = rbound;
< 
<         if (l.first >= 0) {
<             plen[l.first] = l.second + 1;
<         }
<         if (r.first < pn) {
<             int len = plen[r.first] - r.second;
<             if (len > 0) {
<                 memmove(&p[r.first][0], &p[r.first][r.second], len);
<             }
<             plen[r.first] = len;
<         }
<         for (int i = l.first + 1; i < r.first; i++)
<             plen[i] = 0;
