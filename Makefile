

CPP=g++
CPPFLAGS=-I. -c
LINK=g++

main: solver

FONTES=\
	ga/GeneticSolver.cpp\
	sat/2SATSolver.cpp\
	sat/Interpretation.cpp\
	sat/CNFGeneticOperators.cpp\
	sat/Clause.cpp\
	sat/CNFFormula.cpp\
	sat/SATGABuilder.cpp\
	sat/CNFChromossomeImprover.cpp\
	sat/BasicCNFSolver.cpp\
	sat/SATLIBParser.cpp\
	sat/CNFFitnessEvaluator.cpp\
	util/Timer.cpp\
	util/XString.cpp\
	util/Properties.cpp\
	util/BitArrayOps.cpp\
	util/Random.cpp\
	util/EnumDir.cpp\
	benchmarks/benchmarkAntSolver.cpp\
	benchmarks/BenchmarkGeneticSAT.cpp\
	benchmarks/benchmarkAntSolver2.cpp\
	benchmarks/benchmarkMain.cpp\
	sat2csp/DirectEncodingCSP2SAT.cpp\
	sat2csp/LogEncodingCSP2SAT.cpp\
	sat2csp/CSP2SAT.cpp\
	sat2csp/DualEncodingSAT2CSP.cpp\
	csp/RandomCSP.cpp\
	csp/BasicCSP.cpp\
	csp/CSPGABuilder.cpp\
	csp/CSPInterpretation.cpp\
	csp/CSPGeneticSolverExtraData.cpp\
	csp/MinConflicts.cpp\
	csp/NQueensCSPConstraintList.cpp\
	csp/VirtualCSPDomainList.cpp\
	csp/BasicCSPConstraintList.cpp\
	csp/CSPGeneticOperators.cpp\
	csp/CSPChromossomeImprover.cpp\
	csp/Constraint.cpp\
	csp/NQueensCSP.cpp\
	csp/CSPVariableDomain.cpp\
	csp/CrosswordsCSP.cpp\
	csp/CSPProblem.cpp\
	csp/BasicCSPDomainList.cpp\
	csp/CSPVariableValue.cpp\
	aco/AntSolver2.cpp\
	aco/AntSolverGraph2.cpp\
	aco/AntSolverGraph.cpp\
	aco/AntSolver.cpp\
	tests/testMinConflicts.cpp\
	tests/TestMain.cpp\
	tests/TestSATLIBParser.cpp\
	tests/BenchmarkGeneticSAT.cpp\
	tests/TestProperties.cpp\
	tests/TestGeneticSAT.cpp\
	tests/TestDualEncoding.cpp\
	tests/TestNQueensCSP.cpp\
	tests/TestBitArray.cpp\
	tests/TestAntSolver.cpp\
	tests/TestBasicCSP.cpp\
	tests/TestRandomCSP.cpp\
	tests/TestCNFFormula.cpp\
	tests/testCSPToSAT.cpp\
	tests/TestCrosswordCSP.cpp\
	tests/TestArcConsistency.cpp\
	tests/TestGeneticCSP.cpp\
	tests/Test2SATSolver.cpp\
	tests/TestSATInterpretation.cpp\
	main.cpp\


OBJETOS=\
	Objetos/ga/GeneticSolver.o \
	Objetos/sat/2SATSolver.o \
	Objetos/sat/Interpretation.o \
	Objetos/sat/CNFGeneticOperators.o \
	Objetos/sat/Clause.o \
	Objetos/sat/CNFFormula.o \
	Objetos/sat/SATGABuilder.o \
	Objetos/sat/CNFChromossomeImprover.o \
	Objetos/sat/BasicCNFSolver.o \
	Objetos/sat/SATLIBParser.o \
	Objetos/sat/CNFFitnessEvaluator.o \
	Objetos/util/Timer.o \
	Objetos/util/XString.o \
	Objetos/util/Properties.o \
	Objetos/util/BitArrayOps.o \
	Objetos/util/Random.o \
	Objetos/util/EnumDir.o \
	Objetos/benchmarks/benchmarkAntSolver.o \
	Objetos/benchmarks/BenchmarkGeneticSAT.o \
	Objetos/benchmarks/benchmarkAntSolver2.o \
	Objetos/benchmarks/benchmarkMain.o \
	Objetos/sat2csp/DirectEncodingCSP2SAT.o \
	Objetos/sat2csp/LogEncodingCSP2SAT.o \
	Objetos/sat2csp/CSP2SAT.o \
	Objetos/sat2csp/DualEncodingSAT2CSP.o \
	Objetos/csp/RandomCSP.o \
	Objetos/csp/BasicCSP.o \
	Objetos/csp/CSPGABuilder.o \
	Objetos/csp/CSPInterpretation.o \
	Objetos/csp/CSPGeneticSolverExtraData.o \
	Objetos/csp/MinConflicts.o \
	Objetos/csp/NQueensCSPConstraintList.o \
	Objetos/csp/VirtualCSPDomainList.o \
	Objetos/csp/BasicCSPConstraintList.o \
	Objetos/csp/CSPGeneticOperators.o \
	Objetos/csp/CSPChromossomeImprover.o \
	Objetos/csp/Constraint.o \
	Objetos/csp/NQueensCSP.o \
	Objetos/csp/CSPVariableDomain.o \
	Objetos/csp/CrosswordsCSP.o \
	Objetos/csp/CSPProblem.o \
	Objetos/csp/BasicCSPDomainList.o \
	Objetos/csp/CSPVariableValue.o \
	Objetos/aco/AntSolver2.o \
	Objetos/aco/AntSolverGraph2.o \
	Objetos/aco/AntSolverGraph.o \
	Objetos/aco/AntSolver.o \
	Objetos/tests/testMinConflicts.o \
	Objetos/tests/TestMain.o \
	Objetos/tests/TestSATLIBParser.o \
	Objetos/tests/BenchmarkGeneticSAT.o \
	Objetos/tests/TestProperties.o \
	Objetos/tests/TestGeneticSAT.o \
	Objetos/tests/TestDualEncoding.o \
	Objetos/tests/TestNQueensCSP.o \
	Objetos/tests/TestBitArray.o \
	Objetos/tests/TestAntSolver.o \
	Objetos/tests/TestBasicCSP.o \
	Objetos/tests/TestRandomCSP.o \
	Objetos/tests/TestCNFFormula.o \
	Objetos/tests/testCSPToSAT.o \
	Objetos/tests/TestCrosswordCSP.o \
	Objetos/tests/TestArcConsistency.o \
	Objetos/tests/TestGeneticCSP.o \
	Objetos/tests/Test2SATSolver.o \
	Objetos/tests/TestSATInterpretation.o \
	Objetos/./main.o \


