
void ResetarCampo()
{
    int i, j;
    for(i=0; i<(LARG_TELA/DistanciaVetoresEspaciais)+1; i++)
    {
        for(j=0; j<(ALT_TELA/DistanciaVetoresEspaciais)+1; j++)
        {
            Espaco[i][j].Origem.X = DistanciaVetoresEspaciais*i;
            Espaco[i][j].Origem.Y = DistanciaVetoresEspaciais*j;
            Espaco[i][j].Destino.X = DistanciaVetoresEspaciais*i;
            Espaco[i][j].Destino.Y = DistanciaVetoresEspaciais*j;
            Espaco[i][j].Cor = ((PIG_Cor){0,255,0,255});
            Espaco[i][j].Carga = 0;
        }
    }
}

void DistorcerCampo(Charger* it)
{
    float Distancia,F;
    float cosAtual,senAtual, FcosAnterior, FsenAnterior;
    int i, j;

    float X = it->PosicaoX;
    float Y = it->PosicaoY;
    float MassaObj = it->Carga;

    for(i=0; i<(LARG_TELA/DistanciaVetoresEspaciais)+1; i++)
    {
        for(j=0; j<(ALT_TELA/DistanciaVetoresEspaciais)+1; j++)
        {
            Distancia = DistanciaEntrePontos(X, Y, Espaco[i][j].Origem.X, Espaco[i][j].Origem.Y);
            if(Distancia <= 25)
            {
                Distancia = 25;
            }

            if(it->TipoCarga == 1)
            {
                F = -(ConstanteUniversal)*(MassaObj)/(Distancia*Distancia);
            }
            else
            {
                F = (ConstanteUniversal)*(MassaObj)/(Distancia*Distancia);
            }

            cosAtual = ((X-Espaco[i][j].Origem.X)/(Distancia));
            senAtual = ((Y-Espaco[i][j].Origem.Y)/(Distancia));

            FcosAnterior = (Espaco[i][j].Destino.X - Espaco[i][j].Origem.X);
            FsenAnterior = (Espaco[i][j].Destino.Y - Espaco[i][j].Origem.Y);

            Espaco[i][j].Destino.X = (Espaco[i][j].Origem.X) + (F*cosAtual + FcosAnterior);
            Espaco[i][j].Destino.Y = (Espaco[i][j].Origem.Y) + (F*senAtual + FsenAnterior);
        }
    }
}

void NormalizarCampo()
{
    int i, j;
    for(i=0; i<(LARG_TELA/DistanciaVetoresEspaciais)+1; i++)
    {
        for(j=0; j<(ALT_TELA/DistanciaVetoresEspaciais)+1; j++)
        {
            float D = DistanciaEntrePontos(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y,Espaco[i][j].Destino.X,Espaco[i][j].Destino.Y);
            if(D == 0)
                D = 1;

            Espaco[i][j].Destino.X = Espaco[i][j].Origem.X + (DistanciaVetoresEspaciais*sqrt(2.0))*(Espaco[i][j].Destino.X - Espaco[i][j].Origem.X)/D;
            Espaco[i][j].Destino.Y = Espaco[i][j].Origem.Y + (DistanciaVetoresEspaciais*sqrt(2.0))*(Espaco[i][j].Destino.Y - Espaco[i][j].Origem.Y)/D;
        }
    }
}

void DefinirCorCampo(int i, int j)
{
    float Tamanho, Fx, Fy;
    float Verde, Vermelho;
    float Opacidade = 0;

    Fx = Espaco[i][j].Destino.X - Espaco[i][j].Origem.X;
    Fy = Espaco[i][j].Destino.Y - Espaco[i][j].Origem.Y;

    Tamanho = sqrt(Fx*Fx + Fy*Fy);

    Vermelho = (Tamanho)*10;

    if(Vermelho < 0)
        Vermelho = 0;
    if(Vermelho > 255)
        Vermelho = 255;

    Opacidade = 2*Vermelho;
    if(Opacidade > 255)
    {
        Opacidade = 255;
    }

    Verde = 255 - Vermelho;

    if(Espaco[i][j].Carga == 1)
    {
        Espaco[i][j].Cor = ((PIG_Cor){Verde,Verde,255,Opacidade});
    }
    if(Espaco[i][j].Carga == -1)
    {
        Espaco[i][j].Cor = ((PIG_Cor){255,Verde,Verde,Opacidade});
    }
}

void ParticulaMenosDistante(int i, int j)
{
    Charger* it;

    if(Particulas == NULL)
    {
        return;
    }

    float MenorDistancia = DistanciaEntrePontos(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y,Particulas->PosicaoX,Particulas->PosicaoY);
    float Carga = Particulas->TipoCarga;

    for(it=Particulas->Proximo; it!=NULL; it=it->Proximo)
    {
        float D = DistanciaEntrePontos(Espaco[i][j].Origem.X,Espaco[i][j].Origem.Y,it->PosicaoX,it->PosicaoY);
        if(D < MenorDistancia)
        {
            MenorDistancia = D;
            Carga = it->TipoCarga;
        }
    }
    Espaco[i][j].Carga = Carga;
}

void CalcularPontoFinal(float X, float Y, float* XFinal, float* YFinal)
{
    float Distancia,F;
    float cosAtual,senAtual, FcosAnterior, FsenAnterior;
    float XP,YP;
    Charger* i, j;

    *XFinal = X;
    *YFinal = Y;

    for(i=Particulas; i!=NULL; i=i->Proximo)
    {
        XP = i->PosicaoX;
        YP = i->PosicaoY;

        Distancia = DistanciaEntrePontos(X, Y, XP, YP);
        if(Distancia <= 25)
        {
            Distancia = 25;
        }

        if(i->TipoCarga == 1)
        {
            F = -(ConstanteUniversal)*(i->Carga)/(Distancia*Distancia);
        }
        else
        {
            F = (ConstanteUniversal)*(i->Carga)/(Distancia*Distancia);
        }

        cosAtual = ((XP-X)/(Distancia));
        senAtual = ((YP-Y)/(Distancia));

        FcosAnterior = (*XFinal - X);
        FsenAnterior = (*YFinal - Y);

        *XFinal = X + (F*cosAtual + FcosAnterior);
        *YFinal = Y + (F*senAtual + FsenAnterior);
    }
}

void NormalizarVetor(float X, float Y, float* XFinal, float* YFinal)
{
    int i, j;
    float D = DistanciaEntrePontos(X,Y,*XFinal,*YFinal);

    if(D == 0)
    {
        D = 1;
    }

    *XFinal = X + 10*(*XFinal - X)/D;
    *YFinal = Y + 10*(*YFinal - Y)/D;
}
