#include <iostream>
#include"game.h"
using namespace std;

struct ToaDo{
   int x,y;
};
class DoiTuong{
   public:

       SDL_Texture* nv;
       SDL_Rect khung_nv;
       SDL_Renderer* renderer;

       void KhoiTao(string s, SDL_Renderer* _renderer) {
           renderer = _renderer;
           nv= loadTexture(s, _renderer);

           SDL_QueryTexture(nv,NULL,NULL,&khung_nv.w,&khung_nv.h);
       }
       void SetKichThuoc(float denta_h, float denta_w) {

           khung_nv.h /= denta_h;
           khung_nv.w /= denta_w;
       }

       void SetToaDo(int x, int y) {

       khung_nv.x=x;
       khung_nv.y=y;
       }
       void HienThi(){

           SDL_RenderCopy(renderer,nv,NULL, &khung_nv);
       }

};

/*
void Menu(string bg_game, SDL_Renderer* renderer) {
    ///menu : play, resume, pause, setting
SDL_Texture* back_ground = loadTexture(bg_game, renderer);
SDL_RenderCopy(renderer, back_ground, NULL,NULL);

SDL_Event g_event;
DoiTuong play[4];
                play[0].KhoiTao("./pictures//backgroundmenu.png",renderer);
                play[0].SetToaDo(30,-130);
                play[0].HienThi();
                SDL_RenderPresent(renderer);
    cout << play[0].khung_nv.y;
int dem =0;
int frame =0;}
while(true) {
        frame++;
    if(SDL_PollEvent(&g_event)) {
        switch(g_event.type){
            case SDL_MOUSEBUTTONDOWN:{
                cout << g_event.button.x <<", "<<g_event.button.y<< endl;
                break;
            }
            case SDL_KEYDOWN: {
                 dem++;
            if(dem ==1) {
               while(play[0].khung_nv.y >-350) {
                play[0].khung_nv.y--;
                SDL_RenderCopy(renderer, back_ground, NULL,NULL);
                play[0].HienThi();
               }
               //play[0].khung_nv.x = play[0].khung_nv.x;
            }
            }
        }
    }
    SDL_RenderPresent(renderer);
}
}
*/
class Bullet : public DoiTuong{
public:

      int type; //0 dan xanh, 1 dan do, 2 sam set
      int dame;
      int speed;// dan xanh bay nhanh hon

void KhoiTao(SDL_Renderer* _renderer, int stype){

            type=stype;
            dame =50;
            speed=25;
            string s;
            switch(type) {
        case 0:
            s = "./pictures//dan1.png";
            dame+=30;
            break;
        case 1:
            speed+= 4;
            s = "./pictures//dan2.png";
            break;
            }
         DoiTuong:: KhoiTao(s,_renderer);
      }


void AddXY(int dentaX, int dentaY) {

     khung_nv.x += dentaX*speed;
     khung_nv.y += dentaY*speed;
     speed-=1/2;
     }

};



class NhanVat : public DoiTuong{
public:

      int hp_max, hp;
      int mp_max,mp;
      int speed;
      int dame;
      int animation=0;
      vector<Bullet> B;
void KhoiTao(string s, SDL_Renderer* _renderer,int shp,
                   int smp, int sspeed, int sdame, int sanimation) {
                       DoiTuong::KhoiTao(s,_renderer);
                       hp_max= shp; hp = hp_max;
                       mp_max=smp; mp= mp_max;
                       speed= sspeed;
                       dame=sdame;
                       animation=sanimation;

                   }
void Initial_Bullet(int type){
     ToaDo td_Bullet;
     td_Bullet.x = khung_nv.x +khung_nv.w/2 -17;
     td_Bullet.y =khung_nv.y;
     Bullet b;
     b.KhoiTao(renderer,type);
     b.SetToaDo(td_Bullet.x,td_Bullet.y);
     B.push_back(b);
     }

void HienThi() {
 if(hp==0) {
    return;
 }
     DoiTuong ::HienThi();
     for(int i=0;i<B.size();i++) {
        B[i].AddXY(0,-1);
       if(B[i].khung_nv.y <=0) {
        B.erase(B.begin()+i,B.begin()+i+1);
        i--;
        continue;
       }
        B[i].HienThi();

     }
     }

};

