#include <stdio.h>
#include <locale.h>
#include "221022266.h"
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define TAM_NOME 100
#define TAM_CPF 12
#define TAM_CNPJ 15

void cadastrarUsina();
void cadastrarConsumidor ();
void cadastrarContrato();
void consultarConsumidor();
void consultarUsina();
void excluirConsumidor();
void excluirUsina();
void chamado();


//função para cadastro da usina
void cadastrarUsina()
{

    USINA stUsina;
    int cont, validacaoCNPJ, validacaoData, data[3], testeArquivo, vExiste;
    float potencia;
    char cnpjUsina[TAM_CNPJ], nomeUsina[TAM_NOME];

    testeArquivo = 0;

    printf("---------------------------------------------------\n");
    printf("|               Cadastro da Usina                 |\n");
    printf("---------------------------------------------------\n");

    //solicitação do CNPJ até que o mesmo seja válido
    do
    {
        vExiste = 0;
        printf("\nDigite o CPNJ da empresa: (somente numeros)\n");

        fflush(stdin);
        scanf(" %s", cnpjUsina);

        //função de validar o CNPJ contida na biblioteca
        validacaoCNPJ = validarCNPJ(cnpjUsina);

        if(validacaoCNPJ != 2)
        {
            limparTela();
            printf("\nCNPJ incorreto, tente novamente!\n\n");
        }
        else
        {
            //SALVAR CNPJ Na STRUCT
            for(cont=0; cont < TAM_CNPJ; cont++)
            {
                stUsina.cnpj[cont] = cnpjUsina[cont];
            }
            if(pesquisaValidar(cnpjUsina) != 2)
            {
                limparTela();
                printf("\nEsse CNPJ ja existe!\n");
                validacaoCNPJ = 2;
                vExiste = 1;
            }
        }
    }
    while(validacaoCNPJ != 2);

    if(vExiste == 0)
    {
        //solicitando nome com sua devia verificação
        do
        {
            fflush(stdin);
            printf("\nDigite o nome da empresa:\n");
            fgets(stUsina.nomeUsina, TAM_NOME, stdin);

            if(strlen(stUsina.nomeUsina) < 4)
            {
                limparTela();
                printf("Nome invalido, digite novamente!\n");
            }

        }
        while(strlen(stUsina.nomeUsina) < 4);

        //solicitando a data até que ela seja válida
        do
        {
            printf("\nDigite a data de inicio da operacao: (formato: dd/mm/aaaa)\n");
            scanf("%d/%d/%d", &data[0], &data[1], &data[2]);

            //chamando a função de validar data da biblioteca
            validacaoData = validarData(data);

            if(validacaoData != 2)
            {
                limparTela();
                printf("\nData incorreta, tente novamente!\n");
            }
            else
            {
                //SALVAR DATA NA STRUCT
                stUsina.data[0] = data[0];
                stUsina.data[1] = data[1];
                stUsina.data[2] = data[2];

            }
        }
        while(validacaoData != 2);

        //solicitando uma potência até que ela seja válida
        do
        {
            printf("\nDigite potencia de geracao estimada: (MW)\n");
            scanf(" %f", &stUsina.potencia);
            if(stUsina.potencia < 1){
                limparTela();
            printf("\nPotencia Incorreta, digite novamente!\n");}
        }
        while(stUsina.potencia < 1);


        limparTela();
        printf("\nUsina cadastrada com sucesso!\n\n");

        //passando os dados da struct como parâmetro para salvar no arquivo
        arquivoUsina(stUsina.nomeUsina, stUsina.cnpj, stUsina.data, stUsina.potencia);
    }
    chamado(1);

}


