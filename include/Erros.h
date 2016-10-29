/********************************************//**
 * @file Erros.h
 * @brief Contem o valor de todos os identificadores
 *        de erros utilizados pelo programa
 * @bug Nao contem bugs conhecidos!
 * @author Matheus Bispo
 ***********************************************/

#ifndef ERROS_H_SECURE
#define ERROS_H_SECURE

#include<windows.h>

//Proprietario
#define PROP_INSERIR_SUCESSO        90001
#define PROP_INSERIR_ERRO           90002
#define PROP_ALTERAR_SUCESSO        90003
#define PROP_ALTERAR_ERRO           90004
#define PROP_EXCLUIR_SUCESSO        90005
#define PROP_EXCLUIR_ERRO           90006
#define PROP_BUSCA_EXISTENTE        90007
#define PROP_BUSCA_INEXISTENTE      90008
#define PROP_BUSCA_SUCESSO          90009
#define PROP_PEGAPROP_SUCESSO       90010
#define PROP_PEGAPROP_ERRO          90011
#define PROP_EXCLUIR_ERRO_MANUT_EXISTENTE 90016

#define CPF_VALIDO                  90012
#define CPF_INVALIDO                90013
#define TEL_VALIDO                  90014
#define TEL_INVALIDO                90015
#define DDD_VALIDO                  90017
#define DDD_INVALIDO                90018

#define VEIC_INSERIR_SUCESSO        80001
#define VEIC_INSERIR_ERRO           80002
#define VEIC_BUSCA_SUCESSO          80003
#define VEIC_BUSCA_EXISTENTE        80040
#define VEIC_BUSCA_INEXISTENTE      80004
#define VEIC_ALTERAR_SUCESSO        80005
#define VEIC_ALTERAR_ERRO           80006
#define VEIC_EXCLUIR_ERRO_MANUT     80007
#define VEIC_EXCLUIR_SUCESSO        80008
#define VEIC_EXCLUIR_ERRO           80009
#define VEIC_PEGAVEIC_SUCESSO       80010
#define VEIC_PEGAVEIC_ERRO          80011

#define PLACA_VALIDA                80012
#define PLACA_INVALIDA              80013
#define CHASSI_VALIDO               80014
#define CHASSI_REPETIDO             80015

#define MANUT_INSERIR_ERRO_DIA      70001
#define MANUT_INSERIR_SUCESSO       70002
#define MANUT_INSERIR_ERRO          70003
#define MANUT_EXCLUIR_SUCESSO       70004
#define MANUT_EXCLUIR_ERRO          70005
#define MANUT_EXCLUIR_ERRO_MANUT_INEXISTENTE    70006
#define MANUT_BUSCA_SUCESSO         70007
#define MANUT_PEGAMANUT_ERRO        70016
#define MANUT_PEGAMANUT_SUCESSO     70017

#define DATA_ATUAL_SUCESSO          70008
#define DATA_ATUAL_ERRO             70009
#define DATA_INVALIDA_NAO_NUMERO    70010
#define DATA_INVALIDA_NAO_FORMATADA 70011
#define DATA_INVALIDA               70012
#define DATA_VALIDA                 70013
#define CONVERTE_DATA_SUCESSO       70014
#define CONVERTE_DATA_ERRO          70015

//Arquivos
#define ERRO_ABRIR_ARQUIVO          60001
#define ERRO_ARQUIVO_INEXISTENTE    60002
#define ARQUIVO_EXISTENTE           60003
#define ABRIR_ARQUIVO_SUCESSO       60004
#define ERRO_ARQUIVO_LER_PROP       60005
#define ERRO_ARQUIVO_GRAVAR_PROP    60006
#define ERRO_ARQUIVO_LER_VEIC       60007
#define ERRO_ARQUIVO_GRAVAR_VEIC    60008
#define ERRO_ARQUIVO_LER_MANUT      60009
#define ERRO_ARQUIVO_GRAVAR_MANUT   60010
#define ARQ_VEIC_ATUALIZADO         60011
#define ARQ_PROP_ATUALIZADO         60012
#define FECHA_ARQUIVO_SUCESSO		60013
#define FECHA_ARQUIVO_ERRO			60014
#define ERRO_REMOVER_ARQUIVO		60015
#define ERRO_RENOMEAR_ARQUIVO		60016

int win_trataErros(HWND hwnd, int erro);

#endif // ERROS_H_SECURE
