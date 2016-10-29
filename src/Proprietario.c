/********************************************//**
 ** @file Proprietario.c
 * @brief Contém todas as funções de operacoes que envolvem
 *        Proprietario.
 *
 *
 * @bug Nenhum problema conhecido!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Proprietario.h"
#include "../include/Erros.h"
#include "../include/Manutencao.h"

/********************************************//**
 * \brief Inclui um proprietario em um arquivo de dados de um proprietario
 *
 * \param prop - Uma estrutura do tipo Proprietario
 *
 * \return PROP_INSERIR_SUCESSO - Proprietario inserido com Sucesso
 * \return PROP_INSERIR_ERRO    - Erro ao inserir proprietario
 * \return BUSCA_PROP_EXISTENTE - Proprietario ja existente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir\criar arquivo
 ***********************************************/
int incluiProprietario(Proprietario prop)
{
	FILE *dbProp;
	int flag, pos;

    flag = buscaProprietario(prop.cpf, &pos);
    if(pos == -1 && flag == PROP_BUSCA_SUCESSO){
        dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "ab");
        if(dbProp != NULL){
            if(fwrite(&prop, sizeof(Proprietario), 1, dbProp) == 1){
                flag = PROP_INSERIR_SUCESSO;
            }else{
                flag = PROP_INSERIR_ERRO;
            }

            if(fechaArquivo(dbProp) == FECHA_ARQUIVO_ERRO){
                flag = FECHA_ARQUIVO_ERRO;
            }
        }else{
            flag = ERRO_ABRIR_ARQUIVO;
        }
    }else if(flag == PROP_BUSCA_SUCESSO){
        flag =  PROP_BUSCA_EXISTENTE;
    }

	return flag;
}


/********************************************//**
 * \brief Busca a posicao de uma estrutura do tipo
 *        Proprietario no arquivo de dados de proprietario
 *
 * \param cpf - o endereco de memoria de um string contendo o CPF do proprietario desejado
 * \param pos - Um ponteiro contendo o endereco de memoria
 *              de uma variavel do tipo inteiro, onde sera inserida
 *              a posicao encontrada, no caso de -1 o proprietario nao
 *              foi encontrado.
 *
 * \return PROP_BUSCA_SUCESSO - A busca foi realizada com sucesso
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir arquivo
 * \return ERRO_ARQUIVO_INEXISTENTE - Arquivo Inexistente
 ***********************************************/
int buscaProprietario(char *cpf, int *pos)
{
	FILE *dbProp;
	Proprietario pAux;
	int ind = -1, flag;

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_PROPRIETARIO)) return ERRO_ARQUIVO_INEXISTENTE;

	dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
    if(dbProp != NULL){
        while(fread(&pAux, sizeof(Proprietario), 1, dbProp) == 1){
            ind++;

            if(stricmp(pAux.cpf, cpf) == 0){
                *pos = ind;
                break;
            }
        }
        flag = PROP_BUSCA_SUCESSO;
        if(fechaArquivo(dbProp) == FECHA_ARQUIVO_ERRO){
                flag = FECHA_ARQUIVO_ERRO;
        }
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	return flag;

}

/********************************************//**
 * \brief Altera um proprietario em um arquivo de dados de um proprietario
 *
 * \param novoP - Uma estrutura do tipo Proprietario
 * \param cpf - o endereco de memoria de um string contendo o CPF do proprietario desejado
 *
 * \return PROP_ALTERAR_SUCESSO - Proprietario alterado com Sucesso
 * \return PROP_ALTERAR_ERRO    - Erro ao alterar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir arquivo
 ***********************************************/
int alteraProprietario(Proprietario novoP, char *cpf)
{
	int pos, flag;
	FILE *dbProp;

	flag = buscaProprietario(cpf, &pos);
	if(flag == PROP_BUSCA_SUCESSO){
        if(pos == -1){
            flag = PROP_BUSCA_INEXISTENTE;
        }else{
            dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "r+b");
            if(dbProp != NULL){
                if(fseek(dbProp, pos*sizeof(Proprietario), SEEK_SET) == 0){
                    if(fwrite(&novoP, sizeof(Proprietario), 1, dbProp) == 1){
                        flag = PROP_ALTERAR_SUCESSO;
                    }else{
                        flag = PROP_ALTERAR_ERRO;
                    }
                }

                if(fechaArquivo(dbProp) == FECHA_ARQUIVO_ERRO){
                    flag = FECHA_ARQUIVO_ERRO;
                }
            }else{
                flag = ERRO_ABRIR_ARQUIVO;
            }
        }
	}
	return flag;
}

