#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PlaneSlice.h"
#include "includeList.h"

#include "vtkAutoInit.h"
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


class PlaneSlice : public QMainWindow
{
    Q_OBJECT

public:
    PlaneSlice(QWidget *parent = nullptr);
    ~PlaneSlice();

    void fun_posClip();
    void fun_negClip();

    //设置居中
    void setCenter();

    void cilpmodel();

    void cilp2();

    void initTest();

private:
    Ui::PlaneSliceClass ui;

    bool m_IsSlicing = false;
    bool m_isClipOk = false;
    bool running_mode = false;
    int pos_num = 0;
    float plane_pos[90];

    vtkSmartPointer<vtkAxesActor> axesActor;
    vtkSmartPointer<vtkTransform> axesTransformer;
    vtkSmartPointer<vtkRenderer> renderer;
    vtkSmartPointer<vtkActor> m_actors;
    vtkSmartPointer<vtkActor> plane_actor;
    vtkSmartPointer<vtkPlane> plane;
    vtkSmartPointer<vtkPlaneSource> planeSource;
    vtkSmartPointer<vtkPolyDataMapper> m_mapper;
    vtkSmartPointer<vtkPolyDataMapper> plane_mapper;
    vtkSmartPointer<vtkSTLReader> m_STLreader;
    vtkSmartPointer<vtkEventQtSlotConnect> vtkQTconnect;
    vtkSmartPointer<vtkRenderWindowInteractor> interactor;
    vtkSmartPointer<vtkCellPicker> picker;
    vtkSmartPointer<vtkSphereSource> point1, point2, point3;
    vtkSmartPointer<vtkActor> point1_actor, point2_actor, point3_actor;
    vtkSmartPointer<vtkPolyDataMapper> point1mapper, point2mapper, point3mapper;



    //新增
    vtkSmartPointer<vtkPoints> pointList;
    vtkSmartPointer<vtkPolyData> pointListPolyData;
    vtkSmartPointer<vtkPolyDataMapper> pointListMapper;
    vtkSmartPointer<vtkActor> pointListActor;
    vtkSmartPointer<vtkLineSource> line;
    vtkSmartPointer<vtkPolyDataMapper> lineMapper;
    vtkSmartPointer<vtkActor> lineActor;
    vtkSmartPointer<vtkSphereSource> point;
    vtkSmartPointer<vtkPolyDataMapper> pointMapper;
    vtkSmartPointer<vtkActor> pointActor;
    vtkSmartPointer<vtkCellArray> polygons;
    vtkPolyLine *polyLine;

    //新增2
    vtkSmartPointer<vtkLineSource> lineSource1, lineSource2, lineSource3;
    vtkSmartPointer<vtkPolyDataMapper> line_mapper1, line_mapper2, line_mapper3;
    vtkSmartPointer<vtkActor> lineActor1, lineActor2, lineActor3;

    vtkSmartPointer<vtkActor> clipActor;
    vtkSmartPointer<vtkClipClosedSurface> clipper;


public slots:
    void m_mouseClickEvent();

    void m_mouseClickEvent1();


};
