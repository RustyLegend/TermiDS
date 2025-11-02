#include "dsa_unit2_stackqueue.h"
#include "dsa_common.h"
#include<ctype.h>
#define INFIX_STACK_SIZE 100
#define EVAL_STACK_SIZE 100
static int g_eval_stack[EVAL_STACK_SIZE];
static int g_eval_top = -1;
static char g_infix_stack[INFIX_STACK_SIZE];
static int g_infix_top = -1;
static char g_infix_postfix[INFIX_STACK_SIZE];
static int g_postfix_idx = 0;

static struct Stack g_stack;
static struct Queue g_queue;

static void eval_stack_init() { g_eval_top = -1; }
static int eval_stack_is_empty() { return g_eval_top == -1; }
static int eval_stack_is_full() { return g_eval_top == EVAL_STACK_SIZE - 1; }

static void eval_push(int val) {
    if (!eval_stack_is_full()) {
        g_eval_stack[++g_eval_top] = val;
    }
}

static int is_match(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '[' && close == ']') return 1;
    if (open == '{' && close == '}') return 1;
    return 0;
}

static int eval_pop() {
    if (!eval_stack_is_empty()) {
        return g_eval_stack[g_eval_top--];
    }
    return -9999;
}

static void eval_print_stack() {
    printf("Stack (Top to Bottom):\n");
    printf("+-------+\n");

    if (g_eval_top == -1) {
        printf("| Empty |\n");
    } else {
        for (int i = g_eval_top; i >= 0; i--) {
            printf("| %5d |", g_eval_stack[i]);
            if (i == g_eval_top) {
                printf(" <- TOP\n");
            } else {
                printf("\n");
            }
             if (i > 0) {
                printf("+-------+\n");
            }
        }
    }
    printf("+-------+\n");
    printf("  BOTTOM\n");
}

void stack_init() {
    g_stack.top = -1;
}

void stack_push() {
    if (g_stack.top == STACK_SIZE - 1) {
        printf("Stack Overflow! Cannot push.\n");
    } else {
        int item;
        printf("Enter item to push: ");
        if(scanf("%d", &item) != 1) { item = 0; }
        clear_input_buffer();
        
        g_stack.top++;
        g_stack.items[g_stack.top] = item;
        printf("Pushed %d onto the stack.\n", item);
    }
}

void stack_pop() {
    if (g_stack.top == -1) {
        printf("Stack Underflow! Cannot pop.\n");
    } else {
        int item = g_stack.items[g_stack.top];
        g_stack.top--;
        printf("Popped %d from the stack.\n", item);
    }
}

void stack_display() {
    printf("Stack (Size: %d):\n", STACK_SIZE);
    printf("+-------+\n");

    if (g_stack.top == -1) {
        printf("| Empty |\n");
    } else {
        for (int i = g_stack.top; i >= 0; i--) {
            printf("| %5d |", g_stack.items[i]);
            if (i == g_stack.top) {
                printf(" <- TOP\n");
            } else {
                printf("\n");
            }
            if (i > 0) {
                 printf("+-------+\n");
            }
        }
    }
    printf("+-------+\n");
    printf("  BOTTOM\n");
}

void queue_init() {
    g_queue.front = 0;
    g_queue.rear = -1;
    g_queue.count = 0;
}

void queue_enqueue() {
    if (g_queue.count == QUEUE_SIZE) {
        printf("Queue is Full! Cannot enqueue.\n");
    } else {
        int item;
        printf("Enter item to enqueue: ");
        if(scanf("%d", &item) != 1) { item = 0; }
        clear_input_buffer();
        
        g_queue.rear = (g_queue.rear + 1) % QUEUE_SIZE;
        g_queue.items[g_queue.rear] = item;
        g_queue.count++;
        printf("Enqueued %d.\n", item);
    }
}

void queue_dequeue() {
    if (g_queue.count == 0) {
        printf("Queue is Empty! Cannot dequeue.\n");
    } else {
        int item = g_queue.items[g_queue.front];
        g_queue.front = (g_queue.front + 1) % QUEUE_SIZE;
        g_queue.count--;
        printf("Dequeued %d.\n", item);
    }
}

