#ifndef COORD_H
#define COORD_H

struct coord
{
    int x;
    int y;
    coord operator+(coord const dir)
    {
        coord a;
        a.x = x + dir.x;
        a.y = y + dir.y;
        return a;
    }
};

coord const direct[4] = {{1,0},{-1,0},{0,1},{0,-1}};

#endif  //COORD_H