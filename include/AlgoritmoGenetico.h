

typedef struct individuo
{
    double* DNA;
    int TamanhoDNA;
    int Sobrevivera;

    double Fitness;

}   Individuo;

    Individuo Filho[FILHOS_QUANTIDADE];
    Individuo Pai[POPULACAO_TAMANHO];
    Individuo Sobrevivente[FILHOS_QUANTIDADE + POPULACAO_TAMANHO];
    Individuo PopulacaoInicial[POPULACAO_INICIAL_TAMANHO];
    Individuo* VetorOrdenado[POPULACAO_INICIAL_TAMANHO];

    double* DNADaVez[POPULACAO_TAMANHO];

    double MediaFitnessPopulacao[LARG_GRAFICO];
    double MediaFitnessFilhos[LARG_GRAFICO];
    double BestFitnessPopulacao[LARG_GRAFICO];

    int Etapa = 0;
    int InicializandoPopulacao = 1;
    int FilhoDaVez = 0;
    int IndividuoDaVez = POPULACAO_TAMANHO;
    int GeracaoCompleta = 0;


void InicializarGenetico()
{
    int TamanhoDNA = Dinossauros[0].TamanhoDNA;

    for(int i=0; i<FILHOS_QUANTIDADE; i++)
    {
        Filho[i].TamanhoDNA = TamanhoDNA;
        Filho[i].DNA = (double*)malloc(TamanhoDNA*sizeof(double));
        Filho[i].Fitness = 0;
    }

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Pai[i].TamanhoDNA = TamanhoDNA;
        Pai[i].DNA = (double*)malloc(TamanhoDNA*sizeof(double));
        Pai[i].Fitness = 0;

        DNADaVez[i] = (double*)malloc(TamanhoDNA*sizeof(double));
    }

    for(int i=0; i<FILHOS_QUANTIDADE + POPULACAO_TAMANHO; i++)
    {
        Sobrevivente[i].TamanhoDNA = TamanhoDNA;
        Sobrevivente[i].Fitness = 0;
        Sobrevivente[i].DNA = (double*)malloc(TamanhoDNA*sizeof(double));
    }

    for(int i=0; i<POPULACAO_INICIAL_TAMANHO; i++)
    {
        PopulacaoInicial[i].Fitness = 0;
        PopulacaoInicial[i].Sobrevivera = 0;
        PopulacaoInicial[i].TamanhoDNA = TamanhoDNA;
        PopulacaoInicial[i].DNA = (double*)malloc(TamanhoDNA*sizeof(double));
        for(int j=0; j<TamanhoDNA; j++)
        {
            PopulacaoInicial[i].DNA[j] = getRandomValue();
        }
    }

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        for(int j=0; j<TamanhoDNA; j++)
        {
            DNADaVez[i][j] = PopulacaoInicial[i].DNA[j];
        }
    }
}



void SalvarPais()
{
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        for(int j=0; j<Dinossauros[i].TamanhoDNA; j++)
        {
            Pai[i].DNA[j] = Dinossauros[i].DNA[j];
        }
        Pai[i].Fitness = Dinossauros[i].Fitness;
    }
}

int RandomizarPai()
{
    unsigned long int Intervalo = 0;
    unsigned long int Soma = 0;
    unsigned long int Posicao;

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Intervalo = Intervalo + (unsigned long int)Pai[i].Fitness;
    }

    Posicao = gsl_rng_uniform_int(Gerador, Intervalo);

    for(int j=0; j<POPULACAO_TAMANHO; j++)
    {
        Soma = Soma + (unsigned long int)Pai[j].Fitness;
        if(Posicao <= Soma)
        {
            return j;
        }
    }
}

