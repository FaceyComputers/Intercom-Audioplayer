#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T15:05:25
#
#-------------------------------------------------

QT       += core gui
#QT       += multimedia
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IntercomMusicPlayer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        settings.cpp \
        extra_button.cpp \
        addtime.cpp \
    sheettomp3.cpp

HEADERS += \
        mainwindow.h \
        settings.h \
        extra_button.h \
        addtime.h \
    sheettomp3.h

FORMS += \
        mainwindow.ui \
        settings.ui \
        extra_button.ui \
        addtime.ui

RC_FILE = myapp.rc


win32: LIBS += -L$$PWD/./ -lbass

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

unix|win32: LIBS += -L$$PWD/C/ -lbass_fx

INCLUDEPATH += $$PWD/C
DEPENDPATH += $$PWD/C

CONFIG(debug, debug|release) {
    DEFINES += _DEBUG
    DESTDIR = ../taglib-debug
    OBJECTS_DIR = ./debug-o
} else {
    DESTDIR = ../taglib-release
    OBJECTS_DIR = ./release-o
}

# For ID3v2 Tags, if this is not going to get used, please get rid of them!
INCLUDEPATH += C:/Libraries/taglib-1.6.3
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/ape
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/asf
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/flac
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/mp4
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/mpc
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/mpeg
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/ogg
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/riff
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/toolkit
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/trueaudio
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/wavpack
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v1
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/ogg/flac
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/ogg/speex
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/ogg/vorbis
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/riff/aiff
INCLUDEPATH += C:/Libraries/taglib-1.6.3/taglib/riff/wav

HEADERS += C:/Libraries/taglib-1.6.3/taglib/audioproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/fileref.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/tag.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/taglib_export.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/tagunion.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ape/apefooter.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ape/apeitem.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ape/apetag.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/asf/asfattribute.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/asf/asffile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/asf/asfproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/asf/asftag.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/flac/flacfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/flac/flacproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4atom.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4coverart.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4file.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4item.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4properties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4tag.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpc/mpcfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpc/mpcproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/mpegfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/mpegheader.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/mpegproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/xingheader.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v1/id3v1genres.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v1/id3v1tag.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2extendedheader.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2footer.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2frame.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2framefactory.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2header.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2synchdata.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2tag.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/attachedpictureframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/commentsframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/popularimeterframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/privateframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/relativevolumeframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/textidentificationframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/unknownframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/urllinkframe.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/oggfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/oggpage.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/oggpageheader.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/xiphcomment.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/flac/oggflacfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/speex/speexfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/speex/speexproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/vorbis/vorbisfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/ogg/vorbis/vorbisproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/riff/rifffile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/riff/aiff/aifffile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/riff/aiff/aiffproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/riff/wav/wavfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/riff/wav/wavproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/taglib.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tbytevector.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tbytevectorlist.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tdebug.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tlist.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tmap.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tstring.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/tstringlist.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/toolkit/unicode.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/trueaudio/trueaudiofile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/trueaudio/trueaudioproperties.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/wavpack/wavpackfile.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib/wavpack/wavpackproperties.h

SOURCES += C:/Libraries/taglib-1.6.3/taglib/audioproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/fileref.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/tag.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/tagunion.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ape/apefooter.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ape/apeitem.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ape/apetag.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/asf/asfattribute.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/asf/asffile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/asf/asfproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/asf/asftag.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/flac/flacfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/flac/flacproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4atom.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4coverart.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4file.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4item.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4properties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mp4/mp4tag.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpc/mpcfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpc/mpcproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/mpegfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/mpegheader.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/mpegproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/xingheader.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v1/id3v1genres.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v1/id3v1tag.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2extendedheader.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2footer.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2frame.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2framefactory.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2header.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2synchdata.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/id3v2tag.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/attachedpictureframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/commentsframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/popularimeterframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/privateframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/relativevolumeframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/textidentificationframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/unknownframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/mpeg/id3v2/frames/urllinkframe.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/oggfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/oggpage.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/oggpageheader.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/xiphcomment.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/flac/oggflacfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/speex/speexfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/speex/speexproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/vorbis/vorbisfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/ogg/vorbis/vorbisproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/riff/rifffile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/riff/aiff/aifffile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/riff/aiff/aiffproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/riff/wav/wavfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/riff/wav/wavproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/tbytevector.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/tbytevectorlist.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/tdebug.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/tfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/tstring.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/tstringlist.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/toolkit/unicode.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/trueaudio/trueaudiofile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/trueaudio/trueaudioproperties.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/wavpack/wavpackfile.cpp
SOURCES += C:/Libraries/taglib-1.6.3/taglib/wavpack/wavpackproperties.cpp

HEADERS += C:/Libraries/taglib-1.6.3/config.h
HEADERS += C:/Libraries/taglib-1.6.3/taglib_config.h

DEFINES += MAKE_TAGLIB_LIB
DEFINES += WITH_ASF
DEFINES += WITH_MP4