class Enemy : public DoiTuong{
public:
      int hp_max, hp;
      int speed;
      int dame;
      int animation=0;

      vector<Bullet> B;

void KhoiTao(string s, SDL_Renderer* _renderer,int shp,
                    int sspeed, int sdame, int sanimation) {
                       DoiTuong ::KhoiTao(s,_renderer);
                       hp_max= shp; hp = hp_max;
                       speed= sspeed;
                       dame=sdame;
                       animation=sanimation;
                       // gan lai
                   }

void Run() {
       string link_anh[] ={"./pictures//c1.png",
                           "./pictures//c3.png","./pictures//c5.png",
                             "./pictures//c7.png","./pictures//c9.png"
                             ,"./pictures//c11.png","./pictures//c13.png"
                             ,"./pictures//c15.png","./pictures//c17.png"
                             ,"./pictures//c19.png","./pictures//c21.png",
                             "./pictures//c19.png",
                           "./pictures//c17.png","./pictures//c16.png",
                             "./pictures//c15.png","./pictures//c13.png",
                             "./pictures//c11.png","./pictures//c9.png",
                             "./pictures//c7.png","./pictures//c5.png"
                             ,"./pictures//c3.png","./pictures//c1.png"};
        nv= loadTexture(link_anh[animation],renderer);
        animation++;
        if(animation ==21) {
            animation=0;
        }
   }

void Motion(int &X, int &Y) {
   if(khung_nv.x > SCREEN_WIDTH || khung_nv.y < SCREEN_HEIGHT) {
        while(khung_nv.x >0){
    khung_nv.x--;}
   }
    return;
   }

void Initial_Bullet(int type){
     ToaDo td_Bullet;
     td_Bullet.x = khung_nv.x +khung_nv.w/2 -17;
     td_Bullet.y =khung_nv.y;
     Bullet b;
     b.KhoiTao(renderer,type);
     b.SetToaDo(td_Bullet.x,td_Bullet.y);
     B.push_back(b);
     }

void HienThi() {
 if(Enemy::hp==0) return;
     DoiTuong ::HienThi();
     for(int i=0;i<B.size();i++) {
        B[i].AddXY(0,-1);
       if(B[i].khung_nv.y <=0) {
        B.erase(B.begin()+i,B.begin()+i+1);
        i--;
        continue;
       }
        B[i].HienThi();

     }
     }
};
class DanGa : public Enemy{
public:

    vector<Enemy> dan_ga;

