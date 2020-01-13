
void DefinirImagemDeFundo(int i)
{
    char Temp[100];

    sprintf(Temp,"imagens\\fundo%d.bmp",i);
    DefinirFundo(Temp);
}

int TrocarImagemDeFundo()
{
    static int i = 0;

    i = i + 1;
    if(i == 15)
    {
        i = 0;
    }
    DefinirImagemDeFundo(i);

    return i;
}
