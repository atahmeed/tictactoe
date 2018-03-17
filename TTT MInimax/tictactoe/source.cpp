#include <iostream>
#include <cstdlib>
#define infinity 1000
#include <time.h>
using namespace std;

int utility[9];
class Square
{
private:


public:
    char sq[3][3];
    bool filled[3][3] = {{false}};
    Square()
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                sq[i][j] = '.';
    }

    void title()
    {
        cout<<"+----------------------------------------------------+"<<endl;
        cout<<"+         Tic-Tac-Toe with mini-max algorithm        +"<<endl;
        cout<<"+----------------------------------------------------+"<<endl<<endl<<endl;
    }
    void display()
    {
       system("cls");
        title();
        cout<<"r |             "<<endl;
        cout<<"-------------"<<endl;
        for(int i=0;i<3;i++)
        {
            cout<<i+1;
            for(int j=0;j<3;j++)
                cout<<" | "<<sq[i][j];

            if(i!=2){
            cout<<endl<<"  ___________"<<endl;
            }
        }
        cout<<endl<<"-------------"<<endl;
        cout<<"c | 1 | 2 | 3  ";
        cout<<endl;
    }
    bool isTerminalState(Square s)
    {
        if(s.goal_test()!=0) return true;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(sq[i][j] == '.') return false;
        return true;

    }
    void sqinput()
    {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                cin>>sq[i][j];
    }

    int goal_test()
    {
        if(sq[0][0]=='X' && sq[0][1]=='X' && sq[0][2]=='X') return 1;
        else if(sq[1][0]=='X' && sq[1][1]=='X' && sq[1][2]=='X') return 1;
        else if(sq[2][0]=='X' && sq[2][1]=='X' && sq[2][2]=='X') return 1;
        else if(sq[0][0]=='X' && sq[1][0]=='X' && sq[2][0]=='X') return 1;
        else if(sq[0][1]=='X' && sq[1][1]=='X' && sq[2][1]=='X') return 1;
        else if(sq[0][2]=='X' && sq[1][2]=='X' && sq[2][2]=='X') return 1;
        else if(sq[0][0]=='X' && sq[1][1]=='X' && sq[2][2]=='X') return 1;
        else if(sq[2][0]=='X' && sq[1][1]=='X' && sq[0][2]=='X') return 1;

        else if(sq[0][0]=='O' && sq[0][1]=='O' && sq[0][2]=='O') return -1;
        else if(sq[1][0]=='O' && sq[1][1]=='O' && sq[1][2]=='O') return -1;
        else if(sq[2][0]=='O' && sq[2][1]=='O' && sq[2][2]=='O') return -1;
        else if(sq[0][0]=='O' && sq[1][0]=='O' && sq[2][0]=='O') return -1;
        else if(sq[0][1]=='O' && sq[1][1]=='O' && sq[2][1]=='O') return -1;
        else if(sq[0][2]=='O' && sq[1][2]=='O' && sq[2][2]=='O') return -1;
        else if(sq[0][0]=='O' && sq[1][1]=='O' && sq[2][2]=='O') return -1;
        else if(sq[2][0]=='O' && sq[1][1]=='O' && sq[0][2]=='O') return -1;

        else return 0;

    }
    void computer_fill(int action)
    {
        sq[action/3][action%3] = 'X';
    }
    void human_fill(int action)
    {
        sq[action/3][action%3] = 'O';
    }
    int act(int *a,int val)
    {
        for(int i=0;i<9;i++)
            if(a[i]==val)
                return i;
    }
};

int rctoaction(int r,int c)
{
    return r*3 + c;
}

int minimax(int v, bool isMax, Square Tsq,int mov)
{

    if(Tsq.isTerminalState(Tsq)) return Tsq.goal_test();
    if(isMax)
    {
        for(int i = 0 ;i < 9 ; i++)
        {
            Square temp = Tsq;
            if(temp.sq[i/3][i%3]=='.')
            {
                temp.computer_fill(i);
                //Tsq.display();
                int u = minimax(infinity,!isMax,temp,mov+1);
                v= max(v , u);
                if(mov==1)
                    utility[i] = u;

            }
        }
        return v;
    }
    else{
        for(int i = 0 ;i < 9 ; i++)
        {
            Square temp = Tsq;
            if(temp.sq[i/3][i%3]=='.')
            {
                temp.human_fill(i);
                //Tsq.display();
                int u = minimax(-1*infinity,!isMax,temp,mov+1);
                v =  min(v , u);
            }
        }
        return v;

    }
}
int main()
{
    srand(time(NULL));  //first move by the AI will be random if AI plays first
    bool circle, draw = true;
    int Movenum=0;
    char decison;

    Square SQ;  //tic-tac-toe square object

    SQ.title();
    // Computer or Human plays first
    cout<<"Go first?: (y/n):";
    cin>>decison;
    if(decison=='y'||decison=='Y') circle = true;
    else circle = false;

    SQ.display();
    cout<<endl<<"(Row  Column)= ";

    // the play goes on until the game reaches terminal state(all filled/ win/ loss)
    while(!SQ.isTerminalState(SQ))
    {

        //if current player is human = circle
        if(circle){
            int r,c;
            cin>>r>>c;
            if(r>3 || c>3)
            {
                cout<<"Out of the box!"<<endl;
                continue;
            }
            r--; c--;
            if(SQ.filled[r][c] == true )
            {
                cout<<"Already Filled"<<endl;
                continue;
            }
            SQ.human_fill(rctoaction(r,c)); // put O for provided row and column of human
            SQ.filled[r][c] = true;
        }
        //if current player is AI which is not circle
        else
        {
            int action; // to store the action which provides optimal move
            if(Movenum==0) action = rand()%10; //first move by AI = random move
            else
            {
                for(int i=0;i<9;i++) utility[i]=-10; //utility of each square is set to -10, each is set to some value after minimax is called
                int x = minimax(-1*infinity,true,SQ,1); // x stores the highest utility value for all the child nodes from current node
                action = SQ.act(utility, x); // the action that leads to that MAX value x
            }
            SQ.computer_fill(action); // put x for the given action
            SQ.filled[action/3][action%3] = true; //Mark that box as filled
        }
        Movenum++; //increase move number
        circle=(!circle); //change player
        SQ.display(); //show square state after every move
        int res = SQ.goal_test(); // store result

        //output result
        if(res!=0)
        {
            draw = false;
            if(res==-1) cout<<endl<<"You win"<<endl;
            else cout<<endl<<"AI wins"<<endl;
            break;
        }
    }
    if(draw)cout<<endl<<"DRAW!"<<endl;

    return 0;
}