void CruzamentoPontoCorte(int IndiceFilho, int IndicePai1, int IndicePai2)
{
    //printf("Indice filho: %d, indice Pai1: %d, indice Pai2: %d\n",IndiceFilho, IndicePai1, IndicePai2);

    int PontoCorte = rand()%Pai[IndicePai1].TamanhoDNA;

    for(int j=0; j<Filho[IndiceFilho].TamanhoDNA; j++)
    {
        if(j < PontoCorte)
        {
            Filho[IndiceFilho].DNA[j] = Pai[IndicePai1].DNA[j];
        }
        else
        {
            Filho[IndiceFilho].DNA[j] = Pai[IndicePai2].DNA[j];
        }
    }
}

void CruzamentoMedia(int IndiceFilho, int IndicePai1, int IndicePai2)
{
    //printf("Indice filho: %d, indice Pai1: %d, indice Pai2: %d\n",IndiceFilho, IndicePai1, IndicePai2);

    for(int j=0; j<Filho[IndiceFilho].TamanhoDNA; j++)
    {
        Filho[IndiceFilho].DNA[j] = (Pai[IndicePai1].DNA[j] + Pai[IndicePai2].DNA[j])/2.0;
    }
}

void MutacaoPesosAleatorios(int IndiceFilho)
{
    for(int i=0; i<10; i++)
    {
        Filho[IndiceFilho].DNA[rand()%Filho[IndiceFilho].TamanhoDNA] = getRandomValue();
    }
}

void MutacaoTrocaPesos(int IndiceFilho)
{
    double Temp;
    for(int i=0; i<10; i++)
    {
        int Indice1 = rand()%Filho[IndiceFilho].TamanhoDNA;
        int Indice2 = rand()%Filho[IndiceFilho].TamanhoDNA;

        Temp = Filho[IndiceFilho].DNA[Indice1];
        Filho[IndiceFilho].DNA[Indice1] = Filho[IndiceFilho].DNA[Indice2];
        Filho[IndiceFilho].DNA[Indice2] = Temp;
    }
}

void RandomMutation(int IndiceFilho)
{
    for(int i=0; i<10; i++)
    {
        Filho[IndiceFilho].DNA[rand()%Filho[IndiceFilho].TamanhoDNA] = getRandomValue();
    }
}

void GerarFilhos()
{
    int IndicePai1, IndicePai2;

    for(int i=0; i<FILHOS_QUANTIDADE; i++)
    {
        IndicePai1 = RandomizarPai();
        do
        {
            IndicePai2 = RandomizarPai();
        }   while(IndicePai1 == IndicePai2);

        int TipoCruzamento = rand()%2;

        TipoCruzamento = 1;

        switch(TipoCruzamento)
        {
            case 0:
            {
                CruzamentoMedia(i, IndicePai1, IndicePai2);

            }   break;
            case 1:
            {
                CruzamentoPontoCorte(i, IndicePai1, IndicePai2);

            }   break;
            case 2:
            {
                RandomMutation(i);
            }   break;
        }

        int TipoMutacao = rand()%2;
        int ChanceMutacao = rand()%10;

        //int ChanceMutacao = 0;

        if(ChanceMutacao == 0)
        {
            switch(TipoMutacao)
            {
                case 0:
                {
                    MutacaoPesosAleatorios(i);

                }   break;
                case 1:
                {
                    MutacaoTrocaPesos(i);

                }   break;
            }
        }
    }
}

void SalvarFitnessFilhos(int FilhoDaVez)
{
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Filho[FilhoDaVez+i].Fitness = Dinossauros[i].Fitness;
    }
}

int SetarFilhosDaVez(int FilhoDaVez)
{
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        for(int j=0; j<Dinossauros[0].TamanhoDNA; j++)
        {
            DNADaVez[i][j] = Filho[FilhoDaVez].DNA[j];
        }
        FilhoDaVez++;
    }
    return FilhoDaVez;
}

