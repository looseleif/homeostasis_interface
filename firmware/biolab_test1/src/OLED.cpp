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

void oled::printGrip(void) {

    for(int i=0;i<2;i++){
    
        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);

        String myString = "grip\ndemo\nselected";

        for(uint8_t i = 0; i<myString.length(); i++){
            _screen->write(myString[i]);
        }

        _screen->display();
        delay(500);
        this->clearAll();

    }

}

void oled::testdrawcircle(void) {
for (uint8_t i=0; i<_screen->height()/2; i+=2) {
    _screen->drawCircle(_screen->width()/2, _screen->height()/2, i, WHITE);
    _screen->display();
}
}

void oled::testdrawrect(void) {
for (int16_t i=0; i<_screen->height()/2; i+=2) {
    _screen->drawRect(i, i, _screen->width()-2*i, _screen->height()-2*i, WHITE);
    _screen->display();
}
}

void oled::testdrawline() {  
for (int16_t i=0; i<_screen->width(); i+=4) {
    _screen->drawLine(0, 0, i, _screen->height()-1, WHITE);
    _screen->display();
}
for (int16_t i=0; i<_screen->height(); i+=4) {
    _screen->drawLine(0, 0, _screen->width()-1, i, WHITE);
    _screen->display();
}
delay(250);

_screen->clearDisplay();
for (int16_t i=0; i<_screen->width(); i+=4) {
    _screen->drawLine(0, _screen->height()-1, i, 0, WHITE);
    _screen->display();
}
for (int16_t i=_screen->height()-1; i>=0; i-=4) {
    _screen->drawLine(0, _screen->height()-1, _screen->width()-1, i, WHITE);
    _screen->display();
}
delay(250);

_screen->clearDisplay();
for (int16_t i=_screen->width()-1; i>=0; i-=4) {
    _screen->drawLine(_screen->width()-1, _screen->height()-1, i, 0, WHITE);
    _screen->display();
}
for (int16_t i=_screen->height()-1; i>=0; i-=4) {
    _screen->drawLine(_screen->width()-1, _screen->height()-1, 0, i, WHITE);
    _screen->display();
}
delay(250);

_screen->clearDisplay();
for (int16_t i=0; i<_screen->height(); i+=4) {
    _screen->drawLine(_screen->width()-1, 0, 0, i, WHITE);
    _screen->display();
}
for (int16_t i=0; i<_screen->width(); i+=4) {
    _screen->drawLine(_screen->width()-1, 0, i, _screen->height()-1, WHITE); 
    _screen->display();
}
delay(250);
}

void oled::clearAll(){

    _screen->clearDisplay();
    _screen->display();

}

void oled::printDemoMenu(){

    for(int i=0;i<2;i++){

    _screen->setTextSize(2);
    _screen->setTextWrap(true);
    _screen->setTextColor(WHITE);
    _screen->setCursor(0,0);
    
    }

    String myString = "affector:\n\n[ ] grip\n[ ] direct\n[ ] sense";

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

    String myString = "port:\n\n[ ] CON1\n[ ] CON2\n[ ] CON3";

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

void oled::printScore(uint8_t the_score){

    for(int i=0;i<2;i++){

        _screen->setTextSize(2);
        _screen->setTextWrap(true);
        _screen->setTextColor(WHITE);
        _screen->setCursor(0,0);
    
    }

    if(the_score>5){

        String myString = "YOU WIN!";

        for(uint8_t i = 0; i<myString.length(); i++){
            _screen->write(myString[i]);
        }

        _screen->display();

        delay(1000);

    } else {

        String myString = "YOU LOSE!";

        for(uint8_t i = 0; i<myString.length(); i++){
            _screen->write(myString[i]);
        }

        _screen->display();

        delay(1000);

    }
    

    _screen->clearDisplay();

    delay(500);

}