void queue_display() {
    if (g_queue.count == 0) {
        printf("Queue is empty.\n");
        return;
    }
    
    printf("Queue (Front to Rear):\nFRONT -> ");
    int i = g_queue.front;
    int j;
    for (j = 0; j < g_queue.count; j++) {
        printf("%d -> ", g_queue.items[i]);
        i = (i + 1) % QUEUE_SIZE;
    }
    printf("REAR\n");
}

static void dsa_count_sort_visual() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Count Sort Visualization                |\n");
    printf("==========================================\n");
    printf("Note: Count Sort is efficient for a small range of\n");
    printf("non-negative integers. (e.g., 0-99)\n\n");
    
    int n;
    int* arr = get_positive_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);

    int max = get_max(arr, n);
    int range = max + 1;
    
    int* count = (int*) calloc(range, sizeof(int));
    int* output = (int*) malloc(n * sizeof(int));
    
    if (count == NULL || output == NULL) {
        printf("Memory allocation failed!\n");
        if (count) free(count);
        if (output) free(output);
        free(arr);
        _press_enter_to_continue();
        return;
    }

    printf("\n--- Step 1: Frequency Array (size %d) ---\n", range);
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    print_array(count, range);
    _press_enter_to_continue();

    printf("\n--- Step 2: Cumulative Position Array ---\n");
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }
    print_array(count, range);
    _press_enter_to_continue();
    
    printf("\n--- Step 3: Building Output Array ---\n");
    printf("Iterating input array *backwards*...\n");
    for (int i = n - 1; i >= 0; i--) {
        int val = arr[i];
        int pos = count[val] - 1;
        output[pos] = val;
        count[val]--;
        printf("Placed %d at output[%d]. New count[%d] is %d.\n", val, pos, val, count[val]);
    }
    _press_enter_to_continue();

    printf("\n--- Final Result ---\n");
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    print_array(arr, n);

    free(arr);
    free(count);
    free(output);
    _press_enter_to_continue();
}

static void radix_count_sort(int arr[], int n, int exp) {
    int* output = (int*) malloc(n * sizeof(int));
    int count[10] = {0};
    
    if (output == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        int pos = count[digit] - 1;
        output[pos] = arr[i];
        count[digit]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
    
    free(output);
}

static void dsa_radix_sort_visual() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Radix Sort Visualization                |\n");
    printf("==========================================\n");
    printf("Note: Radix Sort (LSD) sorts digit by digit,\n");
    printf("using a stable sort (like Count Sort).\n\n");

    int n;
    int* arr = get_positive_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    _press_enter_to_continue();

    int max = get_max(arr, n);
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        printf("\n--- Sorting on Digit (Place = %d) ---\n", exp);
        radix_count_sort(arr, n, exp);
        print_array(arr, n);
        _press_enter_to_continue();
    }

    printf("\n--- Final Result ---\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

void dsa_count_radix_sort() {
    int choice;
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Count Sort vs. Radix Sort               |\n");
        printf("==========================================\n");
        printf("Select a sort to visualize:\n");
        printf("------------------------------------------\n");
        printf(" 1. Count Sort (Visualizes Frequency/Position Arrays)\n");
        printf(" 2. Radix Sort (Visualizes Pass-by-Pass)\n");
        printf(" 3. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                dsa_count_sort_visual();
                break;
            case 2:
                dsa_radix_sort_visual();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 3);
}

void dsa_stack_operations() {
    int choice;
    stack_init();

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Stack Operations (Size: %d)           |\n", STACK_SIZE);
        printf("==========================================\n");
        stack_display();
        printf("------------------------------------------\n");
        printf(" 1. Push\n");
        printf(" 2. Pop\n");
        printf(" 3. Display Stack\n");
        printf(" 4. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1: stack_push(); _press_enter_to_continue(); break;
            case 2: stack_pop(); _press_enter_to_continue(); break;
            case 3: stack_display(); _press_enter_to_continue(); break;
            case 4: return;
            default: printf("Invalid choice.\n"); _press_enter_to_continue();
        }
    } while (choice != 4);
}

