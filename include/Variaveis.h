
    Charger*            Particulas = NULL;
    Animation           ListaExplosoes[MAX_EXPLOSOES];

    Vetor               Espaco[LARG_TELA+1][ALT_TELA+1];

    int                 CampoObjetos[LARG_TELA+1][ALT_TELA+1];

    int                 TimerGeral = 0;
    int                 TimerAvisos = 0;
    int                 TimerAnimation = 0;
    char                StringAvisos[100];

    int                 MovimentoEsferas = 1;
    int                 DesenharVetoresTrajetorias = -1;
    int                 DesenharGrade = 0;
    int                 ColisaoAtivada = 0;

    int                 DistanciaVetoresEspaciais = 20;

    float               Periodo = 0.01;
