#include "../include/gtest/gtest.h"
#include <stdio.h>
#include <stdlib.h>

#include "../../Projeto/src/Win_Funcoes_Basicas.c"
#include "../../Projeto/src/Proprietario.c"
#include "../../Projeto/src/Manutencao.c"
#include "../../Projeto/src/Veiculo.c"
#include "../../Projeto/include/Erros.h"
#include "../../Projeto/include/Defines.h"

#include "geradores.c"
#include "Util.c"

int main (int argc, char** argv) {
    ::testing::GTEST_FLAG(output) = "xml:xml/logTeste.xml";
    ::testing::InitGoogleTest(&argc, argv);

    //::testing::GTEST_FLAG(filter) = "Teste_de_matematica*";

    int returnValue;

    printf("\n PROJETO FINAL - OFICINA [TESTES]\n");
    printf("\n====================================\n\n");
    
    returnValue =  RUN_ALL_TESTS();

	system("pause");
    return returnValue;
}

// WIN_FUNCOES_BASICAS
TEST(Win_Funcoes_Basicas, configuraAmbiente){
	EXPECT_EQ(FECHA_ARQUIVO_SUCESSO, configuraAmbiente());
	deletaDados();
}

TEST(Win_Funcoes_Basicas, existeArquivo){
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, existeArquivo(ARQUIVO_DADOS_MANUTENCAO));
	configuraAmbiente();
	existeArquivo(ARQUIVO_DADOS_PROPRIETARIO);
	
	deletaDados();
}

TEST(Win_Funcoes_Basicas, guardaPegaHandle){
	HWND handle;
	
	EXPECT_EQ(NULL,  guardaPegaHandle(NULL, 1));
	EXPECT_EQ(&handle, guardaPegaHandle(&handle, 0));

}

TEST(Win_Funcoes_Basicas, fechaArquivo){
	FILE *arq = NULL;
	
	EXPECT_EQ(fechaArquivo(arq), FECHA_ARQUIVO_ERRO);
	configuraAmbiente();
	
	arq = fopen(ARQUIVO_DADOS_MANUTENCAO, "rb");

	EXPECT_EQ(fechaArquivo(arq), FECHA_ARQUIVO_SUCESSO);
	
    deletaDados();

}

TEST(Win_Funcoes_Basicas, isFloat){
	EXPECT_FLOAT_EQ(TRUE, isFloat("2.0"));
	EXPECT_FLOAT_EQ(FALSE, isFloat("Matheus"));
}

TEST(Win_Funcoes_Basicas, stristr){
	char *res;
	res = stristr("aA", "aa");
	EXPECT_TRUE(NULL != res);
	res = stristr("aa", "aa");
	EXPECT_TRUE(NULL != res);
	res = stristr("ba", "aa");
	EXPECT_EQ(NULL, res);
	
}

//PROPRIETARIO
TEST(Proprietario, incluiProprietario){
    Proprietario *prop;
    
    deletaDados();
    
    EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, incluiProprietario(*prop));
    configuraAmbiente();
    
    prop = criaProprietario();
    
    EXPECT_TRUE(prop != NULL);
    EXPECT_EQ(PROP_INSERIR_SUCESSO, incluiProprietario(*prop));
    EXPECT_EQ(PROP_BUSCA_EXISTENTE, incluiProprietario(*prop));
    
    free(prop);
    deletaDados();
}

TEST(Proprietario, buscaProprietario){
	Proprietario *prop;
	int pos;
	char *cpf;
	
	deletaDados();
	
    EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, buscaProprietario(prop->cpf, &pos));
    EXPECT_EQ(pos, -1);
    
    configuraAmbiente();    
    prop = criaProprietario();
    
    EXPECT_TRUE(prop != NULL);
    incluiProprietario(*prop);
    
    EXPECT_EQ(PROP_BUSCA_SUCESSO, buscaProprietario(prop->cpf, &pos));    
    EXPECT_EQ(pos, 0);
    
    cpf = prop->cpf;    
    prop = criaProprietario();
    
    EXPECT_TRUE(prop != NULL);
    incluiProprietario(*prop);
    
    EXPECT_EQ(PROP_BUSCA_SUCESSO, buscaProprietario(cpf, &pos));   
    EXPECT_EQ(pos, 0);
    EXPECT_EQ(PROP_BUSCA_SUCESSO, buscaProprietario(prop->cpf, &pos));
    EXPECT_EQ(pos, 1);
    
    free(prop);
    deletaDados();
}

