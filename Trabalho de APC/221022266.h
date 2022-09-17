#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_CNPJ 15
#define TAM_CPF 12
#define TAM_NOME 100
#define LEITURA 100



//Struct que armazena dados da Usina
typedef struct
{

    char cnpj[TAM_CNPJ], nomeUsina[TAM_NOME];
    int data[3];
    float potencia;
} USINA; //Nome da struct


//Struct que armazena dados do Consumidor
typedef struct
{
    char cpfConsumidor[TAM_CPF], cnpjConsumidor[TAM_CNPJ], nomeConsumidor[TAM_NOME];
} CONSUMIDOR; //Nome da struct



//STRUCT QUE ARMAZENA DADOS DO CONTRATO
typedef struct
{
    char cnpjConsumidor[TAM_CNPJ], cpfConsumidor[TAM_CPF], cnpjUsina[TAM_CNPJ];
    int dataCt[3], potenciaCt;
} CONTRATO; //Nome da struct


//função para limpar tela (somente windows)
void limparTela()
{
#if defined(linux) || defined (unix) || defined(APPLE)
    system("clear");

#endif // defined
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif // defined
}


//SALVANDO DADOS NO ARQUIVO DA USINA
void arquivoUsina(char nomeUsina[], char cnpj[], int data[], int potencia)
{
    FILE* arquivoUsina;
    arquivoUsina = fopen("Usina.txt","a+t");

    if(arquivoUsina == NULL)
    {
        limparTela();
        printf("\nErro ao abrir o arquivo, tente novamente!");
    }
    else
    {
        //SALVANDO DADOS NO ARQUIVO SE FOR ABERTO CORRETAMENTE
        fprintf(arquivoUsina,"%s", nomeUsina);
        fprintf(arquivoUsina,"%s\n", cnpj);
        fprintf(arquivoUsina,"%.02d%.02d%.04d\n", data[0], data[1], data[2]);
        fprintf(arquivoUsina,"%d\n", potencia);
    }

    fclose(arquivoUsina);

}


//SALVANDO DADOS NO ARQUIVO DO CONSUMIDOR
void arquivoConsumidor(char nome[], char identidade[], int opcao)
{
    FILE* arquivoConsumidor;
    arquivoConsumidor = fopen("Consumidor.txt","a+t");

    if(arquivoConsumidor == NULL)
    {
        limparTela();
        printf("\nErro ao abrir o arquivo, tente novamente!");
    }
    else
    {
        //SALVANDO DADOS NO ARQUIVO DO CONSUMIDOR SE ELE ABRIR CORRETAMENTE
        fprintf(arquivoConsumidor,"%s", nome);
        if(opcao == 1)
        {
            fprintf(arquivoConsumidor,"%s\n", identidade);

        }
        else if(opcao == 2)
        {
            fprintf(arquivoConsumidor,"%s\n", identidade);
        }
    }
    fclose(arquivoConsumidor);
}



//SALVANDO DADOS NO ARQUIVO DO CONTRATO
void arquivoContrato(char cnpjUsina[], char identidade[], int data[], int potencia, int opcao)
{
    FILE* arquivoContrato;
    arquivoContrato = fopen("Contrato.txt","a+t");

    if(arquivoContrato == NULL)
    {
        limparTela();
        printf("\nErro ao abrir o arquivo, tente novamente!");
    }
    else
    {
        //SALVANDO DADOS NO ARQUIVO DO CONTRATO SE ELE ABRIR CORRETAMENTE
        fprintf(arquivoContrato,"%s\n", cnpjUsina);
        if(opcao == 1)
        {
            fprintf(arquivoContrato,"%s\n", identidade);
        }
        else if(opcao == 2)
        {
            fprintf(arquivoContrato,"%s\n", identidade);
        }
        fprintf(arquivoContrato,"%.02d%.02d%d\n", data[0], data[1], data[2]);
        fprintf(arquivoContrato, "%d\n", potencia);
    }
    fclose(arquivoContrato);
}


