#ifndef FIND_PATH
#define FIND_PATH



#ifndef TEST
#define TEST
#define FIND_PATH_TEST
#endif



#include "stack.cpp"
#include "queue.cpp"
#include <stdlib.h>
#include <stdio.h>




/************************************************search path*******************************************************/

/**************************************** find one path version*******************************/

#define LABY_MAX 50


typedef enum { AVAILABLE, ROUTE, BACKTRACKED, WALL } Status;

typedef enum { UNKNOWN, EAST, SOUTH, WEST, NORTH, NO_WAY } ORIENT;

struct Cell
{
    size_t x, y;
    ORIENT incoming, outgoing;
    Status status;
};

Cell laby[LABY_MAX][LABY_MAX];
int labysize;
Cell * startcell;
Cell * goalcell;

inline Cell * neighbor(Cell * cell)
{
    switch (cell->outgoing)
    {
        case EAST  : return cell + 1;
        case SOUTH : return cell - LABY_MAX;
        case WEST  : return cell - 1;
        case NORTH : return cell + LABY_MAX;
        default : exit(EXIT_FAILURE);
    }
}

inline Cell * advance(Cell * cell)
{
    Cell * next;
    switch (cell->outgoing)
    {
        case EAST:
            next = cell + 1;
            next->incoming = WEST;
            break;
        case SOUTH:
            next = cell - LABY_MAX;
            next->incoming = NORTH;
            break;
        case WEST:
            next = cell - 1;
            next->incoming = EAST;
            break;
        case NORTH:
            next = cell + LABY_MAX;
            next->incoming = SOUTH;
            break;
        default:
            exit(EXIT_FAILURE);
    }
    return next;
}

inline ORIENT nextORIENT(ORIENT orient)
{
    return ORIENT (orient + 1);
}

void read_laby()
{
    labysize = LABY_MAX / 2 + rand() % (LABY_MAX / 2);
    for (size_t i = 0; i < labysize; ++i)
    {
        for (size_t j = 0; j < labysize; ++j)
        {
            laby[i][j].x = i;
            laby[i][j].y = j;
            laby[i][j].incoming = laby[i][j].outgoing = UNKNOWN;
            laby[i][j].status = WALL;
        }
    }
    for (size_t i = 1; i < labysize - 1; ++i)
    {
        for (size_t j = 1; j < labysize - 1; ++j)
            if (rand() % 3)
                laby[i][j].status = AVAILABLE;
    }
    startcell = &laby[rand() % (labysize - 2) + 1][rand() % (labysize - 2) + 1];
    goalcell = &laby[rand() % (labysize - 2) + 1][rand() % (labysize - 2) + 1];
    startcell->status = goalcell->status = AVAILABLE;
}

void read_laby(char * labyfile)
{
    FILE * fp;
    if ( !(fp = fopen(labyfile, "r") ))
    {
        cout << "can't open laby file: " << labyfile << endl;
        exit(EXIT_FAILURE);
    }
    labysize = LABY_MAX;

    int startX, startY;
    fscanf(fp, "Start = (%d, %d)\n", &startX, &startY);
    startcell = &laby[startX][startY];
    int goalX, goalY;
    fscanf(fp, "Goal = (%d, %d)\n", &goalX, &startY);
    goalcell = &laby[goalX][goalY];
    for (size_t i = 0; i < labysize; ++i)
    {
        for (size_t j = 0; j < labysize; ++j)
        {
            laby[i][j].x = i;
            laby[i][j].y = j;
            int type;
            fscanf(fp, "%d\n", &type);
            switch (type)
            {
                case 1 : laby[i][j].status = WALL; break;
                case 0 : laby[i][j].status = AVAILABLE; break;
                default : exit(EXIT_FAILURE);
            }
            laby[i][j].incoming = laby[i][j].outgoing = UNKNOWN;
        }
    }
    fclose(fp);
}