void dsa_queue_operations() {
    int choice;
    queue_init();

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Queue Operations (Circular Array, Size: %d) |\n", QUEUE_SIZE);
        printf("==========================================\n");
        queue_display();
        printf("------------------------------------------\n");
        printf(" 1. Enqueue (Insert)\n");
        printf(" 2. Dequeue (Delete)\n");
        printf(" 3. Display Queue\n");
        printf(" 4. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1: queue_enqueue(); _press_enter_to_continue(); break;
            case 2: queue_dequeue(); _press_enter_to_continue(); break;
            case 3: queue_display(); _press_enter_to_continue(); break;
            case 4: return;
            default: printf("Invalid choice.\n"); _press_enter_to_continue();
        }
    } while (choice != 4);
}

static void infix_stack_init() { 
    g_infix_top = -1; 
    g_postfix_idx = 0;
    g_infix_postfix[0] = '\0';
}

static int infix_stack_is_empty() { return g_infix_top == -1; }
static int infix_stack_is_full() { return g_infix_top == INFIX_STACK_SIZE - 1; }

static void infix_push(char op) {
    if (!infix_stack_is_full()) {
        g_infix_stack[++g_infix_top] = op;
    }
}

static char infix_pop() {
    if (!infix_stack_is_empty()) {
        return g_infix_stack[g_infix_top--];
    }
    return '\0';
}
    
static char infix_peek() {
    if (!infix_stack_is_empty()) {
        return g_infix_stack[g_infix_top];
    }
    return '\0';
}

static int is_operand(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}

static int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return 0;
}

static void infix_print_stack() {
    printf("Stack (Top to Bottom):\n");
    printf("+-----+\n");

    if (g_infix_top == -1) {
        printf("|Empty|\n");
    } else {
        for (int i = g_infix_top; i >= 0; i--) {
            printf("|  %c  |", g_infix_stack[i]);
            if (i == g_infix_top) {
                printf(" <- TOP\n");
            } else {
                printf("\n");
            }
            if (i > 0) {
                printf("+-----+\n");
            }
        }
    }
    printf("+-----+\n");
    printf(" BOTTOM\n");
}

static void infix_append_postfix(char ch) {
    g_infix_postfix[g_postfix_idx++] = ch;
    g_infix_postfix[g_postfix_idx] = '\0';
    printf("Postfix: %s\n", g_infix_postfix);
}

