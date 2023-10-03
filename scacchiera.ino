//A2 B2 A1 B1

int colonne_app,righe_app,pos=0;
char pos1,pos2;
int posi1,posi2;
int a1=10;
int a2=11;
int b1=8;
int b2=9;



int scacchiera [2][2]={ {0,0},
                        {0,0} 
                        };
int appoggio [2][2]={ {0,0}, 
                      {0,0}
                      };




void Copy()
{

	int n=2, m=2,i,j;
	for (i = 0; i < m; i++)
		for(j = 0; j < n; j++)
		{
			appoggio[i][j] = scacchiera[i][j];
		}
}

int Controllo()
{
	int i, j,c,d,m=2,n=2;
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

void Stampa()
{

	int n=2, m=2,i,j;
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

void stampacoordinate(){
  Serial.print(pos1);
  Serial.print(posi1);
  Serial.print(pos2);
  Serial.print(posi2);
  Serial.println("");
  Serial.println("");
}

void coordinate2(int colonne, int righe){
  switch(colonne){
    case 0: 
      pos2='A';
      posi2=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      stampacoordinate();
      pos=0;
      return;
    case 1: 
      pos2='B';
      posi2=(2-righe);
      if(pos1==pos2 && posi1==posi2){
        return;
      }
      stampacoordinate();
      pos=-1;
      return;
  }
}



void setup() {
  pinMode(a1, INPUT_PULLUP);
  pinMode(a2, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int check;
  riempi();
  check=Controllo();
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
