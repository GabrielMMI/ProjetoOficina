#ifndef PROPRIETARIO_C_SECURE
#define PROPRIETARIO_C_SECURE

/********************************************//**
 ** @file Proprietario.c
 * @brief Implementa todas as funcoes de Proprietario.h
 *
 *
 * @bug Nenhum problema conhecido!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

#include "../include/Proprietario.h"


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
 * \return ALOC_ERRO - Erro ao alocar memoria
 * \return ERRO_ARQUIVO_INEXISTENTE - Arquivo Inexistente
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar arquivo
 ***********************************************/
int buscaProprietario(char *cpf, int *pos)
{
	FILE *dbProp;
	Proprietario *pAux=NULL;
	int ind = -1, flag;

	pAux=(Proprietario *)malloc(sizeof(Proprietario));
	if(pAux==NULL){
		return ALOC_ERRO;
	}else{
		flag=ALOC_SUCESSO;
	}

	*pos = ind;

	if(existeArquivo(ARQUIVO_DADOS_PROPRIETARIO) == ERRO_ARQUIVO_INEXISTENTE) return ERRO_ARQUIVO_INEXISTENTE;

	dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
    if(dbProp != NULL){
        while(fread(pAux, sizeof(Proprietario), 1, dbProp) == 1){
            ind++;

            if(stricmp(pAux->cpf, cpf) == 0){
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

    free(pAux);

	return flag;

}


/********************************************//**
 * \brief Inclui um proprietario em um arquivo de dados de um proprietario
 *
 * \param prop - Uma estrutura do tipo Proprietario
 *
 * \return PROP_INSERIR_SUCESSO - Proprietario inserido com Sucesso
 * \return PROP_INSERIR_ERRO    - Erro ao inserir proprietario
 * \return PROP_BUSCA_EXISTENTE - Proprietario ja existente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir ou criar arquivo
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
 * \brief Altera um proprietario em um arquivo de dados de um proprietario
 *
 * \param novoP - Uma estrutura do tipo Proprietario
 * \param cpf - o endereco de memoria de um string contendo o CPF do proprietario desejado
 *
 * \return PROP_ALTERAR_SUCESSO - Proprietario alterado com Sucesso
 * \return PROP_ALTERAR_ERRO    - Erro ao alterar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar o arquivo
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
 * \brief Exclui um proprietario em um arquivo de dados de um proprietario
 *
 * \param cpf - o endereco de memoria de um string contendo o CPF do proprietario desejado
 *
 * \return PROP_EXCLUIR_SUCESSO - Proprietario alterado com Sucesso
 * \return PROP_EXCLUIR_ERRO    - Erro ao alterar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir arquivo
 * \return PROP_EXCLUIR_ERRO_MANUT_EXISTENTE - Erro ao excluir um proprietario pois ele esta com uma manutencão cadastrada
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar arquivo
 * \return ALOC_ERRO - Erro ao alocar memoria
 ***********************************************/
int excluiProprietario(char *cpf)
{
	int pos = -1, flag = PROP_EXCLUIR_SUCESSO, erro;
	Proprietario *pAux = NULL;
	FILE *arq, *arqSemExcluido;

	pAux = (Proprietario *)malloc(sizeof(Proprietario));
	if(pAux==NULL){
		return ALOC_ERRO;
	}

	arq = fopen(ARQUIVO_DADOS_PROPRIETARIO,"rb");
	arqSemExcluido = fopen("database/dbPropAux.dat","wb");

	if(arq==NULL){
		if(arqSemExcluido != NULL){
			if(fechaArquivo(arqSemExcluido) == FECHA_ARQUIVO_ERRO){
	            flag = FECHA_ARQUIVO_ERRO;
	        }
    	}
        flag = ERRO_ABRIR_ARQUIVO;
		return flag;
	}

	if(arqSemExcluido==NULL){
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
		return flag;
	}

	flag = buscaProprietario(cpf, &pos);
	if(flag == PROP_BUSCA_SUCESSO && pos == -1){

		if(fechaArquivo(arqSemExcluido) == FECHA_ARQUIVO_ERRO) flag = FECHA_ARQUIVO_ERRO;
    	if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO) flag = FECHA_ARQUIVO_ERRO;

		return PROP_EXCLUIR_ERRO;
	}

	flag = buscaManutencaoCPF(cpf, &pos);

	if(pos == -1 && flag == MANUT_BUSCA_SUCESSO){
		while(!feof(arq)){
	        if(fread(pAux,sizeof(Proprietario),1,arq)==1){
	            if(stricmp(pAux->cpf,cpf) != 0){
	                if(fwrite(pAux,sizeof(Proprietario),1,arqSemExcluido) == 1){
					    flag = PROP_EXCLUIR_SUCESSO;
	                }else{
	                    flag = PROP_EXCLUIR_ERRO;
						break;
	                }
	            }else{
	            	flag = PROP_EXCLUIR_SUCESSO;
				}
	        }
	    }

	}else if(pos > -1){
		flag = PROP_EXCLUIR_ERRO_MANUT_EXISTENTE;
        if(fechaArquivo(arqSemExcluido) == FECHA_ARQUIVO_ERRO)flag = FECHA_ARQUIVO_ERRO;
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO)flag = FECHA_ARQUIVO_ERRO;
        return flag;
	}

	if(fechaArquivo(arqSemExcluido) == FECHA_ARQUIVO_ERRO)flag = FECHA_ARQUIVO_ERRO;
	if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO)flag = FECHA_ARQUIVO_ERRO;

	if(flag == PROP_EXCLUIR_SUCESSO){
	    if(remove(ARQUIVO_DADOS_PROPRIETARIO)==0){
	    	if(rename("database/dbPropAux.dat", ARQUIVO_DADOS_PROPRIETARIO)==0){
	    		flag = PROP_EXCLUIR_SUCESSO;
			}else{
				flag = PROP_EXCLUIR_ERRO;
			}
		}else{
			flag = PROP_EXCLUIR_ERRO;
		}
	}else{
		if(remove("database/dbPropAux.dat")==0){
			flag = PROP_EXCLUIR_ERRO;
		}
	}

    free(pAux);
	return flag;
}

