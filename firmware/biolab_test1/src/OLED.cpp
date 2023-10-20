#include <oled.h>

oled::oled(menu *ptr){

    _oled_menu_ptr = ptr;
    ssd1327SPIInit(OLED_128x128, OLED_DC, OLED_CS, OLED_RST, 0, 0, 36000000);
}

void oled::bootingPrint(void) {
    
    
    int num_words = 2;
    char * words[num_words] = {"booting", "device"};
    int letters[num_words] = {9, 8};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }

    delay(750);

}

void oled::resetPrint(void) {
    
    int num_words = 2;
    char * words[num_words] = {"device", "reset"};
    int letters[num_words] = {8, 7};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }

    // ssd1327WriteString(0,4, "device", FONT_LARGE, 15, -1);
    // ssd1327WriteString(0,20, "reset", FONT_LARGE, 15, -1);
    delay(750);

}

void oled::pleaseWaitPrint(void) {

    int num_words = 2;
    char * words[num_words] = {"please", "wait"};
    int letters[num_words] = {8, 6};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }

    // ssd1327WriteString(0,4, "please", FONT_LARGE, 15, -1);
    // ssd1327WriteString(0,20, "wait", FONT_LARGE, 15, -1);
    delay(500);

}

void oled::goingHomePrint() {
    
    int num_words = 2;
    char * words[num_words] = {"going", "home"};
    int letters[num_words] = {7, 6};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }
    delay(500);

}

void oled::clear(){

    ssd1327Fill(0x0);

}

void oled::printGameMenu(){

    int num_words = 1;
    char * words[num_words] = {"game:"};
    int letters[num_words] = {7};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }
    ssd1327WriteString(0,32, "^ ZONE", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,48, "< MEMORY", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,64, "> CHASE", FONT_LARGE, 15, -1);

}

void oled::printAffectorMenu(){

    int num_words = 1;
    char * words[num_words] = {"device:"};
    int letters[num_words] = {9};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }
    delay(100);
    ssd1327WriteString(0,32, "", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,48, "< DIRECT", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,64, "> FIXATE", FONT_LARGE, 15, -1);

}

void oled::printPortMenu(){
    
    int num_words = 1;
    char * words[num_words] = {"port:"};
    int letters[num_words] = {7};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }
    delay(100);
    ssd1327WriteString(0,32, "^ MIDDLE", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,48, "< LEFT", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,64, "> RIGHT", FONT_LARGE, 15, -1);

}

void oled::printAdditionMenu(){
    
    int num_words = 1;
    char * words[num_words] = {"append?"};
    int letters[num_words] = {9};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }
    delay(100);
    ssd1327WriteString(0,32, "", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,48, "< YES", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,64, "> NO", FONT_LARGE, 15, -1);

}

void oled::playingInfo(int game){

    int num_words = 1;
    char * words[num_words] = {"info:"};
    int letters[num_words] = {7};
    int j =0;

    for(int i = 0; i<num_words; i++){
        char * word = (char*)malloc(letters[i]);
        for(j=0; j<letters[i]; j++){
            strlcpy(word, words[i], j);
            ssd1327WriteString(0,16*i, word, FONT_LARGE, 15, -1);
            delay(50);

        }
        free(word);
        
    }
    delay(100);

    switch (game)
    {
    case 1:
        ssd1327WriteString(0,32, "ZONE", FONT_LARGE, 15, -1);
        break;
    case 2:
        ssd1327WriteString(0,32, "MEMORY", FONT_LARGE, 15, -1);
        break;
    case 3:
        ssd1327WriteString(0,32, "CHASE", FONT_LARGE, 15, -1);
        break;        
    default:
        break;
    }

}

void oled::turnPrint(int turn){
    
    switch (turn)
    {
    case 0:
        ssd1327WriteString(0,4, "turn:", FONT_LARGE, 15, -1);
        ssd1327WriteString(0,32, "CPU", FONT_LARGE, 15, -1);
        delay(750);
        break;
    case 1:
        ssd1327WriteString(0,4, "turn:", FONT_LARGE, 15, -1);
        ssd1327WriteString(0,32, "USER", FONT_LARGE, 15, -1);
        delay(750);
        break;
    default:
        break;
    }

}

void oled::printAgainMenu(){
    
    ssd1327WriteString(0,4, "retry?", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,32, "", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,48, "< YES", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,64, "> NO", FONT_LARGE, 15, -1);

}

void oled::printGameOver(){
    
    ssd1327WriteString(0,4, "game", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,20, "over", FONT_LARGE, 15, -1);
    delay(750);

}

void oled::printWin(){
    
    ssd1327WriteString(0,50, "you win!", FONT_LARGE, 15, -1);
    delay(750);
    
}

void oled::printNumber(int score){

    ssd1327WriteString(0,5, "score:", FONT_LARGE, 15, -1);
    ssd1327WriteString(0,37, (char *)numberWords[score], FONT_LARGE, 15, -1);
    delay(1000);

}