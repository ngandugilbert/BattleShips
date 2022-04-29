//BattleShips
//Author: Gilbert Ng'andu
//Date: 27/04/2022
#include<iostream>
#include<unistd.h>
using namespace std;

void MainMenu(),Header(),delay(int),loading(int),GameOver(),Boom();


class Player {
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

class Ships {
    int NumberOfShips;
    int AvailableShips;
    int Latitude;
    int Longitude;
    int Position[7][5] {
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
    };
public:
    Ships()
    {
        NumberOfShips=4;
        AvailableShips=10;
        Latitude=0;
        Longitude=0;
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
    bool Validate(int, int);
    bool Target();

};

Player player1;
Ships shoot;
int main()
{
    MainMenu();

    return 0;
}

void MainMenu()
{
    int choice=0;
    cout<<"Welcome to BattleShips\n\n";
    cout<<"1. Start\n2. Leader Board\n3. Help\n4. Exit\nChoice: ";
    cin>>choice;
    switch(choice) {
    case 1:
        player1.Intro();
        break;
    case 2:
        //LeaderBoard();
        break;
    case 3:
        //Help();
        break;
    case 4:
        //Exit();
        break;
    }

}
void Player::Intro()
{
    system("cls");
    Header();
    string userName;

    cout<<"POP: AAy! Captain, the battle is on!"<<endl;
    cout<<"Captain: Ayt mate but call me by my name!\n"<<endl;
    cout<<"POP: I feel you Caps!, what be your name?"<<endl;
    cout<<"Enter your name: ";
    cin>>userName;
    player1.setName(userName);
    cout<<"\nPOP: Ayt captain, I shall call you "<<player1.getName()<<" from now on!"<<endl;
    cout<<player1.getName()<<" :great mate! let's burn some ships!"<<endl;
    cout<<"\nPlease wait";
    loading(5);
    player1.Start();
}
void Player::Start()
{

    int userLati, userLongi;
    do {
        system("cls");
        Header();
        cout<<"POP: Aaay "<<player1.getName()<<" where's the enemy?"<<endl;
        cout<<player1.getName()<<" :Mates!set the canon here and fire at my command!,"<<endl;
        cout<<"Latitude: ";
        cin>>userLati;
        cout<<"Longitude: ";
        cin>>userLongi;
        if(shoot.Validate(userLati, userLongi)) {
            cout<<"\nLocating target ship";
            loading(5);
            if(shoot.Target()) {
                //shot
                Boom();
                cout<<"\n"<<player1.getName()<<": Got you!"<<endl;
                delay(2);
                if(shoot.getAvailableShips()==0 && player1.getLives()>0) {
                    //You win
                    system("cls");
                    Header();
                    char choice;
                    cout<<"Hooray! We won!";
                    cout<<"Do you wish to play again?(y/n)"<<endl;
                    cin>>choice;
                }
            }
            else {
                //miss
                cout<<"\nEnemy: Is that all you got?! Come! you are not even trying.\n"<<endl;
                delay(2);
                player1.ReduceLives();
                if(player1.getLives()==0 && shoot.getAvailableShips() != 0) {
                    GameOver();
                }
            }
        }
        else {
            //error message
            cout<<"POP: Your coordinates were invalid "<<player1.getName()<<endl;
            delay(2);
        }
    }
    while(shoot.getAvailableShips() != 0 && player1.getLives() >= 0);
}
bool Ships::Validate(int row, int col)
{
    if(row>=0 && row<7 && col>=0 && col<5) {
        setLatitude(row);
        setLongitude(col);
        return true;
    }
    else
        return false;
}
bool Ships::Target()
{
    if(Position[Latitude][Longitude]==1) {
        AvailableShips--;
        Position[Latitude][Longitude]=0;
        return true;
    }
    else
        return false;
}

void Header()
{
    cout<<"____________________________________________________________________________________"<<endl;
    cout<<"BattleShips"<<" | Player Name: "<<player1.getName()<<" | Lives: "<<player1.getLives()<<" | Enemy ship(s): "<<shoot.getAvailableShips()<<endl;
    cout<<"____________________________________________________________________________________\n"<<endl;


}
void delay(int time)
{
    unsigned int microsecond = 1000000;
    usleep(time * microsecond);//sleeps for 1 second
}
void loading(int time)
{
    for(int i=0; i<=time; i++) {
        cout<<".";
        delay(1);
    }
}
void GameOver()
{
    system("cls");
    int choice;
    Header();
    char Lost[]= {'G','A','M','E','O','V','E','R','!'};
    for(int i=0; i<9; i++) {
        cout<<Lost[i]<<"-";
        delay(1);
    }
    cout<<"\nDo you wish to continue?(y/n)";
    cin>>choice;
}
void Boom()
{
    system("cls");
    Header();
    char boom[8]= {'B', 'O','O','O','O','O','M','!'};
    for(int i=0; i<8; i++) {
        cout<<boom[i]<<"-";
        delay(1);
    }
}

