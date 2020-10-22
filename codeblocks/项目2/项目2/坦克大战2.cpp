#include <windows.h>
#include <time.h>
#include <iostream>
using namespace std;

#define UP    1
#define DOWN  2
#define LEFT  3
#define RIGHT 4
#define MAX_LEVEL 4
#define BULLET_NUM 40
#define MAX_LIFE 5
#define MAX_LIFE2 5

//定义一些全局变量
int map[41][41];
void PrintMap();
string s;
int bul_num;
int position;
int speed=7;
int level=2;
int score=0;
int score2=0;
int remain_enemy;
int model;
int bullets1=0;
int bullets2=0;

//定义基本函数
void HideCursor();
void GoToxy(int x,int y);//光标移动函数
void Frame (); //打印游戏主体框架

void SideScreen ();//副屏幕打印
void SideScreen2 ();//副屏幕打印

void ColorChoose(int color);//颜色选择函数
void keyboard();
void Stop();

void GetMap();
void GetMap2();

void PrintMap();
void CleanMainScreen1();

void GameOver(bool home);
void GameOver2(int home);//游戏结束多样化

void Initialize();
void Initialize2();

void Nextlevel();
void Nextlevel2();

void GameCheak();
void GameCheak2();

//坦克模型类，-1代表没有该类型坦克
class LevInfo
{
private:
    int fast_tank_order;
    int firm_tank_order;
public:
    LevInfo(int x,int y)
    {
        fast_tank_order = x;
        firm_tank_order = y;
    }
    int GetFast_tank_order(){return fast_tank_order;};
    int GetFirm_tank_order(){return firm_tank_order;};
};
//列表初始化
LevInfo level_info[MAX_LEVEL] = {{-1,-1},{3,-1},{-1,3},{2,3}};

//坦克类型
const char *tank_figure[4][3][4]=
{
  {
    {"◢┃◣", "◢━◣", "◢┳◣", "◢┳◣"},
    {"┣●┫", "┣●┫", "━●┃", "┃●━"},
    {"◥━◤", "◥┃◤", "◥┻◤", "◥┻◤"}
  },
  {
    {"┏┃┓", "┏┳┓", "┏┳┓", "┏┳┓"},
    {"┣●┫", "┣●┫", "━●┫", "┣●━"},
    {"┗┻┛", "┗┃┛", "┗┻┛", "┗┻┛"}
  },
  {
    {"┏┃┓", "◢━◣", "┏┳◣", "◢┳┓"},
    {"┣●┫", "┣●┫", "━●┃", "┃●━"},
    {"◥━◤", "┗┃┛", "┗┻◤", "◥┻┛"}
  },

  {
    {"╔┃╗", "╔╦╗", "╔╦╗", "╔╦╗"},
    {"╠█╣", "╠█╣", "━█╣", "╠█━"},
    {"╚╩╝", "╚┃╝", "╚╩╝", "╚╩╝"}
  }
};

class Tank
{
private:
    int x,y;
    int direction;
    int color;
    int model;
    int stop;//只能是ai坦克使用的参数，非0代表坦克停止走动，0为可以走动
    int revive;//坦克复活次数
    int num;//坦克编号；
    int CD;
    bool my;
    bool alive;
public:
    int GetModel(){return model;};
    void SetModel(int mod){model = mod;};
    int GetDirection(){return direction;};
    void SetDirection(int direc){direction = direc;};
    int GetColor(){return color;};
    void SetColor(int colo){color = colo;};
    int GetStop(){return stop;};
    void SetStop(int sto){stop = sto;};
    int GetRevive(){return revive;};
    void SetRevive(int reviv){revive = reviv;};
    int GetNum(){return num;};
    void SetNum(int nu){num = nu;};
    int GetCD(){return CD;};
    void SetCD(int x){CD=x;};
    bool GetMy(){return my;};
    void SetMy(bool m){my = m;};
    bool GetAlive(){return alive;};
    void SetAlive(bool ali){alive = ali;};
    int GetX(){return x;};
    int GetY(){return y;};
    void SetX(int x1){x = x1;};
    void SetY(int y1){y = y1;};

    int AIPositionCheak(int position);

    void MoveMyTank(int turn);
    void MoveYourTank(int turn);

    void ClearTank(int x,int y);

    void PrintTank(Tank tank);
    void PrintTank2(Tank tank);

    bool TankCheak(Tank tank,int diretion);
    void BuildBullet(Tank tank);
    void BuildAITank(int *position,Tank *AI_tank);

    void BuildMyTank(Tank *my_tank);
    void BuildYourTank(Tank *your_tank);

    void MoveAITank(Tank *AI_tank);
    void BuildAIBullet(Tank *tank);
};
    Tank AI_tank[4];Tank my_tank;Tank your_tank;

class Bullet
{
private:
    int x,y;
    int direction;
    int exist;
    bool initial;
    bool my;
public:
    int GetX(){return x;};
    int GetY(){return y;};
    void SetX(int x1){x = x1;};
    void SetY(int y1){y = y1;};
    int GetDirection(){return direction;};
    void SetDirection(int dir){direction = dir;};
    int  GetExist(){return exist;};
    void SetExist(int exis){exist = exis;};
    bool GetMy(){return my;};
    void SetMy(bool m){my = m;};
    bool GetInitial(){return initial;};
    bool SetInitial(bool ini){initial = ini;};

    void PrintBullet(int x,int y,int T);
    void ClearBullet(int x,int y,int T);
    int BulletCheak(int x,int y);

    void BulletHit(Bullet *bullet);


};
    Bullet bullet[BULLET_NUM];//函数特殊
    void BulletFly(Bullet bullet[BULLET_NUM]);

void Tank::BuildBullet(Tank tank)
{
    switch(tank.GetDirection())
    {
    case UP:
        bullet[bul_num].SetX(tank.GetX());
        bullet[bul_num].SetY(tank.GetY()-2);
        bullet[bul_num].SetDirection(1);
        break;
    case DOWN:
        bullet[bul_num].SetX(tank.GetX());
        bullet[bul_num].SetY(tank.GetY() + 2);
        bullet[bul_num].SetDirection(2);
        break;
    case LEFT:
        bullet[bul_num].SetX(tank.GetX() - 2);
        bullet[bul_num].SetY( tank.GetY());
        bullet[bul_num].SetDirection(3);
        break;
    case RIGHT:
        bullet[bul_num].SetX(tank.GetX() + 2);
        bullet[bul_num].SetY(tank.GetY());
        bullet[bul_num].SetDirection(4);
        break;
    }
    bullet[bul_num].SetExist(1);
    bullet[bul_num].SetInitial(1);//子弹建立，初始化一
    bullet[bul_num].SetMy(tank.GetMy());
    bul_num++;
    if(bul_num==BULLET_NUM)
        bul_num = 0;
}

