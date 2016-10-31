#include "../include/Veiculo.h"

/********************************************//**
 * \brief Inclui um veiculo no arquivo de veiculos
 *
 * \param veiculo - Struct do tipo veiculo
 *
 * \return VEIC_INSERIR_SUCESSO - Sucesso ao inserir um veiculo
 * \return VEIC_INSERIR_ERRO - Erro ao inserir um veiculo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar um arquivo
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir um arquvio
 * \return VEIC_BUSCA_EXISTENTE - Veiculo buscado ja existe
 ***********************************************/

int incluiVeiculo(Veiculo veiculo)
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

/********************************************//**
 * \brief Verifica se existe um veiculo
 *
 * \param placa - Endereço de memoria de uma string de placa
 * \param pos - Endereço de memoria da variavel de posição
 *
 * \return posicao - a posição no arquivo (se existir)
 * \return -1 - se não existir no arquivo
 * \return ALOC_ERRO - Erro ao alocar memoria
 ***********************************************/

int buscaVeiculo(char *placa, int *pos)
{
	FILE *arq;
	Veiculo *veiculo==NULL;
	int posicao = 0, flag;
	*pos = -1;
	
	veiculo=(Veiculo*)malloc(sizeof(Veiculo));
	if(veiculo==NULL){
		return ALOC_ERRO;
	}else{
		flag=ALOC_SUCESSO;
	}

	if(!existeArquivo(ARQUIVO_DADOS_VEICULO)) return ERRO_ARQUIVO_INEXISTENTE;

	arq=fopen(ARQUIVO_DADOS_VEICULO,"rb");
	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(veiculo,sizeof(Veiculo),1,arq)==1){
				if(stricmp(placa,veiculo->placa)==0){
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

/********************************************//**
 * \brief Altera um veiculo no arquivo de veiculo
 *
 * \param vNovo - Dados novos do veiculo
 * \param placa - Endereço de memoria de uma string de placa
 *
 * \return VEIC_BUSCA_INEXISTENTE - Veiculo buscado é inexistente
 * \return VEIC_ALTERAR_SUCESSO - Sucesso ao alterar o veiculo
 * \return VEIC_ALTERAR_ERRO - Erro ao alterar o veiculo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar o arquivo
 ***********************************************/

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
 * \param void
 *
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir o arquivo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar o arquivo
 * \return ERRO_ARQUIVO_GRAVAR_VEIC - Erro ao gravar no arquivo de veiculos
 * \return ARQ_VEIC_ATUALIZADO - Arquivo de veiculo atualizado com sucesso
 * \return ERRO_ARQUIVO_GRAVAR_VEIC - Erro ao gravar no arquivo de veiculo
 * \return ALOC_ERRO - Erro ao alocar memoria
 ***********************************************/
 
int atualizaArqVeic(){
    FILE *arqEntrada, *arqSaida;
    Veiculo *aux==NULL;
    int flag = ARQ_VEIC_ATUALIZADO;

	aux=(Veiculo*)malloc(sizeof(Veiculo));
	if(aux==NULL){
		return ALOC_ERRO;
	}

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

	while(fread(aux, sizeof(Veiculo), 1, arqEntrada) == 1){
	    if(aux->placa[0] != '\0'){
	        if(fwrite(aux, sizeof(Veiculo), 1, arqSaida) != 1){
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

	if(flag != ARQ_VEIC_ATUALIZADO) return flag;

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

/********************************************//**
 * \brief Excluir um veiculo no arquivo de veiculo
 *
 * \param placa - Endereço de memoria de uma string de placa
 *
 * \return VEIC_EXCLUIR_ERRO_MANUT - Erro ao excluir um veiculo da manutenção, pois ele ja esta cadastrado
 * \return ERRO_ARQUIVO_LER_MANUT - Erro ao ler uma manutenção no arquivo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar o arquivo
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir o arquivo
 * \return VEIC_BUSCA_INEXISTENTE - O veiculo buscado não existe
 * \return VEIC_EXCLUIR_SUCESSO - Sucesso ao excluir o veiculo
 * \return VEIC_EXCLUIR_ERRO - Erro ao excluir o veiculo
 * \return ALOC_ERRO - Erro ao alocar memoria
 ***********************************************/

int excluiVeiculo(char *placa)
{
	FILE *arq;
	Manutencao *manutencao==NULL;
	Veiculo *veiculo==NULL;
	int pos, flag = VEIC_EXCLUIR_SUCESSO, erro;
	
	manutencao=(Manutencao*)malloc(sizeof(Manutencao));
	if(manutencao==NULL){
		return ALOC_ERRO;
	}
	
	veiculo=(Veiculo*)malloc(sizeof(Veiculo));
	if(veiculo==NULL){
		return ALOC_ERRO;
	}
	
	arq = fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	if(arq != NULL){
		while(!feof(arq)){
			if(fread(manutencao,sizeof(Manutencao),1,arq)==1){
				if(stricmp(manutencao->placa,placa) == 0){
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
                veiculo->placa[0] = '\0';
                if(alteraVeiculo(veiculo, placa) == VEIC_ALTERAR_SUCESSO){
                    flag = VEIC_EXCLUIR_SUCESSO;
                }else{
                    flag = VEIC_EXCLUIR_ERRO;
                }
            }
        }
	
    erro = atualizaArqVeic();
    if(erro != ARQ_VEIC_ATUALIZADO) flag = erro;
    }
    return flag;
}

/********************************************//**
 * \brief Validar uma placa no formato AAA-1234
 *
 * \param placa - Endereço de memoria de uma string de placa
 *
 * \return PLACA_VALIDA - Placa valida
 * \return PLACA_INVALIDA - Placa inválida
 ***********************************************/

int validaPlaca(char *placa)
{
	int flag = PLACA_VALIDA;
	if(isalpha(placa[0])==0 || isalpha(placa[1])==0 || isalpha(placa[2])==0 || isalpha(placa[4])!=0 || isalpha(placa[5])!=0 || isalpha(placa[6])!=0 || isalpha(placa[7])!=0){
		flag = PLACA_INVALIDA;
	}

	if(strlen(placa) != TAM_PLACA-1){
        flag = PLACA_INVALIDA;
	}
	return flag;
}

/********************************************//**
 * \brief Verifica se um chassi é repetido
 *
 * \param chassi - Endereço de memoria de uma string de um chassi
 *
 * \return CHASSI_REPETIDO - O chassi informado é repetido
 * \return ERRO_ARQUIVO_LER_VEIC - Erro ao ler um veiculo no arquivo de veiculo
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar um arquivo
 * \return ERRO_ARQUIVO_INEXISTENTE - Arquivo não existe
 * \return ALOC_ERRO - Erro ao alocar memoria
 ***********************************************/

int verificaChassiRepetido(char *chassi)
{
	FILE *arq;
	Veiculo *veiculo==NULL;
	int flag = CHASSI_VALIDO;

	veiculo=(Veiculo*)malloc(sizeof(Veiculo));
	if(veiculo==NULL){
		return ALOC_ERRO;
	}

	arq = fopen(ARQUIVO_DADOS_VEICULO,"rb");

	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(veiculo,sizeof(Veiculo),1,arq)==1){
				if(stricmp(chassi,veiculo->chassi)==0){

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

/********************************************//**
 * \brief Pega um veiculo
 *
 * \param placa - Endereço de memoria de uma string de placa
 * \param veiculo - Endereço de memoria de uma string de veiculo
 *
 * \return VEIC_PEGAVEIC_ERRO - Erro ao pegar um veiculo
 * \return VEIC_PEGAVEIC_SUCESSO - Sucesso ao pegar um veiculo
 * \return ERRO_ARQUIVO_LER_VEIC - Erro ao ler o arquivo de veiculos
 * \return FECHA_ARQUIVO_ERRO - Erro ao fechar o arquivo de veiculos
 * \return ERRO_ABRIR_ARQUIVO - Erro ao abrir o arquivo de veiculos
 ***********************************************/

int pegaVeiculo(char *placa,Veiculo *veiculo)
{
	int flag;
	FILE *arqVeic;
	Veiculo *vAux==NULL;
	int posicaoPlaca;

	vAux=(Veiculo*)malloc(sizeof(Veiculo));
	if(vAux==NULL){
		return ALOC_ERRO;
	}

    flag = buscaVeiculo(placa,&posicaoPlaca);
	if(flag == VEIC_BUSCA_SUCESSO){
        if(posicaoPlaca == -1){
            flag = VEIC_PEGAVEIC_ERRO;
        }else{
            arqVeic=fopen(ARQUIVO_DADOS_VEICULO, "rb");
            if(arqVeic!=NULL){
                if(fseek(arqVeic,posicaoPlaca*sizeof(Veiculo),SEEK_SET)==0){
                    if(fread(vAux,sizeof(Veiculo),1,arqVeic)==1){
                        *veiculo=vAux;
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

/********************************************//**
 * \brief Carrega todos os veiculos
 *
 * \param void
 *
 * \return Endereço de um ponteiro do tipo Veiculo
 ***********************************************/
Veiculo *carregaVeiculos()
{
	FILE *dbVeic;
	int qtVeic;
	Veiculo *veiculos = NULL;

	qtVeic = obtemQuantVeicArquivo();
	veiculos = (Veiculo *)malloc(qtVeic * sizeof(Veiculo));
	if(veiculos != NULL){
		dbVeic = fopen(ARQUIVO_DADOS_VEICULO, "rb");
		if(dbVeic != NULL){
			if(fread(veiculos, sizeof(Veiculo), qtVeic, dbVeic) != qtVeic){
				free(veiculos);
				veiculos = NULL;
			}
			fechaArquivo(dbVeic);
		}
	}

	return veiculos;
}

/********************************************//**
 * \brief Obtem a quantidade de veiculos no arquivo de veiculos
 *
 * \param void
 *
 * \return A quantidade de veiculos
 ***********************************************/

int obtemQuantVeicArquivo()
{
	FILE *arqVeic;
	int qtVeic = -1;

	arqVeic = fopen(ARQUIVO_DADOS_VEICULO, "rb");
	if(arqVeic != NULL){
		if(fseek(arqVeic, 0, SEEK_END) == 0){
			qtVeic = ftell(arqVeic)/sizeof(Veiculo);
		}
		fechaArquivo(arqVeic);
	}
	return qtVeic;
}