/**********************************************find path DFS************************************************/
//             depth first searching
bool search_path_dfs(Cell * start, Cell * goal)
{//       return to the early point which  still has at least one AVAILABLE neighbor.
 //       notice that a Route neighbor is not AVALIBALE.
 //       this means th whole process pass through each point at most one time.
    if ( (start->status != AVAILABLE) || (goal->status != AVAILABLE) )
        return false;
    Stack<Cell *> path;
    start->incoming = UNKNOWN; start->status = ROUTE; path.push(start);
    while (!path.empty())
    {
        Cell * c = path.top();
        if (c == goal) return true;
        while (NO_WAY > (c->outgoing = nextORIENT(c->outgoing)))
            if ( neighbor(c)->status == AVAILABLE )
                break;
        if (NO_WAY == c->outgoing)
        {
            c->status = BACKTRACKED;// this mark is not indispensible. only used fot drawing path graph.
            path.pop();// skip this point . back track last point in the next while loop.
        }
        else
        {
            path.push(c = advance(c));
            c->outgoing = UNKNOWN;
            c->status = ROUTE;
        }
    }
    return false;
}
/**********************************************find path BFS************************************************/
//    breath first searching
bool search_path_bfs(Cell * start, Cell * goal)
{
    if ( (start->status != AVAILABLE) || (goal->status != AVAILABLE) )
        return false;
    Queue<Cell *, Vector<Cell *>> q;
    Cell * cur;
    start->incoming = UNKNOWN; start->status = ROUTE; q.enqueue(start);
    while (!q.empty())
    {
        start = q.dequeue();
        if (start == goal)
            return true;
        while ( NO_WAY > (start->outgoing = nextORIENT(start->outgoing)) )
            if (neighbor(start)->status == AVAILABLE)
            {
                start->status = BACKTRACKED;
                cur = advance(start);
                cur->status = BACKTRACKED;
                q.enqueue(cur);
            }
    }
    return false;
}


void mark_route(Cell * start, Cell * goal)
{
    while (goal != start)
    {
        switch (goal->incoming)
        {
            case EAST :
                goal = goal + 1; goal->outgoing = WEST;
                break;
            case SOUTH :
                goal = goal - LABY_MAX; goal->outgoing = NORTH;
                break;
            case WEST :
                goal = goal - 1; goal->outgoing = EAST;
                break;
            case NORTH :
                goal = goal + LABY_MAX; goal->outgoing = SOUTH;
                break;
            default : break;
        }
        goal->status = ROUTE;
    }
}


void display(Cell laby[LABY_MAX][LABY_MAX], Cell * startcell, Cell * goalcell)
{
    static char const * pattern[5][5] = 
    {
        "┼─", "┼─", "┼─", "┼─", "┼─",
        "┼─", "  ", "┌─", "──", "└─",
        "┼─", "┌─", "  ", "┐ ", "│ ",
        "┼─", "──", "┐ ", "  ", "┘ ",
        "┼─", "└─", "│ ", "┘ ", "  "   
    };
    printf("\n");
    for (int i = labysize - 1 ; i >= 0; --i)
    {
        ( i < 10 ) ? printf ( "%2X", i ) : printf ( " %c", 'A' - 10 + i );
        for (int j = 0; j < labysize; ++j)
        {
            if (goalcell == &laby[i][j])
                printf("$$");
            else if (startcell == &laby[i][j])
                printf("oo");
            else
            {
                switch (laby[i][j].status)
                {
                    case WALL :
                        printf("█▌"); break;
                    case BACKTRACKED :
                        printf("x "); break;
                    case AVAILABLE :
                        printf("  "); break;
                    default :
                        printf("%s", pattern[laby[i][j].outgoing][laby[i][j].incoming]);
                        break;
                }
            }
        }
        cout << endl;
    }
    cout << " ";
    for (int i = 0; i < labysize; ++i)
        ( i < 10 ) ? printf ( "%2X", i ) : printf ( " %c", 'A' - 10 + i );
    cout << endl << endl;
}

#ifdef FIND_PATH_TEST
int main(int argc, char ** argv)
{
    // test search path
    srand((unsigned int)time(NULL));
    ( 1 < argc ) ? read_laby(argv[1]) : read_laby();


    Cell laby1[LABY_MAX][LABY_MAX];
    memcpy(laby1, laby, sizeof(laby));
    Cell * start1;
    Cell * end1;
    for (size_t i = 0; i < LABY_MAX; ++i)
    {
        for (size_t j = 0; j < LABY_MAX; ++j)
        {
            if (&laby[i][j] == startcell)
                start1 = &laby1[i][j];
            if (&laby[i][j] == goalcell)
                end1 = &laby1[i][j];
        }
    }
    
    // depth first searching 
    search_path_dfs(startcell, goalcell) ?
        printf("\nRoute found\a\n") : printf("\n No route found\a\n");
    display(laby, startcell, goalcell);
    // breadth first searching
    if (search_path_bfs(start1, end1))
        mark_route(start1, end1);
    display(laby1, start1, end1);
    
   // for (Cell (&row)[LABY_MAX] : laby)
   // {
   //     for (Cell & elem : row)
   //         cout << elem.status << " ";
   //     cout << endl;
   // }
   // cout << endl;
}
#endif




#endif
