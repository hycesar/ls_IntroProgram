#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMITEPASTAS 50
#define LIMITEARQUIVOS 50
//L5q3
typedef struct arquivo
{
  char* conteudo;
  char* nome;
}Arquivo;
typedef struct pasta
{
  char* nome;
  struct pasta* subPasta;
  struct arquivo* subArquivo;
  struct pasta* pastaAcima;
  int qntSubPastas;//Auxilia o tamanho do vetor acima
  int qntSubArquivos;//Auxilia o tamanho do vetor acima
}Pasta;
  Pasta* raiz = NULL;
  Pasta* atual = NULL;
int acharTituloPasta(char* nomePasta)//retorna zero se nao achar e >0 (a posicao e nao o indice) caso encontre
{
  int i, achou = 0;
  for(i = 0; i < atual->qntSubPastas && !achou && atual->subPasta != NULL; i++)
  {
    if(!(strcmp(atual->subPasta[i].nome, nomePasta)))//Nao existe no interior da pasta
    {
      achou = i + 1;
    }
  }
  return achou;//se achar, sinalizará numero negativo
}
int acharTituloArquivos(char* nomeArquivo)//retorna zero se nao achar e >0 (a posicao e nao o indice) caso encontre
{
  int i, achou = 0;
  for(i = 0; i < atual->qntSubArquivos && !achou && atual->subArquivo != NULL; i++)
  {
    if(!(strcmp(atual->subArquivo[i].nome, nomeArquivo)))//Nao existe no interior da pasta
    {
      achou = i + 1;
    }
  }
  return achou;//se achar, sinalizará numero negativo
}
int cd(char* nomePasta)//ok se bem sucedido retorna 1
{
  int sucesso = 1;
  if(!(strcmp(nomePasta , "..")))//valor igual
  {
    if(atual->pastaAcima)
    {
      atual = atual->pastaAcima;
    }
    else
    {
      printf("Erro: Nao existe pasta acima");
      sucesso = 0;
    }
  }
  else if((strcmp(nomePasta, ".")))//valor diferente
  {
    if(acharTituloPasta(nomePasta) > 0)//Ou seja existe uma pasta e tenho a localizacao (indice + 1)
    {
      atual = atual->subPasta + (acharTituloPasta(nomePasta) - 1);//apontando para subpasta
    }
    else
    {
      printf("Erro: Nao existe uma pasta com esse nome\n");
      sucesso = 0;
    }
  }
  return sucesso;
}

void mkdir(char* nomePasta);//prototipo da funcao;

char* formatarArgumento(char* nome)
{
  int i = 0, j = 0;
  Pasta* pAuxiliar = atual;
  char* novoArgumento = NULL;//crio novo argumento fragmentando
  if(nome[i] == '/')//trata se de um caminho e nao arquivo
  {
    do
    {
      i++;//desconsidera /
      for(j = 0; nome[i] != '/' && nome[i] != '\n' && nome[i] != ' ' && nome[i] != '\0'; i++, j++)
      {
        novoArgumento = (char*) realloc(novoArgumento, (i + 1)*sizeof(char));
        novoArgumento[j] = nome[i];
      }
      if(nome[i] == '/')
      {
        novoArgumento[j] = '\0';//fecha string
        pAuxiliar = atual;
        atual = raiz;
        if(!cd(novoArgumento))//Se for um caminho vou entrando...
        {
          atual = pAuxiliar;
        }
      }
    }
    while(nome[i] != '\n' && nome[i] != ' ' && nome[i] != '\0');
    novoArgumento[j] = '\0';//fecha string
  }
  else
  {
    novoArgumento = nome;
  }
  return novoArgumento;
  }
