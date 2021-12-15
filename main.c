/*De acordo com as políticas de entrega de atividades repassadas pelo professor, 
certifico que os algoritmos e programas que estou entregando são de minha autoria e 
que não os repassei ou os recebi de qualquer outra pessoa. Augusto Durães Camargo-190084731*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> /*biblioteca que eu usei para padronizar todas as informações salvas, com funções como tolower, toupper*/
#include <time.h> /*biblioteca que eu usei para pegar o horário do sistema*/

#define size 3000 /*tamanho que eu usei por segurança ,como tamanho máximo das minhas strings*/

typedef struct /*essa é a minha struct principal quee eu usei para os fornecedores*/
{              /*e que eu uso para  salvar no arquivo de fornecedores "fornecedor_restaurante.bin"*/
    char rest[size];
}fornecedor;

typedef struct /*essa é a struct que eu usei para os pedidos , é a que eu armazeno nos meu arquivo principal, "marm_arq.bin"*/
{
   char restaurante[size];
   char sabor[size];
   char tamanho[size]; 
   char usuario[size]; 
   char cronos[size]; /*existem duas variaveis de tempo , cronos e horapesquisa*/
   char horapesquisa[size]; /*cronos eu usei para salvar a hora que sera exibida, já horapesquisa eu usei para salvar a hora para ser pesquisada*/
}pedido;                    /*contendo apenas dois caracteres, os da hora atual */

typedef struct
{
    char forncopiado[size];  /*essa struct eu usei como um auxiliar para salvar todos os fornecedores, vito quee mesmo excluidos*/
}copiado;                    /*eles necessitam de ser contabilizados, eu armazeno essa struct em um arquivo auxiliar*/
                             /*arquvi auxiliar esse("copia_fornecedor.bin"), quee eu uso para guardar todos os fornecedores já cadastrados*/
struct copia                 
{
    char copiaforn[size];      /*essa struct tem a função de que quando eu abro os arquivos ,eu contabilizo todas as vendas através dela*/
    float vendido;
};
    /*lista das funções que eu usei no decorrer do meu programa*/
void clrscr();
void menuzero();
void registra_fornecedor();
void registra_pedido();
void exclui_fornecedor();
void consulta_pedido();
void emite_relatorio();
void padronizacao(char nome[]);

void main() /*apesar de ser o procedimento main, para uma melhor organização eu preferi deixar apenas um procedimento dentro dele*/
{
    menuzero();
}

