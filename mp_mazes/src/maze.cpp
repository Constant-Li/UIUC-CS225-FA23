/* Your code here! */
#include "maze.h" 
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <queue>
#include <algorithm>
using namespace cs225;

SquareMaze::SquareMaze(){
    width = 0;
    height = 0;
}



void SquareMaze::makeMaze(int w, int h){
    width = w;
    height = h;
    maze.addelements(w * h);
    downwall.assign(h, std::vector<bool>(w, true));
    rightwall.assign(h, std::vector<bool>(w, true));

    while(maze.size(0) != (w * h)){

        int x = rand() % width;
        int y = rand() % height;
        int dir = rand() % 2;

        // if randomly remove right wall
        if(dir == 0){
            // x within bound and right wall has not been removed
            if(x < (width - 1) && rightwall[y][x] == true){
                if(maze.find(x + y * width) != maze.find((x + 1) + y * width)){
                    setWall(x, y, 0, false);
                    maze.setunion(x + y * width, (x + 1) + y * width);
                }
            }
        // if down wall
        }else if(dir == 1){
            // y within bound and down wall has not been removed
            if(y < (height - 1) && downwall[y][x] == true){
                if(maze.find(x + y * width) != maze.find(x + (y + 1) * width)){
                    setWall(x, y, 1, false);
                    maze.setunion(x + y * width, x + (y + 1) * width);
                }
            }
        }
    }
}



bool SquareMaze::canTravel(int x, int y, int dir) const{

    // right
    if(dir == 0){
        // if no wall and within bound
        if((x < (width - 1)) && (rightwall[y][x] == false)){
            return true;
        }
        return false;
    }
    // down
    if(dir == 1){
        // if no wall and within bound
        if((y < (height - 1)) && (downwall[y][x] == false) ){
            return true;
        }
        return false;
    }
    // left
    if(dir == 2){
        // if no wall and within bound
        if((x >= 1) && (rightwall[y][x - 1] == false)){
            return true;
        }
        return false;
    }
    // up
    if(dir == 3){
        // if no wall and within bound
        if((y >= 1) && (downwall[y - 1][x] == false)){
            return true;
        }
        return false;
    }

    return false;
}



void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(x >= width || y >= height){
        return;
    }
    // setright
    if(dir == 0){
        if(x < (width - 1)){
            rightwall[y][x] = exists;
        }
    }
    // setdown
    if(dir == 1){
        if(y < (height - 1)){
            downwall[y][x] = exists;
        }
    }
}



std::vector<int> SquareMaze::solveMaze(){

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<int>> path(height, std::vector<int>(width, 0));
    std::vector<std::vector<int>> length(height, std::vector<int>(width, 0));
    std::queue<int> bfs;

    // set the topleft to be visited
    visited[0][0] = true;
    bfs.push(0);
    while(!bfs.empty()){
        int v = bfs.front();
        bfs.pop();

        // x and y coordinate for curent element
        int x = v % width;
        int y = (v - x) / width;

        // if can travel to right
        if(canTravel(x, y, 0)){
            if(visited[y][x + 1] == false){
                visited[y][x + 1] = true;
                bfs.push(v + 1);
                path[y][x + 1] = v;
                length[y][x + 1] = length[y][x] + 1;
            }
        }
        // if can travel to down
        if(canTravel(x, y, 1)){
            if(visited[y + 1][x] == false){
                visited[y + 1][x] = true;
                bfs.push(v + width);
                path[y + 1][x] = v;
                length[y + 1][x] = length[y][x] + 1;
            }
        }
        // if can travel to left
        if(canTravel(x, y, 2)){
            if(visited[y][x - 1] == false){
                visited[y][x - 1] = true;
                bfs.push(v - 1);
                path[y][x - 1] = v;
                length[y][x - 1] = length[y][x] + 1;
            }
        }
        // if can travel to up
        if(canTravel(x, y, 3)){
            if(visited[y - 1][x] == false){
                visited[y - 1][x] = true;
                bfs.push(v - width);
                path[y - 1][x] = v;
                length[y - 1][x] = length[y][x] + 1;
            }
        }
    }

    // find longest path
    int longest = 0;
    int largestX = 0;
    for(int i = 0; i < width; i++){
        if(length[height - 1][i] > longest){
            longest = length[height - 1][i];
            largestX = i;
        }
    }

    std::vector<int> out;
    int step = largestX + (height - 1) * width;
    int xcord = largestX;
    int ycord = height - 1;
    // convert path into moves
    while(step != 0){

        if(path[ycord][xcord] == (ycord * width) + xcord - 1){
            out.push_back(0);
            xcord = xcord - 1;
        }
        else if(path[ycord][xcord] == ((ycord - 1) * width) + xcord){
            out.push_back(1);
            ycord = ycord - 1;
        }
        else if(path[ycord][xcord] == (ycord * width) + xcord + 1){
            out.push_back(2);
            xcord = xcord + 1;
        }
        else if(path[ycord][xcord] == ((ycord + 1) * width) + xcord){
            out.push_back(3);
            ycord = ycord + 1;
        }
        step = xcord + ycord * width;
    }

    std::reverse(out.begin(), out.end());
    return out;
}