TEST(Proprietario, alteraProprietario){
	Proprietario *prop, *propNovo;
	char *cpf;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, alteraProprietario(*propNovo, cpf));
	
    configuraAmbiente();
    
    prop = criaProprietario();

    EXPECT_EQ(PROP_BUSCA_INEXISTENTE, alteraProprietario(*propNovo, cpf));

    incluiProprietario(*prop);
    
    propNovo = criaProprietario();
    
    cpf = prop->cpf;
    
    EXPECT_EQ(PROP_ALTERAR_SUCESSO, alteraProprietario(*propNovo, cpf));
    
    EXPECT_STRCASENE(propNovo->cpf, prop->cpf);
    
    free(prop);
    free(propNovo);
    deletaDados();
}

TEST(Proprietario, excluiProprietario){
	
	Proprietario *prop;
	Veiculo *veic;
	Manutencao *manut;
	
	char *cpf;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ABRIR_ARQUIVO, excluiProprietario(cpf));
	
    configuraAmbiente();
    
    prop = criaProprietario();

    EXPECT_EQ(PROP_EXCLUIR_ERRO, excluiProprietario(cpf));

    incluiProprietario(*prop);
    
    EXPECT_EQ(PROP_EXCLUIR_SUCESSO, excluiProprietario(prop->cpf));
    
    veic = criaVeiculo();
    manut = criaManutencao();
    
   	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);

    incluiProprietario(*prop);
    incluiVeiculo(*veic);
    incluiManutencao(*manut);
    
    EXPECT_EQ(PROP_EXCLUIR_ERRO_MANUT_EXISTENTE, excluiProprietario(prop->cpf));
    
    free(prop);
    deletaDados();
}

TEST(Proprietario, pegaProprietario){
	Proprietario *prop, propAux;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, pegaProprietario(propAux.cpf, prop));
	
    configuraAmbiente();
    
    EXPECT_EQ(PROP_BUSCA_INEXISTENTE, pegaProprietario(propAux.cpf, prop));
    
    prop = criaProprietario();
    incluiProprietario(*prop);
    
    EXPECT_EQ(PROP_PEGAPROP_SUCESSO, pegaProprietario(prop->cpf, &propAux));
    EXPECT_STRCASEEQ(prop->cpf, propAux.cpf);
    
    free(prop);
    
    deletaDados();

}

TEST(Proprietario, validaCPF){
	char cpf[] = "017.318.971-70";
	char cpfIn[] = "231.456.465-45";
	
	EXPECT_EQ(CPF_VALIDO, validaCPF(cpf));
	EXPECT_EQ(CPF_INVALIDO, validaCPF(cpfIn));
	
}

TEST(Proprietario, validaTelefone){
	char tel[] = "3373-2796";
	char telIn[] = "3373-27966";
	char tel2[] = "9306-1111";
	char tel3[] = "9306-11112";
	char telIn2[] = "33732796";
	
	
	EXPECT_EQ(TEL_VALIDO, validaTelefone(tel));
	EXPECT_EQ(TEL_INVALIDO, validaTelefone(telIn));
	EXPECT_EQ(TEL_VALIDO, validaTelefone(tel2));
	EXPECT_EQ(TEL_VALIDO, validaTelefone(tel3));
	EXPECT_EQ(TEL_INVALIDO, validaTelefone(telIn2));
	
}

TEST(Proprietario, validaDDD){
	char ddd[] = "33";
	char dddIn[] = "01";
	char ddd2[] = "61";
	char dddIn2[] = "30";
	
	
	EXPECT_EQ(DDD_VALIDO, validaDDD(ddd));
	EXPECT_EQ(DDD_INVALIDO, validaDDD(dddIn));
	EXPECT_EQ(DDD_VALIDO, validaDDD(ddd2));
	EXPECT_EQ(DDD_INVALIDO, validaDDD(dddIn2));
	
}

