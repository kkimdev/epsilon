#ifndef PYTHON_PORT_H
#define PYTHON_PORT_H

#include <cstdio>

namespace MicroPython {

class ScriptProvider {
public:
  virtual const char * contentOfScript(const char * name) = 0;
};

class ExecutionEnvironment {
public:
  ExecutionEnvironment();
  static ExecutionEnvironment * currentExecutionEnvironment();
  void runCode(const char * );
  virtual void displaySandbox() {
  }
  virtual void printText(const char * text, size_t length) {
    printf("%s", text);
  }
protected:
  bool m_sandboxIsDisplayed;
};

void init(void * heapStart, void * heapEnd);
void deinit();
void registerScriptProvider(ScriptProvider * s);

};

// Will implement :
// mp_lexer_new_from_file -> Ask the context about a file
// mp_import_stat
// mp_hal_stdout_tx_strn_cooked -> Tell the context Python printed text

#endif
