#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TOKENS "><+-.,[]"

#include "bfparser.h"

void setup() {
  int c;
  int i;

  memset(&vm, 0, sizeof(vm));
  vm.fn['>'] = vm_forward;
  vm.fn['<'] = vm_backward;
  vm.fn['+'] = vm_increment;
  vm.fn['-'] = vm_decrement;
  vm.fn['.'] = vm_output;
  vm.fn[','] = vm_input;
  vm.fn['['] = vm_while_in;
  vm.fn[']'] = vm_while_out;

  for (i = 0; (c = getchar()) != EOF;) {
    if (strchr(TOKENS, c)) {
      vm.cs[i] = c;
      i++;
    }
  }
}

void run() {
  while (vm.cs[vm.ip]) {
    vm.fn[vm.cs[vm.ip]]();
    vm.ip++;
  }
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    freopen(argv[1], "r", stdin);
  }

  setup();
  run();

  return 0;
}
