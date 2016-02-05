OBJECTS_DIR = obj
RCC_DIR = obj
MOC_DIR = obj
UI_DIR = obj

exists(/etc/astra_version):!defined(ASTRA) {
	message( "Configuring for Astra Linux build..." )
	DEFINES += ASTRA
}

exists(/etc/MCBC-release):!defined(MSVS_3) {
	message( "Configuring for MSVS 3 build..." )
	DEFINES += MSVS_3
}

exists(/etc/vniins-release):!defined(MSVS_5) {
	message( "Configuring for MSVS 5 build..." )
	DEFINES += MSVS_5
}

exists(/etc/debian_version):!defined(DEBIAN) {
	message( "Configuring for Debian linux build..." )
	DEFINES += DEBIAN
}

!isEmpty($(XDG_CURRENT_DESKTOP)) {
	message( join("DM is", " ", $(XDG_CURRENT_DESKTOP), "" ))
	DEFINES += $(XDG_CURRENT_DESKTOP)
}