//CONSULTAR OS DADOS NO CONTRATO
void pesquisarContrato(char identidade[], int op)
{
    char cnpjUsina[LEITURA], identidadeConsumidor[LEITURA], potencia[LEITURA];
    int cont, data[LEITURA];
    cont = 1;

    FILE* arquivoContrato;
    arquivoContrato = fopen("Contrato.txt","a+t");

    if(arquivoContrato == NULL)
    {
        limparTela();
        printf("Nenhum contrato!\n\n");
    }
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivoContrato) == 0)
        {
            //LENDO DADOS DO ARQUIVO NO CONTRATO
            fscanf(arquivoContrato,"%[^\n]\n", cnpjUsina);
            fscanf(arquivoContrato,"%s\n", identidadeConsumidor);
            fscanf(arquivoContrato,"%02d%02d%d\n", &data[0], &data[1], &data[2]);
            fscanf(arquivoContrato,"%s\n", potencia);

            //IMPRIMINDO PELA CONSULTA DA USINA OS DADOS PRESENTES NO CONTRATO SE ENCONTRATO
            if(op == 1)
            {
                if(strcmp(identidade, cnpjUsina)==0)
                {
                    printf("------------------------------\n");
                    printf("|         Contrato           |\n");
                    printf("------------------------------\n");
                    printf("CNPJ Usina: %s\n", cnpjUsina);
                    if(strlen(identidadeConsumidor) == 14)
                        printf("CNPJ Consumidor: %s\n", identidadeConsumidor);
                    else
                    {
                        printf("CPF Consumidor: %s\n", identidadeConsumidor);
                    }
                    printf("Data: %02d/%02d/%d\n", data[0], data[1], data[2]);
                    printf("Potencia Contratada: %s\n\n", potencia);

                    cont = 2;

                }
            }
            else
            {
                //IMPRIMINDO OS DADOS DO CONTRATO PELA CONSULTA DO CONSUMIDOR
                if(strcmp(identidade, identidadeConsumidor)==0)
                {

                    printf("------------------------------\n");
                    printf("|           Contrato         |\n");
                    printf("------------------------------\n");
                    printf("CNPJ Usina: %s\n", cnpjUsina);
                    if(strlen(identidadeConsumidor) == 14)
                        printf("CNPJ Consumidor: %s\n", identidadeConsumidor);
                    else
                    {
                        printf("CPF Consumidor: %s\n", identidadeConsumidor);
                    }
                    printf("Data: %02d/%02d/%d\n", data[0], data[1], data[2]);
                    printf("Potencia Contratada: %s\n\n", potencia);

                    cont = 2;

                }

            }
        }
        if(cont == 1)
        {
            printf("Nenhum contrato encontrado!\n\n");
        }
    }

    fclose(arquivoContrato);
}


//FUNÇÃO PARA CONSULTAR O ARQUVIO DA USINA
void consultarArquivoUsina(char cnpjUsina[])
{
    char nome[100], cnpj[100], potencia[100];
    int cont, data[100];

    cont=1;
    FILE * arquivo;
    arquivo = fopen("Usina.txt","r");

    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo, tente novamente!\n");
    }
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo) == 0)
        {
            //LENDO DADOS DO ARQUIVO

            fscanf(arquivo,"%[^\n]\n", nome);
            fscanf(arquivo,"%s\n", cnpj);
            fscanf(arquivo,"%02d%02d%d\n", &data[0], &data[1], &data[2]);
            fscanf(arquivo,"%s\n", potencia);

            //IMPRIMINDO DADOS SE ENCONTRAR A USINA
            if(strcmp(cnpj, cnpjUsina)==0)
            {
                limparTela();

                printf("------------------------------\n");
                printf("|         Dados usina        |\n");
                printf("------------------------------\n");
                printf("Nome: %s\n", nome);
                printf("CNPJ: %s\n", cnpj);
                printf("Data: %02d/%02d/%d\n", data[0], data[1], data[2]);
                printf("Potencia Inicial: %s\n\n", potencia);

                cont = 2;

                printf("================================================================================\n\n");

                //FUNÇÃO PRA PESQUISAR A USINA NO CONTRATO
                pesquisarContrato(cnpjUsina, 1);

            }
        }
        if(cont == 1)
        {
            limparTela();
            printf("Usina nao encontrada!\n");
        }
    }

    fclose(arquivo);
}