void BulletFly(Bullet bullet[BULLET_NUM])
{
    for(int i=0;i<BULLET_NUM;i++)
    {
        if(bullet[i].GetExist())
        {
            if(bullet[i].GetInitial()==0)//如果子弹不是刚刚（指的是没有碰撞）
            {
                if(map[bullet[i].GetY()][bullet[i].GetX()]==0||map[bullet[i].GetY()][bullet[i].GetX()]==5)
                    bullet[i].ClearBullet(bullet[i].GetX(),bullet[i].GetY(),bullet[i].BulletCheak(bullet[i].GetX(),bullet[i].GetY()));
                switch(bullet[i].GetDirection())
                {
                case UP:
                    bullet[i].SetY(bullet[i].GetY()-1);
                    break;
                case DOWN:
                    bullet[i].SetY(bullet[i].GetY()+1);
                    break;
                case LEFT:
                    bullet[i].SetX(bullet[i].GetX()-1);
                    break;
                case RIGHT:
                    bullet[i].SetX(bullet[i].GetX()+1);
                    break;
                }
            }
            if(bullet[i].BulletCheak(bullet[i].GetX(),bullet[i].GetY()))
                bullet[i].PrintBullet(bullet[i].GetX(),bullet[i].GetY(),bullet[i].BulletCheak(bullet[i].GetX(),bullet[i].GetY()));
            else
                bullet[i].BulletHit(&bullet[i]);
            if(bullet[i].GetInitial())
                bullet[i].SetInitial(0);
            for(int j=0;j<BULLET_NUM;j++)
                if(bullet[j].GetExist()&&j!=i&&(bullet[i].GetMy()||bullet[j].GetMy())&&bullet[i].GetX()==bullet[j].GetX()&&bullet[i].GetY()==bullet[j].GetY())
            {
                bullet[j].SetExist(0);
                bullet[i].SetExist(0);
                bullet[i].ClearBullet(bullet[j].GetX(),bullet[j].GetY(),bullet[i].BulletCheak(bullet[j].GetX(),bullet[j].GetY()));
                break;
            }
        }
    }
}
    int j = 0;
void Bullet::BulletHit(Bullet *bullet)
{
    int x = bullet->GetX();
    int y = bullet->GetY();
    int i;
    if(map[y][x]==1||map[y][x]==2)
    {
        if(bullet->GetDirection()==UP||bullet->GetDirection()==DOWN)
            for(i=-1;i<=1;i++)
            if(map[y][x+i]==1||map[y][x+i]==2)
        {
            map[y][x+i]=0;
            GoToxy(2*(x+i),y);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); //背景黑色
            cout<<"  ";
        }
        if(bullet->GetDirection()==LEFT||bullet->GetDirection()==RIGHT)
            for(i=-1;i<=1;i++)
            if(map[y+i][x]==1||map[y+i][x]==2)
        {
            map[y+i][x]=0;
            GoToxy(2*x,y+i);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); //背景黑色
            cout<<"  ";
        }
         bullet->SetExist(0);
    }
    else if(map[y][x]==4||map[y][x]==6)
       bullet->SetExist(0);
    else if(bullet->GetMy()&&map[y][x]>=100&&map[y][x]<104&&model==1)
    {
        ColorChoose(5);
        GoToxy(86,20);
        cout<<"累计击中"<<++j;
        int num = map[y][x]%100;
        if(AI_tank[num].GetModel()==3&&AI_tank[num].GetColor()==2)
            AI_tank[num].SetColor(3);
        else if(AI_tank[num].GetModel()==3&&AI_tank[num].GetColor()==3)
            AI_tank[num].SetColor(4);
        else
        {
            AI_tank[num].SetAlive(0);
            AI_tank[num].ClearTank(AI_tank[num].GetX(),AI_tank[num].GetY());
        }
        bullet->SetExist(0);
        score = score + 100;
        GoToxy(102,4);
        ColorChoose(7);
        cout<<"       ";
        GoToxy(102,4);
        cout<<score;
    }
    else if(map[y][x]==201&&bullet->GetMy()==1&&model==2)
    {
        your_tank.SetAlive(0);
        your_tank.ClearTank(your_tank.GetX(),your_tank.GetY());
        bullet->SetExist(0);
        your_tank.SetRevive(your_tank.GetRevive()+1);
        score2 = score2 - 100;
        GoToxy(102,8);
        ColorChoose(7);
        cout<<"      ";
        GoToxy(102,8);
        cout<<score2;
        GoToxy(102,10);
        cout<<MAX_LIFE-your_tank.GetRevive();
        GoToxy(102,4);
        cout<<"      ";
        score = score + 100;
        GoToxy(102,4);
        cout<<score;
    }
    else if(map[y][x]==200&&bullet->GetMy()==0)
    {
        my_tank.SetAlive(0);
        my_tank.ClearTank(my_tank.GetX(),my_tank.GetY());
        bullet->SetExist(0);
        my_tank.SetRevive(my_tank.GetRevive()+1);
        score = score - 100;

        GoToxy(102,4);
        ColorChoose(7);
        cout<<"      ";
        GoToxy(102,4);
        cout<<score;
        GoToxy(102,6);
        cout<<MAX_LIFE-my_tank.GetRevive();
        if(model==2)
        {
        score2 = score2 + 100;
        GoToxy(102,8);
        cout<<"      ";
        GoToxy(102,8);
        cout<<score2;
        }
    }
    else if(map[y][x]==9&&model==1)
    {
        bullet->SetExist(0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
        GoToxy(38,37);     cout<<"      ";
        GoToxy(38,38);     cout<<"███";
        GoToxy(38,39);     cout<<"      ";
        score = score - 500;
        GoToxy(102,4);
        ColorChoose(7);
        cout<<"       ";
        GoToxy(102,4);
        cout<<score;
        GameOver(1);           //游戏结束,传入1代表老家被毁
    }
    else if(map[y][x]==9&&model==2)
    {
        bullet->SetExist(0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
        GoToxy(38,37);     cout<<"      ";
        GoToxy(38,38);     cout<<"███";
        GoToxy(38,39);     cout<<"      ";
        GameOver2(3);           //游戏结束,传入1代表老家被毁
    }
    else if(map[y][x]==8&&model==2)
    {
        bullet->SetExist(0);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
        GoToxy(38,1);     cout<<"      ";
        GoToxy(38,2);     cout<<"███";
        GoToxy(38,3);     cout<<"      ";
        GameOver2(4);
    }
}
int Bullet::BulletCheak(int x,int y)
{
    if(map[y][x]==0)
        return 1;
    else if(map[y][x]==5)
        return 2;
    else
        return 0;
}

void Bullet::PrintBullet(int x,int y,int T)
{
    if(T==1)//  T==1 表示子弹当前坐标在陆地上
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    else if(T==2)//  T==2 表示子弹当前坐标在水面上
       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_BLUE);
    GoToxy(2*x,y);
    cout<<"a";
}

