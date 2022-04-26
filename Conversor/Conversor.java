import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Conversor
{
	static String mnemonicos(String S) // Retornar a posição da operação conforme a tabela.
	{
		String operacao = "0";
		switch(S)
		{
			case "An":      { operacao = "0"; break; }
			case "nAoB":    { operacao = "1"; break; }
			case "AnB":     { operacao = "2"; break; }
			case "zeroL":   { operacao = "3"; break; }
			case "nAeB":    { operacao = "4"; break; }
			case "Bn":      { operacao = "5"; break; }
			case "AxB":     { operacao = "6"; break; }
			case "ABn":     { operacao = "7"; break; }
			case "AnoB":    { operacao = "8"; break; }
			case "nAxB":    { operacao = "9"; break; }
			case "copiaB":  { operacao = "A"; break; }
			case "AB":      { operacao = "B"; break; }
			case "umL":     { operacao = "C"; break; }
			case "AoBn":    { operacao = "D"; break; }
			case "AoB":     { operacao = "E"; break; }
			case "copiaA":  { operacao = "F"; break; }
		}
		return operacao;
	}

	public static void main (String [] args) throws IOException 
	{ 
		try
		{
			File arquivoULA = new File("testeula.ula");		// Arquivo a ler.
			File arquivoHEX = new File("testeula.hex");		// Arquivo a escrever.

			String X = null;
			String Y = null;
			String W = null;
			
			boolean mod = false;		// Flag para evitar impressões incorretas / desncessárias.
			
			Scanner leitor = new Scanner(arquivoULA);
			FileWriter escritor = new FileWriter(arquivoHEX);

			while(leitor.hasNextLine())		// Continua leitura até o fim do arquivo.
			{
				String linha = leitor.nextLine();
				
				if(!linha.contains("inicio:"))	// Ignora frase inicial.
				{
					switch(linha.substring(0,1))
					{
						case "X": { X = linha.substring(linha.indexOf("=") + 1, linha.indexOf(";"));  break; }
						case "Y": { Y = linha.substring(linha.indexOf("=") + 1, linha.indexOf(";"));  break; }
						case "W": { W = mnemonicos(linha.substring(linha.indexOf("=") + 1, linha.indexOf(";"))); mod = true; break; }
					}
				}
				
				if(X != null && Y != null && W != null && mod) { escritor.write(X+Y+W+"\n"); mod = false; }
			}
			leitor.close();
			escritor.close();
		}
		catch (IOException e) { e.printStackTrace(); }
	}
}
