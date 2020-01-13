
int VerificarColisaoEsferas(float X1, float Y1, float Raio1, float X2, float Y2, float Raio2)
{
    if(DistanciaEntrePontos(X1, Y1, X2, Y2) <= (Raio1 + Raio2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int AplicarColisao(Charger* E1, Charger* E2)
{
    ///////////////////////////////////////////////////////////////////////////

    double m1 = E1->Carga;
    double m2 = E2->Carga;

    double u1x = E1->VelocidadeX;
    double u1y = E1->VelocidadeY;
    double u2x = E2->VelocidadeX;
    double u2y = E2->VelocidadeY;
                                                //Carregando valores para as variaveis da equaçao
    double x1 = E1->PosicaoX;
    double y1 = E1->PosicaoY;
    double x2 = E2->PosicaoX;
    double y2 = E2->PosicaoY;

    double u1 = sqrt(u1x*u1x + u1y*u1y);
    double u2 = sqrt(u2x*u2x + u2y*u2y);

    //////////////////////////////////////////////////////////////////

    double a1 = atan2(y2-y1, x2-x1);
    double b1 = atan2(u1y, u1x);
    double c1 = b1-a1;

    double a2 = atan2(y1-y2, x1-x2);
    double b2 = atan2(u2y, u2x);
    double c2 = b2-a2;

    double u12 = u1*cos(c1);
    double u11 = u1*sin(c1);
                                                                //Resolvendo os calculos
    double u21 = u2*cos(c2);
    double u22 = u2*sin(c2);

    double v12 = (((m1-m2)*u12) - (2*m2*u21))/(m1+m2);
    double v21 = (((m1-m2)*u21) + (2*m1*u12))/(m1+m2);

    double v1x = u11*(-sin(a1)) + v12*(cos(a1));
    double v1y = u11*(cos(a1)) + v12*(sin(a1));

    double v2x = u22*(-sin(a2)) - v21*(cos(a2));
    double v2y = u22*(cos(a2)) - v21*(sin(a2));

    /////////////////////////////////////////////////////////////////////////

    E1->VelocidadeX = v1x;
    E1->VelocidadeY = v1y;
                                        //Retornando o resultado final para as variaveis das esferas
    E2->VelocidadeX = v2x;
    E2->VelocidadeY = v2y;

    /////////////////////////////////////////////////////////////////////////
    float v1 = sqrt(u1x*u1x + u1y*u1y);
    float v2 = sqrt(u2x*u2x + u2y*u2y);

    if(v1 > 2 || v2 > 2)
        return 1;
    else
        return 0;
}

void ResetColision()
{
    Charger* i;

    for(i=Particulas; i!=NULL; i=i->Proximo)
    {
        i->ControleDeColisao = 0;
    }
}

void ExplosionEnergy(Charger* E1, Charger* E2)
{
    double Constante = 1.01;

    float A;

    E1->VelocidadeX = Constante*E1->VelocidadeX;
    E1->VelocidadeY = Constante*E1->VelocidadeY;

    E2->VelocidadeX = Constante*E2->VelocidadeX;
    E2->VelocidadeY = Constante*E2->VelocidadeY;



    //if(E1->VelocidadeX > 10.0)
    {
       //E1->VelocidadeX = E1->VelocidadeX/10.0;
    }
    //if(E1->VelocidadeY > 10.0)
    {
        //E1->VelocidadeY = E1->VelocidadeY/10.0;
    }



    //if(E2->VelocidadeX > 10.0)
    {
        //E2->VelocidadeX = E2->VelocidadeX/10.0;
    }
    //if(E2->VelocidadeY > 10.0)
    {
        //E2->VelocidadeY = E2->VelocidadeY/10.0;
    }
}