void Bullet::ClearBullet(int x,int y,int T)
{
    GoToxy(2*x,y);
    if(T==2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_GREEN);
        cout<<"～";
    }
    else if(T==1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE);
        cout<<"  ";
    }
}

void Tank::BuildAITank(int *position,Tank *AI_tank)
{
    if(AI_tank->AIPositionCheak(*position))
    {
        AI_tank->SetX(20 + 18*(*position));
        AI_tank->SetY(2);
        if(AI_tank->GetRevive()==level_info[level-1].GetFirm_tank_order())//依据管卡的不同而设置不同的坦克
        {
            AI_tank->SetModel(3);
            AI_tank->SetColor(2);
        }
        else if(AI_tank->GetRevive()==level_info[level-1].GetFast_tank_order())
        {
            AI_tank->SetModel(2);
            AI_tank->SetColor(rand()%6 + 1);
        }
        else
        {
            AI_tank->SetModel(1);
            AI_tank->SetColor(rand()%6 + 1);
        }
        AI_tank->SetAlive(1);
        AI_tank->SetDirection(2);
        int revi = AI_tank->GetRevive();
        AI_tank->SetRevive(++revi);
        AI_tank->PrintTank(*AI_tank);
        (*position)++;
        remain_enemy--;
        GoToxy(102,8);
        cout<<"       ";
        ColorChoose(7);
        GoToxy(102,8);
        cout<<remain_enemy;
        if(*position==2)
            *position = -1;
        return ;
    }

}

Tank::AIPositionCheak(int position)
{
    int x,y;
    if(position==2)
      x = 15,y = 38;
    else
        y = 2,x = 20 + 18*position;
    for(int i=0;i<3;i++)
        for(int j = 0;j<3;j++)
        if(map[y+j-1][x+i-1]!=0)
        return 0;
    return 1;
}

void Tank::MoveAITank(Tank *AI_tank)
{
    if(AI_tank->GetAlive())
    {
        if(AI_tank->GetStop()!=0)
        {
            AI_tank->SetStop(AI_tank->GetStop()-1);
            return;
        }
    AI_tank->ClearTank(AI_tank->GetX(),AI_tank->GetY());
    if(AI_tank->TankCheak(*AI_tank,AI_tank->GetDirection()))
        switch(AI_tank->GetDirection())
    {
        case UP: AI_tank->SetY(AI_tank->GetY()-1);break;

        case DOWN:AI_tank->SetY(AI_tank->GetY()+1);break;

        case LEFT:AI_tank->SetX(AI_tank->GetX()-1);break;

        case RIGHT:AI_tank->SetX(AI_tank->GetX()+1);break;
    }
    else
    {
        if(!(rand()%4))//四分之一的几率
           {
               AI_tank->SetDirection(rand()%4 + 1);
               AI_tank->SetStop(2);
               AI_tank->PrintTank(*AI_tank);
               return ;
           }
           else
            {
                int j;
                for(j=1;j<4;j++)
                    if(AI_tank->TankCheak(*AI_tank,j))
                    break;
                if(j==5)
                {
                    AI_tank->PrintTank(*AI_tank);
                    return ;
                }
                while(AI_tank->TankCheak(*AI_tank,AI_tank->GetDirection()==0))
                    AI_tank->SetDirection(rand()%4+1);
            }
    }
    AI_tank->PrintTank(*AI_tank);
  }
}

void Tank::BuildMyTank(Tank *my_tank)
{
    my_tank->SetX(15);
    my_tank->SetY(38);
    my_tank->SetStop(0);
    my_tank->SetDirection(1);
    my_tank->SetModel(0);
    my_tank->SetColor(6);
    my_tank->SetAlive(1);
    my_tank->SetMy(1);
    my_tank->SetCD(0);
    my_tank->PrintTank2(*my_tank);
}
void Tank::BuildYourTank(Tank *your_tank)
{
    your_tank->SetX(26);
    your_tank->SetY(2);
    your_tank->SetStop(0);
    your_tank->SetDirection(1);
    your_tank->SetModel(0);
    your_tank->SetColor(5);
    your_tank->SetAlive(1);
    your_tank->SetMy(0);
    your_tank->SetCD(0);
    your_tank->PrintTank2(*your_tank);
}

void Tank::MoveMyTank(int turn)
{
    my_tank.ClearTank(my_tank.GetX(),my_tank.GetY());
    my_tank.SetDirection(turn);
    if(my_tank.TankCheak(my_tank,my_tank.GetDirection()))
    switch(turn)
    {
        case UP:my_tank.SetY(my_tank.GetY()-1);break;
        case DOWN:my_tank.SetY(my_tank.GetY()+1);break;
        case LEFT:my_tank.SetX(my_tank.GetX()-1);break;
        case RIGHT:my_tank.SetX(my_tank.GetX()+1);break;
    }
    my_tank.PrintTank2(my_tank);
}

void Tank::MoveYourTank(int turn)
{
    your_tank.ClearTank(your_tank.GetX(),your_tank.GetY());
    your_tank.SetDirection(turn);
    if(your_tank.TankCheak(your_tank,your_tank.GetDirection()))
    switch(turn)
    {
        case UP:your_tank.SetY(your_tank.GetY()-1);break;
        case DOWN:your_tank.SetY(your_tank.GetY()+1);break;
        case LEFT:your_tank.SetX(your_tank.GetX()-1);break;
        case RIGHT:your_tank.SetX(your_tank.GetX()+1);break;
    }
    your_tank.PrintTank2(your_tank);
}