void menuzero() /*o procedimento que contém o meu menu*/
{
    int escolha;                    /*dentro desse procedimento ,eu criei algumas variações de um menu*/
    int i = 0;
    int opcaozero = 0;
    int opcaoum = 0;
    pedido p;

    FILE *fornecedor_restaurante;
    FILE *marm_arq;
    /*aqui ele verifica se os arqivos existem, estão vazios ou não*/
    while(i == 0)               /*dependendo do retorno ele exibe diferentes menus, para o usuário não cometer um erro e quebrar o programa*/
    {                           /*obviamente, se o usuario tentar acesssar uma funcao que ainda não seja possível, o menu o  impedirá*/
        fflush(stdin);

        if((fornecedor_restaurante = fopen("fornecedor_restaurante.bin","rb")) == NULL)
        {
            opcaozero = 0;
        }else{
            fclose(fornecedor_restaurante); 
            opcaozero = 1;
        }

        if((marm_arq= fopen("marm_arq.bin","rb")) == NULL)
        {
            opcaoum = 0;
        }else{ 
            if(fread(&p,sizeof(pedido),1,marm_arq) == 0)
            {
                fclose(marm_arq);
                opcaoum = 1;
            }else{
                fclose(marm_arq);
                opcaoum = 2;
            }
        }

        if(opcaozero == 0){/*como aqui ainda não existe nenhum arquivo e nada cadastrado , ele apenas pode registrar um fornecedor*/
            clrscr();
            printf("\n");
            printf("        ****************************************\n");
            printf("        * Bem vindo ao gerenciador de marmita! *\n");
            printf("        ****************************************\n");
            printf("\n");
            printf("\n");
            printf("        ******************MENU******************\n");
            printf("        *   1 - Registrar fornecedor           *\n");
            printf("        *   2 - Sair                           *\n");
            printf("        ****************************************\n");

            scanf(" %d",&escolha);
                switch (escolha)
                {
                    case 1:
                        registra_fornecedor();
                        break;
                    case 2:
                        i++;
                        break;
                    default:
                    printf("Comando inexistente , insira novamente \n");
                    printf("\n");
                    printf("\n");
                        break;
                }
        }
        if(opcaozero != 0){ /*com um fornecedor já cadastrado, ele já pode registrar um pedido e excluir um fornecedor se for do seu gosto*/
            if(opcaoum == 0 || opcaoum == 1)
            {
            clrscr();
            printf("\n");
            printf("\n");
            printf("        ******************MENU******************\n");
            printf("        *   1 - Registrar fornecedor           *\n");
            printf("        *   2 - Registra pedido                *\n");
            printf("        *   3 - Exclui fornecedor              *\n");
            printf("        *   4 - Sair                           *\n");
            printf("        ****************************************\n");

            scanf(" %d",&escolha);

                switch (escolha)
                {
                    case 1:
                        registra_fornecedor();
                        break;
                    case 2: 
                        registra_pedido();
                        break;
                    case 3:
                        exclui_fornecedor();
                        break;
                    case 4:
                        i++;
                        break;
                    default:
                    printf("Comando inexistente , insira novamente \n");
                    printf("\n");
                    printf("\n");                    
                        break;
                }
            }else{  /*aqui com um fornecedor cadastrado, e um pedido, ele já tem acesso a todas as funções do programa*/
                    clrscr();
                    printf("\n");
                    printf("\n");
                    printf("        ******************MENU******************\n");
                    printf("        *   1 - Registrar fornecedor           *\n");
                    printf("        *   2 - Registra pedido                *\n");
                    printf("        *   3 - Exclui fornecedor              *\n");
                    printf("        *   4 - Consulta pedido                *\n");
                    printf("        *   5 - Emitir relatorio               *\n");
                    printf("        *   6 - Sair                           *\n");
                    printf("        ****************************************\n");

                    scanf(" %d",&escolha);

                        switch (escolha)
                        {
                        case 1:
                            registra_fornecedor();
                            break;
                        case 2:
                            registra_pedido();
                            break;
                        case 3:
                            exclui_fornecedor();
                            break;
                        case 4: 
                            consulta_pedido();
                            break;
                        case 5:
                            emite_relatorio();
                            break;
                        case 6:
                            i++;
                            break;
                        default:
                            printf("\nComando inexistente , insira novamente \n");
                            printf("\n");
                            printf("\n");  
                            break;
                        }
                }
        }

        if(i != 0){
            printf("\n");
            printf("\n");
            printf("*   Obrigado pela preferencia    *\n");
            printf("\n");
            printf("\n");
        }
    }
}

