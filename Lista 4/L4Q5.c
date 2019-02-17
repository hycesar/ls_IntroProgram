#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHOPRIMEIRAMAO 7
#define PRIMEIROAJOGAR 0
//L4Q5
int* minhaRealloc(int* ponteiro, int tamanho)
{
  int i;
  if(tamanho <= 0)//esta me indicando o fim do vetor
  {
    tamanho = 1;
    printf("Fim do vetor.");
  }
  int *novoponteiro = malloc(tamanho * sizeof(int));
  if(novoponteiro != NULL && ponteiro != NULL)
  {
    for(i = 0; i < tamanho/sizeof(int); i++)
    {
      *(novoponteiro + i) = *(ponteiro + i);
    }
  }
  else if(novoponteiro == NULL)
  {
    printf("Erro ao realocar!\n");
    exit(1);
  }
  return novoponteiro;
}
void print1Carta(int carta)
{
  if(carta%14 < 10)//ou seja uma carta comum!
  {
    printf("%d%c ", carta%14, carta/14 + 'A');//Decodificando as cartas segundo especificacoes
  }
  else//forma de imprmir diferente
  {
    if(carta%14 == 10)
    {
      printf("+1%c", carta/14 + 'A');
    }
    else if(carta%14 == 11)
    {
      printf("+2%c", carta/14 + 'A');
    }
    else if(carta%14 == 12)
    {
      printf("P%c ", carta/14 + 'A');
    }
    else
    {
      printf("R%c ", carta/14 + 'A');
    }
  }
}
void printCartasMao(int** Time, int *cartasnaMao, int posicaojogador)
{
  int i;
  for(i = 0; i < *(cartasnaMao + posicaojogador); i++)
  {
    printf(" [%d]", i);//posicao da carta no vetor para descarte
    print1Carta(*(*(Time + posicaojogador) + i));
  }
  printf("\n");
}
int* criaVetorCartasnaMao(int numeroJogadores)
{
  int i;
  int* cartasnaMao;
  //trato do vetor cartas na mao
  cartasnaMao = (int*) malloc(numeroJogadores * sizeof(int*));
  if(cartasnaMao == NULL)
  {
    printf("Erro na alocacao");
    exit(1);
  }
  else
  {
    for(i = 0; i < numeroJogadores; i++)
    {
      *(cartasnaMao + i) = TAMANHOPRIMEIRAMAO;
    }
  }
  return cartasnaMao;
}
int descartaPrimeiraCarta(int** Time, int* cartasnaMao, int posicaoJogadornoVetor)//posicao do jogador no time eh a mesma no vetor cartas na mao
{
  int posicaodacarta, i, j, cartadescartada;
  int* vetorauxiliar;
  vetorauxiliar = (int*) calloc(1, sizeof(int*));
  printf("Jogador %d: ", posicaoJogadornoVetor + 1);
  printf("Qual carta deseja descartar? Digite a posicao:");
  do
  {
    scanf("%d", &posicaodacarta);
    if(!(posicaodacarta >= 0 && posicaodacarta < *(cartasnaMao + posicaoJogadornoVetor)))
    {
      printf("Por favor escoha uma carta valida\n");
    }
  }while(!(posicaodacarta >= 0 && posicaodacarta < *(cartasnaMao + posicaoJogadornoVetor)));
  //percorrer o vetor de cartas em time e copiar para um auxiliar, exceto a carta
  for(i = 0, j= 0; i < posicaodacarta; i++, j++)
  {
    vetorauxiliar = (int*) minhaRealloc(vetorauxiliar, (j + 1) * sizeof(int*));
    if(vetorauxiliar == NULL)
    {
      printf("Erro na alocacao");
      exit(1);
    }
    else
    {
      *(vetorauxiliar + j) = *(*(Time + posicaoJogadornoVetor) + i);
    }
  }
  //guardar a carta descartada em um inteiro e retornar ao fim da funcao
  cartadescartada = *(*(Time + posicaoJogadornoVetor) + i);
  i++;//proxima carta
  //continua recolhendo cartas
  for(; i < *(cartasnaMao + posicaoJogadornoVetor); i++, j++)
  {
    vetorauxiliar = minhaRealloc(vetorauxiliar, (j + 1) * sizeof(int*));
    if(vetorauxiliar == NULL)
    {
      printf("Erro na alocacao");
      exit(1);
    }
    else
    {
      *(vetorauxiliar + j) = *(*(Time + posicaoJogadornoVetor) + i);
    }
  }
  free(*(Time + posicaoJogadornoVetor));//libero o vetor antigo
  *(Time + posicaoJogadornoVetor) = vetorauxiliar;//coloco o novo
  //atualizar o veo cartas na mao
  *(cartasnaMao + posicaoJogadornoVetor) = *(cartasnaMao + posicaoJogadornoVetor) - 1;
  return cartadescartada;
}
int descartaCarta(int** Time, int* cartasnaMao, int posicaoJogadornoVetor, int ultimacartadescartada)//posicao do jogador no time eh a mesma no vetor cartas na mao
{
  int posicaodacarta, i, j;
  int* vetorauxiliar;
  vetorauxiliar = (int*) calloc(1, sizeof(int*));
  int existecartavalida = 0;
  //Existe uma carta para descartar???
  for(i = 0, j = 0 ; i < *(cartasnaMao + posicaoJogadornoVetor)&& !existecartavalida; i++)
  {
    if(((ultimacartadescartada%14 == *(*(Time + posicaoJogadornoVetor) + i)%14) || (ultimacartadescartada/14 == *(*(Time + posicaoJogadornoVetor) + i)/14)))
    {
      existecartavalida = 1;//existe uma carta disponivel na sua mao
    }
  }
  //se sim, retira e realoca o vetor
  if(existecartavalida)
  {
    do
    {
      do
      {
        printf("Jogador %d: ", posicaoJogadornoVetor + 1);
        printf("Qual carta deseja descartar? Digite a posicao:");
        scanf("%d", &posicaodacarta);
        if(!(posicaodacarta >= 0 && posicaodacarta < *(cartasnaMao + posicaoJogadornoVetor)))
        {
          printf("Por favor escoha uma carta valida\n");
        }
      }while(!(posicaodacarta >= 0 && posicaodacarta < *(cartasnaMao + posicaoJogadornoVetor)));
      if(!((ultimacartadescartada%14 == *(*(Time + posicaoJogadornoVetor) + posicaodacarta)%14) || (ultimacartadescartada/14 == *(*(Time + posicaoJogadornoVetor) + posicaodacarta)/14)))//carta invalida
      {
        printf("Impossivel descartas essa carta, tente novamente!");
      }
    }while(!((ultimacartadescartada%14 == *(*(Time + posicaoJogadornoVetor) + posicaodacarta)%14) || (ultimacartadescartada/14 == *(*(Time + posicaoJogadornoVetor) + posicaodacarta)/14)));
      //percorrer o vetor de cartas em time e copiar para um auxiliar, exceto a carta
    for(i = 0, j= 0 ; i < posicaodacarta; i++, j++)
    {
      vetorauxiliar = (int*) minhaRealloc(vetorauxiliar, (j + 1) * sizeof(int*));
      if(vetorauxiliar == NULL)
      {
        printf("Erro na alocacao");
        exit(1);
      }
      else
      {
        *(vetorauxiliar + j) = *(*(Time + posicaoJogadornoVetor) + i);
      }
    }
    //guardar a carta descartada em um inteiro e retornar ao fim da funcao
    ultimacartadescartada = *(*(Time + posicaoJogadornoVetor) + i);
    i++;//proxima carta
    //continua recolhendo cartas
    for(; i < *(cartasnaMao + posicaoJogadornoVetor); i++, j++)
    {
      vetorauxiliar = minhaRealloc(vetorauxiliar, (j + 1) * sizeof(int*));
      if(vetorauxiliar == NULL)
      {
        printf("Erro na alocacao");
        exit(1);
      }
      else
      {
        *(vetorauxiliar + j) = *(*(Time + posicaoJogadornoVetor) + i);
      }
    }
    free(*(Time + posicaoJogadornoVetor));//libero o vetor antigo
    *(Time + posicaoJogadornoVetor) = vetorauxiliar;//coloco o novo
    //atualizar o veo cartas na mao
    *(cartasnaMao + posicaoJogadornoVetor) = *(cartasnaMao + posicaoJogadornoVetor) - 1;
  }
  //se nao retorna um valor negativo (sinaliza)
  else
  {
    printf("Jogador %d: ", posicaoJogadornoVetor + 1);
    printf("Voce nao possui cartas validas para descartar!\n");
    ultimacartadescartada = 100;//vazio!
  }
  //Termnou o jogo?
  if(*(cartasnaMao + posicaoJogadornoVetor) == 0)//Ou seja se nao ha cartas na mao do jogador
  {
    //sinalizar fim de jogo
    ultimacartadescartada = - 5;
  }

  return ultimacartadescartada;
}
void puxaCarta(int** Time, int* cartasnaMao, int posicaoJogadornoVetor)
{
  int cartapuxada = rand()%56;
  printf("Jogador %d: ", posicaoJogadornoVetor + 1);
  printf("Voce puxou a carta:");
  print1Carta(cartapuxada);
  printf("\n");
  //adcionar uma nnova carta ao vetor
  *(Time + posicaoJogadornoVetor) = (int*) minhaRealloc(*(Time + posicaoJogadornoVetor), *(cartasnaMao + posicaoJogadornoVetor) * sizeof(int));
  *(*(Time + posicaoJogadornoVetor) + *(cartasnaMao + posicaoJogadornoVetor)) = cartapuxada; //atencao: -1 pois eh aritmetica de vetor um indice a menos
  //atualizar o tamanho do vetor cartas na mao
  *(cartasnaMao + posicaoJogadornoVetor) = *(cartasnaMao + posicaoJogadornoVetor) + 1;
}
int rodadaAntiHoraria(int** Time, int* cartasnaMao, int numeroJogadores, int ultimacartadescartada, int* ultimoaJogar, int* executadoRegraCartaEspecial)
{
  int descarteprovisorio;
  //secao descarte especial
  if(ultimacartadescartada% 14 == 13 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
  }
  if(ultimacartadescartada% 14 == 12 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
    if(*ultimoaJogar > 1)
    {
      *ultimoaJogar = (*ultimoaJogar - 2)%numeroJogadores;//pula o proximo jogador //veja que quando chega ao numero retorna a zero
    }
    else if(*ultimoaJogar == 1)
    {
      *ultimoaJogar = numeroJogadores - 1;//para o ultimo jogadr
    }
    else
    {
      *ultimoaJogar = numeroJogadores - 2;//para antepenultimo jogador
    }
    //veja não tem acao para este jogador :(
  }
  else if(ultimacartadescartada% 14 == 11 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
    if(*ultimoaJogar != 0)
    {
      *ultimoaJogar = (*ultimoaJogar - 1)%numeroJogadores;//pula o proximo jogador //veja que quando chega ao numero retorna a zero
    }
    else
    {
      *ultimoaJogar = numeroJogadores - 1;
    }
    puxaCarta(Time, cartasnaMao, *ultimoaJogar);//veja ele puxa duas cartas em seguida;
    puxaCarta(Time, cartasnaMao, *ultimoaJogar);
    if(*ultimoaJogar != 0)
    {
      *ultimoaJogar = (*ultimoaJogar - 1)%numeroJogadores;//pula o proximo jogador //veja que quando chega ao numero retorna a zero
    }
    else
    {
      *ultimoaJogar = numeroJogadores - 1;
    }
  }
  else if(ultimacartadescartada% 14 == 10 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
    puxaCarta(Time, cartasnaMao, (*ultimoaJogar + 1)%numeroJogadores);
    if(*ultimoaJogar != 0)
    {
      *ultimoaJogar = (*ultimoaJogar - 1)%numeroJogadores;//pula o proximo jogador //veja que quando chega ao numero retorna a zero
    }
    else
    {
      *ultimoaJogar = numeroJogadores - 1;
    }
  }
  else
  {
    if(*ultimoaJogar != 0)//passamos para o proximo jogador
    {
      *ultimoaJogar = (*ultimoaJogar - 1)%numeroJogadores;//pula o proximo jogador //veja que quando chega ao numero retorna a zero
    }
    else
    {
      *ultimoaJogar = numeroJogadores - 1;
    }
  }
  //Continua o jogo
  print1Carta(ultimacartadescartada);
  printf("\n");
  printCartasMao(Time, cartasnaMao, *ultimoaJogar);
  descarteprovisorio = descartaCarta(Time, cartasnaMao, *ultimoaJogar, ultimacartadescartada);
  if(descarteprovisorio == 100)//ou seja nao ha carta para o jogador
  {
    puxaCarta(Time, cartasnaMao, *ultimoaJogar);//puxa uma carta
    printCartasMao(Time, cartasnaMao, *ultimoaJogar);
    descarteprovisorio = descartaCarta(Time, cartasnaMao, *ultimoaJogar, ultimacartadescartada);
      if(descarteprovisorio != 100)
      {
        *executadoRegraCartaEspecial = 0;
        ultimacartadescartada = descarteprovisorio;
      }
  }
  else
  {
    *executadoRegraCartaEspecial = 0;
    ultimacartadescartada = descarteprovisorio;
  }
  return ultimacartadescartada;
}
int rodadaHoraria(int** Time, int* cartasnaMao, int numeroJogadores, int ultimacartadescartada, int* ultimoaJogar, int* executadoRegraCartaEspecial)
{
  int descarteprovisorio;
  //secao descarte especial
  if(ultimacartadescartada% 14 == 13 && *executadoRegraCartaEspecial == 0)//evita um loop de RC -> Nao tem carta <- Retorna para o mesmo
  {
    *executadoRegraCartaEspecial = 1;
  }
  if(ultimacartadescartada% 14 == 12 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
    *ultimoaJogar = (*ultimoaJogar + 2)%numeroJogadores;//pula o proximo jogador //veja que quando chega ao numero retorna a zero
    //veja não tem acao para este jogador :(
  }
  else if(ultimacartadescartada% 14 == 11 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
    *ultimoaJogar = (*ultimoaJogar + 1)%numeroJogadores;
    puxaCarta(Time, cartasnaMao, *ultimoaJogar);//veja ele puxa duas cartas em seguida;
    puxaCarta(Time, cartasnaMao, *ultimoaJogar);
    *ultimoaJogar = (*ultimoaJogar + 1)%numeroJogadores;//O proximo jogador nao joga e
  }
  else if(ultimacartadescartada% 14 == 10 && *executadoRegraCartaEspecial == 0)
  {
    *executadoRegraCartaEspecial = 1;
    if(*ultimoaJogar == 0)//loop como em sentido antihorario
    {
      *ultimoaJogar = numeroJogadores - 1;//retona
      puxaCarta(Time, cartasnaMao, *ultimoaJogar);//mnda puxar
      *ultimoaJogar = (*ultimoaJogar + 1)%numeroJogadores;//volta para o orignal
    }
    else
    {
      puxaCarta(Time, cartasnaMao, (*ultimoaJogar - 1)%numeroJogadores);//manda o anterior puxar
    }
    *ultimoaJogar = (*ultimoaJogar + 1)%numeroJogadores;//deixa em ponto para o proximo jogador valido.
  }
  else
  {
    *ultimoaJogar = (*ultimoaJogar + 1)%numeroJogadores;
  }
  //Continua o jogo
  print1Carta(ultimacartadescartada);
  printf("\n");
  printCartasMao(Time, cartasnaMao, *ultimoaJogar);
  descarteprovisorio = descartaCarta(Time, cartasnaMao, *ultimoaJogar, ultimacartadescartada);
  if(descarteprovisorio == 100)//ou seja nao ha carta para o jogador
  {
    puxaCarta(Time, cartasnaMao, *ultimoaJogar);//puxa uma carta
    printCartasMao(Time, cartasnaMao, *ultimoaJogar);
    descarteprovisorio = descartaCarta(Time, cartasnaMao, *ultimoaJogar, ultimacartadescartada);
      if(descarteprovisorio != 100)
      {
        *executadoRegraCartaEspecial = 0;
        ultimacartadescartada = descarteprovisorio;
      }
  }
  else
  {
    *executadoRegraCartaEspecial = 0;
    ultimacartadescartada = descarteprovisorio;
  }
  return ultimacartadescartada;
}
int primeiraAcao(int** Time, int* cartasnaMao, int numeroJogadores, int* ultimoaJogar)
{
  int ultimacartadescartada;
  //primeira acao descartar primeira carta
  printf("Jogador %d:", *ultimoaJogar + 1);
  printCartasMao(Time, cartasnaMao, *ultimoaJogar);//Enviar jogador e o numero de cartas em sua mao
  ultimacartadescartada = descartaPrimeiraCarta(Time, cartasnaMao, *ultimoaJogar);//Sempre comecamos com o jogador 1 para simplificar
  return ultimacartadescartada;
}
int* criaJogador(int tamanhoPrimeiraMao)
{
  int i;
  int* jogador;
  jogador = (int*) calloc (tamanhoPrimeiraMao, sizeof(int));
  if(jogador == NULL)
  {
    printf("Erro na alocacao");
    exit(1);
  }
  else
  {
    for(i = 0; i < tamanhoPrimeiraMao; i++)
    {
      *(jogador + i) = rand()%56;//55 cartas
    }
  }
  return jogador;
}
int** criarTime(int* cartasnaMao, int* numeroJogadores)
{
  int i;
  int** Time;
  do
  {
    printf("Jogo UNO\nQuantos jogadores irao participar (3 a 6)?\n");
    scanf("%d", numeroJogadores);
  }while(!(*numeroJogadores >= 3 && *numeroJogadores <= 6));
  Time = (int**) calloc(*numeroJogadores, sizeof(int*));
  if(Time == NULL)
  {
    printf("Erro na alocacao");
    exit(1);//Nao sei por que mas acho que iss não é recomendado...se eu retirar ele sai do programa mesmo
  }
  else
  {
    for(i = 0; i < *numeroJogadores; i++)
    {
      *(Time + i) = criaJogador(TAMANHOPRIMEIRAMAO);
    }
  }
  return Time;
}
void liberaMatriz(int** Matriz, int NLinhas)
{
  int linha;
  for(linha = 0; linha< NLinhas;linha++)
  {
    free(Matriz[linha]);//liberar cada vetor (linha)
  }
  free(Matriz);//Liberar a propria matriz que apontava para o primeiro elemento do vetor de ponteiros
}
void jogoUno()
{
  int** Time;
  int* cartasnaMao = NULL;
  int executadoRegraCartaEspecial = 0;
  int numeroJogadores;
  int ultimoaJogar = PRIMEIROAJOGAR;//representara o jogador entre 0 e 3 (###temp imprementar)
  int ultimacartadescartada;
  srand(time(NULL));//Não confunda Time = grupo com time(hora em ingles)
  Time = criarTime(cartasnaMao, &numeroJogadores);//Arrumando...
  cartasnaMao = criaVetorCartasnaMao(numeroJogadores);
  ultimacartadescartada = primeiraAcao(Time, cartasnaMao, numeroJogadores, &ultimoaJogar);
  //jogo propriamente dito
  do
  {
    if(ultimacartadescartada% 14 == 13 && ultimacartadescartada != -5)//reversa
    {
      do
      {
        ultimacartadescartada = rodadaAntiHoraria(Time, cartasnaMao, numeroJogadores, ultimacartadescartada, &ultimoaJogar, &executadoRegraCartaEspecial);
      }while(!(ultimacartadescartada == -5 || (ultimacartadescartada% 14 == 13 && executadoRegraCartaEspecial == 0)));
    }
    if(ultimacartadescartada != -5)//condicao de termino do jogo eh uma carta -5
    {
      do
      {
        ultimacartadescartada = rodadaHoraria(Time, cartasnaMao, numeroJogadores, ultimacartadescartada, &ultimoaJogar, &executadoRegraCartaEspecial);
      }while(!(ultimacartadescartada == -5 || (ultimacartadescartada% 14 == 13 && executadoRegraCartaEspecial == 0)));
    }
  }while(ultimacartadescartada >= 0);//temp
  printf("Jogador %d: ", ultimoaJogar + 1);
  printf("Parabens! Voce Ganhou! Poderia ficar horas escrevendo uma mensagem de felicitacoes, mas tenho de estudar Calculo :(");
  liberaMatriz(Time, numeroJogadores);
  free(cartasnaMao);
  getchar();//Ver a gloria de ganhar
  getchar();
}
int main()
{
  jogoUno();
  return 0;
}
