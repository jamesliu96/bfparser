#define CODE_SEGMENT_SIZE 30000
#define STACK_SEGMENT_SIZE 1000
#define DATA_SEGMENT_SIZE 30000

typedef void (*Callback)(void);

struct {
  char cs[CODE_SEGMENT_SIZE];   /* Code Segment */
  long ip;                      /* Instruction Pointer */

  char ss[STACK_SEGMENT_SIZE];  /* Stack Segment */
  long sp;                      /* Stack Pointer */

  char ds[DATA_SEGMENT_SIZE];   /* Data Segment */
  long bp;                      /* Base Pointer */

  Callback fn[128];
} vm;

void vm_forward() {
  vm.bp = (vm.bp + 1) % DATA_SEGMENT_SIZE;
}

void vm_backward() {
  vm.bp = (vm.bp + DATA_SEGMENT_SIZE - 1) % DATA_SEGMENT_SIZE;
}

void vm_increment() {
  vm.ds[vm.bp]++;
}

void vm_decrement() {
  vm.ds[vm.bp]--;
}

void vm_input() {
  vm.ds[vm.bp] = getchar();
}

void vm_output() {
  putchar(vm.ds[vm.bp]);
}

void vm_while_in() {
  if (vm.ds[vm.bp]) {
    vm.ss[vm.sp] = vm.ip - 1;
    vm.sp++;
  } else {
    int c = 1;
    for (vm.ip++; vm.cs[vm.ip] && c; vm.ip++) {
      if (vm.cs[vm.ip] == '[') {
        c++;
      } else if (vm.cs[vm.ip] == ']') {
        c--;
      }
    }
  }
}

void vm_while_out() {
  if (vm.ds[vm.bp]) {
    vm.sp--;
    vm.ip = vm.ss[vm.sp];
  }
}