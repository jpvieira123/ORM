OUTDIR=$$BUILD_TREE/output/doc/coverage

coverage_genhtml.commands = genhtml --output-directory $$OUTDIR \
                                    $$OUTDIR/coverage_final.info

coverage.commands = mkdir -p $$OUTDIR && \
                    lcov --capture --directory $$BUILD_TREE/src --output-file $$OUTDIR/coverage.info && \
                    lcov --extract $$OUTDIR/coverage.info \"$$SOURCE_TREE/src/*\" --output-file $$OUTDIR/coverage_extracted.info && \
                    lcov --remove $$OUTDIR/coverage_extracted.info \"*/test/*\" --output-file $$OUTDIR/coverage_final.info

run_tests.commands = cd $$BUILD_TREE/test/testsuite && $(MAKE) install

check.depends = sub-src run_tests coverage coverage_genhtml

QMAKE_EXTRA_TARGETS += check run_tests coverage coverage_genhtml
