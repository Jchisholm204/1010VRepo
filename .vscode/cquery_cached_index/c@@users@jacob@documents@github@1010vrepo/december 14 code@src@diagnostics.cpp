#include "main.h"
#include "diagnostics.h"
void diagnostics_fn(void*parameter){
  int diagnosticsCase;
  while(true){
    if(leftSuck.get_temperature() > 30){diagnosticsCase = INTAKE_OVERHEATING;};
    if(partner.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){diagnosticsCase += 1;};
    if(diagnosticsCase > 4){diagnosticsCase = 0;};
    switch(diagnosticsCase){
      case 0:
      printf("0");
      lcd::print(1, "diagnosticsCase = 0");
      break;
      case 1:
        printf("1");
        lcd::print(1, "diagnosticsCase = 1");
        break;
      case 2:
        printf("2");
        lcd::print(1, "diagnosticsCase = 2");
        break;
      case 5:
        lcd::print(1, "diagnosticsCase = INTAKES_OVERHEATING");
      default:
        printf("PGRM ERR:  VALUE NOT WITHIN RANGE");
        lcd::print(1, "diagnosticsCase = WRN::::VALUE NOT WITHIN RANGE");
        break;
    }
  }
}
