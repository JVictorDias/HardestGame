#include "COffscreenRenderer.h"

class CMapaCaracteres{

private:

    int *alturaLetra;
    int *larguraLetra;

    SDL_Renderer *render;
    SDL_Texture **glyphsT;

public:

    char nome[100];
    int tamFonte;

    CMapaCaracteres(char *nomeFonte,SDL_Renderer* renderer,int tamanhoFonte,int estilo, PIG_Cor corFonte,int outline,PIG_Cor corOutline){
        strcpy(nome,nomeFonte);
        tamFonte = tamanhoFonte;
        render = renderer;

        alturaLetra = (int*)malloc(sizeof(int)*(ULTIMO_CAR-PRIMEIRO_CAR));
        larguraLetra = (int*)malloc(sizeof(int)*(ULTIMO_CAR-PRIMEIRO_CAR));

        glyphsT = (SDL_Texture**) malloc(sizeof(SDL_Texture*)*(ULTIMO_CAR-PRIMEIRO_CAR));

        TTF_Font *font = TTF_OpenFont( nome, tamanhoFonte );
        if (font==NULL)
            printf("Erro: arquivo de fonte (%s) nao localizado\n");
        TTF_SetFontStyle(font,estilo);

        SDL_Surface *surfaceTemp[ULTIMO_CAR-PRIMEIRO_CAR];
        int altRend=0,largRend=0;

        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            surfaceTemp[j-PRIMEIRO_CAR] = TTF_RenderGlyph_Solid(font,(Uint16)j,corFonte);
            alturaLetra[j-PRIMEIRO_CAR] = surfaceTemp[j-PRIMEIRO_CAR]->h;
            if (surfaceTemp[j-PRIMEIRO_CAR]->h>altRend)
                altRend = surfaceTemp[j-PRIMEIRO_CAR]->h;
            larguraLetra[j-PRIMEIRO_CAR] = surfaceTemp[j-PRIMEIRO_CAR]->w;
            largRend+=surfaceTemp[j-PRIMEIRO_CAR]->w;
        }

        SDL_Rect rect;
        rect.x=0;
        rect.y=0;
        rect.h=altRend;

        OffscreenRenderer off = new COffscreenRenderer(altRend,largRend);
        if (CORESIGUAIS(corFonte,BRANCO)){
            off->PintarFundo(PRETO);
        }else off->PintarFundo(BRANCO);
        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            glyphsT[j-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(off->GetRenderer(),surfaceTemp[j-PRIMEIRO_CAR]);
            SDL_FreeSurface(surfaceTemp[j-PRIMEIRO_CAR]);
            rect.w=larguraLetra[j-PRIMEIRO_CAR];
            SDL_RenderCopy(off->GetRenderer(),glyphsT[j-PRIMEIRO_CAR],NULL,&rect);
            SDL_DestroyTexture(glyphsT[j-PRIMEIRO_CAR]);
            rect.x += rect.w;
        }
        //off->EncerrarDesenho();
        off->SalvarImagem(NOME_ARQ_TEMP);

        rect.x=0;
        rect.y=0;
        rect.h=altRend;
        SDL_Rect dest;
        dest.x=dest.y=0;

        TTF_SetFontOutline(font,outline);

        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            dest.h=alturaLetra[j-PRIMEIRO_CAR];
            rect.w=dest.w=larguraLetra[j-PRIMEIRO_CAR];
            surfaceTemp[j-PRIMEIRO_CAR] = SDL_CreateRGBSurface(0,larguraLetra[j-PRIMEIRO_CAR],alturaLetra[j-PRIMEIRO_CAR],24,0,0,0,0);
            SDL_BlitSurface(off->GetSurface(),&rect,surfaceTemp[j-PRIMEIRO_CAR],&dest);
            if (outline>0){
                SDL_Surface *out = TTF_RenderGlyph_Solid(font,(Uint16)j,corOutline);
                SDL_BlitSurface(out,NULL,surfaceTemp[j-PRIMEIRO_CAR],&dest);
                SDL_FreeSurface(out);
            }
            if (CORESIGUAIS(corFonte,BRANCO)){
                SDL_SetColorKey(surfaceTemp[j-PRIMEIRO_CAR],SDL_TRUE,SDL_MapRGBA(surfaceTemp[j-PRIMEIRO_CAR]->format, 0,0,0,255));//ROXO
            }else SDL_SetColorKey(surfaceTemp[j-PRIMEIRO_CAR],SDL_TRUE,SDL_MapRGBA(surfaceTemp[j-PRIMEIRO_CAR]->format, 255,255,255,255));//ROXO

