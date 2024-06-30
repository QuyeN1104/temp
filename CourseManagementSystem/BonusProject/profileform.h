#ifndef PROFILEFORM_H
#define PROFILEFORM_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QFormLayout>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"

class ProfileForm : public QLabel
{
public:
    ProfileForm(Student* student);
    ProfileForm(Staff* staff);
};

#endif // PROFILEFORM_H
