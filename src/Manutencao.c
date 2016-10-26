#include "../include/Manutencao.h"

//Objetivo: Ler e incluir uma manutenção no arquivo de manutenção
//Parametros: ---------
//Retorno: ----------
int incluiManutencao(Manutencao m)
{
	FILE *arq;
	Manutencao mAux;
	int flag = 0, posP, posV;

	buscaProprietario(m.cpf, &posP);
	buscaVeiculo(m.placa, &posV);

	arq=fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(&mAux,sizeof(Manutencao),1,arq)==1){
				if(stricmp(m.placa,mAux.placa)==0){
					if(comparaData(m.data, mAux.data) == 0){
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

    if(posP == -1)  flag = PROP_BUSCA_INEXISTENTE;

    if(posV == -1)  flag = VEIC_BUSCA_INEXISTENTE;

	if(flag == 0){
		arq=fopen(ARQUIVO_DADOS_MANUTENCAO,"ab");

		if(arq!=NULL){
				if(fwrite(&m,sizeof(Manutencao),1,arq)==1){
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
int excluiManutencao(char *placa)
{
	FILE *arq,*arqSemExcluido;
	Manutencao m;
	int flag;

	arq = fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	arqSemExcluido = fopen("database/dbManutAux.dat","wb");
	if(arq==NULL){
		printf(" Erro ao abrir o arquivo de manutencao.\n");
        flag = ERRO_ABRIR_ARQUIVO;
		return flag;
	}
	if(arqSemExcluido==NULL){
		printf(" Erro ao abrir o arquivo auxiliar de manutencao.\n");
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
		return flag;
	}

	while(!feof(arq)){
        if(fread(&m,sizeof(Manutencao),1,arq)==1){
            if(stricmp(placa,m.placa)!=0){
                if(fwrite(&m,sizeof(Manutencao),1,arqSemExcluido)==1){
                    flag = MANUT_EXCLUIR_SUCESSO;
                }else{
                    flag = MANUT_EXCLUIR_ERRO;
                    return flag;
                }
            }else{
                flag = MANUT_EXCLUIR_SUCESSO;
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
    		flag = MANUT_EXCLUIR_ERRO;
		}else{
			flag = MANUT_EXCLUIR_ERRO;
		}
	}else{
		flag = MANUT_EXCLUIR_ERRO;
	}

	return flag;

}

int pegaManutencao(char *placa, char *cpf, Data data, Manutencao *manut){
    int flag;
	FILE *arqManut;
	Manutencao mAux;
	int posicaoManut;

    flag = buscaManutencao(placa, cpf, data, &posicaoManut);
	if(flag == MANUT_BUSCA_SUCESSO){
        if(posicaoManut == -1){
            flag = MANUT_PEGAMANUT_ERRO;
        }else{
            arqManut=fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
            if(arqManut!=NULL){
                if(fseek(arqManut,posicaoManut*sizeof(Manutencao),SEEK_SET)==0){
                    if(fread(&mAux,sizeof(Manutencao),1,arqManut)==1){
                        *manut = mAux;
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

int buscaManutencao(char *placa, char *cpf, Data data, int *pos)
{
	FILE *dbManut;
	Manutencao mAux;
	int ind = -1, flag;

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_MANUTENCAO)) return ERRO_ARQUIVO_INEXISTENTE;

	dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(dbManut != NULL){
        while(fread(&mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux.cpf, cpf) == 0 && stricmp(mAux.placa, placa) == 0 && comparaData(mAux.data, data) == 0){
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

	return flag;

}

int buscaManutencaoCPF(char *cpf, int *pos){
    FILE *dbManut;
	Manutencao mAux;
	int ind = -1, flag;

	*pos = ind;

	if(!existeArquivo(ARQUIVO_DADOS_MANUTENCAO)) return ERRO_ARQUIVO_INEXISTENTE;

	dbManut = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");
    if(dbManut != NULL){
        while(fread(&mAux, sizeof(Manutencao), 1, dbManut) == 1){
            ind++;
            if(stricmp(mAux.cpf, cpf) == 0){
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
