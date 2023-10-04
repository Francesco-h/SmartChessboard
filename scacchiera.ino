//A2 B2 A1 B1 schema dei pulsanti che andranno sostituiti con dei sensori magnetici

int colonne_app,righe_app,pos=0,promotion=-1; //interi per colonne e righe nello switch case e per sapere o meno se è una promozione
char pos1,pos2; //valore precedente e attuale della colonna
int posi1,posi2;  //valore precedente e attuale della riga
//configurazione pulsanti, andrà implementato un'altro file dato che ci saranno 64 sensori
int a1=10;
int a2=11;
int b1=8;
int b2=9;
const int n=8;
const int m=8;
//scacchiere sotto forma di matrici attuale e di appoggio per vedere cosa è cambiato
int scacchiera [8][8]={ {0,0,0,0,0,0,0,0}, 
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}, 
                        };
int appoggio [8][8]={   {0,0,0,0,0,0,0,0}, 
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0}, 
                        };



//copia i valori della scacchiera attuale con quella di appoggio
void Copy()
{

	int i,j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
		{
			appoggio[i][j] = scacchiera[i][j];
		}
}

//controlla quale pedina stia muovendo
int Controllo()
{
	int i, j,c,d;
  c=colonne_app;
  d=righe_app;
	for (i = 0; i < m; i++){
		for(j = 0; j < n; j++)
		{
			if(appoggio[i][j] != scacchiera[i][j]){
        colonne_app=j;
        righe_app=i;
        return 1;
      }
		}
  } 
     return 0;
}
//riempie la scacchiera a seconda della pedine posizionate
void riempi()
{
	if(!digitalRead(a1)==0){
    scacchiera[1][0]=0;
  }
  else
    scacchiera[1][0]=1;
  
  
  if(!digitalRead(a2)==0){
    scacchiera[1][1]=0;
  }
  else
    scacchiera[1][1]=1;
  
  if(!digitalRead(b1)==0){
    scacchiera[0][0]=0;
  }
  else
    scacchiera[0][0]=1;

  if(!digitalRead(b2)==0){
    scacchiera[0][1]=0;
  }
  else
    scacchiera[0][1]=1;
  
}

//stampa le 2 scacchiere
void Stampa()
{

	int i,j;
	for (i = 0; i < m; i++){
  Serial.println("");
		for(j = 0; j < n; j++)
		{
			Serial.print(scacchiera[i][j]);
      Serial.print("|");
      
		}
  }
    Serial.println("");
    /*Serial.println(" ");
    for (i = 0; i < m; i++)
		  for(j = 0; j < n; j++)
		  {
			  Serial.print(appoggio[i][j]);
      
		  }*/
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
    Serial.println(" ");
}

//calcola le coordinate iniziali
void coordinate(int colonne, int righe){
  switch(colonne){
    case 0: 
      pos1='A';
      posi1=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      if (pos==1)
        return;
      else
      pos=1;
      return;
    case 1: 
      pos1='B';
      posi1=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      if (pos==1)
        return;
      else
        pos=1;
      return;
  }
}

//stampa la notazione smith della mossa
void stampacoordinate(){
  Serial.print(pos1);
  Serial.print(posi1);
  Serial.print(pos2);
  Serial.print(posi2);
  if(promotion==1){
    Serial.print("Q");
    promotion=-1;
  }
  Serial.println("");
  Serial.println("");
}

//commentata vanno creati 2 pulsanti per leggere se o non è una promozione
void checkpromotion(){
    /*if(posi1==7 and posi2==8){
      Serial.println("E' una promozione?");
      while(promotion==-1){
          if(!digitalRead(b1)==0)                 
            promotion=1;
          if(!digitalRead(b2)==0)
            promotion=0;
      }
    }*/
      stampacoordinate();
}

//calcola le coordinate di arrivo della pedina mossa
void coordinate2(int colonne, int righe){
  switch(colonne){
    case 0: 
      pos2='A';
      posi2=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      checkpromotion();
      pos=0;
      return;
    case 1: 
      pos2='B';
      posi2=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      checkpromotion();
      pos=-1;
      return;
  }
}



void setup() {
  //pulsanti che andranno tolti e sostituiti
  pinMode(a1, INPUT_PULLUP);
  pinMode(a2, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int check;
  riempi();
  check=Controllo();  //restituisce 1 se è stato cambiato qualcosa e se lo è stato calcola cosa
  if (check==1){
    
    if(pos==0)
      coordinate(colonne_app,righe_app);
    else
      coordinate2(colonne_app,righe_app);
    if(pos==-1)
      pos++;
    Copy();
  }
  //Stampa();
  
  
}