//função para cadastrar os consumidores
void cadastrarConsumidor()
{

    CONSUMIDOR stConsumidor;

    char nomeConsumidor[TAM_NOME],cpf[TAM_CPF], cnpj[TAM_CNPJ];
    int validacaoID, opcao, cont2, vExiste;

    printf("---------------------------------------------------\n");
    printf("|             Cadastro do Consumidor              |\n");
    printf("---------------------------------------------------\n");

    //solicitando um nome válido
    do
    {
        fflush(stdin);
        printf("\nDigite o seu nome:\n");
        fgets(stConsumidor.nomeConsumidor, TAM_NOME, stdin);

        if(strlen(stConsumidor.nomeConsumidor) < 4)
        {
            limparTela();
            printf("Nome invalido, digite novamente!\n");
        }

    }
    while(strlen(stConsumidor.nomeConsumidor) < 4);

    //duas opções de cadastro: CPF e CNPJ
    do
    {
        vExiste = 0;

        printf("\nEscolha como deseja se cadastrar:\n1- CPF \n2- CNPJ\n");
        scanf("%d", &opcao);
        if(opcao < 1 || opcao > 2)
        {
            limparTela();
            printf("Entrada incorreta, tente novamente!\n\n");
        }
        else
        {
            //Entrada de dados de acordo com a escolha feita pelo consumidor, para a validação
            switch(opcao)
            {
            //Opção 1 com laço de repetição para garantir que o CPF cadastrado pelo consumidor será válido
            case 1:
                do
                {
                    printf("\nDigite o CPF: (somente numeros)\n");
                    scanf(" %s", cpf);

                    //Verificão de CPF
                    validacaoID = validarCPF(cpf);

                    if(pesquisaValidar(cpf) != 2)
                    {
                        limparTela();
                        printf("\nEsse CPF ja existe!\n\n");
                        validacaoID = 2;
                        vExiste = 1;
                    }
                    else
                    {

                        //Retorno da verifica��o
                        if(validacaoID == 2)
                        {
                            //SALVAR NO STRUCT
                            for(cont2 = 0; cont2 < TAM_CPF; cont2++)
                            {
                                stConsumidor.cpfConsumidor[cont2] = cpf[cont2];
                            }

                            //PASSANDO DADOS COMO PARÂMETRO PARA SALVAR NO ARQUIVO
                            arquivoConsumidor(stConsumidor.nomeConsumidor, stConsumidor.cpfConsumidor, 1);
                        }
                        else
                        {
                            limparTela();
                            printf("\nCPF incorreto, tente novamente!\n");
                        }
                    }
                }

                while(validacaoID != 2);
                break;

            //Opção 2 com laço de repetição para garantir que o CNPJ cadastrado pelo consumidor será válido
            case 2:
                do
                {
                    printf("\nDigite o CNPJ: (somente numeros)\n");
                    scanf("%s", cnpj);

                    //Verificacao de CNPJ
                    validacaoID = validarCNPJ(cnpj);

                    if(pesquisaValidar(cnpj) != 2)
                    {
                        limparTela();
                        printf("\nEsse CNPJ ja existe!\n\n");
                        validacaoID = 2;
                        vExiste = 1;
                    }
                    else
                    {

                        //Retorno da verificacao
                        if(validacaoID == 2)
                        {
                            //SALVAR NA STRUCT
                            for(cont2=0; cont2 < TAM_CNPJ; cont2++)
                            {
                                stConsumidor.cnpjConsumidor[cont2] = cnpj[cont2];
                            }
                            //PASSANDO DADOS COMO PARÂMETRO PARA SALVAR NO ARQUIVO
                            arquivoConsumidor(stConsumidor.nomeConsumidor, stConsumidor.cnpjConsumidor, 2);
                        }
                        else
                        {
                            limparTela();
                            printf("\nCNPJ incorreto, tente novamente!\n");
                        }
                    }
                }
                //VERIFICAÇÃO RESPONSÁVEL PELO CNPJ SE É VÁLIDO OU SE EXISTE
                while(validacaoID != 2);
                break;

            }
        }
    }
    while(opcao < 1 || opcao > 2);
    if(vExiste == 0)
    {
        limparTela();

        printf("Consumidor cadastrado com sucesso!\n\n");
    }
    //CHAMADO DE FINALIZAÇÃO
    chamado(2);
}


