#include "../include/Veiculo.h"

//Objetivo: Incluir um veiculo no arquivo de veiculos
//Parametros: Struct de veiculos
//Retorno: ---------------
int incluiVeiculo(Veiculo v)
{
	FILE *arq;
	int flag, pos;

	flag = buscaVeiculo(v.placa, &pos);
        if(flag == VEIC_BUSCA_SUCESSO){
            if(pos == -1){
                arq = fopen(ARQUIVO_DADOS_VEICULO ,"ab");
                if(arq!=NULL){
                    if(fwrite(&v,sizeof(Veiculo),1,arq)==1){
                        flag = VEIC_INSERIR_SUCESSO;
                    }else{
                        flag = VEIC_INSERIR_ERRO;
                    }

                    if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
                        flag = FECHA_ARQUIVO_ERRO;
                    }
                }else{
                    flag = ERRO_ABRIR_ARQUIVO;
                }
            }else{
                flag = VEIC_BUSCA_EXISTENTE;
            }
        }

	return flag;
}

//Objetivo: Verificar se existe um veiculo
//Parametros: -----------
//Retorno: A posicao do veiculo no arquivo(se existir) ou -1
int buscaVeiculo(char *placa, int *pos)
{
	FILE *arq;
	Veiculo v;
	int posicao = 0, flag;
	*pos = -1;

	if(!existeArquivo(ARQUIVO_DADOS_VEICULO)) return ERRO_ARQUIVO_INEXISTENTE;

	arq=fopen(ARQUIVO_DADOS_VEICULO,"rb");
	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(&v,sizeof(Veiculo),1,arq)==1){
				if(stricmp(placa,v.placa)==0){
					*pos = posicao;
				}
			}
			posicao++;
		}
        flag = VEIC_BUSCA_SUCESSO;
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
	}else{
        flag = ERRO_ABRIR_ARQUIVO;
	}
	return flag;
}

//Objetivo: Ler e alterar um veiculo no arquivo de veiculos
//Parametros: ------------
//Retorno: ----------
int alteraVeiculo(Veiculo vNovo, char *placa)
{
	FILE *arq;
	int flag=0, posicao;
	char teste[20];

	flag = buscaVeiculo(placa, &posicao);
	itoa(posicao, teste, 20);
	if(flag == VEIC_BUSCA_SUCESSO){
        if(posicao == -1){
            flag = VEIC_BUSCA_INEXISTENTE;
        }else{
        	arq = fopen(ARQUIVO_DADOS_VEICULO,"r+b");
            if(arq != NULL){
                if(fseek(arq,posicao*sizeof(Veiculo),SEEK_SET)==0){
                    if(fwrite(&vNovo,sizeof(Veiculo),1,arq)==1){
                        flag = VEIC_ALTERAR_SUCESSO;
                    }else{
                        flag = VEIC_ALTERAR_ERRO;
                    }
                }
                if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
                    flag = FECHA_ARQUIVO_ERRO;
                }
            }
        }
	}

	return flag;
}

/********************************************//**
 * \brief Atualiza o arquivo de veiculos
 *
 * \return PROP_INSERIR_ERRO - Erro na reinsercao dos dados
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir o arquivo
 ***********************************************/
