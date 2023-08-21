#include <oled.h>

oled::oled(menu *ptr){
    _oled_menu_ptr = ptr;
    _screen = &screen;
    _screen->begin();
    _screen->clearDisplay();
    _screen->setRotation(0);
}

void oled::sendString(String toSend) {
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,0);
    for(uint8_t i = 0; i<toSend.length(); i++){
        _screen->write(toSend[i]);
        _screen->display();
    }
}

void oled::bootingPrint(void) {
    
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,0);
    String myString = "booting\ndevice";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
        _screen->display();
    }
}

void oled::rebootingPrint(void) {
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,0);
    String myString = "reboot";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
        _screen->display();
    }
}

void oled::pleaseWaitPrint(void) {
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,0);
    String myString = "please\nwait";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
    delay(500);
    this->clearAll();
}

void oled::clearAll(){
    _screen->clearDisplay();
    _screen->display();
}

void oled::printGameMenu(){
    for(int i=0;i<2;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "game:\n\n[ ] zone\n[ ] memory[ ] chase\n";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
}

void oled::printDemoMenu(){
    for(int i=0;i<2;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "affector:\n\n[ ] sense\n[ ] direct\n[ ] fixate";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
}

void oled::printDeviceMenu(){
    for(int i=0;i<2;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "port:\n\n[ ] LEFT\n[ ] MIDDLE\n[ ] RIGHT";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
}

void oled::printAdditionMenu(){
    for(int i=0;i<1;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "ready?\n\n[ ] YES\n[ ] NO";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();

}

void oled::printAgainMenu(){
    for(int i=0;i<1;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "again?\n\n[ ] YES\n[ ] NO";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
}

void oled::printSelector(int prev, int next, bool clear){
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(BLACK);
    _screen->setCursor(0,0);
    String myString = "\n\n";
    for(int i = 0; i<prev; i++){
        myString += "\n";
    }
    myString+=" x ";
    for(int i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
    if(!clear){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
        myString = "\n\n";
        for(int i = 0; i<next; i++){
            myString += "\n";
        }
        myString+="[x]";
        for(int i = 0; i<myString.length(); i++){
            _screen->write(myString[i]);
        }
        _screen->display();
    }
}

void oled::printGameOver(){
    for(int i=0;i<2;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "GAME\nOVER";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
}

void oled::printWin(){
    for(int i=0;i<2;i++){
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    }
    String myString = "YOU WIN!";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
    delay(1000);
    _screen->clearDisplay();
}

void oled::printLose(){
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,0);
    String myString = "YOU LOSE!";
    for(uint8_t i = 0; i<myString.length(); i++){
        _screen->write(myString[i]);
    }
    _screen->display();
    delay(1000);
    _screen->clearDisplay();
}

void oled::printNumber(int score){
    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,3);
    _screen->println("score:\n");
    _screen->println(numberWords[score]);
    _screen->display();
    delay(1000);
    _screen->clearDisplay();
}