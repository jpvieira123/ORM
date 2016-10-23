# This is based on an old version of qttest_p4

TEMPLATE=app

CONFIG += qt debug warn_on console depend_includepath testcase

qtAddLibrary(QtTest)

# prefix test binary with tst_
!contains(TARGET, ^tst_.*):TARGET = $$join(TARGET,,"tst_")

########################################################################
# Use install rule to run test application.
# This lets you do 'make install' on a test to both build and run it,
# and lets you easily build and run all tests from the parent directory.
# ----------------------------------------------------------------------

runme.files                =
runme.path                 = .

!isEmpty(DESTDIR): runme.commands = cd ./$(DESTDIR) &&

macx:      runme.commands += ./$(QMAKE_TARGET).app/Contents/MacOS/$(QMAKE_TARGET)
else:unix: runme.commands += ./$(QMAKE_TARGET)
else:win32: {
    CONFIG(debug, debug|release):runme.commands += debug\\$(QMAKE_TARGET)
    else:runme.commands += release\\$(QMAKE_TARGET)
}
embedded:  runme.commands += -qws
INSTALLS += runme

# End of qttest_p4 based code

DEFINES   += TEST_DATA=$$SOURCE_TREE/tests/data

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_LIBS     += -lgcov
QMAKE_CLEAN    += *.gcno *.gcda
