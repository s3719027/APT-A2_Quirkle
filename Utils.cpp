#include "Utils.h"

void changeTileOnBoard( Tile tile ) {
  if ( tile->getColour() == RED ) {
    printf("\033[1;31m");
  } else if ( tile->getColour() == ORANGE ) {
    printf("\033[01;33m");
  } else if ( tile->getColour() == YELLOW ) {
    printf("\033[1;33m");
  } else if ( tile->getColour() == GREEN ) {
    printf("\033[0;32m");
  } else if ( tile->getColour() == BLUE ) {
    printf("\033[0;34m");
  } else if ( tile->getColour() == PURPLE ) {
    printf("\033[0;45m");
  }

  if ( tile->getShape() == CIRCLE ) {
    printf("⬤");
  } else if ( tile->getShape() == STAR_4 ) {
    printf("🟄");
  } else if ( tile->getShape() == DIAMOND ) {
    printf("◆");
  } else if ( tile->getShape() == SQUARE ) {
    printf("◼");
  } else if ( tile->getShape() == STAR_6 ) {
    printf("🟌");
  } else if ( tile->getShape() == CLOVER ) {
    printf("🍀");
  }
  printf("\033[0m");
}
