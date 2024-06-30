#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view.h"

class controller
{
// Q_OBJECT
private:
    View *view;
public:
    controller(View *view);
};

#endif // CONTROLLER_H