void registra_fornecedor() /*com um nome auto explicativo, essa função registra um fornecedor*/
{
    FILE *fornecedor_restaurante;
    FILE *marm_arq;
    FILE *copia_fornecedor;
    char aux[size];
    char validado[size];
    char primeiro[] = {0,0,0};
    fornecedor forn;
    pedido p;
    copiado e;
    int escolha;
    int i = 0;
    int z = 0;
    /*aqui eu faço uma repetição infinita dando ao usuário a opção de,se quiser cadastrar mais de um fornecedor*/
    while(i == 0)
    {
        int validador = 0;


        printf("\nPor favor digite o nome do fornecedor que voce deseja cadastrar :\n");
            scanf(" %[^\n]s",validado);
            padronizacao(validado);
    /*a primeira validação que eu faço é se existe ou não o arquivo de fornecedor*/
            if((fornecedor_restaurante = fopen("fornecedor_restaurante.bin","rb")) == NULL)
            {
                strcpy(forn.rest,validado);

                validador = 0;
            }
    /*já aqui eu verifico se ele está vazio ou não e se o fornecedor solicitado para ser cadastrado já existe ou não*/
            if((fornecedor_restaurante = fopen("fornecedor_restaurante.bin","rb")) != NULL)
            { 
                fornecedor_restaurante = fopen("fornecedor_restaurante.bin","r+b");
                fseek(fornecedor_restaurante,0,SEEK_SET);
                    while(fread(&forn.rest,sizeof(fornecedor),1,fornecedor_restaurante))
                    {
                        if(strcmp(forn.rest,validado) == 0)
                        {
                            validador++;
                        }
                        if(strcmp(validado,forn.rest) == 0)
                        {
                            validador++;
                        }
                    }
                fclose(fornecedor_restaurante);

            } 
    /*aqui eu verifico se existe algm usuario com o nome do fornecedor */
            if((marm_arq = fopen("marm_arq.bin","rb")) != NULL)
            {
                fseek(marm_arq,0,SEEK_SET);
                while(fread(&p,sizeof(pedido),1,marm_arq))
                {
                    if(strcmp(p.usuario,validado) == 0)
                    {
                        validador++;
                    }
                    if(strcmp(validado,p.usuario) == 0)
                    {
                        validador++;
                    }
                }
                fclose(marm_arq);
            }
    /*aqui caso for valdio, eu salvo o novo fornecedor nos dois arquivos,"fornecedor_restaurante.bin" e no "copia_restaurante.bin"*/
            if(validador == 0){
                strcpy(forn.rest,validado);

                fornecedor_restaurante = fopen("fornecedor_restaurante.bin","a+b");
                    fwrite(&forn.rest,sizeof(fornecedor),1,fornecedor_restaurante);
                fclose(fornecedor_restaurante);    
                printf("\nFornecedor cadastrado !!!\n");
        
                copia_fornecedor = fopen("copia_fornecedor.bin","a+b");
                    while(fread(&e,sizeof(copiado),1,copia_fornecedor)){
                        if(strcmp(e.forncopiado,validado) == 0){
                            z++;
                        }
                    }
                    if(z == 0){
                        strcpy(e.forncopiado,validado);
                        fwrite(&e.forncopiado,sizeof(copiado),1,copia_fornecedor);
                    }
                fclose(copia_fornecedor);
            
            }else{
                printf("\n***Dado invalido, tente novamente***\n");
                fflush(stdin);
                continue;
            }
            
        printf("\nVoce deseja continuar a cadastrar fornecedores ou sair ? \n");
        printf("\n        ***********************************\n");
        printf("        *          1 - Sair               *\n");
        printf("        *          2 - Continuar          *\n");
        printf("        ***********************************\n");
        scanf("%d",&escolha);
        clrscr();
        if(escolha == 1)
        {
            i++;
            clrscr();
        }
        if(escolha == 2)
        {
            continue;
            clrscr();
        }
        if(escolha != 2 && escolha != 1){
            while(escolha != 2 || escolha != 1)
            {
                escolha = 0;
                printf("\nEscolha invalida, tente novamente !!!\n");
                scanf("%d",&escolha);
            }
            if(escolha == 1)
            {
                i++;
                clrscr();
            }
            if(escolha == 2)
            {
                continue;
                clrscr();
            }            
        } 
    }    
}

