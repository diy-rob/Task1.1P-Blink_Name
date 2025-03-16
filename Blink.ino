#define LED LED_BUILTIN  // Use built-in LED

// Timing Constants
#define DOT 250       // Dot duration (·)
#define DASH 750      // Dash duration (−)
#define GAP 250       // Gap between elements in a letter
#define LETTER_GAP 750 // Gap between letters
#define WORD_GAP 1750  // Gap between words

// Morse code lookup table (A-Z)
const char* morseCode[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",  // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."         // S-Z
};

// Function to blink a dot
void dot() {
  digitalWrite(LED, HIGH);
  delay(DOT);
  digitalWrite(LED, LOW);
  delay(GAP);
}

// Function to blink a dash
void dash() {
  digitalWrite(LED, HIGH);
  delay(DASH);
  digitalWrite(LED, LOW);
  delay(GAP);
}

// Function to blink a letter
void blinkLetter(const char* morse) {
  for (int i = 0; morse[i] != '\0'; i++) {
    if (morse[i] == '.') dot();
    else if (morse[i] == '-') dash();
  }
  delay(LETTER_GAP);
}

// Function to blink a name
void blinkName(const char* name) {
  for (int i = 0; name[i] != '\0'; i++) {
    char letter = toupper(name[i]);
    if (letter >= 'A' && letter <= 'Z') {
      blinkLetter(morseCode[letter - 'A']);
    }
    delay(LETTER_GAP);
  }
  delay(WORD_GAP); // Space after name
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter a name:");
}

void loop() {
  if (Serial.available() > 0) {
    char name[20];  // Buffer for user input
    int len = Serial.readBytesUntil('\n', name, sizeof(name) - 1);
    name[len] = '\0';  // Null-terminate string

    Serial.print("Blinking: ");
    Serial.println(name);
    blinkName(name);
  }
}