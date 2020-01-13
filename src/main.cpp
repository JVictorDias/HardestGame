#include "PIG.h"

    PIG_Cor AZUL_FORA       = {180,180,255,255};
    PIG_Cor VERDE_START     = {180,255,180,255};
    PIG_Cor VERDE_END       = {255,255,180,255};
    PIG_Cor BRANCO_FUNDO    = {247,247,255,255};
    PIG_Cor CINZA_FUNDO     = {230,230,255,255};

    PIG_Cor VERMELHO_FUNDO  = {255,236,244,255};
    PIG_Cor VERMELHO_FORA   = {251,175,173,255};

#define LARGURA_BORDA       5

#define VAZIO               0
#define INICIO              1
#define FINAL               2
#define ANDAVEL             3
#define OBSTACULO           4
#define MOEDA               5
#define INICIO_PONTO        6
#define FINAL_PONTO         7
#define CAMINHO             8

#define QTD_CORES           9
#define QTD_MAX_OBSTACULOS  1000
#define QTD_MAX_MOEDAS      1000
#define QTD_MAX_PIVO        100

typedef struct pivo
{
    int x, y;
    int existe;

}   Pivo;

typedef struct caminho
{
    double destinoX, destinoY;
    double velocidade;

    int angular, direcao, direcaoAtual;
    double anguloSwap, anguloSwapAtual;
    double anguloParada, anguloParadaAtual;
    int IteracoesParado, IteracoesParadoAtual;

}   Caminho;

typedef struct moeda
{
    double X, Y;
    int existe;

}   Moeda;

typedef struct obstaculo
{
    double x, y;
    double xInicial, yInicial;
    Caminho caminho[50];

    int quantidadeCaminhos;
    int caminhoAtual;

    int existe;

}   Obstaculo;

typedef struct mapa
{
    int cenario[100][100];
    int quantidadeBlocos;

    Obstaculo obstaculos[1000];
    Moeda moedas[1000];

    int inicioX, inicioY;
    int finalX, finalY;

    Pivo pivo[100];

}   Mapa;


typedef struct individuo
{
    double X, Y;
    char Morreu, Ganhou;
    int cor;

    int moedas[QTD_MAX_MOEDAS];

}   Individuo;

    Mapa mapaAtual;
    Mapa mapaBackup;

    int TAM_BLOCOS, TAM_PERSONAGEM, TAM_OBSTACULO, QTD_BLOCOS;
    double Periodo;

    int inicioCenarioX, inicioCenarioY;
    int spriteObstaculo, spriteMoeda, spriteInicio, spriteFinal, spriteX;
    int spriteLuzAzul,spriteLuzVermelha,spriteLuzAmarela, spriteFundo, spriteEstrelas;
    int spriteTeclado0[5], spriteTeclado1[5];

    int mapaIniciado;
    int TimerGeral;
    PIG_Cor cores[QTD_CORES] = {VERMELHO,VERDE,AZUL,CIANO,AMARELO,ROSA,ROXO,CINZA,LARANJA};

    Individuo individuo[1];
    int FontePreta;

    int spritePersonagem;

    double espacoReservado[QTD_MAX_OBSTACULOS];
    int id = 0;

    int quantidadeObstaculosCenario, quantidadeMoedasCenario;
    int matrizColisao[LARG_TELA][ALT_TELA];

    double COEF = 1.0;

