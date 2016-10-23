# vim: filetype=make :

win32:SEP=$$quote(\\)
!win32:SEP=$$quote(/)

CACHEFILE = $${OUT_PWD}$${SEP}.qmake.cache

exists($${CACHEFILE}) {
	warning(You may run qmake using -nocache option to avoid using current $${CACHEFILE} definitions)
}

defineTest(CACHERESET) {
	message(Creating $${CACHEFILE})
	msg = $$quote($${LITERAL_HASH} automatically created by $$basename(_PRO_FILE_) at $${_DATE_})
	unix:msg = $$quote(\'$$msg\')  # unix shell won't ignore msg as if it was a comment
	system(echo $$msg > $${CACHEFILE}) {
		return(true)
	}
	return(false)
}

defineTest(CACHEVAR) {
	var = $$quote($$1=$$quote($$eval($$1)))
	message(Storing $$var)
	system(echo $$var >> $${CACHEFILE})
	return(true)
}