solver: $(OBJETOS)
	$(LINK) $(OBJETOS) -o solver

clean:
	rm -f $(OBJETOS) solver
depend:
	makedepend -I. $(FONTES)

Objetos/ga/GeneticSolver.o: ga/GeneticSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/ga/GeneticSolver.o ga/GeneticSolver.cpp

Objetos/sat/2SATSolver.o: sat/2SATSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/2SATSolver.o sat/2SATSolver.cpp

Objetos/sat/Interpretation.o: sat/Interpretation.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/Interpretation.o sat/Interpretation.cpp

Objetos/sat/CNFGeneticOperators.o: sat/CNFGeneticOperators.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/CNFGeneticOperators.o sat/CNFGeneticOperators.cpp

Objetos/sat/Clause.o: sat/Clause.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/Clause.o sat/Clause.cpp

Objetos/sat/CNFFormula.o: sat/CNFFormula.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/CNFFormula.o sat/CNFFormula.cpp

Objetos/sat/SATGABuilder.o: sat/SATGABuilder.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/SATGABuilder.o sat/SATGABuilder.cpp

Objetos/sat/CNFChromossomeImprover.o: sat/CNFChromossomeImprover.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/CNFChromossomeImprover.o sat/CNFChromossomeImprover.cpp

Objetos/sat/BasicCNFSolver.o: sat/BasicCNFSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/BasicCNFSolver.o sat/BasicCNFSolver.cpp

Objetos/sat/SATLIBParser.o: sat/SATLIBParser.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/SATLIBParser.o sat/SATLIBParser.cpp

Objetos/sat/CNFFitnessEvaluator.o: sat/CNFFitnessEvaluator.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat/CNFFitnessEvaluator.o sat/CNFFitnessEvaluator.cpp

Objetos/util/Timer.o: util/Timer.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/util/Timer.o util/Timer.cpp

Objetos/util/XString.o: util/XString.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/util/XString.o util/XString.cpp

Objetos/util/Properties.o: util/Properties.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/util/Properties.o util/Properties.cpp

Objetos/util/BitArrayOps.o: util/BitArrayOps.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/util/BitArrayOps.o util/BitArrayOps.cpp

Objetos/util/Random.o: util/Random.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/util/Random.o util/Random.cpp

Objetos/util/EnumDir.o: util/EnumDir.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/util/EnumDir.o util/EnumDir.cpp

Objetos/benchmarks/benchmarkAntSolver.o: benchmarks/benchmarkAntSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/benchmarks/benchmarkAntSolver.o benchmarks/benchmarkAntSolver.cpp

Objetos/benchmarks/BenchmarkGeneticSAT.o: benchmarks/BenchmarkGeneticSAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/benchmarks/BenchmarkGeneticSAT.o benchmarks/BenchmarkGeneticSAT.cpp

Objetos/benchmarks/benchmarkAntSolver2.o: benchmarks/benchmarkAntSolver2.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/benchmarks/benchmarkAntSolver2.o benchmarks/benchmarkAntSolver2.cpp

Objetos/benchmarks/benchmarkMain.o: benchmarks/benchmarkMain.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/benchmarks/benchmarkMain.o benchmarks/benchmarkMain.cpp

Objetos/sat2csp/DirectEncodingCSP2SAT.o: sat2csp/DirectEncodingCSP2SAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat2csp/DirectEncodingCSP2SAT.o sat2csp/DirectEncodingCSP2SAT.cpp

Objetos/sat2csp/LogEncodingCSP2SAT.o: sat2csp/LogEncodingCSP2SAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat2csp/LogEncodingCSP2SAT.o sat2csp/LogEncodingCSP2SAT.cpp

Objetos/sat2csp/CSP2SAT.o: sat2csp/CSP2SAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat2csp/CSP2SAT.o sat2csp/CSP2SAT.cpp

Objetos/sat2csp/DualEncodingSAT2CSP.o: sat2csp/DualEncodingSAT2CSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/sat2csp/DualEncodingSAT2CSP.o sat2csp/DualEncodingSAT2CSP.cpp

Objetos/csp/RandomCSP.o: csp/RandomCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/RandomCSP.o csp/RandomCSP.cpp

Objetos/csp/BasicCSP.o: csp/BasicCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/BasicCSP.o csp/BasicCSP.cpp

Objetos/csp/CSPGABuilder.o: csp/CSPGABuilder.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPGABuilder.o csp/CSPGABuilder.cpp

Objetos/csp/CSPInterpretation.o: csp/CSPInterpretation.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPInterpretation.o csp/CSPInterpretation.cpp

Objetos/csp/CSPGeneticSolverExtraData.o: csp/CSPGeneticSolverExtraData.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPGeneticSolverExtraData.o csp/CSPGeneticSolverExtraData.cpp

Objetos/csp/MinConflicts.o: csp/MinConflicts.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/MinConflicts.o csp/MinConflicts.cpp

Objetos/csp/NQueensCSPConstraintList.o: csp/NQueensCSPConstraintList.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/NQueensCSPConstraintList.o csp/NQueensCSPConstraintList.cpp

Objetos/csp/VirtualCSPDomainList.o: csp/VirtualCSPDomainList.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/VirtualCSPDomainList.o csp/VirtualCSPDomainList.cpp

Objetos/csp/BasicCSPConstraintList.o: csp/BasicCSPConstraintList.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/BasicCSPConstraintList.o csp/BasicCSPConstraintList.cpp

Objetos/csp/CSPGeneticOperators.o: csp/CSPGeneticOperators.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPGeneticOperators.o csp/CSPGeneticOperators.cpp

Objetos/csp/CSPChromossomeImprover.o: csp/CSPChromossomeImprover.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPChromossomeImprover.o csp/CSPChromossomeImprover.cpp

Objetos/csp/Constraint.o: csp/Constraint.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/Constraint.o csp/Constraint.cpp

Objetos/csp/NQueensCSP.o: csp/NQueensCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/NQueensCSP.o csp/NQueensCSP.cpp

Objetos/csp/CSPVariableDomain.o: csp/CSPVariableDomain.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPVariableDomain.o csp/CSPVariableDomain.cpp

