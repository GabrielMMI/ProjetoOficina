/********************************************//**
 * @file Erros.c
 * @brief Contem as fun��es de tratamento de erros
 * @bug Nao contem bugs conhecidos!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include <windows.h>
#include "../include/Erros.h"


/********************************************//**
 * \brief Apresenta uma mensagem equivalente ao erro que aconteceu
 *
 * \param hwnd - O handle da janela
 * \param erro - O n�mero do erro que aconteceu
 * \return 0 - Caso n�o haja erros
 *         1 - Caso aconte�a algum erro
 *
 ***********************************************/
int win_trataErros(HWND hwnd, int erro)
{
    int qtErros = 0;
    switch(erro){

//---------- PROPRIETARIO

        case PROP_INSERIR_SUCESSO:
            MessageBox(hwnd, "Proprietario adicionado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_INSERIR_ERRO:
            MessageBox(hwnd, "Erro ao adicionar propriet�rio!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_ALTERAR_SUCESSO:
            MessageBox(hwnd, "Proprietario alterado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_ALTERAR_ERRO:
            MessageBox(hwnd, "Erro ao alterar propriet�rio!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_EXCLUIR_SUCESSO:
            MessageBox(hwnd, "Proprietario exclu�do com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_EXCLUIR_ERRO:
            MessageBox(hwnd, "Erro ao excluir propriet�rio!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_BUSCA_SUCESSO:
            MessageBox(hwnd, "Busca realizada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_BUSCA_EXISTENTE:
            MessageBox(hwnd, "Propriet�rio j� existente!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_BUSCA_INEXISTENTE:
            MessageBox(hwnd, "Propriet�rio inexistente!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_PEGAPROP_SUCESSO:
             MessageBox(hwnd, "Propriet�rio recuperado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_PEGAPROP_ERRO:
            MessageBox(hwnd, "Erro ao recuperar propriet�rio!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case CPF_VALIDO:
            MessageBox(hwnd, "Cpf v�lido!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case CPF_INVALIDO:
            MessageBox(hwnd, "Cpf inv�lido!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case TEL_VALIDO:
            MessageBox(hwnd, "Telefone v�lido!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case TEL_INVALIDO:
            MessageBox(hwnd, "Telefone inv�lido!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

//---------- VEICULO

        case VEIC_INSERIR_SUCESSO:
            MessageBox(hwnd, "Veiculo adicionado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_INSERIR_ERRO:
            MessageBox(hwnd, "Erro ao adicionar veiculo!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case VEIC_ALTERAR_SUCESSO:
            MessageBox(hwnd, "Veiculo alterado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_ALTERAR_ERRO:
            MessageBox(hwnd, "Erro ao alterar veiculo!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case VEIC_EXCLUIR_SUCESSO:
            MessageBox(hwnd, "Veiculo exclu�do com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_EXCLUIR_ERRO:
            MessageBox(hwnd, "Erro ao excluir veiculo!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case VEIC_BUSCA_EXISTENTE:
            MessageBox(hwnd, "Veiculo j� existente!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_BUSCA_INEXISTENTE:
            MessageBox(hwnd, "Veiculo inexistente!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_EXCLUIR_ERRO_MANUT:
            MessageBox(hwnd, "Erro ao excluir ve�culo! Veiculo com manuten��o registrada!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case VEIC_BUSCA_SUCESSO:
            MessageBox(hwnd, "Busca efetuada com Sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_PEGAVEIC_SUCESSO:
            MessageBox(hwnd, "Veiculo recuperado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_PEGAVEIC_ERRO:
            MessageBox(hwnd, "Erro ao recuperar ve�culo!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PLACA_VALIDA:
            MessageBox(hwnd, "Placa v�lida!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PLACA_INVALIDA:
            MessageBox(hwnd, "Placa inv�lida!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case CHASSI_VALIDO:
            MessageBox(hwnd, "Chassi v�lido!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case CHASSI_REPETIDO:
            MessageBox(hwnd, "Chassi repetido!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;
//---------- MANUTENCAO
        case MANUT_INSERIR_SUCESSO:
            MessageBox(hwnd, "Manuten��o adicionada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case MANUT_INSERIR_ERRO:
            MessageBox(hwnd, "Erro ao adicionar manuten��o!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_INSERIR_ERRO_DIA:
            MessageBox(hwnd, "Erro ao adicionar manuten��o! Vc j� cadastrou este ve�culo na manuten��o hoje!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_EXCLUIR_SUCESSO:
            MessageBox(hwnd, "Manuten��o exclu�da com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case MANUT_EXCLUIR_ERRO:
            MessageBox(hwnd, "Erro ao excluir manuten��o!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_EXCLUIR_ERRO_MANUT_INEXISTENTE:
            MessageBox(hwnd, "Erro ao excluir manuten��o! Manuten��o inexistente!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_BUSCA_SUCESSO:
            MessageBox(hwnd, "Manuten��o encontrada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case DATA_ATUAL_ERRO:
            MessageBox(hwnd, "Erro ao recuperar a data atual!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case DATA_ATUAL_SUCESSO:
            MessageBox(hwnd, "Data atual recuperada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case DATA_INVALIDA:
            MessageBox(hwnd, "Data inv�lida!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case DATA_INVALIDA_NAO_FORMATADA:
            MessageBox(hwnd, "Data inv�lida! N�o foi inserida no formato correto!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case DATA_INVALIDA_NAO_NUMERO:
            MessageBox(hwnd, "Data inv�lida! N�o s�o n�meros!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case CONVERTE_DATA_SUCESSO:
            MessageBox(hwnd, "Sucesso ao converter a data!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case CONVERTE_DATA_ERRO:
            MessageBox(hwnd, "Erro ao converter data!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;


//---------- ARQUIVO
        case ARQUIVO_EXISTENTE:
            MessageBox(hwnd, "Arquivo existente!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case ABRIR_ARQUIVO_SUCESSO:
            MessageBox(hwnd, "Arquivo criado/aberto com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;
        
        case FECHA_ARQUIVO_SUCESSO:
            MessageBox(hwnd, "Arquivo criado/aberto com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;
        
        case FECHA_ARQUIVO_ERRO:
            MessageBox(hwnd, "Arquivo criado/aberto com sucesso!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

    }

    return qtErros;
}