bool Tank::TankCheak(Tank tank,int diretion)
{
    switch(diretion)
    {
    case 1:
        if(map[tank.GetY()-2][tank.GetX()]==0&&map[tank.GetY()-2][tank.GetX()-1]==0&&map[tank.GetY()-2][tank.GetX()+1]==0)
            return true;
        else
            return false;
            break;
    case 2:
        if(map[tank.GetY()+2][tank.GetX()]==0&&map[tank.GetY()+2][tank.GetX()-1]==0&&map[tank.GetY()+2][tank.GetX()+1]==0)
            return true;
        else
            return false;
            break;
    case 3:
        if(map[tank.GetY()][tank.GetX()-2]==0&&map[tank.GetY()-1][tank.GetX()-2]==0&&map[tank.GetY()+1][tank.GetX()-2]==0)
            return true;
        else
            return false;
            break;
    case 4:
        if(map[tank.GetY()][tank.GetX()+2]==0&&map[tank.GetY()-1][tank.GetX()+2]==0&&map[tank.GetY()+1][tank.GetX()+2]==0)
            return true;
        else
            return false;
            break;
    default:
        return 0;
    }
}

void Tank::ClearTank(int x,int y)
{
    for (int i = 0;i<3;i++)
        for(int j = 0;j<3;j++)
    {
        map[y+j-1][x+i-1]=0;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN);
        GoToxy(2*x+j-2,y+i-1);
        cout<<"  ";
    }
}

void Tank::PrintTank(Tank tank)
{
    ColorChoose(tank.GetColor());
    const char *(*tankF)[4] = tank_figure[tank.GetModel()];
    for(int i=0;i<3;i++)
    {
        GoToxy((tank.GetX()-1)*2,tank.GetY()-1+i);
        cout<<tankF[i][tank.GetDirection()-1];
        for(int j=0;j<3;j++)
        {
            if(tank.GetMy()==1)
                map[tank.GetY()+j-1][tank.GetX()+i-1]=200;
            else
                map[tank.GetY()+j-1][tank.GetX()+i-1]=100+tank.GetNum();

        }
    }
}
void Tank::PrintTank2(Tank tank)
{
    ColorChoose(tank.GetColor());
    const char *(*tankF)[4] = tank_figure[1];
    for(int i=0;i<3;i++)
    {
        GoToxy((tank.GetX()-1)*2,tank.GetY()-1+i);
        cout<<tankF[i][tank.GetDirection()-1];
        for(int j=0;j<3;j++)
        {
            if(tank.GetMy()==1)
                map[tank.GetY()+j-1][tank.GetX()+i-1]=200;
            else
                map[tank.GetY()+j-1][tank.GetX()+i-1]=201;
        }
    }
}

void Tank::BuildAIBullet(Tank *tank)
{
    if(tank->GetCD()==15)
    {
        if(!(rand()%11))
        {
           tank->BuildBullet(*tank);
            tank->SetCD(0);
        }
    }
    else
        tank->SetCD(tank->GetCD()+1);
}
int main()
{
    int i;
    unsigned int interval[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
    srand(time(NULL));
    HideCursor();
    system("mode con cols=112 lines=44");
    GoToxy(40,15);
    ColorChoose(7);
    cout<<"请选择你的游戏模式"<<endl;
    GoToxy(40,16);
    cout<<"model 1  单人模式"<<endl;
    GoToxy(40,17);
    cout<<"model 2  双人模式"<<endl;
    GoToxy(40,18);
    cout<<"model 3  游戏介绍"<<endl;
    GoToxy(40,19);
    cout<<"model 4  退出游戏"<<endl;
    GoToxy(40,20);
    cout<<"输入游戏模式:";
    while(1)
    {
        cin>>s;
        if(s[0]=='1'||s[0]=='2'||s[0]=='3'||s[0]=='4')
            {
                model = s[0] - '0';
                break;
            }
        else
            {
                GoToxy(40,20);
                cout<<"输入不合理,重新输入:";
                cout<<"                                                   ";
                GoToxy(60,20);
            };
    }
    if(model==3)
    {
        Sleep(50);
        CleanMainScreen1();
        GoToxy(0,2);
        cout<<"游戏介绍:"<<endl;
        cout<<"1.坦克大战分为单人模式和双人模式"<<endl;
        cout<<"2.单人模式玩家通过击败所有敌方坦克方可过关"<<endl;
        cout<<"3.双人模式玩家通过击败五次敌方坦克或摧毁敌方阵地方可获胜"<<endl<<endl<<endl;
        cout<<"model 1  单人模式"<<endl;
        cout<<"model 2  双人模式"<<endl;
        cout<<"model 4  退出游戏"<<endl;
        cout<<"请再次选择进入的游戏模式:";
        while(1)
        {
            cin>>s;
            if(s[0]=='1'||s[0]=='2'||s[0]=='4')
            {
                model = s[0]-'0';
                break;
            }
            else
                {
                GoToxy(0,11);
                cout<<"输入不合理,重新输入:";
                GoToxy(20,11);
                cout<<"                 ";
                GoToxy(20,11);
                }
        }
    }
    if(model==1)
    {
    system("mode con cols=112 lines=44");
    Frame();
    Initialize();
    for(;;)
    {
        if(interval[0]++%speed==0)//speed越大，游戏速度越慢，但是21-speed越小；
        {
            GameCheak(); //游戏胜负检测
            BulletFly(bullet);
            for(i=0;i<=3;i++) //AI坦克移动循环
            {
                if(AI_tank[i].GetModel()==2 && interval[i+1]++%2==0) //2号类型的快坦克；
                      AI_tank[i].MoveAITank(&AI_tank[i]);
                if(AI_tank[i].GetModel()!=2 && interval[i+5]++%3==0) //非二号类型的坦克
                    AI_tank[i].MoveAITank(&AI_tank[i]);
            }
            for(i=0;i<=3;i++)                                   //建立AI坦克部分
                     if(AI_tank[i].GetAlive()==0&&AI_tank[i].GetRevive()<5&&interval[9]++%90==0)  //一个敌方坦克每局只有5条命
                {        //如果坦克不存活。计时,每次建立有间隔  1750 ms
                        AI_tank[i].BuildAITank(&position,&AI_tank[i]);//建立AI坦克（复活）
                        break; //每次循环只建立一个坦克
                }
            for(i=0;i<=3;i++)
                if(AI_tank[i].GetAlive())
                    AI_tank[i].BuildAIBullet(&AI_tank[i]); //AIshoot自带int自增计数CD,不使用main中的CD interval
            if(my_tank.GetAlive()&&interval[10]++%2==0 )
                 keyboard();
            if(my_tank.GetAlive()==0&&interval[11]++%30==0&&my_tank.GetRevive()<MAX_LIFE)
                 my_tank.BuildMyTank(&my_tank);
        }
        Sleep(5);
    }
    }
    if(model==2)
    {
    system("mode con cols=112 lines=44");
    Frame();
    Initialize2();
    for(;;)
    {
        if(interval[0]++%speed==0)//speed越大，游戏速度越慢，但是21-speed越小；
        {
            GameCheak2(); //游戏胜负检测
            BulletFly(bullet);
            if(my_tank.GetAlive()&&interval[10]++%2==0)
                 keyboard ();
            if(my_tank.GetAlive()==0&&interval[11]++%30==0&&my_tank.GetRevive()<MAX_LIFE)
                 my_tank.BuildMyTank(&my_tank);
            if(your_tank.GetAlive()&&interval[10]++%2==0)
                 keyboard();
            if(your_tank.GetAlive()==0&&interval[11]++%30==0&&your_tank.GetRevive()<MAX_LIFE)
                 your_tank.BuildYourTank(&your_tank);
        }
        Sleep(7);
    }
    }
    if(model==4)
    {
        Sleep(5000);
        exit(0);
    }
    cout<<endl;
    return 0;
}
void HideCursor()//隐藏光标
{//CONSOLE_CURSOR_INFO结构体包含控制台光标的信息,DWORD dwSize光标百分比厚度（1~100）和BOOL bVisible光标是否可见
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info); //SetConsoleCursorInfo用来设置指定的控制台光标的大小和可见性。
}

