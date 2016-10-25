/********************************************//**
 * @file Erros.c
 * @brief Contem as funções de tratamento de erros
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
 * \param erro - O número do erro que aconteceu
 * \return 0 - Caso não haja erros
 *         1 - Caso aconteça algum erro
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
            MessageBox(hwnd, "Erro ao adicionar proprietário!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_ALTERAR_SUCESSO:
            MessageBox(hwnd, "Proprietario alterado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_ALTERAR_ERRO:
            MessageBox(hwnd, "Erro ao alterar proprietário!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_EXCLUIR_SUCESSO:
            MessageBox(hwnd, "Proprietario excluído com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_EXCLUIR_ERRO:
            MessageBox(hwnd, "Erro ao excluir proprietário!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_BUSCA_SUCESSO:
            MessageBox(hwnd, "Busca realizada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_BUSCA_EXISTENTE:
            MessageBox(hwnd, "Proprietário já existente!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_BUSCA_INEXISTENTE:
            MessageBox(hwnd, "Proprietário inexistente!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PROP_PEGAPROP_SUCESSO:
             MessageBox(hwnd, "Proprietário recuperado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PROP_PEGAPROP_ERRO:
            MessageBox(hwnd, "Erro ao recuperar proprietário!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case CPF_VALIDO:
            MessageBox(hwnd, "Cpf válido!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case CPF_INVALIDO:
            MessageBox(hwnd, "Cpf inválido!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case TEL_VALIDO:
            MessageBox(hwnd, "Telefone válido!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case TEL_INVALIDO:
            MessageBox(hwnd, "Telefone inválido!", "", MB_OK | MB_ICONERROR);
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
            MessageBox(hwnd, "Veiculo excluído com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_EXCLUIR_ERRO:
            MessageBox(hwnd, "Erro ao excluir veiculo!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case VEIC_BUSCA_EXISTENTE:
            MessageBox(hwnd, "Veiculo já existente!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_BUSCA_INEXISTENTE:
            MessageBox(hwnd, "Veiculo inexistente!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_EXCLUIR_ERRO_MANUT:
            MessageBox(hwnd, "Erro ao excluir veículo! Veiculo com manutenção registrada!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case VEIC_BUSCA_SUCESSO:
            MessageBox(hwnd, "Busca efetuada com Sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_PEGAVEIC_SUCESSO:
            MessageBox(hwnd, "Veiculo recuperado com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case VEIC_PEGAVEIC_ERRO:
            MessageBox(hwnd, "Erro ao recuperar veículo!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case PLACA_VALIDA:
            MessageBox(hwnd, "Placa válida!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case PLACA_INVALIDA:
            MessageBox(hwnd, "Placa inválida!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case CHASSI_VALIDO:
            MessageBox(hwnd, "Chassi válido!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case CHASSI_REPETIDO:
            MessageBox(hwnd, "Chassi repetido!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;
//---------- MANUTENCAO
        case MANUT_INSERIR_SUCESSO:
            MessageBox(hwnd, "Manutenção adicionada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case MANUT_INSERIR_ERRO:
            MessageBox(hwnd, "Erro ao adicionar manutenção!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_INSERIR_ERRO_DIA:
            MessageBox(hwnd, "Erro ao adicionar manutenção! Vc já cadastrou este veículo na manutenção hoje!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_EXCLUIR_SUCESSO:
            MessageBox(hwnd, "Manutenção excluída com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case MANUT_EXCLUIR_ERRO:
            MessageBox(hwnd, "Erro ao excluir manutenção!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_EXCLUIR_ERRO_MANUT_INEXISTENTE:
            MessageBox(hwnd, "Erro ao excluir manutenção! Manutenção inexistente!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case MANUT_BUSCA_SUCESSO:
            MessageBox(hwnd, "Manutenção encontrada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case DATA_ATUAL_ERRO:
            MessageBox(hwnd, "Erro ao recuperar a data atual!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case DATA_ATUAL_SUCESSO:
            MessageBox(hwnd, "Data atual recuperada com sucesso!", "", MB_OK | MB_ICONINFORMATION);
            break;

        case DATA_INVALIDA:
            MessageBox(hwnd, "Data inválida!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case DATA_INVALIDA_NAO_FORMATADA:
            MessageBox(hwnd, "Data inválida! Não foi inserida no formato correto!", "", MB_OK | MB_ICONERROR);
            qtErros++;
            break;

        case DATA_INVALIDA_NAO_NUMERO:
            MessageBox(hwnd, "Data inválida! Não são números!", "", MB_OK | MB_ICONERROR);
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
            MessageBox(hwnd, "Arquivo existente!", "", MB_OK | MB_ICONERROR);
            break;

        case ABRIR_ARQUIVO_SUCESSO:
            MessageBox(hwnd, "Arquivo criado/aberto com sucesso!", "", MB_OK | MB_ICONERROR);
            break;

    }

    return qtErros;
}
