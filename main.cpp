#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
void wait (int T)
{
    for (int t=0;t<T;t++)
    {
         for(int c=0; c<=99999;c++)
    {
    }
    }
}
void gotoRowCol(int rpos, int cpos)
{
    int xpos=cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}
void L2R (int R, int cs, int ce, char S)
{
    for (int c=cs; c<= ce; c++)
    {
        gotoRowCol(R,c);
        cout<<S;
    }
}
void T2B (int c, int Rs, int Re, char S)
{
    for (int R=Rs; R<=Re; R++ )
    {
        gotoRowCol(R,c);
        cout<<S;
    }
}
void PrintBox (int Sr,int Sc, int cdim,int rdim,char S)
{
    for (int ri=Sr;ri<rdim+Sr;ri++)
    {
        for (int ci=Sc; ci<cdim+Sc;ci++)
        {
            if(ri==Sr|| ci==Sc||ri==Sr+rdim-1||ci==Sc+cdim-1)
            {
                gotoRowCol(ri,ci);
                cout<<S;
            }
        }
    }
}
void PrintBN(int BN,int rdim,int cdim,char S)
{
    int Sr=((BN-1)/10)*rdim;
    int Sc=(((BN-1)%10)*cdim);
    PrintBox(Sr,Sc,cdim,rdim,S);
}
int NumberToBN (int num)
{
    if (((num-1)/10)%2 ==0   )
        return num;
    else
    {
        int rowskip=( (num-1)/10)*10;
        int ci=10-(num-1 )%10;
        return rowskip+ci;
    }
}
void PrintInCenter (int BN, int value, int rdim, int cdim)
{
    int Cri=((BN-1)/10)*rdim+rdim/2;
    int Cci=(((BN-1)%10)*cdim)+cdim/2-(1);
    value=NumberToBN(value);

    gotoRowCol(Cri,Cci);
    cout<<101-value;
}
void PrintGrid (int rdim, int cdim, char S)
{
    for (int i=1;i<=100;i++)
    {
        PrintBN(i,rdim,cdim,S);
        PrintInCenter(i,i,rdim,cdim);
    }
}
void PrintTable (int Sr,int Sc, int cdim,int rdim,int HL,int VL,char S)
{
    for (int C=Sc, i=1; i<=VL; C+=cdim,i++)
    {
        T2B(C,Sr,(rdim*5)+Sr,S);
    }
    for (int R=Sr, i=1; i<=HL; R+=rdim,i++)
    {
        L2R(R,Sc,(cdim*2)+Sc,S);
    }

}

void PrintSnakesLadders (int Snakes[][2],int Ladders[][2],int Nos,int Nol,int rdim,int cdim)
{
    PrintTable(3,80,8,5,6,3,-37);
    gotoRowCol(1, 85);
    cout<<"SNAKES";
    for (int i=0,R=6; i<Nos; i++,R+=5)
    {
        gotoRowCol(R,83);
        cout<<Snakes[i][0];
        gotoRowCol(R, 92);
        cout<<Snakes[i][1];
    }

    PrintTable(35,80,8,5,6,3,-37);
    gotoRowCol(33,85);
    cout<<"LADDERS";

    for (int i=0,R=38; i<Nol; i++,R+=5)
    {
        gotoRowCol(R,83);
        cout<<Ladders[i][0];
        gotoRowCol(R, 92);
        cout<<Ladders[i][1];
    }
}
void Init (int PPos[], int Nop)
{
    for (int i=0; i<Nop; i++)
    {
        PPos[i]=0;
    }
}

