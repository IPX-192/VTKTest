//#ifndef SURFACECLIPPERR_H
//#define SURFACECLIPPERR_H


//#include <QObject>
//#include <QPointer>
//#include "includeList.h"
//#include "vtkrenderer.h"

//#include <vtkPolyData.h>
//#include <vtkTransform.h>
//#include <vtkBoxWidget.h>
//#include <vtkSeedWidget.h>
//#include <vtkSmartPointer.h>
//#include <vtkSphereWidget.h>



//class SurfaceClipper : public QObject {
//    Q_OBJECT
//public:
//    enum WidgetType {// 切割方式
//        BOX,
//        SPHERE,
//        LINE
//    };
//public:
//    explicit SurfaceClipper(QObject *parent = nullptr);
//    virtual ~SurfaceClipper() override;
//    void Execute();
//    void SetEnable(const bool value);
//    void SetSurface(const vtkSmartPointer<vtkPolyData> value);
//    void SetWidgetType(const WidgetType value);
//    void SetTransform(const vtkSmartPointer<vtkTransform> value);
//    void SetInsideOut(const bool value);
//    void SetvtkRenderer(const QPointer<vtkRenderer> value);
//    vtkSmartPointer<vtkPolyData> GetSurface() const;
//    vtkSmartPointer<vtkPolyData> GetClippedSurface() const;
//    vtkSmartPointer<vtkPolyData> GetCutLines() const;
//    vtkSmartPointer<vtkTransform> GetTransForm() const;
//Q_SIGNALS:
//    void SignalClippedFinish();
//private:
//    void Initial();
//    void Display();
//    void ClipCallback();
//private Q_SLOTS:
//    void SlotKeyPressed(const QString &key);
//    void SlotSeedChanged(vtkObject *caller, unsigned long vtk_event,
//                         void *client_data, void *call_data);
//private:
//    bool first_connect_;
//    bool own_renderer_;
//    bool inside_out_;

//    QPointer<vtkRenderer> vmtk_renderer_;

//    vtkSmartPointer<vtkPolyData> surface_;
//    vtkSmartPointer<vtkPolyData> clipped_surface_;
//    vtkSmartPointer<vtkPolyData> cut_lines_;

//    vtkSmartPointer<vtkEventQtSlotConnect> vtk_connections_;
//    vtkSmartPointer<vtkSeedWidget> seed_widget_;
//    vtkSmartPointer<vtkBoxWidget> clip_box_widget_;
//    vtkSmartPointer<vtkSphereWidget> clip_sphere_widget_;
//    vtkSmartPointer<vtkTransform> transform_;

//    WidgetType widget_type_;
//};


//#endif // SURFACECLIPPERR_H
