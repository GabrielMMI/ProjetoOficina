void deletaDados(){
	system("cd ..");
	system("erase database /Q");
}

Proprietario *criaProprietario(){
	Proprietario *prop = (Proprietario *)malloc(sizeof(Proprietario));
	char *cpf = gerador_cpf();
	static int cont = 0;
	itoa(cont, prop->nome, 2);
	strcpy(prop->cpf , cpf);
	free(cpf);
	strcpy(prop->endereco.cidade, "XXXXXX");
	strcpy(prop->endereco.estado, "XXXXXX");
	strcpy(prop->endereco.descricao, "XXXXXX");
	strcpy(prop->telefone.ddd, "XX");
	strcpy(prop->telefone.telefone, "XXXXXXXXX");
	
	cont++;
	
	return prop;
}

Veiculo *criaVeiculo(){
	Veiculo *veic = (Veiculo *)malloc(sizeof(Veiculo));

	char *placa = gerador_placa();
	static int cont = 0;
	itoa(cont, veic->modelo, 2);
	itoa(cont, veic->fabricante, 2);
	strcpy(veic->placa , placa);
	free(placa);
	itoa(cont, veic->chassi, 2);
	itoa(cont, veic->ano, 2);
	
	cont++;
	
	return veic;
}

Manutencao *criaManutencao(){
	Manutencao *manut = (Manutencao *)malloc(sizeof(Manutencao));

	manut->data.dia = 2;
	manut->data.mes = 2;
	manut->data.ano = 2222;

	return manut;
}

