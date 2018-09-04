                                                                /**********************PROGRAMME DU BOUCLIER FINAL. SYSTEME DE SAISIE : CLAVIER**********************/


#include <Servo.h>
Servo Angulaire;
char input, DemandeArret, OptionArret;
int AngleAct, Angle, i;



                                                    /********DECLARATION DES FONCTIONS DE MISE, LEVER ET ARRET D'URGENCE DU BOUCLIR********/

             /**MISE DU BOUCLIER**/
void Set() {
  while(Angle > 5 && DemandeArret != 'a') {                            //Permet de faire la fermeture du bouclier sur une durée de ~2Sec
            DemandeArret = Serial.read();
            Angle = Angle - 1; 
            Angulaire.write(Angle);
            delay(100);
            Serial.println(Angle);
  }

  if(DemandeArret == 'a') {
            Serial.println("Pour ouvrir le bouclier, appuyez sur 'o' et pour le fermer, appuyez sur 'f'");
            Arret();    
  } else {
            Angulaire.write(Angle); 
  }
  
}


                /**RETRAIT DU BOUCLIER**/
void Remove() {
  while(Angle < 99 && DemandeArret != 'a') {                           //Permet de faire l'ouverture du bouclier sur une durée de ~2Sec
            DemandeArret = Serial.read();
            Angle = Angle + 1; 
            Angulaire.write(Angle);
            delay(100);
            Serial.println(Angle);
  }

  if(DemandeArret == 'a') {
            Serial.println("Pour ouvrir le bouclier de 10°, appuyez sur 'o' et pour le fermer de 10°, appuyez sur 'f'");
            Arret();      
  } else {
            Angulaire.write(Angle); 
  }
  
}

                /**ARRET D'URGENCE DU BOUCLIER**/
void Arret(){
            delay(5000);
            OptionArret = Serial.read();
            
            switch (OptionArret) {
              case 'o': 
                for(i = 1; i <= 10; i = i + 1){
                  Angle = Angle + 1;
                  Angulaire.write(Angle); 
                  Serial.println(Angle);
                  delay(100);
                }
               break;

               case'f':
                for(i = 1; i <= 10; i = i + 1){
                  Angle = Angle - 1;
                  Angulaire.write(Angle); 
                  Serial.println(Angle);
                  delay(100);
                }
               break;

               default: 
               break;      
            }
            Serial.println("Appuyez sur 's' pour mettre le bouclier et sur 'r' pour l'enlever");
            DemandeArret = 'p';                                                                 //Permet de quitter la boucle arrêt et de revenir dans la boucle loop. 
}



                                                                            /********PROGRAMME********/
                                                                            
                /**INITIALISATION DES VARIABLES ET DES PARAMETRES DU PROGRAMME**/
void setup() {

  Serial.begin(9600);
  Angulaire.attach(9);
  Serial.println("Appuyer sur la lettre 's' pour mettre le bouclier.\nAppuyer sur la lettre 'r' pour enlever le bouclier. \nPendant le mouvement, appuyer sur la lettre 'a' pour faire un arrêt d'urgence.");
  Angle = 5;
  Angulaire.write(Angle);
  
}



                /**LES INSTRUCTIONS DU PROGRAMME**/
void loop() {

  if ( Serial.available() > 0) {                                                           //Lance le programme seulement s'il y a une saisie

    input = Serial.read();                                                                 //La variable input contiendra la saisie clavier (caractère)

    switch (input) {

      case 's' :
        if (Angle <= 10) {
          Serial.println("\nLe bouclier est déjà mis, pour l'enlever appuyer sur la lettre 'r'.");
        } else {
          Set();
        }
        break;

      case 'r' :
        if (Angle >= 90) {
          Serial.println("\nLe bouclier est déjà enlevé, pour le mettre appuyez sur la lettre 's'.");
        } else {
          Remove();
        }
        break;


      
    }

  }

}