Objetos/csp/CrosswordsCSP.o: csp/CrosswordsCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CrosswordsCSP.o csp/CrosswordsCSP.cpp

Objetos/csp/CSPProblem.o: csp/CSPProblem.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPProblem.o csp/CSPProblem.cpp

Objetos/csp/BasicCSPDomainList.o: csp/BasicCSPDomainList.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/BasicCSPDomainList.o csp/BasicCSPDomainList.cpp

Objetos/csp/CSPVariableValue.o: csp/CSPVariableValue.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/csp/CSPVariableValue.o csp/CSPVariableValue.cpp

Objetos/aco/AntSolver2.o: aco/AntSolver2.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/aco/AntSolver2.o aco/AntSolver2.cpp

Objetos/aco/AntSolverGraph2.o: aco/AntSolverGraph2.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/aco/AntSolverGraph2.o aco/AntSolverGraph2.cpp

Objetos/aco/AntSolverGraph.o: aco/AntSolverGraph.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/aco/AntSolverGraph.o aco/AntSolverGraph.cpp

Objetos/aco/AntSolver.o: aco/AntSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/aco/AntSolver.o aco/AntSolver.cpp

Objetos/tests/testMinConflicts.o: tests/testMinConflicts.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/testMinConflicts.o tests/testMinConflicts.cpp

Objetos/tests/TestMain.o: tests/TestMain.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestMain.o tests/TestMain.cpp

Objetos/tests/TestSATLIBParser.o: tests/TestSATLIBParser.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestSATLIBParser.o tests/TestSATLIBParser.cpp

Objetos/tests/BenchmarkGeneticSAT.o: tests/BenchmarkGeneticSAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/BenchmarkGeneticSAT.o tests/BenchmarkGeneticSAT.cpp

Objetos/tests/TestProperties.o: tests/TestProperties.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestProperties.o tests/TestProperties.cpp

Objetos/tests/TestGeneticSAT.o: tests/TestGeneticSAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestGeneticSAT.o tests/TestGeneticSAT.cpp

Objetos/tests/TestDualEncoding.o: tests/TestDualEncoding.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestDualEncoding.o tests/TestDualEncoding.cpp

Objetos/tests/TestNQueensCSP.o: tests/TestNQueensCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestNQueensCSP.o tests/TestNQueensCSP.cpp

Objetos/tests/TestBitArray.o: tests/TestBitArray.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestBitArray.o tests/TestBitArray.cpp

Objetos/tests/TestAntSolver.o: tests/TestAntSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestAntSolver.o tests/TestAntSolver.cpp

Objetos/tests/TestBasicCSP.o: tests/TestBasicCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestBasicCSP.o tests/TestBasicCSP.cpp

Objetos/tests/TestRandomCSP.o: tests/TestRandomCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestRandomCSP.o tests/TestRandomCSP.cpp

Objetos/tests/TestCNFFormula.o: tests/TestCNFFormula.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestCNFFormula.o tests/TestCNFFormula.cpp

Objetos/tests/testCSPToSAT.o: tests/testCSPToSAT.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/testCSPToSAT.o tests/testCSPToSAT.cpp

Objetos/tests/TestCrosswordCSP.o: tests/TestCrosswordCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestCrosswordCSP.o tests/TestCrosswordCSP.cpp

Objetos/tests/TestArcConsistency.o: tests/TestArcConsistency.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestArcConsistency.o tests/TestArcConsistency.cpp

Objetos/tests/TestGeneticCSP.o: tests/TestGeneticCSP.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestGeneticCSP.o tests/TestGeneticCSP.cpp

Objetos/tests/Test2SATSolver.o: tests/Test2SATSolver.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/Test2SATSolver.o tests/Test2SATSolver.cpp

Objetos/tests/TestSATInterpretation.o: tests/TestSATInterpretation.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/tests/TestSATInterpretation.o tests/TestSATInterpretation.cpp

Objetos/./main.o: main.cpp
	$(CPP) $(CPPFLAGS) -o Objetos/./main.o main.cpp

# DO NOT DELETE

