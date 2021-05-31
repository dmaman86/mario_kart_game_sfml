

#include "Sounds.h"

Sounds &Sounds::instance() {
    static Sounds  inst;
    return inst;
}

Sounds::Sounds() {


}
