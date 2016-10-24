#ifndef __ALE_C_WRAPPER_H__
#define __ALE_C_WRAPPER_H__

#include <ale_interface.hpp>

extern "C" {

// Declares int rgb_palette[256]
ALEInterface *ALEInterface_new() {return new ALEInterface();}
void ALEInterface_delete(ALEInterface *ale) {delete ale;}
const char *ALEInterface_getString(ALEInterface *ale, const char *key) {return ale->getString(key).c_str();}
int ALEInterface_getInt(ALEInterface *ale, const char *key) {return ale->getInt(key);}
int ALEInterface_getBool(ALEInterface *ale, const char *key) {return ale->getBool(key);}
float ALEInterface_getFloat(ALEInterface *ale, const char *key) {return ale->getFloat(key);}
void ALEInterface_setString(ALEInterface *ale, const char *key, const char *value) {ale->setString(key, value);}
void ALEInterface_setInt(ALEInterface *ale, const char *key, int value) {ale->setInt(key, value);}
void ALEInterface_setBool(ALEInterface *ale, const char *key, int value) {ale->setBool(key, value);}
void ALEInterface_setFloat(ALEInterface *ale, const char *key, float value) {ale->setFloat(key, value);}
void ALEInterface_loadROM(ALEInterface *ale, const char *rom_file) {ale->loadROM(rom_file);}
int ALEInterface_act(ALEInterface *ale, int action) {return ale->act((Action)action);}
int ALEInterface_game_over(ALEInterface *ale) {return ale->game_over();}
void ALEInterface_reset_game(ALEInterface *ale) {ale->reset_game();}
void ALEInterface_getLegalActionSet(ALEInterface *ale, int *actions) {
  ActionVect action_vect = ale->getLegalActionSet();
  for (unsigned int i = 0; i < ale->getLegalActionSet().size(); i++) {
    actions[i] = action_vect[i];
  }
}
int ALEInterface_getLegalActionSize(ALEInterface *ale) {return ale->getLegalActionSet().size();}
void ALEInterface_getMinimalActionSet(ALEInterface *ale, int *actions) {
  ActionVect action_vect = ale->getMinimalActionSet();
  for (unsigned int i = 0; i < ale->getMinimalActionSet().size(); i++) {
    actions[i] = action_vect[i];
  }
}
int ALEInterface_getMinimalActionSize(ALEInterface *ale) {return ale->getMinimalActionSet().size();}
int ALEInterface_getFrameNumber(ALEInterface *ale) {return ale->getFrameNumber();}
int ALEInterface_lives(ALEInterface *ale) {return ale->lives();}
int ALEInterface_getEpisodeFrameNumber(ALEInterface *ale) {return ale->getEpisodeFrameNumber();}
void ALEInterface_getRAM(ALEInterface *ale, unsigned char *ram) {
  unsigned char *ale_ram = ale->getRAM().array();
  size_t size = ale->getRAM().size();
  memcpy(ram, ale_ram, sizeof(unsigned char)*size);
}
int ALEInterface_getRAMSize(ALEInterface *ale) {return ale->getRAM().size();}
void ALEInterface_getScreen(ALEInterface *ale, unsigned char *screen_data) {
  size_t w = ale->getScreen().width();
  size_t h = ale->getScreen().height();
  pixel_t *ale_screen_data = (pixel_t *)ale->getScreen().getArray();
  memcpy(screen_data, ale_screen_data, sizeof(pixel_t)*w*h);
}
int ALEInterface_getScreenWidth(ALEInterface *ale) {return ale->getScreen().width();}
int ALEInterface_getScreenHeight(ALEInterface *ale) {return ale->getScreen().height();}
void ALEInterface_getScreenGrayscale(ALEInterface *ale, unsigned char *output_buffer) {
  size_t w = ale->getScreen().width();
  size_t h = ale->getScreen().height();
  size_t screen_size = w*h;
  pixel_t *ale_screen_data = ale->getScreen().getArray();
  ale->theOSystem->colourPalette().applyPaletteGrayscale(output_buffer, ale_screen_data, screen_size);
}
void ALEInterface_getScreenRGB(ALEInterface *ale, unsigned char *output_buffer) {
  size_t w = ale->getScreen().width();
  size_t h = ale->getScreen().height();
  size_t screen_size = w*h;
  pixel_t *ale_screen_data = ale->getScreen().getArray();
  ale->theOSystem->colourPalette().applyPaletteRGB(output_buffer, ale_screen_data, screen_size * 3);
}
void ALEInterface_saveState(ALEInterface *ale) {ale->saveState();}
void ALEInterface_loadState(ALEInterface *ale) {ale->loadState();}
ALEState* ALEInterface_cloneState(ALEInterface *ale) {return new ALEState(ale->cloneState());}
void ALEInterface_restoreState(ALEInterface *ale, ALEState* state) {ale->restoreState(*state);}
ALEState* ALEInterface_cloneSystemState(ALEInterface *ale) {return new ALEState(ale->cloneSystemState());}
void ALEInterface_restoreSystemState(ALEInterface *ale, ALEState* state) {ale->restoreSystemState(*state);}
void ALEState_delete(ALEState* state) {delete state;}
void ALEInterface_saveScreenPNG(ALEInterface *ale, const char *filename) {ale->saveScreenPNG(filename);}

// Encodes the state as a raw bytestream. This may have multiple '\0' characters
// and thus should not be treated as a C string. Use encodeStateLen to find the length
// of the buffer to pass in, or it will be overrun as this simply memcpys bytes into the buffer.
void ALEState_encodeState(ALEState *state, char *buf, int buf_len);
int ALEState_encodeStateLen(ALEState *state);
ALEState *ALEState_decodeState(const char *serialized, int len);

// 0: Info, 1: Warning, 2: Error
void ALE_setLoggerMode(int mode) { ale::Logger::setMode(ale::Logger::mode(mode)); }
}

#endif
