/********************************************//**
 * @file Manutencao.c
 * @brief Implementa todas as funções de Manutencao.h
 * @bug Nao contem bugs conhecidos!
 *
 *@author Matheus Bispo
 *@author Gabriel Messias
 ***********************************************/

#include "../include/Manutencao.h"

/********************************************//**
 * \brief Busca uma manutenção no arquivo de manutenções através de uma placa
 *
 * \param placa - String contendo a placa cadastrada na manutenção a ser excluída
 * \param pos 	- Um ponteiro para inteiro onde será colocada a posição onde a manutenção foi encontrada
 *
 * \return ALOC_ERRO 				- Erro por falta de memória
 * \return MANUT_BUSCA_SUCESSO		- Busca de Manutenção executada com sucesso
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arquivo
  ***********************************************/
int buscaManutencaoPlaca(char *placa, int *pos)
{
    FILE *dbManut;
	Manutencao *mAux = NULL;
	int ind = -1, flag;

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_MANUTENCAO)) return ERRO_ARQUIVO_INEXISTENTE;

	mAux=(Manutencao*)malloc(sizeof(Manutencao));
	if(mAux==NULL){
		return ALOC_ERRO;
	}

	dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(dbManut != NULL){
        while(fread(mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux->placa, placa) == 0){
            	flag = MANUT_BUSCA_SUCESSO;
                *pos = ind;
                break;
            }
        }
        flag = MANUT_BUSCA_SUCESSO;

        if(fechaArquivo(dbManut) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	free(mAux);
	return flag;

}



/********************************************//**
 * \brief Busca uma manutenção no arquivo de manutenções através de um cpf
 *
 * \param cpf 	- String contendo o cpf cadastrado na manutenção a ser excluída
 * \param pos 	- Um ponteiro para inteiro onde será colocada a posição onde a manutenção foi encontrada
 *
 * \return ALOC_ERRO 				- Erro por falta de memória
 * \return MANUT_BUSCA_SUCESSO		- Busca de Manutenção executada com sucesso
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arquivo
  ***********************************************/
int buscaManutencaoCPF(char *cpf, int *pos)
{
    FILE *dbManut;
	Manutencao *mAux;
	int ind = -1, flag;

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_MANUTENCAO)) return ERRO_ARQUIVO_INEXISTENTE;

	mAux=(Manutencao*)malloc(sizeof(Manutencao));
	if(mAux==NULL){
		return ALOC_ERRO;
	}

	dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(dbManut != NULL){
        while(fread(mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux->cpf, cpf) == 0){
            	flag = MANUT_BUSCA_SUCESSO;
                *pos = ind;
                break;
            }
        }
        flag = MANUT_BUSCA_SUCESSO;

        if(fechaArquivo(dbManut) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	free(mAux);
	return flag;
}

/********************************************//**
 * \brief Compara duas structs do tipo Data
 *
 * \param data1 - Struct do tipo data
 * \param data2 - Struct do tipo data
 *
 * \return 0 	- No caso de igualdade
 * \return 1 	- Se Data1 maior que Data2
 * \return -1 	- Se Data2 maior que Data1
  ***********************************************/
int comparaData(Data data1, Data data2)
{
    int flag;
    if(data1.dia == data2.dia && data1.mes == data2.mes && data1.ano == data2.ano){
        flag = 0;
    }else if(data1.ano > data2.ano){
        flag = 1;
    }else if(data1.mes > data2.mes && data1.ano == data2.ano){
        flag = 1;
    }else if(data1.dia > data2.dia && data1.mes == data2.mes && data1.ano == data2.ano){
        flag = 1;
    }else{
        flag = -1;
    }

    return flag;
}

/********************************************//**
 * \brief Busca uma manutenção no arquivo de manutenções através da Data e de uma placa
 *
 * \param placa - String contendo a placa cadastrada na manutenção a ser excluída
 * \param Data 	- Uma struct do tipo Data
 * \param pos 	- Um ponteiro para inteiro onde será colocada a posição onde a manutenção foi encontrada
 *
 * \return ALOC_ERRO 				- Erro por falta de memória
 * \return MANUT_BUSCA_SUCESSO		- Busca de Manutenção executada com sucesso
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arquivo
  ***********************************************/
int buscaManutencaoPlacDat(char *placa,Data data, int *pos)
{
	FILE *dbManut;
	Manutencao *mAux=NULL;
	int ind = -1, flag = MANUT_BUSCA_SUCESSO;

	mAux=(Manutencao*)malloc(sizeof(Manutencao));
	if(mAux==NULL){
		return ALOC_ERRO;
	}

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_MANUTENCAO)) return ERRO_ARQUIVO_INEXISTENTE;

	dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(dbManut != NULL){
        while(fread(mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux->placa, placa) == 0 && comparaData(mAux->data, data) == 0){
            	flag = MANUT_BUSCA_SUCESSO;
                *pos = ind;
                break;
            }
        }
        flag = MANUT_BUSCA_SUCESSO;
        if(fechaArquivo(dbManut) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	free(mAux);
	return flag;

}


