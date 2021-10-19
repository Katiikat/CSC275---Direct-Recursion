#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>


#define mazetype std::vector<std::vector<int>>
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

#define OPEN 0
#define WALL 1
#define START 2
#define END 6

#define VISITED 13

//prints maze to specific characters to resemble walls as "W" and the track as open space " "
void printMaze(mazetype *a_Mei_zed)
{
    int vectorSize = a_Mei_zed->size();
    for(int y = 0; y < vectorSize; y++)
    {
        int rowSize = a_Mei_zed->at(y).size();
        std::cout << "|";
        for(int x = 0; x < rowSize; x++)
        {
            int cell = a_Mei_zed->at(y).at(x);

            if(cell == OPEN)
            {
                std::cout << "W";
            }
            if(cell >= VISITED)
            {
                std::cout << " ";
            }
            if(cell == WALL)
            {
                std::cout << "W";
            }
            if(cell == END)
            {
                std::cout << "E";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}
//creates our maze to the specified width & height provided by the user
void initalizeMeize(mazetype *a_Mei_zed, int width, int height)
{
    a_Mei_zed->clear();

    for(int y = 0; y < height; y++)
    {
        std::vector<int> row = std::vector<int>();

        for(int x = 0; x < width; x++)
        {
            row.push_back(OPEN);
        }
        a_Mei_zed->push_back(row);
    }
}

//tests all available movements that are currently open. Stores all possible movements in a vector to return.
std::vector<int> validMovements(mazetype *a_Mei_zed, int xCord, int yCord)
{

    std::vector<int> valid;


    if(yCord+1 < a_Mei_zed->size() && a_Mei_zed->at(yCord+1).at(xCord) == OPEN) //checking down or south
    {
        valid.push_back(SOUTH);
    }

    if(yCord-1 > 0 && a_Mei_zed->at(yCord-1).at(xCord) == OPEN) //checking Up or nerth
    {
        valid.push_back(NORTH);
    }

    if(xCord +1 < a_Mei_zed->at(yCord).size() && a_Mei_zed->at(yCord).at(xCord+1) == OPEN) //checking right or east
    {
        valid.push_back(EAST);
    }

    if(xCord -1 > -1 && a_Mei_zed->at(yCord).at(xCord-1) == OPEN) //checking left or west
    {
        valid.push_back(WEST);
    }
    return valid;
}

//decodes direction name to cell offsets.
std::vector<int> decodeDirection(int direction)
{
    if(direction == NORTH)
    {
        return {0,-1};
    }
    if(direction == SOUTH)
    {
        return {0,1};
    }
    if(direction == WEST)
    {
        return {-1,0};
    }
    if(direction == EAST)
    {
        return {1,0};
    }
}

//didn't want to type cout over and over ---LAZY MODE
//prompts user for input
int prompt(std::string a)
{
    int temp;
    std::cout << a << std::endl;
    std::cin >> temp;
    return temp;
}

//the hard part...
void theBuild(mazetype *a_Mei_zed, int x, int y)
{
    // *** TO DO ***
    //set cell to visited
    //test cell areas
    //random direction chosen
    //choose another random for wall that isn't visited
    //then recursive centaur

    //mark the current cell as visited
    a_Mei_zed->at(y).at(x) = VISITED;

    auto valid = validMovements(a_Mei_zed,x,y);
    //while there are available moves
    while(valid.size())
    {
        //no more valid movements
        if (valid.size() == 0)
        {
            return;
        }
        //randomly choose which direction to go from available movements
        int directionIndex = rand() % valid.size();
        int wallIndex = directionIndex;
        //if theres more than one valid movement left
        if (valid.size() > 1)
        {
            //makes sure we don't put a wall where we are moving to
            while (wallIndex == directionIndex)
            {
                wallIndex = rand() % valid.size();
            }
            //creates and places the wall -- pink floyd
            auto wall = decodeDirection(valid.at(wallIndex));
            if (a_Mei_zed->at(y + wall.at(1)).at(x + wall.at(0)) == OPEN)
            {
                a_Mei_zed->at(y + wall.at(1)).at(x + wall.at(0)) = WALL;
            }
        }
        else
        {
            wallIndex = -1;
        }

        auto direction = decodeDirection(valid.at(directionIndex));
        //new coordinates
        int newX = x + direction.at(0);
        int newY = y + direction.at(1);

        //put here for video
        //DOIN' IT LIVE
        printMaze(a_Mei_zed);
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        usleep(32000);

        //RECURSION....is really confusing
        theBuild(a_Mei_zed, newX, newY);

        //Let the backtracking...BEGIN!

        //removes the direction we went in
        valid.erase(valid.begin()+directionIndex);
        //removes the direction we placed a wall in
        if (wallIndex != -1)
        {
            if (directionIndex > wallIndex)
                valid.erase(valid.begin()+wallIndex);
            else
                valid.erase(valid.begin()+wallIndex - 1);
        }
    }
}


int main()
{
    mazetype a_Mei_zed;
    int width = prompt("Enter a number: ");
    int height = prompt("Enter a number: ");
    initalizeMeize(&a_Mei_zed,width, height);
    srand(static_cast<unsigned int>(time(0)));
    theBuild(&a_Mei_zed, 0,0);
    printMaze(&a_Mei_zed);

    return 0; //thumbs up emoji
}