//FUNÇÃO PARA CADASTRAR CONTRATO
void cadastrarContrato()
{

//STRUCT CONTRATO
    CONTRATO stContrato;

    char cnpjCtt[TAM_CNPJ], cpfCtt[TAM_CPF], cnpjUsina[TAM_CNPJ];
    int data[3], validacaoUsina, validacaoID, opcao, cont2, vExisteUsina, vExisteConsumidor, validarPotencia;
    int potenciaInicial, potenciaContratada, comparaPotencia, validarDataContrato;

    potenciaContratada = 0;
    potenciaInicial = 0;
    comparaPotencia = 0;
    vExisteUsina = 0;
    vExisteConsumidor = 0;
    validarPotencia = 0;
    validacaoID = 0;
    validacaoUsina = 0;
    validarDataContrato = 0;

    printf("---------------------------------------------------\n");
    printf("|               Cadastro do Contrato              |\n");
    printf("---------------------------------------------------\n");

    //solicitando o CNPJ de uma usina cadastrada
    do
    {
        fflush(stdin);
        printf("\nDigite o CNPJ da usina:\n");
        scanf("%s", cnpjUsina);

        //verificacao do CNPJ digitado
        if(validarCNPJ(cnpjUsina) != 2)
        {
            limparTela();
            printf("\nCNPJ incorreto, tente novamente!\n\n");
        }
        else
        {
            //VERIFICANDO SE A USINA EXISTE
            if(pesquisaUsina(cnpjUsina) == 1)
            {
                //PASSANDO OS DADOS DO CNP PARA A STRUCT SE A USINA EXISTIR E FOR VÁLIDA
                for(cont2=0; cont2 < TAM_CNPJ; cont2++)
                {
                    stContrato.cnpjUsina[cont2] = cnpjUsina[cont2];
                }
                //ATRIBUINDO VALORES DE VALIDAÇÃO DA USINA
                validacaoUsina = 1;
                vExisteUsina = 0;
            }
            else
            {
                limparTela();
                printf("CNPJ nao cadastrado!\n\n");
                validacaoUsina = 1;
                vExisteUsina = 1;
                //ATRIBUINDO VALORES PARA NÃO VALIDAR A USINA
            }
        }
    }
    while(validacaoUsina != 1);

    if(vExisteUsina == 0)
    {
        //solicitando a data até que ela seja válida
        do
        {
            printf("\nDigite a data de inicio do contrato: (formato: dd/mm/aaaa)\n");
            scanf("%d/%d/%d", &data[0], &data[1], &data[2]);

            if(validarData(data) != 2)
            {
                limparTela();
                printf("\nData incorreta, tente novamente!\n");
            }
            else
            {
                //SALVAR DATA NA STRUCT
                stContrato.dataCt[0] = data[0];
                stContrato.dataCt[1] = data[1];
                stContrato.dataCt[2] = data[2];

                //VERIFICACAO DA DATA EM RELACAO A DATA DE INICIO DE OPERACAO DA USINA
                validarDataContrato = dataContrato(stContrato.cnpjUsina, stContrato.dataCt);
            }
        }
        while(validarData(data) != 2 || validarDataContrato != 2);

        //duas opções de cadastro: CPF e CNPJ
        do
        {
            vExisteConsumidor = 0;
            printf("\nQual das identificacoes deseja para uso no contrato?:\n1- CPF \n2- CNPJ\n");
            scanf("%d", &opcao);
            if(opcao < 1 || opcao > 2)
            {
                limparTela();
                printf("Entrada incorreta, tente novamente!\n\n");
            }
            else
            {
                //Entrada de dados de acordo com a escolha feita pelo consumidor, para a validação
                switch(opcao)
                {
                //Opção 1 com laço de repetição para garantir que o CPF cadastrado pelo consumidor será válido
                case 1:
                    do
                    {
                        fflush(stdin);
                        printf("\nDigite o CPF: (somente numeros)\n");
                        scanf(" %[^\n]", cpfCtt);

                        //FUNCAO PARA VERIFICAR SE O CPF JÁ ESTA CADASTRADO COM ALGUM OUTRO CONSUMIDOR
                        validacaoID = pesquisaConsumidor(cpfCtt);

                        //VALIDACAO DO CPF
                        if(validarCPF(cpfCtt) != 2)
                        {
                            limparTela();
                            printf("CPF incorreto, tente novamente!\n");
                        }
                        else
                        {
                            if(validacaoID == 1)
                            {
                                //SALVAR CPF NA STRUCT
                                for(cont2 = 0; cont2 < TAM_CPF; cont2++)
                                {
                                    stContrato.cpfConsumidor[cont2] = cpfCtt[cont2];
                                }
                                validacaoID = 1;
                            }
                            else
                            {
                                limparTela();
                                printf("\nCPF do consumidor nao cadastrado!\n");
                                //INVALIDANDO O CPF DIGITADO PARA QUE REPITA A OPERACAO CASO ESTEJA ALGO INVÁLIDO
                                vExisteConsumidor = 1;
                                validacaoID = 1;
                            }
                        }
                    }
                    while(validacaoID != 1);
                    break;

                //Opção 2 com laço de repetição para garantir que o CNPJ cadastrado pelo consumidor será válido
                case 2:
                    do
                    {
                        fflush(stdin);
                        printf("\nDigite o CNPJ: (somente numeros)\n");
                        scanf("%s", cnpjCtt);

                        //Retorno da verificacao
                        validacaoID = pesquisaConsumidor(cnpjCtt);

                        if(validarCNPJ(cnpjCtt) != 2)
                        {
                            //CNPJ INVÁLIDO
                            limparTela();
                            printf("CNPJ incorreto, tente novamente!\n");
                        }
                        else
                        {
                            if(validacaoID == 1)
                            {
                                //SALVAR OO CNPJ NA STRUCT
                                for(cont2=0; cont2 < TAM_CNPJ; cont2++)
                                {
                                    stContrato.cnpjConsumidor[cont2] = cnpjCtt[cont2];
                                }
                                //VALIDANDO A PASSAGEM DO CÓDIGO
                                validacaoID = 1;
                            }
                            else
                            {
                                //INVALIDANDO O CNPJ PARA REPETIR A OPERACAO CASO ALGO ESTEJA INVALIDO
                                limparTela();
                                printf("\nCNPJ do consumidor nao cadastrado!\n");
                                vExisteConsumidor = 1;
                                validacaoID = 1;
                            }
                        }
                    }
                    while(validacaoID != 1);
                    break;
                }
            }
        }
        while(opcao < 1 || opcao > 2);


        if(vExisteConsumidor == 0)
        {
            do
            {
                //SOLICITANDO A POTENCIA PARA CONTRATAR
                printf("\nDigite potencia a ser contratada: (MW)\n");
                scanf(" %d", &stContrato.potenciaCt);

                if(stContrato.potenciaCt < 1){
                    limparTela();
                printf("\nPotencia Incorreta!\n\n");

                }
                else{
                //POTENCIA TOTAL DA USINA
                potenciaInicial = consultarPotenciaUsina(cnpjUsina);


                //TOTAL DE POTENCIA JÁ CONTRATADA
                potenciaContratada = potenciaContrato(cnpjUsina);

                //POTENCIA DISPONÍVEL
                comparaPotencia = (potenciaInicial - potenciaContratada);

                //VALIDANDO A POTENCIA SOLICITADA PARA O CONTRATO EM COMPARACAO A DISPONIBILIDADE
                if(stContrato.potenciaCt <= comparaPotencia)
                {
                    //VALIDANDO A PASSAGEM DO CÓDIGO
                    validarPotencia = 1;
                }

                else
                {
                    //POTENCIA INVÁLIDA
                    limparTela();
                    printf("\nEntrada incorreta, a usina possui somente %d (KW) restantes para contrato, tente novamente!\n\n", comparaPotencia);
                }}
            }
            while(stContrato.potenciaCt < 1 && validarPotencia == 1);

            //ENTRANDO NESSA PARTE SE A POTENCIA FOR VÁLIDA
            if(validarPotencia == 1)
            {
                limparTela();
                if(opcao == 1)
                {
                    //PASSANDO OS DADOS PARA SALVAR NO CONTRATO (CONSUMIDOR COM CPF)
                    arquivoContrato(stContrato.cnpjUsina, stContrato.cpfConsumidor, stContrato.dataCt, stContrato.potenciaCt, opcao);
                }
                else
                {
                    //PASSANDO OS DADOS PARA SALVAR NO CONTRATO (CONSUMIDOR COM O CNPJ)
                    arquivoContrato(stContrato.cnpjUsina, stContrato.cnpjConsumidor, stContrato.dataCt, stContrato.potenciaCt, opcao);
                }
                printf("Contrato cadastrado com sucesso!\n\n");
            }
        }
    }
    //CHAMADO DE FINALIZAÇÃO
    chamado(3);
}


