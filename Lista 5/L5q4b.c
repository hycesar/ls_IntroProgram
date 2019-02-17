#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//L5q4
typedef struct machine
{
  int numSerie;
  char data[11];
  char funcao[21];
}Machine;
typedef struct human
{
  int idade;
  char sexo[10];
  float tempoPreparo;
}Human;
typedef enum type
{
  humano, maquina
}Type;
typedef union characteristics
{
  Human* humano;
  Machine* maquina;
}Characteristics;
typedef struct element
{
  char* subject_name;
  Type* subject_type;
  Characteristics* subject_characteristics;
}Element;
typedef struct key
{
  int key_num;
  Element* key_elem;
}Key;
typedef struct database
{
  Key** database_key;
  int password;
  char* nome;
}Database;
char* preeche()//preencher char
{
  fflush(stdin);
  int ch = 1;
  char dado = 0;
  char* retorno = (char*) malloc (ch * sizeof(char));
  if(retorno != NULL)
  {
    do
    {
      scanf("%c", &dado);
      if(dado != '\n')
      {
        ch++;//char valido
        retorno = (char*) realloc(retorno, ch * sizeof(char));
        retorno[ch - 2] = dado;
      }
      if(!((dado <= 'z' && dado >= 'a') || (dado <= 'Z' && dado >= 'A') || (dado <= '9' && dado >= '0') || (dado == '\n')))//nao alpha numerico?
      {
        printf("Erro: Somente alphanumericos!\n");
        retorno = NULL;
      }
    }while(dado != '\n' && retorno != NULL);
    if(retorno != NULL)
    {
      retorno[ch - 1] = '\0';
    }
  }
  else
  {
    printf("Erro: Alloc1");
    exit(1);
  }
  return retorno;
}
int convertePWDtoINT(char* password)//comverterpassword em numero
{
  int i = 0, convertido = 0;
  if(password != NULL)
  {
    while(password[i] != '\0')
    {
      convertido = (convertido * i) + (password[i] - '0');
      i++;
      if(convertido > 50000000)
      {
        convertido %= 10000000;
      }
    }
  }
  if(password != NULL)
  {
    free(password);//Nao mais preciso do vetor ja libeto
    printf("%d\n", convertido);
  }
  return convertido;
}
Database* createNull()
{
  Database* novo = (Database*) malloc (sizeof(Database));
  if(novo != NULL)
  {
    (*novo).nome = NULL;
    (*novo).password = 0;
    (*novo).database_key = NULL;
  }
  else
  {
    printf("Erro:Alloc2");
    exit(1);
  }
  return novo;
}
Database* create(char* PWD)
{
  Database* novo = (Database*) malloc (sizeof(Database));
  if(novo != NULL)
  {
    printf("Digite o nome do Banco de dados: ");
    if(((*novo).nome = preeche()))
    {
      printf("Banco [%s]: criado com sucesso!\n", novo->nome);
    }
    if(((*novo).password = convertePWDtoINT(PWD)))
    {
      printf("Senha atribuida com sucesso!\n");
    }
    novo->database_key = (Key**) malloc(sizeof(Key*));
    if(novo->database_key != NULL)
    {
      novo->database_key = (Key*) malloc(sizeof(Key));
      if(novo->database_key != NULL)
      {
        novo->database_key = NULL;
      }
    }
  }
  else
  {
    printf("Erro: Alloc1");
    exit(1);
  }
  return novo;
}
int qntKeys(Database* bancoDados)
{
  //qnts keys existem?
  int qntKeys = 0;
  if((*bancoDados).database_key != NULL)
  {
    while(*((*bancoDados).database_key + qntKeys) != NULL)
    {
      qntKeys++;
    }
  }
  return qntKeys;
}
int adicionaKey(Database* bancoDados, Key* chave)
{//adicionar mais uma key
  int quantidadeKeys = qntKeys(bancoDados);
  int posicaoTroca;
  Key* nova_database_key = (Key*) malloc((quantidadeKeys + 1 ) * sizeof(Key));
  if(bancoDados->database_key != NULL)
  {
    //descobrir ordem de copia
    int ordem = 0, j = 0;
    while(bancoDados->database_key[ordem]->key_num < chave->key_num)
    {
      nova_database_key[j] = *(bancoDados->database_key[ordem]);
      ordem++;
      j++;
    }
    //retorno essa posicao para manipular elementos
    posicaoTroca = j;
    //copio o elemento novo
    nova_database_key[j] = *(chave);
    j++;
    while(ordem <= quantidadeKeys)
    {
      nova_database_key[j] = *(bancoDados->database_key[ordem]);
      ordem++;
      j++;
    }
  }
  else
  {
    //tb copia mas fecha com null
    int j = 0, ordem = 0;
    //retorno essa posicao para manipular elementos
    posicaoTroca = j;
    nova_database_key[j] = *(chave);
    j++;
//    while(ordem <= quantidadeKeys)
//    {
//      nova_database_key[j] = *(bancoDados->database_key[ordem]);
//      ordem++;
//      j++;
//    }
  }
  bancoDados->database_key = &nova_database_key;

  ///minhafree(nova_database_key);

  return posicaoTroca;
}
void write(Key* chave, Element* elemento, Database* bancoDados, char* password)
{
  int posicaoInsecao;
  if(bancoDados->password == convertePWDtoINT(password))
  {
    posicaoInsecao = adicionaKey(bancoDados, chave);
    *(bancoDados->database_key[posicaoInsecao]->key_elem) = *elemento;
  }
  else
  {
    printf("Erro:Senha invalida\n");
  }
}
int eraserKey(Database* bancoDados, Key* chave)
{
  int quantidadeKeys = qntKeys(bancoDados);
  int posicaoTroca;
  Key* nova_database_key = (Key*) malloc((quantidadeKeys + 1 ) * sizeof(Key));
  if(bancoDados->database_key != NULL)
  {
    //descobrir ordem de copia
    int ordem = 0, j = 0;
    while(bancoDados->database_key[ordem]->key_num != chave->key_num)
    {
      nova_database_key[j] = *(bancoDados->database_key[ordem]);
      ordem++;
      j++;
    }
    //retorno essa posicao para manipular elementos
    posicaoTroca = j;
    //pulo o elemento novo
///    nova_database_key[j] = *(chave);
    ordem++;
    while(ordem <= quantidadeKeys)
    {
      nova_database_key[j] = *(bancoDados->database_key[ordem]);
      ordem++;
      j++;
    }
  }
  else
  {
    //tb copia mas fecha com null
    int j = 0, ordem = 0;
    //retorno essa posicao para manipular elementos
    posicaoTroca = j;
    nova_database_key[j] = *(chave);
    ordem++;
    while(ordem <= quantidadeKeys)
    {
      nova_database_key[j] = *(bancoDados->database_key[ordem]);
      ordem++;
      j++;
    }
  }
  bancoDados->database_key = &nova_database_key;
    ///minhafree( *(bancoDados->database_key[posicaoTroca] );//retorno a key para apagar em Free

  return posicaoTroca;
}
void eraser(Key* chave, Database* bancoDados, char* password)
{
  if(bancoDados->password == convertePWDtoINT(password))
  {
    eraserKey(bancoDados, chave);
  }
  else
  {
    printf("Erro:Senha invalida\n");
  }
}
void printfElemento(Element* qualquer)
{
  printf("%s\n", qualquer->subject_name);
  if(qualquer->subject_type == 0)//humano
  {
    printf("Idade:%d\n", qualquer->subject_characteristics->humano->idade);
    printf("Sexo:%s\n", qualquer->subject_characteristics->humano->sexo);
    printf("Tempo Miojo:%f\n", qualquer->subject_characteristics->humano->tempoPreparo);
  }
  else//maquina
  {
    printf("Data:%s\n", qualquer->subject_characteristics->maquina->data);
    printf("Funcao:%s\n", qualquer->subject_characteristics->maquina->funcao);
    printf("Serie:%d\n", qualquer->subject_characteristics->maquina->numSerie);
  }
}
void printfKey(Key* qualquer)
{
  printf("KeyNumber[%d]\n", qualquer->key_num);
  printfElemento(qualquer->key_elem);
}
void printfKDbRecursivo(Database* bancoDados, int ordem)//exigencia da questao :(
{
  if(bancoDados->database_key != NULL)
  {
    ordem++;
    printfKDbRecursivo(bancoDados, ordem);
  }
  else
  {
    printfKey(bancoDados->database_key[ordem]);
  }
}
void printfKDb(Database* bancoDados, char* password)
{
  if(bancoDados->password == convertePWDtoINT(password))
  {
    printf("%s", bancoDados->nome);
    printfKDbRecursivo(bancoDados, 0);//comecamos do inicio do vetor
  }
  else
  {
    printf("Erro:Senha invalida\n");
  }
}
void readerKey(Database* bancoDados, Key* chave)
{
  if(bancoDados->database_key != NULL)
  {
    //descobrir ordem de copia
    int ordem = 0;
    while(bancoDados->database_key[ordem]->key_num != chave->key_num)
    {
      ordem++;
    }
    printfElemento(bancoDados->database_key[ordem]->key_elem);
  }
  else
  {
    printf("Erro: BD Vazio\n");
  }
}
void reader(Key* chave, Database* bancoDados, char* password)
{
  if(bancoDados->password == convertePWDtoINT(password))
  {
    readerKey(bancoDados, chave);
  }
  else
  {
    printf("Erro:Senha invalida\n");
  }
}
Element* criaElementoEPreenche()
{
  int aux;
  Element* qualquer = (Element*) malloc(sizeof(Element));
  if(qualquer != NULL)
  {
    qualquer->subject_characteristics = (Characteristics*) malloc(sizeof(Characteristics));
    qualquer->subject_type = (Type*) malloc(sizeof(Type));
    if(qualquer->subject_characteristics != NULL && qualquer->subject_type != NULL)
    {
      printf("Nome do Elemento: ");
      qualquer->subject_name = preeche();
      do
      {
        printf("Trata-se de homem - 0 ou maquina - 1?");
        scanf("%d", &aux);
        if(aux == 0)
        {
          qualquer->subject_characteristics->humano = (Human*) malloc(sizeof(Human));

          if(qualquer->subject_characteristics->humano != NULL)
          {
//            qualquer->subject_type = humano;
            printf("Idade humana: ");
            scanf("%d", &qualquer->subject_characteristics->humano->idade);
            printf("Idade:%d\n", qualquer->subject_characteristics->humano->idade);
            fflush(stdin);
            printf("Genero: ");
            scanf("%s", qualquer->subject_characteristics->humano->sexo);
            fflush(stdin);
            printf("Sexo:%s\n", qualquer->subject_characteristics->humano->sexo);
            printf("Tempo de Miojo: ");
            scanf("%f", &qualquer->subject_characteristics->humano->tempoPreparo);
            printf("Tempo Miojo:%f\n", qualquer->subject_characteristics->humano->tempoPreparo);
          }
        }
        else if(aux == 1)
        {
          qualquer->subject_characteristics->maquina = (Machine*) malloc(sizeof(Machine));
          if(qualquer->subject_characteristics->maquina != NULL)
          {
//            qualquer->subject_type = maquina;
            printf("Data da Maquina Formato dd/mm/aaaa: ");
            scanf("%s", qualquer->subject_characteristics->maquina->data);
            fflush(stdin);
            printf("Data:%s\n", qualquer->subject_characteristics->maquina->data);
            printf("Funcao Maquina: ");
            scanf("%s", qualquer->subject_characteristics->maquina->funcao);
            fflush(stdin);
            printf("Funcao:%s\n", qualquer->subject_characteristics->maquina->funcao);
            printf("Num Serie Maquina: ");
            scanf("%d", &qualquer->subject_characteristics->maquina->numSerie);
            printf("Serie:%d\n", qualquer->subject_characteristics->maquina->numSerie);
          }
        }
        else
        {
          printf("Erro: Opcao invalida\n");
        }
      }while(!(aux >= 0 && aux <= 1));
    }
  }
  else
  {
    printf("Erro: Alloc 12");
    exit(1);
  }
  return qualquer;
}
Key* criaKeyEPreenche()
{
  Key* novo = (Key*) malloc(sizeof(Key));
  if(novo != NULL)
  {
    printf("Numero da Key, deve ser diferente de outra escolhida: ");
    scanf("%d", &novo->key_num);
  }
  else
  {
    printf("Erro: Alloc");
    exit(1);
  }
  return novo;
}
void freeStruct(Database* Struct)//vou entrando na arvore e liberando do mais interno até o mais externo
{
  int i;
  if(Struct->database_key != NULL)
  {
    for(i = 0; Struct->database_key != NULL; i++)
    {
      if(Struct->database_key[i]->key_elem->subject_characteristics->humano != NULL)
      {
        free(Struct->database_key[i]->key_elem->subject_characteristics->humano);
      }
      if(Struct->database_key[i]->key_elem->subject_characteristics->maquina != NULL)
      {
        free(Struct->database_key[i]->key_elem->subject_characteristics->maquina);
      }
      if(Struct->database_key[i]->key_elem->subject_characteristics != NULL)
      {
        free(Struct->database_key[i]->key_elem->subject_characteristics);
      }
      if(Struct->database_key[i]->key_elem->subject_name != NULL)
      {
        free(Struct->database_key[i]->key_elem->subject_name);
      }
      if(Struct->database_key[i]->key_elem->subject_type != NULL)
      {
        free(Struct->database_key[i]->key_elem->subject_type);
      }
      if(Struct->database_key[i]->key_elem != NULL)
      {
        free(Struct->database_key[i]->key_elem);
      }
      if(Struct->database_key + i != NULL)
      {
        free(Struct->database_key);
      }
    }
  }
}
void Destroy(Database* bancoDados, char* password)
{
  if(bancoDados->password == convertePWDtoINT(password))
  {
    freeStruct(bancoDados);
  }
  else if(!strcmp(password, "sair")) //finalizando...
  {
    freeStruct(bancoDados);
  }
  else
  {
    printf("Erro:Senha invalida\n");
  }
}
void programa()
{
  int opcao, numBanco;
  int qntBancoDados = 0;
  Database** novo = (Database**) malloc(sizeof(Database*));
  if(novo != NULL)
  {
    do
    {
      printf("<1>Create\t<2>Insert\t<3>Delete\n<4>Read \t<5>Print\t<6>Destroy\n<7>Sair\n>>>");
      scanf("%d", &opcao);
      if(opcao == 1)
      {
        printf("Digite senha do novo banco de dados: ");
        if((novo[qntBancoDados] = create(preeche())))//ja foi verificara allocacao (funcao com exit) nao reverificar
        {
          printf("Criacao:Todas operacoes realizadas com sucesso!\n");
          qntBancoDados++;
        }
      }
      else if(opcao == 2)
      {
        printf("Qual banco de dados quer, digite um numero partindo do 0?");
        scanf("%d", &numBanco);
        {
          printf("Digite a senha:");
          write(criaKeyEPreenche(), criaElementoEPreenche(), novo[numBanco], preeche());
        }
      }
      else if(opcao == 3)
      {
        printf("Qual banco de dados quer, digite um numero partindo do 0?");
        scanf("%d", &numBanco);
        {
          printf("Digite a senha:");
          eraser(criaKeyEPreenche(), novo[numBanco], preeche());
        }
      }
      else if(opcao == 4)
      {
        printf("Qual banco de dados quer, digite um numero partindo do 0?");
        scanf("%d", &numBanco);
        {
          printf("Digite a senha:");
          reader(criaKeyEPreenche(), novo[numBanco], preeche());
        }
      }
      else if(opcao == 5)
      {
        printf("Qual banco de dados quer, digite um numero partindo do 0?");
        scanf("%d", &numBanco);
        {
          printf("Digite a senha: ");
          printfKDb(novo[numBanco], preeche());
        }
      }
      else if(opcao == 6)
      {
        printf("Qual banco de dados quer, digite um numero partindo do 0?");
        scanf("%d", &numBanco);
        {
          printf("Senha do banco de dados: ");
          Destroy(novo[numBanco], "sair");
        }
        free(novo);
      }
      else if(opcao == 7)
      {
        printf("Finalizando...");
        int i = 0;
        while(i < qntBancoDados)
        {
          Destroy(novo[i], preeche());
        }
      }
      else
      {
        printf("\nErro: Selecao invalida\n");
        fflush(stdin);
      }
    }while(1);//opcao != 7
  }
  else
  {
    printf("Erro: alloc3");
    exit(1);
  }
}
int main()
{
  programa();
  return 0;
}