void DisplayDice()
{
    L2R(70,80,88,-37);
    L2R(76,80,88,-37);
    T2B(80,70,76,-37);
    T2B(88,70,76,-37);
}
int RollDice()
{
    int d,total=0;

    do
    {
        gotoRowCol(71,0);
        cout<<"Press Any Key to Roll the Dice and Again Press To Stop !";
        getch();
        while(!kbhit())
        {
            wait(3);
            d=rand()%6+1;

            gotoRowCol(72,83);
            cout<<d;

        }
        while (kbhit())
            {
                getch();
            }
        total=total+d;
        if (d%6==0)
            {
                gotoRowCol(73,0);
                cout<<"You Got 6! Press Any Key to Go Again!";
            }
        if (d==18)
            return 0;
    }
    while (d%6==0);

    return total;
}
void ChangePos ( int & Ppos, int dice)
{
    if ((Ppos==0 && dice >6) )
        {
            Ppos=Ppos+dice-6;
        }
    else if (Ppos>0 && Ppos+dice<101)
        Ppos=Ppos+dice;
}
void PrintPlayerPos (int Ppos, char S, int rdim, int cdim)
{
    Ppos=101-Ppos;
    Ppos=NumberToBN(Ppos);

    int Cri=((Ppos-1)/10)*rdim+rdim/3;
    int Cci=(((Ppos-1)%10)*cdim)+cdim/2+2;
    gotoRowCol(Cri,Cci);
    cout<<S;
}
bool CheckForSnakeBite (int & Ppos, int Snakes[][2],int Nos)
{
    for (int s=0; s<Nos;s++)
    {
        if (Snakes[s][0]==Ppos)
        {
            Ppos=Snakes[s][1];
            return true;
        }
    }
    return false;
}
bool CheckForLadders (int & Ppos, int Ladders[][2],int Nol)
{
    for (int s=0; s<Nol;s++)
    {
        if (Ladders[s][0]==Ppos)
        {
            Ppos=Ladders[s][1];
            return true;
        }
    }
    return false;
}
void TurnChanger (int & Turn, int Nop)
{
    Turn=(Turn+1)%Nop;
}
void SnakeLaddersPlaces (int Snakes [][2],int Ladders[][2],int Nos, int Nol,int rdim,int cdim)
{
    for (int k=1; k<=100;k++)
    {
       int S=k;

        for (int i=0;i<Nos;i++)
        {
            if (S==Snakes[i][0] )
            {
                S=101-S;
                S=NumberToBN(S);
                int Cri=((S-1)/10)*rdim+rdim/2-1;
                int Cci=(((S-1)%10)*cdim)+cdim/2;
                gotoRowCol(Cri,Cci);
                cout<<"S";

            }
            if (S==Snakes[i][1])
            {
                S=101-S;
                S=NumberToBN(S);
                int Cri=((S-1)/10)*rdim+rdim/2-1;
                int Cci=(((S-1)%10)*cdim)+cdim/2;
                gotoRowCol(Cri,Cci);
                cout<<"s";
            }
            if (S==Ladders[i][0] )
            {
                S=101-S;
                S=NumberToBN(S);
                int Cri=((S-1)/10)*rdim+rdim/2-1;
                int Cci=(((S-1)%10)*cdim)+cdim/2;
                gotoRowCol(Cri,Cci);
                cout<<"l";
            }
            if (S==Ladders[i][1] )
            {
                S=101-S;
                S=NumberToBN(S);
                int Cri=((S-1)/10)*rdim+rdim/2-1;
                int Cci=(((S-1)%10)*cdim)+cdim/2;
                gotoRowCol(Cri,Cci);
                cout<<"L";

            }

        }

    }
}
int main()
{
    int  Turn=0,dice,Nop=2;
    cout<<"Number Of Players : ";
    cin>>Nop;
    char Psym[Nop];
    for (int i=0; i<Nop;i++)
    {
        cout<<"Enter P"<<Turn+1<<"'s Symbol : ";
        cin>>Psym[i];

    }
    system("cls");
    int Winners[Nop];
    int wi=0;
    int Rows=100, Cols=100;
    int cdim=Cols/13,rdim=Rows/13;
    int Nos;
    ifstream SR ("Snakes.txt");
    SR>>Nos;
    int Snakes [Nos][2];
    for (int s=0; s<Nos; s++)
    {
        int ss, se;
        SR>>ss>>se;
        Snakes[s][0]=ss;
        Snakes[s][1]=se;
    }

    int Nol;
    ifstream LR ("Ladders.txt");
    LR>>Nol;
    int Ladders [Nol][2];
    for (int s=0; s<Nol; s++)
    {
        int ls, le;
        LR>>ls>>le;
        Ladders[s][0]=ls;
        Ladders[s][1]=le;
    }
    int Ppos[Nop];
    Init(Ppos,Nop);
    PrintGrid(rdim,cdim,-37);
    PrintSnakesLadders (Snakes,Ladders,Nos,Nol,rdim,cdim);
    DisplayDice();
    SnakeLaddersPlaces(Snakes,Ladders,Nos,Nol,rdim,cdim);
    do
    {
//        gotoRowCol(84,2);
//        cout<<"                                      ";
        gotoRowCol(81,2);
        cout<<"P"<<Turn+1<<"'s Turn!";
        dice=RollDice();
        int PrevPos=Ppos[Turn];
        ChangePos(Ppos[Turn],dice);
        PrintPlayerPos(PrevPos,' ', rdim,cdim);
        PrintPlayerPos(Ppos[Turn],Psym[Turn],rdim,cdim);
        PrevPos=Ppos[Turn];
        if (CheckForSnakeBite(Ppos[Turn],Snakes,Nos))
        {
            gotoRowCol(84,2);
            cout<<"\bYou Have Been Bitten By Snake!";
            PrintPlayerPos(PrevPos,' ', rdim,cdim);
            PrintPlayerPos(Ppos[Turn],Psym[Turn],rdim,cdim);
        }
//        PrevPos=Ppos[Turn];
        if (CheckForLadders(Ppos[Turn],Snakes,Nos))
        {
            gotoRowCol(84,2);
            cout<<"WowW! You Have Got A   Ladder!";
            PrintPlayerPos(PrevPos,' ', rdim,cdim);
            PrintPlayerPos(Ppos[Turn],Psym[Turn],rdim,cdim);
        }
        if (Ppos[Turn]==100)
        {
            Winners[wi]=Turn;
            wi++;
        }
        do
        {
            TurnChanger(Turn,Nop);
        }
        while (Ppos[Turn]==100);
    }
    while(wi<Nop-1);
    gotoRowCol(82,2);
    cout<<"Player "<<Winners[0]+1<<" Came First !";
    getch();
    cout<<"\n\n\n\n\n\n\n\n\n";
    return 0;
}
