
#include "Fonts.h"

Fonts &Fonts::instance() {
    static Fonts inst;
    return inst;
}

Fonts::Fonts() {

}
