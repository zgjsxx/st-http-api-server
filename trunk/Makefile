.PHONY: default all _default install help clean destroy server srs_ingest_hls utest _prepare_dir 
.PHONY: clean_srs clean_modules clean_openssl clean_srtp2 clean_opus clean_ffmpeg clean_st
.PHONY: st ffmpeg

GCC = gcc
CXX = g++
AR = ar
LINK = ld
RANDLIB = randlib
CXXFLAGS =  -std=c++11 -Wall -Wno-deprecated-declarations -g -O0

# install prefix.
SRS_PREFIX=/usr/local/srs
SRS_DEFAULT_CONFIG=conf/srs.conf
__REAL_INSTALL=$(DESTDIR)$(SRS_PREFIX)

default: server

all: _default

_default: server srs_ingest_hls utest 

help:
	@echo "Usage: make <help>|<clean>|<destroy>|<server>|<utest>|<install>|<uninstall>"
	@echo "     help            Display this help menu"
	@echo "     clean           Cleanup project and all depends"
	@echo "     destroy         Cleanup all files for this platform in objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64"
	@echo "     server          Build the srs and other modules in main"
	@echo "     utest           Build the utest for srs"
	@echo "     install         Install srs to the prefix path"
	@echo "     uninstall       Uninstall srs from prefix path"
	@echo "To rebuild special module:"
	@echo "     st              Rebuild st-srs in objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64/st-srs"
	@echo "     ffmpeg          Rebuild ffmpeg in ./objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64/ffmpeg-4.2-fit"
	@echo "To reconfigure special depends:"
	@echo "     clean_openssl   Remove the openssl cache."
	@echo "     clean_srtp2     Remove the libsrtp2 cache."
	@echo "     clean_opus      Remove the opus cache."
	@echo "     clean_ffmpeg    Remove the FFmpeg cache."
	@echo "     clean_st        Remove the ST cache."
	@echo "For example:"
	@echo "     make"
	@echo "     make help"

doclean:
	(cd objs && rm -rf srs srs_utest )
	(cd objs && rm -rf src/* include lib)
	(mkdir -p objs/utest && cd objs/utest && rm -rf *.o *.a)

clean: clean_srs clean_modules

destroy:
	(cd objs && rm -rf Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64)

clean_srs:
	@(cd objs && rm -rf srs srs_utest)
	@(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && rm -rf include/* lib/*)
	@(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && find src -name "*.o" -delete)
	@(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && find utest -name "*.o" -delete)

clean_modules:
	@(cd objs && rm -rf )

clean_openssl:
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && rm -rf openssl*)
	@echo "Please rebuild openssl by: ./configure"

clean_srtp2:
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && rm -rf libsrtp-2.0.0)
	@echo "Please rebuild libsrtp2 by: ./configure"

clean_opus:
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && rm -rf opus-1.3.1)
	@echo "Please rebuild opus by: ./configure"

clean_ffmpeg:
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && rm -rf ffmpeg-4.2-fit)
	@echo "Please rebuild FFmpeg by: ./configure"

clean_st:
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64 && rm -rf st-srs)
	@echo "Please rebuild ST by: ./configure"

st:
	(cd objs && rm -f srs srs_utest)
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64/st-srs && $(MAKE) clean)
	(cd objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64/st-srs && env EXTRA_CFLAGS="-DMALLOC_STACK" $(MAKE) linux-debug STATIC_ONLY=yes CC=gcc AR=ar LD=ld RANDLIB=randlib CC=$(GCC) AR=$(AR) LD=$(LINK) RANDLIB=$(RANDLIB))
	@echo "Please rebuild srs by: rm -f objs/srs && make"

ffmpeg:
	(cd objs && rm -f srs srs_utest)
	(cd ./objs/Platform-Linux-3.10.0-GCC7.3.1-SRS5-x86_64/ffmpeg-4.2-fit && $(MAKE) && $(MAKE) install-libs)
	@echo "Please rebuild srs by: rm -f objs/srs && make"

server: _prepare_dir
	@echo "Build the SRS server"
	$(MAKE) -f objs/Makefile srs
	@bash objs/_srs_build_summary.sh

uninstall:
	@echo "rmdir $(SRS_PREFIX)"
	@rm -rf $(SRS_PREFIX)

install:
	@echo "Now mkdir $(__REAL_INSTALL)"
	@mkdir -p $(__REAL_INSTALL)
	@echo "Now make the http root dir"
	@mkdir -p $(__REAL_INSTALL)/objs/nginx/html
	@cp -f research/api-server/static-dir/index.html $(__REAL_INSTALL)/objs/nginx/html
	@cp -f research/players/crossdomain.xml $(__REAL_INSTALL)/objs/nginx/html
	@cp -f research/api-server/static-dir/favicon.ico $(__REAL_INSTALL)/objs/nginx/html
	@cp -Rf research/players $(__REAL_INSTALL)/objs/nginx/html/
	@cp -Rf research/console $(__REAL_INSTALL)/objs/nginx/html/
	@cp -Rf 3rdparty/signaling/www/demos $(__REAL_INSTALL)/objs/nginx/html/
	@echo "Now copy binary files"
	@mkdir -p $(__REAL_INSTALL)/objs
	@cp -f objs/srs $(__REAL_INSTALL)/objs
	@echo "Now copy srs conf files"
	@mkdir -p $(__REAL_INSTALL)/conf
	@cp -f conf/*.conf $(__REAL_INSTALL)/conf
	@cp -f conf/server.key conf/server.crt $(__REAL_INSTALL)/conf
	@echo "Now copy init.d script files"
	@mkdir -p $(__REAL_INSTALL)/etc/init.d
	@cp -f etc/init.d/srs $(__REAL_INSTALL)/etc/init.d
	@sed -i "s|^ROOT=.*|ROOT=\"$(SRS_PREFIX)\"|g" $(__REAL_INSTALL)/etc/init.d/srs
	@sed -i "s|^CONFIG=.*|CONFIG=\"$(SRS_DEFAULT_CONFIG)\"|g" $(__REAL_INSTALL)/etc/init.d/srs
	@echo "Now copy systemctl service files"
	@mkdir -p $(__REAL_INSTALL)/usr/lib/systemd/system
	@cp -f usr/lib/systemd/system/srs.service $(__REAL_INSTALL)/usr/lib/systemd/system/srs.service
	@echo ""
	@echo "@see: https://ossrs.net/lts/zh-cn/docs/v4/doc/service"

utest: server
	@echo "Ignore utest for it's disabled."

# the ./configure will generate it.
_prepare_dir:
	@mkdir -p objs
	@mkdir -p objs/src/core
	@mkdir -p objs/src/kernel
	@mkdir -p objs/src/protocol
	@mkdir -p objs/src/app
	@mkdir -p objs/src/main
	@mkdir -p objs/src/main
