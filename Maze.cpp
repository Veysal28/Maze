#include <iostream>
#include <fstream>

using namespace std;

class Maze
{
    char maze[100][100];
    int rows, cols;
    int x, y; // x - column, y - row

public:
    void load();
    void print();
    bool find_path(int x, int y);
    bool solve();
};

// load maze from file
void Maze::load()
{
    ifstream fin("maze1.txt"); 
    string line;
    int i = 0;
    while(getline(fin, line))
    {
        for(int j = 0; j<line.size(); j++)
        {
            maze[i][j] = line[j];

            // determine current robot's position 
            if(maze[i][j] == 'S')
            {
                x = j;
                y = i;
            }
        }
        i++;
        cols = line.size();
    }
    rows = i;
}

// print maze to screen
void Maze::print()
{
    cout << rows << " " << cols << endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Robot at pos " << x << ", " << y << endl;
}

// find path from position 'S' to position 'G'
bool Maze::find_path(int x, int y)
{
    // base cases
    if(maze[y][x]=='G')
    {
        return true; 
    }

    // out of maze
    if(x<0 || x>cols-1 || y<0 || y>rows-1)
    {
        return false;
    }

    // if wall or position is already marked
    if(maze[y][x]=='#' or maze[y][x]=='+')
    {
        return false;
    }

    // mark current position
    maze[y][x] = '+';

    // recursion
    bool north = find_path(x, y-1);
    bool east = find_path(x+1, y);
    bool south = find_path(x, y+1);
    bool west = find_path(x-1, y);
    
    if( north || east || south || west ) return true;

    maze[y][x] = '.';
    return false;
}

bool Maze::solve()
{
    return find_path(x,y);
}

int main()
{
    Maze maze; // create labirint object

    maze.load();
    maze.print();

    bool res = maze.solve();
    if(res == true)
    {
        cout << "Maze solved!" << endl;
        maze.print();
    }
    else
    {
        cout << "Can't solve maze... " << endl;
    }

    return 0;
}