void desenharCenario(int X, int Y)
{
    PIG_Cor cor;
    int codigo;

    for(int i=0; i<QTD_BLOCOS; i++)
    {
        for(int j=0; j<QTD_BLOCOS; j++)
        {
            codigo = mapaAtual.cenario[i][j];

            switch(codigo)
            {
                case VAZIO:
                {
                    if(id == 30)
                    {
                        cor = VERMELHO_FORA;
                    }
                    else
                    {
                        cor = AZUL_FORA;
                    }

                }   break;
                case INICIO:
                {
                    cor = VERDE_START;
                }   break;
                case FINAL:
                {
                    cor = VERDE_END;
                }   break;
                case ANDAVEL:
                {
                    if((i+j)%2 == 0)
                    {
                        cor = BRANCO_FUNDO;
                    }
                    else
                    {
                        if(id == 30)
                        {
                            cor = VERMELHO_FUNDO;
                        }
                        else
                        {
                            cor = CINZA_FUNDO;
                        }

                    }
                }   break;
            }

            if(codigo != VAZIO)
            {
                DesenharRetangulo(X + COEF*i*TAM_BLOCOS,
                                  Y + COEF*j*TAM_BLOCOS,
                                  COEF*TAM_BLOCOS, COEF*TAM_BLOCOS,
                                  cor);
            }
        }
    }
}

void desenharBordas(int X, int Y)
{
    PIG_Cor cor = PRETO;
    for(int i=0; i<QTD_BLOCOS; i++)
    {
        for(int j=0; j<QTD_BLOCOS; j++)
        {
            if(mapaAtual.cenario[i][j] == VAZIO)
            {
                if(i+1 < QTD_BLOCOS && mapaAtual.cenario[i+1][j] != VAZIO)
                {
                    DesenharRetangulo(X + (i+1)*TAM_BLOCOS*COEF - LARGURA_BORDA*COEF + 1,
                                      Y + j*TAM_BLOCOS*COEF,
                                      TAM_BLOCOS*COEF, LARGURA_BORDA*COEF, cor);

                    if(mapaAtual.cenario[i+1][j+1] == VAZIO)
                    {
                        DesenharRetangulo(X + (i+1)*TAM_BLOCOS*COEF - LARGURA_BORDA*COEF + 1,
                                          Y +  (j+1)*TAM_BLOCOS*COEF,
                                          LARGURA_BORDA*COEF, LARGURA_BORDA*COEF, cor);
                    }

                    if(mapaAtual.cenario[i+1][j-1] == VAZIO)
                    {
                        DesenharRetangulo(X + (i+1)*TAM_BLOCOS*COEF - LARGURA_BORDA*COEF + 1,
                                          Y + (j)*TAM_BLOCOS*COEF - LARGURA_BORDA*COEF,
                                                LARGURA_BORDA*COEF, LARGURA_BORDA*COEF, cor);
                    }

                }
                if(i-1 >= 0 && mapaAtual.cenario[i-1][j] != VAZIO)
                {
                    DesenharRetangulo(X + (i)*TAM_BLOCOS*COEF,
                                      Y + j*TAM_BLOCOS*COEF,
                                      TAM_BLOCOS*COEF, LARGURA_BORDA*COEF, cor);

                    if(mapaAtual.cenario[i-1][j+1] == VAZIO)
                    {
                        DesenharRetangulo(X + (i)*TAM_BLOCOS*COEF,
                                          Y + (j+1)*TAM_BLOCOS*COEF,
                                                LARGURA_BORDA*COEF, LARGURA_BORDA*COEF, cor);
                    }

                    if(mapaAtual.cenario[i-1][j-1] == VAZIO)
                    {
                        DesenharRetangulo(X + (i)*TAM_BLOCOS*COEF,
                                          Y + (j)*TAM_BLOCOS*COEF - LARGURA_BORDA*COEF,
                                                LARGURA_BORDA*COEF+1, LARGURA_BORDA*COEF, cor);
                    }
                }
//
//
                if(j+1 < QTD_BLOCOS && mapaAtual.cenario[i][j+1] != VAZIO)
                {
                    DesenharRetangulo(X + i*TAM_BLOCOS*COEF,
                                      Y + (j+1)*TAM_BLOCOS*COEF - LARGURA_BORDA*COEF,
                                      LARGURA_BORDA*COEF+1, TAM_BLOCOS*COEF, cor);
                }
                if(j-1 >= 0 && mapaAtual.cenario[i][j-1] != VAZIO)
                {
                    DesenharRetangulo(X + i*TAM_BLOCOS*COEF,
                                      Y + (j)*TAM_BLOCOS*COEF,
                                      LARGURA_BORDA*COEF, TAM_BLOCOS*COEF, cor);
                }
            }
        }
    }
}