/********************************************//**
 * \brief Recupera uma manutenção do arquivo de manutenções através da Data e de uma placa
 *
 * \param placa - String contendo a placa cadastrada na manutenção a ser excluída
 * \param Data 	- Uma struct do tipo Data
 * \param manut - Um ponteiro do tipo Manutenção
 *
 * \return MANUT_PEGAMANUT_ERRO 	- Erro ao recuperar manutenção
 * \return MANUT_PEGAMANUT_SUCESSO	- Manutenção recuperada com sucesso
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arquivo
  ***********************************************/
int pegaManutencaoPlacDat(char *placa, Data data, Manutencao *manut)
{
    int flag;
	FILE *arqManut;
	int posicaoManut;

    flag = buscaManutencaoPlacDat(placa, data, &posicaoManut);
	if(flag == MANUT_BUSCA_SUCESSO){
        if(posicaoManut == -1){
            flag = MANUT_PEGAMANUT_ERRO;
        }else{
            arqManut=fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
            if(arqManut!=NULL){
                if(fseek(arqManut,posicaoManut*sizeof(Manutencao),SEEK_SET)==0){
                    if(fread(manut,sizeof(Manutencao),1,arqManut)==1){
                        flag = MANUT_PEGAMANUT_SUCESSO;
                    }
                }
                if(fechaArquivo(arqManut) == FECHA_ARQUIVO_ERRO){
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
 * \brief Busca uma manutenção no arquivo de manutenções através da Data, de um cpf e de uma placa
 *
 * \param placa - String contendo a placa cadastrada na manutenção a ser excluída
 * \param cpf 	- String contendo o cpf cadastrado na manutenção a ser excluída
 * \param data 	- Uma struct do tipo Data
 * \param pos 	- Um ponteiro para inteiro onde será colocada a posição onde a manutenção foi encontrada
 *
 * \return ALOC_ERRO 				- Erro por falta de memória
 * \return MANUT_BUSCA_SUCESSO		- Busca de Manutenção executada com sucesso
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arquivo
  ***********************************************/
int buscaManutencao(char *placa, char *cpf, Data data, int *pos)
{
	FILE *dbManut;
	Manutencao *mAux = NULL;
	int ind = -1, flag = MANUT_BUSCA_SUCESSO;;

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_MANUTENCAO)) return ERRO_ARQUIVO_INEXISTENTE;

	mAux=(Manutencao*)malloc(sizeof(Manutencao));
	if(mAux==NULL){
		return ALOC_ERRO;
	}

	dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(dbManut != NULL){
        while(fread(mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux->cpf, cpf) == 0 && stricmp(mAux->placa, placa) == 0 && comparaData(mAux->data, data) == 0){
            	flag = MANUT_BUSCA_SUCESSO;
                *pos = ind;
                break;
            }
        }
        flag = MANUT_BUSCA_SUCESSO;
        if(fechaArquivo(dbManut) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	free(mAux);
	return flag;

}


/********************************************//**
 * \brief Inclui uma manutenção no arquivo de manutenções
 *
 * \param manutencao - Struct do tipo Manutencao
 *
 * \return MANUT_INSERIR_ERRO_DIA 	- Erro ao cadastrar manutenção, já houve uma manutenção igual no mesmo dia
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arqui
 * \return ALOC_ERRO 				- Erro por falta de memória
 * \return PROP_BUSCA_INEXISTENTE 	- Proprietario inexistente
 * \return VEIC_BUSCA_INEXISTENTE   - Veiculo inexistente
 * \return MANUT_INSERIR_SUCESSO    - Manutenção cadastrada com Sucesso
 * \return MANUT_INSERIR_ERRO		- Erro ao cadastrar Manutenção
 ***********************************************/
int incluiManutencao(Manutencao manutencao)
{
	FILE *arq;
	Manutencao *mAux = NULL;
	int flag = 0, posP, posV;

	buscaProprietario(manutencao.cpf, &posP);
	buscaVeiculo(manutencao.placa, &posV);

	mAux=(Manutencao*)malloc(sizeof(Manutencao));
	if(mAux==NULL){
		return ALOC_ERRO;
	}

	arq=fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(mAux,sizeof(Manutencao),1,arq)==1){
				if(stricmp(manutencao.placa,mAux->placa)==0){
					if(comparaData(manutencao.data, mAux->data) == 0){
						flag = MANUT_INSERIR_ERRO_DIA;
						break;
					}
				}
			}else{
				break;
			}
		}
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
	}else{
        flag = ERRO_ABRIR_ARQUIVO;
	}

	free(mAux);

    if(posP == -1)  flag = PROP_BUSCA_INEXISTENTE;

    if(posV == -1)  flag = VEIC_BUSCA_INEXISTENTE;

	if(flag == 0){
		arq=fopen(ARQUIVO_DADOS_MANUTENCAO,"ab");

		if(arq!=NULL){
				if(fwrite(&manutencao,sizeof(Manutencao),1,arq)==1){
                    flag = MANUT_INSERIR_SUCESSO;
                }else{
                    flag = MANUT_INSERIR_ERRO;
                }
            if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
                flag = FECHA_ARQUIVO_ERRO;
            }
		}else{
            flag = ERRO_ABRIR_ARQUIVO;
		}
    }

	return flag;
}