//FUNÇÃO PARA CONSULTAR USINA
void consultarUsina()
{
    char cnpj[TAM_CNPJ], validador, vExiste;
    vExiste = 0;

    limparTela();

    printf("---------------------------------------------------\n");
    printf("|                 Consultar Usina                 |\n");
    printf("---------------------------------------------------\n");

    do
    {
        validador = 1;

        //SOLICITANDO O CNPJ DA USINA
        printf("Digite o CNPJ da Usina que deseja encontrar:\n");
        scanf("%s", cnpj);

        //VALIDANDO O CNPJ
        if(validarCNPJ(cnpj) != 2)
        {
            limparTela();
            printf("\nCNPJ invalido, tente novamente!\n\n");
            validador = 0;
        }
        else
        {
            //VERIFICANDO SE ESSE CNPJ EXISTE
            if(pesquisaUsina(cnpj) != 1)
            {
                //INVALIDANDO A EXXISTENCIA DA USINA
                limparTela();
                printf("Essa Usina nao existe!\n\n");
                validador = 1;
            }
            else
            {
                //VALIDANDO O CNPJ
                vExiste = 1;
            }
        }
    }
    while(validador == 0);

    //SE A USINA EXISTIR CONSULTE-A
    if(vExiste == 1)
    {
        //CHAMANDO A FUNÇÃO DE CONSULTA
        consultarArquivoUsina(cnpj);
    }
    chamado(4);
}