/********************************************//**
 * \brief Busca um proprietario em um arquivo de dados de proprietarios
 *
 * \param cpf - O endereco de memoria de um string contendo o CPF do proprietario desejado
 * \param proprietario - O endereco de memoria de uma estrutura do tipo Proprietario
 *
 * \return PROP_PEGAPROP_SUCESSO - Proprietario recuperado com Sucesso
 * \return PROP_PEGAPROP_ERRO    - Erro ao recuperar proprietario
 * \return BUSCA_PROP_INEXISTENTE - Proprietario inexistente
 * \return ERRO_ABRIR_ARQUIVO   - Erro ao abrir arquivo
 ***********************************************/
int pegaProprietario(char *cpf, Proprietario *proprietario){
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
                if(fread(proprietario, sizeof(Proprietario), 1, dbProp) == 1){
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
 * \return TEL_VALIDO - Telefone valido
 * \return TEL_INVALIDO - Telefone invalido
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

/********************************************//**
 * \brief Valida um DDD
 *
 * \param ddd - O endereco de memoria de um string contendo um DDD
 *
 * \return DDD_VALIDO - DDD valido
 * \return DDD_INVALIDO - DDD invalido
 ***********************************************/
int validaDDD(char *ddd)
{
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

/********************************************//**
 * \brief Obtem a quantidade de proprietarios no arquivo de proprietarios
 *
 * \return A quantidade de proprietarios
 ***********************************************/
int obtemQuantPropArquivo()
{
	FILE *arqProp;
	int qtProp = -1;

	arqProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
	if(arqProp != NULL){
		if(fseek(arqProp, 0, SEEK_END) == 0){
			qtProp = ftell(arqProp)/sizeof(Proprietario);
		}
		fechaArquivo(arqProp);
	}
	return qtProp;
}

/********************************************//**
 * \brief Carrega os proprietario de um arquivo de dados de proprietarios
 *
 *
 * \return Endereco de um ponteiro do tipo Proprietario
 ***********************************************/
Proprietario *carregaProprietarios()
{
	FILE *dbProp;
	int qtProp;
	Proprietario *proprietario = NULL;

	qtProp = obtemQuantPropArquivo();

	if(qtProp == -1 || qtProp == 0) return proprietario;

	proprietario = (Proprietario *)malloc(qtProp * sizeof(Proprietario));
	if(proprietario != NULL){
		dbProp = fopen(ARQUIVO_DADOS_PROPRIETARIO, "rb");
		if(dbProp != NULL){
			if(fread(proprietario, sizeof(Proprietario), qtProp, dbProp) != qtProp){
				free(proprietario);
				proprietario = NULL;
			}
			fechaArquivo(dbProp);
		}
	}

	return proprietario;
}

#endif
