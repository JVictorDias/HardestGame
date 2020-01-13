
typedef struct animation
{
    int SpriteAtual;
    int* VetorSprites;
    int QuantidadeSprites;
    int Largura, Altura;
    double X, Y;
    double Angulo;

    struct animation* Proximo;

}   Animation;

    Animation* AnimationsList = NULL;

void DesenharAnimations(Animation* List)
{
    Animation* i;

    for(i=List; i!=NULL; i=i->Proximo)
    {
        DesenharSprite(i->VetorSprites[i->SpriteAtual], i->X, i->Y, i->Largura, i->Altura, i->Angulo);
    }
}

void PlayAnimation(int Codigo, double X, double Y, int Largura, int Altura, double Angulo)
{
    char String[100];
    int i;

    Animation* Temp = (Animation*)malloc(sizeof(Animation));

    Temp->Altura = Altura;
    Temp->Largura = Largura;
    Temp->Angulo = Angulo;

    Temp->X = X;
    Temp->Y = Y;
    Temp->SpriteAtual = 0;
    Temp->Proximo = AnimationsList;

    switch(Codigo)
    {
        //case EXEMPLO:
        {
            //Temp->QuantidadeSprites = 50;
            //Temp->VetorSprites = EXEMPLOSprites;

        }   break;
    }

    AnimationsList = Temp;
}

Animation* DestruirAnimations(Animation* List)
{
    if(List == NULL)
    {
        return NULL;
    }
    else
    {
        Animation* Temp;

        List->Proximo = DestruirAnimations(List->Proximo);
        if(List->SpriteAtual == List->QuantidadeSprites)
        {
            Temp = List->Proximo;
            free(List);
            return Temp;
        }
        return List;
    }

}

Animation* AtualizarAnimations(Animation* List)
{
    Animation* i;

    for(i=List; i!=NULL; i=i->Proximo)
    {
        i->SpriteAtual = i->SpriteAtual + 1;
    }

    List = DestruirAnimations(List);

    return List;
}

void CriarAnimations()
{
    int i;

    char String[100];

    for(i=0; i<50; i++)
    {
        sprintf(String,"imagens\\Sangue\\sangue (%d).png", i+1);
        //EXEMPLOSprites[i] = CriarSprite(String);
    }
}