            glyphsT[j-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(renderer,surfaceTemp[j-PRIMEIRO_CAR]);
            SDL_FreeSurface(surfaceTemp[j-PRIMEIRO_CAR]);
            rect.x+=larguraLetra[j-PRIMEIRO_CAR];
        }

        TTF_CloseFont(font);
        delete off;
        remove(NOME_ARQ_TEMP);
    }

    CMapaCaracteres(char *nomeFonte,SDL_Renderer* renderer,int tamanhoFonte,int estilo, char *fundoFonte,int outline,PIG_Cor corOutline){
        strcpy(nome,nomeFonte);
        tamFonte = tamanhoFonte;
        render = renderer;

        alturaLetra = (int*)malloc(sizeof(int)*(ULTIMO_CAR-PRIMEIRO_CAR));
        larguraLetra = (int*)malloc(sizeof(int)*(ULTIMO_CAR-PRIMEIRO_CAR));

        glyphsT = (SDL_Texture**) malloc(sizeof(SDL_Texture*)*(ULTIMO_CAR-PRIMEIRO_CAR));

        TTF_Font *font = TTF_OpenFont( nome, tamanhoFonte );
        TTF_SetFontStyle(font,estilo);

        SDL_Surface *surfaceTemp[ULTIMO_CAR-PRIMEIRO_CAR];
        int altOffScreen=0,largOffScreen=0;

        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            surfaceTemp[j-PRIMEIRO_CAR] = TTF_RenderGlyph_Solid(font,(Uint16)j,PRETO);
            alturaLetra[j-PRIMEIRO_CAR] = surfaceTemp[j-PRIMEIRO_CAR]->h;
            if (surfaceTemp[j-PRIMEIRO_CAR]->h>altOffScreen)
                altOffScreen = surfaceTemp[j-PRIMEIRO_CAR]->h;
            larguraLetra[j-PRIMEIRO_CAR] = surfaceTemp[j-PRIMEIRO_CAR]->w;
            largOffScreen+=surfaceTemp[j-PRIMEIRO_CAR]->w;
        }

        SDL_Rect rect;
        rect.x=0;
        rect.y=0;
        rect.h=altOffScreen;

        OffscreenRenderer off = new COffscreenRenderer(altOffScreen,largOffScreen);
        off->PintarFundo(BRANCO);
        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            glyphsT[j-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(off->GetRenderer(),surfaceTemp[j-PRIMEIRO_CAR]);
            SDL_FreeSurface(surfaceTemp[j-PRIMEIRO_CAR]);
            rect.w=larguraLetra[j-PRIMEIRO_CAR];
            SDL_RenderCopy(off->GetRenderer(),glyphsT[j-PRIMEIRO_CAR],NULL,&rect);
            SDL_DestroyTexture(glyphsT[j-PRIMEIRO_CAR]);
            rect.x += rect.w;
        }

        rect.w=1;
        rect.h=altOffScreen;
        rect.x=0;
        rect.y=0;
        SDL_FillRect(off->GetSurface(),&rect,SDL_MapRGB(off->GetSurface()->format,0,0,0));

        //off->EncerrarDesenho();
        off->SalvarImagem(NOME_ARQ_TEMP);
        off->PintarFundo(BRANCO);

        SDL_Surface* stencil = IMG_Load(NOME_ARQ_TEMP);
        SDL_SetColorKey(stencil,SDL_TRUE,SDL_MapRGBA(stencil->format, 0,0,0,255));
        SDL_Texture *textStencil = SDL_CreateTextureFromSurface(off->GetRenderer(),stencil);

        SDL_Surface* fundo = IMG_Load(fundoFonte);
        SDL_Texture *textFundo = SDL_CreateTextureFromSurface(off->GetRenderer(),fundo);

        rect.w=fundo->w;
        rect.x=0;
        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            rect.w=larguraLetra[j-PRIMEIRO_CAR];
            SDL_RenderCopy(off->GetRenderer(),textFundo,NULL,&rect);
            rect.x+=larguraLetra[j-PRIMEIRO_CAR];
        }
        SDL_RenderCopy(off->GetRenderer(),textStencil,NULL,NULL);
        //off->EncerrarDesenho();
        off->SalvarImagem(NOME_ARQ_TEMP);

        rect.x=0;
        rect.y=0;
        rect.h=altOffScreen;
        SDL_Rect dest;
        dest.x=dest.y=0;

        TTF_SetFontOutline(font,outline);

        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            dest.h=alturaLetra[j-PRIMEIRO_CAR];
            rect.w=dest.w=larguraLetra[j-PRIMEIRO_CAR];
            surfaceTemp[j-PRIMEIRO_CAR] = SDL_CreateRGBSurface(0,larguraLetra[j-PRIMEIRO_CAR],alturaLetra[j-PRIMEIRO_CAR],24,0,0,0,0);
            SDL_BlitSurface(off->GetSurface(),&rect,surfaceTemp[j-PRIMEIRO_CAR],&dest);
            if (outline>0){
                SDL_Surface *out = TTF_RenderGlyph_Solid(font,(Uint16)j,corOutline);
                SDL_BlitSurface(out,NULL,surfaceTemp[j-PRIMEIRO_CAR],&dest);
                SDL_FreeSurface(out);
            }
            SDL_SetColorKey(surfaceTemp[j-PRIMEIRO_CAR],SDL_TRUE,SDL_MapRGBA(surfaceTemp[j-PRIMEIRO_CAR]->format, 255,255,255,255));//ROXO
            glyphsT[j-PRIMEIRO_CAR] = SDL_CreateTextureFromSurface(renderer,surfaceTemp[j-PRIMEIRO_CAR]);
            SDL_FreeSurface(surfaceTemp[j-PRIMEIRO_CAR]);
            rect.x+=larguraLetra[j-PRIMEIRO_CAR];
        }

        TTF_CloseFont(font);
        delete off;

        remove(NOME_ARQ_TEMP);
    }

    ~CMapaCaracteres(){
        for (Uint16 j=PRIMEIRO_CAR;j<ULTIMO_CAR;j++){
            SDL_DestroyTexture(glyphsT[j-PRIMEIRO_CAR]);
        }
        free(glyphsT);
        free(larguraLetra);
        free(alturaLetra);
    }

    int GetLarguraPixelsString(char *str){
        int resp=0;
        Uint16 aux;

        for (int i=0;i<strlen(str);i++){
            aux = str[i];
            aux = aux % 256;
            resp += larguraLetra[aux-PRIMEIRO_CAR];
        }

        return resp;
    }

    void EscreveStringCentralizado(char *str,int x,int y){
        int larguraPixels = GetLarguraPixelsString(str);
        EscreveStringEsquerda(str,x-larguraPixels/2,y);
    }

    void EscreveStringEsquerda(char *str,int x,int y){
        SDL_Rect rectDestino;
        rectDestino.x = x;
        rectDestino.y = ALT_TELA-y-tamFonte;

        Uint16 aux;
        for (int i=0;i<strlen(str);i++){
            aux = str[i];
            if(aux == '\n')
            {
                rectDestino.x = x;
                rectDestino.y = rectDestino.y - tamFonte;
                continue;
            }
            aux = aux % 256;//UTF16 string, retirando só o byte que interessa

            rectDestino.w = larguraLetra[aux-PRIMEIRO_CAR];
            rectDestino.h = alturaLetra[aux-PRIMEIRO_CAR];
            SDL_RenderCopy(render,glyphsT[aux-PRIMEIRO_CAR],NULL,&rectDestino);

            rectDestino.x += rectDestino.w;
        }
    }

    void EscreveStringDireita(char *str,int x,int y){
        int larguraPixels = GetLarguraPixelsString(str);
        EscreveStringEsquerda(str,x-larguraPixels,y);
    }
};

typedef CMapaCaracteres* MapaCaracteres;