void UnirPaisFilhos()
{
    int IndiceDaVez = 0;

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Sobrevivente[IndiceDaVez].TamanhoDNA = Pai[i].TamanhoDNA;
        Sobrevivente[IndiceDaVez].Fitness = Pai[i].Fitness;
        Sobrevivente[IndiceDaVez].Sobrevivera = 0;
        for(int j=0; j<Pai[i].TamanhoDNA; j++)
        {
            Sobrevivente[IndiceDaVez].DNA[j] = Pai[i].DNA[j];
        }
        IndiceDaVez++;
    }

    for(int i=0; i<FILHOS_QUANTIDADE; i++)
    {
        Sobrevivente[IndiceDaVez].TamanhoDNA = Filho[i].TamanhoDNA;
        Sobrevivente[IndiceDaVez].Fitness = Filho[i].Fitness;
        Sobrevivente[IndiceDaVez].Sobrevivera = 0;
        for(int j=0; j<Filho[i].TamanhoDNA; j++)
        {
            Sobrevivente[IndiceDaVez].DNA[j] = Filho[i].DNA[j];
        }
        IndiceDaVez++;
    }
}

int BuscarMaiorFitness()
{
    double MaiorFitness = 0;
    int Indice = -1;

    for(int i=0; i<POPULACAO_TAMANHO + FILHOS_QUANTIDADE; i++)
    {
        if(Sobrevivente[i].Fitness > MaiorFitness)
        {
            MaiorFitness = Sobrevivente[i].Fitness;
            Indice = i;
        }
    }
    return Indice;
}

void SelecionarSobreviventes()
{
    unsigned long int Intervalo = 0;
    unsigned long int Soma = 0;
    unsigned long int Posicao;

    /// Elitismo

    int IndiceMelhor = BuscarMaiorFitness();
    Sobrevivente[IndiceMelhor].Sobrevivera = 1;

    //printf("Indice do melhor sobrevivente: %d, fitness = %f\n", IndiceMelhor, Sobrevivente[IndiceMelhor].Fitness);

    /// --------

    for(int i=0; i<POPULACAO_TAMANHO + FILHOS_QUANTIDADE; i++)
    {
        Intervalo = Intervalo + (unsigned long int)Sobrevivente[i].Fitness;
    }

    for(int i=0; i<POPULACAO_TAMANHO-1; i++)
    {
        Posicao = gsl_rng_uniform_int(Gerador, Intervalo);

        Soma = 0;
        for(int j=0; j<POPULACAO_TAMANHO + FILHOS_QUANTIDADE; j++)
        {
            Soma = Soma + (unsigned long int)Sobrevivente[j].Fitness;
            if(Posicao <= Soma)
            {
                if(Sobrevivente[j].Sobrevivera == 0)
                {
                    Sobrevivente[j].Sobrevivera = 1;
                    break;
                }
                else
                {
                    i--;
                    break;
                }
            }
        }
    }
}

void SetarNovaPopulacao()
{
    int IndiceDaVez = 0;

    for(int i=0; i<POPULACAO_TAMANHO + FILHOS_QUANTIDADE; i++)
    {
        if(Sobrevivente[i].Sobrevivera == 1)
        {
            for(int j=0; j<Sobrevivente[i].TamanhoDNA; j++)
            {
                DNADaVez[IndiceDaVez][j] = Sobrevivente[i].DNA[j];
            }
            IndiceDaVez++;
        }
    }
}





void SalvarFitnessIndividuo(int IndividuoDaVez)
{
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        PopulacaoInicial[IndividuoDaVez+i].Fitness = Dinossauros[i].Fitness;
    }
}

int SetarIndividuoDaVez(int IndividuoDaVez)
{
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        for(int j=0; j<Dinossauros[0].TamanhoDNA; j++)
        {
            DNADaVez[i][j] = PopulacaoInicial[IndividuoDaVez].DNA[j];
        }
        IndividuoDaVez++;
    }
    return IndividuoDaVez;
}