TEST(Proprietario, obtemQuantPropArquivo){
	Proprietario *prop;
	int cont = 4, x;
	
	deletaDados();
	
	EXPECT_EQ( -1 , obtemQuantPropArquivo());
	
	configuraAmbiente();
	
	EXPECT_EQ( 0 , obtemQuantPropArquivo());
	
	for(x = 0; x < cont;x++){
		prop = criaProprietario();
		incluiProprietario(*prop);
		free(prop);
	}
	
	EXPECT_EQ( 4 , obtemQuantPropArquivo());

	deletaDados();
}

TEST(Proprietario, carregaProprietarios){
	Proprietario *prop, *props = NULL;
	int cont = 4, x;
	
	deletaDados();
	
	props = carregaProprietarios();

	EXPECT_EQ(NULL, props);
	
	free(props);
	
	configuraAmbiente();
	
	props = carregaProprietarios();
	EXPECT_EQ( NULL , props);
	
	free(props);
	
	for(x = 0; x < cont;x++){
		prop = criaProprietario();
		incluiProprietario(*prop);
		free(prop);
	}
	
	props = carregaProprietarios();
	EXPECT_EQ(4  , sizeof(props));
	
	free(props);
	deletaDados();
}

//VEICULO
TEST(Veiculo, incluiVeiculo){
	Veiculo *veic;
    
    deletaDados();
    
    EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, incluiVeiculo(*veic));
    configuraAmbiente();
    
    veic = criaVeiculo();
    
    EXPECT_TRUE(veic != NULL);
    EXPECT_EQ(VEIC_INSERIR_SUCESSO, incluiVeiculo(*veic));
    EXPECT_EQ(VEIC_BUSCA_EXISTENTE, incluiVeiculo(*veic));
    
    free(veic);
    deletaDados();

}

TEST(Veiculo, buscaVeiculo){
	Veiculo *veic, *veicNew;
	int pos;
	
	deletaDados();
	
    EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, buscaVeiculo(veic->placa, &pos));
    EXPECT_EQ(pos, -1);
    
    configuraAmbiente();    
    veic = criaVeiculo();
    
    EXPECT_TRUE(veic != NULL);
    incluiVeiculo(*veic);
    
    EXPECT_EQ(VEIC_BUSCA_SUCESSO, buscaVeiculo(veic->placa, &pos));    
    EXPECT_EQ(pos, 0);
       
    veicNew = criaVeiculo();
    
    EXPECT_TRUE(veicNew != NULL);
    incluiVeiculo(*veicNew);
    
    EXPECT_EQ(VEIC_BUSCA_SUCESSO, buscaVeiculo(veic->placa, &pos));   
    EXPECT_EQ(0, pos);
    EXPECT_EQ(VEIC_BUSCA_SUCESSO, buscaVeiculo(veicNew->placa, &pos));
    EXPECT_EQ(1, pos);
    
    free(veic);
    free(veicNew);
    deletaDados();
}

TEST(Veiculo, alteraVeiculo){
	Veiculo *veic, *veicNovo;
	char *placa;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, alteraVeiculo(*veicNovo, placa));
	
    configuraAmbiente();
    
    veic = criaVeiculo();

    EXPECT_EQ(VEIC_BUSCA_INEXISTENTE,  alteraVeiculo(*veicNovo, placa));

    incluiVeiculo(*veic);
    
    veicNovo = criaVeiculo();
    
    placa = veic->placa;
    
    EXPECT_EQ(VEIC_ALTERAR_SUCESSO, alteraVeiculo(*veicNovo, placa));
    
    EXPECT_STRCASENE(veicNovo->placa, veic->placa);
    
    free(veic);
    free(veicNovo);
    deletaDados();
}

TEST(Veiculo, excluiVeiculo){
	
	Veiculo *veic;
	char *placa;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ABRIR_ARQUIVO, excluiVeiculo(placa));
	
    configuraAmbiente();
    
    veic = criaVeiculo();

    EXPECT_EQ(VEIC_EXCLUIR_ERRO, excluiVeiculo(placa));

    incluiVeiculo(*veic);
    
    EXPECT_EQ(VEIC_EXCLUIR_SUCESSO, excluiVeiculo(veic->placa));
    
    incluiVeiculo(*veic);
    incluiVeiculo(*veic);
    //incluiManutencao(*manut);
    
    //EXPECT_EQ(PROP_EXCLUIR_ERRO_MANUT_EXISTENTE, excluiProprietario(prop->cpf));
    
    free(veic);
    deletaDados();
}