//FUNÇÃO PARA CONSULTAR CONSUMIDOR
void consultarConsumidor()
{
    int op, validador, vExiste;
    char idConsumidor[100];
    validador = 0;

    limparTela();

    printf("---------------------------------------------------\n");
    printf("|              Consultar Consumidor               |\n");
    printf("---------------------------------------------------\n");

    do
    {
        //SOLICITANDO SE SERÁ CPF OU CNPJ PARA A CONSULTA
        printf("A identificacao do consumidor e:\n\n1 - CPF\n2 - CNPJ\n");
        scanf("%d", &op);

        if(op < 1 || op > 2)
        {
            limparTela();
            printf("Entrada invalida, digite novamente!\n\n");
        }
    }
    while(op < 1 || op > 2);

    do
    {
        vExiste = 0;
        if(op == 1)
        {
            //SOLICITANDO CPF PADA A CONSULTA
            printf("\nDigite o CPF do consumidor:\n");
            scanf("%s", idConsumidor);

            //VALIDANDO O CPF
            if(validarCPF(idConsumidor) == 2)
            {
                validador = 1;
                //VERIFICANDO SE O CPF EXISTE
                if (pesquisaConsumidor(idConsumidor) != 1)
                {
                    //VALIDANDO A PASSAGEM DO CÓDIGO
                    limparTela();
                    printf("Esse CPF nao existe!\n\n");
                    vExiste = 1;
                }
            }

            else
            {
                limparTela();
                printf("\nCPF invalido, tente novamente!\n\n");
            }
        }
        else
        {
            //SOLICITANDO O CNPJ
            printf("\nDigite o CNPJ do consumidor:\n");
            scanf("%s", idConsumidor);
            //VALIDANDO O CNPJ
            if(validarCNPJ(idConsumidor) == 2)
            {
                validador = 1;
                //VERIFICANDO SE O CNPJ EXISTE
                if(pesquisaConsumidor(idConsumidor) != 1)
                {
                    //VERIRICANDO SE O CNPJ EXISTE
                    limparTela();
                    printf("Esse CNPJ nao existe!\n\n");
                    vExiste = 1;
                }
            }
            else
            {
                limparTela();
                printf("\nCNPJ invalido, tente novamente!\n\n");
            }
        }
    }
    while(validador != 1);
    //CHAMANDO A FUNCAO DE CONSULTAR O CONSUMIDOR
    if(vExiste == 0)
    {
        consultarArquivoConsumidor(idConsumidor);
    }
    //FUNCAO DE FINALIZAÇÃO
    chamado(5);
}


