TEMPLATE = subdirs

OTHER_FILES += \
    debian/rules \
    debian/README \
    debian/manifest.aegis \
    debian/copyright \
    debian/control \
    debian/compat \
    debian/changelog \
    debian/prerm \
    debian/postinst

SUBDIRS += \
    musicshaker \
    musicshakerd
