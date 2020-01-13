
typedef struct charger
{
    int Obj;

    int TipoCarga;
    int ControleDeColisao;
    float Carga;

    float PosicaoX;
    float PosicaoY;
    float VelocidadeX;
    float VelocidadeY;
    float AceleracaoX;
    float AceleracaoY;
    float ForcaX;
    float ForcaY;
    float Largura;
    float Altura;

    float TrajetoriaX[TrajetoriaMax+10];
    float TrajetoriaY[TrajetoriaMax+10];
    int TotalTrajetoria;
    int IndiceTrajetoria;
    PIG_Cor TrajetoriaCor;

    struct charger* Proximo;

}   Charger;

typedef struct animation
{
    int X;
    int Y;
    int Largura;
    int Altura;
    float Angulo;

    int Ativada;
    int FrameAtual;
    int QuantidadeFrames;

}   Animation;

typedef struct ponto
{
    float X;
    float Y;
    float Z;
    PIG_Cor Cor;

}   Ponto;

typedef struct vetor
{
    Ponto Origem;
    Ponto Destino;
    PIG_Cor Cor;

    float Carga;

}   Vetor;
