#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adt_logger.h"
#include "ABGS_MemoryManager/abgs_memory_manager.h"

#include "./../tests/test_base.c"

int main() {
  Logger* log_1 = CREATE_Logger(20);
  s16 error_type = 0;

  u8* data_1 = MM->malloc(16);
  strcpy(data_1, "First Log");
  //log_1->ops_->write(log_1, data_1);
  //log_1->ops_->write(log_1, ...);
  //log_1->ops_->write(log_1, ...);

  //error_type = log_1->destroy();
  //TESTBASE_printFunctionResult(error_type);

  MM->status();
  MM->destroy();

  return 0;
}