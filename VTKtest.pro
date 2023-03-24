QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    MouseInteractorStyle.cpp \
    SurfaceClipper.cpp \
    main.cpp \
    PlaneSlice.cpp

HEADERS += \
    MouseInteractorStyle.h \
    PlaneSlice.h\
    SurfaceClipper.h \
    includeList.h
FORMS += \
    PlaneSlice.ui

CONFIG(debug, debug|release) {
   VTK_DIR=E:\Project\vtk8.2\debug
}else{
   VTK_DIR=E:\Project\vtk8.2\Release
}

#CONFIG(debug, debug|release) {
#   VTK_DIR=D:\HspClient\vtk8.2\debug
#}else{
#   VTK_DIR=D:\HspClient\vtk8.2\Release
#}

INCLUDEPATH += $${VTK_DIR}\include\vtk-8.2

LIBS += -lDbgHelp

LIBS += $${VTK_DIR}\lib\vtkChartsCore-8.2.lib \
$${VTK_DIR}\lib\vtkCommonColor-8.2.lib \
$${VTK_DIR}\lib\vtkCommonComputationalGeometry-8.2.lib \
$${VTK_DIR}\lib\vtkCommonCore-8.2.lib \
$${VTK_DIR}\lib\vtkCommonDataModel-8.2.lib \
$${VTK_DIR}\lib\vtkCommonExecutionModel-8.2.lib \
$${VTK_DIR}\lib\vtkCommonMath-8.2.lib \
$${VTK_DIR}\lib\vtkCommonMisc-8.2.lib \
$${VTK_DIR}\lib\vtkCommonSystem-8.2.lib \
$${VTK_DIR}\lib\vtkCommonTransforms-8.2.lib \
$${VTK_DIR}\lib\vtkDICOMParser-8.2.lib \
$${VTK_DIR}\lib\vtkDomainsChemistry-8.2.lib \
$${VTK_DIR}\lib\vtkDomainsChemistryOpenGL2-8.2.lib \
$${VTK_DIR}\lib\vtkdoubleconversion-8.2.lib \
$${VTK_DIR}\lib\vtkexodusII-8.2.lib \
$${VTK_DIR}\lib\vtkexpat-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersAMR-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersCore-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersExtraction-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersFlowPaths-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersGeneral-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersGeneric-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersGeometry-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersHybrid-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersHyperTree-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersImaging-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersModeling-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersParallel-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersParallelImaging-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersPoints-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersProgrammable-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersSelection-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersSMP-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersSources-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersStatistics-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersTexture-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersTopology-8.2.lib \
$${VTK_DIR}\lib\vtkFiltersVerdict-8.2.lib \
$${VTK_DIR}\lib\vtkfreetype-8.2.lib \
$${VTK_DIR}\lib\vtkGeovisCore-8.2.lib \
$${VTK_DIR}\lib\vtkgl2ps-8.2.lib \
$${VTK_DIR}\lib\vtkglew-8.2.lib \
$${VTK_DIR}\lib\vtkGUISupportQt-8.2.lib \
$${VTK_DIR}\lib\vtkGUISupportQtOpenGL-8.2.lib \
$${VTK_DIR}\lib\vtkGUISupportQtSQL-8.2.lib \
$${VTK_DIR}\lib\vtkhdf5-8.2.lib \
$${VTK_DIR}\lib\vtkhdf5_hl-8.2.lib \
$${VTK_DIR}\lib\vtkImagingColor-8.2.lib \
$${VTK_DIR}\lib\vtkImagingCore-8.2.lib \
$${VTK_DIR}\lib\vtkImagingFourier-8.2.lib \
$${VTK_DIR}\lib\vtkImagingGeneral-8.2.lib \
$${VTK_DIR}\lib\vtkImagingHybrid-8.2.lib \
$${VTK_DIR}\lib\vtkImagingMath-8.2.lib \
$${VTK_DIR}\lib\vtkImagingMorphological-8.2.lib \
$${VTK_DIR}\lib\vtkImagingSources-8.2.lib \
$${VTK_DIR}\lib\vtkImagingStatistics-8.2.lib \
$${VTK_DIR}\lib\vtkImagingStencil-8.2.lib \
$${VTK_DIR}\lib\vtkInfovisCore-8.2.lib \
$${VTK_DIR}\lib\vtkInfovisLayout-8.2.lib \
$${VTK_DIR}\lib\vtkInteractionImage-8.2.lib \
$${VTK_DIR}\lib\vtkInteractionStyle-8.2.lib \
$${VTK_DIR}\lib\vtkInteractionWidgets-8.2.lib \
$${VTK_DIR}\lib\vtkIOAMR-8.2.lib \
$${VTK_DIR}\lib\vtkIOAsynchronous-8.2.lib \
$${VTK_DIR}\lib\vtkIOCityGML-8.2.lib \
$${VTK_DIR}\lib\vtkIOCore-8.2.lib \
$${VTK_DIR}\lib\vtkIOEnSight-8.2.lib \
$${VTK_DIR}\lib\vtkIOExodus-8.2.lib \
$${VTK_DIR}\lib\vtkIOExport-8.2.lib \
$${VTK_DIR}\lib\vtkIOExportOpenGL2-8.2.lib \
$${VTK_DIR}\lib\vtkIOExportPDF-8.2.lib \
$${VTK_DIR}\lib\vtkIOGeometry-8.2.lib \
$${VTK_DIR}\lib\vtkIOImage-8.2.lib \
$${VTK_DIR}\lib\vtkIOImport-8.2.lib \
$${VTK_DIR}\lib\vtkIOInfovis-8.2.lib \
$${VTK_DIR}\lib\vtkIOLegacy-8.2.lib \
$${VTK_DIR}\lib\vtkIOLSDyna-8.2.lib \
$${VTK_DIR}\lib\vtkIOMINC-8.2.lib \
$${VTK_DIR}\lib\vtkIOMovie-8.2.lib \
$${VTK_DIR}\lib\vtkIONetCDF-8.2.lib \
$${VTK_DIR}\lib\vtkIOParallel-8.2.lib \
$${VTK_DIR}\lib\vtkIOParallelXML-8.2.lib \
$${VTK_DIR}\lib\vtkIOPLY-8.2.lib \
$${VTK_DIR}\lib\vtkIOSegY-8.2.lib \
$${VTK_DIR}\lib\vtkIOSQL-8.2.lib \
$${VTK_DIR}\lib\vtkIOTecplotTable-8.2.lib \
$${VTK_DIR}\lib\vtkIOVeraOut-8.2.lib \
$${VTK_DIR}\lib\vtkIOVideo-8.2.lib \
$${VTK_DIR}\lib\vtkIOXML-8.2.lib \
$${VTK_DIR}\lib\vtkIOXMLParser-8.2.lib \
$${VTK_DIR}\lib\vtkjpeg-8.2.lib \
$${VTK_DIR}\lib\vtkjsoncpp-8.2.lib \
$${VTK_DIR}\lib\vtklibharu-8.2.lib \
$${VTK_DIR}\lib\vtklibxml2-8.2.lib \
$${VTK_DIR}\lib\vtklz4-8.2.lib \
$${VTK_DIR}\lib\vtklzma-8.2.lib \
$${VTK_DIR}\lib\vtkmetaio-8.2.lib \
$${VTK_DIR}\lib\vtkNetCDF-8.2.lib \
$${VTK_DIR}\lib\vtkogg-8.2.lib \
$${VTK_DIR}\lib\vtkParallelCore-8.2.lib \
$${VTK_DIR}\lib\vtkpng-8.2.lib \
$${VTK_DIR}\lib\vtkproj-8.2.lib \
$${VTK_DIR}\lib\vtkpugixml-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingAnnotation-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingContext2D-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingContextOpenGL2-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingCore-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingFreeType-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingGL2PSOpenGL2-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingImage-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingLabel-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingLOD-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingOpenGL2-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingQt-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingVolume-8.2.lib \
$${VTK_DIR}\lib\vtkRenderingVolumeOpenGL2-8.2.lib \
$${VTK_DIR}\lib\vtksqlite-8.2.lib \
$${VTK_DIR}\lib\vtksys-8.2.lib \
$${VTK_DIR}\lib\vtktheora-8.2.lib \
$${VTK_DIR}\lib\vtktiff-8.2.lib \
$${VTK_DIR}\lib\vtkverdict-8.2.lib \
$${VTK_DIR}\lib\vtkViewsContext2D-8.2.lib \
$${VTK_DIR}\lib\vtkViewsCore-8.2.lib \
$${VTK_DIR}\lib\vtkViewsInfovis-8.2.lib \
$${VTK_DIR}\lib\vtkViewsQt-8.2.lib \
$${VTK_DIR}\lib\vtkzlib-8.2.lib \

RESOURCES += \
    PlaneSlice.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