TEST(Veiculo, pegaVeiculo){
	Veiculo *veic, veicAux;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, pegaVeiculo(veicAux.placa, veic));
	
    configuraAmbiente();
    
    EXPECT_EQ(VEIC_PEGAVEIC_ERRO, pegaVeiculo(veicAux.placa, veic));
    
    veic = criaVeiculo();
    incluiVeiculo(*veic);
    
    EXPECT_EQ(VEIC_PEGAVEIC_SUCESSO, pegaVeiculo(veic->placa, &veicAux));
    EXPECT_STRCASEEQ(veic->placa, veicAux.placa);
    
    free(veic);
    
    deletaDados();

}

TEST(Veiculo, validaPlaca){
	char placa[] = "AAA-2796";
	char placaIn[] = "AAAA-2796";
	char placaIn2[] = "AA-A1234";
	char placaIn3[] = "232-SADU";
	
	
	EXPECT_EQ(PLACA_VALIDA, validaPlaca(placa));
	EXPECT_EQ(PLACA_INVALIDA, validaPlaca(placaIn));
	EXPECT_EQ(PLACA_INVALIDA, validaPlaca(placaIn2));
	EXPECT_EQ(PLACA_INVALIDA, validaPlaca(placaIn3));
}

TEST(Veiculo, obtemQuantVeicArquivo){
	Veiculo *veic;
	int cont = 4, x;
	
	deletaDados();
	
	EXPECT_EQ( -1 , obtemQuantVeicArquivo());
	
	configuraAmbiente();
	
	EXPECT_EQ( 0 , obtemQuantVeicArquivo());
	
	for(x = 0; x < cont;x++){
		veic = criaVeiculo();
		incluiVeiculo(*veic);
		free(veic);
	}
	
	EXPECT_EQ( 4 , obtemQuantVeicArquivo());

	deletaDados();
}

TEST(Veiculo, carregaVeiculos){
	Veiculo *veic, *veics = NULL;
	int cont = 4, x;
	
	deletaDados();
	
	veics = carregaVeiculos();

	EXPECT_EQ(NULL, veics);
	
	free(veics);
	
	configuraAmbiente();
	
	veics = carregaVeiculos();
	EXPECT_EQ( NULL , veics);
	
	free(veics);
	
	for(x = 0; x < cont;x++){
		veic = criaVeiculo();
		incluiVeiculo(*veic);
		free(veic);
	}
	
	veics = carregaVeiculos();
	EXPECT_EQ(4  , sizeof(veics));
	
	free(veics);
	deletaDados();
}

//MANUTENCAO
TEST(Manutencao, buscaManutencaoPlaca){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	int pos;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, buscaManutencaoPlaca(veic->placa, &pos));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencaoPlaca(veic->placa, &pos));
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencaoPlaca(veic->placa, &pos));
	EXPECT_EQ(0, pos);
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, buscaManutencaoCPF){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	int pos;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, buscaManutencaoCPF(prop->cpf, &pos));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencaoCPF(prop->cpf, &pos));
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencaoCPF(prop->cpf, &pos));
	EXPECT_EQ(0, pos);
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, comparaData){
	Data data1, data2;
	
	data1.ano = 2012;
	data1.mes = 10;
	data1.dia = 22;
	
	data2 = data1;
	EXPECT_EQ(0, comparaData(data1, data2));
	data2.ano = 2011;	
	EXPECT_EQ(1, comparaData(data1, data2));
	data2.ano = 2013;
	EXPECT_EQ(-1, comparaData(data1, data2));
	
	data2 = data1;
	EXPECT_EQ(0, comparaData(data1, data2));
	data2.mes = 1;	
	EXPECT_EQ(1, comparaData(data1, data2));
	data2.mes = 12;
	EXPECT_EQ(-1, comparaData(data1, data2));
	
	data2 = data1;
	EXPECT_EQ(0, comparaData(data1, data2));
	data2.dia = 1;	
	EXPECT_EQ(1, comparaData(data1, data2));
	data2.dia = 23;
	EXPECT_EQ(-1, comparaData(data1, data2));
	
	data1.ano = 2016;
	data1.mes = 1;
	data1.dia = 1;
	data2.ano = 2014;
	data2.dia = 29;
	data2.mes = 12;
	
	EXPECT_EQ(1, comparaData(data1, data2));
}

