#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <iostream>

enum class inst_enum {
Add,
Smake,
Sload,
Hmake,
Hload,
Set, // used to set the value of a variable
Seq, // sequences dominate what the type is, every other type is disregarded
Scope,
Temp,
Init,
Ret,
Add,
Mul,
Div,
Sub,
Mod,
Escope,
Call,
Fn,
If, // takes bool
While, // takes bool
// no For loop, compiler will just create it with a while loop and then add the iterator at the end
Static, // sets something to data section
Array, // takes string seperated by commas
Type, // defines the type of last instruction
};

class variable {
  public:
    std::string& name;
    std::string& arg;
    std::string& type;
    int scope;
    bool depended_on;
    int to_destroy;
    std::vector<variable&>& free_array;

    variable(std::string& name, std::string& arg, std::string& type,
        int scope, bool depended_on, int to_destroy, auto free_array)
      
      :name(name), arg(arg), type(type), scope(scope), depended_on(depended_on),
      to_destroy(to_destroy), free_array(free_array) {}
};

class instruction {
  protected:
    inst_enum inst;
    variable arg;
  public:
    instruction(const inst_enum inst, const std::string& arg)
      : inst(inst), arg(arg) {}
};

class program {
  protected:
    std::vector<std::unique_ptr<instruction>> instructions;
    std::vector<std::unique_ptr<variable>> variables;
  
  public:
    instruction(std::vector<std::unique_ptr<instruction>>& instructions)
      : instructions(instructions) {}

    void process(){
      int current_scope = 0;
      for (int i = 0; i < instructions.size(); i++){
        bool not_first = (i > 0) ? true : false;
        bool not_last = (i != instructions.size() - 1) ? true : false;

        switch (instructions[i]->inst){
        case (Smake): {
          std::string& name = instructions[i]->arg;
          std::string& arg;
          if (not_last && instructions[i + 1]->inst == Set) arg = instructions[i + 1]->arg;
          else arg = "";

          std::unique_ptr<variable> new_var = std::make_unique<variable>(name, arg, type, scope, false, NULL);
          variables.push_back(std::move(new_var));

          break;
        }

        case (Sload): {
          if (instructions[i]->arg->free_list == NULL) break;
          int j = i;
          while (j > 0 && instructions[j]->inst != Seq){
            j--;
          }

          instructions[j]->arg->free_list.append_range(instructions[i]->arg->free_list);
          instructions[i]->arg->depended_on = true;

          break;
        }

        case (Hload): {
          int j = i;
          while (j > 0 && instructions[j]->inst != Seq){
            j--;
          }

          if (instructions[j]->inst != Seq) {
            std::cout << "Attempted heap-load declared outside of a sequence on instruction #" << i << '\n';
            exit(EXIT_FAILURE);
          }

          // instructions[j] argument depends on instructions[i] argument
          // to_destroy is set at -1, they're evaluated for every variable at flux phase
          // to_destroy applies to both stack and heap variables since both can have dependencies

          if (instructions[i]->scope < instructions[j]->scope) {
            if (instructions[j]->arg->free_array == NULL){
              std::vector<variable&> free_array;
              instructions[j]->arg->free_array = std::move(free_array);
            }

            instructions[j]->arg->free_array.push_back(instructions[i]);
            instructions[i]->arg->depended_on = true;
          }

          break;
        }
        }
      }
    }

    void flux() {} // does compiler time travel
    void print_ir() const {}
};

int main() {
  
}
