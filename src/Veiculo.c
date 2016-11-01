/********************************************//**
 ** @file Veiculo.c
 * @brief Implementa todas as funções de Veiculo.h
 *
 *
 * @bug Nenhum problema conhecido!
 * @author Matheus Bispo
 * @author Gabriel Messias
 ***********************************************/

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

	flag = buscaVeiculo(veiculo.placa, &pos);
        if(flag == VEIC_BUSCA_SUCESSO){
            if(pos == -1){
                arq = fopen(ARQUIVO_DADOS_VEICULO ,"ab");
                if(arq!=NULL){
                    if(fwrite(&veiculo,sizeof(Veiculo),1,arq)==1){
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
	Veiculo *veiculo = NULL;
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
	
	free(veiculo);
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
	int pos = -1, flag = VEIC_EXCLUIR_ERRO, erro;
	Veiculo *vAux = NULL;
	FILE *arq, *arqSemExcluido;

	vAux = (Veiculo *)malloc(sizeof(Veiculo));
	if(vAux==NULL){
		return ALOC_ERRO;
	}

	arq = fopen(ARQUIVO_DADOS_VEICULO,"rb");
	arqSemExcluido = fopen("database/dbVeicAux.dat","wb");
	
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

	buscaManutencaoPlaca(placa, &pos);

	if(pos == -1){
		while(!feof(arq)){
	        if(fread(vAux,sizeof(Veiculo),1,arq)==1){
	            if(stricmp(vAux->placa,placa) != 0){
	                if(fwrite(vAux,sizeof(Veiculo),1,arqSemExcluido)==1){
	                    flag = VEIC_EXCLUIR_SUCESSO;
	                }else{
	                    flag = VEIC_EXCLUIR_ERRO;
	                    return flag;
	                }
	            }
	        }
	    }
	}else{
		flag = VEIC_EXCLUIR_ERRO_MANUT;
	}
    
    if(fechaArquivo(arqSemExcluido) == FECHA_ARQUIVO_ERRO){
        flag = FECHA_ARQUIVO_ERRO;
    }

    if(fechaArquivo(arq) == FECHA_ARQUIVO_ERRO){
        flag = FECHA_ARQUIVO_ERRO;
    }

	if(flag == VEIC_EXCLUIR_SUCESSO){
	    if(remove(ARQUIVO_DADOS_VEICULO)==0){
	    	if(rename("database/dbVeicAux.dat", ARQUIVO_DADOS_VEICULO)==0){
	    		flag = VEIC_EXCLUIR_SUCESSO;
			}else{
				flag = VEIC_EXCLUIR_ERRO;
			}
		}else{
			flag = VEIC_EXCLUIR_ERRO;
		}
	}

    free(vAux);
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
	Veiculo *veiculo = NULL;
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
	
	free(veiculo);
	return flag;
}

/********************************************//**
 * \brief Pega um veiculo no arquivo de Veiculos
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
	int posicaoPlaca;

    flag = buscaVeiculo(placa,&posicaoPlaca);
	if(flag == VEIC_BUSCA_SUCESSO){
        if(posicaoPlaca == -1){
            flag = VEIC_PEGAVEIC_ERRO;
        }else{
            arqVeic=fopen(ARQUIVO_DADOS_VEICULO, "rb");
            if(arqVeic!=NULL){
                if(fseek(arqVeic,posicaoPlaca*sizeof(Veiculo),SEEK_SET)==0){
                    if(fread(veiculo,sizeof(Veiculo),1,arqVeic)==1){
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
 * \brief Carrega todos os veiculos de um arquivo de veículos
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

