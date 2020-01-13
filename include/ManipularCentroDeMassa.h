

CentroDeMassa* BuscarCentroDeMassaClicado()
{
    int i;

    for(i=0;i<QuantidadeCM;i++)
    {
        if
        (   PIG_evento.mouse.posX >= PegarX(CentrosDeMassa[i].Obj) &&
            PIG_evento.mouse.posX <= PegarX(CentrosDeMassa[i].Obj) + PegarLargura(CentrosDeMassa[i].Obj) &&
            PIG_evento.mouse.posY >= PegarY(CentrosDeMassa[i].Obj) &&
            PIG_evento.mouse.posY <= PegarY(CentrosDeMassa[i].Obj) + PegarAltura(CentrosDeMassa[i].Obj)
        )
        {
            return &CentrosDeMassa[i];
        }
    }
    return NULL;
}

void CriarCentrosDeMassa()
{
    int i;

    for(i=0;i<QuantidadeCM;i++)
    {
        CentrosDeMassa[i].Obj = CriarObjeto(CentroDeMassaTextura[i],0,0,0,0);
        CentrosDeMassa[i].Altura = 0;
        CentrosDeMassa[i].Largura = 0;
        CentrosDeMassa[i].PosicaoX = 0;
        CentrosDeMassa[i].PosicaoY = 0;
        CentrosDeMassa[i].VelocidadeX = 0;
        CentrosDeMassa[i].VelocidadeY = 0;
        CentrosDeMassa[i].AceleracaoX = 0;
        CentrosDeMassa[i].AceleracaoY = 0;
        CentrosDeMassa[i].Codigo = i;
    }
}

void AdicionarVelocidadeCentroDeMassa()
{
    static int Controle = 0;
    Esfera* i;

    if(PIG_evento.mouse.acao == 1025 && Controle == 0 && PIG_evento.mouse.botao == 2 && DesenharVetoresTrajetorias == 1 && EsferaRecebendoVelocidade == NULL)
    {
        CentroDeMassaRecebendoVelocidade = BuscarCentroDeMassaClicado();
        if(CentroDeMassaRecebendoVelocidade != NULL)
        {
            Controle = 1;
        }
    }

    if(PIG_evento.mouse.acao == 1026 && Controle == 1 && PIG_evento.mouse.botao == 2)
    {
        Controle = 2;
    }

    if(PIG_evento.mouse.acao == 1025 && Controle == 2 && PIG_evento.mouse.botao == 2)
    {
        Controle = 3;
    }
    if(PIG_evento.mouse.acao == 1026 && Controle == 3 && PIG_evento.mouse.botao == 2)
    {
        for(i=Esferas;i!=NULL;i=i->Proximo)
        {
            if(i->SistemaInserida == CentroDeMassaRecebendoVelocidade->Codigo)
            {
                i->VelocidadeX = i->VelocidadeX + (XVirtualParaReal(PIG_evento.mouse.posX,PIG_evento.mouse.posY)-XVirtualParaReal(PegarCentroX(CentroDeMassaRecebendoVelocidade->Obj),PegarCentroY(CentroDeMassaRecebendoVelocidade->Obj)))/20;
                i->VelocidadeY = i->VelocidadeY + (YVirtualParaReal(PIG_evento.mouse.posX,PIG_evento.mouse.posY)-YVirtualParaReal(PegarCentroX(CentroDeMassaRecebendoVelocidade->Obj),PegarCentroY(CentroDeMassaRecebendoVelocidade->Obj)))/20;
            }
        }
        Controle = 0;
        CentroDeMassaRecebendoVelocidade = NULL;
    }
}

