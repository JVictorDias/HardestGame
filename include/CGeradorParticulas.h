#include "CParticula.h"

class CGeradorParticulas{

private:
Particula parts[MAX_PARTICULAS];
int px,py,dx,dy;    //posicao e direcao atual das particulas
SDL_Renderer* renderer;
int hp;
int maxParticulas;
char nome[50];
int ativas;
int usaGerTimer;

public:

    CGeradorParticulas(int maximoParticulas,SDL_Renderer* renderizador, char *nomeArq, int usaGerenciadorTimer){
        maxParticulas = maximoParticulas;
        strcpy(nome,nomeArq);
        usaGerTimer = usaGerenciadorTimer;

        for (int i=0;i<maxParticulas;i++)
            parts[i] = NULL;

        renderer = renderizador;
	    dy = 0;
		dx = 0;
		hp = 1;
		ativas = 0;
    }

    ~CGeradorParticulas(){
        for (int i=0;i<maxParticulas;i++)
            if (parts[i]) delete parts[i];
    }

    void MoveParticulas(){
        for (int i=0;i<maxParticulas;i++)
            if (parts[i]) {
                parts[i]->Move();
                if (!parts[i]->viva){
                    delete parts[i];
                    parts[i] = NULL;
                    ativas--;
                }
            }
    }

    void Move(int nx,int ny){
        px = nx;
        py = ny;
    }

    void MudaDirecao(int novaDx,int novaDy){
        dx = novaDx;
        dy = novaDy;
    }

    void MudaHP(int novoValor){
        hp = novoValor;
    }

    void Desenha(){
        for (int i=0;i<maxParticulas;i++)
            if ((parts[i])&&(parts[i]->viva)) {
                parts[i]->Desenha(NULL);
            }
    }

    int CriaParticula(int fadingOut=0,int minX=-50,int minY=-50,int maxX=LARG_TELA+50,int maxY=ALT_TELA+50,float maxTempo=9999999.9){
        int i=0;
        if (ativas>=maxParticulas) return -1;
        while (parts[i])
            i++;
        parts[i] = new CParticula(px,py,dx,dy,hp,fadingOut,renderer,nome,usaGerTimer);
        parts[i]->DefineLimites(minX,maxX,minY,maxY,maxTempo);
        ativas++;
        return i;
    }

    int Colisao(Objeto outro){
        int resp = 0;
        int i=0,cont=0;
        while (!resp && i<maxParticulas && cont<ativas){
            if (parts[i]){
                cont++;
                resp = parts[i]->Colisao(outro);
            }
            i++;
        }
        return resp;
    }

    int GetQtdAtivas(){
        return ativas;
    }
};

typedef CGeradorParticulas* GeradorParticulas;
