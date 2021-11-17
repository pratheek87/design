// samples.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<vector>
#include <string>
using namespace std;

vector<vector<int>> d = { {-1, 0}, {0, -1} , {1, 0} , {0, 1} };
bool solveRec(vector<vector<int>>& maze, int px, int py, vector<vector<string>>&soln, vector<vector<int>>& visited)
{

    if (maze[px][py] == 3)
    {
        soln[px][py] = "3";
        return true;
    }
    else if (maze[px][py] == 0)
    {
        soln[px][py] = "S";
    }
    else if (maze[px][py] == 1)
    {
        return false;
    }

    visited[px][py] = 1;
    for (auto i = 0; i < d.size() ; ++i)
    {
        int row = px + d[i][0];
        int col = py + d[i][1];

        if ((row >= 0 && row < maze.size()) && (col >= 0 && col < maze[0].size()) && (visited[row][col] == 0))
        {

            if (solveRec(maze, row, col, soln, visited))
            {
                return true;
            }

        }
    }
    visited[px][py] == 0;

    return false;    
}

void solveMze(vector<vector<int>>& maze, int sx, int sy)
{
    //initialize direction vevtors.
    
    vector<vector<string>> soln(maze.size(), vector<string>(maze[0].size(), "-"));
    vector<vector<int>> visited(maze.size(), vector<int>(maze.size(), 0));

    soln[sx][sy] = "2";

    if (solveRec(maze, sx, sy, soln, visited))
    {
        cout << "solution found" << endl;

        for (auto i = 0; i < soln.size(); ++i)
        {
            for (auto j = 0; j < soln[i].size(); ++j)
            {
                cout << soln[i][j] << "\t";
            }
            cout << endl;
        }

    }
    else
        cout << "no" << endl;



}

int main()
{

    //integer 1 represents walls
    //integer 2 is the starting point
    //integer 3 is the destination (so this is what we are looking for)
    vector<vector<int>> maze = {
                                {1, 1, 1, 1, 1},
                                {0, 2, 0, 1, 1},
                                {0, 1, 1, 0, 1},
                                {0, 1, 0, 3, 0},
                                {0, 0, 0, 1, 1}
                                };

    solveMze(maze, 1, 1);
    return 1;
}