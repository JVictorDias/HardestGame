
void AtualizarAceleracao(Charger* Objeto)
{
    Objeto->AceleracaoX = Objeto->ForcaX/Objeto->Carga;
    Objeto->AceleracaoY = Objeto->ForcaY/Objeto->Carga;

    Objeto->ForcaX = 0;
    Objeto->ForcaY = 0;
}

void AtualizarVelocidade(Charger* Objeto)
{
    Objeto->VelocidadeX = Objeto->VelocidadeX + Objeto->AceleracaoX;
    Objeto->VelocidadeY = Objeto->VelocidadeY + Objeto->AceleracaoY;
}
