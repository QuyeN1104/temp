#ifndef VIEW_H
#define VIEW_H

#include "loginform.h"
#include "studentform.h"
#include "changepasswordform.h"
#include "staffform.h"
#include "profileform.h"
#include "tabliststudent.h"

class View {
    // Q_OBJECT
    private:
        LoginForm *loginForm;
    public:
        View();
};

#endif // VIEW_H
