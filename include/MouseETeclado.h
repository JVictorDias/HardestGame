
void VerificarBotaoClicado()
{
    switch(PegarBotao())
    {
        case 1:
        {
            Particulas = InserirParticula(Particulas,1,CARGA_PARTICULA,PIG_evento.mouse.posX,PIG_evento.mouse.posY,0,0);
        }   break;
        case 2:
        {
            Particulas = RemoverParticula(Particulas,PIG_evento.mouse.posX,PIG_evento.mouse.posY);
        }   break;
        case 3:
        {
            Particulas = InserirParticula(Particulas,-1,CARGA_PARTICULA,PIG_evento.mouse.posX,PIG_evento.mouse.posY,0,0);
        }   break;
    }
}

void VerificarTeclaApertada()
{
    switch(PegarTecla())
    {
        case 1:
        {
            Periodo = Periodo/2.0;
            ReiniciarTimer(TimerAvisos);
            sprintf(StringAvisos,"Intervalo entre iterações: %.5f",Periodo);
        }   break;

        case 2:
        {
            Periodo = Periodo*2.0;
            ReiniciarTimer(TimerAvisos);
            sprintf(StringAvisos,"Intervalo entre iterações: %.5f",Periodo);
        }   break;


        case 7:
        {
            DesenharVetoresTrajetorias = DesenharVetoresTrajetorias * (-1);
            ReiniciarTimer(TimerAvisos);
            strcpy(StringAvisos,AvisoTrajetoria[DesenharVetoresTrajetorias+1]);

        }   break;

        case 8:
        {
            MovimentoEsferas = MovimentoEsferas * (-1);
            ReiniciarTimer(TimerAvisos);
            strcpy(StringAvisos,AvisoMovimento[MovimentoEsferas+1]);
        }   break;

        case 9:
        {
            ColisaoAtivada = (ColisaoAtivada+1)%3;
            ReiniciarTimer(TimerAvisos);
            strcpy(StringAvisos,AvisoColisao[ColisaoAtivada]);
        }   break;

        case 10:
        {
            DesenharGrade = (DesenharGrade+1)%4;

            ReiniciarTimer(TimerAvisos);
            strcpy(StringAvisos,AvisoEspaco[DesenharGrade]);
        }   break;

    }
}