void dsa_infix_to_postfix() {
    char infix[INFIX_STACK_SIZE];
    int i;
    
    infix_stack_init();
    
    _clear_screen();
    printf("==========================================\n");
    printf("| Infix to Postfix Conversion (Visualized)|\n");
    printf("==========================================\n");
    printf("Note: Supports operands a-z, A-Z, 0-9\n");
    printf("Operators: +, -, *, /, ^ (right-assoc), ()\n");
    printf("Enter an infix expression (e.g., a+b*(c^d-e)/f ):\n");
    
    if(scanf("%s", infix) != 1) { strcpy(infix, "a+b"); }
    clear_input_buffer();
    
    printf("\n--- Starting Conversion ---\n");
    printf("Infix: %s\n", infix);
    
    for (i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        printf("------------------------------------------\n");
        printf("Reading: '%c'\n", ch);

        if (is_operand(ch)) {
            printf("Action: Is Operand. Append to postfix.\n");
            infix_append_postfix(ch);
        } 
        else if (ch == '(') {
            printf("Action: Is '('. Push onto stack.\n");
            infix_push(ch);
        }
        else if (ch == ')') {
            printf("Action: Is ')'. Pop from stack until '(' is found.\n");
            while (!infix_stack_is_empty() && infix_peek() != '(') {
                char popped = infix_pop();
                printf("  Popped '%c'. Appending to postfix.\n", popped);
                infix_append_postfix(popped);
            }
            if (!infix_stack_is_empty()) {
                infix_pop();
                printf("  Popped and discarded '('\n");
            }
        }
        else { 
            printf("Action: Is Operator.\n");
            
            if (ch == '^') {
                while (!infix_stack_is_empty() && infix_peek() != '(' && 
                       precedence(infix_peek()) > precedence(ch)) {
                    
                    char popped = infix_pop();
                    printf("  Popped '%c' (precedence >). Appending.\n", popped);
                    infix_append_postfix(popped);
                }
            } 
            else {
                while (!infix_stack_is_empty() && infix_peek() != '(' && 
                       precedence(infix_peek()) >= precedence(ch)) {
                    
                    char popped = infix_pop();
                    printf("  Popped '%c' (precedence >=). Appending.\n", popped);
                    infix_append_postfix(popped);
                }
            }
            printf("  Pushing current operator '%c' onto stack.\n", ch);
            infix_push(ch);
        }
        infix_print_stack();
    }
    
    printf("------------------------------------------\n");
    printf("End of infix string. Popping remaining stack:\n");
    while (!infix_stack_is_empty()) {
        char popped = infix_pop();
        printf("  Popped '%c'. Appending to postfix.\n", popped);
        infix_append_postfix(popped);
    }
    
    printf("\n--- Final Result ---\n");
    printf("Infix:   %s\n", infix);
    printf("Postfix: %s\n", g_infix_postfix);
    
    _press_enter_to_continue();
}

void dsa_string_reversal_stack() {
    char original[INFIX_STACK_SIZE];
    char reversed[INFIX_STACK_SIZE];
    int i = 0;
    
    infix_stack_init();
    
    _clear_screen();
    printf("==========================================\n");
    printf("| String Reversal using Stack (Visualized)|\n");
    printf("==========================================\n");
    printf("Enter a string to reverse (no spaces):\n");
    
    if(scanf("%s", original) != 1) { strcpy(original, "error"); }
    clear_input_buffer();

    printf("\n--- Phase 1: Pushing to Stack ---\n");
    
    for (i = 0; original[i] != '\0'; i++) {
        if (!infix_stack_is_full()) {
            infix_push(original[i]);
            printf("Pushed: '%c'\n", original[i]);
            infix_print_stack();
        } else {
            printf("Stack is full! Cannot push more characters.\n");
            original[i] = '\0';
            break;
        }
    }
    
    printf("\nStack is full. Ready to pop.\n");
    _press_enter_to_continue();
    
    printf("\n--- Phase 2: Popping to build new string ---\n");

    i = 0;
    while (!infix_stack_is_empty()) {
        char ch = infix_pop();
        reversed[i++] = ch;
        printf("Popped: '%c'\n", ch);
        infix_print_stack();
    }
    reversed[i] = '\0';
    
    printf("\n--- Final Result ---\n");
    printf("Original: %s\n", original);
    printf("Reversed: %s\n", reversed);
    
    _press_enter_to_continue();
}

void dsa_postfix_evaluation() {
    char postfix[EVAL_STACK_SIZE];
    int i;
    
    eval_stack_init();
    
    _clear_screen();
    printf("==========================================\n");
    printf("| Postfix Evaluation (Visualized)         |\n");
    printf("==========================================\n");
    printf("Note: Supports single-digit operands (0-9)\n");
    printf("Operators: +, -, *, /, ^\n");
    printf("Enter a postfix expression (e.g., 23+5* or 82/3- ):\n");
    
    if(scanf("%s", postfix) != 1) { strcpy(postfix, "23+"); }
    clear_input_buffer();
    
    printf("\n--- Starting Evaluation ---\n");
    printf("Postfix: %s\n", postfix);

    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        printf("------------------------------------------\n");
        printf("Reading: '%c'\n", ch);

        if (isdigit(ch)) {
            int val = ch - '0';
            printf("Action: Is Operand. Pushing %d onto stack.\n", val);
            eval_push(val);
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
            printf("Action: Is Operator.\n");
            
            if (eval_stack_is_empty()) {
                printf("Error: Malformed expression! (Stack empty on op)\n");
                break;
            }
            int val2 = eval_pop();
            
            if (eval_stack_is_empty()) {
                printf("Error: Malformed expression! (Stack empty on 2nd pop)\n");
                break;
            }
            int val1 = eval_pop();
            
            printf("  Popped %d (as val2).\n", val2);
            printf("  Popped %d (as val1).\n", val1);

            int result = 0;
            switch(ch) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        goto cleanup;
                    }
                    result = val1 / val2; 
                    break;
                case '^': 
                    result = 1;
                    for(int j=0; j<val2; j++) result *= val1;
                    break;
            }
            printf("  Calculation: %d %c %d = %d\n", val1, ch, val2, result);
            printf("  Pushing result %d onto stack.\n", result);
            eval_push(result);
        }
        else {
             printf("Action: Unknown character. Skipping.\n");
        }
        eval_print_stack();
    }

