#include "CPilhaCoordenada.h"

class COffscreenRenderer{

private:

SDL_Renderer *render;
SDL_Surface *surface;
int alt,larg;

public:

    SDL_Renderer *GetRenderer(){
        return render;
    }

    SDL_Surface *GetSurface(){
        return surface;
    }

    int GetAltura(){
        return alt;
    }

    int GetLargura(){
        return larg;
    }

    COffscreenRenderer(int altura,int largura){
        alt = altura;
        larg=largura;
        surface = SDL_CreateRGBSurface(0, largura, altura, 32, 0,0,0,0);//0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        render = SDL_CreateSoftwareRenderer(surface);
        SDL_RenderClear( render );
    }

    void PintarFundo(SDL_Color cor){
        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderClear( render );
    }

    void PintarArea(int px,int py,PIG_Cor cor){
        SDL_LockSurface(surface);
        Uint32 color = SDL_MapRGB((const SDL_PixelFormat*) &surface->format->format,cor.r,cor.g,cor.b);
        CPilhaCoordenada *pilha = new CPilhaCoordenada();
        pilha->Empilha(px,alt-py);
        int x,y;
        Uint32 *p;
        while (pilha->Desempilha(x,y)){
            p = (Uint32*) surface->pixels;
            p += (x+(alt-y)*larg);

            if (x>=0&&y>=0&&x<larg&&y<alt&&(*p)!=color){
                *p = color;     //muda efetivamente a cor
                pilha->Empilha(x+1,y+0);
                pilha->Empilha(x+0,y+1);
                pilha->Empilha(x-1,y+0);
                pilha->Empilha(x+0,y-1);
            }
        }

        delete pilha;
        SDL_UnlockSurface(surface);
    }

    void DesenharLinha(int x1,int y1,int x2,int y2,PIG_Cor cor){
        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawLine(render,x1,alt-y1,x2,alt-y2);
    }

    void DesenharRetangulo(int x,int y,int altura,int largura,PIG_Cor cor){
        SDL_Rect r={x,alt-y-altura,largura,altura};

        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderFillRect(render,&r);
    }

    void DesenharRetanguloVazado(int x,int y,int altura,int largura,PIG_Cor cor){
        SDL_Rect r={x,alt-y-altura,largura,altura};

        SDL_SetRenderDrawColor(render,cor.r,cor.g,cor.b,cor.a);
        SDL_RenderDrawRect(render,&r);
    }

    void SalvarImagem(char *nomearq){
        SDL_RenderReadPixels(render, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
        SDL_SaveBMP(surface, nomearq);
    }

    ~COffscreenRenderer(){
        SDL_DestroyRenderer(render);
        SDL_FreeSurface(surface);
    }

};

typedef COffscreenRenderer* OffscreenRenderer;