//FUNÇÃO PARA REALIZAR A EXCLUSÃO DA USINA
void excluirUsina()
{
    char cnpjUsina[TAM_CNPJ], vExiste;
    int validador, op;
    validador = 0;
    vExiste = 0;

    limparTela();

    printf("---------------------------------------------------\n");
    printf("|                 Excluir Usina                   |\n");
    printf("---------------------------------------------------\n");

    do
    {
        //SOLICITANDO O CNPJ DA USINA
        printf("Digite o CNPJ da usina que deseja excluir:\n");
        scanf("%s", cnpjUsina);

        //VALIDANDO O CNPJ
        if(validarCNPJ(cnpjUsina) == 2 )
        {
            //VERIFICANDO SE O CNPJ EXISTE
            if(pesquisaUsina (cnpjUsina) == 1)
            {
                validador = 1;
            }
            else
            {
                limparTela();
                printf("Essa usina nao existe!\n\n");
                vExiste = 1;
                validador = 1;
            }
        }
        else
        {
            limparTela();
            printf("CNPJ incorreto, tente novamente!\n\n");
        }

    }
    while(validador != 1);

    //SE A USINA EXISTIR, ENTRA NESSA CONDIÇÃO DE EXCLUSAO
    if(vExiste == 0)
    {
        do
        {
            //CONFIRMACAO DA EXCLUSAO DA USINA
            printf("\n\nRealmente deseja excluir a usina com  o CNPJ %s juntamente com todos os seus contratos?\n1 - Sim\n2 - Nao\n", cnpjUsina);
            scanf("%d", &op);
            if(op == 1)
            {
                //CHAMANDO A FUNÇÃO DE EXCLUIR A USINA
                limparTela();
                exclusaoUsina(cnpjUsina);
            }
            else if(op == 2)
            {
                limparTela();
                printf("Exclusao da Usina cancelada!\n\n");
            }
            else
            {
                limparTela();
                printf("Entrada incorreta, digite novamente!\n");
            }

        }
        while(op < 1 || op > 2);
    }

    //CHAMANDO A "FUNCAO FINAL"
    chamado(6);
}