void GoToxy(int x,int y)
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    HANDLE  str=GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出句柄
    SetConsoleCursorPosition(str,coord);//
}

void keyboard()
{
    int count=0;
    if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
        exit(0);//退出
    else if(GetAsyncKeyState(VK_RETURN)&0x8000)
        Stop();//暂停
    else if(my_tank.GetAlive()&&GetAsyncKeyState(VK_UP)&0x8000)
        my_tank.MoveMyTank(UP);
    else if(my_tank.GetAlive()&&GetAsyncKeyState(VK_DOWN)&0x8000)
        my_tank.MoveMyTank(DOWN);
    else if(my_tank.GetAlive()&&GetAsyncKeyState(VK_LEFT)&0x8000)
        my_tank.MoveMyTank(LEFT);
    else if(my_tank.GetAlive()&&GetAsyncKeyState(VK_RIGHT)&0x8000)
        my_tank.MoveMyTank(RIGHT);
    else if(your_tank.GetAlive()&&model==2&&GetAsyncKeyState('W')&0x8000)
        your_tank.MoveYourTank(UP);
    else if(your_tank.GetAlive()&&model==2&&GetAsyncKeyState('S')&0x8000)
        your_tank.MoveYourTank(DOWN);
    else if(your_tank.GetAlive()&&model==2&&GetAsyncKeyState('A')&0x8000)
        your_tank.MoveYourTank(LEFT);
    else if(your_tank.GetAlive()&&model==2&&GetAsyncKeyState('D')&0x8000)
        your_tank.MoveYourTank(RIGHT);
    else if(count++%7==0)
    {
       if(speed>1&&GetAsyncKeyState('0')&0x8000)//加速度
    {
        if(model==1)
        {
        speed = speed-1;
        GoToxy(100,10);
        cout<<"      ";
        GoToxy(102,10);
        ColorChoose(7);
        cout<<21-speed;
        }
        else if(model==2)
        {
            ColorChoose(7);
            speed = speed - 1;
            GoToxy(102,12);
            cout<<"       ";
            GoToxy(102,12);
            cout<<21 - speed;
        }

    }
    else if(speed<20&&GetAsyncKeyState('9')&0x8000)//减速度
    {
        if(model==1)
        {
        speed = speed + 1;
        GoToxy(100,10);
        cout<<"      ";
        ColorChoose(7);
        GoToxy(102,10);
        cout<<21-speed;
        }
        else if(model==2)
        {
            ColorChoose(7);
            speed = speed + 1;
            GoToxy(102,12);
            cout<<"      ";
            GoToxy(102,12);
            cout<<21-speed;
        }
    }
    }
    if(GetAsyncKeyState('M')&0x8000)
    {
             if(my_tank.GetCD()==2)
             {
                 my_tank.BuildBullet(my_tank);
                 if(model==2)
                 {
                 bullets1++;
                 GoToxy(102,20);
                 ColorChoose(7);
                 cout<<bullets1;
                 score = score - 10;
                 GoToxy(102,4);
                 cout<<"      ";
                 GoToxy(102,4);
                 cout<<score;
                 }
                 my_tank.SetCD(0);
             }
             else
                 my_tank.SetCD(my_tank.GetCD()+1);
    }

    if(model==2)
    if(GetAsyncKeyState('F')&0x8000)
    {
             if(your_tank.GetCD()==2)
             {
                 your_tank.BuildBullet(your_tank);
                 bullets2++;
                 GoToxy(102,21);
                 ColorChoose(7);
                 cout<<bullets2;
                 score2 = score2 - 10;
                 GoToxy(102,8);
                 cout<<"      ";
                 GoToxy(102,8);
                 cout<<score2;
                 your_tank.SetCD(0);
             }
             else
                 your_tank.SetCD(your_tank.GetCD()+1);
    }
}

void ColorChoose(int color)
{
    switch(color)
    {
    case 1://天蓝
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
        break;
    case 2://绿色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
        break;
    case 3://黄色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN);
        break;
    case 4://橙色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
        break;
    case 5://粉红色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE|FOREGROUND_RED);
        break;
    case 6://白色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
        break;
    case 7://深蓝色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_BLUE);
        break;

    }
}

void Stop()//暂停
{
    int timing = 0;//延时
    while(1)//循环
    {
        if(timing++%30==0)
        {
            ColorChoose(7);
            if(model==1)
            {
            GoToxy(100,12);
            cout<<"游戏暂停";
            }
            else if(model==2)
            {
                GoToxy(100,14);
                cout<<"游戏暂停";
            }
            GoToxy(88,17);
            cout<<"按Shift见回到游戏";
            GoToxy(88,18);
            cout<<"或按Esc键退出游戏";
        }
        if(GetAsyncKeyState(VK_SHIFT)&0x8000)
        {
            if(model==1)
            {
            GoToxy(100,12);
            ColorChoose(7);
            cout<<"正在进行";
            GoToxy(88,17);
            cout<<"                     ";
            GoToxy(88,18);
            cout<<"                     ";
            }
            if(model==2)
            {
            GoToxy(100,14);
            ColorChoose(7);
            cout<<"正在进行";
            GoToxy(88,17);
            cout<<"                     ";
            GoToxy(88,18);
            cout<<"                     ";
            }
            break;
        }
        else if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
        exit(0);
    }
}

