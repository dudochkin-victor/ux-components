TEMPLATE = subdirs
CONFIG += ordered
TARGET =+ meego-ux-components

SUBDIRS += src \
           examples

include(doc/doc.pri)

OTHER_FILES += README

SOURCES += src

TRANSLATIONS += $${SOURCES} $${OTHER_FILES} $${HEADERS}
VERSION = 0.2.8.6
PROJECT_NAME = meego-ux-components

dist.commands += rm -fR $${PROJECT_NAME}-$${VERSION} &&
dist.commands += [ ! -e .git/refs/tags/$${VERSION} ] || git tag -d $${VERSION} &&
dist.commands += git tag $${VERSION} -m \"make dist auto-tag for $${VERSION}\" &&
dist.commands += git archive --prefix=$${PROJECT_NAME}-$${VERSION}/ $${VERSION} --format=tar | tar x &&
dist.commands += mkdir -p $${PROJECT_NAME}-$${VERSION}/ts &&
dist.commands += lupdate $${TRANSLATIONS} -ts $${PROJECT_NAME}-$${VERSION}/ts/$${PROJECT_NAME}.ts &&
dist.commands += tar jcpvf $${PROJECT_NAME}-$${VERSION}.tar.bz2 $${PROJECT_NAME}-$${VERSION}

QMAKE_EXTRA_TARGETS += dist

doc.depends += FORCE
doc.commands += cd doc &&
doc.commands += qdoc3 meego-ux-components.qdocconf &&
doc.commands += echo "Documentation created in doc/html/meego-ux-components.hmtl"
QMAKE_EXTRA_TARGETS += doc
