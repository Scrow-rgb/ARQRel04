import java.io.File;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.IOException;

public class Conversor
{
        static char mnemonicos(String S)
        {
                char operacao = '0';
                switch(S)
                {
                        case "An":      { operacao = '0'; break; }
                        case "nAoB":    { operacao = '1'; break; }
                        case "AnB":     { operacao = '2'; break; }
                        case "zeroL":   { operacao = '3'; break; }
                        case "nAeB":    { operacao = '4'; break; }
                        case "Bn":      { operacao = '5'; break; }
                        case "AxB":     { operacao = '6'; break; }
                        case "ABn":     { operacao = '7'; break; }
                        case "AnoB":    { operacao = '8'; break; }
                        case "nAxB":    { operacao = '9'; break; }
                        case "copiaB":  { operacao = 'A'; break; }
                        case "AB":      { operacao = 'B'; break; }
                        case "umL":     { operacao = 'C'; break; }
                        case "AoBn":    { operacao = 'D'; break; }
                        case "AoB":     { operacao = 'E'; break; }
                        case "copiaA":  { operacao = 'F'; break; }
                }
                return operacao;
        }
        public static void main (String [] args) throws IOException 
        { 
                
        }
}
