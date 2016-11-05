<?xml version="1.0"?>

<xsl:stylesheet version = "1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
		<html>
			<head>				
				<title>Relatório de testes</title>
				<link href="bootstrap/css/bootstrap.min.css" rel="stylesheet" media="screen"/>
				<link href="css/style.css" rel="stylesheet" media="screen"/>
				<script src="bootstrap/bootstrap/js/bootstrap.min.js"/>
				<script src="bootstrap/bootstrap/js/npm.js"/>
			</head>
			<body>
			<div class="row">
				<div class = "col-sm-3" id="tela-direita">
					<h1 id="titulo-direita">Relatório de testes</h1>
					<table class="table" id="tabela-direita">
						<tr>
							<td>Número de testes executados:</td>
							<td><xsl:value-of select="testsuites/@tests"/></td>	
						</tr>
						<tr>
							<td>Testes que falharam: </td>					
							<td><xsl:value-of select="testsuites/@failures"/></td>
						</tr>
						<tr>
							<td>Testes desabilitados:</td>	
							<td> <xsl:value-of select="testsuites/@disabled"/></td>
						</tr>
						<tr>
							<td>Erros:</td>	
							<td> <xsl:value-of select="testsuites/@errors"/></td>
						</tr>
						<tr>
							<td>Tempo gasto:</td>	
							<td> <xsl:value-of select="testsuites/@time"/> ms</td>
						</tr>
					</table>
				</div>

				<div class = "col-sm-9" id="tela-esquerda">
					<ul class="list-group">
						<xsl:for-each select="testsuites/testsuite">
							<a href="#" class="list-group-item"><xsl:value-of select="@name"/></a>
						</xsl:for-each>
					</ul>
				</div>
			</div>
			</body>
		</html>
	</xsl:template>
	
</xsl:stylesheet>