cs225::PNG* SquareMaze::drawMaze() const{
    PNG* out = new PNG(width * 10 + 1, height * 10 + 1);   

    // Blacken the entire topmost row except 1-9
    out->getPixel(0, 0).l = 0;
    for(int i = 10; i < width * 10 + 1; i++){
        out->getPixel(i, 0).l = 0;
    }
    // blacken the leftmost coloumn 

    for(int j = 0; j < height * 10 + 1; j++){
        out->getPixel(0, j).l = 0;
    }
    for(int a = 0; a < width; a++){
        for(int b = 0; b < height; b++){
            // if rightwall exist
            if(rightwall[b][a] == true){
                // blacken ((x+1)*10,y*10+k) for k from 0 to 10
                for (int x = 0; x <= 10; x++){
                    out->getPixel((a + 1) * 10, b * 10 + x).l = 0;
                }
            }
            // if downwall exist
            if(downwall[b][a] == true){
                //blacken (x*10+k, (y+1)*10) for k from 0 to 10.
                for (int y = 0; y <= 10; y++){
                    out->getPixel(a * 10 + y, (b + 1) * 10).l = 0;
                }
            }
        }
    }
    return out;
}



cs225::PNG* SquareMaze::drawMazeWithSolution(){
    PNG* out = drawMaze();
    std::vector<int> path = solveMaze();
    // start point
    int x = 5;
    int y = 5;
    
    for(int i = 0; i < (int)path.size(); i++){
        // right
        if(path[i] == 0){
            for(int j = 0; j <= 10; j++){
                out->getPixel(x + j, y).h = 0;
                out->getPixel(x + j, y).s = 1;
                out->getPixel(x + j, y).l = 0.5;
                out->getPixel(x + j, y).a = 1;
            }
            x = x + 10;
        }
        // down
        else if(path[i] == 1){
            for(int j = 0; j <= 10; j++){
                out->getPixel(x, y + j).h = 0;
                out->getPixel(x, y + j).s = 1;
                out->getPixel(x, y + j).l = 0.5;
                out->getPixel(x, y + j).a = 1;
            }
            y = y + 10;
        }
        // left
        else if(path[i] == 2){
            for(int j = 0; j <= 10; j++){
                out->getPixel(x - j, y).h = 0;
                out->getPixel(x - j, y).s = 1;
                out->getPixel(x - j, y).l = 0.5;
                out->getPixel(x - j, y).a = 1;
            }
            x = x - 10;
        }
        // up
        else if(path[i] == 3){
            for(int j = 0; j <= 10; j++){
                out->getPixel(x, y - j).h = 0;
                out->getPixel(x, y - j).s = 1;
                out->getPixel(x, y - j).l = 0.5;
                out->getPixel(x, y - j).a = 1;
            }
            y = y - 10;
        }
    }
    // whiten the exit
    for (int a = std::max(x - 4, 0); a <= std::min((x + 4), (width * 10 - 1)); a++) {
        out->getPixel(a, y + 5).h = 0;  
        out->getPixel(a, y + 5).s = 1;  
        out->getPixel(a, y + 5).l = 1; 
    }
    return out;
}