TEST(Manutencao, buscaManutencaoPlacDat){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	Data data1;
	int pos;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, buscaManutencaoPlacDat(veic->placa, data1, &pos));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencaoPlacDat(veic->placa, data1, &pos));
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	data1.ano = 2222;
	data1.dia = 2;
	data1.mes = 2;
	
	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencaoPlacDat(veic->placa, data1, &pos));
	EXPECT_EQ(0, pos);
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, pegaManutencaoPlacDat){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL, manutAux;
	Proprietario *prop = NULL;
	Data data1;
	int pos;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, pegaManutencaoPlacDat(veic->placa, data1, &manutAux));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_PEGAMANUT_ERRO, pegaManutencaoPlacDat(veic->placa, data1, &manutAux));
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	data1.ano = 2222;
	data1.dia = 2;
	data1.mes = 2;
	
	EXPECT_EQ(MANUT_PEGAMANUT_SUCESSO, pegaManutencaoPlacDat(veic->placa, data1, &manutAux));
	EXPECT_STRCASEEQ(veic->placa, manutAux.placa);
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, buscaManutencao){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	Data data1;
	int pos;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, buscaManutencao(veic->placa, prop->cpf,data1, &pos));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencao(veic->placa, prop->cpf, data1, &pos));
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	data1.ano = 2222;
	data1.dia = 2;
	data1.mes = 2;
	
	EXPECT_EQ(MANUT_BUSCA_SUCESSO, buscaManutencao(veic->placa, prop->cpf, data1, &pos));
	EXPECT_EQ(0, pos);
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, incluiManutencao){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	Data data1;
	int pos;
	
	deletaDados();
	manut = criaManutencao();
	
	EXPECT_EQ(ERRO_ABRIR_ARQUIVO, incluiManutencao(*manut));
	
	configuraAmbiente();

	EXPECT_EQ(PROP_BUSCA_INEXISTENTE, incluiManutencao(*manut));
	
	prop = criaProprietario();
	incluiProprietario(*prop);
	strcpy(manut->cpf,prop->cpf);
	
	EXPECT_EQ(VEIC_BUSCA_INEXISTENTE, incluiManutencao(*manut));
	
	veic = criaVeiculo();
	incluiVeiculo(*veic);
	strcpy(manut->placa,veic->placa);
	
	EXPECT_EQ(MANUT_INSERIR_SUCESSO, incluiManutencao(*manut));
	EXPECT_EQ(MANUT_INSERIR_ERRO_DIA, incluiManutencao(*manut));
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, excluiManutencao){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	Data data1;
	int pos;
	
	deletaDados();
	manut = criaManutencao();
	
	EXPECT_EQ(MANUT_EXCLUIR_ERRO, excluiManutencao(veic->placa, prop->cpf, data1));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_EXCLUIR_ERRO, excluiManutencao(veic->placa, prop->cpf, data1));
	
	prop = criaProprietario();
	incluiProprietario(*prop);
	strcpy(manut->cpf,prop->cpf);
	
	veic = criaVeiculo();
	incluiVeiculo(*veic);
	strcpy(manut->placa,veic->placa);
	
	incluiManutencao(*manut);
	
	EXPECT_EQ(MANUT_EXCLUIR_SUCESSO, excluiManutencao(veic->placa, prop->cpf, manut->data));
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, pegaManutencao){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL, manutAux;
	Proprietario *prop = NULL;
	Data data1;
	int pos;
	
	deletaDados();
	
	EXPECT_EQ(ERRO_ARQUIVO_INEXISTENTE, pegaManutencao(veic->placa, prop->cpf, data1, &manutAux));
	
	configuraAmbiente();

	EXPECT_EQ(MANUT_PEGAMANUT_ERRO, pegaManutencao(veic->placa,  prop->cpf, data1, &manutAux));
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	data1.ano = 2222;
	data1.dia = 2;
	data1.mes = 2;
	
	EXPECT_EQ(MANUT_PEGAMANUT_SUCESSO, pegaManutencao(veic->placa,  prop->cpf, data1, &manutAux));
	EXPECT_STRCASEEQ(veic->placa, manutAux.placa);
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, carregaManutencoesCPF){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL, *manuts;
	Proprietario *prop = NULL;
	int qtProp;
	
	deletaDados();
	manuts = carregaManutencoesCPF(prop->cpf, &qtProp);
	EXPECT_TRUE(NULL == manuts);	
	EXPECT_EQ(-1, qtProp);
	
	configuraAmbiente();

	manuts = carregaManutencoesCPF(prop->cpf, &qtProp);
	EXPECT_TRUE(NULL == manuts);	
	EXPECT_EQ(0, qtProp);
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	manuts = carregaManutencoesCPF(prop->cpf, &qtProp);
	EXPECT_TRUE(NULL != manuts);	
	EXPECT_EQ(1, qtProp);
	
	free(manuts);
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, convertTime){
	Data data1;
	SYSTEMTIME st;
	
	st.wDay = 1;
	st.wMonth = 2;
	st.wYear = 3;
	
	data1 = convertTime(st);
	
	EXPECT_EQ(data1.ano, 3);
	EXPECT_EQ(data1.mes, 2);
	EXPECT_EQ(data1.dia, 1);
}

