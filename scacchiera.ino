//A2 B2 A1 B1 schema dei pulsanti che andranno sostituiti con dei sensori magnetici
int a_1=1;
int colonne_app,righe_app,pos=0,promotion=-1,temp=0,temp_col1,temp_righe1; //interi per colonne e righe nello switch case e per sapere o meno se è una promozione
char pos1,pos2; //valore precedente e attuale della colonna
int posi1,posi2;  //valore precedente e attuale della riga
//configurazione pulsanti, andrà implementato un'altro file dato che ci saranno 64 sensori
int a1=4;
int a2=2;
int b1=3;
int b2=5;
const int n=2;
const int m=2;
//scacchiere sotto forma di matrici attuale e di appoggio per vedere cosa è cambiato
int scacchiera [n][m]={ {0,0}, 
                        {2,9}
                        };
int appoggio [n][m]={   {0,0}, 
                        {2,9}
                        };


void Elimina()
{

	int i,j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
		{
      if(scacchiera[i][j]==-1)
			  scacchiera[i][j]=0;
		}
    Copy();
}

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
    
  }
  else{
    temp=scacchiera[1][0];
    Serial.print("temppp: ");
    Serial.println(temp);
    scacchiera[1][0]=0;
  }
  
  if(!digitalRead(a2)==0){
    
  }
  else{
    temp=scacchiera[0][0];
    scacchiera[0][0]=0;
  }
  if(!digitalRead(b1)==0){
   
  }
  else{
    temp=scacchiera[1][1];
    scacchiera[1][1]=0;
  }
  if(!digitalRead(b2)==0){
   
  }
  else{
    temp=scacchiera[0][1];
    scacchiera[0][1]=0;
  }
    
  return;
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
    Serial.println(digitalRead(a1));
    Serial.println(digitalRead(a2));
    Serial.println(digitalRead(b1));
    Serial.println(digitalRead(b2));
    Serial.println(" ");
    Serial.println(" ");
}

//calcola le coordinate iniziali
void coordinate(int colonne, int righe){
  temp_col1=colonne;
  temp_righe1=righe;
  switch(colonne){
    case 0: 
      pos1='a';
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
      pos1='b';
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
  switch(temp){
    case 1:
      break;
    case 2:
      Serial.print("N");
      break;
    case 3:
      Serial.print("B");
      break;
    case 5:
      Serial.print("R");
      break;
    case 6:
      Serial.print("K");
      break;
    case 9:
      Serial.print("Q");
      break;
    

  }
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
      pos2='a';
      posi2=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      } 
      if(posi1==7 && posi2==8)
        checkpromotion();
      else 
        stampacoordinate();
      scacchiera[righe][colonne]=temp;
      pos=0;
      temp=0;
      return;
    case 1: 
      pos2='b';
      posi2=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      if(posi1==7 && posi2==8)
        checkpromotion();
      else 
        stampacoordinate();
      scacchiera[righe][colonne]=temp;
      pos=0;
      temp=0;
      return;
  }
}

void riempi_temp()
{
	if(digitalRead(a1)==0){
    scacchiera[1][0]=-1;
  }
  
  if(digitalRead(a2)==0){
    scacchiera[0][0]=-1;
  }
 
  if(digitalRead(b1)==0){
   scacchiera[1][1]=-1;
  }
  if(digitalRead(b2)==0){
   scacchiera[0][1]=-1;
  }
}


void setup() {
  //pulsanti che andranno tolti e sostituiti
  pinMode(a1, INPUT);
  pinMode(a2, INPUT);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);

  Serial.begin(115200);
}

void loop() {
  int check;
  if(temp==-1)
    temp=0;
  if(temp==0){
    riempi();
    Elimina();
  }
  else
    riempi_temp();
  check=Controllo();  //restituisce 1 se è stato cambiato qualcosa e se lo è stato calcola cosa
  if (check==1){
    
    if(pos==0)
      coordinate(colonne_app,righe_app);
    else
      coordinate2(colonne_app,righe_app);
    
    Copy();
  }
  Stampa();
  Serial.print("temp: ");
  Serial.println(temp);
  
  delay(3000);
  
  
}
