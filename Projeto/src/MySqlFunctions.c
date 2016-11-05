#include<mysql.h>

int conexao_Banco(HWND hwnd){
    MYSQL conexao;
    mysql_init(&conexao);
    if ( mysql_real_connect(&conexao, "sql9.freesqldatabase.com", "sql9140988", "QUYb73z1BU", "sql9140988", 3306, NULL, 0) )
    {
        if(mysql_query(&conexao,"SELECT * FROM database")){
            printf("Erro: %s\n",mysql_error(&conexao));
        }

    }
    else
    {
        MessageBox(hwnd, "Falha de conexao\n", "Falha de conexao\n", MB_OK);
    }
    system("PAUSE");
    return(0);
}

