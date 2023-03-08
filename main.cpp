#include <iostream>
#include"game.h"
using namespace std;
// de tai len 1 anh su dung sdl_texture
// sdl_rendercopy de hien thi anh ay
// ham query lay kich thuoc anh
// ham rect de lay toa do khung nhan vat- 1 hinh chu nhat
// co nhieu doi tuong hinh anh nen minh tao class cho nhanh
struct ToaDo{
   int x,y;
};
class DoiTuong{
   public:
       SDL_Texture* nv;
       SDL_Rect khung_nv;
       SDL_Renderer* renderer;
       // xay dung cac hham
       void KhoiTao(string s, SDL_Renderer* _renderer) {
           renderer = _renderer; // khong co cai nay la no meo in ra
           nv= loadTexture(s, _renderer); // ham load anh
           //goi ham lay kich thuoc
           SDL_QueryTexture(nv,NULL,NULL,&khung_nv.w,&khung_nv.h);// vi trong ngoac la *h *w
       }
       void SetKichThuoc(float denta_h, float denta_w) {
           khung_nv.h /= denta_h;
           khung_nv.w /= denta_w;
       }
       // bay h set toa do
       void SetToaDo(int x, int y) {
       khung_nv.x=x;
       khung_nv.y=y;
       }
       void HienThi(){
           SDL_RenderCopy(renderer,nv,NULL, &khung_nv);
       }

};
class NhanVat : public DoiTuong{
  public:
      int hp_max, hp;
      int mp_max,mp;
      int speed;
      int dame;
      int animation=0;
      void KhoiTao(string s, SDL_Renderer* _renderer,int shp,
                   int smp, int sspeed, int sdame, int sanimation) {
                       DoiTuong ::KhoiTao(s,_renderer);
                       hp_max= shp; hp = hp_max;
                       mp_max=smp; mp= mp_max;
                       speed= sspeed;
                       dame=sdame;
                       animation=sanimation;
                       // gan lai
                   }
     void AddXY(int &dentaX, int &dentaY) { // gia tri cua dentaXY up 0 -1 down 0 1 left -1 0 right 1 0
        // h lam the nao de nhan vat den bien cua window thi dung lai
        if((khung_nv.x <= 0 && dentaX ==-1) || (khung_nv.x>=SCREEN_WIDTH -khung_nv.w && dentaX ==1)
           || (khung_nv.y <=0 && dentaY == -1) || (khung_nv.y >= SCREEN_HEIGHT - khung_nv.h && dentaY ==1))
           {dentaX*= -1;
            dentaY *= -1;
            return;}
     khung_nv.x += dentaX*speed;
     khung_nv.y += dentaY*speed;
     }
    void Run() {
       string link_anh[] ={"./pictures//chicken1.png","./pictures//chicken2.png",
                           "./pictures//chicken3.png","./pictures//chicken4.png","./pictures//chicken5.png",
                             "./pictures//chicken6.png"};
        nv= loadTexture(link_anh[animation],renderer);
        animation++;
        if(animation==5) {
            animation=0;
        }
    }
};

int main(int argc, char* argv[])
{
SDL_Window *window;
SDL_Renderer* renderer = NULL;
SDL_Event g_event;
initSDL(window, renderer);
SDL_Texture* background = loadTexture("./pictures//bg.png", renderer);
//SDL_Rect size;
SDL_RenderCopy(renderer,background,NULL,NULL);
NhanVat player;
player.KhoiTao("./pictures//chicken1.png",renderer,2000,1000,3,100,0);
ToaDo td_nv;
td_nv.x = 100;
td_nv.y=100;
//int speed =6;
player.SetKichThuoc(10,10);
player.SetToaDo(td_nv.x,td_nv.y);
player.HienThi();
/*
for(int i=0;i<100;i++) {
    player.SetToaDo(td_nv.x+i*5,td_nv.y);
     SDL_RenderCopy(renderer,background,NULL,NULL);
    // SDL_RenderPresent(renderer);
    player.HienThi();
    SDL_RenderPresent(renderer); // ham cap nhat
}
*/
int dentaX=0,dentaY=0;
// dieu khien nhan vat theo huong minh muon

while(true) {
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
                }
                break;

                // tiep theo kiem tra xem do la phim gi
            }
            case SDL_MOUSEBUTTONDOWN:{ // click chuot
                cout << g_event.button.x <<", "<<g_event.button.y<< endl;
                break;
            }

        }
    }
     player.Run();
     player.AddXY(dentaX,dentaY);
     //player.SetToaDo(td_nv.x,td_nv.y);
    SDL_RenderCopy(renderer,background,NULL,NULL);
   // SDL_RenderPresent(renderer);
    player.HienThi();
    SDL_RenderPresent(renderer);
}
SDL_RenderPresent(renderer);
//player.SetKichThuoc(8,8);
//player.SetToaDo(td_nv.x,td_nv.y); // han che bien kieu so nhu nay
//player.HienThi();
// tao hieu ung di chuyen

//player.SetToaDo(td_nv.x+200,td_nv.y);
//player.HienThi(); // phai co ham Rendercopy moi in ra man hinh
/*
SDL_Texture *player = loadTexture("./pictures//playerwalk1.png",renderer); // gan anh
//ham query lay kich thuoc cua anh
int h,w;
SDL_QueryTexture(background,NULL,NULL,&h,&w);// chieu cao va chieu rong
//cout << h<< " " <<w<< endl;
h/= 8;
w/=8;
// muon hien nhan vat len phai co ham xac dinh 1 hinh chu nhat Rect
SDL_Rect toa_do_nv;
toa_do_nv.x =200;
toa_do_nv.y=100;
toa_do_nv.h=h;
toa_do_nv.w=w;
SDL_RenderCopy(renderer, player,NULL,&toa_do_nv);// ham tai len man hinh
*/
//SDL_RenderPresent(renderer);
getch();
return 0;
// handle .-> update -> render


}