void registra_pedido() /*aqui eu faço o registro de pedidos*/
{
    FILE *marm_arq;
    FILE *fornecedor_restaurante;
    pedido p;
    fornecedor forn;
    time_t horaatual;
    struct tm *horario;
    char vfornecedor[size] , vusuario[size];
    char buffer[size];
    char hora[size];
    char tamanhofinal[size];
    char vtamanho;
    int vsabor;
    int contador = 0;
    int i = 0, e = 0 , v1 = 0 , v2 = 0 ,y = 0, z = 0;
    int escolha;
    /*nessa função eu também fiz uma repetição infinita, para o cadastro de diversos usuários*/
    /*nessa função em todas as entradas de informações eu fiz repeticoes infinitas, que só se encerram ao entrar uma informação correta*/
    clrscr();
    
    while(i == 0){
        printf("Esses sao os fornecedores disponiveis : \n");
        printf("\n");
        printf("\n");
        fornecedor_restaurante = fopen("fornecedor_restaurante.bin","r+b");
            fseek(fornecedor_restaurante,0,SEEK_SET);
        while(fread(&forn,sizeof(fornecedor),1,fornecedor_restaurante))
        {
            if(strstr(forn.rest,"0") == 0){
                printf("        -------------------------------------------\n");
                printf("                    %s\n",forn.rest);
            }    
        }
        printf("        -------------------------------------------\n");
            fclose(fornecedor_restaurante);
        printf("\n");
        printf("\n");

        e = 0;
        while(e == 0){
            fflush(stdin);
            printf("Digite em qual fornecedor voce gostaria de pedir : \n");
                scanf(" %[^\n]s",vfornecedor);
                padronizacao(vfornecedor);

            fornecedor_restaurante = fopen("fornecedor_restaurante.bin","r+b");
                fseek(fornecedor_restaurante,0,SEEK_SET);
                while(fread(&forn,sizeof(fornecedor),1,fornecedor_restaurante))
                {
                    if(strcmp(vfornecedor,forn.rest) == 0){
                        contador++;
                    }
                    if(strcmp(forn.rest,vfornecedor) == 0){
                        contador++;
                    }
                }
            fclose(fornecedor_restaurante);
            
            if(contador >= 2)
            {
                strcpy(p.restaurante,vfornecedor);
                e++;
            }else if(contador != 2){
                printf("\nFornecedor nao cadastrado, tente novamente!!!\n");      
                continue;              
            }
        }


        e = 0;
        while(e == 0){
            fflush(stdin);
            printf("\nNos disponibilizamos os seguintes sabores \n");
            printf("\n");
            printf("        *************** Sabores ***************\n");
            printf("        *   1 - Arroz e feijao                *\n");
            printf("        *   2 - Strogonoff                    *\n");
            printf("        *   3 - Churrasco                     *\n");
            printf("        *   4 - Macarrao                      *\n");
            printf("        ***************************************\n");
            printf("\n");
            printf("Digite o numero do sabor que voce gostaria :\n");
            scanf("%d",&vsabor);
            if(vsabor == 1){
                strcpy(p.sabor,"Arroz e feijao");
                e++;
            }
            if(vsabor == 2){
                strcpy(p.sabor,"Strogonoff");
                e++;
            }
            if(vsabor == 3){
                strcpy(p.sabor,"Churrasco");
                e++;
            }
            if(vsabor == 4){
                strcpy(p.sabor,"Macarrao");
                e++;
            }
            if(vsabor != 1 && vsabor != 2 && vsabor != 3 && vsabor != 4)
            {
                printf("\nSabor inexistente, digite novamente !!!\n");
                continue;
            }
        }
        

        e = 0;
        printf("\nA marmita de %s tem tres tamanhos disponiveis P , M , G , insira o que voce gostaria\n", p.sabor);
        printf("[P,M,G] : \n");
        fflush(stdin);
        while(e == 0)
        {
            fflush(stdin);
            scanf(" %c",&vtamanho);
            vtamanho = toupper(vtamanho);

            if (vtamanho != 'P' && vtamanho != 'M' && vtamanho != 'G')
            {
                printf("\n Tamanho invalido , digite novamente : \n");
                continue;
            }else{
                tamanhofinal[0] = vtamanho;
                tamanhofinal[1] = '\0';
                strcpy(p.tamanho,tamanhofinal);
                e++;
            }
        }
        

        e = 0; 
        while(e == 0){
            v2 = 0;
            fflush(stdin);
            printf("Insira o seu nome por favor : \n");
                scanf(" %[^\n]s",vusuario);
                padronizacao(vusuario);
            
            fornecedor_restaurante = fopen("fornecedor_restaurante.bin","rb");
            fseek(fornecedor_restaurante,0,SEEK_SET);
            while(fread(&forn,sizeof(fornecedor),1,fornecedor_restaurante))
            {   
                if(strcmp(forn.rest,vusuario) == 0)
                {
                    v2++;
                }
            }
            fclose(fornecedor_restaurante);
            
            if(v2 == 0)
            {
                strcpy(p.usuario,vusuario);
                e++;
            }else{
                printf("\nEsse nome pertence a um fornecedor\n");
                continue;
            }
        }
        
        
        time(&horaatual);
        horario = localtime(&horaatual);
        strftime(buffer,7,"%H:%M",horario);
        strftime(hora,4,"%H",horario);
        printf("\n--------[horario do pedido :%s]--------\n",buffer);
        strcpy(p.cronos,buffer);
        strcpy(p.horapesquisa,hora);

        

        marm_arq = fopen("marm_arq.bin","a+b");
        if(!marm_arq){
            printf("Erro no cadastro!\n");
            exit(1);
        }
        fwrite(&p,sizeof(pedido),1,marm_arq);
        printf("\n");
        printf("        **********************************\n");
        printf("        *Pedido registrado com sucesso   *\n");
        printf("        **********************************\n");
        fclose(marm_arq);

        printf("\nVoce deseja fazer um novo pedido ou sair ? \n");
        printf("\n        ***********************************\n");
        printf("        *          1 - Sair               *\n");
        printf("        *          2 - Continuar          *\n");
        printf("        ***********************************\n");
        scanf("%d",&escolha);
        clrscr();
        if(escolha == 1)
        {
            i++;
        }
        if(escolha == 2)
        {
            continue;
        }
        if(escolha != 2 && escolha != 1){
            while(escolha != 2 || escolha != 1)
            {
                escolha = 0;
                printf("\nEscolha invalida, tente novamente !!!\n");
                scanf("%d",&escolha);
            }
            if(escolha == 1)
            {
                i++;
            }
            if(escolha == 2)
            {
                continue;
            }            
        } 
    }    
}

