// v1 02/16/10
// v2 10/31/19 ... wow!
#include "PCMmod.h"
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#define CRUSH_SWITCH 8
#define HAT_DECAY_POT 0
#define CLAP_SNARE_FX_DECAY_POT 1
#define GLITCH_POT 4

bool btcrush;
float glitchPitch;
float decay1;
float decay2;
unsigned long currentMillis;
unsigned long pollPrevMillis = 0;
const long pollInterval = 300;

void triggerKick(){
  int sample_size = sizeof(kckClean) - 10;
//  sample_length = (sample_size - (sample_length/1023.0)*sample_size)-10;
//  startGlitchPlayback(kckClean, sample_length, glitchPitch, btcrush);
  startGlitchPlayback(kckClean, sample_size, 1, false);
}

void triggerGet(){
  int sample_size = sizeof(getup);
  int sample_length = sample_size - (decay1*sample_size) - 10;
  startGlitchPlayback(getup, sample_length, glitchPitch, btcrush);
}

void triggerHat(){
  int sample_size = sizeof(hhClean);
  int sample_length = sample_size - (decay2*sample_size) - 10;
  startGlitchPlayback(hhClean, sample_length, glitchPitch + 3, btcrush);
}

void triggerFX(){
  int sample_size = sizeof(fxClean);
  int sample_length = sample_size - (decay1*sample_size) - 10;
  startGlitchPlayback(fxClean, sample_length, glitchPitch, btcrush);
}

void triggerClap2(){
  int sample_size = sizeof(clap);
  int sample_length = (int(decay1 * sample_size))-10;
  startGlitchPlayback(clap, sample_length, glitchPitch, btcrush);
}

void triggerSnare(){
  int sample_size = sizeof(snare);
  int sample_length = (int(decay1 * sample_size))-10;
  startGlitchPlayback(snare, sample_length, glitchPitch, btcrush);
}

void triggerSKick(){
  int sample_size = sizeof(kckClean)/4.0 - 10;
//  sample_length = (sample_size - (sample_length/1023.0)*sample_size)-10;
//  startGlitchPlayback(kckClean, sample_length, glitchPitch, btcrush);
  startGlitchPlayback(kckClean, sample_size, 1, false);
}

void triggerSGet(){
  int sample_size = sizeof(getup)/2.0;
  int sample_length = sample_size - (decay1*sample_size) - 10;
  startGlitchPlayback(getup, sample_length, glitchPitch+1, btcrush);
}

void triggerSHat(){
  int sample_size = sizeof(hhClean)/2.0;
  int sample_length = sample_size - (decay2*sample_size) - 10;
  startGlitchPlayback(hhClean, sample_length, glitchPitch + 4, btcrush);
}

void triggerSFX(){
  int sample_size = sizeof(fxClean)/2.0;
  int sample_length = sample_size - (decay1*sample_size) - 10;
  startGlitchPlayback(fxClean, sample_length, glitchPitch+1, btcrush);
}

void triggerSClap2(){
  int sample_size = sizeof(clap)/2.0;
  int sample_length = (int(decay1 * sample_size))-10;
  startGlitchPlayback(clap, sample_length, glitchPitch+1, btcrush);
}

void triggerSSnare(){
  int sample_size = sizeof(snare)/2.0;
  int sample_length = (int(decay1 * sample_size))-10;
  startGlitchPlayback(snare, sample_length, glitchPitch+1, btcrush);
}

void pollInputs() {
  btcrush = digitalRead(CRUSH_SWITCH);
  analogRead(GLITCH_POT);
  glitchPitch = 5 * (analogRead(GLITCH_POT))/1023 + 1;
  analogRead(CLAP_SNARE_FX_DECAY_POT);
  decay1 = analogRead(CLAP_SNARE_FX_DECAY_POT) / 1053.0;
  analogRead(HAT_DECAY_POT);
  decay2 = analogRead(HAT_DECAY_POT) / 1053.0;
}

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  if (channel == 10) {
    switch (pitch) {
      case byte(46):
        triggerKick();
        break;
      case byte(47):
        triggerGet();
        break;
      case byte(48):
        triggerHat();
        break;
      case byte(49):
        triggerClap2();
        break;
      case byte(50):
        triggerFX();
        break;
      case byte(51):
        triggerSnare();
        break;
      case byte(52):
        triggerSKick();
        break;
      case byte(53):
        triggerSGet();
        break;
      case byte(54):
        triggerSHat();
        break;
      case byte(55):
        triggerSClap2();
        break;
      case byte(56):
        triggerSFX();
        break;
      case byte(57):
        triggerSSnare();
        break;
      default:
        break;
    }
  }
}

void testPot(int pot) {  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(analogRead(pot));
  digitalWrite(LED_BUILTIN, LOW);
  delay(analogRead(pot));
}

void testSwitch() {
  pollInputs();
  digitalWrite(LED_BUILTIN, btcrush);
}

void setup() {
  pinMode(CRUSH_SWITCH, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  MIDI.begin(10);
  MIDI.setHandleNoteOn(handleNoteOn);
}
void loop () {
  currentMillis= millis();
  MIDI.read();
  if (currentMillis - pollPrevMillis >= pollInterval) {
    pollInputs();
    pollPrevMillis = currentMillis;
  }
}