void CleanMainScreen1()
{
    for(int i=1;i<40;i++)
    {
        GoToxy(2,i);
        cout<<"                                                                              ";
    }
}

void Frame()//打印游戏框架
{
    ColorChoose(7);
    cout<<"  ▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁  ";
    cout<<"  ▁▁▁▁▁▁▁▁▁▁▁▁▁ "<<endl;
    for(int i=0;i<14;i++)
    {
       cout<<"▕                                                                              ▏";
        cout<<"▕                         ▕"<<endl;
    }
    cout<<"▕                                                                              ▏";
    cout<<"▕▁▁▁▁▁▁▁▁▁▁▁▁▁1"<<endl;
    for(int i=0;i<24;i++)
    {
        cout<<"▕                                                                              ▏";
        cout<<"▕                         ▕"<<endl;
    }
    cout<<"  ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔  ";
    cout<<"  ▔▔▔▔▔▔▔▔▔▔▔▔▔"<<endl;
    if(model==1)
       SideScreen ();
    if(model==2)
        SideScreen2();
}

void SideScreen()//副屏幕游戏信息打印，动态打印，和主屏幕分开是为了更好的操作
{
    GoToxy(93,2);
    ColorChoose(5);
    cout<<"第    关";
    GoToxy(86,4);
    cout<<"我的分数:";
    GoToxy(86,6);
    cout<<"坦克生命:";
    GoToxy(86,8);
    cout<<"剩余敌方坦克:";
    GoToxy(86,10);
    cout<<"当前游戏速度:";
    GoToxy(86,12);
    cout<<"当前游戏状态:";
    GoToxy(94,24);
    ColorChoose(7);
    cout<<"小提示:";
    GoToxy(86,27);
    ColorChoose(5);
    cout<<"M 键射击";
    GoToxy(86,29);
    cout<<"0 9 调整游戏速度";
    GoToxy(86,31);
    cout<<"Enter键暂停游戏";
    GoToxy(86,33);
    cout<<"Esc键退出游戏";
    //cout<<"游戏速度范围1~20";
    GoToxy(86,35);
    cout<<"方向键  ←↑→↓";
    //GoToxy(86,37);
}

void SideScreen2()//副屏幕游戏信息打印，动态打印，和主屏幕分开是为了更好的操作
{
    GoToxy(93,2);
    ColorChoose(5);
    cout<<"第    关";
    GoToxy(86,4);
    cout<<"玩家一分数:";
    GoToxy(86,6);
    cout<<"玩家一生命:";
    GoToxy(86,8);
    cout<<"玩家二分数:";
    GoToxy(86,10);
    cout<<"玩家二生命:";
    GoToxy(86,12);
    cout<<"游戏速度:";
    GoToxy(86,14);
    cout<<"游戏状态:";
    GoToxy(86,20);
    cout<<"玩家一射击次数:";
    GoToxy(86,21);
    cout<<"玩家二射击次数:";
    GoToxy(94,23);
    ColorChoose(7);
    cout<<"小提示:";
    ColorChoose(5);
    GoToxy(86,25);
    cout<<"玩家一 M 键射击";
    GoToxy(86,27);
    cout<<"玩家二 F 键射击";
    GoToxy(86,29);
    cout<<"0 9 调整游戏速度";
    GoToxy(86,31);
    cout<<"Enter键暂停游戏";
    GoToxy(86,33);
    cout<<"Esc键退出游戏";
    GoToxy(86,35);
    cout<<"玩家一方向键  ←↑→↓";
    GoToxy(86,37);
    cout<<"玩家二方向键  A W D S";
}

void PrintMap()//打印地图多了背景颜色
{
    for(int j=0;j<41;j++)
        for(int i=0;i<41;i++)
        if(map[i][j]==6)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN
                                |FOREGROUND_RED|FOREGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_BLUE);
        GoToxy(2*j,i);
        cout<<"■";
    }
    else if(map[i][j]==1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|BACKGROUND_GREEN|BACKGROUND_RED);
        GoToxy(2*j,i);
        cout<<"▓";
    }
    else if(map[i][j]==2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN
                                |FOREGROUND_RED|BACKGROUND_GREEN|BACKGROUND_RED);
        GoToxy(2*j,i);
        cout<<"▓";
    }
    else if(map[i][j]==5)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|BACKGROUND_BLUE|FOREGROUND_BLUE|FOREGROUND_GREEN);
        GoToxy(2*j,i);
        cout<<"～";
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_GREEN);
    GoToxy(38,37);
    cout<<"◢█◣";
    GoToxy(38,38);
    cout<<"███";
    GoToxy(38,39);
    cout<<"◢█◣";
    if(model==2)//模式二的情况下
    {
        GoToxy(38,1);
        cout<<"◢█◣";
        GoToxy(38,2);
        cout<<"███";
        GoToxy(38,3);
        cout<<"◢█◣";
    }
}

void GameOver(bool home)
{
    int timing = 0;
    while(1)
    {
        if(timing++%30==0)
        {
            ColorChoose(7);
            if(home)
            {
                GoToxy(37,19);
                cout<<"家被毁";
            }
            GoToxy(37,20);
            cout<<"游戏结束";
            GoToxy(100,12);
            cout<<"游戏结束";
            GoToxy(88,17);
            cout<<"请按Enter键重新开始";
            GoToxy(88,18);
            cout<<"或按Esc键退出游戏";
        }
        if(GetAsyncKeyState(VK_RETURN)&0x8000)
        {
            GoToxy(88,17);
            cout<<"                  ";
            GoToxy(88,18);
            cout<<"                  ";
            CleanMainScreen1();
            Initialize();
            break;
        }
        else if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
            exit(0);
        Sleep(20);
    }
}