    Enemy x;

void KhoiTao(SDL_Renderer* _renderer){
        //Enemy::Run();
        string s;
    x.KhoiTao("./pictures//c1.png",_renderer,2000,4,100,0);
    x.SetKichThuoc(10,10);
    for(int i=0;i<10;i++) {
        x.SetToaDo(-i*(x.khung_nv.w),100);
        dan_ga.push_back(x);
    }
    }

void HienThi(vector<Bullet> B,SDL_Renderer* _renderer) {
    renderer = _renderer;
   for(int i=0;i<10;i++) {
        //dan_ga[i].Run();
       dan_ga[i].khung_nv.x += dan_ga[i].speed;
      dan_ga[i].khung_nv.y = 100-30*sin(dan_ga[i].khung_nv.x*3.14/180);
     dan_ga[i].HienThi();
      bool collision = false;

      for(int j=0;j<B.size();j++) {
      if(SDL_HasIntersection(&dan_ga[i].khung_nv,&B[j].khung_nv)){
            Enemy::hp =0;
        dan_ga.erase(dan_ga.begin()+i,dan_ga.begin()+i+1);
        i--;
        B.erase(B.begin()+j,B.begin()+j+1);
        j--;
        cout << B.size() << endl;
        if(dan_ga.size()==0) {
            KhoiTao(_renderer);
        }
        collision = true;
        continue;
      }
      if(collision==false) {

     dan_ga[i].HienThi();
      }
    }
   }
}
};
int main(int argc, char* argv[]){
SDL_Window *window;
SDL_Renderer* renderer = NULL;
SDL_Event g_event;
initSDL(window, renderer);

//Menu("./pictures//bg.png", renderer);


SDL_Texture* background = loadTexture("./pictures//bg.png", renderer);
//SDL_Rect size;
SDL_RenderCopy(renderer,background,NULL,NULL);

NhanVat player;

player.KhoiTao("./pictures//spaceship.png",renderer,2000,1000,3,100,0);
ToaDo td_nv;
td_nv.x = 100;
td_nv.y=700;
//int speed =6;
player.SetKichThuoc(1,1);
player.SetToaDo(td_nv.x,td_nv.y);
player.HienThi();

//Enemy chicken;
//chicken.KhoiTao("./pictures//c1.png",renderer,2000,3,100,0);
//chicken.SetKichThuoc(10,10);
//chicken.SetToaDo(td_nv.x,td_nv.y-600);
//chicken.HienThi();
DanGa a;
a.KhoiTao(renderer);
//a.SetKichThuoc(10,10);
//a.SetToaDo(td_nv.x,td_nv.y-600);
//a.HienThi();
int dentaX=0,dentaY=0;
// dieu khien nhan vat theo huong minh muon
int frame =0;
/*while(true) {
       frame++;
    // sdl_pollevent kiem tra su kien game dang true false
    if(SDL_PollEvent(&g_event)) {
        switch(g_event.type) {// nay la loai su kien
            // su kien chuot, su kien ohim, su kien toa do
            case SDL_KEYDOWN:{ // co phim dc bam
               // switch(g_event.key.keysym.sym) { // kiem tra phim duoc bam
                    //cout << g_event.key.keysym.sym<< endl;
                    switch(g_event.key.keysym.sym) {
                    case SDLK_UP:
                       {
                           dentaX=0;
                           dentaY=-1;
                        //player.AddXY(0,-1);
                        //td_nv.y-= speed;
                        break;}
                    case SDLK_DOWN:
                       {
                            dentaX=0;
                           dentaY=1;
                      // player.AddXY(0,1);
                     //  td_nv.y+=speed;
                        break;}
                    case SDLK_LEFT:{
                         dentaX=-1;
                           dentaY=0;
                      //  player.AddXY(-1,0);
                       // td_nv.x-=speed;
                        break;}
                    case SDLK_RIGHT:{
                         dentaX=1;
                           dentaY=0;
                        //player.AddXY(1,0);
                       // td_nv.x+=speed;
                        break;}
                    case SDLK_SPACE: {
                        if(frame >5) {
                       player.Initial_Bullet(0);
                       frame =0;
                        }
                     break;
                }
// tiep theo kiem tra xem do la phim gi
            }
               }
            case SDL_MOUSEBUTTONDOWN:{ // click chuot
                cout << g_event.button.x <<", "<<g_event.button.y<< endl;
                break;
            }

        }
    }
    // player.Run();

     player.AddXY(dentaX,dentaY);
    // player.SetToaDo(td_nv.x,td_nv.y);
    SDL_RenderCopy(renderer,background,NULL,NULL);
    player.HienThi();
    //a.Run();
    a.HienThi();
  //  frame =0;
   // }

//if(frame > 2) {
//        chicken.Run();
 //   frame =0;}
//       chicken.HienThi();
    SDL_RenderPresent(renderer);
}
*/
while(true) {
        frame++;
    if(SDL_PollEvent(&g_event)){
        if(SDL_QUIT == g_event.type) {
                quitSDL(window,renderer);
        }
        switch(g_event.type) {
        case SDL_MOUSEMOTION:{
            player.SetToaDo(g_event.motion.x - player.khung_nv.w/2,g_event.motion.y);
            break;
        }
        case SDL_KEYDOWN:
            switch(g_event.key.keysym.sym) {
            case SDLK_SPACE: {
                if(frame >5) {
                       player.Initial_Bullet(0);
                       frame =0;
                        }
                break;
            }
            }
        }
    }
    SDL_RenderCopy(renderer,background,NULL,NULL);
player.HienThi();
a.HienThi(player.B,renderer);
SDL_RenderPresent(renderer);
}
/// check fps,
SDL_RenderClear(renderer);
SDL_RenderPresent(renderer);
getch();
quitSDL(window, renderer);
return 0;
}