void exclui_fornecedor() /*aqui eu removo os fornecedores*/
{
    FILE *fornecedor_restaurante;
    fornecedor forn;
    pedido p;
    char pesquisa[size];
    int contador = 0;
    int aux = 0;
    int i = 0;
    int z = 0;
    int escolha;
    char zero = '0';

    while(i == 0){
    /*aqui eu exibo os fornecedores disponíves para exclusão*/
        printf("Os fornecedores disponiveis para exclusao sao :\n");
        printf("\n");
        printf("\n");
        
        fornecedor_restaurante = fopen("fornecedor_restaurante.bin","r+b");
        fseek(fornecedor_restaurante,0,SEEK_SET);
        while(fread(&forn,sizeof(fornecedor),1,fornecedor_restaurante))
        {        
            if(strstr(forn.rest,"0") != 0)
            {
            }
            if(strstr(forn.rest,"0") == 0){
                printf("        -------------------------------------------\n");
                printf("                %s \n",forn.rest);
            }
        }
        printf("        -------------------------------------------\n");
        fclose(fornecedor_restaurante);
    /*já aqui eu solicito a entrada do nome do fornecedor, e verifico se ele é válido ou não*/        
        z = 0;
        while(z == 0){
            printf("\nDigite o nome do fornecedor que voce deseja excluir \n");
            scanf(" %[^\n]s",pesquisa);
            padronizacao(pesquisa);

            fornecedor_restaurante = fopen("fornecedor_restaurante.bin","r+b");
                fseek(fornecedor_restaurante,0,SEEK_SET);
            
                contador = 0;
            
            while(fread(&forn,sizeof(fornecedor),1,fornecedor_restaurante))
            {
                if(strcmp(forn.rest,pesquisa) == 0)
                {
                    fseek(fornecedor_restaurante,-1*sizeof(fornecedor),SEEK_CUR);
                        fwrite(&zero,sizeof(zero),1,fornecedor_restaurante);
                    contador++;
                    printf("Fornecedor encontrado e excluido\n");
                    z++;
                }
            }
            if(contador == 0){
                printf("\nNao foi encontrado o fornecedor, tente novamente\n");
                continue;
            }
            fclose(fornecedor_restaurante);
        }
    /*aqui eu exibo os fornecedores atuais , após a exclusão*/
        printf("\nEsses sao os fornecedores disponiveis atualmente :\n");
        printf("\n");
        
        fornecedor_restaurante = fopen("fornecedor_restaurante.bin","r+b");
        fseek(fornecedor_restaurante,0,SEEK_SET);

            while(fread(&forn,sizeof(fornecedor),1,fornecedor_restaurante))
            {
            
                if(strstr(forn.rest,"0") != 0)
                {

                }
                if(strstr(forn.rest,"0") == 0){
                    printf("        -------------------------------------------\n");
                    printf("                     %s\n",forn.rest);
                }    
            }
            printf("        -------------------------------------------\n");
        fclose(fornecedor_restaurante);

        printf("\nVoce deseja continuar a excluir fornecedores ou sair ? \n");
        printf("\n        ***********************************\n");
        printf("        *          1 - Sair               *\n");
        printf("        *          2 - Continuar          *\n");
        printf("        ***********************************\n");
        scanf("%d",&escolha);
        clrscr();
        if(escolha == 1)
        {
            i++;
        }
        if(escolha == 2)
        {
            continue;
        }
        if(escolha != 2 && escolha != 1){
            while(escolha != 2 || escolha != 1)
            {
                escolha = 0;
                printf("\nEscolha invalida, tente novamente !!!\n");
                scanf("%d",&escolha);
            }
            if(escolha == 1)
            {
                i++;
            }
            if(escolha == 2)
            {
                continue;
            }            
        } 
    
    }
}