//FUNÇÃO PARA REALIZAR A EXCLUSÃO DO CONSUMIDOR
void excluirConsumidor()
{
    char cnpjConsumidor[TAM_CNPJ], cpfConsumidor[TAM_CPF], vExiste;
    int validador, op, opId;
    validador = 0;
    vExiste = 0;

    limparTela();

    printf("---------------------------------------------------\n");
    printf("|                Excluir Consumidor               |\n");
    printf("---------------------------------------------------\n");

    do
    {
        //SOLICITANDO QUAL IDENTIDADE O CONSUMIDOR ESTÁ CADASTRADO
        printf("Digite qual a opcao da identificacao do Consumidor que deseja excluir:\n\n1 - CPF\n2 - CNPJ\n");
        scanf("%d", &opId);

        if(opId < 1 || opId > 2)
        {
            limparTela();
            printf("Entrada incorreta, digite novamente!\n\n");
        }
    }
    while(opId < 1 || opId > 2);

    do
    {
        if(opId == 1)
        {
            //SOLICITANDO O CPF DO CONSUMIDOR
            printf("\nDigite o CPF do Consumidor:\n");
            scanf("%s", cpfConsumidor);

            //VALIDANDO O CPF DO CONSUMIDOR
            if(validarCPF(cpfConsumidor) == 2 )
            {
                //VALIDANDO SE O CPF EXISTE
                if(pesquisaConsumidor(cpfConsumidor) == 1)
                {
                    validador = 1;
                }
                else
                {
                    //INVALIDANDO A PASSAGEM DO CÓDIGO
                    limparTela();
                    printf("Esse consumidor nao existe!\n\n");
                    vExiste = 1;
                    validador = 1;
                }
            }
            else
            {
                limparTela();
                printf("CPF incorreto, tente novamente!\n\n");
            }
        }

        if(opId == 2)
        {
            //SOLICITANDO O CNPJ CADASTRADO PELO CONSUMIDOR
            printf("\nDigite o CNPJ do Consumidor:\n");
            scanf("%s", cnpjConsumidor);

            //VALIDANDO O CNPJ
            if(validarCNPJ(cnpjConsumidor) == 2 )
            {
                //VALIDANDO SE O CNPJ EXISTE
                if(pesquisaConsumidor(cnpjConsumidor) == 1)
                {
                    validador = 1;
                }
                else
                {
                    //INVALIDANDO A PASSAGEM DO CÓDIGO
                    limparTela();
                    printf("Esse consumidor nao existe!\n\n");
                    vExiste = 1;
                    validador = 1;
                }
            }
            else
            {
                limparTela();
                printf("CNPJ incorreto, tente novamente!\n\n");
            }
        }
    }
    while(validador != 1);


    if(opId == 1 && vExiste == 0)
    {
        do
        {
            //CONFIRMAÇÃO DA EXCLUSÃO DO CONSUMIDOR
            printf("\n\nRealmente deseja excluir o consumidor com o CPF %s juntamente com todos os seus contratos?\n\n1 - Sim\n2 - Nao\n", cpfConsumidor);
            scanf("%d", &op);
            if(op == 1)
            {
                //CHAMANDO A FUNÇÃO DE EXCLUSÃO DO CONSUMIDOR
                limparTela();
                exclusaoConsumidor(cpfConsumidor);
            }
            else if(op == 2)
            {
                limparTela();
                printf("Exclusao do consumidor cancelada!\n\n");
            }
            else
            {
                limparTela();
                printf("Entrada incorreta, digite novamente!\n");
            }
        }
        while(op < 1 || op > 2);
    }


    if(opId == 2 && vExiste == 0)
    {
        do
        {
            //CONFIRMANDO EXCLUSÃO DO CONSUMIDOR
            printf("\n\nRealmente deseja excluir o consumidor com o CNPJ %s juntamente com todos os seus contratos?\n\n1 - Sim\n2 - Nao\n", cnpjConsumidor);
            scanf("%d", &op);
            if(op == 1)
            {
                //CHAMANDO FUNÇÃO PARA EXCLUIR O CONSUMIDOR
                //limparTela();
                exclusaoConsumidor(cnpjConsumidor);
            }
            else if(op == 2)
            {
                limparTela();
                printf("Exclusao do Consumidor cancelada!\n\n");
            }
            else
            {
                limparTela();
                printf("Entrada incorreta, digite novamente!\n");
            }

        }
        while(op < 1 || op > 2);
    }

    //CHAMANDO A FUNÇÃO FINAL
    chamado(7);
}