void desenharObstaculos(int X, int Y)
{
    if(id == 30)
    {
        DefinirColoracao(spriteObstaculo, VERMELHO);
        DefinirColoracao(spriteLuzAzul, VERMELHO);
    }
    else
    {
        DefinirColoracao(spriteObstaculo, AZUL);
        DefinirColoracao(spriteLuzAzul, AZUL);
    }

    for(int i=0; i<QTD_MAX_OBSTACULOS; i++)
    {
        if(mapaAtual.obstaculos[i].existe == 1)
        {
            DesenharSprite(spriteLuzAzul,
                           X+ mapaAtual.obstaculos[i].x*COEF,
                           Y+ mapaAtual.obstaculos[i].y*COEF,
                           1.8*TAM_OBSTACULO*COEF, 1.8*TAM_OBSTACULO*COEF, 0);

            DesenharSprite(spriteObstaculo,
                           X+ mapaAtual.obstaculos[i].x*COEF,
                           Y+ mapaAtual.obstaculos[i].y*COEF,
                           TAM_OBSTACULO*COEF, TAM_OBSTACULO*COEF, 0);
        }
    }
}

void desenharMoedas(double X, double Y)
{
    for(int i=0; i<QTD_MAX_MOEDAS; i++)
    {
        if(mapaAtual.moedas[i].existe == 1 && individuo[0].moedas[i] == 0)
        {
            DesenharSprite(spriteMoeda,
                           X+mapaAtual.moedas[i].X,
                           Y+mapaAtual.moedas[i].Y,
                           TAM_OBSTACULO, TAM_OBSTACULO, 0);
        }
    }
}

void desenharPersonagens(double X, double Y)
{
    X = X - inicioCenarioX;
    Y = Y - inicioCenarioY;

    int i = 0;
    if(individuo[i].Morreu == 0)
    {
        DesenharSprite(spritePersonagem,
                       X + individuo[i].X + (TAM_PERSONAGEM/2.0),
                       Y + individuo[i].Y + (TAM_PERSONAGEM/2.0),
                       TAM_PERSONAGEM, TAM_PERSONAGEM, 0);
    }
}

void desenhar()
{
    int x = 300, y = 50;
    IniciarDesenho();

    if(id == 30)
    {
        DesenharRetangulo(0, 0, ALT_TELA, LARG_TELA, VERMELHO_FORA);
    }
    else
    {
        DesenharRetangulo(0, 0, ALT_TELA, LARG_TELA, AZUL_FORA);
    }

    desenharCenario(x, y);
    desenharBordas(x, y);
    desenharObstaculos(x,y);
    desenharPersonagens(x,y);
    desenharMoedas(x,y);

    EscreverEsquerda("F2 - Carregar próximo mapa", 25, 75, FontePreta);
    EscreverEsquerda("ENTER - Iniciar mapa", 25, 25, FontePreta);

    EncerrarDesenho();
}






