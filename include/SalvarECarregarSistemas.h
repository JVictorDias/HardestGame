
void SalvarEsferas(Esfera* Lista, FILE* f)
{
    if(Lista != NULL)
    {
        fwrite(Lista,1,sizeof(Esfera),f);
        SalvarEsferas(Lista->Proximo,f);
    }
}


int CarregarEsferasArquivo(char* TempString)
{
    FILE* f;
    Esfera* it;
    char String[100];
    int Contador = 0, i, CMCode = QuantidadeCM;
    float NumeradorX = 0, NumeradorY = 0, Denominador = 0, Zoom;

    for(i=ArquivoIndice; i<101; i++)
    {
        sprintf(String,"data\\Sistema%d.sis",i);
        f = fopen(String,"rb");

        if(f == NULL)
        {
            if(i == 100)
            {
                i = 0;
                Contador = Contador+1;
                if(Contador == 2)
                {
                    break;
                }
            }
        }
        else
        {
            ArquivoIndice = i+1;
            break;
        }
    }

    if(f != NULL)
    {
        Esferas = DestruirEsferas(Esferas);
        Esferas = CarregarEsferas(f);

        ProximoIDEsferas = BuscarMaiorID(Esferas) + 1;

        for(it=Esferas; it!=NULL; it=it->Proximo)
        {
            if(it->SistemaInserida < CMCode)
            {
                CMCode = it->SistemaInserida;
            }
        }
        for(it=Esferas; it!=NULL; it=it->Proximo)
        {
            if(it->SistemaInserida == CMCode)
            {
                NumeradorX = NumeradorX + (it->Massa * it->PosicaoX);
                NumeradorY = NumeradorY + (it->Massa * it->PosicaoY);
                Denominador = Denominador + it->Massa;
            }
        }
        Zoom = CameraZoom;
        CameraZoom = 0;
        CameraPosX = CameraPosX - (NumeradorX/Denominador - XVirtualParaReal(600,300));
        CameraPosY = CameraPosY - (NumeradorY/Denominador - YVirtualParaReal(600,300));
        CameraZoom = Zoom;

        AjustarPosicaoObjetos(Esferas);
        AjustarPosicaoCentrosDeMassa();

        sprintf(TempString,"Sistema%d.sis",i);

        fclose(f);
        return 1;
    }
    else
    {
        return 0;
    }
}

void SalvarEsferasArquivo(char* TempString)
{
    FILE* f;
    int Temp = 1;
    char String[100];

    while(1)
    {
        sprintf(String,"data\\Sistema%d.sis",Temp);
        f = fopen(String,"rb");
        if(f == NULL)
        {
            fclose(f);
            break;
        }
        else
        {
            Temp = (Temp%100)+1;
            fclose(f);
        }
    }

    f = fopen(String,"wb");
    SalvarEsferas(Esferas,f);
    fclose(f);

    sprintf(TempString,"Sistema%d.sis",Temp);
}

int CarregarCondicaoInicial()
{
    FILE* f;
    int i,QuantidadeDeEsferas;
    char Temp[200];

    int CodigoTextura, SistemaInserida,Obj;
    float Massa,Px,Py,Vx,Vy;

    Esfera* it;
    int CMCode = 0;
    float NumeradorX = 0, NumeradorY = 0, Denominador = 1;

    f = fopen("data\\CondicoesIniciais.txt","r");
    if(f != NULL)
    {
        Esferas = DestruirEsferas(Esferas);
        CameraZoom = 0;
        ProximoIDEsferas = 0;

        fscanf(f,"%s",Temp);
        fscanf(f,"%d",&QuantidadeDeEsferas);
        for(i=0;i<QuantidadeDeEsferas;i++)
        {
            fscanf(f,"%s",Temp);
            fscanf(f,"%s",Temp);
            fscanf(f,"%d",&CodigoTextura);
            fscanf(f,"%s",Temp);
            fscanf(f,"%d",&SistemaInserida);
            SistemaAtual = SistemaInserida;
            fscanf(f,"%s",Temp);
            fscanf(f,"%f",&Massa);
            fscanf(f,"%s",Temp);
            fscanf(f,"%f",&Px);
            fscanf(f,"%s",Temp);
            fscanf(f,"%f",&Py);
            fscanf(f,"%s",Temp);
            fscanf(f,"%f",&Vx);
            fscanf(f,"%s",Temp);
            fscanf(f,"%f",&Vy);
            Obj = CriarObjeto(Estrela[CodigoTextura],Px,Py,Massa,Massa);
            Esferas = InserirEsfera(Esferas,Obj,Massa,Px,Py,Vx,Vy,CodigoTextura);
        }
        fclose(f);

        for(it=Esferas; it!=NULL; it=it->Proximo)
        {
            if(it->SistemaInserida < CMCode)
            {
                CMCode = it->SistemaInserida;
            }
        }
        for(it=Esferas; it!=NULL; it=it->Proximo)
        {
            if(it->SistemaInserida == CMCode)
            {
                NumeradorX = NumeradorX + (it->Massa * it->PosicaoX);
                NumeradorY = NumeradorY + (it->Massa * it->PosicaoY);
                Denominador = Denominador + it->Massa;
            }
        }
        CameraPosX = CameraPosX - (NumeradorX/Denominador - XVirtualParaReal(600,300));
        CameraPosY = CameraPosY - (NumeradorY/Denominador - YVirtualParaReal(600,300));

        AjustarPosicaoObjetos(Esferas);
        AjustarPosicaoCentrosDeMassa();

        return 1;
    }
    return 0;
}