TEST(Manutencao, obtemDataAtual){
	Data data1;
	SYSTEMTIME st;
	
	obtemDataAtual(&data1);
	
	GetLocalTime(&st);
	
	EXPECT_EQ(data1.dia, st.wDay);
	EXPECT_EQ(data1.mes, st.wMonth);
	EXPECT_EQ(data1.ano, st.wYear);
}

TEST(Manutencao, obtemQuantManutArquivo){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL;
	Proprietario *prop = NULL;
	
	deletaDados();
	
	EXPECT_TRUE(-1 == obtemQuantManutArquivo());	
	
	configuraAmbiente();

	EXPECT_TRUE(0 == obtemQuantManutArquivo());	
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	EXPECT_TRUE(1 == obtemQuantManutArquivo());	
	
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, carregaManutencoes){
	Veiculo *veic = NULL;
	Manutencao *manut = NULL, *manuts;
	Proprietario *prop = NULL;
	int qtProp;
	
	deletaDados();
	manuts = carregaManutencoes();
	EXPECT_TRUE(NULL == manuts);
	
	configuraAmbiente();

	manuts = carregaManutencoes();
	EXPECT_TRUE(NULL == manuts);	
	
	veic = criaVeiculo();
	prop = criaProprietario();
	
	incluiProprietario(*prop);
	incluiVeiculo(*veic);
	
	manut = criaManutencao();
	strcpy(manut->placa,veic->placa);
	strcpy(manut->cpf,prop->cpf);
	
	incluiManutencao(*manut);
	
	manuts = carregaManutencoes();
	EXPECT_TRUE(NULL != manuts);
	
	free(manuts);
	free(manut);
	free(veic);
	free(prop);
	
	deletaDados();
	
}

TEST(Manutencao, converteDataString){
	Data data1;
	char data[TAM_DATA];
	
	data1.dia = 1;
	data1.mes = 2;
	data1.ano = 2222;
	
	EXPECT_TRUE( 0 < converteDataString(data, data1));
	EXPECT_STRCASEEQ("01/02/2222", data);
	
}

TEST(Manutencao, converteStringData){
	Data data1;
	char data[] = "01/02/2222", dataIn[] = "01112/2222";
	
	EXPECT_TRUE( 3 == converteStringData(data, &data1));
	
	EXPECT_EQ(data1.ano, 2222);
	EXPECT_EQ(data1.mes, 2);
	EXPECT_EQ(data1.dia, 1);
	
	EXPECT_TRUE( 3 > converteStringData(dataIn, &data1));
	
}

