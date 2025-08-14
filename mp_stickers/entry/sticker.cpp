#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  Image alma; alma.readFromFile("../data/alma.png");
  Image i; i.readFromFile("../data/i.png");
  Image penguin; penguin.readFromFile("../data/penguin.png");

  StickerSheet final(alma, 4);

  final.addSticker(i, 100, -225);
  final.addSticker(i, 580, -225);
  final.addSticker(penguin, 352, -48);

  Image result = final.render();
  result.writeToFile("../data/myImage.png");

  return 0;
}