void movimentarObstaculos()
{
    for(int i=0; i<QTD_MAX_OBSTACULOS; i++)
    {
        if(mapaAtual.obstaculos[i].existe == 1 && mapaAtual.obstaculos[i].quantidadeCaminhos != 0)
        {
            double vx, vy;
            Obstaculo* obs = &mapaAtual.obstaculos[i];
            int caminho = obs->caminhoAtual;

            double dist = DistanciaEntrePontos(obs->x, obs->y, obs->caminho[caminho].destinoX, obs->caminho[caminho].destinoY);
            if(obs->caminho[caminho].angular == 1)
            {
                double ang = AnguloEntrePontos    (obs->caminho[caminho].destinoX, obs->caminho[caminho].destinoY, obs->x, obs->y);
                double raio = DistanciaEntrePontos(obs->x, obs->y, obs->caminho[caminho].destinoX, obs->caminho[caminho].destinoY);
                double direcao = obs->caminho[caminho].direcaoAtual;

                ang = ang + direcao*obs->caminho[caminho].velocidade;

                /// Swap
                obs->caminho[caminho].anguloSwapAtual = obs->caminho[caminho].anguloSwapAtual - fabs(obs->caminho[caminho].velocidade);
                if(obs->caminho[caminho].anguloSwapAtual <= 0 && obs->caminho[caminho].anguloSwap != -1)
                {
                    obs->caminho[caminho].anguloSwapAtual = obs->caminho[caminho].anguloSwap;
                    obs->caminho[caminho].direcaoAtual = -obs->caminho[caminho].direcaoAtual;
                }

                /// Parada
                if(obs->caminho[caminho].anguloParada != -1)
                {
                    if(obs->caminho[caminho].anguloParadaAtual <= 0)
                    {
                        obs->caminho[caminho].IteracoesParadoAtual++;
                        if(obs->caminho[caminho].IteracoesParadoAtual == obs->caminho[caminho].IteracoesParado)
                        {
                            obs->caminho[caminho].IteracoesParadoAtual = 0;
                            obs->caminho[caminho].anguloParadaAtual = obs->caminho[caminho].anguloParada;
                        }
                        ang = ang - direcao*obs->caminho[caminho].velocidade;
                        obs->caminho[caminho].anguloSwapAtual = obs->caminho[caminho].anguloSwapAtual + fabs(obs->caminho[caminho].velocidade);
                    }
                    else
                    {
                        obs->caminho[caminho].anguloParadaAtual = obs->caminho[caminho].anguloParadaAtual - fabs(obs->caminho[caminho].velocidade);
                        if(obs->caminho[caminho].anguloParadaAtual <= 0)
                        {
                            if(obs->caminho[caminho].IteracoesParadoAtual == 0)
                            {
                                ang = ang + obs->caminho[caminho].anguloParadaAtual;
                            }
                        }
                    }
                }

                obs->x = obs->caminho[caminho].destinoX + raio*cos(DEGTORAD*ang);
                obs->y = obs->caminho[caminho].destinoY + raio*sin(DEGTORAD*ang);
            }
            else
            {
                double distAnterior = DistanciaEntrePontos(obs->x, obs->y, obs->caminho[caminho].destinoX, obs->caminho[caminho].destinoY);
                double velocidade = obs->caminho[caminho].velocidade;
                double xAnterior = obs->x;
                double yAnterior = obs->y;

                if(fabs(espacoReservado[i]) >= velocidade)
                {
                    if(espacoReservado[i] > 0)
                    {
                        espacoReservado[i] = espacoReservado[i] - velocidade;
                        velocidade = 0;
                    }
                    if(espacoReservado[i] < 0)
                    {
                        espacoReservado[i] = espacoReservado[i] + velocidade;
                        velocidade = 2.0*velocidade;
                    }
                }

                vx = velocidade * ((obs->caminho[caminho].destinoX - obs->x)/(distAnterior));
                vy = velocidade * ((obs->caminho[caminho].destinoY - obs->y)/(distAnterior));

                obs->x = obs->x + vx;
                obs->y = obs->y + vy;

                double distPosterior = DistanciaEntrePontos(obs->x, obs->y, obs->caminho[caminho].destinoX, obs->caminho[caminho].destinoY);
                double distAnteriorPosterior = DistanciaEntrePontos(obs->x, obs->y, xAnterior, yAnterior);

                if(distPosterior < obs->caminho[caminho].velocidade)
                {
                    obs->x = obs->caminho[caminho].destinoX;
                    obs->y = obs->caminho[caminho].destinoY;

                    if(distAnteriorPosterior < distAnterior)
                    {
                        espacoReservado[i] = espacoReservado[i] + distPosterior;
                    }
                    if(distAnteriorPosterior > distAnterior)
                    {
                        espacoReservado[i] = espacoReservado[i] - distPosterior;
                    }

                    obs->caminhoAtual++;
                    if(obs->caminhoAtual == obs->quantidadeCaminhos)
                    {
                        obs->caminhoAtual = 0;
                    }
                }
            }
        }
    }
}

