/********************************
A função DefineFundo() permite escolher um arquivo de imagem como fundo (background) do jogo que será automaticamente desenhado a cada nova etapa de desenho na tela.
Parâmetros:
nome_ArquivoImagem (entrada, passagem por referência*): indica o caminho relativo ou absoluto do arquivo de imagem que será utilizado como fundo do jogo.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void DefinirFundo(char *nome_ArquivoImagem)
{
    jogo->DefineFundo(nome_ArquivoImagem);
}

/********************************
A função GetTeclado() faz um mapeamento entre o teclado físico a uma variável do tipo PIG_Teclado que funciona como um vetor de variáveis lógicas,
sendo cada posição do vetor relativo a uma tecla física.
Uma lista das possíveis teclas e seus código pode ser vista no arquivo Tipos_PIG.h.
Retorno:
O valor de retorno da função é um vetor de números inteiros que indicam se uma determinada tecla (índice do vetor) foi
pressionada (valor diferente de 0,zero) ou não (valor igual a zero).
********************************/
PIG_Teclado PegarTeclado()
{
    return jogo->PegaTeclado();
}

/********************************
A função CriaJogo() é responsável pela criação da janela do jogo e pelos componentes audio-visuais.
Ela deve ser chamada antes de qualquer outra função da biblioetac PIG.h. Não é possível criar dois
jogos no mesmo progama. Logo, somente a primeira chamada terá efeito.
Parâmetros:
nome_Janela (entrada, passagem por referência*): indica o nome que a janela do jogo mostrará no seu título.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
cursor_Proprio (entrada, passagem por valor): indica se o jogo utilizará cursores (ponteiros) próprios para o mouse ou utilizará o cursor padrão.
********************************/
void CriarJanela(char *nome_Janela,int cursor_Proprio=0)
{
    if (jogo==NULL){
        jogo = new CJogo(nome_Janela,cursor_Proprio);
        CAssetLoader::Inicia();
        if (cursor_Proprio!=0)
            CMouse::Inicia(jogo->renderer);
        CGerenciadorTimers::Inicia();
        CGerenciadorObjetos::Inicia(jogo->renderer);
        CGerenciadorParticulas::Inicia(jogo->renderer);
        CGerenciadorAnimacoes::Inicia(jogo->renderer);
        PIG_meuTeclado = PegarTeclado();
        PIG_JogoRodando = 1;
        srand(time(NULL));
    }
}

/********************************
A função GetEvento() indica se houve algum tipo de evento desde a última vez que a função foi chamada.
Um evento pode ser uma tecla pressionada, um clique do mouse ou outra coisa relacionada à tela do jogo.
Maiores informaçõe podem ser vistas no arquivo Tipo_PIG.h
Retorno:
O valor de retorno é um struct contendo o tipo de evento ocorrido e vários outros structs com informações específicas.
********************************/
PIG_Evento PegarEvento()
{
    return jogo->PegaEvento();
}

/********************************
A função IniciaDesenho() é responsável por preparar a janela do jogo para que os objetos gráficos
possam ser mostrados, além de desenhar a imagem de fundo do jogo, caso tenha sido definida.
Deve ser chamada repetidamente a cada novo quadro (frame) a ser desenhado.
********************************/
void IniciarDesenho()
{
    jogo->IniciaDesenho();
}

/********************************
A função EncerraDesenho() é responsável por encerrar o desenho que foi criado, mostrando na tela do jogo.
Deve ser chamado sempre ao final do loop principal do jogo.
********************************/
void EncerrarDesenho()
{
    if (jogo->cursorPadrao!=0)
        CMouse::Desenha();
    jogo->EncerraDesenho();
}

/********************************
A função PegarTecla reconhece a tecla apertada ou soltada(cima,baixo,esquerda,direita,enter,esc,z,x) e retorna um codigo.

Apertar = Positivo
Soltar = Negativo

********************************/

