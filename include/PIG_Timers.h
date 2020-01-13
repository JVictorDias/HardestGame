/********************************
Seção dos temporizadores
********************************/

/********************************
A função CriaTimer() é responsável por criar um timer (temporizador). Após a criação o tempo decorrido
poderá ser obtido a partir da função Tempo_Decorrido(), informando o identificador que é passado na resposta.
Retorno:
inteiro que identifica o timer criado.
********************************/
int CriarTimer()
{
    int timer;

    timer = CGerenciadorTimers::CriaTimer();
    PIG_ExistenciaTimer[timer] = 1;
    return timer;
}

/********************************
A função TempoDecorrido() é responsável por informar o tempo decorrido desde a criação do timer
até a hora em que a função for chamada.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
Retorno:
número real indicando o tempo (em segundos) desde a criação do timer.
********************************/
double TempoDecorrido(int id_timer)
{
    if(PIG_ExistenciaTimer[id_timer] == 1)
    {
        return CGerenciadorTimers::GetTempoDecorrido(id_timer);
    }
}

int TimerCriado(int id_timer)
{
    if(PIG_ExistenciaTimer[id_timer] == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/********************************
A função PausaTimer() é responsável por realizar uma pausa na contagem do tempo de um timer. Após a despausa,
o timer continuará a contar o tempo normalmente.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void PausarTimer(int id_timer)
{
    if(PIG_ExistenciaTimer[id_timer] == 1)
    {
        CGerenciadorTimers::PausaTimer(id_timer);
    }
}

/********************************
A função PausaTudo() é responsável por realizar uma pausa na contagem do tempo de todos os timers
criados pela função CriaTimer();
********************************/
void PausarTudo()
{
    CGerenciadorTimers::PausaTodos();
}

/********************************
A função DespausaTimer() é responsável por retomar a contagem do tempo de um timer após uma pausa.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void DespausarTimer(int id_timer)
{
    if(PIG_ExistenciaTimer[id_timer] == 1)
    {
        CGerenciadorTimers::DespausaTimer(id_timer);
    }
}

/********************************
A função DespausaTudo() é responsável por retomar a contagem do tempo de todos os timers
criados pela função CriaTimer();
********************************/
void DespausarTudo()
{
    CGerenciadorTimers::DespausaTodos();
}

/********************************
A função ReiniciaTimer() é responsável por zerar a contagem do tempo de um timer, idependente do tempo já decorrido.
Na prática, é equivalente a encerrer um temporizador e recriá-lo em seguida.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void ReiniciarTimer(int id_timer)
{
    if(PIG_ExistenciaTimer[id_timer] == 1)
    {
        CGerenciadorTimers::ReiniciaTimer(id_timer);
    }
}

/********************************
A função DestroiTimer() é responsável por encerrar a utilização de timer.
Seu identificador não poderá ser utilizado após a função ser executada.
Parâmetros:
id_timer (entrada, passagem por valor): identificador do timer.
********************************/
void DestruirTimer(int id_timer)
{
    if(PIG_ExistenciaTimer[id_timer] == 1)
    {
        PIG_ExistenciaTimer[id_timer] = 0;
        CGerenciadorTimers::DestroiTimer(id_timer);
    }
}