//FUNÇÃO PARA CONSULTAR O ARQUVIO DO CONSUMIDOR
void consultarArquivoConsumidor(char idConsumidor[])
{

    char nome [TAM_NOME], identidade[TAM_CNPJ];
    int cont;
    cont=0;

    FILE * arquivo;

    arquivo = fopen("Consumidor.txt","r");

    printf("\n");

    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo, tente novamente!\n");
    }

    //LENDO O ARQUIVO CONSUMIDOR
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo)== 0)
        {
            //IMPRIMINDO OS DADOS DO CONSUMIDOR

            fscanf(arquivo,"%[^\n]\n", nome);
            fscanf(arquivo,"%[^\n]\n", identidade);

            if(strcmp(identidade, idConsumidor) == 0)
            {
                limparTela();

                printf("------------------------------\n");
                printf("|     Dados Consumidor       |\n");
                printf("------------------------------\n");

                printf("Nome: %s\n", nome);

                if(strlen(identidade) == 11)
                {
                    printf("CPF: %s\n\n", identidade);
                }
                else
                {
                    printf("CNPJ: %s\n\n", identidade);
                }

                cont = 2;
            }
        }
        if(cont != 2)
        {
            limparTela();
            printf("\nConsumidor nao encontrado!\n\n");
        }

    }
    if(cont == 2)
    {
        printf("================================================================================\n\n");

        //IMPRIMINDO DADOS NO CONTRATO PELA CONSULTA DO CONSUMIDOR
        pesquisarContrato(idConsumidor, 2);
    }

    fclose(arquivo);
}


//Função para Validar Data
int validarData(int data[])
{

    int validador, validadorBissexto;
    validadorBissexto = 0;
    validador = 0;

    //VERIFICAÇÃO SE É BISSEXTO OU NÃO
    if(data[2] % 4 == 0 && data [2] % 100!= 0 || data[2] % 400 == 0)
    {
        validadorBissexto = 1;
    }
    else
    {
        validadorBissexto = 0;
    }

    //VERIFICAÇÃO DE DIAS, MESES E ANO MAIOR QUE 0
    if(data[0] < 1 || data[0] > 31 || data[1] < 1 || data[1] > 12 || data[2] < 1 )
    {
        validador = 1;
    }
    else
    {
        //VERIFICAÇÃO DE DIAS (INCLUINDO FEVEREIRO E NO ANO BISSEXTO
        if(( data[1] == 4 || data[1] == 6 || data[1] == 9 || data[1] == 11) && (data[0] <= 30))
        {
            validador = 0;
        }
        else if((data[1] == 1 || data[1] == 3 || data[1] == 5 || data[1] == 7 || data[1] == 8 || data[1] == 10 || data[1] == 12) && (data[0] <= 31))
        {
            validador = 0;
        }
        else if( validadorBissexto == 0 && data[0] <= 28)
        {
            validador = 0;

        }
        else if( validadorBissexto == 1 && data[0] <= 29)
        {
            validador = 0;

        }
        else
        {
            validador =1;
        }
    }

//RETORNA 1 PARA INVÁLIDO 2 PARA VÁLIDO
    if(validador == 1)
    {
        return 1;
    }

    else if(validador == 0)
    {
        return 2;
    }
    return 0;
}



