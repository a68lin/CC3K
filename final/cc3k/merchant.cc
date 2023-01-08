#include "merchant.h"

merchant::merchant(int x, int y, bool ifCompass): enemy(CharType::Merchant, 40, 70, 5, 4, x, y, false) {}

bool merchant::if_Attack() {
    return ifAttack;
}