int PegarTecla()
{
    int i;

    if(PIGTeclasControle == 0)
    {
        if(PIG_evento.teclado.acao == 768)
        {
            for(i=0; i<SDL_NUM_SCANCODES; i++)
            {
                if(PIG_meuTeclado[i] == 1)
                {
                    PIGTeclasReturn = i;
                    PIGTeclasControle = 1;
                    return i;
                }
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if(PIG_evento.teclado.acao == 769)
        {
            for(i=0; i<SDL_NUM_SCANCODES; i++)
            {
                if(PIGTeclasReturn == i && PIG_meuTeclado[i] == 0)
                {
                    PIGTeclasControle = 0;
                    return -i;
                }
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
}

int PegarBotao()
{
    static int Controle = 0;
    if(PIG_evento.mouse.acao == 1025)
    {
        Controle = 1;
    }
    else
    {
        if(PIG_evento.mouse.acao == 1026 && Controle == 1)
        {
            if(PIG_evento.mouse.botao == 1)
            {
                Controle = 0;
                return 1;
            }
            else
            {
                if(PIG_evento.mouse.botao == 2)
                {
                    Controle = 0;
                    return 2;
                }
                else
                {
                    Controle = 0;
                    return 3;
                }
            }
        }
    }
    return 0;
}

/********************************
A função AtualizarEstadoJogo() é reponsável por retornar se o jogo ainda está ativo ou não.
O jogo será encerrado se a janela do jogo for fechada, por exemplo.
Retorno:
inteiro que indica se o jogo ainda está sendo executado (valor diferente de zero) ou não (valor igual a 0, zero).
********************************/

int AtualizarJanela()
{
    PIG_evento = PegarEvento();
    if(PIG_JogoRodando != 0)
    {
        PIG_JogoRodando = jogo->GetRodando();
    }
    PIG_Tecla = PegarTecla();
    PIG_Botao = PegarBotao();
}

/********************************
A função Espera() "congela" a tela do jogo por alguns milisegundos, impedindo que qualquer outro comando seja executado enquanto isso.
Parâmetros:
tempo (entrada, passagem por valor): indica a quantidade de milisegundos durante a qual o jogo será pausado.
********************************/
void Esperar(int tempo)
{
    SDL_Delay(tempo);
}

/********************************
A função FinalizaJogo() é responsável por encerrar com a PIG. Após tudo o jogo ser executado
a função deve ser chamada e ela irá realizar a liberação de memória dos elementos criados pela PIG.
********************************/
void FinalizarJanela()
{
    CGerenciadorAnimacoes::Encerra();
    CGerenciadorParticulas::Encerra();
    CGerenciadorObjetos::Encerra();
    CGerenciadorTimers::Encerra();
    if (jogo->cursorPadrao==0)
        CMouse::Encerra();
    CAssetLoader::Encerra();
    delete jogo;
}

/********************************
A função GetFPS() é responsável por calcular o valor do Frames Per Seconds (FPS), que representa a quantidade de
frames (quadros) desenhados por segundo pela PIG.
Retorno:
float que indica a média de quadros desenhados por segundo.
********************************/
float PegarFPS()
{
    return jogo->GetFPS();
}

/********************************
A função CarregaCursor() é responsável por armazenar um novo cursor para o mouse, dado pelo arquivo de imagem indicado.
O arquivo deve ser uma imagem com 32 pixels de altura orbigatoriamente.
Parâmetro:
indice (entrada, passagem por valor): informa um índice para este novo cursor. Se o índice já estiver sendo utilizado,
o cursor antigo é removido. O valor deve estar entre 0..MAX_CURSORES-1.
nomeArquivoCursor (entrada, passagem por referência*): indica o nome do arquivo de imagem que será utilziado como cursor do mouse.
É utilizado o operador * apenas por se tratar de um parâmetro string. O valor do parâmetro não é alterado dentro da função.
********************************/
void CarregarCursor(int indice,char *nomeArquivoCursor)
{
    CMouse::CarregaCursor(indice,nomeArquivoCursor);
}

/********************************
A função MudaCursor() é responsável por alterar o cursor atual do mouse por outro já carregado.
Parâmetro:
indice (entrada, passagem por valor): informa um índice para este novo cursor que já deve ter sido
carregado anteriormente e deve estar no intervalo 0..MAX_CURSORES-1.
********************************/
void MudarCursor(int indice)
{
    CMouse::MudaCursor(indice);
}
