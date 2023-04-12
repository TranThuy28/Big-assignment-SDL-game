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
   public:
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
       void Release() {
       SDL_DestroyRenderer(renderer);
       SDL_DestroyTexture(nv);
       }

};

class Animation: public DoiTuong{
public :
       //SDL_Texture* image= NULL;
      bool animated(string link_anh,SDL_Renderer* _renderer);
      void next();
protected:

    int frameCount;
     vector<SDL_Texture*> images;

};

bool Animation::animated(string link_anh, SDL_Renderer* _renderer) {
   nv  = loadTexture(link_anh,_renderer);
  if(nv){
    images.push_back(nv);
    return true;
  }
  else {
        cout << " can not load image :" << SDL_GetError() << endl;
    return false;
  }
}
void Animation::next() {
     frameCount++;
     nv = images[frameCount % (images.size()-1)];
}
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
     cout << B.size() << endl;
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

class Enemy : public Animation{
public:
      int hp_max, hp;
      int speed;
      int dame;
      int animation=0;


      vector<Bullet> B;
       SDL_Texture* image= NULL;

void KhoiTao(string s, SDL_Renderer* _renderer,int shp,
                    int sspeed, int sdame, int sanimation) {
                       DoiTuong ::KhoiTao(s,_renderer);
                       hp_max= shp; hp = hp_max;
                       speed= sspeed;
                       dame=sdame;
                       animation=sanimation;
                       // gan lai
                   }

void Run(string s) {
    /*
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
                             */
       // nv= loadTexture(link_anh[animation],renderer);
        animation++;
        if(animation ==21) {
            animation=0;
        }
   }
///tóm tắt ý tưởng làm lại animation
/*
class animation: public item
{
public:
bool addImage(string filePath); -> ham tai anh len
void next();
protected:
int frameCount;
vector <SDL_Texture*> images;
};
bool animation::addImage(string filePath){
 if( loadImage(filePath)){
 images.push_back(image);
 return true;
 }
 else return false;
}
void animation::next() {
frameCount++;
image = images[frameCount % (Images.size()-1)];
}
 Trong ham main.cpp
 animation box;
 box.setrenderer(screen);
 ///set toa do, sẻ kich thuoc
 string path = "heart/";
 string count = "0000";
 string ext = ".png";
  for(int i=0;i<80;i++){
    count[3] += 1;
    ì(count[3] >'9'){
    count[2ư++;
    count[3]=0;
    }
  box.addImage(path +count + ext);
  }
  xong sau do chi can them ham next vao trong vong lap
*/
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
     cout << 1 << endl;
     cout << B.size() << endl;
     }

void HienThi() {
 if(Enemy::hp==0) return;
     DoiTuong ::HienThi();
   //  cout << B.size()<< endl;
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
    Enemy Collision_Animation;
    string link_anh;
    SDL_Texture* image= NULL;

void KhoiTao(SDL_Renderer* _renderer){
  //  DoiTuong::KhoiTao("./pictures//collision1.png", _renderer);
      // Enemy::Run(s);
       // string s;
      x.nv = nv;
   Collision_Animation.KhoiTao("./pictures//collision1.png",_renderer,0,0,0,0);
   Collision_Animation.SetKichThuoc(1,1);
    x.KhoiTao("./pictures//c01.png",_renderer,2000,3,100,0);
    x.SetKichThuoc(10,10);
    for(int i=0;i<10;i++) {
        x.SetToaDo(-i*(x.khung_nv.w),100);
        dan_ga.push_back(x);
    }
    }

void HienThi(vector<Bullet> B,SDL_Renderer* _renderer, string link_anh) {
   // renderer = _renderer;

   for(int i=0;i<10;i++) {
          dan_ga[i].nv= nv;
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
        if(dan_ga.size()==0) {
            KhoiTao(_renderer);
        }
        collision = true;
     Collision_Animation.khung_nv.x = dan_ga[i].khung_nv.x;
     Collision_Animation.khung_nv.y = dan_ga[i].khung_nv.y;
     string path = "./pictures//collision";
     string index = "1";
     string tail = ".png";
     for( int z =0;z <5;z++) {
     Collision_Animation.nv = nv;
     Collision_Animation.animated(path + index + tail,_renderer);
     cout << path + index + tail << endl;
     index[0]++;
     }
     for(int a=0;a<5;a++){
     Collision_Animation.next();
     Collision_Animation.HienThi();
     }
        continue;
      }
      if(collision==false) {

     dan_ga[i].HienThi();
      }
    }
   }
}
};
/*
class Animation: public DanGa{
public :
       //SDL_Texture* image= NULL;
      bool animated(string link_anh,SDL_Renderer* _renderer);
      void next();
protected:

    int frameCount;
     vector<SDL_Texture*> images;

};

bool Animation::animated(string link_anh, SDL_Renderer* _renderer) {
   image = loadTexture(link_anh,_renderer);
  if(image){
    images.push_back(image);
    return true;
  }
  else {
        cout << " can not load image :" << SDL_GetError() << endl;
    return false;
  }
}
void Animation::next() {
     frameCount++;
     image = images[frameCount % (images.size()-1)];
}
*/
int main(int argc, char* argv[]){
SDL_Window *window;
SDL_Renderer* renderer = NULL;
SDL_Event g_event;
SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8* wavBuffer;

SDL_Init(SDL_INIT_AUDIO);
initSDL(window, renderer);

if(SDL_LoadWAV("./RunGameAudio.wav",&wavSpec, &wavBuffer, &wavLength)) {

SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL,0, &wavSpec,NULL, 0);
SDL_QueueAudio(deviceId, wavBuffer, wavLength);

SDL_PauseAudioDevice(deviceId,0);
}
else {
        cout << " Can not load audio:" << SDL_GetError() << endl;
}
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
string s;
DanGa a;
a.KhoiTao(renderer);
//a.SetKichThuoc(10,10);
//a.SetToaDo(td_nv.x,td_nv.y-600);
//a.HienThi();
int dentaX=0,dentaY=0;
//a.nv= loadTexture(link_anh[0],renderer);
string path = "./pictures//c";
string index = "01";
string tail = ".png";
int dem =0;
for(int i =0; i<21;i++) {
  a.animated(path+index+tail,renderer);
  if(index == "21") {dem++;}

  if(dem ==0) {
        if(index[1]< '9'){
        index[1] =index[1] + 1;}
        else{
            index[0]++;
            index[1]= '0';
        }
}
  else {
      if(index[1] < '2') {
        index[1]= index[1] - 1;
        index[0]--;}
       else {index[1] -=1;}
        }
}
//DanGa Collision;
//Collision.KhoiTao("./pictures//collision1.png", renderer);

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
  //a.HienThi(player.B,renderer);
while(true) {
        frame++;
        //cout << frame << endl;
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
a.next();
a.HienThi(player.B,renderer,s);
SDL_RenderPresent(renderer);
}
player.Release();
a.Release();
SDL_RenderClear(renderer);
SDL_RenderPresent(renderer);
getch();
//quitSDL(window, renderer);
return 0;
}



