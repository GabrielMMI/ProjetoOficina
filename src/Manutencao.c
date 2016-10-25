#include "../include/Manutencao.h"

//Objetivo: Ler e incluir uma manutenção no arquivo de manutençao
//Parametros: ---------
//Retorno: ----------
int incluiManutencao(Manutencao m)
{
	FILE *arq;
	Manutencao mAux;
	int flag = 0;

	arq=fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	if(arq!=NULL){
		while(!feof(arq)){
			if(fread(&mAux,sizeof(Manutencao),1,arq)==1){
				if(stricmp(m.placa,mAux.placa)==0){
					if(stricmp(m.data,mAux.data)==0){
						flag = MANUT_INSERIR_ERRO_DIA;
						break;
					}
				}
			}else{
				break;
			}
		}
		fclose(arq);
	}else{
        flag = ERRO_ABRIR_ARQUIVO;
	}

	if(flag == 0){
		arq=fopen(ARQUIVO_DADOS_MANUTENCAO,"ab");

		if(arq!=NULL){
				if(fwrite(&m,sizeof(Manutencao),1,arq)==1){
                    flag = MANUT_INSERIR_SUCESSO;
                }else{
                    flag = MANUT_INSERIR_ERRO;
                }
			fclose(arq);
		}else{
            flag = ERRO_ABRIR_ARQUIVO;
		}
    }

	return flag;
}

//Objetivo: Ler e excluir uma manutenção no arquivo de manutençao
//Parametros: ---------
//Retorno: ----------
int excluiManutencao(char *placa)
{
	FILE *arq,*arqSemExcluido;
	Manutencao m;
	int flag;

	arq = fopen(ARQUIVO_DADOS_MANUTENCAO,"rb");
	if(arq!=NULL){
		arqSemExcluido = fopen("database/dbManutAux.txt","ab");
		if(arqSemExcluido!=NULL){
			while(!feof(arq)){
                if(fread(&m,sizeof(Manutencao),1,arq)==1){
                    if(stricmp(placa,m.placa)!=0){
                        if(fwrite(&m,sizeof(Manutencao),1,arqSemExcluido)!=1){
                            flag = MANUT_EXCLUIR_ERRO;
                        }else{
                            flag = MANUT_EXCLUIR_SUCESSO;
                        }
                    }else{
                       flag = MANUT_EXCLUIR_ERRO_MANUT_INEXISTENTE;
                    }
                }else{
                    flag = ERRO_ARQUIVO_LER_MANUT;
                    break;
                }
            }
			fclose(arqSemExcluido);
		}else{
            flag = ERRO_ABRIR_ARQUIVO;
            return flag;
		}
		fclose(arq);
		remove(ARQUIVO_DADOS_MANUTENCAO);
        rename("database/dbManutAux.txt", ARQUIVO_DADOS_MANUTENCAO);
	}else{
        flag = ERRO_ABRIR_ARQUIVO;
	}

	return flag;

}

int buscaManutencao(char *placa, char *cpf, char *data, int *pos)
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
            if(stricmp(mAux.cpf, cpf) == 0 && stricmp(mAux.placa, placa) == 0 && stricmp(mAux.data, data) == 0){
                *pos = ind;
                break;
            }
        }
        flag = MANUT_BUSCA_SUCESSO;
        fclose(dbManut);
    }else{
        flag = ERRO_ABRIR_ARQUIVO;
    }

	return flag;

}

//Objetivo: Pegar Data atual
//Parametros: ---------
//Retorno: ----------
void obtemDataAtual(time_t *data)
{
	time(data);
}