//FUNÇÃO PARA VALIDAR O CPF
int validarCPF(char cpf[])
{
    int cont, j, digito1 = 0, digito2 = 0;
    if (strlen(cpf) != 11)
        return 0;
    else if ((strcmp(cpf, "00000000000") == 0) ||
             (strcmp(cpf, "11111111111") == 0) ||
             (strcmp(cpf, "22222222222") == 0) ||
             (strcmp(cpf, "33333333333") == 0) ||
             (strcmp(cpf, "44444444444") == 0) ||
             (strcmp(cpf, "55555555555") == 0) ||
             (strcmp(cpf, "66666666666") == 0) ||
             (strcmp(cpf, "77777777777") == 0) ||
             (strcmp(cpf, "88888888888") == 0) ||
             (strcmp(cpf, "99999999999") == 0))
        return 0; // VERIFICANDO A IGUALDADE DOS DIGITOS DO CPF, SE FOREM IGUAIS E INVALIDO.
    else
    {
// SOMANDO OS DÍGITOS PARA VERIFICACAO DO DÍGITO 1
        for (cont = 0, j = 10; cont < strlen(cpf) - 2;
                cont++, j--)
            digito1 += (cpf[cont] - 48) * j;
        digito1 %= 11;
//OBTENDDO O PRIMEIRO DIGITO VERIFICADOR
        if (digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if ((cpf[9] - 48) != digito1)
            return 0; // VERIFICANDO SE O DÍGITO OBTIDO E O DIGITADO SÃO IGUAIS SE NAO FOR RETORNA INVÁLIDO
        else
// SOMANDO OS DIGITOS DO 2 DÍGITO VERIFICADOR
        {
            for (cont = 0, j = 11; cont < strlen(cpf) - 1;
                    cont++, j--)
                digito2 += (cpf[cont] - 48) * j;
//OBTENDDO O PRIMEIRO DIGITO VERIFICADOR
            digito2 %= 11;
            if (digito2 < 2)
                digito2 = 0;
            else
                digito2 = 11 - digito2;
            if ((cpf[10] - 48) != digito2)
                return 0; // VERIFICANDO SE O DÍGITO OBTIDO E O DIGITADO SÃO IGUAIS SE NAO FOR RETORNA INVÁLIDO
        }
    }
//SE FOR IGUAL RETORNA 2
    return 2;
}



//FUNÇÃO PARA VALIDAR CNPJ
int validarCNPJ(char cnpj[])
{
    int cont1[12];
    int cont2[13];
    int resultado[12];
    int inteiro[14];
    int cont, soma, resto, digito_verificador_01, digito_verificador_02;

    //VERIFICANDO O TAMANHO DO CNPJ
    if(strlen(cnpj) != 14)
        return 0;
    for(cont = 0; cont < TAM_CNPJ; cont++)
    {
        switch (cnpj[cont])
        {
        case 48:
            inteiro[cont] = 0;
            break;
        case 49:
            inteiro[cont] = 1;
            break;
        case 50:
            inteiro[cont] = 2;
            break;
        case 51:
            inteiro[cont] = 3;
            break;
        case 52:
            inteiro[cont] = 4;
            break;
        case 53:
            inteiro[cont] = 5;
            break;
        case 54:
            inteiro[cont] = 6;
            break;
        case 55:
            inteiro[cont] = 7;
            break;
        case 56:
            inteiro[cont] = 8;
            break;
        case 57:
            inteiro[cont] = 9;
            break;
        }
    }

    //ATRIBUINDO OS VALORES PARA  SEQUENCIA DE VERIFICAÇÃO DO CNPJ: COMEÇANDO DE 5 ATÉ 2
    //DEPOIS DE 9 ATÉ 2 PARA O PRIMEIRO DÍGITO VERIFICADOR
    cont1[0] = 5;
    cont1[1] = 4;
    cont1[2] = 3;
    cont1[3] = 2;
    cont1[4] = 9;
    cont1[5] = 8;
    cont1[6] = 7;
    cont1[7] = 6;
    cont1[8] = 5;
    cont1[9] = 4;
    cont1[10] = 3;
    cont1[11] = 2;

    //ATRIBUINDO OS VALORES PARA  SEQUENCIA DE VERIFICAÇÃO DO CNPJ: COMEÇANDO DE 6 ATÉ 2
    //DEPOIS DE 9 ATÉ 2
    cont2[0] = 6;
    cont2[1] = 5;
    cont2[2] = 4;
    cont2[3] = 3;
    cont2[4] = 2;
    cont2[5] = 9;
    cont2[6] = 8;
    cont2[7] = 7;
    cont2[8] = 6;
    cont2[9] = 5;
    cont2[10] = 4;
    cont2[11] = 3;
    cont2[12] = 2;


// SOMA PARA O PRIMEIRO DIGITO

    for (cont = 0; cont < 12; cont++)
        resultado[cont] = cont1[cont] * inteiro[cont];

    soma = 0;

    for (cont = 0; cont < 12; cont++)
        soma += resultado[cont];

    resto = soma % 11;

// PRIMEIRO DÍGITO VERIFICADOR
    if (resto < 2)
        digito_verificador_01 = 0;
    else
        digito_verificador_01 = 11 - resto;

    if (inteiro[12] != digito_verificador_01)
        return 0;



// SE O DIGITO VERIFICADOR FOR DIFERENTE DO DÍGITO PELA VERIFICAÇÃO, RETORNA INVÁLIDO
    for (cont = 0; cont < 13; cont++)
        resultado[cont] = cont2[cont] * inteiro[cont];

    soma = 0;

    for (cont = 0; cont < 13; cont++)
        soma += resultado[cont];

    resto = soma % 11;

// SEGUNDO DÍGITO VERIFICADOR
    if (resto < 2)
        digito_verificador_02 = 0;
    else
        digito_verificador_02 = 11 - resto;

    if (inteiro[13] != digito_verificador_02)
        return 0;

// RETORNA 2 SE FOR VALIDO
    return 2;
}


//FUNÇÃO PARA PESQUISAR SE A USINA EXISTE
int pesquisaUsina(char idValidar[])
{
    char validador[100];
    int retorno;
    retorno = 2;

    FILE * arquivo1;
    arquivo1 = fopen("Usina.txt","r");

    if(arquivo1 == NULL)
    {
        retorno = 3;
    }
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo1) == 0)
        {
            //LENDO TODOS OS DADOS, SE A USINA ESTIVER CADASTRADA RETORNA 1
            fscanf(arquivo1,"%s", validador);
            if(strcmp(validador, idValidar)==0)
            {
                retorno = 1;
            }

        }

    }
    fclose(arquivo1);
    return retorno;
}


