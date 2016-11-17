
char* gerador_cpf() {
    int cpf[11], pesos[11], vetSoma[11], soma, resto, digito,  i;
    char *cpfAux;
    
    // Aloca memória para o cpf
    cpfAux = (char *) malloc(sizeof(char) * 15);
     
    // Gera 9 números aleatórios
    for(i = 0; i < 9; i++) {
        cpf[i] = rand() % 10;
    }
     
    // Cálculo do primeiro dígito verificador
     
    // Gera os 9 pesos
    for(i = 0; i < 9; i++) {
        pesos[i] = 10 - i;
    }
     
    // Multiplica os valores de cada coluna
    for(i = 0; i < 9; i++) {
        vetSoma[i] = cpf[i] * pesos[i];
    }
     
    // Calcula o somatório dos resultados
    soma = 0;
    for(i = 0; i < 9; i++) {
        soma += vetSoma[i];
    }
     
    // Realiza-se a divisão inteira do resultado por 11
    resto = soma % 11;
     
    // Verifica o resto da divisão
    if(resto < 2) {
        digito = 0;
    } else {
        digito = 11 - resto;
    }
     
    // Adiciona o 1º dígito verificador ao cpf
    cpf[9] = digito;
     
    // Cálculo do segundo dígito verificador
     
    // Gera os 10 pesos
    for(i = 0; i < 10; i++) {
        pesos[i] = 11 - i;
    }
     
    // Multiplica os valores de cada coluna
    for(i = 0; i < 10; i++) {
        vetSoma[i] = cpf[i] * pesos[i];
    }
     
    // Calcula o somatório dos resultados
    soma = 0;
    for(i = 0; i < 10; i++) {
        soma += vetSoma[i];
    }
     
    // Realiza-se a divisão inteira do resultado por 11
    resto = soma % 11;
     
    // Verifica o resto da divisão
    if(resto < 2) {
        digito = 0;
    } else {
        digito = 11 - resto;
    }
     
    // Adiciona o 2º dígito verificador ao cpf
    cpf[10] = digito;
    
    cpfAux[0] = cpf[0] + '0';cpfAux[1] = cpf[1]+ '0';cpfAux[2] = cpf[2]+ '0';cpfAux[3] = '.';
    cpfAux[4] = cpf[3]+ '0';cpfAux[5] = cpf[4]+ '0';cpfAux[6] = cpf[5]+ '0';cpfAux[7] = '.';
    cpfAux[8] = cpf[6]+ '0';cpfAux[9] = cpf[7]+ '0';cpfAux[10] = cpf[8]+ '0';cpfAux[11] = '-';
    cpfAux[12] = cpf[9]+ '0';cpfAux[13] = cpf[10]+ '0';
     
    return cpfAux;
}

char* gerador_placa() {
	char *placa;
	
	placa = (char *)malloc(sizeof(char)*9);

	placa[0] = 65 + rand() %90;
	placa[1] = 65 + rand() %90;
	placa[2] = 65 + rand() %90;
	placa[3] = '-';
	placa[4] = '1';
	placa[5] = '2';
	placa[6] = '3';	
	placa[7] = '4';
	placa[8] = '\0';
	
	return placa;
}