/********************************************//**
 * \brief Ler e excluir uma manutenção no arquivo de manutenção
 *
 * \param placa - String contendo a placa cadastrada na manutenção a ser excluída
 * \param cpf	- String contendo o cpf cadastrado na manutenção a ser excluída
 * \param data 	- Uma struct do tipo Data
 *
 * \return MANUT_INSERIR_ERRO_DIA 	- Erro ao cadastrar manutenção, já houve uma manutenção igual no mesmo dia
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arqui
 * \return ALOC_ERRO 				- Erro por falta de memória
 * \return MANUT_EXCLUIR_SUCESSO    - Manutenção excluída com Sucesso
 * \return MANUT_EXCLUIR_ERRO		- Erro ao excluir Manutenção
 ***********************************************/
int excluiManutencao(char *placa,char *cpf, Data data)
{
	FILE *arq,*arqSemExcluido;
	Manutencao *manutencao = NULL;
	int flag;

	arq = fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	arqSemExcluido = fopen("database/dbManutAux.dat","wb");
	if(arq==NULL){
        flag = ERRO_ABRIR_ARQUIVO;
		return flag;
	}
	if(arqSemExcluido==NULL){
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
		return flag;
	}

	manutencao=(Manutencao*)malloc(sizeof(Manutencao));
	if(manutencao==NULL){
		return ALOC_ERRO;
	}

	while(!feof(arq)){
        if(fread(manutencao,sizeof(Manutencao),1,arq)==1){
            if(stricmp(manutencao->cpf,cpf) != 0 || stricmp(manutencao->placa,placa) != 0 || comparaData(data, manutencao->data) != 0){
                if(fwrite(manutencao,sizeof(Manutencao),1,arqSemExcluido)==1){
                    flag = MANUT_EXCLUIR_SUCESSO;
                }else{
                    flag = MANUT_EXCLUIR_ERRO;
                    free(manutencao);
                    return flag;
                }
            }
        }
    }

    if(fechaArquivo(arqSemExcluido) == FECHA_ARQUIVO_ERRO){
        flag = FECHA_ARQUIVO_ERRO;
    }

    if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
        flag = FECHA_ARQUIVO_ERRO;
    }

    if(remove(ARQUIVO_DADOS_MANUTENCAO)==0){
    	if(rename("database/dbManutAux.dat", ARQUIVO_DADOS_MANUTENCAO)==0){
    		flag = MANUT_EXCLUIR_SUCESSO;
		}else{
			flag = MANUT_EXCLUIR_ERRO;
		}
	}else{
		flag = MANUT_EXCLUIR_ERRO;
	}

	free(manutencao);
	return flag;

}

/********************************************//**
 * \brief Recupera uma manutenção do arquivo de manutenções
 *
 * \param placa - String contendo a placa cadastrada na manutenção a ser excluída
 * \param cpf 	- String contendo o cpf cadastrado na manutenção a ser excluída
 * \param data 	- Uma struct do tipo Data
 * \param manut - Um ponteiro do tipo Manutenção
 *
 * \return MANUT_PEGAMANUT_ERRO 	- Erro ao recuperar manutenção
 * \return MANUT_PEGAMANUT_SUCESSO	- Manutenção recuperada com sucesso
 * \return FECHA_ARQUIVO_ERRO 		- Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO 		- Erro ao abrir o arquivo
  ***********************************************/