int atualizaArqVeic(){
    FILE *arqEntrada, *arqSaida;
    Veiculo aux;
    int flag = ARQ_VEIC_ATUALIZADO;

    arqEntrada = fopen(ARQUIVO_DADOS_VEICULO, "rb");
    arqSaida = fopen("database/dbVeicAux.dat", "wb");

	if(arqEntrada==NULL){
		return ERRO_ABRIR_ARQUIVO;
	}

	if(arqSaida==NULL){
        flag = ERRO_ABRIR_ARQUIVO;
        if(fechaArquivo(arqEntrada) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
		return flag;
	}

	while(fread(&aux, sizeof(Veiculo), 1, arqEntrada) == 1){
	    if(aux.placa[0] != '\0'){
	        if(fwrite(&aux, sizeof(Veiculo), 1, arqSaida) != 1){
	        	return ERRO_ARQUIVO_GRAVAR_VEIC;
			}
	    }
	}

    if(fechaArquivo(arqEntrada) == FECHA_ARQUIVO_ERRO){
        flag = FECHA_ARQUIVO_ERRO;
    }

    if(fechaArquivo(arqSaida) == FECHA_ARQUIVO_ERRO){
        flag = FECHA_ARQUIVO_ERRO;
    }

	if(flag != 0) return flag;

    if(remove(ARQUIVO_DADOS_VEICULO)==0){
    	if(rename("database/dbVeicAux.dat", ARQUIVO_DADOS_VEICULO)==0){
    		return ARQ_VEIC_ATUALIZADO;
		}else{
			return ERRO_ARQUIVO_GRAVAR_VEIC;
		}
	}else{
		return ERRO_ARQUIVO_GRAVAR_VEIC;
	}
}


//Objetivo: Ler e excluir um veiculo no arquivo de veiculos
//Parametros: Endereco da placa que sera excluida
//Retorno: -------------
int excluiVeiculo(char *placa)
{
	FILE *arq;
	Manutencao m;
	Veiculo v;
	int pos, flag = VEIC_EXCLUIR_SUCESSO, erro;

	arq = fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	if(arq != NULL){
		while(!feof(arq)){
			if(fread(&m,sizeof(Manutencao),1,arq)==1){
				if(stricmp(m.placa,placa) == 0){
					flag = VEIC_EXCLUIR_ERRO_MANUT;
					break;
				}
			}else{
			    flag = ERRO_ARQUIVO_LER_MANUT;
				break;
			}
		}
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
	}else{
        flag = ERRO_ABRIR_ARQUIVO;
        return flag;
	}

	if(flag != VEIC_EXCLUIR_ERRO_MANUT){

        flag = buscaVeiculo(placa, &pos);
        if(flag == VEIC_BUSCA_SUCESSO){
            if(pos == -1){
                flag = VEIC_BUSCA_INEXISTENTE;
                return flag;
            }else{
                v.placa[0] = '\0';
                if(alteraVeiculo(v, placa) == VEIC_ALTERAR_SUCESSO){
                    flag = VEIC_EXCLUIR_SUCESSO;
                }else{
                    flag = VEIC_EXCLUIR_ERRO;
                }
            }
        }
	}
    erro = atualizaArqVeic();
    if(erro != ARQ_VEIC_ATUALIZADO) flag = erro;
    return flag;
}

//Objetivo: Validar uma placa no formato AAA1234
//Parametros: Endereco da placa
//Retorno: 0(placa valida) ou 1(placa invalida)
int validaPlaca(char *placa)
{
	int flag = PLACA_VALIDA;
	if(isalpha(placa[0])==0 || isalpha(placa[1])==0 || isalpha(placa[2])==0 || isalpha(placa[3])!=0 || isalpha(placa[4])!=0 || isalpha(placa[5])!=0 || isalpha(placa[6])!=0){
		flag = PLACA_INVALIDA;
	}
	return flag;
}

int verificaChassiRepetido(char *chassi)
{
	FILE *arq;
	Veiculo v;
	int flag = CHASSI_VALIDO;

	arq = fopen(ARQUIVO_DADOS_VEICULO,"rb");

	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(&v,sizeof(Veiculo),1,arq)==1){
				if(stricmp(chassi,v.chassi)==0){

					flag = CHASSI_REPETIDO;

					break;
				}
			}else{
			    flag = ERRO_ARQUIVO_LER_VEIC;
				break;
			}
		}
        if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
            flag = FECHA_ARQUIVO_ERRO;
        }
	}else{
        flag = ERRO_ARQUIVO_INEXISTENTE;
	}
	return flag;
}

int pegaVeiculo(char *placa,Veiculo *v)
{
	int flag;
	FILE *arqVeic;
	Veiculo vAux;
	int posicaoPlaca;

    flag = buscaVeiculo(placa,&posicaoPlaca);
	if(flag == VEIC_BUSCA_SUCESSO){
        if(posicaoPlaca == -1){
            flag = VEIC_PEGAVEIC_ERRO;
        }else{
            arqVeic=fopen(ARQUIVO_DADOS_VEICULO, "rb");
            if(arqVeic!=NULL){
                if(fseek(arqVeic,posicaoPlaca*sizeof(Veiculo),SEEK_SET)==0){
                    if(fread(&vAux,sizeof(Veiculo),1,arqVeic)==1){
                        *v=vAux;
                        flag = VEIC_PEGAVEIC_SUCESSO;
                    }else{
                        flag = ERRO_ARQUIVO_LER_VEIC;
                    }
                }
                if(fechaArquivo(arqVeic) == FECHA_ARQUIVO_ERRO){
                    flag = FECHA_ARQUIVO_ERRO;
                }
            }else{
                flag = ERRO_ABRIR_ARQUIVO;
            }
        }
	}
	return flag;
}