void GameOver2(int home)
{
    if(home==3)
    {
                ColorChoose(7);
                score = score - 500;
                score2 = score2 + 500;
                GoToxy(102,4);
                cout<<"       ";
                GoToxy(102,4);
                cout<<score;
                GoToxy(102,8);
                cout<<"       ";
                GoToxy(102,8);
                cout<<score2;
    }
    else if(home==4)
    {
                ColorChoose(7);
                score2 = score2 - 500;
                score = score + 500;
                GoToxy(102,4);
                cout<<"       ";
                GoToxy(102,4);
                cout<<score;
                GoToxy(102,8);
                cout<<"       ";
                GoToxy(102,8);
                cout<<score2;
    }
    int timing = 0;
    while(1)
    {
        if(timing++%30==0)
        {
            ColorChoose(7);
            if(home==3)
            {
                GoToxy(32,19);
                cout<<"                   ";
                GoToxy(32,20);
                cout<<"                   ";
                GoToxy(37,19);
                cout<<"玩家一家被毁";
                GoToxy(37,20);
                cout<<"此关卡玩家二获胜";

            }
            else if(home==4)
            {
                GoToxy(32,19);
                cout<<"                   ";
                GoToxy(32,20);
                cout<<"                   ";
                GoToxy(37,19);
                cout<<"玩家二家被毁";
                GoToxy(37,20);
                cout<<"此关卡玩家一获胜";
            }
            else if(home==1)
            {
                GoToxy(32,19);
                cout<<"                   ";
                GoToxy(32,20);
                cout<<"                   ";
                GoToxy(37,20);
                cout<<"此关卡玩家二获胜";
            }
            else if(home==2)
            {
                GoToxy(32,19);
                cout<<"                   ";
                GoToxy(32,20);
                cout<<"                   ";
                GoToxy(37,20);
                cout<<"此关卡玩家一获胜";
            }
            GoToxy(100,14);
            cout<<"游戏结束";
        }
            GoToxy(88,17);
            cout<<"请按Enter键继续";
            GoToxy(88,18);
            cout<<"或按Esc键退出游戏";
        if(GetAsyncKeyState(VK_RETURN)&0x8000)
        {
            GoToxy(88,17);
            cout<<"                  ";
            GoToxy(88,18);
            cout<<"                  ";
            CleanMainScreen1();
            Nextlevel2();
            break;
        }
        else if(GetAsyncKeyState(VK_ESCAPE)&0x8000)
            exit(0);
        Sleep(20);
    }
}

void Nextlevel()
{
    int timing = 0;
    level++;
    if(level<=MAX_LEVEL)
        while(1)
    {
        if(timing++%10==0)
        {
            ColorChoose(7);
            GoToxy(37,20);
            cout<<"恭喜过关";
            GoToxy(100,12);
            cout<<"等下一关";
            GoToxy(88,17);
            cout<<"请按Enter键继续";
            GoToxy(88,18);
            cout<<"或者按Esc键退出游戏";
        }
        if(GetAsyncKeyState(VK_RETURN)&0x8000)
        {
            GoToxy(87,17);
            cout<<"                    ";
            GoToxy(88,18);
            cout<<"                    ";
            CleanMainScreen1();
            Initialize();
            break;
        }
           else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000)
               exit(0);
           Sleep(20);
       }
   else//level>4 通关
       while(1)
      {
           if(timing++%5==0)
        {
            ColorChoose(7);
            GoToxy(33,20);
            cout<<"恭喜通过全部关卡";
            GoToxy(100,12);
            cout<<"已通全关";
            GoToxy(88,16);
            cout<<"恭喜通过全部关卡";
            GoToxy(88,19);
            cout<<"按Esc键退出游戏";
            }
           if(GetAsyncKeyState( 0x1B )& 0x8000)
               exit(0);
           Sleep(10);
    }
}


void Nextlevel2()
{
    int timing = 0;
    level++;
    if(level<=MAX_LEVEL)
        while(1)
    {
        if(timing++%10==0)
        {
            ColorChoose(7);
            GoToxy(100,14);
            cout<<"等下一关";
            GoToxy(87,17);
            cout<<"请按Enter键继续";
            GoToxy(88,18);
            cout<<"或者按Esc键退出游戏!";
        }
        if(GetAsyncKeyState(VK_RETURN)&0x8000)
        {
            GoToxy(87,17);
            cout<<"                     ";
            GoToxy(88,18);
            cout<<"                     ";
            CleanMainScreen1();
            Initialize2();
            break;
        }
           else if(GetAsyncKeyState(VK_ESCAPE)& 0x8000)
               exit(0);
           Sleep(20);
       }
   else//level>4 通关
   {
    CleanMainScreen1();
       while(1)
      {
           if(timing++%5==0)
        {
            if(score2>score)
            {
                ColorChoose(7);
                GoToxy(33,18);
                cout<<"最终玩家二获胜";
            }
            else if(score2<score)
            {
                ColorChoose(7);
                GoToxy(33,18);
                cout<<"最终玩家一获胜";
            }
            else
            {
                ColorChoose(7);
                GoToxy(33,18);
                cout<<"平局";
            }
            ColorChoose(7);
            GoToxy(33,20);
            cout<<"结束全部关卡";
            GoToxy(88,17);
            cout<<"恭喜通过全部关卡";
            GoToxy(88,18);
            cout<<"按Esc键退出游戏";
            }
           if(GetAsyncKeyState( 0x1B )& 0x8000)
               exit(0);
           Sleep(10);
    }
   }
}

void GameCheak()
{
    if(remain_enemy<=0 &&!AI_tank[0].GetAlive()&&!AI_tank[1].GetAlive()&&!AI_tank[2].GetAlive()&&!AI_tank[3].GetAlive())
        Nextlevel();   //进入下一关
    if(my_tank.GetRevive()>=MAX_LIFE)//我的生命值(复活次数)全部用完 MAX_LIFE
        GameOver(0);  //游戏结束，传入0代表我的复活次数用光(生命值为0)。游戏结束有两种判断，另一种是老家被毁
}

