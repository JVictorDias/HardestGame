
Charger* InserirParticula(Charger* Lista, int TipoCarga, float Carga, float Px, float Py, float Vx, float Vy)
{
    //Inserindo em ordem crescente de massa(o menor vem primeiro)
    Charger* Temp;

    if(Lista == NULL || Carga < Lista->Carga)
    {
        Temp = (Charger*)malloc(sizeof(Charger));

        if(TipoCarga == 1)
        {
            Temp->Obj = CriarObjeto("imagens\\Positiva.bmp",Px,Py,TAMANHO_PARTICULA,TAMANHO_PARTICULA);
            Temp->TrajetoriaCor = ((PIG_Cor){0,0,255,255});
        }
        if(TipoCarga == -1)
        {
            Temp->Obj = CriarObjeto("imagens\\Negativa.bmp",Px,Py,TAMANHO_PARTICULA,TAMANHO_PARTICULA);
            Temp->TrajetoriaCor = ((PIG_Cor){255,0,0,255});
        }
        Temp->TipoCarga = TipoCarga;
        Temp->ControleDeColisao = 0;
        Temp->Carga = Carga;
        Temp->PosicaoX = Px;
        Temp->PosicaoY = Py;
        Temp->VelocidadeX = Vx;
        Temp->VelocidadeY = Vy;
        Temp->AceleracaoX = 0;
        Temp->AceleracaoY = 0;
        Temp->ForcaX = 0;
        Temp->ForcaY = 0;
        Temp->Largura = TAMANHO_PARTICULA;
        Temp->Altura = TAMANHO_PARTICULA;

        Temp->IndiceTrajetoria = 0;
        Temp->TotalTrajetoria = 0;
        //Temp->TrajetoriaCor = ((PIG_Cor){rand()%256,rand()%256,rand()%256,255});

        if(Lista == NULL)
        {
            Temp->Proximo = NULL;
        }
        else
        {
            Temp->Proximo = Lista;
        }
        return Temp;
    }
    else
    {
        Lista->Proximo = InserirParticula(Lista->Proximo,TipoCarga,Carga,Px,Py,Vx,Vy);
        return Lista;
    }
}

Charger* RemoverParticula(Charger* Lista, int Px, int Py)
{
    Charger* Temp;

    if(Lista == NULL)
    {
        return NULL;
    }
    else
    {
        if  (   Px >= PegarX(Lista->Obj) &&
                Px <= PegarX(Lista->Obj) + PegarLargura(Lista->Obj) &&
                Py >= PegarY(Lista->Obj) &&
                Py <= PegarY(Lista->Obj) + PegarAltura(Lista->Obj)
            )
        {
            Temp = Lista->Proximo;
            free(Lista);
            return Temp;
        }
        else
        {
            Lista->Proximo = RemoverParticula(Lista->Proximo,Px,Py);
            return Lista;
        }
    }
}

Charger* DestruirParticula(Charger* Lista)
{
    if(Lista != NULL)
    {
        DestruirParticula(Lista->Proximo);

        DestruirObjeto(Lista->Obj);
        free(Lista);
    }
    return NULL;
}

