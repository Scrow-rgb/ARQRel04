int X;         // Entrada A
int Y;         // Entrada B
int S;         // Saída

int F0 = 10;    // Pino 10
int F1 = 11;    // Pino 11
int F2 = 12;    // Pino 12
int F3 = 13;    // Pino 13

void umL()      { S = 0xF;      }       // 1 Lógico
void copiaA()   { S = X;        }       // A
void copiaB()   { S = Y;        }       // B
void AB()       { S = X & Y;    }       // AB
void zeroL()    { S = 0x0;      }       // 0 Lógico
void AxB()      { S = X ^ Y;    }       // A⊕B
void AoB()      { S = X | Y;    }       // A+B
void AnB()      { S = ~X & Y;   }       // A'B
void Bn()       { S = ~Y & 0xF; }       // B'
void ABn()      { S = X & ~Y;   }       // AB'
void AnoB()     { S = ~X | Y;   }       // A'+ B
void An()       { S = ~X & 0xF; }       // A’
void AoBn()     { S = X | ~Y;   }       // A+B'
void nAxB()     { S = ~(X ^ Y); }       // (A⊕B)'
void nAoB()     { S = ~(X | Y); }       // (A+B)’
void nAeB()     { S = ~(X & Y); }       // (AB)'

void (*operacoes[16])() = { An, nAoB, AnB, zeroL, nAeB, Bn, AxB, ABn, AnoB, nAxB, copiaB, AB, umL, AoBn, AoB, copiaA }; // Ordem das operacões seguindo a tabela.

int converteInteiro(char C)    // Hexadecimal para inteiro.
{
    int Z = 0;
    if(C >= 65 && C <= 70) { Z = C - '7'; }  // De A até F.
    else { Z = C - '0'; }
    return Z; 
}

void setup()
{
        Serial.begin(9600);         // Comunicação com o serial.
        pinMode(10, OUTPUT);        // Saída 10
        pinMode(11, OUTPUT);        // Saída 11
        pinMode(12, OUTPUT);        // Saída 12
        pinMode(13, OUTPUT);        // Saída 13 
}

void loop()
{
        char c[10];             // Vetor que irá armazenar os dados preenchidos pelo usuário.
        
        String memoria[] =      // Vetor memória pré-preenchido.
        { 
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1",
                "-1","-1","-1","-1","-1","-1","-1","-1","-1","-1"
        };
        
        int i = 4;
  
        String OP = "0";
        
        do
        {
                if(Serial.available() > 0)
                {
                        OP = Serial.readString();
                        
                        if(!OP.equals("FIM")) 
                        { 
                                OP.toCharArray(c,OP.length() + 1);
                                
                                X = converteInteiro(c[0]);              // → X ← Y W
                                Y = converteInteiro(c[1]);              // X → Y ← W
                                
                                operacoes[converteInteiro(c[2])]();       // X Y → W ←

                                memoria[i] = OP;
                                memoria[0] = i;
                                memoria[1] = String(S);
                                memoria[2] = c[0];
                                memoria[3] = c[1];
                                i++;
                                
                                int j = 0;

                                digitalWrite(F3, S & 0x8);
                                digitalWrite(F2, S & 0x4);
                                digitalWrite(F1, S & 0x2);
                                digitalWrite(F0, S & 0x1);

                                Serial.print("> ");
                                while(!memoria[j].equals("-1"))
                                {
                                        Serial.print(" ");
                                        Serial.print(memoria[j]);
                                        j++;
                                }
                                Serial.println();                          
                        }
                }
        }
        while(!OP.equals("FIM"));
  
        Serial.println("Programa encerrado.");
}