void reiniciarObstaculos()
{
    for(int i=0; i<QTD_MAX_OBSTACULOS; i++)
    {
        if(mapaAtual.obstaculos[i].existe == 1)
        {
            mapaAtual.obstaculos[i].x = mapaAtual.obstaculos[i].xInicial;
            mapaAtual.obstaculos[i].y = mapaAtual.obstaculos[i].yInicial;
            mapaAtual.obstaculos[i].caminhoAtual = 0;
            espacoReservado[i] = 0;

            for(int j=0; j<mapaAtual.obstaculos[i].quantidadeCaminhos; j++)
            {
                mapaAtual.obstaculos[i].caminho[j].anguloSwapAtual      = mapaAtual.obstaculos[i].caminho[j].anguloSwap;
                mapaAtual.obstaculos[i].caminho[j].anguloParadaAtual    = mapaAtual.obstaculos[i].caminho[j].anguloParada;
                mapaAtual.obstaculos[i].caminho[j].direcaoAtual         = mapaAtual.obstaculos[i].caminho[j].direcao;
                mapaAtual.obstaculos[i].caminho[j].IteracoesParadoAtual = 0;
            }
        }
    }
}

void definirQuantidadeBlocos(int quantidade)
{
    QTD_BLOCOS = quantidade;
    TAM_BLOCOS = ALT_TELA/QTD_BLOCOS;
    TAM_PERSONAGEM = (TAM_BLOCOS*(24.0/32.0));
    TAM_OBSTACULO = (TAM_BLOCOS*(17.0/32.0));

    inicioCenarioX = (LARG_TELA-(QTD_BLOCOS*TAM_BLOCOS))/2;
    inicioCenarioY = (ALT_TELA-(QTD_BLOCOS*TAM_BLOCOS))/2;
}




void inicializarMatrizColisao()
{
    for(int i=0; i<LARG_TELA; i++)
    {
        for(int j=0; j<ALT_TELA; j++)
        {
            int x = (double)(i-inicioCenarioX)/(double)TAM_BLOCOS;
            int y = (double)(j-inicioCenarioY)/(double)TAM_BLOCOS;

            if(mapaAtual.cenario[x][y] == VAZIO)
            {
                matrizColisao[i][j] = 0;
            }
            else
            {
                matrizColisao[i][j] = 1;
            }
        }
    }
}

void adicionarColisao(double X, double Y, double Altura, double Largura)
{
    X = X + inicioCenarioX;
    Y = Y + inicioCenarioY;
    for(int i=X; i<X+Largura; i++)
    {
        for(int j=Y; j<Y+Altura; j++)
        {
            matrizColisao[i][j] = 0;
        }
    }
}