int pegaManutencao(char *placa, char *cpf, Data data, Manutencao *manut)
{
    int flag;
	FILE *arqManut;
	int posicaoManut;

    flag = buscaManutencao(placa, cpf, data, &posicaoManut);
	if(flag == MANUT_BUSCA_SUCESSO){
        if(posicaoManut == -1){
            flag = MANUT_PEGAMANUT_ERRO;
        }else{
            arqManut=fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
            if(arqManut!=NULL){
                if(fseek(arqManut,posicaoManut*sizeof(Manutencao),SEEK_SET)==0){
                    if(fread(manut,sizeof(Manutencao),1,arqManut)==1){
                        flag = MANUT_PEGAMANUT_SUCESSO;
                    }
                }
                if(fechaArquivo(arqManut) == FECHA_ARQUIVO_ERRO){
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
 * \brief Carrega na memória todos as manutenções de um determinado CPF
 *
 * \param cpf 			- String contendo o cpf cadastrado na manutenção a ser excluída
 * \param qtManutCPF	- Um ponteiro para inteiro onde será colocada a quantidade de elementos carregados
 *
 * \return Manutencao *	- Um ponteiro do tipo Manutenção contendo os elementos encontrados, caso nenhum seja encontrado retorna NULL
  ***********************************************/
Manutencao * carregaManutencoesCPF(char *cpf, int *qtManutCPF)
{
    int flag, cont, aux;
	FILE *arqManut;
	Manutencao mAux, *manutencao = NULL;
	int posicaoManut;
	cont = 0;

    arqManut=fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(arqManut!=NULL){
    	while(!feof(arqManut)){
	        if(fread(&mAux,sizeof(Manutencao),1,arqManut)==1){
	        	if(strcmp(mAux.cpf, cpf) == 0){
	        		manutencao = (Manutencao *)realloc(manutencao, (cont+1)*sizeof(Manutencao));
		            manutencao[cont] = mAux;
		            cont++;

	        	}
	        }
		}

		*qtManutCPF = cont;

        if(fechaArquivo(arqManut) == FECHA_ARQUIVO_ERRO){
            free(manutencao);
            manutencao = NULL;
        }

    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }


	return manutencao;
}


/********************************************//**
 * \brief Converte um struct do tipo SYSTEMTIME em
 *        um time_t
 * \param st SYSTEMTIME
 *
 * \return time_t
 *
 ***********************************************/
Data convertTime(SYSTEMTIME st)
{
    Data data;

	data.dia = (int)st.wDay;
	data.mes = (int)st.wMonth;
	data.ano = (int)st.wYear;

	return data;
}


/********************************************//**
 * \brief Pega a data atual
 *
 * \param data - Um ponteiro do tipo Data, que irá receber a data atual
 *
 * \return void
  ***********************************************/
void obtemDataAtual(Data *data)
{
    SYSTEMTIME lt;

    GetLocalTime(&lt);

    *data = convertTime(lt);
}

/********************************************//**
 * \brief Obtem a quantidade de manutenções existentes em um arquivo
 *
 *
 * \return n 	- número de manutenções existentes no arquivo
 * \return -1 	- Caso não seja verificar a quantidade de manutenções
 ***********************************************/
int obtemQuantManutArquivo()
{
	FILE *arqManut;
	int qtManut = -1;

	arqManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
	if(arqManut != NULL){
		if(fseek(arqManut, 0, SEEK_END) == 0){
			qtManut = ftell(arqManut)/sizeof(Manutencao);
		}
		fechaArquivo(arqManut);
	}
	return qtManut;
}


/********************************************//**
 * \brief Carrega todas as manutenções de um arquivo de manutenções
 *
 *
 * \return Manutencao - Um ponteiro para um array de manutenções alocado dinamicamente na memória
 * \return NULL 	  - Caso não seja possível carregar as manutenções
 ***********************************************/
Manutencao *carregaManutencoes()
{
	FILE *dbManut;
	int qtManut;
	Manutencao *manutencoes = NULL;

	qtManut = obtemQuantManutArquivo();
	manutencoes = (Manutencao *)malloc(qtManut * sizeof(Manutencao));
	if(manutencoes != NULL){
		dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
		if(dbManut != NULL){
			if(fread(manutencoes, sizeof(Manutencao), qtManut, dbManut) != qtManut){
				free(manutencoes);
				manutencoes = NULL;
			}
			fechaArquivo(dbManut);
		}
	}

	return manutencoes;
}

/********************************************//**
 * \brief Converte um struct do tipo Data em uma string
 *
 * \param stringData	- A string que receberá a conversão
 * \param data			- Uma struct do tipo Data que será convertida
 *
 * \return flag > 0	- Conversão executada com sucesso
 * \return flag < 0 - Caso não seja executada a conversão de modo devido
 ***********************************************/
int converteDataString(char* stringData, Data data)
{
	int flag;

	flag = sprintf(stringData, "%d/%d/%d", data.dia, data.mes, data.ano);

	return flag;
}

/********************************************//**
 * \brief Converte uma string em uma struct do tipo Data
 *
 * \param stringData	- A string que receberá a conversão
 * \param data			- Uma struct do tipo Data que será convertida
 *
 * \return flag > 0	- Conversão executada com sucesso
 * \return flag < 0 - Caso não seja executada a conversão de modo devido
 ***********************************************/
int converteStringData(char *stringData, Data *data)
{
	int flag = 0;
	sscanf(stringData,"%d/%d/%d",&(data->dia),&(data->mes),&(data->ano));

	return flag;
}