//FUNÇÃO MENU
void menu()
{
    int opcaoMenu, confirmacaoFinal;

    do
    {
        //OPÇÕES DO MENU
        printf("---------------------------------------------------\n");
        printf("|               Menu de opcoes                    |\n");
        printf("---------------------------------------------------\n\n");
        printf("1) Cadastrar Usina\n");
        printf("2) Cadastrar Consumidor\n");
        printf("3) Cadastrar Contrato entre Consumidor e Usina\n");
        printf("4) Consultar Usina Cadastrada\n");
        printf("5) Consultar Consumidor Cadastrado\n");
        printf("6) Excluir Usina\n");
        printf("7) Excluir Consumidor\n");
        printf("8) Encerrar Programa\n\n");

        printf("Digite o numero da operacao desejada:\n");
        scanf("%d", &opcaoMenu);

        limparTela();

        //VERIFICAÇÃO SE A ENTRADA É VÁLIDA
        if(opcaoMenu > 0 && opcaoMenu <= 8)
        {

            switch(opcaoMenu)
            {
            case 1:
                //CHAMANDO FUNÇÃO PARA CADASTRAR USINA
                cadastrarUsina();

                break;
            case 2:
                //CHAMANDO FUNÇÃO PARA CADASTRAR CONSUMIDOR
                cadastrarConsumidor();

                break;
            case 3:
                //CHAMANDO FUNÇÃO PARA CADASTRAR CONTRATO
                cadastrarContrato();

                break;
            case 4:
                //CHAMANDO FUNÇÃO PARA CONSULTAR USINA
                consultarUsina();

                break;
            case 5:
                //CHAMANDO FUNÇÃO PARA CONSULTAR CONSUMIDOR
                consultarConsumidor();

                break;
            case 6:
                //CHAMANDO FUNÇÃO PARA EXCLUIR USINA
                excluirUsina();

                break;
            case 7:
                //CHAMANDO FUNÇÃO PARA EXCLUIR CONSUMIDOR
                excluirConsumidor();

                break;
            //CASO PARA ENCERRAR A EXECUÇÃO DO PROGRAMA COM CONFIRMAÇÃO
            case 8:
                printf("\nDeseja realmente encerrar o programa? (escolha o número a frente da operacao)");
                printf("\n1- Sim");
                printf("\n2- Nao\n");
                scanf("%d", &confirmacaoFinal);

                //CONFIRMANDO O ENCERRAMENTO DO PROGRAMA
                do
                {
                    if(confirmacaoFinal == 2)
                    {
                        opcaoMenu = 100;
                        limparTela();
                    }
                    else if(confirmacaoFinal == 1)
                    {
                        limparTela();
                        printf("Ate uma proxima!\n");
                    }
                    else
                    {
                        printf("\nEntrada incorreta, digite novamente!\n");
                    }
                }
                while(confirmacaoFinal < 1 || confirmacaoFinal > 2);
                break;

            }
        }

        else
        {
            printf("\nEntrada incorreta, digite novamente!\n");
        }

    }
    while(opcaoMenu < 1 || opcaoMenu > 8);
}



//FUNÇÃO FINAL DA OPERAÇÃO
void chamado (int n)
{

    int opcao;
    do
    {
        printf("---------------------------------------------------\n");
        printf("|    1 - Refazer a operao                         |\n");
        printf("|    2 - Voltar ao menu principal                 |\n");
        printf("|    3 - Encerrar                                 |\n");
        printf("---------------------------------------------------\n");
        scanf("%d", &opcao);

        if(opcao < 1 || opcao > 3)
        {

            limparTela();
            printf("Entrada incorreta, tente novamente!\n\n");

        }
        else
        {
            //CHAMANDO A FUNÇÃO NOVAMENTE DE ACORDO COM O PARÂMETRO PASSADO POR ELA PARA UMA REEXECUÇÃO DA FUNÇÃO
            switch(opcao)
            {
            case 1:
                switch(n)
                {
                case 1:
                    limparTela();
                    cadastrarUsina();
                    break;
                case 2:
                    limparTela();
                    cadastrarConsumidor();
                    break;
                case 3:
                    limparTela();
                    cadastrarContrato();
                    break;
                case 4:
                    limparTela();
                    consultarUsina();
                    break;
                case 5:
                    limparTela();
                    consultarConsumidor();
                    break;
                case 6:
                    limparTela();
                    excluirUsina();
                    break;
                case 7:
                    limparTela();
                    excluirConsumidor();
                    break;
                }
                break;
            //VOLTANDO PARA O MENU INICIAL
            case 2:
                limparTela();
                menu();
                break;
            //ENCERRANDO A OPERAÇÃO DO CÓDIGO
            case 3:
                limparTela();
                break;
            }
        }

    }
    while(opcao < 1 || opcao > 3);
}



//função principal chamando a função menu na biblioteca 221022266.h
int main()
{
    setlocale(LC_ALL,"");

    printf("---------------------------------------------------\n");
    printf("|      Sistema de Geracao Compartilhada (SGC)     |\n");
    printf("---------------------------------------------------\n\n");

    //CHAMANDO A FUNÇÃO MENU
    menu();

    return 0;
}