void incluirColisaoParedes()
{
    for(int i=0; i<QTD_BLOCOS; i++)
    {
        for(int j=0; j<QTD_BLOCOS; j++)
        {
            if(mapaAtual.cenario[i][j] == VAZIO)
            {
                if(i+1 < QTD_BLOCOS && mapaAtual.cenario[i+1][j] != VAZIO)
                {
                    adicionarColisao(    (i+1)*TAM_BLOCOS - LARGURA_BORDA,
                                             j*TAM_BLOCOS,
                                               TAM_BLOCOS, LARGURA_BORDA);

                    if(mapaAtual.cenario[i+1][j+1] == VAZIO)
                    {
                        adicionarColisao(  (i+1)*TAM_BLOCOS - LARGURA_BORDA,
                                            (j+1)*TAM_BLOCOS,
                                                  LARGURA_BORDA, LARGURA_BORDA);
                    }

                    if(mapaAtual.cenario[i+1][j-1] == VAZIO)
                    {
                        adicionarColisao(  (i+1)*TAM_BLOCOS - LARGURA_BORDA,
                                              (j)*TAM_BLOCOS - LARGURA_BORDA,
                                                  LARGURA_BORDA, LARGURA_BORDA);
                    }

                }
                if(i-1 >= 0 && mapaAtual.cenario[i-1][j] != VAZIO)
                {
                    adicionarColisao((i)*TAM_BLOCOS,
                                        j*TAM_BLOCOS,
                                          TAM_BLOCOS, LARGURA_BORDA);

                    if(mapaAtual.cenario[i-1][j+1] == VAZIO)
                    {
                        adicionarColisao((i)*TAM_BLOCOS,
                                        (j+1)*TAM_BLOCOS,
                                        LARGURA_BORDA, LARGURA_BORDA);
                    }

                    if(mapaAtual.cenario[i-1][j-1] == VAZIO)
                    {
                        adicionarColisao((i)*TAM_BLOCOS,
                                          (j)*TAM_BLOCOS - LARGURA_BORDA,
                                        LARGURA_BORDA, LARGURA_BORDA);
                    }
                }
//
//
                if(j+1 < QTD_BLOCOS && mapaAtual.cenario[i][j+1] != VAZIO)
                {
                    adicionarColisao(i*TAM_BLOCOS,
                                     (j+1)*TAM_BLOCOS - LARGURA_BORDA,
                                      LARGURA_BORDA, TAM_BLOCOS);
                }
                if(j-1 >= 0 && mapaAtual.cenario[i][j-1] != VAZIO)
                {
                    adicionarColisao(i*TAM_BLOCOS,
                                     (j)*TAM_BLOCOS,
                                     LARGURA_BORDA, TAM_BLOCOS);
                }
            }
        }
    }
}





void inicializarIndividuo(int i, double X, double Y)
{
    individuo[i].X = X;
    individuo[i].Y = Y;
    individuo[i].Morreu = 0;
    individuo[i].Ganhou = 0;

    for(int j=0; j<QTD_MAX_MOEDAS; j++)
    {
        individuo[i].moedas[j] = 0;
    }
    individuo[i].cor = i;
}

void inicializarIndividuos()
{
    int i = 0;
    inicializarIndividuo(i, mapaAtual.inicioX + inicioCenarioX - TAM_PERSONAGEM/2,
                            mapaAtual.inicioY + inicioCenarioY - TAM_PERSONAGEM/2);

}

void inicializarPartida()
{
    inicializarIndividuos();
    reiniciarObstaculos();
}

void definirQuantidadeObstaculos()
{
    quantidadeObstaculosCenario = 0;
    for(int i=0; i<QTD_MAX_OBSTACULOS; i++)
    {
        if(mapaAtual.obstaculos[i].existe == 1)
        {
            quantidadeObstaculosCenario++;
        }
    }
}

void definirQuantidadeMoedas()
{
    quantidadeMoedasCenario = 0;
    for(int i=0; i<QTD_MAX_MOEDAS; i++)
    {
        if(mapaAtual.moedas[i].existe == 1)
        {
            quantidadeMoedasCenario++;
        }
    }
}


int carregarMapa(int id)
{
    char String[1000];
    sprintf(String,"mapas\\mapa%d",id);

    FILE* f = fopen(String,"rb");
    if(f == NULL)
    {
        return 1;
    }
    else
    {
        fread(&mapaAtual, 1, sizeof(Mapa), f);
        fclose(f);

        mapaBackup = mapaAtual;

        definirQuantidadeBlocos(mapaAtual.quantidadeBlocos);
        definirQuantidadeObstaculos();
        definirQuantidadeMoedas();

        inicializarMatrizColisao();
        incluirColisaoParedes();

        inicializarPartida();

        mapaIniciado = -1;

        return 0;
    }
}

int buscarIdVazio()
{
    char String[1000];
    int id = 0;

    while(1)
    {
        sprintf(String,"mapa%d",id);
        FILE* f = fopen(String,"rb");
        if(f == NULL)
        {
            return id;
        }
        else
        {
            id++;
            fclose(f);
        }
    }
}

/// -------------------------------

