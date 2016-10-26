/********************************************//**
 ** @file Proprietario.c
 * @brief Cont�m todas as fun��es de opera��es que envolvem
 *        Proprietario.
 *
 *
 * @bug Nenhum problema conhecido!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Proprietario.h"
#include "../include/Erros.h"

/********************************************//**
 * \brief Inclui um propriet�rio em um arquivo de dados de um proprietario
 *
 * \param prop - Uma estrutura do tipo Proprietario
 *
 * \return PROP_INSERIR_SUCESSO - Proprietario inserido com Sucesso
 * \return PROP_INSERIR_ERRO    - Erro ao inserir proprietario
 * \return BUSCA_PROP_EXISTENTE - Proprietario j� existente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir\criar arquivo
 ***********************************************/
int incluiProprietario(Proprietario prop)
{
	FILE *dbProp;
	int flag, pos;

    dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "ab");
    if(dbProp != NULL){
        flag = buscaProprietario(prop.cpf, &pos);
        if(pos == -1 && flag == PROP_BUSCA_SUCESSO){
            if(fwrite(&prop, sizeof(Proprietario), 1, dbProp) == 1){
                flag = PROP_INSERIR_SUCESSO;
            }else{
                flag = PROP_INSERIR_ERRO;
            }
        }else if(flag == PROP_BUSCA_SUCESSO){
            flag =  PROP_BUSCA_EXISTENTE;
        }
        flag = fechaArquivo(dbProp);
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	return flag;
}


/********************************************//**
 * \brief Busca a posi��o de uma estrutura do tipo
 *        Propriet�rio no arquivo de dados de proprietario
 *
 * \param cpf - o endere�o de memoria de um string contendo o CPF do propriet�rio desejado
 * \param pos - Um ponteiro contendo o endere�o de mem�ria
 *              de uma variavel do tipo inteiro, onde sera inserida
 *              a posicao encontrada, no caso de -1 o proprietario n�o
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
            if(strcmp(pAux.cpf, cpf) == 0){
                *pos = ind;
                break;
            }
        }
        flag = PROP_BUSCA_SUCESSO;
        flag = fechaArquivo(dbProp);
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	return flag;

}

/********************************************//**
 * \brief Altera um propriet�rio em um arquivo de dados de um proprietario
 *
 * \param novoP - Uma estrutura do tipo Proprietario
 * \param cpf - o endere�o de memoria de um string contendo o CPF do propriet�rio desejado
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

                flag = fechaArquivo(dbProp);
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
 * \return PROP_INSERIR_ERRO - Erro na reinser��o dos dados
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
	                	breaK;
					}
	            }
	        }
        	flag = fechaArquivo(arqSaida);
		}else{
			flag = return ERRO_ABRIR_ARQUIVO;
		}
		
    	fclose(arqEntrada);       
    }else{
        flag =  ERRO_ABRIR_ARQUIVO;
    }

    if(remove(ARQUIVO_DADOS_PROPRIETARIO) == EOF) flag = ERRO_REMOVER_ARQUIVO;
    if(rename("XXXX.txt", ARQUIVO_DADOS_PROPRIETARIO))flag = ERRO_RENOMEAR_ARQUIVO;

    return flag;
}

/********************************************//**
 * \brief Exclui um propriet�rio em um arquivo de dados de um proprietario
 *
 * \param cpf - o endere�o de memoria de um string contendo o CPF do propriet�rio desejado
 *
 * \return PROP_EXCLUIR_SUCESSO - Proprietario alterado com Sucesso
 * \return PROP_EXCLUIR_ERRO    - Erro ao alterar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir arquivo
 ***********************************************/
int excluiProprietario(char *cpf)
{
	int pos, flag;
	Proprietario pAux;
	FILE *dbProp;

	flag = buscaProprietario(cpf, &pos);
	if(flag == PROP_BUSCA_SUCESSO){
        if(pos == -1){
            flag = PROP_BUSCA_INEXISTENTE;
        }else{
            dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "r+b");
            if(dbProp != NULL){
                pAux.nome[0] = '\0';

                flag = alteraProprietario(pAux, cpf);
                if(flag == PROP_ALTERAR_SUCESSO){
                    flag = PROP_EXCLUIR_SUCESSO;
                }else{
                    flag = PROP_EXCLUIR_ERRO;
                }

                flag = fechaArquivo(dbProp);
            }else{
                flag = ERRO_ABRIR_ARQUIVO;
            }
        }
	}

	atualizaArqProp();
	return flag;
}

/********************************************//**
 * \brief Busca um propriet�rio em um arquivo de dados de proprietarios
 *
 * \param pos - A posi��o do proprietario desejado dentro do arquivo de dados
 * \param pAux - O endere�o de mem�ria de uma estrutura do tipo Proprietario
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

                flag = fechaArquivo(dbProp);
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
 * \param cpf - O endere�o de mem�ria de um string contendo um cpf
 *
 * \return CPF_VALIDO - CPF v�lido
 * \return CPF_INVALIDO - CPF inv�lido
 ***********************************************/
int validaCPF(char *cpf)
{
	 // cpfs inv�lidos
       char *cpfInval[] = {"00000000000","11111111111",
                         "22222222222",
                         "33333333333",
                         "44444444444",
                         "55555555555",
                         "66666666666",
                         "77777777777",
                         "88888888888",
                         "99999999999"};

		int cont,retorno = CPF_VALIDO,aux2,dig[11],soma=0,digVeri[2];

		if(strlen(cpf) != 11)
			return CPF_INVALIDO;


         // verifica se cpf so contem nros iguais
	     for(cont=0;cont<9;cont++)
         {
               if(strcmp(cpfInval[cont],cpf)==0)
               {
                  retorno = CPF_INVALIDO;
                  break;
               }
         }

         if(retorno == CPF_INVALIDO)
            return retorno;

         // transforma os caracteres do cpf em n�meros
         for(cont=0;cont<strlen(cpf);cont++)
         {
                dig[cont] = cpf[cont] - '0';
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
 * \param tel - O endere�o de mem�ria de um string contendo um telefone
 *
 * \return TEL_VALIDO - CPF v�lido
 * \return TEL_INVALIDO - CPF inv�lido
 ***********************************************/
int validaTelefone(char *tel)
{
	if(strlen(tel) != 10)
		return TEL_INVALIDO;

	return TEL_VALIDO;
}