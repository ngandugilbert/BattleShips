#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include<time.h>
using namespace std;

//Create ships
int Gen()
{
    srand(time(NULL));
    return  rand()%2;
}

class Player
{
    string Name;
    int Lives;


public:
    Player()
    {
        Lives=4;
        Name="Captain";
    }
    //get lives
    int getLives()
    {
        return Lives;
    }
    void ReduceLives()
    {
        Lives--;
    }
    void setName(string Name)
    {
        Player::Name=Name;
    }
    string getName()
    {
        return Name;
    }
    void Start();
    void Intro();

};

class Ships
{
    string level;
    int NumberOfShips;
    int AvailableShips;
    int Latitude;
    int Longitude;
    int addShips();
    int counted;
    int Position[7][5]; /*{
        {
            0,1,0,0,0
        },
        {
            0,0,1,0,0
        },
        {
            0,0,1,0,0
        },
        {
            1,0,0,1,0
        },
        {
            0,0,1,0,0
        },
        {
            1,0,0,0,1
        },
        {
            0,1,0,1,0
        }
    };*/
public:


    Ships()
    {
        NumberOfShips=4;
        //AvailableShips=10;
        Latitude=0;
        Longitude=0;

        counted = addShips();
        if(counted == 0)
            counted = addShips();
        if(counted > 0 && counted <=4)
            level = "Easy";
        else if(counted>=5 && counted<8)
            level = "Medium";
        else if(counted == 10 || counted ==9 )
            level = "Hard";


    }
    int getNumberOfShips()
    {
        return NumberOfShips;
    }
    int getAvailableShips()
    {
        return AvailableShips;
    }
    void setLatitude(int Latitude)
    {
        Ships::Latitude=Latitude;
    }
    int getLatitude()
    {
        return Latitude;
    }
    void setLongitude(int Longitude)
    {
        Ships::Longitude=Longitude;
    }
    int getLongitude()
    {
        return Longitude;
    }
    string getLevel()
    {
        return level;
    }
    bool Validate(int, int);
    bool Target();

};

int Ships::addShips()
{
    for(int col = 0; col<7; col++)
    {
        for(int row = 0; row<4; row++)
        {
            int cod = Gen();

            if(AvailableShips<10)
            {
                //keep track of created ships
                AvailableShips +=cod;
                Position[col][row] = cod;
            }
            else
            {
                //if more ships are there set the rest to zeros
                Position[col][row] = 0;

            }
        }
    }

    return AvailableShips;
}



//Player Storage as team multiplayer
struct node
{
    string name;
    node* next;
};

node* End = NULL;
node* p;

#endif // MAIN_H_INCLUDED