void GameCheak2()
{
    if(my_tank.GetRevive()>=MAX_LIFE)
    {
         GameOver2(1);
    }
    if(your_tank.GetRevive()>=MAX_LIFE2)
    {
        GameOver2(2);
    }
}
void Initialize()      //初始化
{
    remain_enemy=20;
    my_tank.SetRevive(0);//我的坦克已经复活的次数为0
    position=0;
    bul_num=0;
    GetMap();
    my_tank.BuildMyTank(&my_tank);
    for(int i=0;i<20;i++) //子弹初始化
    {
      bullet[i].SetExist(0);
      bullet[i].SetInitial(0);
    }
        for(int i=0;i<=3;i++)         //AI坦克初始化
        {
            AI_tank [i].SetRevive(0);
            AI_tank [i].SetAlive(0);  //初始化坦克全是不存活的，BuildAITank()会建立重新建立不存活的坦克
            AI_tank [i].SetStop(0);
            AI_tank [i].SetNum(i);
            AI_tank [i].SetMy(0);
            AI_tank [i].SetCD(4);
        }
        ColorChoose(7);
        GoToxy(97,2);
        cout<<level;
        GoToxy(102,4);
        cout<<score;
        GoToxy(102,6);
        cout<<MAX_LIFE-my_tank.GetRevive();
        GoToxy(102,8);
        cout<<remain_enemy;
        GoToxy(102,10);
        cout<<21-speed;
        GoToxy(100,12);
        cout<<"正在游戏";
}
void Initialize2()//双人模式初始化
{
    my_tank.SetRevive(0);//我的坦克已经复活的次数为0
    your_tank.SetRevive(0);//你的坦克已复活的次数为0
    position=0;
    bul_num=0;
    GetMap2();
    my_tank.BuildMyTank(&my_tank);
    your_tank.BuildYourTank(&your_tank);
    for(int i=0;i<BULLET_NUM;i++) //子弹初始化
    {
      bullet[i].SetExist(0);
      bullet[i].SetInitial(0);
    }
        ColorChoose(7);
        GoToxy(97,2);
        cout<<level;
        GoToxy(102,4);
        cout<<score;
        GoToxy(102,6);
        cout<<MAX_LIFE-my_tank.GetRevive();
        GoToxy(102,8);
        cout<<score2;
        GoToxy(102,10);
        cout<<MAX_LIFE-your_tank.GetRevive();
        GoToxy(102,12);
        cout<<21-speed;
        GoToxy(100,14);
        cout<<"正在游戏";
        GoToxy(102,20);
        cout<<bullets1;
        GoToxy(102,21);
        cout<<bullets2;
}
void GetMap()//地图存放函数
{//map里的值: 个位数的值为地图方块部分，百位数的值为坦克
    int i ,j;//map里的值: 0为可通过陆地，1为红砖，2待定，5为水，100为敌方坦克，200为我的坦克,201为你的坦克
    int Map[4][41][41]=
    {
        {
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },
{
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,4},
            {4,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,4},
            {4,6,6,6,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,6,6,6,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },


        {
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,2,2,2,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,2,2,2,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,2,2,2,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,6,6,6,0,0,0,4},
            {4,1,1,1,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,6,6,6,0,0,0,4},
            {4,1,1,1,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,6,6,6,0,0,0,4},
            {4,1,1,1,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,1,1,1,6,6,6,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,1,1,1,6,6,6,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,1,1,1,6,6,6,6,6,6,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,6,6,6,1,1,1,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,6,6,6,1,1,1,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,6,6,6,1,1,1,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,1,1,1,6,6,6,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,1,1,1,6,6,6,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,1,1,1,6,6,6,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,1,1,1,6,6,6,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,1,1,1,6,6,6,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,1,1,1,6,6,6,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,1,1,1,6,6,6,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,1,1,1,6,6,6,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,0,0,0,2,2,2,1,1,1,6,6,6,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,6,6,6,6,6,6,6,6,6,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,6,6,6,6,6,6,6,6,6,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,6,6,6,6,6,6,6,6,6,2,2,2,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,4},
            {4,6,6,6,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,0,0,0,0,0,0,4},
            {4,6,6,6,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,0,0,0,0,0,0,4},
            {4,6,6,6,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,0,0,0,0,0,0,4},
            {4,6,6,6,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,1,1,1,1,1,1,0,0,0,4},
            {4,6,6,6,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,1,1,1,1,1,1,0,0,0,4},
            {4,6,6,6,0,0,0,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,1,1,1,1,1,1,0,0,0,4},
            {4,2,2,2,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,4},
            {4,2,2,2,6,6,6,6,6,6,6,6,6,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,4},
            {4,2,2,2,6,6,6,6,6,6,6,6,6,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,6,6,6,6,6,6,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },



        {
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,6,6,6,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,1,1,1,6,6,6,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,1,1,1,6,6,6,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,6,6,6,0,0,0,1,1,1,5,5,5,0,0,0,6,6,6,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,5,5,5,0,0,0,6,6,6,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,5,5,5,0,0,0,6,6,6,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,5,5,5,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,5,5,5,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,1,1,1,5,5,5,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,1,1,1,0,0,0,1,1,1,5,5,5,5,5,5,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,1,1,1,4},
            {4,1,1,1,0,0,0,1,1,1,5,5,5,5,5,5,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,1,1,1,4},
            {4,1,1,1,0,0,0,1,1,1,5,5,5,5,5,5,0,0,0,5,5,5,5,5,5,5,5,5,5,5,5,0,0,0,0,0,0,1,1,1,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,6,6,6,6,6,6,4},
            {4,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,6,6,6,0,0,0,1,1,1,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,6,6,6,0,0,0,1,1,1,0,0,0,5,5,5,0,0,0,1,1,1,1,1,1,4},
            {4,1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,6,6,6,0,0,0,1,1,1,0,0,0,5,5,5,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,5,5,5,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },
    };
        for(i=0;i<41;i++)
            for(j=0;j<41;j++)
                    map[i][j]=Map[level-1][i][j];
    PrintMap();         //打印地图
}
void GetMap2()//地图存放函数
{//map里的值: 个位数的值为地图方块部分，百位数的值为坦克
    int i ,j;//map里的值: 0为可通过陆地，1为红砖，2待定，5为水，6为白砖，100为敌方坦克，200为我的坦克,201为你的坦克
    int Map2[4][41][41]=
    {
        {
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },
{
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,6,6,6,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,6,6,6,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,6,6,6,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,1,1,1,0,0,0,1,1,1,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,1,1,1,0,0,0,1,1,1,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,1,1,1,0,0,0,1,1,1,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,4},
            {4,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,4},
            {4,6,6,6,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,6,6,6,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,6,6,6,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },


        {
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,6,6,6,6,6,6,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,6,6,6,6,6,6,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,0,0,0,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,2,2,2,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,4},
            {4,0,0,0,2,2,2,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,4},
            {4,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,4},
            {4,0,0,0,0,0,2,2,2,2,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,4},
            {4,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },



        {
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,8,8,8,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
            {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}
        },
    };
        for(i=0;i<41;i++)
            for(j=0;j<41;j++)
                    map[i][j]=Map2[level-1][i][j];
    PrintMap();         //打印地图
}
