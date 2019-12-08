#include "templatedialog.h"
#include "ui_templatedialog.h"

TemplateDialog::TemplateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemplateDialog)
{
    ui->setupUi(this);
}

TemplateDialog::~TemplateDialog()
{
    delete ui;
}
