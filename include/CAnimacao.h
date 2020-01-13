class CAnimacao:public CObjeto{

typedef struct {
    int loop;
    int qtdFrames;
    int frames[MAX_FRAMES_MODO];
    float delays[MAX_FRAMES_MODO];
}Modo;

private:

int souCopia;
int qtdTotalFrames;
Modo *modos[MAX_MODOS];
int frameDoModo;
SDL_Rect *frames[MAX_FRAMES];
Timer tempoFrame;
int idTimer;
int offx,offy;
int modoAtual;
int frameAtual;

public:

CAnimacao(int px,int py,SDL_Renderer* renderizador,char *nomeArq,int usaGerenciadorTimer=0,int retiraFundo=1,int opacidade=255):CObjeto(px,py,renderizador,nomeArq,retiraFundo,opacidade){
    souCopia = 0;
    offx = offy = 0;
    modoAtual = 0;
    frameDoModo=-1;

    for (int i=0;i<MAX_FRAMES;i++)
        frames[i] = (SDL_Rect*)malloc(sizeof(SDL_Rect));

    qtdTotalFrames = 0;
    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = NULL;
    }

    if (usaGerenciadorTimer){
        tempoFrame = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        tempoFrame = new CTimer();
        idTimer = -1;
    }
}

CAnimacao(int px,int py,CAnimacao* base,int usaGerenciadorTimer=0):CObjeto(px,py,base->renderer,base->nomeImagem){
    souCopia= 1;
    frameDoModo=-1;

    qtdTotalFrames = base->qtdTotalFrames;
    for (int i=0;i<MAX_FRAMES;i++){
        frames[i] = base->frames[i];
    }

    for (int i=0;i<MAX_MODOS;i++){
        modos[i] = base->modos[i];
    }
    SetDimensoes(base->alt,base->larg);

    offx = base->offx;
    offy = base->offy;
    modoAtual = base->modoAtual;

    if (usaGerenciadorTimer){
        tempoFrame = NULL;
        idTimer = CGerenciadorTimers::CriaTimer();
    }else{
        tempoFrame = new CTimer();
        idTimer = -1;
    }
}

~CAnimacao(){
    if (!souCopia){
        for (int i=0;i<MAX_MODOS;i++){
            if (modos[i])
                free(modos[i]);
        }
        for (int i=0;i<MAX_FRAMES;i++)
            free(frames[i]);
    }

    if (tempoFrame){
        delete tempoFrame;
    }else {
        CGerenciadorTimers::DestroiTimer(idTimer);
    }
}

//define o retangulo da imagem que corresponde ao frame
void CriaFrame(int codFrame,int x,int y,int altura,int largura){
    frames[codFrame]->x = x;
    frames[codFrame]->y = y;
    frames[codFrame]->h = altura;
    frames[codFrame]->w = largura;
}

//cria um modo vazio, sem frames associados
void CriaModo(int idModo, int loop){
    if (modos[idModo]) free(modos[idModo]);
    modos[idModo] = (Modo*) malloc(sizeof(Modo));
    Modo *atual = modos[idModo];
    atual->loop = loop;
    atual->qtdFrames = 0;
}

//insere um frame em um dos modos
void InsereFrame(int idModo, int idFrame, float delayFrame){
    int aux = modos[idModo]->qtdFrames;
    modos[idModo]->frames[ aux ] = idFrame;
    modos[idModo]->delays[ aux ] = delayFrame;
    modos[idModo]->qtdFrames++;
}

//muda o modo atual
void MudaModo(int idModo,int inicia){
    modoAtual = idModo;

    if (inicia) frameDoModo = 0;
    else frameDoModo = modos[idModo]->qtdFrames-1;
    frameAtual = modos[idModo]->frames[frameDoModo];

    if (tempoFrame)
        tempoFrame->Reinicia();
    else CGerenciadorTimers::ReiniciaTimer(idTimer);

    CObjeto::DefineFrame(frames[frameAtual]);
}

//desenha a animação
int Desenha(){
    int resp=0; //0 indica que que o modo de animação atual não terminou
    Modo *modo = modos[modoAtual];
    float tempo = modo->delays[frameDoModo];
    float tempoDecorrido;

    if (tempoFrame)
        tempoDecorrido = tempoFrame->GetTempoDecorrido();
    else tempoDecorrido = CGerenciadorTimers::GetTempoDecorrido(idTimer);

    if (tempoDecorrido>tempo){
        frameDoModo++;
        if (frameDoModo>=modo->qtdFrames){//testa se chegou ao ultimo frame do modo atual
            if (modo->loop){
                frameDoModo=0;
            }else{
                frameDoModo--; //permanece no ultimo frame e informa o encerramento do modo com resp=1
                resp=1;
            }
        }
        if (tempoFrame)
            tempoFrame->Reinicia();
        else CGerenciadorTimers::ReiniciaTimer(idTimer);

        frameAtual = modo->frames[frameDoModo];
        CObjeto::DefineFrame(frames[frameAtual]);
    }

    int px = x+offx;
    int py = y+offy;

    CObjeto::Move(px,py);
    CObjeto::Desenha(NULL);

    px -=offx;
    py -=offy;

    CObjeto::Move(px,py);

    return resp;
}

};


typedef CAnimacao* Animacao;