void SelecionarPopulacaoInicial()
{
    for(int i=0; i<POPULACAO_INICIAL_TAMANHO; i++)
    {
        VetorOrdenado[i] = &PopulacaoInicial[i];
    }

    for(int i=0; i<POPULACAO_INICIAL_TAMANHO; i++)
    {
        for(int j=0; j<POPULACAO_INICIAL_TAMANHO-1; j++)
        {
            if(VetorOrdenado[i]->Fitness < VetorOrdenado[i+1]->Fitness)
            {
                Individuo* Temp = VetorOrdenado[i];
                VetorOrdenado[i] = VetorOrdenado[i+1];
                VetorOrdenado[i+1] = Temp;
            }
        }
    }

    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        for(int j=0; j<Dinossauros[0].TamanhoDNA; j++)
        {
            Dinossauros[i].DNA[j] = VetorOrdenado[i]->DNA[j];
        }
    }
}

double BestFitnessGeracao()
{
    double Maior = 0;
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        if(Dinossauros[i].Fitness > Maior)
        {
            Maior = Dinossauros[i].Fitness;
        }
    }
    return Maior;
}

double MediaFitnessGeracao()
{
    double Media = 0;
    for(int i=0; i<POPULACAO_TAMANHO; i++)
    {
        Media = Media + Dinossauros[i].Fitness;
    }
    Media = Media/(double)POPULACAO_TAMANHO;
    return Media;
}

double MediaFitnessFilho()
{
    double Media = 0;
    for(int i=0; i<FILHOS_QUANTIDADE; i++)
    {
        Media = Media + Filho[i].Fitness;
    }
    Media = Media/(double)FILHOS_QUANTIDADE;
    return Media;
}

double BestFitnessEver()
{
    double Maior = 0;
    for(int i=0; i<GeracaoCompleta; i++)
    {
        if(BestFitnessPopulacao[i] > Maior)
        {
            Maior = BestFitnessPopulacao[i];
        }
    }
    return Maior;
}







void AlgoritmoGenetico()
{
    if(InicializandoPopulacao == 1)
    {
        SalvarFitnessIndividuo(IndividuoDaVez - POPULACAO_TAMANHO);
        if(IndividuoDaVez == POPULACAO_INICIAL_TAMANHO)
        {
            SelecionarPopulacaoInicial();
            IndividuoDaVez = 0;
            InicializandoPopulacao = 0;
        }
        else
        {
            IndividuoDaVez = SetarIndividuoDaVez(IndividuoDaVez);
        }
    }

    if(InicializandoPopulacao == 0)
    {
        if(Etapa == 0)
        {
            GeracaoCompleta = Geracao;
            BestFitnessPopulacao[Geracao] = BestFitnessGeracao();
            MediaFitnessPopulacao[Geracao] = MediaFitnessGeracao();

            SalvarPais();
            GerarFilhos();
            FilhoDaVez = SetarFilhosDaVez(0);
            Etapa = 1;
        }
        else
        {
            if(Etapa == 1)
            {
                SalvarFitnessFilhos(FilhoDaVez - POPULACAO_TAMANHO);
                if(FilhoDaVez == FILHOS_QUANTIDADE)
                {
                    FilhoDaVez = 0;
                    Etapa = 2;
                }
                else
                {
                    FilhoDaVez = SetarFilhosDaVez(FilhoDaVez);
                }
            }
        }

        if(Etapa == 2)
        {
            MediaFitnessFilhos[Geracao] = MediaFitnessFilho();

            UnirPaisFilhos();
            SelecionarSobreviventes();
            SetarNovaPopulacao();
            Etapa = 0;
            Geracao = Geracao + 1;

        }
    }

    //printf("Sai genetico\n");
}


//int SelecionarPai()
//{
//    unsigned int Soma = 0;
//
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        Soma = Soma + (unsigned int)Dinossauros[i].Fitness;
//    }
//    unsigned long int Posicao = gsl_rng_uniform_int(Gerador, Soma);
//    Soma = 0;
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        Soma = Soma + (unsigned int)Dinossauros[i].Fitness;
//        if(Posicao <= Soma)
//        {
//            return i;
//        }
//    }