/********************************************//**
 * \brief Atualiza o arquivo de proprietarios
 *
 * \return PROP_INSERIR_ERRO - Erro na reinsercao dos dados
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir o arquivo
 ***********************************************/
int atualizaArqProp(){
    FILE *arqEntrada, *arqSaida;
    Proprietario aux;
    int flag = ARQ_PROP_ATUALIZADO;

    arqEntrada = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
    arqSaida = fopen("XXXX.txt", "wb");

    if(arqEntrada != NULL){
    	if(arqSaida != NULL){
	        while(fread(&aux, sizeof(Proprietario), 1, arqEntrada) == 1){
	            if(aux.nome[0] != '\0'){
	                if(fwrite(&aux, sizeof(Proprietario), 1, arqSaida) != 1){
	                	flag = ERRO_ARQUIVO_GRAVAR_PROP;
	                	break;
					}
	            }
	        }
            if(fechaArquivo(arqSaida) == FECHA_ARQUIVO_ERRO){
                flag = FECHA_ARQUIVO_ERRO;
            }
		}else{
            flag = ERRO_ABRIR_ARQUIVO;
		}

        if(fechaArquivo(arqEntrada) == FECHA_ARQUIVO_ERRO){
                flag = FECHA_ARQUIVO_ERRO;
        }
    }else{
        flag =  ERRO_ABRIR_ARQUIVO;
    }

    if(remove(ARQUIVO_DADOS_PROPRIETARIO) != 0) flag = ERRO_REMOVER_ARQUIVO;
    if(rename("XXXX.txt", ARQUIVO_DADOS_PROPRIETARIO) != 0)flag = ERRO_RENOMEAR_ARQUIVO;

    return flag;
}

/********************************************//**
 * \brief Exclui um proprietario em um arquivo de dados de um proprietario
 *
 * \param cpf - o endereco de memoria de um string contendo o CPF do proprietario desejado
 *
 * \return PROP_EXCLUIR_SUCESSO - Proprietario alterado com Sucesso
 * \return PROP_EXCLUIR_ERRO    - Erro ao alterar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir arquivo
 ***********************************************/
int excluiProprietario(char *cpf)
{
	int pos = -1, flag = 0, erro;
	Proprietario pAux;
	FILE *dbProp;

	flag = buscaProprietario(cpf, &pos);
	if(flag == PROP_BUSCA_SUCESSO){
        if(pos == -1){
            flag = PROP_BUSCA_INEXISTENTE;
        }else{
            flag = buscaManutencaoCPF(cpf, &pos);
            if(pos == -1 && flag == MANUT_BUSCA_SUCESSO){
                dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "r+b");
                if(dbProp != NULL){
                    pAux.nome[0] = '\0';

                    flag = alteraProprietario(pAux, cpf);
                    if(flag == PROP_ALTERAR_SUCESSO){
                        flag = PROP_EXCLUIR_SUCESSO;
                    }else{
                        flag = PROP_EXCLUIR_ERRO;
                    }

                    if(fechaArquivo(dbProp) == FECHA_ARQUIVO_ERRO){
                        flag = FECHA_ARQUIVO_ERRO;
                    }
                }else{
                    flag = ERRO_ABRIR_ARQUIVO;
                }
            }else{
                flag = PROP_EXCLUIR_ERRO_MANUT_EXISTENTE;
            }
        }
	}

    erro = atualizaArqProp();
    if(erro != ARQ_PROP_ATUALIZADO) flag = erro;
	return flag;
}

/********************************************//**
 * \brief Busca um proprietario em um arquivo de dados de proprietarios
 *
 * \param pos - A posicao do proprietario desejado dentro do arquivo de dados
 * \param pAux - O endereco de memoria de uma estrutura do tipo Proprietario
 *
 * \return PROP_PEGAPROP_SUCESSO - Proprietario recuperado com Sucesso
 * \return PROP_PEGAPROP_ERRO    - Erro ao recuperar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir arquivo
 ***********************************************/