ga/GeneticSolver.o: /usr/include/stdlib.h /usr/include/features.h
ga/GeneticSolver.o: /usr/include/stdc-predef.h /usr/include/alloca.h
ga/GeneticSolver.o: ./ga/GeneticSolver.h ./util/Random.h
sat/2SATSolver.o: /usr/include/stdlib.h /usr/include/features.h
sat/2SATSolver.o: /usr/include/stdc-predef.h /usr/include/alloca.h
sat/2SATSolver.o: ./sat/2SATSolver.h ./sat/CNFFormula.h
sat/2SATSolver.o: ./sat/Interpretation.h ./sat/Clause.h ./util/Random.h
sat/Interpretation.o: ./sat/Interpretation.h /usr/include/memory.h
sat/Interpretation.o: /usr/include/features.h /usr/include/stdc-predef.h
sat/Interpretation.o: /usr/include/string.h
sat/CNFGeneticOperators.o: /usr/include/stdlib.h /usr/include/features.h
sat/CNFGeneticOperators.o: /usr/include/stdc-predef.h /usr/include/alloca.h
sat/CNFGeneticOperators.o: ./sat/CNFGeneticOperators.h ./ga/GeneticSolver.h
sat/CNFGeneticOperators.o: ./util/Random.h
sat/Clause.o: ./sat/Clause.h ./sat/Interpretation.h /usr/include/memory.h
sat/Clause.o: /usr/include/features.h /usr/include/stdc-predef.h
sat/Clause.o: /usr/include/string.h /usr/include/stdio.h /usr/include/libio.h
sat/Clause.o: /usr/include/_G_config.h /usr/include/wchar.h
sat/CNFFormula.o: ./sat/CNFFormula.h ./sat/Interpretation.h ./sat/Clause.h
sat/CNFFormula.o: /usr/include/stdio.h /usr/include/features.h
sat/CNFFormula.o: /usr/include/stdc-predef.h /usr/include/libio.h
sat/CNFFormula.o: /usr/include/_G_config.h /usr/include/wchar.h
sat/SATGABuilder.o: ./sat/SATGABuilder.h ./sat/CNFFormula.h
sat/SATGABuilder.o: ./sat/Interpretation.h ./sat/Clause.h
sat/SATGABuilder.o: ./ga/GeneticSolver.h ./sat/CNFFitnessEvaluator.h
sat/SATGABuilder.o: ./sat/CNFGeneticOperators.h
sat/SATGABuilder.o: ./sat/CNFChromossomeImprover.h
sat/CNFChromossomeImprover.o: /usr/include/stdio.h /usr/include/features.h
sat/CNFChromossomeImprover.o: /usr/include/stdc-predef.h /usr/include/libio.h
sat/CNFChromossomeImprover.o: /usr/include/_G_config.h /usr/include/wchar.h
sat/CNFChromossomeImprover.o: /usr/include/stdlib.h /usr/include/alloca.h
sat/CNFChromossomeImprover.o: /usr/include/memory.h /usr/include/string.h
sat/CNFChromossomeImprover.o: ./sat/CNFChromossomeImprover.h
sat/CNFChromossomeImprover.o: ./ga/GeneticSolver.h ./sat/CNFFormula.h
sat/CNFChromossomeImprover.o: ./sat/Interpretation.h ./sat/Clause.h
sat/CNFChromossomeImprover.o: ./util/Random.h
sat/BasicCNFSolver.o: ./sat/Interpretation.h ./sat/BasicCNFSolver.h
sat/BasicCNFSolver.o: ./sat/CNFFormula.h ./sat/Clause.h
sat/SATLIBParser.o: ./sat/CNFFormula.h ./sat/Interpretation.h ./sat/Clause.h
sat/SATLIBParser.o: ./sat/SATLIBParser.h /usr/include/stdio.h
sat/SATLIBParser.o: /usr/include/features.h /usr/include/stdc-predef.h
sat/SATLIBParser.o: /usr/include/libio.h /usr/include/_G_config.h
sat/SATLIBParser.o: /usr/include/wchar.h /usr/include/string.h
sat/SATLIBParser.o: /usr/include/stdlib.h /usr/include/alloca.h
sat/CNFFitnessEvaluator.o: /usr/include/stdio.h /usr/include/features.h
sat/CNFFitnessEvaluator.o: /usr/include/stdc-predef.h /usr/include/libio.h
sat/CNFFitnessEvaluator.o: /usr/include/_G_config.h /usr/include/wchar.h
sat/CNFFitnessEvaluator.o: /usr/include/memory.h /usr/include/string.h
sat/CNFFitnessEvaluator.o: ./sat/CNFFitnessEvaluator.h ./ga/GeneticSolver.h
sat/CNFFitnessEvaluator.o: ./sat/CNFFormula.h ./sat/Interpretation.h
sat/CNFFitnessEvaluator.o: ./sat/Clause.h
util/Timer.o: ./util/Timer.h
util/XString.o: /usr/include/string.h /usr/include/features.h
util/XString.o: /usr/include/stdc-predef.h ./util/XString.h
util/Properties.o: /usr/include/stdio.h /usr/include/features.h
util/Properties.o: /usr/include/stdc-predef.h /usr/include/libio.h
util/Properties.o: /usr/include/_G_config.h /usr/include/wchar.h
util/Properties.o: /usr/include/stdlib.h /usr/include/alloca.h
util/Properties.o: /usr/include/string.h ./util/Properties.h ./util/XString.h
util/BitArrayOps.o: /usr/include/memory.h /usr/include/features.h
util/BitArrayOps.o: /usr/include/stdc-predef.h /usr/include/string.h
util/BitArrayOps.o: ./util/BitArrayOps.h
util/Random.o: /usr/include/time.h /usr/include/features.h
util/Random.o: /usr/include/stdc-predef.h /usr/include/stdlib.h
util/Random.o: /usr/include/alloca.h util/Random.h
util/EnumDir.o: /usr/include/string.h /usr/include/features.h
util/EnumDir.o: /usr/include/stdc-predef.h /usr/include/fnmatch.h
util/EnumDir.o: ./util/EnumDir.h /usr/include/dirent.h ./util/XString.h
benchmarks/benchmarkAntSolver.o: /usr/include/string.h
benchmarks/benchmarkAntSolver.o: /usr/include/features.h
benchmarks/benchmarkAntSolver.o: /usr/include/stdc-predef.h
benchmarks/benchmarkAntSolver.o: /usr/include/stdlib.h /usr/include/alloca.h
benchmarks/benchmarkAntSolver.o: ./sat/SATLIBParser.h ./sat/CNFFormula.h
benchmarks/benchmarkAntSolver.o: ./sat/Interpretation.h ./sat/Clause.h
benchmarks/benchmarkAntSolver.o: /usr/include/stdio.h /usr/include/libio.h
benchmarks/benchmarkAntSolver.o: /usr/include/_G_config.h
benchmarks/benchmarkAntSolver.o: /usr/include/wchar.h ./util/Random.h
benchmarks/benchmarkAntSolver.o: ./util/Timer.h ./aco/AntSolver.h
benchmarks/benchmarkAntSolver.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
benchmarks/benchmarkAntSolver.o: ./csp/CSPVariableDomain.h
benchmarks/benchmarkAntSolver.o: ./csp/CSPVariableValue.h
benchmarks/benchmarkAntSolver.o: ./csp/CSPConstraintList.h
benchmarks/benchmarkAntSolver.o: ./csp/CSPInterpretation.h
benchmarks/benchmarkAntSolver.o: ./aco/AntSolverGraph.h ./csp/RandomCSP.h
benchmarks/benchmarkAntSolver.o: ./csp/Constraint.h
benchmarks/benchmarkAntSolver.o: ./sat2csp/DualEncodingSAT2CSP.h
benchmarks/benchmarkAntSolver.o: ./sat2csp/SAT2CSP.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/strings.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/features.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/stdc-predef.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/string.h /usr/include/stdlib.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/alloca.h ./ga/GeneticSolver.h
benchmarks/BenchmarkGeneticSAT.o: ./sat/CNFFormula.h ./sat/Interpretation.h
benchmarks/BenchmarkGeneticSAT.o: ./sat/Clause.h ./sat/SATGABuilder.h
benchmarks/BenchmarkGeneticSAT.o: ./sat/SATLIBParser.h /usr/include/stdio.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/libio.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/_G_config.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/wchar.h ./util/BitArrayOps.h
benchmarks/BenchmarkGeneticSAT.o: ./util/Random.h ./util/Timer.h
benchmarks/BenchmarkGeneticSAT.o: ./util/Properties.h ./util/EnumDir.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/dirent.h /usr/include/unistd.h
benchmarks/BenchmarkGeneticSAT.o: /usr/include/getopt.h
benchmarks/benchmarkAntSolver2.o: ./sat/SATLIBParser.h ./sat/CNFFormula.h
benchmarks/benchmarkAntSolver2.o: ./sat/Interpretation.h ./sat/Clause.h
benchmarks/benchmarkAntSolver2.o: /usr/include/stdio.h
benchmarks/benchmarkAntSolver2.o: /usr/include/features.h
benchmarks/benchmarkAntSolver2.o: /usr/include/stdc-predef.h
benchmarks/benchmarkAntSolver2.o: /usr/include/libio.h
benchmarks/benchmarkAntSolver2.o: /usr/include/_G_config.h
benchmarks/benchmarkAntSolver2.o: /usr/include/wchar.h ./util/Random.h
benchmarks/benchmarkAntSolver2.o: ./util/Timer.h ./aco/AntSolver2.h
benchmarks/benchmarkAntSolver2.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
benchmarks/benchmarkAntSolver2.o: ./csp/CSPVariableDomain.h
benchmarks/benchmarkAntSolver2.o: ./csp/CSPVariableValue.h
benchmarks/benchmarkAntSolver2.o: ./csp/CSPConstraintList.h
benchmarks/benchmarkAntSolver2.o: ./csp/CSPInterpretation.h
benchmarks/benchmarkAntSolver2.o: ./aco/AntSolverGraph2.h ./csp/RandomCSP.h
benchmarks/benchmarkAntSolver2.o: ./csp/Constraint.h
benchmarks/benchmarkAntSolver2.o: ./sat2csp/DualEncodingSAT2CSP.h
benchmarks/benchmarkAntSolver2.o: ./sat2csp/SAT2CSP.h
benchmarks/benchmarkMain.o: /usr/include/string.h /usr/include/features.h
benchmarks/benchmarkMain.o: /usr/include/stdc-predef.h
sat2csp/DirectEncodingCSP2SAT.o: ./sat2csp/DirectEncodingCSP2SAT.h
sat2csp/DirectEncodingCSP2SAT.o: ./sat2csp/CSP2SAT.h ./csp/CSPProblem.h
sat2csp/DirectEncodingCSP2SAT.o: ./csp/CSPDomainList.h
sat2csp/DirectEncodingCSP2SAT.o: ./csp/CSPVariableDomain.h
sat2csp/DirectEncodingCSP2SAT.o: ./csp/CSPVariableValue.h
sat2csp/DirectEncodingCSP2SAT.o: ./csp/CSPConstraintList.h
sat2csp/DirectEncodingCSP2SAT.o: ./csp/CSPInterpretation.h ./sat/CNFFormula.h
sat2csp/DirectEncodingCSP2SAT.o: ./sat/Interpretation.h ./sat/Clause.h
sat2csp/LogEncodingCSP2SAT.o: ./sat2csp/LogEncodingCSP2SAT.h
sat2csp/LogEncodingCSP2SAT.o: ./sat2csp/CSP2SAT.h ./csp/CSPProblem.h
sat2csp/LogEncodingCSP2SAT.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
sat2csp/LogEncodingCSP2SAT.o: ./csp/CSPVariableValue.h
sat2csp/LogEncodingCSP2SAT.o: ./csp/CSPConstraintList.h
sat2csp/LogEncodingCSP2SAT.o: ./csp/CSPInterpretation.h ./sat/CNFFormula.h
sat2csp/LogEncodingCSP2SAT.o: ./sat/Interpretation.h ./sat/Clause.h
sat2csp/CSP2SAT.o: ./sat2csp/CSP2SAT.h ./csp/CSPProblem.h
sat2csp/CSP2SAT.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
sat2csp/CSP2SAT.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
sat2csp/CSP2SAT.o: ./csp/CSPInterpretation.h ./sat/CNFFormula.h
sat2csp/CSP2SAT.o: ./sat/Interpretation.h ./sat/Clause.h
sat2csp/DualEncodingSAT2CSP.o: /usr/include/stdio.h /usr/include/features.h
sat2csp/DualEncodingSAT2CSP.o: /usr/include/stdc-predef.h
sat2csp/DualEncodingSAT2CSP.o: /usr/include/libio.h /usr/include/_G_config.h
sat2csp/DualEncodingSAT2CSP.o: /usr/include/wchar.h /usr/include/math.h
sat2csp/DualEncodingSAT2CSP.o: ./sat2csp/DualEncodingSAT2CSP.h
sat2csp/DualEncodingSAT2CSP.o: ./sat2csp/SAT2CSP.h ./sat/CNFFormula.h
sat2csp/DualEncodingSAT2CSP.o: ./sat/Interpretation.h ./sat/Clause.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/CSPVariableDomain.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/CSPVariableValue.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/CSPConstraintList.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/BasicCSPDomainList.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/BasicCSPConstraintList.h
sat2csp/DualEncodingSAT2CSP.o: ./csp/BasicCSP.h ./util/BitArrayOps.h
csp/RandomCSP.o: ./util/Random.h ./csp/BasicCSP.h ./csp/CSPProblem.h
csp/RandomCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/RandomCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
csp/RandomCSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
csp/RandomCSP.o: ./csp/BasicCSPConstraintList.h ./csp/BasicCSPDomainList.h
csp/RandomCSP.o: ./csp/RandomCSP.h
csp/BasicCSP.o: ./csp/BasicCSP.h ./csp/CSPProblem.h ./csp/CSPDomainList.h
csp/BasicCSP.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
csp/BasicCSP.o: ./csp/CSPConstraintList.h ./csp/CSPInterpretation.h
csp/BasicCSP.o: ./csp/Constraint.h
csp/CSPGABuilder.o: ./csp/CSPGABuilder.h ./csp/CSPProblem.h
csp/CSPGABuilder.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/CSPGABuilder.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
csp/CSPGABuilder.o: ./csp/CSPInterpretation.h ./ga/GeneticSolver.h
csp/CSPGABuilder.o: ./csp/CSPGeneticOperators.h
csp/CSPGABuilder.o: ./csp/CSPChromossomeImprover.h
csp/CSPGABuilder.o: ./csp/CSPGeneticSolverExtraData.h
csp/CSPInterpretation.o: /usr/include/string.h /usr/include/features.h
csp/CSPInterpretation.o: /usr/include/stdc-predef.h ./csp/CSPInterpretation.h
csp/CSPGeneticSolverExtraData.o: /usr/include/stdio.h /usr/include/features.h
csp/CSPGeneticSolverExtraData.o: /usr/include/stdc-predef.h
csp/CSPGeneticSolverExtraData.o: /usr/include/libio.h
csp/CSPGeneticSolverExtraData.o: /usr/include/_G_config.h
csp/CSPGeneticSolverExtraData.o: /usr/include/wchar.h
csp/CSPGeneticSolverExtraData.o: ./csp/CSPGeneticSolverExtraData.h
csp/CSPGeneticSolverExtraData.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
csp/CSPGeneticSolverExtraData.o: ./csp/CSPVariableDomain.h
csp/CSPGeneticSolverExtraData.o: ./csp/CSPVariableValue.h
csp/CSPGeneticSolverExtraData.o: ./csp/CSPConstraintList.h
csp/CSPGeneticSolverExtraData.o: ./csp/CSPInterpretation.h
csp/CSPGeneticSolverExtraData.o: ./ga/GeneticSolver.h
csp/MinConflicts.o: ./csp/MinConflicts.h ./csp/CSPProblem.h
csp/MinConflicts.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/MinConflicts.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
csp/MinConflicts.o: ./csp/CSPInterpretation.h ./csp/CSPLocalSearch.h
csp/MinConflicts.o: ./util/Random.h
csp/NQueensCSPConstraintList.o: /usr/include/assert.h /usr/include/features.h
csp/NQueensCSPConstraintList.o: /usr/include/stdc-predef.h
csp/NQueensCSPConstraintList.o: /usr/include/math.h
csp/NQueensCSPConstraintList.o: ./csp/NQueensCSPConstraintList.h
csp/NQueensCSPConstraintList.o: ./csp/CSPConstraintList.h
csp/NQueensCSPConstraintList.o: ./csp/CSPInterpretation.h
csp/VirtualCSPDomainList.o: /usr/include/stdio.h /usr/include/features.h
csp/VirtualCSPDomainList.o: /usr/include/stdc-predef.h /usr/include/libio.h
csp/VirtualCSPDomainList.o: /usr/include/_G_config.h /usr/include/wchar.h
csp/VirtualCSPDomainList.o: /usr/include/assert.h
csp/VirtualCSPDomainList.o: ./csp/VirtualCSPDomainList.h
csp/VirtualCSPDomainList.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/VirtualCSPDomainList.o: ./csp/CSPVariableValue.h
csp/BasicCSPConstraintList.o: /usr/include/stdio.h /usr/include/features.h
csp/BasicCSPConstraintList.o: /usr/include/stdc-predef.h /usr/include/libio.h
csp/BasicCSPConstraintList.o: /usr/include/_G_config.h /usr/include/wchar.h
csp/BasicCSPConstraintList.o: /usr/include/assert.h
csp/BasicCSPConstraintList.o: ./csp/BasicCSPConstraintList.h
csp/BasicCSPConstraintList.o: ./csp/CSPConstraintList.h
csp/BasicCSPConstraintList.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
csp/CSPGeneticOperators.o: ./csp/CSPGeneticOperators.h ./ga/GeneticSolver.h
csp/CSPGeneticOperators.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
csp/CSPGeneticOperators.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
csp/CSPGeneticOperators.o: ./csp/CSPConstraintList.h
csp/CSPGeneticOperators.o: ./csp/CSPInterpretation.h ./util/Random.h
csp/CSPChromossomeImprover.o: ./csp/CSPChromossomeImprover.h
csp/CSPChromossomeImprover.o: ./ga/GeneticSolver.h ./csp/CSPProblem.h
csp/CSPChromossomeImprover.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/CSPChromossomeImprover.o: ./csp/CSPVariableValue.h
csp/CSPChromossomeImprover.o: ./csp/CSPConstraintList.h
csp/CSPChromossomeImprover.o: ./csp/CSPInterpretation.h ./util/Random.h
csp/Constraint.o: ./csp/Constraint.h ./csp/CSPInterpretation.h
csp/NQueensCSP.o: /usr/include/stdio.h /usr/include/features.h
csp/NQueensCSP.o: /usr/include/stdc-predef.h /usr/include/libio.h
csp/NQueensCSP.o: /usr/include/_G_config.h /usr/include/wchar.h
csp/NQueensCSP.o: /usr/include/stdlib.h /usr/include/alloca.h
csp/NQueensCSP.o: /usr/include/math.h ./csp/NQueensCSP.h ./csp/CSPProblem.h
csp/NQueensCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/NQueensCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
csp/NQueensCSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
csp/NQueensCSP.o: ./csp/BasicCSP.h ./csp/VirtualCSPDomainList.h
csp/NQueensCSP.o: ./csp/BasicCSPConstraintList.h
csp/NQueensCSP.o: ./csp/NQueensCSPConstraintList.h
csp/CSPVariableDomain.o: /usr/include/stdio.h /usr/include/features.h
csp/CSPVariableDomain.o: /usr/include/stdc-predef.h /usr/include/libio.h
csp/CSPVariableDomain.o: /usr/include/_G_config.h /usr/include/wchar.h
csp/CSPVariableDomain.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
csp/CrosswordsCSP.o: ./csp/BasicCSP.h ./csp/CSPProblem.h
csp/CrosswordsCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
csp/CrosswordsCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
csp/CrosswordsCSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
csp/CrosswordsCSP.o: ./csp/CrosswordsCSP.h /usr/include/stdio.h
csp/CrosswordsCSP.o: /usr/include/features.h /usr/include/stdc-predef.h
csp/CrosswordsCSP.o: /usr/include/libio.h /usr/include/_G_config.h
csp/CrosswordsCSP.o: /usr/include/wchar.h /usr/include/memory.h
csp/CrosswordsCSP.o: /usr/include/string.h ./csp/BasicCSPDomainList.h
csp/CrosswordsCSP.o: ./csp/BasicCSPConstraintList.h
csp/CSPProblem.o: /usr/include/memory.h /usr/include/features.h
csp/CSPProblem.o: /usr/include/stdc-predef.h /usr/include/string.h
csp/CSPProblem.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
csp/CSPProblem.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
csp/CSPProblem.o: ./csp/CSPConstraintList.h ./csp/CSPInterpretation.h
csp/BasicCSPDomainList.o: /usr/include/stdio.h /usr/include/features.h
csp/BasicCSPDomainList.o: /usr/include/stdc-predef.h /usr/include/libio.h
csp/BasicCSPDomainList.o: /usr/include/_G_config.h /usr/include/wchar.h
csp/BasicCSPDomainList.o: ./csp/BasicCSPDomainList.h ./csp/CSPDomainList.h
csp/BasicCSPDomainList.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
csp/CSPVariableValue.o: ./csp/CSPVariableValue.h
aco/AntSolver2.o: /usr/include/stdio.h /usr/include/features.h
aco/AntSolver2.o: /usr/include/stdc-predef.h /usr/include/libio.h
aco/AntSolver2.o: /usr/include/_G_config.h /usr/include/wchar.h
aco/AntSolver2.o: /usr/include/math.h ./aco/AntSolver2.h ./csp/CSPProblem.h
aco/AntSolver2.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
aco/AntSolver2.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
aco/AntSolver2.o: ./csp/CSPInterpretation.h ./aco/AntSolverGraph2.h
aco/AntSolver2.o: ./util/Random.h ./csp/MinConflicts.h ./csp/CSPLocalSearch.h
aco/AntSolverGraph2.o: ./aco/AntSolverGraph2.h ./csp/CSPProblem.h
aco/AntSolverGraph2.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
aco/AntSolverGraph2.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
aco/AntSolverGraph2.o: ./csp/CSPInterpretation.h
aco/AntSolverGraph.o: ./aco/AntSolverGraph.h ./csp/CSPProblem.h
aco/AntSolverGraph.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
aco/AntSolverGraph.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
aco/AntSolverGraph.o: ./csp/CSPInterpretation.h
aco/AntSolver.o: /usr/include/stdio.h /usr/include/features.h
aco/AntSolver.o: /usr/include/stdc-predef.h /usr/include/libio.h
aco/AntSolver.o: /usr/include/_G_config.h /usr/include/wchar.h
aco/AntSolver.o: /usr/include/math.h ./aco/AntSolver.h ./csp/CSPProblem.h
aco/AntSolver.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
aco/AntSolver.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
aco/AntSolver.o: ./csp/CSPInterpretation.h ./aco/AntSolverGraph.h
aco/AntSolver.o: ./util/Random.h ./csp/MinConflicts.h ./csp/CSPLocalSearch.h
tests/testMinConflicts.o: ./sat/SATLIBParser.h ./sat/CNFFormula.h
tests/testMinConflicts.o: ./sat/Interpretation.h ./sat/Clause.h
tests/testMinConflicts.o: /usr/include/stdio.h /usr/include/features.h
tests/testMinConflicts.o: /usr/include/stdc-predef.h /usr/include/libio.h
tests/testMinConflicts.o: /usr/include/_G_config.h /usr/include/wchar.h
tests/testMinConflicts.o: ./util/Random.h ./csp/MinConflicts.h
tests/testMinConflicts.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
tests/testMinConflicts.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
tests/testMinConflicts.o: ./csp/CSPConstraintList.h ./csp/CSPInterpretation.h
tests/testMinConflicts.o: ./csp/CSPLocalSearch.h ./csp/NQueensCSP.h
tests/testMinConflicts.o: ./csp/Constraint.h ./csp/RandomCSP.h
tests/testMinConflicts.o: ./sat2csp/DualEncodingSAT2CSP.h ./sat2csp/SAT2CSP.h
tests/TestMain.o: /usr/include/string.h /usr/include/features.h
tests/TestMain.o: /usr/include/stdc-predef.h
tests/TestSATLIBParser.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/TestSATLIBParser.o: ./sat/Clause.h ./sat/SATLIBParser.h
tests/TestSATLIBParser.o: /usr/include/stdio.h /usr/include/features.h
tests/TestSATLIBParser.o: /usr/include/stdc-predef.h /usr/include/libio.h
tests/TestSATLIBParser.o: /usr/include/_G_config.h /usr/include/wchar.h
tests/BenchmarkGeneticSAT.o: /usr/include/string.h /usr/include/features.h
tests/BenchmarkGeneticSAT.o: /usr/include/stdc-predef.h /usr/include/stdlib.h
tests/BenchmarkGeneticSAT.o: /usr/include/alloca.h ./ga/GeneticSolver.h
tests/BenchmarkGeneticSAT.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/BenchmarkGeneticSAT.o: ./sat/Clause.h ./sat/SATGABuilder.h
tests/BenchmarkGeneticSAT.o: ./sat/SATLIBParser.h /usr/include/stdio.h
tests/BenchmarkGeneticSAT.o: /usr/include/libio.h /usr/include/_G_config.h
tests/BenchmarkGeneticSAT.o: /usr/include/wchar.h ./util/BitArrayOps.h
tests/BenchmarkGeneticSAT.o: ./util/Random.h ./util/Timer.h
tests/BenchmarkGeneticSAT.o: ./util/Properties.h ./util/EnumDir.h
tests/BenchmarkGeneticSAT.o: /usr/include/dirent.h /usr/include/unistd.h
tests/BenchmarkGeneticSAT.o: /usr/include/getopt.h
tests/TestProperties.o: ./util/Properties.h
tests/TestGeneticSAT.o: /usr/include/time.h /usr/include/features.h
tests/TestGeneticSAT.o: /usr/include/stdc-predef.h ./sat/SATLIBParser.h
tests/TestGeneticSAT.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/TestGeneticSAT.o: ./sat/Clause.h /usr/include/stdio.h
tests/TestGeneticSAT.o: /usr/include/libio.h /usr/include/_G_config.h
tests/TestGeneticSAT.o: /usr/include/wchar.h ./util/Timer.h ./util/Random.h
tests/TestGeneticSAT.o: ./sat/SATGABuilder.h ./ga/GeneticSolver.h
tests/TestDualEncoding.o: ./sat2csp/DualEncodingSAT2CSP.h ./sat2csp/SAT2CSP.h
tests/TestDualEncoding.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/TestDualEncoding.o: ./sat/Clause.h ./csp/CSPProblem.h
tests/TestDualEncoding.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestDualEncoding.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
tests/TestDualEncoding.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
tests/TestDualEncoding.o: ./sat/SATLIBParser.h /usr/include/stdio.h
tests/TestDualEncoding.o: /usr/include/features.h /usr/include/stdc-predef.h
tests/TestDualEncoding.o: /usr/include/libio.h /usr/include/_G_config.h
tests/TestDualEncoding.o: /usr/include/wchar.h ./aco/AntSolver.h
tests/TestDualEncoding.o: ./aco/AntSolverGraph.h ./util/Random.h
tests/TestDualEncoding.o: ./csp/BasicCSP.h
tests/TestNQueensCSP.o: ./csp/NQueensCSP.h ./csp/CSPProblem.h
tests/TestNQueensCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestNQueensCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
tests/TestNQueensCSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
tests/TestBitArray.o: ./util/BitArrayOps.h ./util/Random.h
tests/TestAntSolver.o: ./util/Random.h ./aco/AntSolver.h ./csp/CSPProblem.h
tests/TestAntSolver.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestAntSolver.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
tests/TestAntSolver.o: ./csp/CSPInterpretation.h ./aco/AntSolverGraph.h
tests/TestAntSolver.o: ./csp/NQueensCSP.h ./csp/Constraint.h
tests/TestAntSolver.o: ./csp/RandomCSP.h
tests/TestBasicCSP.o: ./csp/BasicCSP.h ./csp/CSPProblem.h
tests/TestBasicCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestBasicCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
tests/TestBasicCSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
tests/TestBasicCSP.o: ./csp/CrosswordsCSP.h /usr/include/stdio.h
tests/TestBasicCSP.o: /usr/include/features.h /usr/include/stdc-predef.h
tests/TestBasicCSP.o: /usr/include/libio.h /usr/include/_G_config.h
tests/TestBasicCSP.o: /usr/include/wchar.h /usr/include/memory.h
tests/TestBasicCSP.o: /usr/include/string.h
tests/TestRandomCSP.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
tests/TestRandomCSP.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
tests/TestRandomCSP.o: ./csp/CSPConstraintList.h ./csp/CSPInterpretation.h
tests/TestRandomCSP.o: ./csp/RandomCSP.h ./csp/Constraint.h
tests/TestRandomCSP.o: ./csp/CSPGABuilder.h ./ga/GeneticSolver.h
tests/TestCNFFormula.o: ./sat/BasicCNFSolver.h ./sat/CNFFormula.h
tests/TestCNFFormula.o: ./sat/Interpretation.h ./sat/Clause.h
tests/testCSPToSAT.o: /usr/include/time.h /usr/include/features.h
tests/testCSPToSAT.o: /usr/include/stdc-predef.h ./sat/SATGABuilder.h
tests/testCSPToSAT.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/testCSPToSAT.o: ./sat/Clause.h ./ga/GeneticSolver.h ./csp/NQueensCSP.h
tests/testCSPToSAT.o: ./csp/CSPProblem.h ./csp/CSPDomainList.h
tests/testCSPToSAT.o: ./csp/CSPVariableDomain.h ./csp/CSPVariableValue.h
tests/testCSPToSAT.o: ./csp/CSPConstraintList.h ./csp/CSPInterpretation.h
tests/testCSPToSAT.o: ./csp/Constraint.h ./sat2csp/DirectEncodingCSP2SAT.h
tests/testCSPToSAT.o: ./sat2csp/CSP2SAT.h ./sat2csp/LogEncodingCSP2SAT.h
tests/testCSPToSAT.o: ./util/Random.h ./util/Timer.h
tests/TestCrosswordCSP.o: ./csp/CrosswordsCSP.h ./csp/CSPProblem.h
tests/TestCrosswordCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestCrosswordCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
tests/TestCrosswordCSP.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
tests/TestCrosswordCSP.o: /usr/include/stdio.h /usr/include/features.h
tests/TestCrosswordCSP.o: /usr/include/stdc-predef.h /usr/include/libio.h
tests/TestCrosswordCSP.o: /usr/include/_G_config.h /usr/include/wchar.h
tests/TestCrosswordCSP.o: /usr/include/memory.h /usr/include/string.h
tests/TestCrosswordCSP.o: ./csp/BasicCSP.h
tests/TestArcConsistency.o: ./csp/CrosswordsCSP.h ./csp/CSPProblem.h
tests/TestArcConsistency.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestArcConsistency.o: ./csp/CSPVariableValue.h
tests/TestArcConsistency.o: ./csp/CSPConstraintList.h
tests/TestArcConsistency.o: ./csp/CSPInterpretation.h ./csp/Constraint.h
tests/TestArcConsistency.o: /usr/include/stdio.h /usr/include/features.h
tests/TestArcConsistency.o: /usr/include/stdc-predef.h /usr/include/libio.h
tests/TestArcConsistency.o: /usr/include/_G_config.h /usr/include/wchar.h
tests/TestArcConsistency.o: /usr/include/memory.h /usr/include/string.h
tests/TestArcConsistency.o: ./csp/BasicCSP.h ./csp/BasicCSPDomainList.h
tests/TestGeneticCSP.o: ./ga/GeneticSolver.h ./csp/CSPProblem.h
tests/TestGeneticCSP.o: ./csp/CSPDomainList.h ./csp/CSPVariableDomain.h
tests/TestGeneticCSP.o: ./csp/CSPVariableValue.h ./csp/CSPConstraintList.h
tests/TestGeneticCSP.o: ./csp/CSPInterpretation.h ./csp/BasicCSP.h
tests/TestGeneticCSP.o: ./csp/Constraint.h ./csp/CSPGABuilder.h
tests/TestGeneticCSP.o: ./csp/CrosswordsCSP.h /usr/include/stdio.h
tests/TestGeneticCSP.o: /usr/include/features.h /usr/include/stdc-predef.h
tests/TestGeneticCSP.o: /usr/include/libio.h /usr/include/_G_config.h
tests/TestGeneticCSP.o: /usr/include/wchar.h /usr/include/memory.h
tests/TestGeneticCSP.o: /usr/include/string.h ./csp/NQueensCSP.h
tests/TestGeneticCSP.o: ./csp/BasicCSPDomainList.h ./util/Random.h
tests/Test2SATSolver.o: /usr/include/time.h /usr/include/features.h
tests/Test2SATSolver.o: /usr/include/stdc-predef.h /usr/include/stdlib.h
tests/Test2SATSolver.o: /usr/include/alloca.h ./sat/2SATSolver.h
tests/Test2SATSolver.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/Test2SATSolver.o: ./sat/Clause.h ./util/Timer.h ./util/Random.h
tests/Test2SATSolver.o: ./sat/SATLIBParser.h /usr/include/stdio.h
tests/Test2SATSolver.o: /usr/include/libio.h /usr/include/_G_config.h
tests/Test2SATSolver.o: /usr/include/wchar.h
tests/TestSATInterpretation.o: ./sat/CNFFormula.h ./sat/Interpretation.h
tests/TestSATInterpretation.o: ./sat/Clause.h
