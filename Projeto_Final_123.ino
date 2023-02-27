
//Bibliotecas utilizadas no Projeto
#include <SPI.h>
#include <MFRC522.h>


//Pinos
#define SS_PIN 10
#define RST_PIN 2
int Vermelho = 5;





String IDtag = ""; //Variável que armazenará o ID da Tag
bool Permitido = false; //Variável que verifica a permissão 

//Vetor responsável por armazenar os ID's das Tag's cadastradas
String TagsCadastradas[] = {"baaeb115", 
                            "47ad0c207380",
                            "4ae1c8a646984"};

MFRC522 LeitorRFID(SS_PIN, RST_PIN);    // Cria uma nova instância para o leitor e passa os pinos como parâmetro


void setup() {
        Serial.begin(9600);             // Inicializa a comunicação Serial
        SPI.begin();                    // Inicializa comunicacao SPI 
        LeitorRFID.PCD_Init();          // Inicializa o leitor RFID
        pinMode(Vermelho, OUTPUT);  // Declara o pino do led vermelho como saída
}

void loop() {  
  Leitura();  //Chama a função responsável por fazer a leitura das Tag's
}

void Leitura(){

        IDtag = ""; //Inicialmente IDtag deve estar vazia.
        
        // Verifica se existe uma Tag presente
        if ( !LeitorRFID.PICC_IsNewCardPresent() || !LeitorRFID.PICC_ReadCardSerial() ) {
            delay(50);
            return;
        }
        
        // Pega o ID da Tag através da função LeitorRFID.uid e Armazena o ID na variável IDtag        
        for (byte i = 0; i < LeitorRFID.uid.size; i++) {        
            IDtag.concat(String(LeitorRFID.uid.uidByte[i], HEX));
        }        
        
        //Compara o valor do ID lido com os IDs armazenados no vetor TagsCadastradas[]
        for (int i = 0; i < (sizeof(TagsCadastradas)/sizeof(String)); i++) {
          if(  IDtag.equalsIgnoreCase(TagsCadastradas[i])  ){
              Permitido = true; //Variável Permitido assume valor verdadeiro caso o ID Lido esteja cadastrado
          }
        }       

        if(Permitido == true)
        acessoLiberado();  
         //Se a variável Permitido for verdadeira será chamada a função acessoLiberado()      
           
        else acessoNegado(); //Se não será chamada a função acessoNegado()

        delay(1000); //aguarda 1 segundo para efetuar uma nova leitura
         
}

void acessoLiberado(){

  Serial.println("Acesso Liberado:  " + IDtag); //Exibe a mensagem de informação
    efeitoPermitido();  //Chama a função efeitoPermitido()
    Permitido = false;  //zera a variável Permitido como false novamente
 
}

void acessoNegado(){
  Serial.println("Acesso Negado:  " + IDtag); //Exibe a mensagem "Tag NAO Cadastrada" e o ID da tag cadastrada
  efeitoNegado(); //Chama a função efeitoNegado()
}

void efeitoPermitido(){  
  int qtd_bips = 10;  //definindo a quantidade de bips
  for(int j=0; j<qtd_bips; j++){  

     digitalWrite( Vermelho , HIGH);
     delay(500);
     digitalWrite( Vermelho , LOW ) ;
     delay(500);
  }
}

void efeitoNegado(){  
  int qtd_bips = 10;  //definindo a quantidade de bips
  for(int j=0; j<qtd_bips; j++){  

     digitalWrite( Vermelho , HIGH);
     delay(100);
     digitalWrite( Vermelho , LOW ) ;
     delay(100);
  }
}


  


  
