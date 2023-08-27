#ifndef _MENU_H_
#define _MENU_H_

#include <mbed.h>

class Menu {
private:
  enum class Page : uint8_t { VALUES };

  Page currentPage = Page::VALUES;

  void drawNumber(
      const int x, const int line, const char * format, const double data);

public:
  Menu();

  void update(int knobMovement);
  void render();
};

#endif /* _MENU_H_ */