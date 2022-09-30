cmake_minimum_required(VERSION 3.23)
project(LogicCalculator)

set(CMAKE_CXX_STANDARD 14)

include_directories(LogicInterpreter)

add_executable(LogicCalculator
        LogicInterpreter/Assign.h
        LogicInterpreter/Calculator.h
        LogicInterpreter/InfixExpression.h
        LogicInterpreter/main.cpp
        LogicInterpreter/Operator.h
        LogicInterpreter/Outputer.h
        LogicInterpreter/PublicMethod.h
        LogicInterpreter/QuickCalculator.h
        LogicInterpreter/Stack.h
        LogicInterpreter/Translate.h
        LogicInterpreter/Variables.h)