//    return rand()%TAM_POPULACAO;

    //return -1;
//}

//int SelecionarSobrevivente()
//{
//    unsigned int Soma = 0;
//
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        Soma = Soma + Dinossauros[i].Fitness;
//    }
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        Soma = Soma + FitnessFilho[i];
//    }
//
//    unsigned long int Position = gsl_rng_uniform_int(Gerador, Soma);
//    unsigned int Soma2 = 0;
//
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        if(Position <= Soma2)
//        {
//            return i;
//        }
//        else
//        {
//            Soma2 = Soma2 + Dinossauros[i].Fitness;
//        }
//    }
//
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        if(Position <= Soma2)
//        {
//            return i+100;
//        }
//        else
//        {
//            Soma2 = Soma2 + FitnessFilho[i];
//        }
//    }
//
//
//
//
//
//}

//int SelecionarSobrevivente()
//{
//    unsigned long int Position;
//    int j;
//
//    while(1)
//    {
//        Position = gsl_rng_uniform_int(Gerador, 2*TAM_POPULACAO);
//
//        if(Position < TAM_POPULACAO)
//        {
//            j = Position;
//            if(Dinossauros[j].Fitness != -1)
//            {
//                return Position;
//            }
//        }
//        else
//        {
//            j = Position - TAM_POPULACAO;
//            if(FitnessFilho[j] != -1)
//            {
//                return Position;
//            }
//        }
//    }
//}
//
//
//
//
//void CopiarDNA(int destino, int origem)
//{
//    for(int i=0; i<Dinossauros[destino].TamanhoDNA; i++)
//    {
//        if(origem >= TAM_POPULACAO)
//        {
//            DNABackup[destino][i] = DNAFilho[origem-TAM_POPULACAO][i];
//
//        }
//        else
//        {
//            DNABackup[destino][i] = Dinossauros[origem].DNA[i];
//        }
//    }
//}
//
//void TrocarValores(double* Vetor1, double* Vetor2, int Tamanho)
//{
//    double temp;
//    for(int i=0; i<Tamanho; i++)
//    {
//        temp = Vetor1[i];
//        Vetor1[i] = Vetor2[i];
//        Vetor2[i] = temp;
//    }
//}
//
//int BuscarMaiorFitness()
//{
//    double Maior = 0;
//    int Indice = -1;
//
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        if(Dinossauros[i].Fitness > Maior)
//        {
//            Maior = Dinossauros[i].Fitness;
//            Indice = i;
//        }
//    }
//
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        if(FitnessFilho[i] > Maior)
//        {
//            Maior = FitnessFilho[i];
//            Indice = i+TAM_POPULACAO;
//        }
//    }
//
//    return Indice;
//}
//
//
//void AlgoritmoGenetico()
//{
//    if(Modo == 1)       /// Avaliou os pais
//    {
//        int Pai1, Pai2;
//
//        for(int i=0; i<TAM_POPULACAO; i++)  /// Gerando filhos
//        {
//            Pai1 = SelecionarPai();
//            do
//            {
//                Pai2 = SelecionarPai();
//
//            }   while(Pai1 == Pai2);
//
//            int PontoCorte = rand()%Dinossauros[Pai1].TamanhoDNA;
//
//            for(int j=0; j<Dinossauros[Pai1].TamanhoDNA; j++)
//            {
//                //double Peso1 = Dinossauros[Pai1].DNA[j];
//                //double Peso2 = Dinossauros[Pai2].DNA[j];
//
//                //DNAFilho[i][j] = (Peso1 + Peso2)/2.0;
//
//                if(j < PontoCorte)
//                {
//                    DNAFilho[i][j] = Dinossauros[Pai1].DNA[j];
//                }
//                else
//                {
//                    DNAFilho[i][j] = Dinossauros[Pai2].DNA[j];
//                }
//            }
//
//            if(rand()%10 == 0)
//            {
//                int QuantidadeMutacoes = (rand()%10)+1;
//                for(int k=0; k<QuantidadeMutacoes; k++)
//                {
//                    DNAFilho[i][rand()%Dinossauros[Pai1].TamanhoDNA] = getRandomValue();
//                }
//            }
//        }
//
//        for(int i=0; i<TAM_POPULACAO; i++)  /// Trocando filho de lugar com o pai, para poder avaliar os filhos
//        {
//            TrocarValores(DNAFilho[i], Dinossauros[i].DNA, Dinossauros[i].TamanhoDNA);
//            FitnessFilho[i] = Dinossauros[i].Fitness;
//        }
//    }
//    else                /// Avaliou os filhos
//    {
//        int Indice = BuscarMaiorFitness();
//        CopiarDNA(0, Indice);
//        Dinossauros[Indice].Fitness = -1;
//
//        for(int i=1; i<TAM_POPULACAO; i++)
//        {
//            int Sobrevivente = SelecionarSobrevivente();
//            if(Sobrevivente < TAM_POPULACAO)
//            {
//                Dinossauros[Sobrevivente].Fitness = -1;
//            }
//            else
//            {
//                FitnessFilho[Sobrevivente-TAM_POPULACAO] = -1;
//            }
//            CopiarDNA(i, Sobrevivente);
//        }
//
//        for(int i=0; i<TAM_POPULACAO; i++)
//        {
//            for(int j=0; j<Dinossauros[i].TamanhoDNA; j++)
//            {
//                Dinossauros[i].DNA[j] = DNABackup[i][j];
//            }
//        }
//    }
//
//    Modo = -Modo;
//}
//
//void RandomMutations()
//{
//    for(int j=1; j<TAM_POPULACAO; j++)
//    {
//        for(int k=0; k<VetorOrdenado[j]->TamanhoDNA; k++)
//        {
//            VetorOrdenado[j]->DNA[k] = VetorOrdenado[0]->DNA[k];
//        }
//    }
//
////    int mod = 100 - Geracao;
////    if(mod < 1)
////        mod = 1;
//    for(int i=1; i<TAM_POPULACAO; i++)
//    {
//        int QuantidadeMutacoes = (rand()%10)+1;
//        for(int k=0; k<QuantidadeMutacoes; k++)
//        {
//            VetorOrdenado[i]->DNA[rand()%VetorOrdenado[i]->TamanhoDNA] = getRandomValue();
//        }
//    }
//}
//
//void BuscaLocal()
//{
//    for(int j=1; j<TAM_POPULACAO; j++)
//    {
//        for(int k=0; k<VetorOrdenado[j]->TamanhoDNA; k++)
//        {
//            VetorOrdenado[j]->DNA[k] = VetorOrdenado[0]->DNA[k];
//        }
//    }
//
//    for(int i=1; i<TAM_POPULACAO; i++)
//    {
//        VetorOrdenado[i]->DNA[rand()%VetorOrdenado[i]->TamanhoDNA] = getRandomValue();
//        VetorOrdenado[i]->DNA[rand()%VetorOrdenado[i]->TamanhoDNA] = getRandomValue();
//    }
//}
//
//double getMediaFitness()
//{
//    double soma = 0;
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        soma = soma + Dinossauros[i].Fitness;
//    }
//    soma = soma/(double)TAM_POPULACAO;
//
//    return soma;
//}
//
//double getMaiorFitness()
//{
//    double Maior = 0;
//    for(int i=0; i<TAM_POPULACAO; i++)
//    {
//        if(Dinossauros[i].Fitness > Maior)
//        {
//            Maior = Dinossauros[i].Fitness;
//        }
//    }
//    return Maior;
//}
//

