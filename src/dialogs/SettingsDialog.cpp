#include "SettingsDialog.h"



SettingsDialog* SettingsDialog::getSettingsDialog ( QWidget* parent ) {  
  static SettingsDialog sinstance(parent);
  return &sinstance;
}

/***
 *** CONSTRUCTORS AND DESTRUCTOR
 */
SettingsDialog::SettingsDialog ( QWidget* parent ) : QDialog ( parent ) {

}


/********/