//FUNÇÃO PARA PESQUISAR SE A USINA TEM ALGUM CONTRATO
int pesquisaUsinaContrato(char idValidar[])
{

    char validador[LEITURA];
    int retorno;
    retorno = 2;

    FILE * arquivo1;
    arquivo1 = fopen("Contrato.txt","r");

    if(arquivo1 == NULL)
    {
        retorno = 3;
    }
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo1) == 0)
        {
            //SE A USINA ESTIVER NO CONTRATO RETORNA 1
            fscanf(arquivo1,"%s", validador);
            if(strcmp(validador, idValidar)==0)
            {
                retorno = 1;
            }
        }
    }
    fclose(arquivo1);
    return retorno;
}

//FUNÇÃO PARA CONSULTAR SE O CONSULTOR EXISTE
int pesquisaConsumidor(char idValidar[])
{
    char validador[100];
    int retorno;
    retorno = 2;

    FILE * arquivo1;
    arquivo1 = fopen("Consumidor.txt","r");

    if(arquivo1 == NULL)
    {
        retorno = 3;
    }
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo1) == 0)
        {
            //SE O CONSUMIDOR ESTIVER CADASTRADO RETORNA 1
            fscanf(arquivo1,"%s", validador);
            if(strcmp(validador, idValidar)==0)
            {
                retorno = 1;
            }
        }
    }
    fclose(arquivo1);
    return retorno;
}


//FUNÇÃO PARA VERIFICAR NOS DOIS ARQUIVOS SE AQUELA IDENTIFICAÇÃO EXISTE (USINA OU CONSUMIDOR)
int pesquisaValidar(char idValidar[])
{
    int retorno;
    retorno = 2;

    if(pesquisaUsina(idValidar) == 1 || pesquisaConsumidor(idValidar) == 1)
    {
        retorno =1;
    }
    else
    {
        retorno = 2;
    }
    return retorno;
}


//FUNCAO PARA EXCLUIR USINA OU CONSUMIDOR DO CONTRATO
void excluirContrato(char identidade[], int op)
{
    char cnpjUsina[LEITURA], identidadeConsumidor[LEITURA], data[LEITURA], potencia[LEITURA];
    int cont;
    cont = 1;

    FILE* arquivo;
    arquivo= fopen("Contrato.txt","r");

    FILE* arquivoContrato;
    arquivoContrato = fopen("ContratoTemp.txt","a+t");

    if(arquivo == NULL)
    {
        limparTela();
        printf("Erro na abertura do Arquivo!\n");
    }
    else
    {
        //LENDO O ARQUIVO DO CONTRATO
        while(feof(arquivo) == 0)
        {
            //LENDO DADOS DO ARQUIVO
            fscanf(arquivo,"%s\n", cnpjUsina);
            fscanf(arquivo,"%s\n", identidadeConsumidor);
            fscanf(arquivo,"%s\n", data);
            fscanf(arquivo,"%s\n", potencia);

            //IMPRIMINDO DADOS NO NOVO ARQUIVO
            if(op == 1)
            {
                if(strcmp(identidade, cnpjUsina)!=0)
                {
                    fprintf(arquivoContrato,"%s\n", cnpjUsina);
                    fprintf(arquivoContrato,"%s\n", identidadeConsumidor);
                    fprintf(arquivoContrato,"%s\n", data);
                    fprintf(arquivoContrato,"%s\n", potencia);
                }
            }
            if(op == 2)
            {
                if(strcmp(identidade, identidadeConsumidor)!=0)
                {
                    fprintf(arquivoContrato,"%s\n", cnpjUsina);
                    fprintf(arquivoContrato,"%s\n", identidadeConsumidor);
                    fprintf(arquivoContrato,"%s\n", data);
                    fprintf(arquivoContrato,"%s\n", potencia);
                }
            }
        }
    }
    fclose(arquivo);
    fclose(arquivoContrato);

    //EXCLUINDO O CONTRATO ANTIGO E RENOMEANDO O NOVO
    remove("Contrato.txt");
    rename("ContratoTemp.txt", "Contrato.txt");

}