void movimentarPersonagem(int ID, int Cima, int Baixo, int Esquerda, int Direita)
{
    if(individuo[ID].Morreu == 1 || individuo[ID].Ganhou == 1)
    {
        return;
    }

    double velocidade = 1.0;
    double TamanhoPersonagem = TAM_PERSONAGEM-2;

    double X = individuo[ID].X;
    double Y = individuo[ID].Y;

    double XmaisVelo =  X + velocidade;
    double XmenosVelo = X - velocidade;
    double YmaisVelo =  Y + velocidade;
    double YmenosVelo = Y - velocidade;

    double XFinal = XmaisVelo + TamanhoPersonagem;
    double YFinal = YmaisVelo + TamanhoPersonagem;

    if(Cima == 1)
    {
        if(matrizColisao[(int)X][(int)YFinal] == 1 &&
           matrizColisao[(int)(X+TamanhoPersonagem)][(int)YFinal] == 1)
        {
            individuo[ID].Y = YmaisVelo;
        }
    }
    if(Baixo == 1)
    {
        if(matrizColisao[(int)X][(int)YmenosVelo] == 1 &&
           matrizColisao[(int)(X+TamanhoPersonagem)][(int)YmenosVelo] == 1)
        {
            individuo[ID].Y = YmenosVelo;
        }
    }
    if(Esquerda == 1)
    {
        if(matrizColisao[(int)XmenosVelo][(int)Y] == 1 &&
           matrizColisao[(int)XmenosVelo][(int)(Y+TamanhoPersonagem)] == 1)
        {
            individuo[ID].X = XmenosVelo;
        }
    }
    if(Direita == 1)
    {
        if(matrizColisao[(int)XFinal][(int)Y] == 1 &&
           matrizColisao[(int)XFinal][(int)(Y+TamanhoPersonagem)] == 1)
        {
            individuo[ID].X = XmaisVelo;
        }
    }
}

void detectarColisaoInimigos()
{
    int i = 0;
    for(int j=0; j<quantidadeObstaculosCenario; j++)
    {
        if(individuo[i].Morreu == 0 && individuo[i].Ganhou == 0)
        {
            double xNo = (int)individuo[i].X + (TAM_PERSONAGEM/2.0);
            double yNo = (int)individuo[i].Y + (TAM_PERSONAGEM/2.0);
            double xObs = mapaAtual.obstaculos[j].x + inicioCenarioX;
            double yObs = mapaAtual.obstaculos[j].y + inicioCenarioY;
            double Raio = TAM_PERSONAGEM/2.0 + TAM_OBSTACULO/2.0;

            if(DistanciaEntrePontos(xNo, yNo, xObs, yObs) < Raio)
            {
                if(individuo[i].Ganhou == 0)
                {
                    individuo[i].Morreu = 1;
                    inicializarIndividuo(i, mapaAtual.inicioX + inicioCenarioX - TAM_PERSONAGEM/2,
                                            mapaAtual.inicioY + inicioCenarioY - TAM_PERSONAGEM/2);

                }
            }
        }
    }
}

void carregarProximoMapa()
{
    int erro = carregarMapa(id);
    if(erro == 1)
    {
        id = 0;
        carregarMapa(id);
    }
    id++;
}

void detectarColisaoChegada()
{
    int obstaculosVerificados;

    int i = 0;
    int contarMoedas = 0;

    for(int j=0; j<QTD_MAX_MOEDAS; j++)
    {
        if(individuo[i].moedas[j] == 1)
            contarMoedas++;
    }

    double dist = DistanciaEntrePontos( individuo[i].X,
                                        individuo[i].Y,
                                        mapaAtual.finalX + inicioCenarioX,
                                        mapaAtual.finalY + inicioCenarioY);
    if(dist < 10 &&
       individuo[i].Morreu == 0 &&
       individuo[i].Ganhou == 0 &&
       contarMoedas == quantidadeMoedasCenario)
    {
        individuo[i].Ganhou = 1;
    }
}

