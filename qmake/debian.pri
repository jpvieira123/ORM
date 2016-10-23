# vim: filetype=make :

unix {

	deb.commands = cd $${SOURCE_TREE}; \
		LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):`ls -d libs/* | tr '[:space:]' :`:$${BUILD_TREE}/output/libs:$$[QT_INSTALL_LIBS] \
		dpkg-buildpackage -rfakeroot -b -uc -us $(DEB_BUILD_OPTIONS)

	QMAKE_EXTRA_TARGETS += deb

	qtconf.path = $${PREFIX}/bin
	qtconf.files = $${SOURCE_TREE}/data/qt.conf
	INSTALLS += qtconf

	dsmio.path = $${PREFIX}/libs
	dsmio.files = $${SOURCE_TREE}/binaries/libdsmio*
	INSTALLS += dsmio

	drma1.path = $${PREFIX}/libs
	drma1.files = $${SOURCE_TREE}/binaries/lib*
	INSTALLS += drma1

#	drma2.path = $${PREFIX}/libs
#	drma2.files = $${SOURCE_TREE}/binaries/libL*
#	INSTALLS += drma2

#	drma3.path = $${PREFIX}/libs
#	drma3.files = $${SOURCE_TREE}/binaries/libl*
#	INSTALLS += drma3

	drma4.path = $${PREFIX}/libs
	drma4.files = $${SOURCE_TREE}/binaries/DarumaFramework.xml
	INSTALLS += drma4

	QT_RUNTIME_LIBS = \
					  $$[QT_INSTALL_LIBS]/libphonon.so.$${QT_MAJOR_VERSION} \
					  $$[QT_INSTALL_LIBS]/libQt5Core.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5DBus.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Gui.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Network.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5OpenGL.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Script.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Sql.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5WebKit.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5XmlPatterns.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Xml.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Script.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5PrintSupport.so.$$[QT_VERSION] \
					  $$[QT_INSTALL_LIBS]/libQt5Widgets.so.$$[QT_VERSION]  \
                                          $$[QT_INSTALL_LIBS]/libicudata.so.53 \
					  $$[QT_INSTALL_LIBS]/libicuuc.so.53 \
                                          $$[QT_INSTALL_LIBS]/libicui18n.so.53

	qtruntime.path = $${PREFIX}/bin
	qtruntime.files = $${QT_RUNTIME_LIBS}
	INSTALLS += qtruntime

	qtsqlplugins.path = $${PREFIX}/bin/sqldrivers
	qtsqlplugins.files = $$[QT_INSTALL_PLUGINS]/sqldrivers/lib*
	INSTALLS += qtsqlplugins

	qtimgplugins.path = $${PREFIX}/bin/imageformats
	qtimgplugins.files = $$[QT_INSTALL_PLUGINS]/imageformats/*
	INSTALLS += qtimgplugins

	qtplaplugins.path = $${PREFIX}/bin/platforms
	qtplaplugins.files = $$[QT_INSTALL_PLUGINS]/platforms/*
	INSTALLS += qtplaplugins

	qtpriplugins.path = $${PREFIX}/bin/printsupport
	qtpriplugins.files = $$[QT_INSTALL_PLUGINS]/printsupport/*
	INSTALLS += qtpriplugins

	laudo.path = $${PREFIX}/bin
	laudo.files = $${SOURCE_TREE}/src/dsm-paf/laudo.xml
	INSTALLS += laudo

	icons.path = $${PREFIX}/icons
	icons.files = $${SOURCE_TREE}/icons/dsm.png
	INSTALLS += icons

	desktop.path = $${PREFIX}/data
	desktop.files = $${SOURCE_TREE}/data/xdg/*
	INSTALLS += desktop

	fonts.path = /usr/share/fonts/truetype
	fonts.files = $${SOURCE_TREE}/data/fonts/*ttf
	INSTALLS += fonts

}