int contaCaminho(char* nome)//conta quantidade de vezes que tenho de voltar a parta original quando o argumento eh um caminho
{
  int i = 0;
  int qntBarras = 0;
  while(nome[i] != '\0')
  {
    if(nome[i] == '/')
    {
      qntBarras++;
    }
    i++;
  }
  if(qntBarras > 0)//qntBarras eh contado mais de uma vez
  {
    qntBarras--;
  }
  return qntBarras;
}
void imprimirTerminal(int i)//imprime o inicio da tela antes de esperar comando//sempre com zero de argumento para imprimir $ ou 1 para o resto
{
  //int i = primeiro nivel de recursão
  Pasta* pAuxiliar = atual;
  if(atual->pastaAcima)//Conto os níveis
  {
    cd("..");
    imprimirTerminal(i + 1);
  }
  if(pAuxiliar->nome && i > 1)
  {
    printf("/%s", pAuxiliar->nome); //Imprimir que / pasta
  }
  else if(pAuxiliar->nome && i == 0)
  {
    printf("%s$", pAuxiliar->nome);//que estou seguido de $
  }
  else if(pAuxiliar->nome && i == 1)
  {
    printf("/%s/", pAuxiliar->nome);//sem o $
  }
  else
  {
    printf("/");//apenas para imprimir o caso no null (raix)
  }
  atual = pAuxiliar;//retorna o valor original
}
void inicializarPasta()//Substitui memset(ptr, 0, sizeof(ptr))
{
  atual->nome = NULL;
  atual->subPasta = NULL;
  atual->subArquivo = NULL;
  atual->pastaAcima = NULL;
  atual->qntSubPastas = 0;
  atual->qntSubArquivos = 0;
}
void inicializarArquivo()
{
  atual->subArquivo[atual->qntSubArquivos - 1].nome = NULL;
  atual->subArquivo[atual->qntSubArquivos - 1].conteudo = NULL;
}
char* preencheArray()
{
  char dado;
  int i = 0;//posicao do vetor é zero, primeira execucao
  char* vetor = (char*) malloc(sizeof(char));
  do
  {
    scanf("%c", &dado);
    if(dado != ' ' && dado != '\n')//caractere valido?
    {
      vetor = (char*) realloc(vetor, i + 1 * sizeof(char));
      if(vetor == NULL)
      {
        printf("\tErro na realocacao\n");
        exit(1);
      }
      else
      {
        *(vetor + i) = dado;//preecho o dado
        i++;
      }
    }
  }while(dado != ' ' && dado != '\n');
  *(vetor + i) = '\0';//preenchendo com /0 para finalizar string
  return vetor;
}
char* preencheArrayEnter()
{
  char dado;
  int i = 0;//posicao do vetor é zero, primeira execucao
  char* vetor = (char*) malloc(sizeof(char));
  do
  {
    scanf("%c", &dado);
    if(dado != '\n')//caractere valido?
    {
      vetor = (char*) realloc(vetor, i + 1 * sizeof(char));
      if(vetor == NULL)
      {
        printf("\tErro na realocacao\n");
        exit(1);
      }
      else
      {
        *(vetor + i) = dado;//preecho o dado
        i++;
      }
    }
  }while(dado != '\n');
  *(vetor + i) = '\0';//preenchendo com /0 para finalizar string
  return vetor;
}
void mkdir(char* nomePasta)//ok
{
  int qntRetornos = contaCaminho(nomePasta);//conto qnt de entradas CD
  nomePasta = formatarArgumento(nomePasta);//formato o argumento no formato nomePasta e nao caminho

  atual->subPasta = (Pasta*) realloc(atual->subPasta, (atual->qntSubPastas + 1) * sizeof(Pasta));//crio + 1 pasta
  if(atual->subPasta != NULL)
  {
    if(atual->qntSubPastas <= LIMITEPASTAS)
    {
      if(acharTituloPasta(nomePasta) == 0)//Ou seja nao existe uma pasta dessa
      {
        Pasta* pAuxiliar;//crio um ponteiro auxiliar
        atual->qntSubPastas++;//atualizando qntidade
        pAuxiliar = atual;//quardo o valor de atual
        atual = atual->subPasta + (atual->qntSubPastas - 1);//entro na subpasta
        inicializarPasta();//zero o interior do vetor;
        atual->nome = nomePasta;//coloco o nome;
        atual->pastaAcima = pAuxiliar;// coloco o endereço acima
        atual = pAuxiliar;//volto a pasta inicial
      }
      else
      {
        printf("Erro: Ja existe uma pasta com mesmo nome\n");
      }
    }
    else
    {
      printf("Erro:Limite de pastas eh %d\n", LIMITEPASTAS);
    }
  }
  else
  {
    printf("Erro: Realloc\n");
    exit(1);
  }

  while(qntRetornos > 0)//por fim retorno a posicao original da pasta
  {
    cd("..");
    qntRetornos--;
  }
}
void criaArvoreInicial()//ok
{
  char* nomePasta = "home";//especificado no problema
  raiz = (Pasta*) malloc(sizeof(Pasta));//criando pasta raiz;
  atual = raiz;
  inicializarPasta();//zerar conteudo da raiz
  mkdir(nomePasta);//criar subpasta home
  cd(nomePasta);//Começar por home
}
void ls()
{
  int i;
  for(i = 0; i < atual->qntSubPastas; i++)//diretorio
  {
    printf("%s \t[D]\n", atual->subPasta[i].nome);
  }
  for(i = 0; i < atual->qntSubArquivos; i++)//arquivos
  {
    printf("%s \t[F]\n", atual->subArquivo[i].nome);
  }
}
void touch(char* texto, char* nomeArquivo)//percebaque ta nvertido pois ele é "lido" da direita para esquerda, entao pego primeiro o nome mais a direita
{
  int qntRetornos = contaCaminho(nomeArquivo);//conto qnt de entradas CD
  nomeArquivo = formatarArgumento(nomeArquivo);//formato o argumento no formato nomePasta e nao caminho

  atual->subArquivo = (Arquivo*) realloc(atual->subArquivo, (atual->qntSubArquivos + 1) * sizeof(Arquivo));//crio + 1 pasta
  if(atual->subArquivo != NULL)
  {
    if(atual->qntSubArquivos <= LIMITEPASTAS)
    {
      if(acharTituloArquivos(nomeArquivo) == 0)//Ou seja nao existe uma pasta dessa
      {
        atual->qntSubArquivos++;//atualizando qntidade
        inicializarArquivo();//zero o interior do vetor;
        atual->subArquivo[atual->qntSubArquivos - 1].nome = nomeArquivo;
        atual->subArquivo[atual->qntSubArquivos - 1].conteudo = texto;
      }
      else
      {
        printf("Erro: Ja existe um arquivo com mesmo nome\n");
      }
    }
    else
    {
      printf("Erro:Limite de pastas eh %d\n", LIMITEARQUIVOS);
    }
  }
  else
  {
    printf("Erro: Realloc\n");
    exit(1);
  }

  while(qntRetornos > 0)//por fim retorno a posicao original da pasta
  {
    cd("..");
    qntRetornos--;
  }
}
void cat(char* nomeArquivo)
{
  int qntRetornos = contaCaminho(nomeArquivo);//conto qnt de entradas CD
  nomeArquivo = formatarArgumento(nomeArquivo);//formato o argumento no formato nomePasta e nao caminho

  int i = acharTituloArquivos(nomeArquivo);
  if(i != 0)//Ou seja nao existe uma pasta dessa
  {
    printf("%s\n", atual->subArquivo[i - 1].conteudo);
  }
  else
  {
    printf("Erro: Nao existe um arquivo esse nome\n");
  }

  while(qntRetornos > 0)//por fim retorno a posicao original da pasta
  {
    cd("..");
    qntRetornos--;
  }
}
void auxiliarLocate(char* nome)//aqui eu uso recursão
{
  int i = acharTituloArquivos(nome);
  int j = acharTituloPasta(nome);
  int k;
  Pasta* pAuxiliarRecursivo = atual;//quardo a posição
  if(i != 0)//arquivo
  {
    imprimirTerminal(1);// 1 para nao imprimir o $
    printf("%s \t[F]\n", atual->subArquivo[i - 1].nome);//conversao para indice (- 1)
  }
  //Pastas
  if(j != 0)//me passa a posicao
  {
    imprimirTerminal(1);// 1 para nao imprimir o $
    printf("%s \t[D]\n", atual->subPasta[j - 1].nome);
  }
  //ainda tem pasta dentro?
  if(atual->qntSubPastas)//ou seja se tenho uma
  {
    for(k = 0; k < pAuxiliarRecursivo->qntSubPastas; k++)
    {
      atual = &(atual->subPasta[k]);
      auxiliarLocate(nome);
      atual = pAuxiliarRecursivo;//etona a pasta original
    }
  }
}
void locate()
{
  Pasta* auxiliar = atual;//guardo o valor atual
  atual = raiz;//inicio pela raiz
  auxiliarLocate(preencheArray());
  atual = auxiliar;//devolvo o valor guardado
}
void freePasta(Pasta* pasta)//vou entrando na arvore e liberando do mais interno até o mais externo
{
//  int i;
  if(pasta->qntSubPastas == 0)
  {
    free(pasta->subPasta);
  }
  else
  {
//    for(i = 0; i <= pasta->qntSubPastas; i++)
//    {
      freePasta(pasta->subPasta);
//    }
    free(pasta->subPasta);
//
  }
//  Pasta* pAuxiliar = atual->subPasta + i;//guardo o valor inicial
//  for(i = 0; i < atual->qntSubPastas; i++)
//  {
//    freePastaRecursivo(pAuxiliar);
//  }
//  free(atual->subPasta);
//  atual = pAuxiliar;//retorno o orginial
}
Pasta* minhaReallocPasta(int indice)//argumento: posicao da estrutura a retirar
{
  int i, j;
  Pasta* novaSubPasta = (Pasta*) malloc((atual->qntSubPastas - 1) * sizeof(Pasta));
  if(novaSubPasta != NULL)
  {
    atual->qntSubPastas--;//atualizo qnt de pastas
    for(i = j = 0; i < indice - 1; i++, j++)
    {
      novaSubPasta[j] = atual->subPasta[i];
    }
    freePasta(atual->subPasta + i);
    i++;//inicia com i++ para pular proxima estrutura
    for(; i <= atual->qntSubPastas; i++, j++)
    {
      novaSubPasta[j] = atual->subPasta[i];
    }
    free(atual->subPasta);//apago a subpasta
  }
  else
  {
    printf("Erro ao realocar!\n");
    exit(1);
  }
  return novaSubPasta;//retorna noava subpasta
}
Arquivo* minhaReallocArquivo(int indice)//argumento: posicao da estrutura a retirar
{
  int i, j;
  Arquivo* novaSubArquivo = (Arquivo*) malloc((atual->qntSubArquivos - 1) * sizeof(Arquivo));
  if(novaSubArquivo != NULL)
  {
    atual->qntSubArquivos--;//atualizo qnt de Arquivos
    for(i = j = 0; i < indice - 1; i++, j++)
    {
      novaSubArquivo[j] = atual->subArquivo[i];
    }
    i++;//inicia com i++ para pular proxima estrutura
    for(; i <= atual->qntSubArquivos; i++, j++)
    {
      novaSubArquivo[j] = atual->subArquivo[i];
    }
  }
  else
  {
    printf("Erro ao realocar!\n");
    exit(1);
  }
  return novaSubArquivo;//retorna noava subArquivo
}
void rm(char* nome)
{
  int qntRetornos = contaCaminho(nome);//conto qnt de entradas CD
  nome = formatarArgumento(nome);//formato o argumento no formato nomePasta e nao caminho

  int i = acharTituloArquivos(nome);
  int j = acharTituloPasta(nome);
  if(i == 0 && j == 0)
  {
    printf("Erro: Nao ha item para excluir");
  }
  else
  {
    if(i != 0)//arquivo
    {
      atual->subArquivo = minhaReallocArquivo(i);
    }
    //Pastas
    if(j != 0)//me passa a posicao
    {
      atual->subPasta = minhaReallocPasta(j);
    }
  }

  while(qntRetornos > 0)//por fim retorno a posicao original da pasta
  {
    cd("..");
    qntRetornos--;
  }
}
void comando()
{
  criaArvoreInicial();
  char* opcao;
  do
  {
    imprimirTerminal(0);//sempre com 0 primeiro nivel de recursao
    opcao = preencheArray();
    if(!(strcmp(opcao, "ls")))
    {
      ls();
    }
    else if(!(strcmp(opcao, "cd")))
    {
      cd(preencheArrayEnter());
    }
    else if(!(strcmp(opcao, "mkdir")))
    {
      mkdir(preencheArrayEnter());
    }
    else if(!(strcmp(opcao, "touch")))
    {
      touch(preencheArrayEnter(), preencheArray());
    }
    else if(!(strcmp(opcao, "cat")))
    {
      cat(preencheArrayEnter());
    }
    else if(!(strcmp(opcao, "locate")))
    {
      locate();
    }
    else if(!(strcmp(opcao, "rm")))
    {
      rm(preencheArrayEnter());
    }
    else if(strcmp(opcao, "exit"))
    {
      printf("Erro: comandos invalido. Maiusculo?\n");
      fflush(stdin);//liba buffer e tentamos novamente;
    }
  }while(strcmp(opcao, "exit"));
  free(raiz);//liberando
  free(atual);
}
int main()
{
  comando();
  return 0;
}