void consulta_pedido() /*aqui eu disponibilizo a cunsulta de um pedido por hora ou nome*/
{
    FILE *marm_arq;
    pedido p;
    int e = 0;
    int alternativa;
    int a = 0 , b = 0;

    while(e == 0)
    {
        a = 0;
        b = 0;
        char consulta[size];
        char procurado[size];
        char opcao;

        int i = 0;
        
        printf("\nVoce deseja pesquisar um pedido por nome ou horario ?\n");
        scanf(" %[^\n]s",consulta);
        printf("\n");
    /*aqui eu dou a opção de o usuario iniciar a pesquisa pelo nome e ou hora*/
        opcao = tolower(consulta[0]);
    /*sendo que a pesquisa da hora é feita apenas pelos 2 diigtos da hora, mas é exibida a hora exata*/
        if(opcao == 'n')/*a pesquisa do nome mostra não apenas pelo nome, mas também fracções do nome*/
        {
            printf("Insira o nome do usuario que voce deseja pesquisar : \n");
                scanf(" %[^\n]s",procurado);
                padronizacao(procurado);
            printf("\n");

            marm_arq = fopen("marm_arq.bin","r+b");
            fseek(marm_arq,0,SEEK_SET);
                a++;
                while(fread(&p,sizeof(pedido),1,marm_arq) != 0)
                {
                    if(strstr(p.usuario,procurado) != NULL)
                    {
                        printf("        ----------------------------------------------------\n");
                        printf("             Usuario : %s\n",p.usuario);
                        printf("             Restaurante do pedido : %s\n",p.restaurante);
                        printf("             Sabor da marmita : %s\n",p.sabor);
                        printf("             Marmita de tamanho : %s\n",p.tamanho);
                        printf("             Hora do pedido : %s\n",p.cronos);
                        printf("        ----------------------------------------------------\n");
                        a++;
                    }
                }
            fclose(marm_arq);
        }
        if (opcao == 'h')
        {
            printf("Insira a hora do seu pedido : \n");
                scanf(" %[^\n]s",procurado);
                padronizacao(procurado);
            printf("\n");
            marm_arq = fopen("marm_arq.bin","r+b");
            fseek(marm_arq,0,SEEK_SET);
                b++;
                while(fread(&p,sizeof(pedido),1,marm_arq) != 0)
                {
                        if(strstr(p.horapesquisa,procurado) != NULL)
                        {
                            printf("        ----------------------------------------------------\n");
                            printf("             Usuario : %s\n",p.usuario);
                            printf("             Restaurante do pedido : %s\n",p.restaurante);
                            printf("             Sabor da marmita : %s\n",p.sabor);
                            printf("             Marmita de tamanho : %s\n",p.tamanho);
                            printf("             Hora do pedido : %s\n",p.cronos);
                            printf("        ----------------------------------------------------\n");
                            b++;
                        }
                }
            fclose(marm_arq);
        }

        if(a == 1 && b == 0)
        {
            printf("\nNome nao encontrado ,tente novamente\n");
            continue;
        }

        if(a == 0 && b == 1)
        {
            printf("\nHora nao encontrada , tente novamente\n");
            printf("tente digitar apenas as horas\n");
            continue;
        }
        
        if(opcao != 'h' && opcao != 'n')
        {
            clrscr();
            printf("Esse modo de consulta esta indisponivel, tente novamente \n");
            continue;
        }
        printf("Voce deseja continuar a sua pesquisa ou sair ? \n");
        printf("        ***********************************\n");
        printf("        *          1 - Sair               *\n");
        printf("        *          2 - Continuar          *\n");
        printf("        ***********************************\n");
        scanf("%d",& alternativa);
        clrscr();
        if(alternativa == 1)
        {
            e++;
        }
    }    
}