//FUNÇÃO PARA EXCLUIR A USINA
void exclusaoUsina(char cnpjUsina[])
{
    char nome[100], cnpj[100], data[100], potencia[100];
    int cont;

    cont=1;
    FILE * arquivo;
    arquivo = fopen("Usina.txt","r");

    FILE * arquivoTemp;
    arquivoTemp = fopen("Usina_temp.txt","a+t");

    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo, tente novamente!\n");
    }
    else
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo) == 0)
        {
            //LENDO DADOS DO ARQUIVO

            fscanf(arquivo,"%[^\n]\n", nome);
            fscanf(arquivo,"%s\n", cnpj);
            fscanf(arquivo,"%s\n", data);
            fscanf(arquivo,"%s\n", potencia);;

            //IMPRIMINDO DADOS NO NOVO ARQUIVO
            if(strcmp(cnpj, cnpjUsina)!=0)
            {
                limparTela();

                fprintf(arquivoTemp,"%s\n", nome);
                fprintf(arquivoTemp,"%s\n", cnpj);
                fprintf(arquivoTemp,"%s\n", data);
                fprintf(arquivoTemp,"%s\n", potencia);
            }
        }
        excluirContrato(cnpjUsina, 1);
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    //EXCLUINDO O ARQUIVO ANTIGO E RENOMEANDO O NOVO
    remove("Usina.txt");
    rename("Usina_temp.txt", "Usina.txt");

    limparTela();
    printf("\nExclusao da Usina feita com sucesso!\n\n");

}


