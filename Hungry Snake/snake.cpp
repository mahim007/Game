#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<windows.h>
#include<conio.h>
using namespace std;

#define ll long long int
#define ROW 35
#define COL 50

char grid[ROW+5][COL+5];
deque<pair<ll,ll> >Flow;


ll start=0;
ll point=0;
ll prev_point=1;
ll dir=1;
ll lvl=50;

struct snake{
    ll snake_size=2;
    ll snake_pos_x=25;
    ll snake_pos_y=25;
    ll is_alive=1;


    void init_snake(){
        Flow.push_back({snake_pos_x,snake_pos_y-1});
        Flow.push_back({snake_pos_x,snake_pos_y});
    }

    void draw_snake(){
        ll sz=Flow.size();
        sz--;

        for(ll i=sz;i>=0;i--){
            grid[Flow[i].first][Flow[i].second]='*';
        }

        if(dir==1){
            grid[Flow[sz].first][Flow[sz].second]='>';
        }
        else if(dir==2){
            grid[Flow[sz].first][Flow[sz].second]='<';
        }
        else if(dir==3){
            grid[Flow[sz].first][Flow[sz].second]='^';
        }
        else if(dir==4){
            grid[Flow[sz].first][Flow[sz].second]='v';
        }

    }

    void move_snake(){
        if(dir==1){
            snake_pos_y++;
            Flow.push_back({snake_pos_x,snake_pos_y});
            pair<ll,ll>P=Flow.front();
            grid[P.first][P.second]=' ';
            Flow.pop_front();
        }
        else if(dir==2){
            snake_pos_y--;
            Flow.push_back({snake_pos_x,snake_pos_y});
            pair<ll,ll>P=Flow.front();
            grid[P.first][P.second]=' ';
            Flow.pop_front();
        }
        else if(dir==3){
            snake_pos_x--;
            Flow.push_back({snake_pos_x,snake_pos_y});
            pair<ll,ll>P=Flow.front();
            grid[P.first][P.second]=' ';
            Flow.pop_front();
        }
        else if(dir==4){
            snake_pos_x++;
            Flow.push_back({snake_pos_x,snake_pos_y});
            pair<ll,ll>P=Flow.front();
            grid[P.first][P.second]=' ';
            Flow.pop_front();
        }
    }

    void snake_move_right(){
        if(dir==1){
            dir=1;
        }
        else if(dir==3){
            dir=1;
        }
        else if(dir==4){
            dir=1;
        }
    }

    void snake_move_left(){
        if(dir==2){
            dir=2;
        }
        else if(dir==3){
            dir=2;
        }
        else if(dir==4){
            dir=2;
        }
    }

    void snake_move_up(){
        if(dir==3){
            dir=3;
        }
        else if(dir==1){
            dir=3;
        }
        else if(dir==2){
            dir=3;
        }
    }

    void snake_move_down(){
        if(dir==4){
            dir=4;
        }
        else if(dir==1){
            dir=4;
        }
        else if(dir==2){
            dir=4;
        }
    }

};

struct fruit{
    ll fruit_no=0;
    ll fruit_pos_x;
    ll fruit_pos_y;

    void generate_food(){
        fruit_no++;
        while(1){
            fruit_pos_x=2+(rand()%(ROW));
            fruit_pos_y=2+(rand()%(COL));
            pair<ll,ll>P;
            P.first=fruit_pos_x;
            P.second=fruit_pos_y;

            if(P.first>=ROW || P.second>=COL) continue;

            deque<pair<ll,ll> >::iterator it;
            it=find(Flow.begin(),Flow.end(),P);
            if(it==Flow.end()){
                break;
            }
        }

        grid[fruit_pos_x][fruit_pos_y]='X';

    }

    int fruit_eaten(){
        pair<ll,ll>P=Flow.front();
//        cout<<"lej x="<<P.first<<" y="<<P.second<<"\n";
//        cout<<"fruit pos x="<<fruit_pos_x<<" y="<<fruit_pos_y<<"\n";
        if(P.first==fruit_pos_x && P.second==fruit_pos_y){
            Flow.push_front({fruit_pos_x,fruit_pos_y});
            point=Flow.size();
            return 1;
        }
        return 0;
    }
};

struct border{

    void fill_border(){
        for(ll i=1;i<=COL;i++){
            grid[1][i]='#';
        }

        for(ll i=2;i<ROW;i++){
            grid[i][1]='#';

            for(ll j=2;j<COL;j++) grid[i][j]=' ';
            grid[i][COL]='#';
        }
        for(ll i=1;i<=COL;i++) grid[ROW][i]='#';
    }

    void draw_border(){
        for(ll i=1;i<=COL;i++) printf("%c",grid[1][i]);
        printf("\n");
        for(ll i=2;i<ROW;i++){
            printf("%c",grid[i][1]);
            for(ll j=2;j<COL;j++) printf("%c",grid[i][j]);
            printf("%c\n",grid[i][COL]);
        }
        for(ll i=1;i<=COL;i++) printf("%c",grid[ROW][i]);
    }
};




border Border;
snake Snake;
fruit Fruit;

struct game{
    int game_over(){
        ll sz=Flow.size();
        sz--;
        if(grid[Flow[sz].first][Flow[sz].second]=='#'){
            return 1;
        }
    }

    void game_level_up(){
        lvl-=5;
        if(lvl<0) lvl=0;

        prev_point=point;

        system("CLS");
        cout<<"LEVEL UP!!!\n";
        Sleep(2000);
    }
};

game Game;

int main(){
    //cout<<"mahim\n";
    srand(time(NULL));
    Border.fill_border();
    Snake.init_snake();
    Snake.draw_snake();
    Fruit.generate_food();
    Border.draw_border();

    while(1){
        if(point%10==0 && point>prev_point){
            Game.game_level_up();

        }
        Snake.move_snake();
        if(Game.game_over()==1){
            system("CLS");
            cout<<"Game Over\n";
            cout<<"Your point="<<point<<"\n";
            Sleep(2000);
            break;
        }
        system("CLS");
        //Border.fill_border();

        if(Fruit.fruit_eaten()==1){
            Fruit.generate_food();
        }
        Snake.draw_snake();

        Border.draw_border();
        Sleep(lvl);

        if(kbhit()){
            char ch;
            ch=getch();
            if((int)ch=='8'){
                Snake.snake_move_up();
            }
            else if((int)ch=='5'){
                Snake.snake_move_down();
            }
            else if((int)ch=='4'){
                Snake.snake_move_left();
            }
            else if((int)ch=='6'){
                Snake.snake_move_right();
            }
        }

    }

// mahim
}
