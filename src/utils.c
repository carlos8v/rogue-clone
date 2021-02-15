#include "nethack.h"

/**
 * Retorna se uma posição está no perímetro passado
 * 
 * @param Position initial
 * @param Position final
 * @param int range
 * @param bool perspective
 * @param bool smooth
 */
bool isInRange(Position initial, Position final, int range, bool perspective, bool smooth) {
  if (smooth)
    return getDistance(initial, final, perspective) <= range;
  else
    return getDistance(initial, final, perspective) < (range + 1);
}

/**
 * Retorna a distância entre dois pontos
 *
 * @param Position* initial
 * @param Position* final
 * @param bool perspective
 * @returns double
 */
double getDistance(Position initial, Position final, bool perspective) {
  int offset = perspective ? 2 : 1;
  return sqrt(pow(final.x - initial.x, 2) + pow((final.y - initial.y) * offset, 2));
}