int pegaProprietario(char *cpf, Proprietario *pAux){
    int flag;
	FILE *dbProp;
	int pos;

	flag = buscaProprietario(cpf, &pos);
	if(flag == PROP_BUSCA_SUCESSO){
        if(pos == -1){
            flag = PROP_BUSCA_INEXISTENTE;
        }else{
            dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
            if(dbProp != NULL){
                fseek(dbProp, pos*sizeof(Proprietario), SEEK_SET);
                if(fread(pAux, sizeof(Proprietario), 1, dbProp) == 1){
                    flag = PROP_PEGAPROP_SUCESSO;
                }else{
                    flag = PROP_PEGAPROP_ERRO;
                }

                if(fechaArquivo(dbProp) == FECHA_ARQUIVO_ERRO){
                    flag = FECHA_ARQUIVO_ERRO;
                }
            }else{
                flag = ERRO_ABRIR_ARQUIVO;
            }
        }
	}
	return flag;
}

/********************************************//**
 * \brief Valida um CPF
 *
 * \param cpf - O endereco de memoria de um string contendo um cpf
 *
 * \return CPF_VALIDO - CPF valido
 * \return CPF_INVALIDO - CPF invalido
 ***********************************************/
int validaCPF(char *cpf)
{
	 // cpfs invalidos
       char *cpfInval[] = {"000.000.000-00","111.111.111-11",
                         "222.222.222-22",
                         "333.333.333-33",
                         "444.444.444-44",
                         "555.555.555-55",
                         "666.666.666-66",
                         "777.777.777-77",
                         "888.888.888-88",
                         "999.999.999-99"};

		int cont,retorno = CPF_VALIDO,aux2,dig[11],soma=0,digVeri[2], contAux = 0;

		if(strlen(cpf) != TAM_CPF-1)
			return CPF_INVALIDO;


         // verifica se cpf so contem nros iguais
	     for(cont=0;cont<10;cont++)
         {
               if(strcmp(cpfInval[cont],cpf)==0)
               {
                  retorno = CPF_INVALIDO;
                  break;
               }
         }

         if(retorno == CPF_INVALIDO)
            return retorno;

         // transforma os caracteres do cpf em numeros
         for(cont=0;cont<strlen(cpf);cont++)
         {
                if(cont != 3 && cont != 7 && cont != 11){
                    dig[contAux] = cpf[cont] - '0';
                    contAux++;
                }
         }

         // obtem o primeiro digito verificador
         aux2 = 10;
         for(cont=0;cont<9;cont++,aux2--)
         {
            soma += dig[cont] * aux2;
         }
         digVeri[0]=soma % 11;
         digVeri[0]= digVeri[0]<2 ? 0 : 11-digVeri[0];

         // obtem o segundo digito verificador
         soma=0;
         aux2=11;
         for(cont=0;cont<10;cont++,aux2--)
         {
               if(cont==9)
                  soma+= digVeri[0] * aux2;
               else
                  soma+= dig[cont] * aux2;
         }
         digVeri[1]=soma % 11;
         digVeri[1]= digVeri[1]<2 ? 0 : 11-digVeri[1];
         if(digVeri[0]!=dig[9] || digVeri[1]!=dig[10])
         {
               retorno = CPF_INVALIDO;
         }
         return retorno;
}

/********************************************//**
 * \brief Valida um telefone
 *
 * \param tel - O endereco de memoria de um string contendo um telefone
 *
 * \return TEL_VALIDO - CPF valido
 * \return TEL_INVALIDO - CPF invalido
 ***********************************************/
int validaTelefone(char *tel)
{
    int aux, tamTel = strlen(tel);

	if( tamTel != TAM_TEL-1 && tamTel != TAM_TEL - 2)return TEL_INVALIDO;

    aux = tel[0] - '0';
    if(aux < 2 || aux > 9){
        return TEL_INVALIDO;
    }

    if(aux > 1 && aux < 5){
        if(tamTel == TAM_TEL - 1){
            return TEL_INVALIDO;
        }
    }

	return TEL_VALIDO;
}

int validaDDD(char *ddd){
    int i, valido = DDD_VALIDO;
    i = ddd[0] - '0';
    if(i > 9 || i < 1){
        valido = DDD_INVALIDO;
    }

    i = ddd[1] - '0';
    if(i > 9 || i < 1){
        valido = DDD_INVALIDO;
    }

    return valido;
}
