
############ Autoconf-generated variables  ###################
INCLUDES = $(all_includes)
LDFLAGS	= $(all_libraries) $(KDE_RPATH)
LDADD =  $(LIB_KDEUI)


bin_PROGRAMS = karm
SUBDIRS = doc support

karm_METASOURCES =  USE_AUTOMOC

karm_SOURCES =  version.h adddata.cpp adddlg.cpp karm.cpp main.cpp \
	task.cpp top.cpp kaccelmenuwatch.h kaccelmenuwatch.cpp 

noinst_HEADERS = adddata.h adddlg.h karm.h task.h toolicons.h top.h 

kde_icon_DATA = karm.xpm

EXTRA_DIST = $(kde_icon_DATA) mini-karm.xpm

appsdir = $(kde_appsdir)/Utilities

install-data-local:
	$(mkinstalldirs) $(appsdir)
	$(INSTALL_DATA) $(srcdir)/support/KArm.kdelnk $(appsdir)
	$(mkinstalldirs) $(kde_toolbardir)
	$(INSTALL_DATA) $(srcdir)/support/filedel.xpm $(kde_toolbardir)
	$(mkinstalldirs) $(kde_minidir)
	$(INSTALL_DATA) $(srcdir)/mini-karm.xpm $(kde_minidir)/karm.xpm
	$(mkinstalldirs) $(kde_icondir)/large
	$(INSTALL_DATA) $(srcdir)/large-karm.xpm $(kde_icondir)/large/karm.xpm

uninstall-local:
	rm -f $(kde_appsdir)/Utilities/KArm.kdelnk
	rm -f $(kde_minidir)/karm.xpm
	rm -f $(kde_icondir)/large/karm.xpm
	rm -f $(kde_toolbardir)/filedel.xpm
	-rmdir -p $(kde_toolbardir)
	-rmdir -p $(kde_minidir)
	-rmdir -p $(kde_appsdir)

messages:
	$(XGETTEXT) -C -ktranslate -ki18n -x $(includedir)/kde.pot *.cpp && mv messages.po ../po/karm.pot


srcdoc:
	kdoc -a -p -H -d $(HOME)/web/src/karm karm *.h -lkdecore -lkdeui -lqt