void detectarColisaoMoeda()
{
    int i = 0;
    for(int j=0; j<quantidadeMoedasCenario; j++)
    {
        if(individuo[i].moedas[j] == 0)
        {
            if(DistanciaEntrePontos(individuo[i].X + (TAM_PERSONAGEM/2.0),
                                    individuo[i].Y + (TAM_PERSONAGEM/2.0),
                                    mapaAtual.moedas[j].X + inicioCenarioX,
                                    mapaAtual.moedas[j].Y + inicioCenarioY) < 15)
            {
                individuo[i].moedas[j] = 1;
            }
        }
    }
}

void inicializarMapaAtual()
{
    for(int i=0; i<QTD_BLOCOS; i++)
    {
        for(int j=0; j<QTD_BLOCOS; j++)
        {
            mapaAtual.cenario[i][j] = VAZIO;
        }
    }

    for(int i=0; i<QTD_MAX_OBSTACULOS; i++)
    {
        mapaAtual.obstaculos[i].existe = 0;
    }

    for(int i=0; i<QTD_MAX_MOEDAS; i++)
    {
        mapaAtual.moedas[i].existe = 0;
    }

    for(int i=0; i<QTD_MAX_PIVO; i++)
    {
        mapaAtual.pivo[i].existe = 0;
    }

    mapaAtual.finalX = -1;
    mapaAtual.finalY = -1;
    mapaAtual.inicioX = -1;
    mapaAtual.inicioY = -1;
    mapaAtual.quantidadeBlocos = 22;
}

void inicializarSprites()
{
    spritePersonagem = CriarSprite("imagens\\personagem.bmp", 1);

    spriteObstaculo = CriarSprite("imagens\\obstaculo.bmp");
    DefinirColoracao(spriteObstaculo, AZUL);

    spriteMoeda = CriarSprite("imagens\\obstaculo.bmp");
    DefinirColoracao(spriteMoeda,AMARELO);

    spriteInicio = CriarSprite("imagens\\inicio.png");
    spriteFinal = CriarSprite("imagens\\final.png");
    spriteX = CriarSprite("imagens\\x1.png");
    spriteLuzAzul = CriarSprite("imagens\\luzBranca.png",0);
    spriteLuzVermelha = CriarSprite("imagens\\luzBranca.png",0);
    spriteLuzAmarela = CriarSprite("imagens\\luzBranca.png",0);

    DefinirColoracao(spriteLuzAzul, AZUL);
}

void processarTeclado()
{
    if(PIG_Tecla == TECLA_ENTER)
    {
        mapaIniciado = -mapaIniciado;
    }

    if(PIG_Tecla == TECLA_F2)
    {
        carregarProximoMapa();
    }
}


void configuracoesIniciais()
{
    CriarJanela("Hardest Game", 0);

    Periodo = 0.01;
    mapaIniciado = -1;

    inicializarSprites();

    TimerGeral = CriarTimer();

    FontePreta = CriarFonteNormal("..\\fontes\\arial.ttf", 20, PRETO, 0, PRETO);

    inicializarMapaAtual();
}

void verificarTeclas()
{
    if(PIG_meuTeclado[TECLA_ESQUERDA])
    {
        movimentarPersonagem(0, 0, 0, 1, 0);
    }
    if(PIG_meuTeclado[TECLA_DIREITA])
    {
        movimentarPersonagem(0, 0, 0, 0, 1);
    }
    if(PIG_meuTeclado[TECLA_CIMA])
    {
        movimentarPersonagem(0, 1, 0, 0, 0);
    }
    if(PIG_meuTeclado[TECLA_BAIXO])
    {
        movimentarPersonagem(0, 0, 1, 0, 0);
    }
}

int main(int argc, char* args[])
{
    configuracoesIniciais();

    while(PIG_JogoRodando == 1)
    {
        AtualizarJanela();
        processarTeclado();

        if(TempoDecorrido(TimerGeral) >= Periodo)
        {
            if(mapaIniciado == 1)
            {
                verificarTeclas();
                movimentarObstaculos();
                detectarColisaoInimigos();
                detectarColisaoMoeda();
                detectarColisaoChegada();
            }
            desenhar();

            ReiniciarTimer(TimerGeral);
        }
    }
    FinalizarJanela();

    return 0;
}
