TEMPLATE = subdirs

OTHER_FILES += \
    debian/rules \
    debian/README \
    debian/manifest.aegis \
    debian/copyright \
    debian/control \
    debian/compat \
    debian/changelog

SUBDIRS += \
    musicshaker \
    musicshakerdaemon
