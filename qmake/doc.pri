OUTPUT_DOC_DIR = $$BUILD_TREE/output/docs

doc.commands = \
    [ -d $$OUTPUT_DOC_DIR ] || mkdir -p $$OUTPUT_DOC_DIR ; \
    OUTPUT_DIRECTORY=$$OUTPUT_DOC_DIR \
    STRIP_FROM_PATH=$$SOURCE_TREE \
    doxygen $$SOURCE_TREE/docs/Doxyfile
doc.depends = FORCE

QMAKE_EXTRA_TARGETS += doc
