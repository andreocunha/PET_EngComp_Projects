//funcao para ler uma digital e verificar se ela esta registrada

int leituraBiometrica() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK){
    return -1;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) {
    return -1;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) {
    digitalWrite(pinoLedVermelho, HIGH);
    delay(1500); //INTERVALO DE 1,5 SEGUNDOS
    digitalWrite(pinoLedVermelho, LOW);
    return -1;
  }
  
  //Encontrou uma digital!
   else {
      return finger.fingerID;
  } 
}
