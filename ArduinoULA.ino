char A;     // Entrada A
char B;     // Entrada B
char R;     // Saída
char OP;    // Operação
int Z;

int F0 = 10;
int F1 = 11;
int F2 = 12;
int F3 = 13;

int vetorInstrucoes[100];

void umL() { R = 0xF; }             // 1 Lógico
void copiaA() { R = A; }            // A
void copiaB() { R = B; }            // B
void AB() { R = A & B; }            // AB
void zeroL() { R = 0x0; }           // 0 Lógico
void AxB() { R = A ^ B; }           // A⊕B
void AoB() { R = A | B; }           // A+B
void AnB() { R = ~A & B; }          // A'B
void Bn(){ R = ~B & 0xF; }          // B'
void ABn() { R = A & ~B; }          // AB'
void AnoB(){ R = ~A | B; }          // A'+ B
void An() { R = ~A & 0xF; }         // A’
void AoBn() { R = A | ~B; }         // A+B'
void nAxB(){ R = ~(A ^ B); }        // (A⊕B)'
void nAoB() { R = ~(A | B); }       // (A+B)’
void nAeB() { R = ~(A & B); }       // (AB)'

void (*operacoes[16])() = { An, nAoB, AnB, zeroL, nAeB, Bn, AxB, ABn, AnoB, nAxB, copiaB, AB, umL, AoBn, AoB, copiaA }; // Ordem das operacões seguindo a tabela.

int converteInteiro(char C)    // Hexadecimal para inteiro.
{
    int S = 0;
    if(C >= 65 && C <= 70) { S = C - '7'; }  // De A/a até F/f.
    else { S = C - '0'; }
    return S;
}

void setup()
{
    Serial.begin(9600);         // Comunicação com o serial.
    pinMode(10, OUTPUT);        // Saída 10
    pinMode(11, OUTPUT);        // Saída 11
    pinMode(12, OUTPUT);        // Saída 12
    pinMode(13, OUTPUT);        // Saída 13
    vetorInstrucoes[0] = 0;     // Posição da primeira operação;
}

void loop()
{
    if(Serial.available())
    {
        String leitor = Serial.readString();

        A = converteInteiro(leitor.charAt(0));      // → A ← B OP
        B = converteInteiro(leitor.charAt(1));      // A → B ← OP
        OP = converteInteiro(leitor.charAt(2));     // A B → OP ←
        Z = leitor.toInt();


        if(Serial.read() == '\n')
        {
            (*operacoes[OP])();         // Após detectar o ENTER, se iniciam os cálculos.

            vetorInstrucoes[1] = R;     // Resultado.
            vetorInstrucoes[2] = A;     // Valor de A.
            vetorInstrucoes[3] = B;     // Valor de B.

            int i = 3;
            bool preenchido = true;


            do
            {
                i++;
                if(vetorInstrucoes[i] == NULL)
                {
                    vetorInstrucoes[0] = i++;   // Preencher a primeira posição do vetor com o valor da posição da operação.
                    vetorInstrucoes[i] = Z;    // Preencher com os dados informados pelo usuário.
                    preenchido = false;
                }
            }
            while(!preenchido); // Procura pela primeiro endereço vazio do vetor.

            Serial.print("\n\tResultado: ");
            Serial.print((bool)(R & 0x8));
            Serial.print((bool)(R & 0x4));
            Serial.print((bool)(R & 0x2));
            Serial.print((bool)(R & 0x1));

            digitalWrite(F3, R & 0x8);
            digitalWrite(F2, R & 0x4);
            digitalWrite(F1, R & 0x2);
            digitalWrite(F0, R & 0x1);

            Serial.print("\n\t ‣ Cálculos realizados com sucesso, verifique os LEDs.\n");
        }
        Serial.print("\n\n\tFim.\n");
    }
}
