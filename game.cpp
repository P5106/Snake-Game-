#include<bits/stdc++.h> // includes all cpp libraries
#include<conio.h>
#include<windows.h>   // will let us know the coordinates


using namespace std;
#define MAX_LENGTH 1000    //size of snake

//directions
const char DIR_UP='U';
const char DIR_DOWN='D';
const char DIR_LEFT='L';
const char DIR_RIGHT='R';



int consoleWidth,consoleHeight;   //stores height and width of the window

//initializing console screen
void initScreen(){ 
    HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);       //handle is a predefine data type in windows.h help us to handle the console window
    CONSOLE_SCREEN_BUFFER_INFO csbi; // use to store info abput console screen buffer
    GetConsoleScreenBufferInfo(hConsole,&csbi);// fills csbi with current console details
    consoleHeight=csbi.srWindow.Bottom - csbi.srWindow.Top+1;  //srwindow shows visible portion of the console window not buffer
    consoleWidth=csbi.srWindow.Right - csbi.srWindow.Left+1;   
}
struct Point{   //simple data structure, not a behavior-driven object if we use class then also same work will be done
    int xCoord;
    int yCoord;
    Point(){
    }
    Point(int x,int y){
        xCoord=x;
        yCoord=y;
    }
};
class Snake{
    int length;
    int direction;
    public:
    Point body[MAX_LENGTH];  //used to store the position of snakes entire body
    Snake(int x,int y){
        length=1;
        body[0]=Point(x,y); // head of the snake
        direction=DIR_RIGHT;   // by default right

    }

    


    int getLength(){
        return length;
    }  //returns the current length

    void changeDirection(char newDirection){
        if(newDirection==DIR_UP&& direction!=DIR_UP){
            direction=newDirection;
        }
         else if(newDirection==DIR_DOWN && direction!=DIR_UP){
            direction=newDirection;
        }
         else if(newDirection==DIR_LEFT && direction!=DIR_RIGHT){
            direction=newDirection;
        }
         else if(newDirection==DIR_RIGHT && direction!=DIR_LEFT){
            direction=newDirection;
        }
    }
    bool move(Point food){    
        for(int i=length;i>0;i--){
            body[i]=body[i-1];    
        }
        switch(direction)
        {
            int val;
            case DIR_UP:
                val=body[0].yCoord;
                body[0].yCoord=val-1;
                break;
            case DIR_DOWN:
                val=body[0].yCoord;
                body[0].yCoord=val+1;
                break;
            case DIR_RIGHT:
                val=body[0].xCoord;
                body[0].xCoord=val+1;
                break;
            case DIR_LEFT:
                val=body[0].xCoord;
                body[0].xCoord=val-1;
                break;

        }

        //snake bites itself
        for(int i=1;i<length;i++){
            if(body[0].xCoord==body[i].xCoord && body[0].yCoord==body[i].yCoord){
                return false;
            }
        }

        //snake eats food
        if(food.xCoord==body[0].xCoord && food.yCoord==body[0].yCoord){
            body[length]=Point(body[length-1].xCoord,body[length-1].yCoord);
            length ++;

        }
        return true;
    }
};

class Board{
    Snake *snake;
    const char SNAKE_BODY='O';
    Point food;
    const char FOOD='o';
    int score;
    public:
    Board(){
        spawnFood();
        snake=new Snake(10,10);   //start position
        score=0;
    }
    ~Board(){

        
        delete snake;
    }
    int getScore(){
        return score;
    }
    void spawnFood(){   /// give random position for food
        int x=rand()%consoleWidth;
        int y=rand()%consoleHeight;   
        food=Point(x,y);
    }

    void displayCurrentScore(){
        gotoxy(consoleWidth/2,0);     ///print score in the middle
        cout<<"display current score"<<score;
    }
    void gotoxy(int x,int y){
        COORD coord; // present in windows.h
        coord.X=x;
        coord.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);   //take cursor at the that position


    }
    void draw(){
        system ("cls");   /// clear console window
        for(int i=0;i<snake->getLength();i++){
            gotoxy(snake->body[i].xCoord,snake->body[i].yCoord);
            cout<<SNAKE_BODY;
        }
        gotoxy(food.xCoord,food.yCoord);
        cout<<FOOD;
        displayCurrentScore();
    }

    bool update(){    /// ask whether we want to continue the game or not
        bool isAlive=snake->move(food);
        if(isAlive==false){
            return false;
        }
        if(food.xCoord==snake->body[0].xCoord && food.yCoord==snake->body[0].yCoord){
            score++;
            spawnFood();


        }
        return true;
    }

    void getInput(){
        if(kbhit()){
            int key=getch();
            if(key=='u'||key=='U'){
                snake->changeDirection(DIR_UP);
            }
             if(key=='d'||key=='D'){
                snake->changeDirection(DIR_DOWN);
            }
             if(key=='r'||key=='R'){
                snake->changeDirection(DIR_RIGHT);
            }
             if(key=='l'||key=='L'){
                snake->changeDirection(DIR_LEFT);
            }
        }
    }


};




int main(){
    initScreen();
    Board *board=new Board();
    while(board->update()){
        board->getInput();
        board->draw();
        Sleep(1000);   // change position after 1 sec
    }
    cout<<"game over"<<endl;
    cout<<"final score:"<<board->getScore();


    return 0;
}


