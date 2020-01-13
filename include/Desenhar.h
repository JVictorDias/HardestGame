
Charger* DesenharParticula(Charger* Lista)
{
    if(Lista != NULL)
    {
        DesenharParticula(Lista->Proximo);
        DesenharObjeto(Lista->Obj);
    }
}

Charger* DesenharTrajetorias(Charger* Lista)
{
    int i,j;
    if(Lista != NULL)
    {
        SDL_Point Pontos[TrajetoriaMax];
        for(i=0; i<Lista->TotalTrajetoria; i++)
        {
            j = ((i+Lista->IndiceTrajetoria)%Lista->TotalTrajetoria);
            Pontos[i].x = XRealParaVirtual              (Lista->TrajetoriaX[j],Lista->TrajetoriaY[j]);
            Pontos[i].y = ALT_TELA - YRealParaVirtual   (Lista->TrajetoriaX[j],Lista->TrajetoriaY[j],0);
        }
        DesenharLinhas(Pontos,Lista->TotalTrajetoria,Lista->TrajetoriaCor);
        DesenharTrajetorias(Lista->Proximo);
    }
}

void DesenharCampoVetorial()
{
    int i,j;
    Charger* it;

    ResetarCampo();

    for(it=Particulas; it!=NULL; it=it->Proximo)
    {
        DistorcerCampo(it);
    }
    //NormalizarCampo();

    for(i=0; i<(LARG_TELA/DistanciaVetoresEspaciais)+1; i++)
    {
        for(j=0; j<(ALT_TELA/DistanciaVetoresEspaciais)+1; j++)
        {
            DefinirAngulo(CampoObjetos[i][j],AnguloEntrePontos(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y,Espaco[i][j].Destino.X,Espaco[i][j].Destino.Y));

            if(DesenharGrade == 1)
            {
                DefinirColoracao(CampoObjetos[i][j],((PIG_Cor){0,255,0,255}));
                DefinirOpacidade(CampoObjetos[i][j],255);
            }
            else
            {
                ParticulaMenosDistante(i,j);
                DefinirCorCampo(i,j);
                DefinirColoracao(CampoObjetos[i][j],Espaco[i][j].Cor);
                DefinirOpacidade(CampoObjetos[i][j],Espaco[i][j].Cor.a);
            }
            DesenharObjeto(CampoObjetos[i][j]);


            //if(Espaco[i][j].Origem.X == Espaco[i][j].Destino.X && Espaco[i][j].Origem.Y == Espaco[i][j].Destino.Y)
            //{
                //DesenharPonto(XRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), YRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), 1, Espaco[i][j].Cor);
            //}
            //else
            //{
                //DesenharLinhaSimples(XRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), YRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), XRealParaVirtual(Espaco[i][j].Destino.X,Espaco[i][j].Destino.Y), YRealParaVirtual(Espaco[i][j].Destino.X,Espaco[i][j].Destino.Y), Espaco[i][j].Cor);
            //}
        }
    }
}

void DesenharLinhaDoCampo(Charger* Particula, float Angulo)
{
    float X = Particula->PosicaoX + (Particula->Largura/2.0)*cos(M_Radi*Angulo);
    float Y = Particula->PosicaoY + (Particula->Altura/2.0)*sin(M_Radi*Angulo);
    float XFinal, YFinal;
    int Contador = 1;

    SDL_Point Points[2050];
    Charger* i;

    Points[0].x = X;
    Points[0].y = ALT_TELA - Y;
    while(1)
    {
        for(i=Particulas; i!=NULL; i=i->Proximo)
        {
            if(i->Obj != Particula->Obj)
            {
                if(DistanciaEntrePontos(X,Y,i->PosicaoX,i->PosicaoY) <= i->Largura/2.0)
                {
                    DesenharLinhas(Points,Contador,BRANCO);
                    return;
                }
            }
        }

        if(X > 2*LARG_TELA || X < -LARG_TELA || Y > 2*ALT_TELA || Y < -ALT_TELA)
        {
            DesenharLinhas(Points,Contador,BRANCO);
            return;
        }

        if(Contador > 2000)
        {
            DesenharLinhas(Points,Contador,BRANCO);
            return;
        }

        CalcularPontoFinal(X,Y,&XFinal,&YFinal);
        NormalizarVetor(X,Y,&XFinal,&YFinal);

        if(Particula->TipoCarga == -1)
        {
            XFinal = X - (XFinal - X);
            YFinal = Y - (YFinal - Y);
        }

        //DesenharLinhaSimples(X, Y, XFinal, YFinal, BRANCO);

        X = XFinal;
        Y = YFinal;

        Points[Contador].x = X;
        Points[Contador].y = ALT_TELA - Y;

        Contador = Contador + 1;
    }
}

void DesenharLinhasDoCampo(Charger* Particula)
{
    int i;
    if(Particula != NULL)
    {
        if(Particula->TipoCarga == 1)
        {
            for(i=0;i<10;i++)
            {
                DesenharLinhaDoCampo(Particula, i*36 + 18.0);
            }
        }
        else
        {
            for(i=0;i<10;i++)
            {
                DesenharLinhaDoCampo(Particula, i*36);
            }
        }

        DesenharLinhasDoCampo(Particula->Proximo);
    }

    //int i, j;
    //int m, n;
    //float A;
    //Charger* it;

    //ResetarCampo();
    //for(it=Particulas; it!=NULL; it=it->Proximo)
    {
        //DistorcerCampo(it);
    }
    //NormalizarCampo();

    //for(i=0; i<(LARG_TELA/DistanciaVetoresEspaciais)+1; i++)
    {
        //for(j=0; j<(ALT_TELA/DistanciaVetoresEspaciais)+1; j++)
        {
            //if(Espaco[i][j].Origem.X == Espaco[i][j].Destino.X && Espaco[i][j].Origem.Y == Espaco[i][j].Destino.Y)
            {
                //DesenharPonto(XRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), YRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), 1, Espaco[i][j].Cor);
            }
            //else
            {
                //DesenharLinhaSimples(XRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), YRealParaVirtual(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y), XRealParaVirtual(Espaco[i][j].Destino.X,Espaco[i][j].Destino.Y), YRealParaVirtual(Espaco[i][j].Destino.X,Espaco[i][j].Destino.Y), Espaco[i][j].Cor);
            }
        }
    }
}

void ProcurarIndice(float A, int* i, int* j)
{
    int Quadrante;

    Quadrante = A/45.0 + 1.0;
    if(A > 337.5)
        Quadrante = 1;

    *i = 1;
    *j = 1;

    if(Quadrante == 3 || Quadrante == 7)
        *i = 0;
    if(Quadrante == 4 || Quadrante == 5 || Quadrante == 6)
        *i = -*i;


    if(Quadrante == 1 || Quadrante == 5)
        *j = 0;
    if(Quadrante == 6 || Quadrante == 7 || Quadrante == 8)
        *j = -*j;
}

void Desenhar()
{
    int i,j;
    Charger* it;

    if(DesenharGrade == 1 || DesenharGrade == 2)
    {
        DesenharCampoVetorial();
    }
    if(DesenharGrade == 3)
    {
        DesenharLinhasDoCampo(Particulas);
    }

    if(DesenharVetoresTrajetorias == 1)
    {
        DesenharTrajetorias(Particulas);
    }

    DesenharParticula(Particulas);

    if(TempoDecorrido(TimerAvisos) <= 1.5)
    {
        EscreverEsquerda(StringAvisos,50,525,0);
    }
}
