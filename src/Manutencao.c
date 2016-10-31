#include "../include/Manutencao.h"


/********************************************//**
 * \brief Inclui uma manutenção no arquivo de manutenções
 *
 * \param manutencao - Struct do tipo Manutencao
 *
 * \return MANUT_INSERIR_ERRO_DIA
 * \return FECHA_ARQUIVO_ERRO
 * \return ERRO_ABRIR_ARQUIVO
 * \return 
 * \return 
 * \return 
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

//Objetivo: Ler e excluir uma manutenção no arquivo de manutenção
//Parametros: ---------
//Retorno: ----------
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

int pegaManutencao(char *placa, char *cpf, Data data, Manutencao *manut){
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

int buscaManutencaoPlacDat(char *placa,Data data, int *pos)
{
	FILE *dbManut;
	Manutencao *mAux=NULL;
	int ind = -1, flag;

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

int buscaManutencao(char *placa, char *cpf, Data data, int *pos)
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
            if(stricmp(mAux->cpf, cpf) == 0 && stricmp(mAux->placa, placa) == 0 && comparaData(mAux->data, data) == 0){
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

int buscaManutencaoCPF(char *cpf, int *pos){
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
        while(fread(&mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux->cpf, cpf) == 0){
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

int buscaManutencaoPlaca(char *placa, int *pos){
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
        while(fread(&mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux->placa, placa) == 0){
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

int carregaManutencoesCPF(char *cpf, int *qtManutCPF, Manutencao *manutencao){
    int flag, cont;
	FILE *arqManut;
	Manutencao *manuts = NULL, *mAux = NULL;
	int posicaoManut;
	cont = 0;

	mAux = (Manutencao *)malloc(sizeof(Manutencao));
	if(mAux == NULL){
		return ALOC_ERRO;
	}

	manuts = (Manutencao *)malloc(sizeof(Manutencao));
	if(manuts != NULL){
	    arqManut=fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
	    if(arqManut!=NULL){
	    	while(!feof(arqManut)){
		        if(fread(mAux,sizeof(Manutencao),1,arqManut)==1){
		        	if(strcmp(mAux->cpf, cpf) == 0){
			            manuts[cont] = *mAux;
			            flag = MANUT_PEGAMANUT_SUCESSO;
			            cont++;
			            manuts = (Manutencao *)realloc(manuts, (cont+1)*sizeof(Manutencao));
		        	}
		        }
			}
			
			*qtManutCPF = cont;
			manutencao = manuts;
			
	        if(fechaArquivo(arqManut) == FECHA_ARQUIVO_ERRO){
	            flag = FECHA_ARQUIVO_ERRO;
	        }
	        
	    }else{
	        flag = ERRO_ABRIR_ARQUIVO;
	    }
	}else{
		flag = ALOC_ERRO;
	}
	
	free(mAux);
	return flag;
}

//Objetivo: Pegar Data atual
//Parametros: ---------
//Retorno: ----------
void obtemDataAtual(Data *data)
{
    SYSTEMTIME lt;

    GetLocalTime(&lt);

    *data = convertTime(lt);
}

int comparaData(Data data1, Data data2){
    int flag;
    if(data1.dia == data2.dia && data1.mes == data2.mes && data1.ano == data2.ano){
        flag = 0;
    }else if(data1.ano > data2.ano){
        flag = 1;
    }else if(data1.mes > data2.mes){
        flag = 1;
    }else if(data1.dia > data2.dia){
        flag = 1;
    }else{
        flag = -1;
    }

    return flag;
}

/********************************************//**
 * \brief Converte um struct do tipo SYSTEMTIME em
 *        um time_t
 * \param st SYSTEMTIME
 * \return time_t
 *
 ***********************************************/
Data convertTime(SYSTEMTIME st){
    Data data;

	data.dia = (int)st.wDay;
	data.mes = (int)st.wMonth;
	data.ano = (int)st.wYear;

	return data;
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

int converteDataString(char* stringData, Data data)
{
	int flag = 0;
	sprintf(stringData, "%d/%d/%d", data.dia, data.mes, data.ano);

	return flag;
}

int converteStringData(char *stringData, Data *data)
{
	int flag = 0;
	sscanf(stringData,"%d/%d/%d",&data->dia,&data->mes,&data->ano);

	return flag;
}
