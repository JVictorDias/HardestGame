#ifndef FORCACLASS_H
#define FORCACLASS_H

typedef struct force
{
    int Forca[2];

    int Objeto;
    struct force* Proximo;

}   Forca;

class ForcaClass
{
    public:
        ForcaClass();
        void ExecutarForcas();
        void AplicarForca(int Objeto, int ForcaAplicada, int Direcao);
        void ZerarForca(int Objeto, int Direcao);
        void InverterForca(int Objeto, int Direcao);
        int GetForca(int Objeto, int Direcao);
    private:
        Forca *Lista;
        int ForcaTimer;

};

ForcaClass::ForcaClass()
{
    Lista = NULL;
    ForcaTimer = CriarTimer();
}

void ForcaClass::AplicarForca(int Objeto, int ForcaAplicada, int Direcao)
{
    Forca *i;
    Forca *Anterior;

    switch(Direcao)
    {
        case 180:
        {
            Direcao = 0;
            ForcaAplicada = ForcaAplicada * (-1);
        }   break;
        case 270:
        {
            Direcao = 90;
            ForcaAplicada = ForcaAplicada * (-1);
        }   break;
    }

    if(Lista == NULL)
    {
        Lista = (Forca*)malloc(sizeof(Forca));

        Lista->Forca[0] = 0;
        Lista->Forca[1] = 0;

        Lista->Forca[Direcao/90] = ForcaAplicada;

        Lista->Objeto = Objeto;
        Lista->Proximo = NULL;
    }
    else
    {
        i = Lista;
        Anterior = Lista;

        while(i != NULL)
        {
            if(i->Objeto == Objeto)
            {
                i->Forca[Direcao/90] = i->Forca[Direcao/90] + ForcaAplicada;
                return;
            }
            Anterior = i;
            i = i->Proximo;
        }

        i = (Forca*)malloc(sizeof(Forca));

        i->Forca[0] = 0;
        i->Forca[1] = 0;
        i->Forca[Direcao/90] = ForcaAplicada;

        i->Objeto = Objeto;
        i->Proximo = NULL;

        Anterior->Proximo = i;
    }
}

void ForcaClass::ExecutarForcas()
{
    Forca *i = Lista;

    if(TempoDecorrido(ForcaTimer) >= 0.01)
    {
        while(i != NULL)
        {
            MoverOffset(i->Objeto,i->Forca[0],0);
            MoverOffset(i->Objeto,i->Forca[1],90);

            if(PegarY(i->Objeto) < 135)
            {
                if(PegarLargura(i->Objeto) != 1200)
                {
                    MoverObjeto(i->Objeto,PegarX(i->Objeto),135);
                }
            }

            i = i->Proximo;
        }
        ReiniciarTimer(ForcaTimer);
    }
}

void ForcaClass::ZerarForca(int Objeto, int Direcao)
{
    Forca *i = Lista;

    switch(Direcao)
    {
        case 180:
        {
            Direcao = 0;
        }   break;
        case 270:
        {
            Direcao = 90;
        }   break;
    }

    while(i != NULL)
    {
        if(i->Objeto == Objeto)
        {
            i->Forca[Direcao/90] = 0;
            break;
        }
        else
        {
            i = i->Proximo;
        }
    }
}

void ForcaClass::InverterForca(int Objeto, int Direcao)
{
    Forca *i = Lista;

    switch(Direcao)
    {
        case 180:
        {
            Direcao = 0;
        }   break;
        case 270:
        {
            Direcao = 90;
        }   break;
    }

    while(i != NULL)
    {
        if(i->Objeto == Objeto)
        {
            i->Forca[Direcao/90] = i->Forca[Direcao/90]*(-1);
            break;
        }
        else
        {
            i = i->Proximo;
        }
    }
}

int ForcaClass::GetForca(int Objeto, int Direcao)
{
    Forca *i = Lista;

    while(i != NULL)
    {
        if(i->Objeto == Objeto)
        {
            switch(Direcao)
            {
                case 0:
                {
                    return i->Forca[0];
                }   break;
                case 90:
                {
                    return i->Forca[1];
                }   break;
                case 180:
                {
                    return (i->Forca[0]*(-1));
                }   break;
                case 270:
                {
                    return (i->Forca[1]*(-1));
                }   break;
            }
        }
        else
        {
            i = i->Proximo;
        }
    }
}


#endif // FORCACLASS_H