//FUNÇÃO PARA EXCLUIR O CONSUMIDOR
void exclusaoConsumidor(char identidade[])
{

    char nome[100], idConsumidor[100];
    int cont;

    cont=1;
    FILE * arquivo;
    arquivo = fopen("Consumidor.txt","r");

    FILE * arquivoTemp;
    arquivoTemp = fopen("Consumidor_temp.txt","a+t");

    if(arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo, tente novamente!\n");
    }
    else
    {
        //LENDO O ARQUIVO
        while(feof(arquivo) == 0)
        {
            //LENDO DADOS DO ARQUIVO
            fscanf(arquivo,"%[^\n]\n", nome);
            fscanf(arquivo,"%s\n", idConsumidor);

            //IMPRIMINDO DADOS NO NOVO ARQUIVO CONSUMIDOR
            if(strcmp(idConsumidor, identidade)!=0)
            {
                limparTela();

                fprintf(arquivoTemp, "%s\n", nome);
                fprintf(arquivoTemp, "%s\n", idConsumidor);

            }
        }
        excluirContrato(identidade, 2);
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    //EXCLUINDO O ARQUIVO ANTIGO E RENOMEANDO O NOVO
    remove("Consumidor.txt");
    rename("Consumidor_temp.txt", "Consumidor.txt");

    limparTela();
    printf("\nExclusao do consumidor feita com sucesso!\n\n");

}


//FUNÇÃO PARA CONSULTAR A POTENCIA INICIAL DA USINA
int consultarPotenciaUsina(char cnpjUsina[])
{
    char nome[100], cnpj[100], potencia[100];
    int cont, data[100], potenciaUsina, validarUsinaContrato;
    potenciaUsina = 0;
    validarUsinaContrato = 0;

    FILE * arquivo;
    arquivo = fopen("Usina.txt","r");

    if(arquivo != NULL)
    {
        //LENDO O ARQUIVO USINA
        while(feof(arquivo) == 0)
        {
            //LENDO DADOS DO ARQUIVO
            fscanf(arquivo,"%[^\n]\n", nome);
            fscanf(arquivo,"%s", cnpj);
            fscanf(arquivo,"%02d%02d%d\n", &data[0], &data[1], &data[2]);
            fscanf(arquivo,"%s", potencia);

            //PEGANDO A POTENCIA TOTAL DA USINA
            if(strcmp(cnpj, cnpjUsina)==0)
            {
                potenciaUsina = atoi(potencia);
            }
        }
    }

    fclose(arquivo);

    return potenciaUsina;
}


//FUNÇÃO PARA CONSULTAR O TOTAL DE POTENCIA CONTRATADA POR USINA NO CONTRATO
int potenciaContrato(char cnpjUsina[])
{

    char idConsumidor[100], cnpj[100], potencia[100];
    int cont, data[100], potenciaUsina, potenciaTotal, validarUsinaContrato;
    potenciaTotal = 0;
    validarUsinaContrato = 0;
    cont = 1;

    FILE* arquivoContrato;
    arquivoContrato = fopen("Contrato.txt","r");

    //VALIDANDO SE A USINA ESTÁ PRESENTE NO CONTRATO
    validarUsinaContrato = pesquisaUsinaContrato(cnpjUsina);

    if(validarUsinaContrato == 1)
    {

        if(arquivoContrato != NULL)
        {
            //LENDO O ARQUIVO USINA
            while(feof(arquivoContrato) == 0)
            {
                //LENDO DADOS DO ARQUIVO

                fscanf(arquivoContrato,"%s", cnpj);
                fscanf(arquivoContrato,"%s", idConsumidor);
                fscanf(arquivoContrato,"%02d%02d%d", &data[0], &data[1], &data[2]);
                fscanf(arquivoContrato,"%s\n", potencia);

                //SOOMANDO TODOS AS POTENCIAIS CONTRATADAS DAQUELA USINA
                if(strcmp(cnpj, cnpjUsina)==0)
                {
                    potenciaTotal = potenciaTotal + atoi(potencia);
                    cont = 2;
                }
            }
        }

        fclose(arquivoContrato);
        return potenciaTotal;
    }
    if(validarUsinaContrato == 2)
    {
        return 0;
    }
}



//FUNÇÃO PARA VALIDAR DATA DO CONTRATO, DE ACORDO COM A DATA DE INICIO DE OPERAÇÃO DA USINA
int dataContrato(char identidade[], int data[])
{

    char cnpjUsina[100], nome[100], potencia[100];
    int cont, dataInicial[3], dataComp[3];
    cont = 1;

    FILE* arquivoUsina;
    arquivoUsina = fopen("Usina.txt","r");

    if(arquivoUsina == NULL)
    {
        //limparTela();
        printf("Nenhum contrato!\n");
    }
    else
    {
        //LENDO O ARQUIVO
        while(feof(arquivoUsina) == 0)
        {
            //LENDO DADOS DO ARQUIVO
            fscanf(arquivoUsina,"%[^\n]\n", nome);
            fscanf(arquivoUsina,"%s", cnpjUsina);
            fscanf(arquivoUsina,"%02d%02d%d", &dataInicial[0], &dataInicial[1], &dataInicial[2]);
            fscanf(arquivoUsina,"%s", potencia);

            //VERIFICANDO AS DATAS SE ENCONTRAR A USINA
            if(strcmp(identidade, cnpjUsina)==0)
            {

                dataComp[0] = dataInicial[0];
                dataComp[1] = dataInicial[1];
                dataComp[2] = dataInicial[2];

                if(data[2] < dataInicial[2])
                {
                    cont = 2;
                }
                else
                {
                    if(data[2] == dataInicial[2] && data[1] < dataInicial[1])
                    {
                        cont = 2;
                    }
                    else
                    {
                        if(data[2] == dataInicial[2] && data[1] == dataInicial[1] && data[0] < dataInicial[0])
                        {
                            cont = 2;
                        }
                    }
                }
            }
        }

        fclose(arquivoUsina);

        //SE A DATA DIGITADA FOR ANTERIOR A DATA DE INICIO DA USINA
        if(cont == 2)
        {
            limparTela();
            printf("\nData incorreta, o inicio de operacao da usina foi em: ");
            printf("%02d/%02d/%02d\n", dataComp[0], dataComp[1], dataComp[2]);
            return 1;
        }
        else
        {
            return 2;
        }
    }
}