void emite_relatorio() 
{
    FILE *marm_arq;
    FILE *fornecedor_restaurante;
    FILE *copia_fornecedor;
    pedido p;
    fornecedor forn;
    copiado cpy;
    int i;
    int contador = 0;
    int soma = 0;
    float total = 0, pe = 0, m = 0 , g = 0;
    float arroz = 0 , strog = 0, churr = 0 , macar = 0;
    float r1 , r2 , r3 , r4;
    char pct = '%';
    /*primeiramente eu exibo o relatorio das porcentagens de pedidos em cada fornecedor*/
    clrscr();
    printf("\n******************[Relatorio de pedidos]*********************\n");

    copia_fornecedor = fopen("copia_fornecedor.bin","r+b");
        fseek(copia_fornecedor,0,SEEK_SET);
                
        while(fread(&cpy,sizeof(copiado),1,copia_fornecedor))
        {
            contador++;
        }

    fclose(copia_fornecedor);
    
    struct copia e[contador];/*eu uso essa struct para copiar todos os fornecedores, e eela me auxiliara depois enquanto eu contabilizo as vendas*/

    copia_fornecedor = fopen("copia_fornecedor.bin","r+b");
        fseek(copia_fornecedor,0,SEEK_SET);
        
        while(fread(&cpy,sizeof(copiado),1,copia_fornecedor))
        {
            strcpy(e[soma].copiaforn,cpy.forncopiado);
            soma++;     
        }     
    fclose(copia_fornecedor);

        for(i = 0;i < soma;i++)
        {
             e[i].vendido = 0.0;
        }

    marm_arq = fopen("marm_arq.bin","r+b");
        fseek(marm_arq,0,SEEK_SET);
        
        while(fread(&p,sizeof(pedido),1,marm_arq))
        {
            total++;

            for(i = 0;i < soma;i++)
            {
                if(strstr(p.restaurante,e[i].copiaforn) != NULL)
                {
                    e[i].vendido++;
                }
            }
        }
    fclose(marm_arq);
    printf("\n");
    printf("\n        **************************************************\n");
    for(i = 0;i < soma;i++)
    {   
        printf("        *       %s =  teve %.2f%c das vendas    *\n",e[i].copiaforn,(100*(e[i].vendido/total)),pct);
    }
    printf("        **************************************************\n");

    total = 0;
    /*logo apos eu exibo a porcentagem de pedidos de cada tamanho de marmita P , M , G*/
    marm_arq = fopen("marm_arq.bin","r+b");
        fseek(marm_arq,0,SEEK_SET);
    
        while(fread(&p,sizeof(pedido),1,marm_arq))
        {
            if(strstr("P",p.tamanho) != NULL)
            {
                pe++;
                total++;
            }
            if(strstr("M",p.tamanho) != NULL)
            {
                m++;
                total++;
            }
            if(strstr("G",p.tamanho) != NULL)
            {
                g++;
                total++;
            }
        }
        r1 = (pe/total);
        r2 = (m/total);
        r3 = (g/total);
    fclose(marm_arq);
        printf("\n[-----------percentual tamanho de marmita-----------]\n");
        printf("\n        ***********************************\n");
        printf("        *       Pequenas = %.2f%c         *\n",100*r1,pct);
        printf("        *       Medias = %.2f%c           *\n",100*r2,pct);
        printf("        *       Grandes = %.2f%c          *\n",100*r3,pct);
        printf("        ***********************************\n");

    total = 0;
    r1 = 0;
    r2 = 0;
    r3 = 0;
    r4 = 0;
    /*por fim eu exibo os percentuais de pedidos de cada sabor de marmita */
    marm_arq = fopen("marm_arq.bin","r+b");
        fseek(marm_arq,0,SEEK_SET);
        
        while(fread(&p,sizeof(pedido),1,marm_arq))
        {
            if(strstr("Arroz e feijao",p.sabor))
            {
                arroz++;
                total++;
            }
            if(strstr("Strogonoff",p.sabor))
            {
                strog++;
                total++;
            }
            if(strstr("Churrasco",p.sabor))
            {
                churr++;
                total++;
            }
            if(strstr("Macarrao",p.sabor))
            {
                macar++;
                total++;
            }
        }
    fclose(marm_arq);
    
        r1 = (arroz/total);
        r2 = (strog/total);
        r3 = (churr/total);
        r4 = (macar/total);
        printf("\n[-----------percentual sabor de marmita-----------]\n");
        printf("\n        ***********************************\n");
        printf("        *       Arroz e feijao = %.2f%c   *\n",(100)*(r1),pct);
        printf("        *       Strogonoff = %.2f%c       *\n",(100)*(r2),pct);
        printf("        *       Churrasco = %.2f%c        *\n",(100)*(r3),pct);
        printf("        *       Macarrao = %.2f%c         *\n",(100)*(r4),pct);
        printf("        ***********************************\n");

        printf("\ndigite qualquer tecla para sair !!!\n");
        getchar();
        getchar();

}

void clrscr()/*essa função eu utilizo para limpar a tela e ela é funcional tanto no linux quanto no windows */
{
    system("@cls||clear");
}

void padronizacao(char nome[])/*essa função eu criei para padronizar todas s strings que eu pretendo salvar*/
{   /*eu transformo a primeira letra em maíuscula etodas as outras em minusculas*/
    int e;
    for(e = 0; e < strlen(nome);e++)
    {
        if(e == 0){
            nome[0] = toupper(nome[0]);
        }else{
            nome[e] = tolower(nome[e]);
        }

    }
}