cleanup:
    printf("------------------------------------------\n");
    printf("End of expression.\n");
    
    if (!eval_stack_is_empty()) {
        int final_result = eval_pop();
        if (eval_stack_is_empty()) {
            printf("\n--- Final Result ---\n");
            printf("Result: %d\n", final_result);
        } else {
            printf("\n--- Error ---\n");
            printf("Malformed expression: Too many operands.\n");
            eval_print_stack();
        }
    } else {
        printf("\n--- Error ---\n");
        printf("Malformed expression or stack is empty.\n");
    }

    _press_enter_to_continue();
}

void dsa_balancing_symbols() {
    char expr[INFIX_STACK_SIZE];
    int i;
    int is_balanced = 1;

    infix_stack_init();
    
    _clear_screen();
    printf("==========================================\n");
    printf("| Balancing Symbols (Visualized)          |\n");
    printf("==========================================\n");
    printf("Checks for balanced: (), [], {}\n");
    printf("Enter an expression (e.g., a*(b+[c*d])-{e} ):\n");
    
    if(scanf("%s", expr) != 1) { strcpy(expr, "()"); }
    clear_input_buffer();
    
    printf("\n--- Starting Check ---\n");
    printf("Expression: %s\n", expr);

    for (i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        printf("------------------------------------------\n");
        printf("Reading: '%c'\n", ch);

        if (ch == '(' || ch == '[' || ch == '{') {
            printf("Action: Opening symbol. Pushing to stack.\n");
            if (infix_stack_is_full()) {
                printf("ERROR: Stack is full! Expression is too long.\n");
                is_balanced = 0;
                break;
            }
            infix_push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            printf("Action: Closing symbol. Checking for match.\n");
            
            if (infix_stack_is_empty()) {
                printf("  ERROR: Mismatch! Stack is empty, but found closing '%c'.\n", ch);
                is_balanced = 0;
                break;
            }
            
            char popped = infix_pop();
            printf("  Popped: '%c'\n", popped);
            
            if (is_match(popped, ch)) {
                printf("  Match OK: '%c' and '%c'.\n", popped, ch);
            } else {
                printf("  ERROR: Mismatch! Popped '%c' does not match closing '%c'.\n", popped, ch);
                is_balanced = 0;
                break;
            }
        }
        else {
            printf("Action: Not a symbol. Ignoring.\n");
        }
        
        infix_print_stack();
    }
    
    printf("------------------------------------------\n");
    printf("End of expression.\n");

    if (is_balanced) {
        if (infix_stack_is_empty()) {
            printf("Final Check: Stack is empty.\n");
            printf("\n--- Final Result: BALANCED ---\n");
        } else {
            printf("Final Check: ERROR! Stack is not empty.\n");
            printf("  Unmatched opening symbols remain on the stack.\n");
            infix_print_stack();
            printf("\n--- Final Result: NOT BALANCED ---\n");
        }
    } else {
        printf("\n--- Final Result: NOT BALANCED ---\n");
        printf("A mismatch error was detected during the scan.\n");
    }

    _press_enter_to_continue();
}